/**********************************************************
 * @ File name -> DC_bias.c
 * @ Version   -> V1.0
 * @ Date      -> 2026-01-21
 * @ Brief     -> 直流偏置(DAC)控制相关函数实现
 **********************************************************/

#include "DC_bias.h"

static uint16_t g_dc_bias_vref_mv = 3300u;

static void DC_bias_GPIOInit(uint8_t channel)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	uint16_t pin = 0u;

	if (channel & DC_BIAS_CH1)
	{
		pin |= GPIO_Pin_4;
	}
	if (channel & DC_BIAS_CH2)
	{
		pin |= GPIO_Pin_5;
	}

	if (pin == 0u)
	{
		return;
	}

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void DC_bias_Init(uint8_t channel)
{
	DAC_InitTypeDef DAC_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	DC_bias_GPIOInit(channel);

	DAC_StructInit(&DAC_InitStruct);
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_OutputBuffer = DC_BIAS_OUTPUT_BUFFER;

	if (channel & DC_BIAS_CH1)
	{
		DAC_Init(DAC_Channel_1, &DAC_InitStruct);
		DAC_Cmd(DAC_Channel_1, ENABLE);
	}
	if (channel & DC_BIAS_CH2)
	{
		DAC_Init(DAC_Channel_2, &DAC_InitStruct);
		DAC_Cmd(DAC_Channel_2, ENABLE);
	}
}

void DC_bias_SetRaw(uint8_t channel, uint16_t value)
{
	if (value > 4095u)
	{
		value = 4095u;
	}

	if (channel & DC_BIAS_CH1)
	{
		DAC_SetChannel1Data(DAC_Align_12b_R, value);
	}
	if (channel & DC_BIAS_CH2)
	{
		DAC_SetChannel2Data(DAC_Align_12b_R, value);
	}
}

void DC_bias_SetVoltage_mV(uint8_t channel, uint16_t mv)
{
	uint16_t raw = DC_bias_VoltageToRaw(mv);
	DC_bias_SetRaw(channel, raw);
}

void DC_bias_SetVref_mV(uint16_t vref_mv)
{
	if (vref_mv == 0u)
	{
		return;
	}
	g_dc_bias_vref_mv = vref_mv;
}

uint16_t DC_bias_GetVref_mV(void)
{
	return g_dc_bias_vref_mv;
}

uint16_t DC_bias_VoltageToRaw(uint16_t mv)
{
	uint32_t raw;

	if (mv >= g_dc_bias_vref_mv)
	{
		return 4095u;
	}

	raw = ((uint32_t)mv * 4095u + (g_dc_bias_vref_mv / 2u)) / g_dc_bias_vref_mv;

	if (raw > 4095u)
	{
		raw = 4095u;
	}

	return (uint16_t)raw;
}

uint16_t DC_bias_RawToVoltage_mV(uint16_t raw)
{
	uint32_t mv;

	if (raw > 4095u)
	{
		raw = 4095u;
	}

	mv = ((uint32_t)raw * g_dc_bias_vref_mv + 2047u) / 4095u;
	return (uint16_t)mv;
}
