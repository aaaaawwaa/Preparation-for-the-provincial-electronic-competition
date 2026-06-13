#include "encode.h"
#include "../HARDWARE/AD9833/ad9833.h"

/* ============================================================
 * 发送端
 * ============================================================ */

static ASK_TX_State g_tx_state = ASK_TX_IDLE;
static uint8_t g_tx_byte = 0;
static uint8_t g_tx_bit_idx = 0;
static uint8_t g_tx_data[ASK_MAX_DATA_LEN + 4]; /* header + len + data + checksum */
static uint8_t g_tx_data_len = 0;
static uint8_t g_tx_data_pos = 0;
static uint16_t g_tx_tick = 0;

void ENCODE_Init(void)
{
    g_tx_state = ASK_TX_IDLE;
    g_tx_byte = 0;
    g_tx_bit_idx = 0;
}

/*
 * 发送单字节 (UART-like: start + 8bit LSB + stop)
 * 在ASK_TxTicker中按位输出
 */
void ENCODE_SendByte(uint8_t byte)
{
    /* 等待当前发送完成 */
    if (g_tx_state != ASK_TX_IDLE)
        return;

    g_tx_byte = byte;
    g_tx_bit_idx = 0;
    g_tx_tick = 0;
    g_tx_state = ASK_TX_START_BIT;
}

/*
 * 发送数据帧: [0xAA] [len] [data...] [checksum]
 * len = 数据长度 (不包含header/len/checksum)
 */
uint8_t ENCODE_SendData(uint8_t *data, uint8_t len)
{
    uint8_t i;
    uint8_t checksum = 0;

    if (len > ASK_MAX_DATA_LEN)
        return 0;
    if (g_tx_state != ASK_TX_IDLE)
        return 0;

    g_tx_data[0] = ASK_FRAME_HEADER;
    g_tx_data[1] = len;
    for (i = 0; i < len; i++)
    {
        g_tx_data[2 + i] = data[i];
        checksum += data[i];
    }
    g_tx_data[2 + len] = checksum;

    g_tx_data_len = len + 3; /* header + len + data + checksum */
    g_tx_data_pos = 0;
    g_tx_state = ASK_TX_IDLE;

    /* 开始发送第一个字节 */
    ENCODE_SendByte(g_tx_data[0]);
    return 1;
}

/*
 * 定时调用 (每ASK_BIT_MS毫秒一次)
 * 驱动2ASK发送状态机
 */
void ENCODE_TxTicker(void)
{
    if (g_tx_state == ASK_TX_IDLE)
    {
        AD9833_ASK_Symbol(0);
        return;
    }

    if (g_tx_state == ASK_TX_DONE)
    {
        /* 发送完成, 准备下一个字节 */
        g_tx_data_pos++;
        if (g_tx_data_pos < g_tx_data_len)
        {
            ENCODE_SendByte(g_tx_data[g_tx_data_pos]);
        }
        else
        {
            g_tx_state = ASK_TX_IDLE;
            AD9833_ASK_Symbol(0);
        }
        return;
    }

    /* 状态机跳转 */
    switch (g_tx_state)
    {
        case ASK_TX_START_BIT:
            /* 发送start bit (0) -> 关闭载波 */
            AD9833_ASK_Symbol(0);
            g_tx_state = ASK_TX_DATA_BITS;
            g_tx_bit_idx = 0;
            break;

        case ASK_TX_DATA_BITS:
            /* 发送数据位 (LSB first) */
            AD9833_ASK_Symbol((g_tx_byte >> g_tx_bit_idx) & 0x01);
            g_tx_bit_idx++;
            if (g_tx_bit_idx >= 8)
                g_tx_state = ASK_TX_STOP_BIT;
            break;

        case ASK_TX_STOP_BIT:
            /* 发送stop bit (1) -> 打开载波 */
            AD9833_ASK_Symbol(1);
            g_tx_state = ASK_TX_DONE;
            break;

        default:
            break;
    }
}

/* ============================================================
 * 接收端 (从FPGA 2ASK解码输出读取)
 * ============================================================ */

