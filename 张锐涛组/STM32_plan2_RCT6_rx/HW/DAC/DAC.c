#include "DAC.h"
#include "Wave.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

#define WAVE_SIZE      100
#define ASK_TABLE_SIZE 100  // 每bit采样点数 = 100 (50ms @ 2kHz触发)
#define MAX_DATA_LEN   16   // 数据区最大字节数

// ============================================================
// DC测试
// ============================================================
void DAC_Test_DC(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    DAC_Cmd(DAC_Channel_1, ENABLE);
    DAC_Cmd(DAC_Channel_2, ENABLE);

    DAC_SetChannel1Data(DAC_Align_12b_R, 2048);
    DAC_SetChannel2Data(DAC_Align_12b_R, 2048);
}

// ============================================================
// 正弦波模式: PA4 20Hz + PA5 1kHz
// ============================================================
void DAC_SineWave_Init(void)
{
    DAC_InitTypeDef DAC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC | RCC_APB1Periph_TIM6
                           | RCC_APB1Periph_TIM7, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // TIM6: 2kHz → PA4 20Hz
    TIM_TimeBaseStructure.TIM_Period = 35999;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

    // TIM7: 100kHz → PA5 1kHz
    TIM_TimeBaseStructure.TIM_Period = 719;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM7, TIM_TRGOSource_Update);

    DAC_StructInit(&DAC_InitStructure);
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    DAC_StructInit(&DAC_InitStructure);
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T7_TRGO;
    DAC_Init(DAC_Channel_2, &DAC_InitStructure);

    DMA_DeInit(DMA2_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(DAC->DHR12R1);
    DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)GetSineWave100PointAddr();
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = WAVE_SIZE;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);

    DMA_DeInit(DMA2_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(DAC->DHR12R2);
    DMA_Init(DMA2_Channel4, &DMA_InitStructure);

    DAC_DMACmd(DAC_Channel_1, ENABLE);
    DAC_DMACmd(DAC_Channel_2, ENABLE);
    DAC_Cmd(DAC_Channel_1, ENABLE);
    DAC_Cmd(DAC_Channel_2, ENABLE);
    DMA_Cmd(DMA2_Channel3, ENABLE);
    DMA_Cmd(DMA2_Channel4, ENABLE);
    TIM_Cmd(TIM6, ENABLE);
    TIM_Cmd(TIM7, ENABLE);
}

// ============================================================
// 2ASK 模式 — PA4输出20Hz载波，20bps帧调制
// ============================================================

// 100点包络载波表 (bit=1: 缓升30点 + 持续40点 + 缓降30点, 1.50Vpp)
// 升/降采用升余弦包络: env = 0.5*(1-cos(π*n/30))
static const u16 g_ask_one[ASK_TABLE_SIZE] = {
    2048, 2048, 2049, 2052, 2058, 2067, 2080, 2098, 2122, 2150,
    2184, 2224, 2268, 2316, 2369, 2424, 2482, 2540, 2599, 2656,
    2712, 2763, 2811, 2853, 2888, 2916, 2936, 2949, 2952, 2947,
    2933, 2913, 2890, 2863, 2834, 2801, 2765, 2726, 2685, 2641,
    2595, 2546, 2496, 2444, 2390, 2335, 2279, 2222, 2164, 2106,
    2048, 1989, 1931, 1873, 1816, 1760, 1705, 1651, 1599, 1549,
    1500, 1454, 1410, 1369, 1330, 1294, 1261, 1232, 1205, 1182,
    1162, 1148, 1143, 1146, 1159, 1179, 1207, 1242, 1284, 1332,
    1383, 1439, 1496, 1555, 1613, 1671, 1726, 1779, 1827, 1871,
    1911, 1945, 1973, 1997, 2015, 2028, 2037, 2043, 2046, 2047
};

