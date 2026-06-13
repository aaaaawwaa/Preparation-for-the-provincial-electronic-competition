#include "fpga_if.h"
#include "delay.h"

void FPGA_IF_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 时钟使能: GPIOC(数据+控制), GPIOB(地址) */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);

    /* 数据总线 (PC0-PC7): 初始为输入模式 */
    GPIO_InitStructure.GPIO_Pin = FPGA_DATA_ALL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FPGA_DATA_PORT, &GPIO_InitStructure);

    /* 控制信号 (PC8-PC10): 推挽输出, 初始高电平 (无效状态) */
    GPIO_InitStructure.GPIO_Pin = FPGA_CS_N_PIN | FPGA_RD_N_PIN | FPGA_WR_N_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FPGA_CTRL_PORT, &GPIO_InitStructure);

    /* 地址线 (PB2-PB4): 推挽输出 */
    GPIO_InitStructure.GPIO_Pin = FPGA_ADDR_ALL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FPGA_ADDR_PORT, &GPIO_InitStructure);

    /* 初始: 全部无效 */
    FPGA_CS_N(1);
    FPGA_RD_N(1);
    FPGA_WR_N(1);
    FPGA_SetAddr(0);
}

/* 数据总线设为输出 */
static void FPGA_IF_DataOut(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = FPGA_DATA_ALL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FPGA_DATA_PORT, &GPIO_InitStructure);
}

/* 数据总线设为输入 */
static void FPGA_IF_DataIn(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = FPGA_DATA_ALL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FPGA_DATA_PORT, &GPIO_InitStructure);
}

/*
 * 向FPGA写入寄存器
 * 时序: 设置地址 → CS拉低 → 数据输出 → WR拉低 → 保持 → WR拉高 → CS拉高
 */
void FPGA_IF_WriteReg(uint8_t addr, uint8_t data)
{
    FPGA_IF_DataOut();

    /* 先设置地址, 然后CS */
    FPGA_SetAddr(addr);
    delay_us(1);
    FPGA_CS_N(0);
    delay_us(1);

    /* 输出数据到总线 */
    GPIO_Write(FPGA_DATA_PORT, (uint16_t)data);
    delay_us(1);

    /* WR脉冲 */
    FPGA_WR_N(0);
    delay_us(1);
    FPGA_WR_N(1);
    delay_us(1);

    FPGA_CS_N(1);

    FPGA_IF_DataIn();
}

/*
 * 从FPGA读取寄存器
 * 时序: 设置地址 → CS拉低 → RD拉低 → 数据建立 → 读数据 → RD拉高 → CS拉高
 */
uint8_t FPGA_IF_ReadReg(uint8_t addr)
{
    uint8_t data;

    FPGA_IF_DataIn();

    FPGA_SetAddr(addr);
    delay_us(1);
    FPGA_CS_N(0);
    delay_us(1);
    FPGA_RD_N(0);
    delay_us(2);

    data = (uint8_t)(GPIO_ReadInputData(FPGA_DATA_PORT) & 0xFFU);

    FPGA_RD_N(1);
    delay_us(1);
    FPGA_CS_N(1);

    return data;
}

/* 读状态寄存器 */
uint8_t FPGA_IF_Status(void)
{
    return FPGA_IF_ReadReg(FPGA_REG_STATUS);
}

/* 读LPF输出 */
uint16_t FPGA_IF_ReadLPF(void)
{
    uint16_t high = (uint16_t)FPGA_IF_ReadReg(FPGA_REG_LPF_H);
    uint16_t low  = (uint16_t)FPGA_IF_ReadReg(FPGA_REG_LPF_L);
    return (high << 8) | low;
}

/* 读BPF输出 */
uint16_t FPGA_IF_ReadBPF(void)
{
    uint16_t high = (uint16_t)FPGA_IF_ReadReg(FPGA_REG_BPF_H);
    uint16_t low  = (uint16_t)FPGA_IF_ReadReg(FPGA_REG_BPF_L);
    return (high << 8) | low;
}

/* 读2ASK解码数据 */
uint8_t FPGA_IF_ReadASKData(void)
{
    return FPGA_IF_ReadReg(FPGA_REG_ASK_DATA);
}
