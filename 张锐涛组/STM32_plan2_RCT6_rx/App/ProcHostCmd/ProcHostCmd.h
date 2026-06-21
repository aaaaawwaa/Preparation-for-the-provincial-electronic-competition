#ifndef _PROC_HOST_CMD_H_
#define _PROC_HOST_CMD_H_

#include "DataType.h"

/* 接收数据处理模块 — RX端 */

void  ProcRxData(u8 *data, u8 len);    /* 处理接收到的数据 */
void  ProcRxPrintStats(void);          /* 打印接收统计 */

#endif
