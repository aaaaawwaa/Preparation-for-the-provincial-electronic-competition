/*********************************************************************************************************
* 模块名称：Main.c
* 摘    要：RX端主文件 — 2ASK信号接收解调 + OLED显示 + LED指示
* 当前版本：1.0.0
* 注    意：勾选Options for Target->Code Generation->Use MicroLIB
*********************************************************************************************************/

#include "Main.h"
#include "stm32f10x_conf.h"
#include "DataType.h"
#include "NVIC.h"
#include "SysTick.h"
#include "RCC.h"
#include "Timer.h"
#include "UART1.h"
#include "ASKDemod.h"
#include "OLED.h"
#include <stdio.h>

static u8  g_last_data[ASK_MAX_DATA_LEN];
static u8  g_last_len;
static u32 g_frame_count;

/* LED控制 */
static u8  g_led1_timer;   /* PC4: 帧闪烁剩余时间(2ms单位), 0=熄灭 */
static u8  g_has_carrier;  /* 载波检测标志 */
static u16 g_dbg_timer;     /* 调试打印间隔(2ms单位) */

static void InitSoftware(void);
static void InitHardware(void);
static void Proc2msTask(void);
static void Proc1SecTask(void);
static void InitLED_RX(void);
static void LED1_Blink(void);      /* PC4帧到达短闪 */
static void LED2_Set(u8 on);       /* PC5载波指示 */

/* ================================================================
 * LED控制 (PC4=帧闪, PC5=载波)
 * ================================================================ */
static void InitLED_RX(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_SetBits(GPIOC, GPIO_Pin_4);    /* LED1(PC4): 初始灭 */
    GPIO_ResetBits(GPIOC, GPIO_Pin_5);  /* LED2(PC5): 初始灭 */
}

static void LED1_Blink(void)
{
    g_led1_timer = 50;  /* 50*2ms=100ms点亮 */
    GPIO_ResetBits(GPIOC, GPIO_Pin_4);  /* 开LED1 (低电平亮) */
}

static void LED2_Set(u8 on)
{
    if (on)
        GPIO_ResetBits(GPIOC, GPIO_Pin_5);  /* 开LED2 */
    else
        GPIO_SetBits(GPIOC, GPIO_Pin_5);    /* 关LED2 */
}

/* ================================================================
 * OLED 显示更新
 * ================================================================ */
/* BCD解压: 将[0x21,0x43]还原为[1,2,3,4], 返回解压后字节数 */
static u8 bcd_unpack(const u8 *src, u8 src_len, u8 *dst, u8 dst_max)
{
    u8 di = 0, si;
    for (si = 0; si < src_len && di + 1 < dst_max; si++) {
        u8 hi = (src[si] >> 4) & 0x0F;
        u8 lo = src[si] & 0x0F;
        if (hi <= 9) dst[di++] = hi;
        if (lo <= 9 && di < dst_max) dst[di++] = lo;
    }
    return di;
}

/* 判断是否为BCD编码: 所有半字节 <= 9 */
static u8 is_bcd_data(const u8 *data, u8 len)
{
    u8 i;
    for (i = 0; i < len; i++) {
        if (((data[i] >> 4) & 0x0F) > 9) return 0;
        if ((data[i] & 0x0F) > 9) return 0;
    }
    return 1;
}

static void OLED_Update(void)
{
    char line[17];
    u8 i, pos;
    OLED_Clear();
    OLED_ShowString(0, 0, "2ASK RX Ready");

    if (g_last_len > 0 && is_bcd_data(g_last_data, g_last_len)) {
        /* BCD解压显示: 1 2 3 4 */
        u8 unpacked[16];
        u8 unpack_len = bcd_unpack(g_last_data, g_last_len, unpacked, 16);
        OLED_ShowString(0, 2, "Data:");
        pos = 0;
        for (i = 0; i < unpack_len && pos < 15; i++) {
            line[pos++] = '0' + unpacked[i];
            line[pos++] = ' ';
        }
        if (pos > 0) pos--;
        line[pos] = '\0';
        OLED_ShowString(36, 2, line);
    } else if (g_last_len > 0) {
        OLED_ShowString(0, 2, "Hex:");
        OLED_ShowHex(36, 2, g_last_data, g_last_len > 8 ? 8 : g_last_len);
        if (g_last_len > 8) {
            OLED_ShowHex(0, 3, g_last_data + 8, g_last_len - 8);
        }
    } else {
        OLED_ShowString(0, 2, "Waiting...");
    }

    OLED_ShowString(0, 5, "Frames:");
    OLED_ShowNum(54, 5, g_frame_count, 5);

    OLED_ShowString(0, 7, g_has_carrier ? "SIG:OK" : "SIG:---");
    OLED_Refresh();
}

/* ================================================================
 * 主逻辑
 * ================================================================ */
static void InitSoftware(void)
{
    u8 i;
    for (i = 0; i < ASK_MAX_DATA_LEN; i++) g_last_data[i] = 0;
    g_last_len    = 0;
    g_frame_count = 0;
    g_led1_timer  = 0;
    g_has_carrier = 0;
    g_dbg_timer   = 0;
}

static void InitHardware(void)
{
    SystemInit();
    InitRCC();
    InitNVIC();
    InitUART1(115200);
    InitTimer();
    InitSysTick();
    InitLED_RX();        /* PC4+PC5 LED */
    OLED_Init();         /* SPI2 OLED */
    ASKDemod_Init();     /* PA1 ADC + 2ASK解调 */
}

static void Proc2msTask(void)
{
    if (Get2msFlag())
    {
        /* LED1 帧闪烁控制 */
        if (g_led1_timer > 0) {
            g_led1_timer--;
            if (g_led1_timer == 0)
                GPIO_SetBits(GPIOC, GPIO_Pin_4);  /* 关LED1 */
        }

        /* 载波实时检测 + LED2实时更新 (每2ms) */
        g_has_carrier = ASKDemod_GetCarrier();
        LED2_Set(g_has_carrier);

        /* 实时检测新帧 (不等1秒轮询, 收到立即刷新OLED) */
        {
            u8 buf[ASK_MAX_DATA_LEN];
            u8 len;
            if (ASKDemod_GetFrame(buf, &len))
            {
                u8 i;
                printf("[RX#%u] %d bytes: ",
                       (unsigned int)g_frame_count + 1, len);
                for (i = 0; i < len; i++) printf("%02X ", buf[i]);
                printf("\r\n");

                g_last_len = len;
                for (i = 0; i < len && i < ASK_MAX_DATA_LEN; i++)
                    g_last_data[i] = buf[i];
                g_frame_count++;
                LED1_Blink();
                OLED_Update();
            }
        }

        /* 每2秒打印一次解调器状态(调试用) */
        g_dbg_timer++;
        if (g_dbg_timer >= 1000) {
            g_dbg_timer = 0;
            ASKDemod_PrintStatus();
        }

        Clr2msFlag();
    }
}

static void Proc1SecTask(void)
{
    if (Get1SecFlag())
    {
        /* 周期性刷新OLED (SIG状态已由Proc2msTask实时更新) */
        OLED_Update();
        Clr1SecFlag();
    }
}

int main(void)
{
    InitSoftware();
    InitHardware();

    printf("================================\r\n");
    printf(" 2ASK RX Ready\r\n");
    printf(" ADC: PA1 @ 2kHz\r\n");
    printf(" OLED: SPI2 (PB12-15,PC3)\r\n");
    printf(" LED1(PC4)=Frame LED2(PC5)=Signal\r\n");
    printf("================================\r\n");

    while (1) {
        Proc2msTask();
        Proc1SecTask();
    }
}
