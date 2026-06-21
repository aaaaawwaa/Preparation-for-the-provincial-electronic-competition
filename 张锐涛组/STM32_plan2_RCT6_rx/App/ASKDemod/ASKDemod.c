#include "ASKDemod.h"
#include "stm32f10x_conf.h"
#include "UART1.h"
#include <stdio.h>

/* ================================================================
 * 2ASK解调器 — RX端核心模块
 *
 * TX端参数: 载波20Hz(100采样/周期@2kHz), 比特率20bps(50ms/bit)
 * RX端: ADC@2kHz采样 → 能量检测 → 位判决 → 字节组装 → 帧解析
 *
 * 帧格式: 0xAA + 长度 + N数据 + XOR校验和
 * 每字节: 起始位(0) + 8数据位(LSB) + 停止位(1) = 10bit
 * ================================================================ */

/* 采样参数 */
#define SAMPLE_RATE_HZ      2000
#define BIT_SAMPLES         80        /* 40ms @ 2kHz (25bps) */
#define DC_LEVEL            2048      /* 12位DAC/ADC中心值 */
#define ENERGY_THRESHOLD    12000     /* 能量检测阈值 */

/* 解调器状态 */
#define DEMOD_IDLE          0
#define DEMOD_HUNT_START    1         /* 寻找起始位 */
#define DEMOD_COLLECT_BYTE  2         /* 收集一字节(10bit) */
#define DEMOD_FRAME_SYNC    3         /* 帧同步中 */
#define DEMOD_FRAME_DATA    4         /* 接收帧数据 */

/* 接收帧缓冲 */
static u8  g_rx_frame_buf[ASK_MAX_DATA_LEN + 4];  /* 帧头+长度+数据+校验 */
static u8  g_rx_frame_len;
static u8  g_rx_data_len;
static u8  g_rx_byte_idx;
static u8  g_rx_bit_idx;
static u8  g_rx_byte_acc;           /* 当前正在接收的字节累加器 */

/* 帧接收完毕标志 */
static u8  g_frame_ready;           /* 1=新帧就绪 */
static u8  g_frame_data[ASK_MAX_DATA_LEN];
static u8  g_frame_data_len;

/* 解调器工作状态 */
static u8  g_demod_state;
static u8  g_running;

/* 连续0位计数: 用于检测帧间隔, 达到10时强制复位状态机 */
static u8  g_consecutive_zeros;

/* 0xAB短帧接收 */
static u8  g_is_short_frame;   /* 1=正在接收0xAB短帧 */
static u8  g_short_data[3];    /* 临时: [0]=data0 [1]=data1 [2]=checksum */
static u8  g_short_idx;        /* 已收字节数 (0-3) */

/* ADC采样缓冲 */
static volatile u16 g_adc_sample;   /* DMA目标 */
static u16 g_sample_buf[BIT_SAMPLES]; /* 存放最近100个样本 */
static u16 g_sample_idx;            /* 当前写入位置 */

/* 统计 */
static u32 g_total_bits_rx;
static u32 g_total_frames_rx;
static u32 g_good_frames;
static u32 g_bad_frames;

/* 调试: 记录最近的能量值和位判决 */
static u32 g_last_energy;
static u8  g_last_bit;
static u8  g_last_8bits[8];
static u8  g_last_8bits_idx;

/* ================================================================
 * 能量计算: 100个样本的AC能量和
 * ================================================================ */
static u32 ask_calc_energy(void)
{
    u32 energy = 0;
    u8 i;
    for (i = 0; i < BIT_SAMPLES; i++) {
        i16 diff = (i16)g_sample_buf[i] - (i16)DC_LEVEL;
        if (diff < 0) diff = -diff;
        energy += diff;
    }
    return energy;
}

/* ================================================================
 * 判断当前100样本块是bit 1还是bit 0
 * ================================================================ */
static u8 ask_detect_bit(void)
{
    u32 energy = ask_calc_energy();
    u8  bit    = (energy > ENERGY_THRESHOLD) ? 1 : 0;
    g_last_energy = energy;
    g_last_bit    = bit;
    g_last_8bits[g_last_8bits_idx & 0x07] = bit;
    g_last_8bits_idx++;
    return bit;
}

/* ================================================================
 * 每收到一个bit后的处理 (UART式状态机)
 * ================================================================ */
