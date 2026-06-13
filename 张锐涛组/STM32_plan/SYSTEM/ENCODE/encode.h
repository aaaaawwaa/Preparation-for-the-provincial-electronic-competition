#ifndef __ENCODE_H
#define __ENCODE_H

#include "stm32f10x.h"

/*
 * 2ASK 编解码模块
 *
 * 编码格式: UART-like, 1 start bit (0) + 8 data bits (LSB first) + 1 stop bit (1)
 * 波特率: 100 bps (每位10ms)
 * 载波: 11.5kHz (由AD9833产生)
 *
 * 数据包格式:
 *   [帧头: 0xAA] [数据长度(1字节)] [有效数据...] [校验和]
 */

/* 2ASK通信参数 */
#define ASK_BAUD_RATE       100U        /* 波特率 (bps) */
#define ASK_BIT_MS          10U         /* 每位时间 (ms) = 1000/100 */
#define ASK_CARRIER_HZ      11500UL     /* 2ASK载波频率 */

/* 帧格式 */
#define ASK_FRAME_HEADER    0xAAU
#define ASK_MAX_DATA_LEN    16U

/* 编码状态机 */
typedef enum {
    ASK_TX_IDLE = 0,
    ASK_TX_START_BIT,
    ASK_TX_DATA_BITS,
    ASK_TX_STOP_BIT,
    ASK_TX_DONE
} ASK_TX_State;

/* 解码状态机 */
typedef enum {
    ASK_RX_IDLE = 0,
    ASK_RX_WAIT_START,
    ASK_RX_DATA_BITS,
    ASK_RX_STOP_BIT,
    ASK_RX_DONE
} ASK_RX_State;

/* 函数声明 */

/* 发送 */
void ENCODE_Init(void);
void ENCODE_SendByte(uint8_t byte);
uint8_t ENCODE_SendData(uint8_t *data, uint8_t len);
void ENCODE_TxTicker(void);     /* 定时调用 (每ASK_BIT_MS调用一次) */

/* 接收 */
void DECODE_Init(void);
void DECODE_FeedBit(uint8_t bit);   /* 从FPGA接收1位数据 */
uint8_t DECODE_GetByte(uint8_t *byte); /* 取1字节, 返回1=成功 */

/* 工具 */
uint8_t ENCODE_HexToAscii(uint8_t hex);
uint8_t ENCODE_AsciiToHex(uint8_t ascii);

#endif /* __ENCODE_H */
