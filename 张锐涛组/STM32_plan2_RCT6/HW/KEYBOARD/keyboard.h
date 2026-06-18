#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "DataType.h"

/* 4x4矩阵键盘模块 (STM32F103RCT6)
 *
 * 行 (输出): PB11(ROW0), PB10(ROW1), PB2(ROW2), PB1(ROW3)
 * 列 (输入): PA0(COL0), PA1(COL1), PA2(COL2), PA3(COL3)
 */

/* 行引脚 */
#define KEYB_ROW_PORT       GPIOB
#define KEYB_ROW0           GPIO_Pin_11
#define KEYB_ROW1           GPIO_Pin_10
#define KEYB_ROW2           GPIO_Pin_2
#define KEYB_ROW3           GPIO_Pin_1

/* 列引脚 */
#define KEYB_COL_PORT       GPIOA
#define KEYB_COL0           GPIO_Pin_0
#define KEYB_COL1           GPIO_Pin_1
#define KEYB_COL2           GPIO_Pin_2
#define KEYB_COL3           GPIO_Pin_3

/* 行操作宏 */
#define KEYB_ROW0_H()       GPIO_SetBits(KEYB_ROW_PORT, KEYB_ROW0)
#define KEYB_ROW0_L()       GPIO_ResetBits(KEYB_ROW_PORT, KEYB_ROW0)
#define KEYB_ROW1_H()       GPIO_SetBits(KEYB_ROW_PORT, KEYB_ROW1)
#define KEYB_ROW1_L()       GPIO_ResetBits(KEYB_ROW_PORT, KEYB_ROW1)
#define KEYB_ROW2_H()       GPIO_SetBits(KEYB_ROW_PORT, KEYB_ROW2)
#define KEYB_ROW2_L()       GPIO_ResetBits(KEYB_ROW_PORT, KEYB_ROW2)
#define KEYB_ROW3_H()       GPIO_SetBits(KEYB_ROW_PORT, KEYB_ROW3)
#define KEYB_ROW3_L()       GPIO_ResetBits(KEYB_ROW_PORT, KEYB_ROW3)

/* 按键码 */
#define KEY_NONE            0xFFU
#define KEY_0               0U
#define KEY_1               1U
#define KEY_2               2U
#define KEY_3               3U
#define KEY_4               4U
#define KEY_5               5U
#define KEY_6               6U
#define KEY_7               7U
#define KEY_8               8U
#define KEY_9               9U
#define KEY_A               10U
#define KEY_B               11U
#define KEY_C               12U
#define KEY_D               13U
#define KEY_E               14U
#define KEY_F               15U
#define KEY_SEND            0xE0U
#define KEY_MODE            0xE1U
#define KEY_CLR             0xE2U

void KEYBOARD_Init(void);
u8   KEYBOARD_Scan(void);
u8   KEYBOARD_GetKeyBlocking(void);

#endif
