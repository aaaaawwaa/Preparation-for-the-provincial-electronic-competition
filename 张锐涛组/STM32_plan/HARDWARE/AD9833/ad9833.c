#include "ad9833.h"
#include "delay.h"

/*
 * AD9833 DDS 驱动实现
 * 用于生成 11.5kHz 载波, 通过控制输出通断实现2ASK调制
 */

void AD9833_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 时钟使能 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    /* 配置FSYNC(PA6), SCLK(PA7), SDATA(PB0) 推挽输出 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    /* PA6, PA7 */
    GPIO_InitStructure.GPIO_Pin = AD9833_FSYNC_PIN | AD9833_SCLK_PIN;
    GPIO_Init(AD9833_FSYNC_PORT, &GPIO_InitStructure);

    /* PB0 */
    GPIO_InitStructure.GPIO_Pin = AD9833_SDATA_PIN;
    GPIO_Init(AD9833_SDATA_PORT, &GPIO_InitStructure);

    /* 空闲电平: FSYNC=1, SCLK=0, SDATA=0 */
    AD9833_FSYNC(1);
    AD9833_SCLK(0);
    AD9833_SDATA(0);

    delay_ms(10);

    /* 复位AD9833 */
    AD9833_Reset();

    /* 配置: B28=1 (双字节模式), RESET=1 (保持复位) */
    AD9833_Write16(AD9833_CTRL_B28 | AD9833_CTRL_RESET);

    /* 设置FREQ0寄存器为11.5kHz */
    AD9833_SetFrequency(11500UL, 0);

    /* 退出复位, 选择FREQ0, 正弦波输出 */
    AD9833_Write16(AD9833_CTRL_B28);
    AD9833_OutputSine();

    /* 默认关闭输出 (ASK symbol = 0) */
    AD9833_OutputOff();
}

void AD9833_Reset(void)
{
    AD9833_Write16(AD9833_CTRL_B28 | AD9833_CTRL_RESET);
    delay_ms(1);
    AD9833_Write16(AD9833_CTRL_B28);
}

/*
 * 向AD9833写入16位数据 (SPI 16-bit)
 * 时序: FSYNC拉低 → 16个SCLK上升沿移入数据 → FSYNC拉高
 */
void AD9833_Write16(uint16_t data)
{
    uint8_t i;

    AD9833_FSYNC(0);
    delay_us(1);

    for (i = 0; i < 16; i++)
    {
        /* MSB优先 */
        if (data & 0x8000U)
            AD9833_SDATA(1);
        else
            AD9833_SDATA(0);

        /* SCLK上升沿锁存数据 */
        AD9833_SCLK(1);
        delay_us(1);
        AD9833_SCLK(0);
        delay_us(1);

        data <<= 1;
    }

    AD9833_FSYNC(1);
    delay_us(1);
}

/*
 * 设置频率
 * freq_hz: 目标频率 (Hz)
 * reg_sel: 0=FREQ0, 1=FREQ1
 *
 * FREQ_REG = (freq_hz * 2^28) / MCLK
 */
void AD9833_SetFrequency(uint32_t freq_hz, uint8_t reg_sel)
{
    uint32_t freq_word;
    uint16_t reg_base;

    if (freq_hz > (AD9833_MCLK_HZ / 2UL))
    {
        freq_hz = AD9833_MCLK_HZ / 2UL;
    }

    /* 计算频率控制字 (28-bit) */
    freq_word = (uint32_t)(((uint64_t)freq_hz * (1UL << 28)) / AD9833_MCLK_HZ);
    freq_word &= 0x0FFFFFFFUL;

    reg_base = (reg_sel == 0) ? AD9833_REG_FREQ0 : AD9833_REG_FREQ1;

    /* B28=1: 先写低14位, 再写高14位 */
    /* 低14位 */
    AD9833_Write16((uint16_t)(reg_base | (freq_word & 0x3FFFU)));
    /* 高14位 */
    AD9833_Write16((uint16_t)(reg_base | ((freq_word >> 14) & 0x3FFFU)));
}

/* 正弦波输出 */
void AD9833_OutputSine(void)
{
    AD9833_Write16(AD9833_CTRL_B28);
}

/* 关闭输出 (通过复位实现输出为0) */
void AD9833_OutputOff(void)
{
    AD9833_Write16(AD9833_CTRL_B28 | AD9833_CTRL_RESET);
}

/*
 * 2ASK符号调制
 * bit=1: 输出11.5kHz载波
 * bit=0: 关闭输出
 */
void AD9833_ASK_Symbol(uint8_t bit)
{
    if (bit)
    {
        AD9833_OutputSine();
    }
    else
    {
        AD9833_OutputOff();
    }
}
