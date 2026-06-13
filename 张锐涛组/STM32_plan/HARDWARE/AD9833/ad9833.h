#ifndef __AD9833_H
#define __AD9833_H

#include "stm32f10x.h"

/*
 * AD9833 DDS 驱动 (用于2ASK 11.5kHz载波生成)
 *
 * 引脚映射 (SPI软件模拟):
 *   FSYNC  -> PA6
 *   SCLK   -> PA7
 *   SDATA  -> PB0
 *
 * 这些引脚不与现有外设冲突 (PA6/PA7, PB0未被占用)
 */

/* 引脚定义 */
#define AD9833_FSYNC_PORT   GPIOA
#define AD9833_FSYNC_PIN    GPIO_Pin_6
#define AD9833_SCLK_PORT    GPIOA
#define AD9833_SCLK_PIN     GPIO_Pin_7
#define AD9833_SDATA_PORT   GPIOB
#define AD9833_SDATA_PIN    GPIO_Pin_0

#define AD9833_FSYNC(x)     GPIO_WriteBit(AD9833_FSYNC_PORT, AD9833_FSYNC_PIN, (BitAction)(x))
#define AD9833_SCLK(x)      GPIO_WriteBit(AD9833_SCLK_PORT, AD9833_SCLK_PIN, (BitAction)(x))
#define AD9833_SDATA(x)     GPIO_WriteBit(AD9833_SDATA_PORT, AD9833_SDATA_PIN, (BitAction)(x))

/* AD9833 控制寄存器位 */
#define AD9833_CTRL_B28     (1U << 13)  // 双字节写入
#define AD9833_CTRL_HLB     (1U << 12)  // 单字节选择
#define AD9833_CTRL_FSEL    (1U << 11)  // 频率寄存器选择 (0=FREQ0, 1=FREQ1)
#define AD9833_CTRL_PSEL    (1U << 10)  // 相位寄存器选择
#define AD9833_CTRL_RESET   (1U << 8)   // 复位 (输出为0)
#define AD9833_CTRL_SLEEP1  (1U << 7)   // DAC休眠
#define AD9833_CTRL_SLEEP12 (1U << 6)   // 时钟休眠
#define AD9833_CTRL_OPBITEN (1U << 5)   // 方波输出使能
#define AD9833_CTRL_DIV2    (1U << 3)   // 方波分频
#define AD9833_CTRL_MODE    (1U << 1)   // 输出模式 (0=正弦, 1=三角/方波)

/* 寄存器地址 */
#define AD9833_REG_FREQ0    0x2000U
#define AD9833_REG_FREQ1    0x4000U
#define AD9833_REG_PHASE0   0xC000U
#define AD9833_REG_PHASE1   0xE000U

/* 默认主时钟 25MHz */
#define AD9833_MCLK_HZ      25000000UL

/* 函数声明 */
void AD9833_Init(void);
void AD9833_Reset(void);
void AD9833_SetFrequency(uint32_t freq_hz, uint8_t reg_sel);
void AD9833_OutputSine(void);
void AD9833_OutputOff(void);
void AD9833_ASK_Symbol(uint8_t bit);  // 1=输出载波, 0=关闭
void AD9833_Write16(uint16_t data);

#endif /* __AD9833_H */
