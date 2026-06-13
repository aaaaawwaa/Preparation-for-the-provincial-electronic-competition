#ifndef __FPGA_IF_H
#define __FPGA_IF_H

#include "stm32f10x.h"

/*
 * STM32 ↔ FPGA 并行接口
 *
 * 引脚映射:
 *   FPGA_D[7:0]   -> PC0-PC7  (数据总线, 双向)
 *   FPGA_ADDR[2:0] -> PB2(LSB), PB3, PB4(MSB) (地址线, 输出)
 *   FPGA_CS_N     -> PC8      (片选, 低有效)
 *   FPGA_RD_N     -> PC9      (读使能, 低有效)
 *   FPGA_WR_N     -> PC10     (写使能, 低有效)
 */

/* 数据总线引脚 */
#define FPGA_DATA_PORT      GPIOC
#define FPGA_DATA_ALL       (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | \
                             GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7)

/* 控制信号引脚 */
#define FPGA_CTRL_PORT      GPIOC
#define FPGA_CS_N_PIN       GPIO_Pin_8
#define FPGA_RD_N_PIN       GPIO_Pin_9
#define FPGA_WR_N_PIN       GPIO_Pin_10

/* 地址线引脚 (PB2=addr0 LSB, PB3=addr1, PB4=addr2 MSB) */
#define FPGA_ADDR_PORT      GPIOB
#define FPGA_ADDR_PIN0      GPIO_Pin_2
#define FPGA_ADDR_PIN1      GPIO_Pin_3
#define FPGA_ADDR_PIN2      GPIO_Pin_4

#define FPGA_SetAddr(addr)  do{ \
    GPIO_WriteBit(FPGA_ADDR_PORT, FPGA_ADDR_PIN0, (BitAction)((addr) & 0x01)); \
    GPIO_WriteBit(FPGA_ADDR_PORT, FPGA_ADDR_PIN1, (BitAction)(((addr) >> 1) & 0x01)); \
    GPIO_WriteBit(FPGA_ADDR_PORT, FPGA_ADDR_PIN2, (BitAction)(((addr) >> 2) & 0x01)); \
}while(0)

#define FPGA_CS_N(x)        GPIO_WriteBit(FPGA_CTRL_PORT, FPGA_CS_N_PIN, (BitAction)(x))
#define FPGA_RD_N(x)        GPIO_WriteBit(FPGA_CTRL_PORT, FPGA_RD_N_PIN, (BitAction)(x))
#define FPGA_WR_N(x)        GPIO_WriteBit(FPGA_CTRL_PORT, FPGA_WR_N_PIN, (BitAction)(x))

/* FPGA寄存器地址 */
#define FPGA_REG_STATUS     0U   // 状态: [0]=data_valid, [1]=lock_detect
#define FPGA_REG_LPF_H      1U   // LPF输出高8位
#define FPGA_REG_LPF_L      2U   // LPF输出低8位
#define FPGA_REG_BPF_H      3U   // BPF输出高8位
#define FPGA_REG_BPF_L      4U   // BPF输出低8位
#define FPGA_REG_ASK_DATA   5U   // 2ASK解码数据

/* 初始化 */
void FPGA_IF_Init(void);

/* 基本总线操作 */
void FPGA_IF_WriteReg(uint8_t addr, uint8_t data);
uint8_t FPGA_IF_ReadReg(uint8_t addr);

/* 高级读取函数 */
uint8_t FPGA_IF_Status(void);
uint16_t FPGA_IF_ReadLPF(void);
uint16_t FPGA_IF_ReadBPF(void);
uint8_t FPGA_IF_ReadASKData(void);

/* 数据总线方向控制 */
static void FPGA_IF_DataOut(void);
static void FPGA_IF_DataIn(void);

#endif /* __FPGA_IF_H */
