#ifndef _OLED_H_
#define _OLED_H_

#include "DataType.h"

/* SSD1306 128x64 SPI OLED 引脚定义
 * DIN(MOSI)=PB15, RES=PB14, SCK=PB13, CS=PB12, DC=PC3 */

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowString(u8 x, u8 y, const char *str);
void OLED_ShowHex(u8 x, u8 y, u8 *data, u8 len);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 digits);
void OLED_Refresh(void);

#endif
