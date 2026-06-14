/********************************************************************
 * @File    : main.c
 * @Brief   : STM32F103C8T6 4x4矩阵键盘 + 2ASK发送系统
 *           WORK_MODE 0: 键盘测试 (OLED显示按键信息)
 *           WORK_MODE 1: 2ASK发送 (键盘输入→编码→AD9851 11.5kHz 2ASK调制)
 * @Hardware: STM32F103C8T6
 *           - 键盘行: PB10(ROW0), PB9(ROW1), PB1(ROW2), PB11(ROW3)
 *           - 键盘列: PA0(COL0), PA1(COL1), PA2(COL2), PA3(COL3)
 *           - AD9851: PB5(D7), PB6(RST), PB7(FQ_UD), PB8(CLK)
 *           - OLED: PB12(SCL), PB13(SDA), I2C
 *           - 串口(调试): PA9(TX), PA10(RX) @ 9600 baud
 ********************************************************************/

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "../SYSTEM/KEYBOARD/keyboard.h"
#include "../HARDWARE/OLED.h"

/* ============================================================
 * 编译时模式选择
 *   0 = 键盘测试 (OLED显示)
 *   1 = 2ASK 发送 (键盘→编码→AD9833 + AD9851载波)
 * ============================================================ */
#define WORK_MODE               1

/* 行引脚名称表 */
static const char *row_names[4] = {"PB10", "PB9", "PB1", "PB11"};
/* 列引脚名称表 */
static const char *col_names[4] = {"PA0", "PA1", "PA2", "PA3"};

/* 按键映射表 (匹配物理接线, 行列均反向) */
static const uint8_t key_map[4][4] = {
    {KEY_D, KEY_F, KEY_0, KEY_E},
    {KEY_C, KEY_9, KEY_8, KEY_7},
    {KEY_B, KEY_6, KEY_5, KEY_4},
    {KEY_A, KEY_3, KEY_2, KEY_1},
};

static char KeyToChar(uint8_t key)
{
    if (key <= 9)       return (char)('0' + key);
    if (key == KEY_A)   return 'A';
    if (key == KEY_B)   return 'B';
    if (key == KEY_C)   return 'C';
    if (key == KEY_D)   return 'D';
    if (key == KEY_E)   return '*';
    if (key == KEY_F)   return '#';
    return '?';
}

static uint8_t FindKeyPos(uint8_t key, uint8_t *p_row, uint8_t *p_col)
{
    uint8_t r, c;
    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            if (key_map[r][c] == key)
            {
                *p_row = r;
                *p_col = c;
                return 0;
            }
        }
    }
    return 1;
}

/* ============================================================
 * 模式0: 键盘测试
 * ============================================================ */
#if WORK_MODE == 0

static void ShowInitScreen(void)
{
    if (!OLED_IsReady()) return;
    OLED_Clear();
    OLED_ShowString(1, 1, "KEY TEST");
    OLED_ShowString(2, 1, "Ready! Press any");
    OLED_ShowString(3, 1, "key to test...");
}

static void ShowKeyOnOLED(uint8_t key, uint32_t count)
{
    char line[17];
    uint8_t row, col;

    if (!OLED_IsReady()) return;

    line[0] = 'K'; line[1] = 'e'; line[2] = 'y'; line[3] = ':';
    line[4] = ' ';
    line[5] = KeyToChar(key);
    line[6] = ' '; line[7] = '('; line[8] = '0'; line[9] = 'x';
    {
        uint8_t hi = (key >> 4) & 0x0F;
        uint8_t lo = key & 0x0F;
        line[10] = (hi < 10) ? ('0' + hi) : ('A' + hi - 10);
        line[11] = (lo < 10) ? ('0' + lo) : ('A' + lo - 10);
    }
    line[12] = ')'; line[13] = '\0';
    OLED_ShowString(1, 1, line);

    if (FindKeyPos(key, &row, &col) == 0)
    {
        char row_str[5], col_str[5];
        uint8_t i;
        for (i = 0; i < 4 && row_names[row][i] != '\0'; i++)
            row_str[i] = row_names[row][i];
        row_str[i] = '\0';
        for (i = 0; i < 4 && col_names[col][i] != '\0'; i++)
            col_str[i] = col_names[col][i];
        col_str[i] = '\0';
        snprintf(line, sizeof(line), "R%d:%-4s C%d:%-4s",
                 (unsigned)row, row_str, (unsigned)col, col_str);
        OLED_ShowString(2, 1, line);
    }

    snprintf(line, sizeof(line), "Cnt:%5lu", (unsigned long)count);
    OLED_ShowString(3, 1, line);
}

