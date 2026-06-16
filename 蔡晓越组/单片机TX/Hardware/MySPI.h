#ifndef __MYSPI_H
#define __MYSPI_H

#include "stm32f10x.h"

// 软件控制片选信号线
#define FPGA_CS_LOW()   GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define FPGA_CS_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_4)

void MySPI_Init(void);
void FPGA_SendPacket(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);

#endif


