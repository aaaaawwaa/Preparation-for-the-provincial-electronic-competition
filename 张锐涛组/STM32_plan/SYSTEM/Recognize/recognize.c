#include "recognize.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "RDA5820.h"
#include "math.h"

ReceiverMode current_mode = MODE_AM;
uint16_t confirm_counter = 0;
static uint8_t g_recognize_inited = 0U;

/*
 * Mode switch control mapping:
 * RECOGNIZE_SW_PIN -> analog switch control
 * High: AM path, Low: FM path.
 */

static void Recognize_SetSwitchLevel(ReceiverMode mode)
{
    if (mode == MODE_AM) {
        GPIO_SetBits(RECOGNIZE_SW_GPIO, RECOGNIZE_SW_PIN);
    } else {
        GPIO_ResetBits(RECOGNIZE_SW_GPIO, RECOGNIZE_SW_PIN);
    }
}

void Recognize_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = RECOGNIZE_SW_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RECOGNIZE_SW_GPIO, &GPIO_InitStructure);

    Recognize_SetSwitchLevel(current_mode);
    g_recognize_inited = 1U;
}

void Recognize_SetMode(ReceiverMode mode)
{
    if (g_recognize_inited == 0U) {
        Recognize_Init();
    }

    current_mode = mode;
    Recognize_SetSwitchLevel(current_mode);
}

/**
 * @brief  计算包络检波信号的平均绝对偏差 (MAD)
 * @details 相比方差计算，MAD 避免了平方运算，极大提高了实时性
 * @return uint16_t 计算得到的偏差值
 */
uint16_t Calculate_Envelope_MAD(void) {
    uint16_t adc_buffer[100];
    uint32_t sum = 0;
    uint16_t mean = 0;
    uint32_t abs_diff_sum = 0;
    
    // 1. 快速采集 100 个点
    for(int i = 0; i < 100; i++) {
        adc_buffer[i] = Get_ADC_Average(1); 
        sum += adc_buffer[i];
    }
    mean = sum / 100;
    
    // 2. 计算平均绝对偏差 (减法 + 绝对值)
    for(int i = 0; i < 100; i++) {
        if (adc_buffer[i] > mean)
            abs_diff_sum += (adc_buffer[i] - mean);
        else
            abs_diff_sum += (mean - adc_buffer[i]);
    }
    
    return (uint16_t)(abs_diff_sum / 100);
}

void Update_Receiver_Logic(void) {
    int score_fm = 0;
    int score_am = 0;

    if (g_recognize_inited == 0U) {
        Recognize_Init();
    }
    
    // --- 第一维：频率区间预判 (初筛) ---
    float freq = Get_Current_Frequency(); 
    if (freq > 27.0f) {
        score_fm += 2; // 倾向于 FM
    } else if (freq < 26.0f) {
        score_am += 2; // 倾向于 AM
    }
    
    // --- 第二维：幅度偏差检测 ---
    uint16_t mad_val = Calculate_Envelope_MAD();
    // 阈值需根据 ADC 位数调试，FM 信号非常稳定，MAD 接近 0
    if (mad_val < MAD_THRESHOLD) {
        score_fm += 3; // 幅度稳定，判定为 FM
    } else {
        score_am += 3; // 幅度剧烈变化，判定为 AM
    }
    
    // --- 第三维：RDA5820 数字状态读取 (终端确认) ---
    uint8_t rda_rssi = RDA5820_Read_RSSI(); // 假设底层已有通过 I2C 读取 RSSI 的函数
    uint8_t rda_locked = RDA5820_Check_Lock(); // 芯片锁定状态
    
    if (rda_locked && rda_rssi > RSSI_THRESHOLD) {
        score_fm += 5; // 如果芯片锁定且有信号，FM 权重极大
    }
    
    // --- 综合决策与滞后处理 ---
    ReceiverMode target_mode = (score_fm > score_am) ? MODE_FM : MODE_AM;
    
    if (current_mode != target_mode) {
        confirm_counter++;
        if (confirm_counter > CONFIRM_THRESHOLD) {
            current_mode = target_mode;
            Recognize_SetSwitchLevel(current_mode);
            confirm_counter = 0;
        }
    } else {
        confirm_counter = 0; // 状态一致则重置计数器，防止偶发干扰累积
    }
}
