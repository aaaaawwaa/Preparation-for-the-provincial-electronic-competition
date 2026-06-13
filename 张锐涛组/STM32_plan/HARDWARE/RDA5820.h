#ifndef __RDA5820_H
#define __RDA5820_H

#include "stm32f10x.h"

/* RDA5820 寄存器地址 */
#define RDA5820_R00    0x00  // 芯片 ID
#define RDA5820_R02    0x02  // 配置寄存器：DHIZ / DMUTE / MONO / ENABLE 等
#define RDA5820_R03    0x03  // 调谐寄存器：CHAN / TUNE / BAND / SPACE
#define RDA5820_R04    0x04  // 中断和音频相关控制
#define RDA5820_R05    0x05  // 搜台阈值 / LNA 输入选择 / 音量
#define RDA5820_R0A    0x0A  // 状态读取 1：STC / SF / READCHAN
#define RDA5820_R0B    0x0B  // 状态读取 2：RSSI / FM_TRUE / FM_READY
#define RDA5820_R40    0x40  // 工作模式控制（RX / TX）

/* 默认配置 */
#define RDA5820_I2C_ADDR    0x22  // RDA5820 7位地址 0x11, 8位地址写则为 0x22

/* 函数原型 */
uint8_t RDA5820_Init(void);
void RDA5820_WriteReg(uint8_t reg, uint16_t val);
uint16_t RDA5820_ReadReg(uint8_t reg);

void RDA5820_RX_Mode(void);
void RDA5820_TX_Mode(void);
void RDA5820_Band_Set(uint8_t band);
void RDA5820_Space_Set(uint8_t spc);
uint8_t RDA5820_Space_Get(void);
void RDA5820_SeekTh_Set(uint8_t seek_th);
void RDA5820_Freq_Set(uint16_t freq_10khz);
uint16_t RDA5820_Freq_Get(void);

void RDA5820_SetFreq(float freq_mhz);
uint8_t RDA5820_AutoTuneAround(float freq_mhz);
uint8_t RDA5820_Rssi_Get(void);
uint8_t RDA5820_Read_RSSI(void);
uint8_t RDA5820_Check_Lock(void);
void RDA5820_Mute_Set(uint8_t mute);
void RDA5820_Vol_Set(uint8_t vol);

#endif /* __RDA5820_H */