static void main_key_test(void)
{
    uint8_t last_key = KEY_NONE;
    uint8_t key;
    uint32_t press_count = 0;

    delay_init(72);
    USARTx_Init(9600);
    OLED_Init();
    KEYBOARD_Init();

    ShowInitScreen();
    printf("Key test started (OLED mode)\r\n");

    while (1)
    {
        key = KEYBOARD_Scan();

        if (key != KEY_NONE && key != last_key)
        {
            press_count++;
            last_key = key;
            ShowKeyOnOLED(key, press_count);
            printf("[OK] Key=%c(0x%02X) Cnt=%lu\r\n",
                   KeyToChar(key), (unsigned)key, (unsigned long)press_count);
        }
        else if (key == KEY_NONE)
        {
            last_key = KEY_NONE;
        }

        delay_ms(10);
    }
}

#endif /* WORK_MODE == 0 */

/* ============================================================
 * 模式1: 2ASK 发送
 * ============================================================ */
#if WORK_MODE == 1

#include "../SYSTEM/ENCODE/encode.h"
#include "../HARDWARE/ad9851.h"

#define TX_BUF_SIZE  ASK_MAX_DATA_LEN

static uint8_t tx_buffer[TX_BUF_SIZE];
static uint8_t tx_buf_len = 0;
static uint8_t cw_mode = 0;    /* 连续载波模式: 1=持续输出未调制11.5kHz */
static uint8_t dbg_mode = 0;   /* 调试模式: 1=循环发送0x55 2ASK信号 */

#define DBG_BYTE  0x55U        /* 调试发送的固定字节 (01010101, 示波器上清晰可辨) */

static void TX_ShowScreen(void)
{
    if (!OLED_IsReady()) return;
    OLED_Clear();
    OLED_ShowString(1, 1, "2ASK TX Ready");
    OLED_ShowString(2, 1, "A=Send C=Clr #=Dbg");
    OLED_ShowString(3, 1, "-");
}

static void TX_ShowBuffer(void)
{
    char line[17];
    uint8_t i, pos = 0;

    if (!OLED_IsReady()) return;

    for (i = 0; i < tx_buf_len && pos < 15; i++)
    {
        line[pos++] = KeyToChar(tx_buffer[i]);
        line[pos++] = ' ';
    }
    if (pos == 0) line[pos++] = '-';
    line[pos] = '\0';
    OLED_ShowString(3, 1, line);
}

static void TX_ShowStatus(const char *msg)
{
    if (!OLED_IsReady()) return;
    OLED_ShowString(2, 1, "                ");
    OLED_ShowString(2, 1, (char *)msg);
}

/*
 * 阻塞式发送: 暂停键盘扫描, 以精确10ms间隔驱动ENCODE_TxTicker
 * 每字节约11个tick (start+8data+stop+done) = 110ms
 * 帧头+长度+数据+校验 = tx_buf_len + 3 字节
 */
