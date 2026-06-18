#include "keyboard.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "SysTick.h"

/*
 * 4x4矩阵键盘扫描 (STM32F103RCT6)
 *
 * 按键映射:
 *   +----+----+----+----+
 *   | D  | F  | 0  | E  |  <- ROW0 (PB11)
 *   +----+----+----+----+
 *   | C  | 9  | 8  | 7  |  <- ROW1 (PB10)
 *   +----+----+----+----+
 *   | B  | 6  | 5  | 4  |  <- ROW2 (PB2)
 *   +----+----+----+----+
 *   | A  | 3  | 2  | 1  |  <- ROW3 (PB1)
 *   +----+----+----+----+
 *     ^    ^    ^    ^
 *     |    |    |    |
 *   COL0 COL1 COL2 COL3
 *   PA0  PA1  PA2  PA3
 *
 * 特殊功能: A=发送, B=模式切换, C=清除, D/E/F=功能
 */

static const u8 key_map[4][4] = {
    {KEY_D, KEY_F, KEY_0, KEY_E},
    {KEY_C, KEY_9, KEY_8, KEY_7},
    {KEY_B, KEY_6, KEY_5, KEY_4},
    {KEY_A, KEY_3, KEY_2, KEY_1},
};

void KEYBOARD_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    /* 行: 推挽输出 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = KEYB_ROW0 | KEYB_ROW1 | KEYB_ROW2 | KEYB_ROW3;
    GPIO_Init(KEYB_ROW_PORT, &GPIO_InitStructure);

    /* 列: 上拉输入 */
    GPIO_InitStructure.GPIO_Pin = KEYB_COL0 | KEYB_COL1 | KEYB_COL2 | KEYB_COL3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEYB_COL_PORT, &GPIO_InitStructure);

    /* 所有行初始置高 */
    KEYB_ROW0_H();
    KEYB_ROW1_H();
    KEYB_ROW2_H();
    KEYB_ROW3_H();
}

/*
 * 扫描矩阵键盘, 非阻塞
 * 返回: KEY_NONE (0xFF) = 无按键, 否则返回按键码
 */
u8 KEYBOARD_Scan(void)
{
    u8 row, col;
    u16 col_data;
    static u8 last_key = KEY_NONE;
    static u8 release_wait = 0;

    if (release_wait > 0)
    {
        release_wait--;
        return KEY_NONE;
    }

    for (row = 0; row < 4; row++)
    {
        /* 全部行置高 */
        KEYB_ROW0_H(); KEYB_ROW1_H(); KEYB_ROW2_H(); KEYB_ROW3_H();

        /* 当前行拉低 */
        switch (row)
        {
            case 0: KEYB_ROW0_L(); break;
            case 1: KEYB_ROW1_L(); break;
            case 2: KEYB_ROW2_L(); break;
            case 3: KEYB_ROW3_L(); break;
        }

        DelayNms(2);

        /* 读列, 找被拉低的列 */
        col_data = GPIO_ReadInputData(KEYB_COL_PORT);
        col = 0;
        if      ((col_data & KEYB_COL0) == 0) col = 0;
        else if ((col_data & KEYB_COL1) == 0) col = 1;
        else if ((col_data & KEYB_COL2) == 0) col = 2;
        else if ((col_data & KEYB_COL3) == 0) col = 3;
        else continue;

        /* 消抖确认 */
        DelayNms(20);
        col_data = GPIO_ReadInputData(KEYB_COL_PORT);
        switch (col)
        {
            case 0: if (col_data & KEYB_COL0) continue; break;
            case 1: if (col_data & KEYB_COL1) continue; break;
            case 2: if (col_data & KEYB_COL2) continue; break;
            case 3: if (col_data & KEYB_COL3) continue; break;
        }

        /* 有效按键 (不重复触发同一键) */
        if (last_key != key_map[row][col])
        {
            last_key = key_map[row][col];
            release_wait = 5;
            return key_map[row][col];
        }
    }

    last_key = KEY_NONE;
    return KEY_NONE;
}

/* 阻塞等待按键 */
u8 KEYBOARD_GetKeyBlocking(void)
{
    u8 key;
    while (1)
    {
        key = KEYBOARD_Scan();
        if (key != KEY_NONE)
            return key;
        DelayNms(10);
    }
}
