/**********************************************************
 * @ File name -> DC_bias.h
 * @ Version   -> V1.0
 * @ Date      -> 2026-01-21
 * @ Brief     -> 直流偏置(DAC)控制相关函数头文件
 **********************************************************/

#ifndef _DC_BIAS_H_
#define _DC_BIAS_H_

/**********************************************************
					 外部函数头文件                        
**********************************************************/

#include "sys.h"
#include "stm32f10x_dac.h"

/**********************************************************
					DAC通道选择宏定义
**********************************************************/

/*
 * MCU DAC mapping:
 * DAC CH1 -> PA4, DAC CH2 -> PA5.
 * PA5 may conflict with mode-switch control if both functions are enabled.
 */

#define DC_BIAS_CH1			0x01u	// DAC通道1 (PA4)
#define DC_BIAS_CH2			0x02u	// DAC通道2 (PA5)
#define DC_BIAS_CH_BOTH		(DC_BIAS_CH1 | DC_BIAS_CH2)

/**********************************************************
					DAC输出缓冲配置
**********************************************************/

// 可选：DAC_OutputBuffer_Enable / DAC_OutputBuffer_Disable
#define DC_BIAS_OUTPUT_BUFFER	DAC_OutputBuffer_Enable

/**********************************************************
					可控直流偏置接口
**********************************************************/

void DC_bias_Init(uint8_t channel);
void DC_bias_SetRaw(uint8_t channel, uint16_t value);
void DC_bias_SetVoltage_mV(uint8_t channel, uint16_t mv);

void DC_bias_SetVref_mV(uint16_t vref_mv);
uint16_t DC_bias_GetVref_mV(void);

uint16_t DC_bias_VoltageToRaw(uint16_t mv);
uint16_t DC_bias_RawToVoltage_mV(uint16_t raw);

#endif
