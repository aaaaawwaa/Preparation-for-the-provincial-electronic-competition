#include "ProcHostCmd.h"
#include "UART1.h"
#include <stdio.h>

/* 接收统计 */
static u32 s_rx_count;
static u32 s_rx_bytes;

void ProcRxData(u8 *data, u8 len)
{
    u8 i;
    if (data == NULL || len == 0) return;

    s_rx_count++;
    s_rx_bytes += len;

    printf("[CMD] %d bytes: ", len);
    for (i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\r\n");
}

void ProcRxPrintStats(void)
{
    printf("RX Stat: frames=%lu bytes=%lu\r\n", s_rx_count, s_rx_bytes);
}
