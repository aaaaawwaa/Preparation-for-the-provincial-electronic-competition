#ifndef __RECOGNIZE_H
#define __RECOGNIZE_H

#include "stm32f10x.h"

/* 模式枚举定义 */
typedef enum {
    MODE_AM = 0,
    MODE_FM = 1
} ReceiverMode;

/* 外部变量声明 */
extern ReceiverMode current_mode;

/* 配置宏 (可根据实际电路调试调整) */
#define CONFIRM_THRESHOLD  30    // 连续检测一致次数
#define MAD_THRESHOLD      15    // 平均绝对偏差判定 阈值 (替代原 VAR_THRESHOLD)
#define RSSI_THRESHOLD     60    // RDA5820 RSSI 有效判定阈值 (7-bit RSSI, 0~127)
#define RECOGNIZE_SW_GPIO  GPIOA // 模拟开关控制口
#define RECOGNIZE_SW_PIN   GPIO_Pin_5

/* 函数原型声明 */
void Recognize_Init(void);
void Recognize_SetMode(ReceiverMode mode);
void Update_Receiver_Logic(void);
uint16_t Calculate_Envelope_MAD(void);

/* 外部底层支撑接口声明 (需在对应的 .c 中实现) */
extern float Get_Current_Frequency(void);
extern uint16_t Get_ADC_Average(uint8_t times);
extern uint8_t RDA5820_Read_RSSI(void);
extern uint8_t RDA5820_Check_Lock(void);

#endif /* __RECOGNIZE_H */