static void TX_BlockingSend(void)
{
    uint16_t total_bytes;
    uint16_t max_ticks;
    uint16_t tick;

    if (tx_buf_len == 0)
        return;

    total_bytes = tx_buf_len + 3U;              /* header + len + data + checksum */
    max_ticks   = total_bytes * 12U + 5U;       /* 每字节~11tick + 余量 */

    printf("TX: sending %u bytes\r\n", (unsigned)tx_buf_len);

    ENCODE_SendData(tx_buffer, tx_buf_len);

    for (tick = 0; tick < max_ticks; tick++)
    {
        ENCODE_TxTicker();
        delay_ms(10);
    }

    printf("TX: done\r\n");
}

static void main_tx_2ask(void)
{
    uint8_t key, last_key = KEY_NONE;

    delay_init(72);
    USARTx_Init(9600);
    OLED_Init();
    KEYBOARD_Init();

    ENCODE_Init();
    ad9851_GPIOInit();

    printf("AD9851: 11.5kHz 2ASK ready\r\n");
    printf("2ASK TX mode started\r\n");

    TX_ShowScreen();

    while (1)
    {
        key = KEYBOARD_Scan();

        if (key != KEY_NONE && key != last_key)
        {
            last_key = key;

            if (key == KEY_D)
            {
                /* D键切换: 连续载波模式 开/关 */
                cw_mode = !cw_mode;
                dbg_mode = 0;  /* 互斥 */
                if (cw_mode)
                {
                    TX_ShowStatus("CW: 11.5kHz ON");
                    printf("TX: continuous wave ON (11.5kHz unmodulated)\r\n");
                }
                else
                {
                    TX_ShowScreen();
                    printf("TX: continuous wave OFF\r\n");
                }
            }
            else if (key == KEY_A)
            {
                if (tx_buf_len == 0)
                {
                    TX_ShowStatus("Buffer empty!");
                    delay_ms(500);
                    TX_ShowScreen();
                }
                else
                {
                    TX_ShowStatus("Sending...");
                    TX_BlockingSend();
                    TX_ShowScreen();
                    TX_ShowBuffer();
                }
            }
            else if (key == KEY_C)
            {
                tx_buf_len = 0;
                TX_ShowScreen();
                printf("TX: buffer cleared\r\n");
            }
            else if (key == KEY_F)
            {
                /* #键切换: 调试模式 开/关, 循环发送0x55 */
                dbg_mode = !dbg_mode;
                cw_mode = 0;  /* 互斥 */
                if (dbg_mode)
                {
                    TX_ShowStatus("Debug: 0x55 loop");
                    printf("TX: debug mode ON (sending 0x55 repeatedly)\r\n");
                }
                else
                {
                    TX_ShowScreen();
                    printf("TX: debug mode OFF\r\n");
                }
            }
            else if (!cw_mode && !dbg_mode
                     && (key == KEY_B || key == KEY_E
                         || key <= 9))
            {
                if (tx_buf_len < TX_BUF_SIZE)
                {
                    tx_buffer[tx_buf_len++] = key;
                    TX_ShowBuffer();
                    printf("TX: buffered '%c' (0x%02X) [%u/%u]\r\n",
                           KeyToChar(key), (unsigned)key,
                           (unsigned)tx_buf_len, (unsigned)TX_BUF_SIZE);
                }
            }
        }
        else if (key == KEY_NONE)
        {
            last_key = KEY_NONE;
        }

        if (cw_mode)
        {
            AD9851_ASK_Symbol(1);   /* 持续输出未调制11.5kHz载波 */
        }
        else if (dbg_mode)
        {
            ENCODE_TxTicker();      /* 驱动状态机 */
            ENCODE_SendByte(DBG_BYTE);  /* 上一字节发完后自动重启, 未完成时无操作 */
        }
        else
        {
            ENCODE_TxTicker();      /* 空闲时维持输出为0 */
        }
        delay_ms(10);
    }
}

#endif /* WORK_MODE == 1 */

/* ============================================================
 * 主函数
 * ============================================================ */
int main(void)
{
#if WORK_MODE == 0
    main_key_test();
    return 0;
#elif WORK_MODE == 1
    main_tx_2ask();
    return 0;
#else
    #error "WORK_MODE must be 0 or 1"
#endif
}
