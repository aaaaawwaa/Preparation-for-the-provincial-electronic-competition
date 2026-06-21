#ifndef _DAC_H_
#define _DAC_H_

#include "DataType.h"

void DAC_Test_DC(void);          // DC测试：PA4/PA5输出约1.65V
void DAC_SineWave_Init(void);    // PA4 20Hz + PA5 1kHz正弦波

void DAC_2ASK_Init(void);        // PA4输出2ASK调制信号（20Hz载波/5bps）
void DAC_2ASK_SetDigits(u8 d0, u8 d1, u8 d2, u8 d3);  // 设置4位BCD数字
void DAC_2ASK_SendData(u8 *data, u8 len);   // 发送标准帧(0xAA头, 有长度字节)
void DAC_2ASK_SendShort(u8 *data, u8 len);  // 发送短帧
void DAC_2ASK_SendDataNoCS(u8 *data, u8 len); // 无校验发送(调SendData路径)
void DAC_2ASK_CW(u8 enable);                 // 连续载波模式 1=开 0=关
void DAC_2ASK_Debug(u8 enable);              // 调试模式 1=循环发送0x55
u8   DAC_2ASK_IsBusy(void);                  // 查询发送忙状态

#endif
