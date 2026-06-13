#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "OLED.h"
#include "OLED_Font.h"


/* I2C OLED (SSD1306) mapping
 * SCL -> PB12  // SCL引脚位置（软件I2C）
 * SDA -> PB13  // SDA引脚位置（软件I2C）
 * RES -> PA12 (optional, if connected)
 */
#define OLED_I2C_GPIO_RCC       RCC_APB2Periph_GPIOB
#define OLED_I2C_SCL_PORT       GPIOB
#define OLED_I2C_SDA_PORT       GPIOB
#define OLED_I2C_SCL_PIN        GPIO_Pin_12
#define OLED_I2C_SDA_PIN        GPIO_Pin_13
#define OLED_I2C_ADDRESS_DEFAULT 0x3C // 7-bit address
#define OLED_I2C_ADDRESS_ALT     0x3D // 7-bit address

#define OLED_SCL(x)             GPIO_WriteBit(OLED_I2C_SCL_PORT, OLED_I2C_SCL_PIN, (BitAction)(x))
#define OLED_SDA(x)             GPIO_WriteBit(OLED_I2C_SDA_PORT, OLED_I2C_SDA_PIN, (BitAction)(x))
#define OLED_SDA_READ()         GPIO_ReadInputDataBit(OLED_I2C_SDA_PORT, OLED_I2C_SDA_PIN)

#define OLED_RES_PORT           GPIOA
#define OLED_RES_PIN            GPIO_Pin_12
#define OLED_RES(x)             GPIO_WriteBit(OLED_RES_PORT, OLED_RES_PIN, (BitAction)(x))

#define OLED_I2C_DELAY_LOOP     30U

static uint8_t g_oled_i2c_addr_7bit = OLED_I2C_ADDRESS_DEFAULT;
static uint8_t g_oled_is_ready = 0U;
static uint8_t g_oled_last_error = OLED_ERR_NONE;
static uint16_t g_oled_ack_fail_count = 0U;

static void OLED_I2C_Delay(void)
{
	volatile uint16_t i = OLED_I2C_DELAY_LOOP;
	while (i--)
	{
		__NOP();
	}
}

static void OLED_DelayMs(uint32_t ms)
{
	uint32_t i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 8000; j++)
		{
			__NOP();
		}
	}
}

static void OLED_I2C_SDA_Output(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = OLED_I2C_SDA_PIN;
	GPIO_Init(OLED_I2C_SDA_PORT, &GPIO_InitStructure);
}

static void OLED_I2C_SDA_Input(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = OLED_I2C_SDA_PIN;
	GPIO_Init(OLED_I2C_SDA_PORT, &GPIO_InitStructure);
}

static void OLED_I2C_Start(void)
{
	OLED_I2C_SDA_Output();
	OLED_SDA(1);
	OLED_SCL(1);
	OLED_I2C_Delay();
	OLED_SDA(0);
	OLED_I2C_Delay();
	OLED_SCL(0);
}

static void OLED_I2C_Stop(void)
{
	OLED_I2C_SDA_Output();
	OLED_SCL(0);
	OLED_SDA(0);
	OLED_I2C_Delay();
	OLED_SCL(1);
	OLED_I2C_Delay();
	OLED_SDA(1);
	OLED_I2C_Delay();
}

static uint8_t OLED_I2C_WriteByte(uint8_t byte)
{
	uint8_t i;
	uint8_t ack;
	for (i = 0; i < 8; i++)
	{
		OLED_SDA((byte & 0x80) != 0);
		OLED_I2C_Delay();
		OLED_SCL(1);
		OLED_I2C_Delay();
		OLED_SCL(0);
		byte <<= 1;
	}
	// ACK
	OLED_I2C_SDA_Input();
	OLED_SDA(1);
	OLED_I2C_Delay();
	OLED_SCL(1);
	OLED_I2C_Delay();
	ack = (OLED_SDA_READ() == 0);
	OLED_SCL(0);
	OLED_I2C_SDA_Output();
	if (!ack)
	{
		g_oled_ack_fail_count++;
	}
	return ack;
}

static uint8_t OLED_I2C_ProbeAddress(uint8_t addr7)
{
	uint8_t ack;
	OLED_I2C_Start();
	ack = OLED_I2C_WriteByte((uint8_t)(addr7 << 1));
	OLED_I2C_Stop();
	return ack;
}