// 100点载波表 (CW模式用, 纯净20Hz正弦波 1.50Vpp)
#define CW_TABLE_SIZE 100
static const u16 g_cw_carrier[CW_TABLE_SIZE] = {
    2048, 2106, 2164, 2222, 2279, 2335, 2390, 2444, 2496, 2546,
    2595, 2641, 2685, 2726, 2765, 2801, 2834, 2863, 2890, 2913,
    2933, 2949, 2962, 2971, 2977, 2979, 2977, 2971, 2962, 2949,
    2933, 2913, 2890, 2863, 2834, 2801, 2765, 2726, 2685, 2641,
    2595, 2546, 2496, 2444, 2390, 2335, 2279, 2222, 2164, 2106,
    2048, 1989, 1931, 1873, 1816, 1760, 1705, 1651, 1599, 1549,
    1500, 1454, 1410, 1369, 1330, 1294, 1261, 1232, 1205, 1182,
    1162, 1146, 1133, 1124, 1118, 1117, 1118, 1124, 1133, 1146,
    1162, 1182, 1205, 1232, 1261, 1294, 1330, 1369, 1410, 1454,
    1500, 1549, 1599, 1651, 1705, 1760, 1816, 1873, 1931, 1989
};

// 100点零值表（bit=0时输出DC中心电平2048, 避免bit切换瞬态跳变）
static const u16 g_ask_zero[ASK_TABLE_SIZE] = {
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048
};

// 发送状态
#define STATE_IDLE    0
#define STATE_SENDING 1
#define STATE_CW      2
#define STATE_DEBUG   3

static u8 g_send_buf[2 + MAX_DATA_LEN + 1]; // 帧头+长度+N数据+校验
static u8 g_frame_len;    // 当前帧字节数
static u8 g_total_bits;   // 总bit数 (帧bit + 5静默bit)
static u8 g_bit_index;    // 当前bit位置
static u8 g_state;        // 发送状态

// 从帧数据中提取指定位
// byte_index: 帧内字节索引, bit_in_byte: 0(起始位) 1-8(数据LSB) 9(停止位)
static u8 ask_get_byte_bit(u8 byte_index, u8 bit_in_byte)
{
    if (bit_in_byte == 0) {
        return 0;  // 起始位 = 0
    } else if (bit_in_byte == 9) {
        return 1;  // 停止位 = 1
    } else {
        return (g_send_buf[byte_index] >> (bit_in_byte - 1)) & 0x01;
    }
}

// 提取当前帧位置的bit值
static u8 ask_get_bit(u8 bit_index)
{
    if (bit_index >= g_frame_len * 10) {
        return 0;  // 帧间静默期
    }
    return ask_get_byte_bit(bit_index / 10, bit_index % 10);
}

// 切换DMA源表
static void ask_switch_table(u32 addr, u16 count)
{
    DMA_Cmd(DMA2_Channel3, DISABLE);
    DMA2_Channel3->CMAR = addr;
    DMA2_Channel3->CNDTR = count;
    DMA_Cmd(DMA2_Channel3, ENABLE);
}

// 计算帧校验和 (XOR)
static void ask_update_checksum(void)
{
    u8 cs = 0;
    u8 i;
    for (i = 0; i < g_frame_len - 1; i++) {
        cs ^= g_send_buf[i];
    }
    g_send_buf[g_frame_len - 1] = cs;
}

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);

        if (g_state == STATE_CW) {
            ask_switch_table((u32)g_cw_carrier, CW_TABLE_SIZE);
            return;
        }

        if (g_state == STATE_IDLE) {
            ask_switch_table((u32)g_ask_zero, ASK_TABLE_SIZE);
            return;
        }

        // STATE_SENDING 或 STATE_DEBUG
        if (ask_get_bit(g_bit_index)) {
            ask_switch_table((u32)g_ask_one, ASK_TABLE_SIZE);
        } else {
            ask_switch_table((u32)g_ask_zero, ASK_TABLE_SIZE);
        }
        g_bit_index++;

        if (g_bit_index >= g_total_bits) {
            if (g_state == STATE_DEBUG) {
                g_bit_index = 0;  // 循环发送
            } else {
                g_state = STATE_IDLE;  // 发送完成
            }
        }
    }
}

