#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "stm32f10x.h"

/*
 * 4x4 矩阵键盘模块
 * 注意: 与FPGA数据总线分时复用(TX模式使用键盘, RX模式使用FPGA)
 *
 * 引脚映射:
 *   行 (输出): PB8(ROW0), PB9(ROW1), PB1(ROW2), PC11(ROW3)
 *   列 (输入): PC0(COL0), PC1(COL1), PC2(COL2), PC3(COL3)
 */

/* 行引脚 (输出) */
#define KEYB_ROW_PORT_H     GPIOB
#define KEYB_ROW0           GPIO_Pin_8
#define KEYB_ROW1           GPIO_Pin_9
#define KEYB_ROW2           GPIO_Pin_1
#define KEYB_ROW_PORT_L     GPIOC
#define KEYB_ROW3           GPIO_Pin_11

/* 列引脚 (输入, 上拉) */
#define KEYB_COL_PORT       GPIOC
#define KEYB_COL0           GPIO_Pin_0
#define KEYB_COL1           GPIO_Pin_1
#define KEYB_COL2           GPIO_Pin_2
#define KEYB_COL3           GPIO_Pin_3

/* 功能: 行置位/清零 */
#define KEYB_ROW0_H()       GPIO_SetBits(KEYB_ROW_PORT_H, KEYB_ROW0)
#define KEYB_ROW0_L()       GPIO_ResetBits(KEYB_ROW_PORT_H, KEYB_ROW0)
#define KEYB_ROW1_H()       GPIO_SetBits(KEYB_ROW_PORT_H, KEYB_ROW1)
#define KEYB_ROW1_L()       GPIO_ResetBits(KEYB_ROW_PORT_H, KEYB_ROW1)
#define KEYB_ROW2_H()       GPIO_SetBits(KEYB_ROW_PORT_H, KEYB_ROW2)
#define KEYB_ROW2_L()       GPIO_ResetBits(KEYB_ROW_PORT_H, KEYB_ROW2)
#define KEYB_ROW3_H()       GPIO_SetBits(KEYB_ROW_PORT_L, KEYB_ROW3)
#define KEYB_ROW3_L()       GPIO_ResetBits(KEYB_ROW_PORT_L, KEYB_ROW3)

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
#define KEY_SEND            0xE0U   /* 发送键 */
#define KEY_MODE            0xE1U   /* 模式切换 */
#define KEY_CLR             0xE2U   /* 清除 */

void KEYBOARD_Init(void);
uint8_t KEYBOARD_Scan(void);
uint8_t KEYBOARD_GetKeyBlocking(void);

#endif /* __KEYBOARD_H */