static uint8_t OLED_WriteCommandChecked(uint8_t Command)
{
	OLED_I2C_Start();
	if (!OLED_I2C_WriteByte((uint8_t)(g_oled_i2c_addr_7bit << 1)))
	{
		OLED_I2C_Stop();
		return 0U;
	}
	if (!OLED_I2C_WriteByte(0x00))
	{
		OLED_I2C_Stop();
		return 0U;
	}
	if (!OLED_I2C_WriteByte(Command))
	{
		OLED_I2C_Stop();
		return 0U;
	}
	OLED_I2C_Stop();
	return 1U;
}

static uint8_t OLED_WriteDataChecked(uint8_t Data)
{
	OLED_I2C_Start();
	if (!OLED_I2C_WriteByte((uint8_t)(g_oled_i2c_addr_7bit << 1)))
	{
		OLED_I2C_Stop();
		return 0U;
	}
	if (!OLED_I2C_WriteByte(0x40))
	{
		OLED_I2C_Stop();
		return 0U;
	}
	if (!OLED_I2C_WriteByte(Data))
	{
		OLED_I2C_Stop();
		return 0U;
	}
	OLED_I2C_Stop();
	return 1U;
}

/* I2C GPIO + peripheral init */
void OLED_I2C_Init(void)
{
	RCC_APB2PeriphClockCmd(OLED_I2C_GPIO_RCC | RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = OLED_I2C_SCL_PIN | OLED_I2C_SDA_PIN;
	GPIO_Init(OLED_I2C_SCL_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_RES_PIN;
	GPIO_Init(OLED_RES_PORT, &GPIO_InitStructure);
	OLED_RES(1);

	OLED_SCL(1);
	OLED_SDA(1);
}

/**
  * @brief  Write OLED command
  * @param  Command Command byte to send
  * @retval None
  */
void OLED_WriteCommand(uint8_t Command)
{
	if (!OLED_WriteCommandChecked(Command) && g_oled_last_error == OLED_ERR_NONE)
	{
		g_oled_last_error = OLED_ERR_RUNTIME_I2C;
	}
}

/**
  * @brief  Write OLED data
  * @param  Data Data byte to send
  * @retval None
  */
void OLED_WriteData(uint8_t Data)
{
	if (!OLED_WriteDataChecked(Data) && g_oled_last_error == OLED_ERR_NONE)
	{
		g_oled_last_error = OLED_ERR_RUNTIME_I2C;
	}
}

/**
  * @brief  Set OLED cursor position
  * @param  Y Row index from top (0~7)
  * @param  X Column index from left (0~127)
  * @retval None
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					// Set Y position
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	// Set X position (high 4 bits)
	OLED_WriteCommand(0x00 | (X & 0x0F));			// Set X position (low 4 bits)
}

/**
  * @brief  Clear OLED display
  * @param  None
  * @retval None
  */
void OLED_Clear(void)
{
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for (i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

/**
  * @brief  Show one ASCII character
  * @param  Line Line index (1~4)
  * @param  Column Column index (1~16)
  * @param  Char ASCII character to display
  * @retval None
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		// Set cursor to upper half
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			// Draw upper half bytes
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	// Set cursor to lower half
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		// Draw lower half bytes
	}
}

/**
  * @brief  Show string
  * @param  Line Start line (1~4)
  * @param  Column Start column (1~16)
  * @param  String Null-terminated ASCII string
  * @retval None
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  Integer power
  * @retval X to the power of Y
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  Show unsigned decimal number
  * @param  Line Start line (1~4)
  * @param  Column Start column (1~16)
  * @param  Number Number to display
  * @param  Length Number of digits (1~10)
  * @retval None
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  Show signed decimal number
  * @param  Line Start line (1~4)
  * @param  Column Start column (1~16)
  * @param  Number Number to display
  * @param  Length Number of digits (1~10)
  * @retval None
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  Show unsigned hexadecimal number
  * @param  Line Start line (1~4)
  * @param  Column Start column (1~16)
  * @param  Number Number to display
  * @param  Length Number of hex digits (1~8)
  * @retval None
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  Show unsigned binary number
  * @param  Line Start line (1~4)
  * @param  Column Start column (1~16)
  * @param  Number Number to display
  * @param  Length Number of bits (1~16)
  * @retval None
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
  * @brief  OLED initialization
  * @param  None
  * @retval None
  */
void OLED_Init(void)
{
	g_oled_is_ready = 0U;
	g_oled_last_error = OLED_ERR_NONE;

	OLED_I2C_Init();
	OLED_DelayMs(20U);

	OLED_RES(0);
	OLED_DelayMs(20U);
	OLED_RES(1);
	OLED_DelayMs(20U);

	if (OLED_I2C_ProbeAddress(OLED_I2C_ADDRESS_DEFAULT))
	{
		g_oled_i2c_addr_7bit = OLED_I2C_ADDRESS_DEFAULT;
	}
	else if (OLED_I2C_ProbeAddress(OLED_I2C_ADDRESS_ALT))
	{
		g_oled_i2c_addr_7bit = OLED_I2C_ADDRESS_ALT;
	}
	else
	{
		g_oled_last_error = OLED_ERR_I2C_ADDR_NACK;
		return;
	}

	if (!OLED_WriteCommandChecked(0xAE))
	{
		g_oled_last_error = OLED_ERR_CMD_AE;
		return;
	}

	if (!OLED_WriteCommandChecked(0xD5) || !OLED_WriteCommandChecked(0x80) ||
		!OLED_WriteCommandChecked(0xA8) || !OLED_WriteCommandChecked(0x3F) ||
		!OLED_WriteCommandChecked(0xD3) || !OLED_WriteCommandChecked(0x00) ||
		!OLED_WriteCommandChecked(0x40) || !OLED_WriteCommandChecked(0xA1) ||
		!OLED_WriteCommandChecked(0xC8) || !OLED_WriteCommandChecked(0xDA) ||
		!OLED_WriteCommandChecked(0x12) || !OLED_WriteCommandChecked(0x81) ||
		!OLED_WriteCommandChecked(0xCF) || !OLED_WriteCommandChecked(0xD9) ||
		!OLED_WriteCommandChecked(0xF1) || !OLED_WriteCommandChecked(0xDB) ||
		!OLED_WriteCommandChecked(0x30) || !OLED_WriteCommandChecked(0xA4) ||
		!OLED_WriteCommandChecked(0xA6))
	{
		g_oled_last_error = OLED_ERR_RUNTIME_I2C;
		return;
	}

	if (!OLED_WriteCommandChecked(0x8D) || !OLED_WriteCommandChecked(0x14))
	{
		g_oled_last_error = OLED_ERR_CMD_8D;
		return;
	}

	if (!OLED_WriteCommandChecked(0xAF))
	{
		g_oled_last_error = OLED_ERR_CMD_AF;
		return;
	}

	g_oled_is_ready = 1U;
	g_oled_last_error = OLED_ERR_NONE;
	OLED_Clear();
	OLED_ShowString(1, 1, "OLED READY");
}

uint8_t OLED_IsReady(void)
{
	return g_oled_is_ready;
}

uint8_t OLED_GetInitError(void)
{
	return g_oled_last_error;
}

uint16_t OLED_GetAckFailCount(void)
{
	return g_oled_ack_fail_count;
}

uint8_t OLED_GetI2CAddress(void)
{
	return g_oled_i2c_addr_7bit;
}

/**
  * @brief  Show floating-point number (with decimal part)
  * @param  Line Start line (1~4)
  * @param  Column Start column (1~16)
  * @param  Number Number to display, e.g. 40.7
  * @param  DecimalLength Number of decimal digits, e.g. 1
  * @retval None
  */
void OLED_ShowFloatNum(uint8_t Line, uint8_t Column, float Number, uint8_t DecimalLength)
{
	// Split integer and fractional parts
	int32_t IntegerPart = Number * 10 / 10;
	int32_t DecimalPart = (int32_t)(Number * 10) % 10;
	// Show integer part
	OLED_ShowNum(Line, Column, IntegerPart, 2);
	// Show decimal point
	OLED_ShowChar(Line, Column + 2, '.');
	// Show fractional part
	OLED_ShowNum(Line, Column + 3, DecimalPart, 1);
}
