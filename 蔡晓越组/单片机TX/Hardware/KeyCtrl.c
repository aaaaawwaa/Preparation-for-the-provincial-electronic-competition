#include "KeyCtrl.h"
#include "Delay.h"
#include "MySPI.h"

// 全局变量定义
uint8_t MyDigits[4] = {2, 0, 2, 6}; // 四位数据：默认上电显示 2026
uint8_t CurrentSelect = 0;          // 当前选中的修改位 (0:千位, 1:百位, 2:十位, 3:个位)
uint8_t IsTransmitting = 0;         // 0: 设置模式(熄灭状态)  1: 发送模式(循环发送)

void KeyCtrl_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    // 初始化 PB1 和 PB11（你原本就有的设置键）
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // 新增初始化 PA0 为上拉输入，作为我们的 [启动/停止] 复用键
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void KeyCtrl_Process(void)
{
    // ---- 按键1：切换修改的“数字位” (PB1) ----
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
        {
            if (IsTransmitting == 0) // 只有处于停止设置状态，才允许修改数值
            {
                CurrentSelect = (CurrentSelect + 1) % 4; // 在 0~3 之间轮流切换
            }
            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);
            Delay_ms(20);
        }
    }
    
    // ---- 按键2：被选中位数字 +1 循环 (PB11) ----
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
        {
            if (IsTransmitting == 0)
            {
                MyDigits[CurrentSelect] = (MyDigits[CurrentSelect] + 1) % 10; // 0~9 循环
            }
            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);
            Delay_ms(20);
        }
    }
    
    // ---- 按键3：[发送 / 停止] 复用切换控制键 (PA0) ----
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
    {
        Delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
        {
            if (IsTransmitting == 0)
            {
                IsTransmitting = 1; // 切入发送模式
            }
            else
            {
                IsTransmitting = 0; // 切回停止设置模式
                
                // 重点得分设计：按下停止键，立刻向 FPGA 发送一帧全 0xFF 的“强制熄灭指令”
                FPGA_SendPacket(0xFF, 0xFF, 0xFF, 0xFF);
            }
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0);
            Delay_ms(20);
        }
    }
}