static ASK_RX_State g_rx_state = ASK_RX_IDLE;
static uint8_t g_rx_byte = 0;
static uint8_t g_rx_bit_idx = 0;
static uint8_t g_rx_frame[ASK_MAX_DATA_LEN + 4];
static uint8_t g_rx_frame_pos = 0;
static uint8_t g_rx_frame_len = 0;
static uint8_t g_rx_bit_history = 0;   /* 用于检测边沿 */
static uint16_t g_rx_silence_cnt = 0;  /* 空闲超时 */

void DECODE_Init(void)
{
    g_rx_state = ASK_RX_IDLE;
    g_rx_byte = 0;
    g_rx_bit_idx = 0;
    g_rx_frame_pos = 0;
    g_rx_silence_cnt = 0;
}

/*
 * 喂一位数据 (从FPGA读取的2ASK解码输出)
 * 波特率100bps: 每10ms调用一次
 */
void DECODE_FeedBit(uint8_t bit)
{
    g_rx_bit_history = (g_rx_bit_history << 1) | (bit & 0x01);

    switch (g_rx_state)
    {
        case ASK_RX_IDLE:
            /* 检测到高电平 (载波) -> 可能是start bit的下降沿 */
            if (bit == 1)
            {
                g_rx_silence_cnt++;
                if (g_rx_silence_cnt > 30) /* 300ms无信号 */
                {
                    g_rx_silence_cnt = 0;
                    g_rx_frame_pos = 0;
                }
            }
            else
            {
                /* 检测到低电平 -> start bit? */
                if ((g_rx_bit_history & 0x03) == 0x02) /* 下降沿 */
                {
                    g_rx_state = ASK_RX_START_BIT;
                    g_rx_bit_idx = 0;
                    g_rx_byte = 0;
                    g_rx_silence_cnt = 0;
                }
            }
            break;

        case ASK_RX_START_BIT:
            /* 确认start bit仍然为0 */
            if (bit == 0)
            {
                g_rx_state = ASK_RX_DATA_BITS;
                g_rx_bit_idx = 0;
                g_rx_byte = 0;
            }
            else
            {
                g_rx_state = ASK_RX_IDLE; /* 误触发 */
            }
            break;

        case ASK_RX_DATA_BITS:
            /* 接收8位数据 (LSB first) */
            if (bit)
                g_rx_byte |= (1 << g_rx_bit_idx);
            g_rx_bit_idx++;
            if (g_rx_bit_idx >= 8)
                g_rx_state = ASK_RX_STOP_BIT;
            break;

        case ASK_RX_STOP_BIT:
            /* 验证stop bit = 1 */
            if (bit == 1)
            {
                g_rx_state = ASK_RX_DONE;
            }
            else
            {
                g_rx_state = ASK_RX_IDLE; /* 帧错误 */
            }
            break;

        case ASK_RX_DONE:
            /* 字节完成, 返回IDLE (上层通过DECODE_GetByte读取) */
            g_rx_state = ASK_RX_IDLE;
            break;

        default:
            g_rx_state = ASK_RX_IDLE;
            break;
    }
}

/*
 * 获取接收到的字节
 * 返回: 1=有数据, *byte=数据; 0=无数据
 */
uint8_t DECODE_GetByte(uint8_t *byte)
{
    if (g_rx_state != ASK_RX_DONE)
        return 0;

    *byte = g_rx_byte;
    return 1;
}

/* ============================================================
 * 工具函数
 * ============================================================ */

uint8_t ENCODE_HexToAscii(uint8_t hex)
{
    if (hex <= 9) return '0' + hex;
    return 'A' + (hex - 10);
}

uint8_t ENCODE_AsciiToHex(uint8_t ascii)
{
    if (ascii >= '0' && ascii <= '9') return ascii - '0';
    if (ascii >= 'A' && ascii <= 'F') return ascii - 'A' + 10;
    if (ascii >= 'a' && ascii <= 'f') return ascii - 'a' + 10;
    return 0;
}
