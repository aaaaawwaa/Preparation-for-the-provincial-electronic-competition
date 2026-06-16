/*

#include "stm32f10x.h"                  // Device header

void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}



void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;
	SPI_InitStructure.SPI_CRCPolynomial=7;
	SPI_Init(SPI1,&SPI_InitStructure);
	
	SPI_Cmd(SPI1,ENABLE);

	MySPI_W_SS(1);
}

void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)!=SET);

	SPI_I2S_SendData(SPI1,ByteSend);

	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)!=SET);

	return SPI_I2S_ReceiveData(SPI1);
}



*/


#include "stm32f10x.h"  
#include "MySPI.h"

void MySPI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;
    
    // 1. 开启 GPIOA 和硬件 SPI1 的外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
    
    // 2. 配置片选引脚 CS (PA4) 为普通推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 3. 配置时钟引脚 CLK (PA5) 和 串行输出引脚 MOSI (PA7) 为复用推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 4. 硬件 SPI1 核心参数配置
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                  // STM32作主机
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;      // 设为只发送模式，精简时序
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;              // 8位字节传输
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;             // 高位在前
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; // 72MHz/128 ≈ 562kHz，无惧长杜邦线
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                     // CPOL=0 (Mode 0)
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                   // CPHA=0
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                      // 软件片选
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);
    
    SPI_Cmd(SPI1, ENABLE); // 使能硬件SPI1
    FPGA_CS_HIGH();        // 初始化片选拉高，处于空闲
}

// 专属数字打包发送函数（6字节通信帧）
void FPGA_SendPacket(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4)
{
    uint8_t i;
    uint8_t frame[6];
    
    // 封装我们和 FPGA 约定好的通信协议
    frame[0] = 0x5A; // 帧头指示器
    frame[1] = d1;   // 千位
    frame[2] = d2;   // 百位
    frame[3] = d3;   // 十位
    frame[4] = d4;   // 个位
    frame[5] = (d1 + d2 + d3 + d4) & 0xFF; // 强大的基础和校验
    
    FPGA_CS_LOW(); // 激活总线，通知 ZYNQ 开始锁存波形
    
    for(i = 0; i < 6; i++)
    {
        // 检查状态寄存器(SPI_SR)的 TXE 标志位（发送缓冲区是否为空）
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
        // 把当前字节拍入数据寄存器(SPI_DR)
        SPI_I2S_SendData(SPI1, frame[i]);
    }
    
    // 必须等待硬件将最后一个字节彻底移位传送完毕（忙标志 BSY 降零）
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    
    FPGA_CS_HIGH(); // 挂起总线，完成本次同步
}










































