#ifndef _ASK_DEMOD_H_
#define _ASK_DEMOD_H_

#include "DataType.h"

/* TX端协议参数:
 * 载波: 20Hz正弦 (100采样点/周期 @ 2kHz DAC)
 * 比特率: 20bps (50ms/bit, 100采样点/bit)
 * 帧格式: 0xAA帧头 + 长度(1B) + N字节数据 + XOR校验和
 * 短帧:   0xAB帧头 + 2字节数据 + XOR校验 (固定4字节=40bit=2.0s)
 * 每字节: 起始位0 + 8位数据(LSB) + 停止位1 = 10bit
 * 帧间: 10bit静默期
 */

#define ASK_MAX_DATA_LEN    16
#define ASK_BIT_SAMPLES     100     /* 每bit采样点数 = 50ms @ 2kHz */
#define ASK_FRAME_GAP_BITS  10      /* 帧间静默bit数 (>=10确保字节同步) */

void  ASKDemod_Init(void);
void  ASKDemod_Proc(void);                       /* 在主循环中调用 */
void  ASKDemod_SetRunning(u8 on);                /* 1=运行 0=暂停 */
u8    ASKDemod_GetFrame(u8 *buf, u8 *len);       /* 获取已解调帧, 返回1=有新帧 */
u8    ASKDemod_GetCarrier(void);                 /* 返回当前载波检测状态: 1=有载波 */
void  ASKDemod_PrintStatus(void);                /* 打印解调器状态 */

#endif