void DAC_2ASK_Init(void)
{
    DAC_InitTypeDef DAC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // ===== 1. 时钟 =====
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC | RCC_APB1Periph_TIM6
                           | RCC_APB1Periph_TIM4, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    // ===== 2. PA4 → 模拟模式 =====
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ===== 3. TIM6: 2kHz触发 → 20Hz载波 (100采样/周期) =====
    //     72MHz / 72 / 500 = 2kHz
    TIM_TimeBaseStructure.TIM_Period = 499;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

    // ===== 4. TIM4: 20Hz → 50ms bit周期 (20bps,每bit含100个采样点) =====
    //     72MHz / 360 / 10000 = 20Hz
    TIM_TimeBaseStructure.TIM_Period = 9999;
    TIM_TimeBaseStructure.TIM_Prescaler = 359;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // ===== 5. DAC通道1: TIM6触发 =====
    DAC_StructInit(&DAC_InitStructure);
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    // ===== 6. DMA2 Channel3: 载波表 → DHR12R1, 循环模式 =====
    DMA_DeInit(DMA2_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(DAC->DHR12R1);
    DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)g_ask_zero;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = ASK_TABLE_SIZE;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);

    // ===== 7. 初始状态：空闲 =====
    g_state     = STATE_IDLE;
    g_bit_index = 0;

    // ===== 8. 使能 =====
    DAC_DMACmd(DAC_Channel_1, ENABLE);
    DAC_Cmd(DAC_Channel_1, ENABLE);
    DMA_Cmd(DMA2_Channel3, ENABLE);
    TIM_Cmd(TIM6, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

// 更新要发送的4位BCD数字（兼容旧接口）
void DAC_2ASK_SetDigits(u8 d0, u8 d1, u8 d2, u8 d3)
{
    u8 data[2];
    data[0] = (d1 << 4) | (d0 & 0x0F);
    data[1] = (d3 << 4) | (d2 & 0x0F);
    DAC_2ASK_SendData(data, 2);
}

// 发送任意数据帧
void DAC_2ASK_SendData(u8 *data, u8 len)
{
    u8 i;
    if (len > MAX_DATA_LEN) len = MAX_DATA_LEN;

    g_send_buf[0] = 0xAA;   // 帧头
    g_send_buf[1] = len;    // 数据长度
    for (i = 0; i < len; i++) {
        g_send_buf[2 + i] = data[i];
    }

    g_frame_len = 2 + len + 1;  // 帧头 + 长度 + N数据 + 校验
    ask_update_checksum();

    g_total_bits = g_frame_len * 10 + 5;  // +5bit静默期
    g_bit_index  = 0;
    g_state      = STATE_SENDING;
}

// 连续载波模式
void DAC_2ASK_CW(u8 enable)
{
    if (enable) {
        g_state = STATE_CW;
        ask_switch_table((u32)g_cw_carrier, CW_TABLE_SIZE);
    } else {
        g_state = STATE_IDLE;
        ask_switch_table((u32)g_ask_zero, ASK_TABLE_SIZE);
    }
}

// 调试模式：循环发送 0x55
void DAC_2ASK_Debug(u8 enable)
{
    if (enable) {
        u8 dbg = 0x55;
        g_send_buf[0] = 0xAA;
        g_send_buf[1] = 1;
        g_send_buf[2] = dbg;
        g_send_buf[3] = g_send_buf[0] ^ g_send_buf[1] ^ g_send_buf[2];

        g_frame_len  = 4;
        g_total_bits = g_frame_len * 10 + 5;
        g_bit_index  = 0;
        g_state      = STATE_DEBUG;
    } else {
        g_state = STATE_IDLE;
        ask_switch_table((u32)g_ask_zero, ASK_TABLE_SIZE);
    }
}

// 查询是否正在发送
u8 DAC_2ASK_IsBusy(void)
{
    return (g_state == STATE_SENDING || g_state == STATE_DEBUG) ? 1 : 0;
}