static void ask_process_bit(u8 bit)
{
    g_total_bits_rx++;

    /* 连续0计数: 检测帧间隔, ≥10个连续0时清除帧缓冲 */
    if (bit == 0) {
        g_consecutive_zeros++;
        if (g_consecutive_zeros >= 10) {
            g_rx_frame_len = 0;     /* 清除帧状态, 等待下一帧 */
            g_is_short_frame = 0;   /* 同时清除短帧标志 */
        }
    } else {
        g_consecutive_zeros = 0;
    }

    switch (g_demod_state) {
    case DEMOD_HUNT_START:
        /* 等待起始位(0), 起始位已在当前bit消耗, 下一bit从数据位d0开始 */
        if (bit == 0) {
            g_demod_state    = DEMOD_COLLECT_BYTE;
            g_rx_bit_idx     = 1;
            g_rx_byte_acc    = 0;
        }
        break;

    case DEMOD_COLLECT_BYTE:
        if (g_rx_bit_idx >= 1 && g_rx_bit_idx <= 8) {
            /* 数据位 LSB first: bit_idx 1→bit0, 2→bit1, ... 8→bit7 */
            if (bit) g_rx_byte_acc |= (1 << (g_rx_bit_idx - 1));
        } else if (g_rx_bit_idx == 9) {
            /* 停止位应该是1 */
            if (bit == 1) {
                /* 字节接收成功, 送入帧解析 */
                u8 rx_byte = g_rx_byte_acc;

                if (g_demod_state == DEMOD_COLLECT_BYTE) {
                    /* 转换为帧解析状态 */

                    /* === 0xA1快速帧: 无长度无校验, 直收 === */
                    if (g_is_short_frame) {
                        u8 j;
                        g_short_data[g_short_idx++] = rx_byte;
                        if (g_short_idx >= g_is_short_frame) {
                            g_frame_data_len = g_is_short_frame;
                            for (j = 0; j < g_is_short_frame; j++)
                                g_frame_data[j] = g_short_data[j];
                            g_frame_ready = 1;
                            g_good_frames++;
                            g_total_frames_rx++;
                            g_is_short_frame = 0;
                        }
                    }
                    /* === 0xA1快速帧头检测: 预期2字节数据 === */
                    else if (rx_byte == 0xA1 && g_rx_frame_len == 0) {
                        g_is_short_frame = 2;
                        g_short_idx = 0;
                    }
                    /* === 标准帧: 0xAA帧头 === */
                    else if (rx_byte == 0xAA && g_rx_frame_len == 0) {
                        /* 帧头 */
                        g_rx_frame_buf[0] = rx_byte;
                        g_rx_frame_len = 1;
                    } else if (g_rx_frame_len == 1) {
                        /* 长度字节 */
                        if (rx_byte > ASK_MAX_DATA_LEN) {
                            /* 长度非法, 丢弃帧 */
                            g_rx_frame_len = 0;
                        } else {
                            g_rx_data_len = rx_byte;
                            g_rx_frame_buf[1] = rx_byte;
                            g_rx_frame_len = 2;
                            g_rx_byte_idx = 0;
                        }
                    } else if (g_rx_frame_len >= 2 &&
                               g_rx_frame_len < 2 + g_rx_data_len + 1) {
                        /* 数据字节或校验和 */
                        g_rx_frame_buf[g_rx_frame_len] = rx_byte;
                        g_rx_frame_len++;
                    }

                    /* 快速BCD交付: 数据收完且全为BCD, 不等校验 */
                    if (g_rx_frame_len >= 3 &&
                        g_rx_frame_len == (u8)(2 + g_rx_data_len)) {
                        u8 all_bcd = 1;
                        u8 k;
                        for (k = 0; k < g_rx_data_len; k++) {
                            u8 b = g_rx_frame_buf[2 + k];
                            if (((b >> 4) & 0x0F) > 9 || (b & 0x0F) > 9)
                                { all_bcd = 0; break; }
                        }
                        if (all_bcd) {
                            g_frame_data_len = g_rx_data_len;
                            for (k = 0; k < g_rx_data_len; k++)
                                g_frame_data[k] = g_rx_frame_buf[2 + k];
                            g_frame_ready = 1;
                            g_good_frames++;
                            g_total_frames_rx++;
                            g_rx_frame_len = 0;
                        }
                    }
                    /* 标准校验交付: 头(1)+长度(1)+N数据+校验(1) */
                    else if (g_rx_frame_len >= 4 &&
                        g_rx_frame_len == (u8)(2 + g_rx_data_len + 1)) {
                        /* 校验 */
                        u8 cs = 0;
                        u8 i;
                        for (i = 0; i < g_rx_frame_len - 1; i++) {
                            cs ^= g_rx_frame_buf[i];
                        }
                        if (cs == g_rx_frame_buf[g_rx_frame_len - 1]) {
                            /* 校验通过 */
                            g_frame_data_len = g_rx_data_len;
                            for (i = 0; i < g_rx_data_len; i++) {
                                g_frame_data[i] =
                                    g_rx_frame_buf[2 + i];
                            }
                            g_frame_ready = 1;
                            g_good_frames++;
                        } else {
                            g_bad_frames++;
                        }
                        g_total_frames_rx++;
                        g_rx_frame_len = 0;  /* 准备接收下一帧 */
                    }
                }
            }
            /* 回到寻找起始位状态 */
            g_demod_state = DEMOD_HUNT_START;
            break;
        }
        g_rx_bit_idx++;
        break;

    default:
        g_demod_state = DEMOD_HUNT_START;
        break;
    }
}

/* ================================================================
 * 处理一个新ADC样本
 * ================================================================ */
