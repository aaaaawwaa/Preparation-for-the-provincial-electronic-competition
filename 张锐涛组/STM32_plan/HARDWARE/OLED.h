#ifndef __OLED_H
#define __OLED_H

#define OLED_ERR_NONE              0x00U
#define OLED_ERR_I2C_ADDR_NACK     0x01U
#define OLED_ERR_CMD_AE            0x02U
#define OLED_ERR_CMD_8D            0x03U
#define OLED_ERR_CMD_AF            0x04U
#define OLED_ERR_RUNTIME_I2C       0x05U

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowFloatNum(uint8_t Line, uint8_t Column, float Number, uint8_t DecimalLength);

uint8_t OLED_IsReady(void);
uint8_t OLED_GetInitError(void);
uint16_t OLED_GetAckFailCount(void);
uint8_t OLED_GetI2CAddress(void);


#endif
