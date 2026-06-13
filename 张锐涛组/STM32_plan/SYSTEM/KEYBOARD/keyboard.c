#include "keyboard.h"
#include "delay.h"

/*
 * 4x4 矩阵键盘扫描
 *
 * 按键映射:
 *   +----+----+----+----+
 *   | 1  | 2  | 3  | A  |  <- ROW0
 *   +----+----+----+----+
 *   | 4  | 5  | 6  | B  |  <- ROW1
 *   +----+----+----+----+
 *   | 7  | 8  | 9  | C  |  <- ROW2
 *   +----+----+----+----+
 *   | *  | 0  | #  | D  |  <- ROW3
 *   +----+----+----+----+
 *     ^    ^    ^    ^
 *   COL0 COL1 COL2 COL3
 *
 * 特殊功能: A=发送, B=模式切换, C=清除, D=功能
 */

/* 键值表 (行x列) */
static const uint8_t key_map[4][4] = {
    {KEY_1, KEY_2, KEY_3, KEY_A},
    {KEY_4, KEY_5, KEY_6, KEY_B},
    {KEY_7, KEY_8, KEY_9, KEY_C},
    {KEY_E, KEY_0, KEY_F, KEY_D},   /* D=E(0xE0), 0=0, #=F */
};

void KEYBOARD_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 时钟使能 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

    /* 行: 推挽输出, 初始高电平 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    /* PB8, PB9, PB1 */
    GPIO_InitStructure.GPIO_Pin = KEYB_ROW0 | KEYB_ROW1 | KEYB_ROW2;
    GPIO_Init(KEYB_ROW_PORT_H, &GPIO_InitStructure);

    /* PC11 */
    GPIO_InitStructure.GPIO_Pin = KEYB_ROW3;
    GPIO_Init(KEYB_ROW_PORT_L, &GPIO_InitStructure);

    /* 列: 上拉输入 */
    GPIO_InitStructure.GPIO_Pin = KEYB_COL0 | KEYB_COL1 | KEYB_COL2 | KEYB_COL3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEYB_COL_PORT, &GPIO_InitStructure);

    /* 所有行置高 */
    KEYB_ROW0_H();
    KEYB_ROW1_H();
    KEYB_ROW2_H();
    KEYB_ROW3_H();
}

/*
 * 扫描矩阵键盘
 * 返回: KEY_NONE (0xFF) = 无按键, 否则返回按键码
 */
uint8_t KEYBOARD_Scan(void)
{
    uint8_t row, col;
    uint16_t col_data;
    static uint8_t last_key = KEY_NONE;
    static uint8_t release_wait = 0;

    /* 去抖动 */
    if (release_wait > 0)
    {
        release_wait--;
        return KEY_NONE;
    }

    for (row = 0; row < 4; row++)
    {
        /* 将所有行置高 */
        KEYB_ROW0_H(); KEYB_ROW1_H(); KEYB_ROW2_H(); KEYB_ROW3_H();

        /* 将当前行拉低 */
        switch (row)
        {
            case 0: KEYB_ROW0_L(); break;
            case 1: KEYB_ROW1_L(); break;
            case 2: KEYB_ROW2_L(); break;
            case 3: KEYB_ROW3_L(); break;
        }

        delay_ms(2); /* 等待电平稳定 */

        /* 读取列状态 */
        col_data = GPIO_ReadInputData(KEYB_COL_PORT);

        /* 检查哪一列被拉低 */
        col = 0;
        if ((col_data & KEYB_COL0) == 0) col = 0;
        else if ((col_data & KEYB_COL1) == 0) col = 1;
        else if ((col_data & KEYB_COL2) == 0) col = 2;
        else if ((col_data & KEYB_COL3) == 0) col = 3;
        else
            continue; /* 该行无按键 */

        /* 检测到按键: 去抖动 */
        delay_ms(20);

        /* 再次确认 */
        col_data = GPIO_ReadInputData(KEYB_COL_PORT);
        switch (col)
        {
            case 0: if (col_data & KEYB_COL0) continue; break;
            case 1: if (col_data & KEYB_COL1) continue; break;
            case 2: if (col_data & KEYB_COL2) continue; break;
            case 3: if (col_data & KEYB_COL3) continue; break;
        }

        /* 按键有效 */
        if (last_key != key_map[row][col])
        {
            last_key = key_map[row][col];
            release_wait = 5; /* 防重复触发 */
            return key_map[row][col];
        }
    }

    /* 无按键: 清除last_key以允许下次按下 */
    last_key = KEY_NONE;
    return KEY_NONE;
}

/* 阻塞等待按键 */
uint8_t KEYBOARD_GetKeyBlocking(void)
{
    uint8_t key;
    while (1)
    {
        key = KEYBOARD_Scan();
        if (key != KEY_NONE)
            return key;
        delay_ms(10);
    }
}