static void ask_process_sample(u16 sample)
{
    static u16 sample_cnt = 0;

    /* 帧间隔同步: 第10个0位时一次性重置窗口 */
    {
        static u8 was_zeros10 = 0;
        if (g_consecutive_zeros >= 10) {
            if (!was_zeros10) {
                sample_cnt = 0;
                was_zeros10 = 1;
            }
        } else {
            was_zeros10 = 0;
        }
    }

    /* 存到循环缓冲 */
    g_sample_buf[g_sample_idx] = sample;
    g_sample_idx++;
    if (g_sample_idx >= BIT_SAMPLES) {
        g_sample_idx = 0;
    }

    /* 每收集满BIT_SAMPLES个样本, 做一次bit判决 */
    sample_cnt++;
    if (sample_cnt >= BIT_SAMPLES) {
        sample_cnt = 0;
        if (g_running) {
            u8 bit = ask_detect_bit();
            ask_process_bit(bit);
        }
    }
}

/* ================================================================
 * TIM3中断: 2kHz触发, 将ADC结果送入解调器
 * ================================================================ */
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
        ask_process_sample(g_adc_sample);
    }
}

/* ================================================================
 * 硬件初始化: ADC1(PA1) + TIM3(2kHz) + DMA
 * ================================================================ */
static void ask_hw_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    ADC_InitTypeDef   ADC_InitStructure;
    DMA_InitTypeDef   DMA_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    /* === 时钟 === */
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  /* ADCCLK = 72/6 = 12MHz */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1,
                           ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* === PA1: 2ASK模拟输入 === */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* === TIM3: 2kHz触发ADC ===
     * 72MHz / (71+1) = 1MHz, 1MHz / (499+1) = 2kHz */
    TIM_TimeBaseStructure.TIM_Period        = 499;
    TIM_TimeBaseStructure.TIM_Prescaler     = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* === ADC1: 单通道规则组, TIM3触发 === */
    ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode       = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_T3_TRGO;
    ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel       = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1,
                             ADC_SampleTime_71Cycles5);

    /* === DMA1 Channel1: ADC→g_adc_sample, 循环模式 === */
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(ADC1->DR);
    DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)&g_adc_sample;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = 1;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    /* === 使能 === */
    ADC_DMACmd(ADC1, ENABLE);
    ADC_ExternalTrigConvCmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));

    DMA_Cmd(DMA1_Channel1, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

/* ================================================================
 * API
 * ================================================================ */

void ASKDemod_Init(void)
{
    u8 i;
    g_demod_state    = DEMOD_HUNT_START;
    g_running        = 1;
    g_frame_ready    = 0;
    g_sample_idx     = 0;
    g_rx_frame_len   = 0;
    g_total_bits_rx  = 0;
    g_total_frames_rx = 0;
    g_good_frames    = 0;
    g_bad_frames     = 0;
    g_last_energy    = 0;
    g_last_bit       = 0;
    g_last_8bits_idx = 0;
    for (i = 0; i < 8; i++) g_last_8bits[i] = 0;

    for (i = 0; i < BIT_SAMPLES; i++) {
        g_sample_buf[i] = DC_LEVEL;
    }
    for (i = 0; i < ASK_MAX_DATA_LEN; i++) {
        g_frame_data[i] = 0;
    }
    g_frame_data_len = 0;
    g_consecutive_zeros = 0;
    g_is_short_frame = 0;
    g_short_idx = 0;

    ask_hw_init();
}

void ASKDemod_Proc(void)
{
    /* 大部分处理在TIM3_IRQHandler中完成 */
    /* 此处可添加超时检测或其他辅助逻辑 */
}

void ASKDemod_SetRunning(u8 on)
{
    g_running = on ? 1 : 0;
}

u8 ASKDemod_GetFrame(u8 *buf, u8 *len)
{
    if (g_frame_ready && buf != NULL && len != NULL) {
        u8 i;
        *len = g_frame_data_len;
        for (i = 0; i < g_frame_data_len; i++) {
            buf[i] = g_frame_data[i];
        }
        g_frame_ready = 0;
        return 1;
    }
    return 0;
}

u8 ASKDemod_GetCarrier(void)
{
    return (ask_calc_energy() > ENERGY_THRESHOLD) ? 1 : 0;
}

void ASKDemod_PrintStatus(void)
{
    printf("RX: bits=%u frames=%u good=%u bad=%u state=%d E=%u bit=%u [%u%u%u%u%u%u%u%u]\r\n",
           (unsigned int)g_total_bits_rx, (unsigned int)g_total_frames_rx,
           (unsigned int)g_good_frames, (unsigned int)g_bad_frames,
           g_demod_state,
           (unsigned int)g_last_energy, g_last_bit,
           g_last_8bits[(g_last_8bits_idx - 8) & 0x07],
           g_last_8bits[(g_last_8bits_idx - 7) & 0x07],
           g_last_8bits[(g_last_8bits_idx - 6) & 0x07],
           g_last_8bits[(g_last_8bits_idx - 5) & 0x07],
           g_last_8bits[(g_last_8bits_idx - 4) & 0x07],
           g_last_8bits[(g_last_8bits_idx - 3) & 0x07],
           g_last_8bits[(g_last_8bits_idx - 2) & 0x07],
           g_last_8bits[(g_last_8bits_idx - 1) & 0x07]);
}
