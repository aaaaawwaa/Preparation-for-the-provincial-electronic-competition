#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "MySPI.h"
#include "KeyCtrl.h"

int main(void)
{
    // 1. 各功能模块底层硬件初始化
    OLED_Init();     // 江协科技原版 OLED 初始化
    MySPI_Init();    // 优化后的硬件SPI1初始化
    KeyCtrl_Init();  // 按键交互阵列初始化
    
    // 2. 在 OLED 上绘制静态基础 UI
    OLED_ShowString(32, 0, "STM32 TX", OLED_8X16);
    OLED_Update();
    
    while (1)
    {
        KeyCtrl_Process(); // 实时轮询按键输入状态
        
        // ---- 状态机逻辑分支 1：当前处于循环轰炸状态 ----
        if (IsTransmitting == 1)
        {
            // 向 ZYNQ FPGA 不断灌入数据，时间间隔 30ms 完美契合赛题响应控制
            FPGA_SendPacket(MyDigits[0], MyDigits[1], MyDigits[2], MyDigits[3]);
            
            // 更新本地 OLED 屏的状态显示
            OLED_ShowString(0, 24, "Status: SENDING ", OLED_8X16);
        }
        // ---- 状态机逻辑分支 2：当前处于调整挂起状态 ----
        else
        {
            OLED_ShowString(0, 24, "Status: SETTING ", OLED_8X16);
            Delay_ms(10); // 降低空闲能耗
        }
        
        // ---- 数据实时界面刷新刷新 ----
        // 通过判断 CurrentSelect 的值，高亮或标记出我们当前正在修改的是哪一个数字
// 修改后的 main.c 第 31 行 OLED_Printf 替换为：
// 修改后的 main.c 第 31 行，直接用方案 C 替换：
			
//		OLED_Printf(0, 45, OLED_8X16, "Data: %c%d%c%c%d%c%c%d%c%c%d%c", 
//            (CurrentSelect == 0) ? '[' : ' ', MyDigits[0], (CurrentSelect == 0) ? ']' : ' ',
//            (CurrentSelect == 1) ? '[' : ' ', MyDigits[1], (CurrentSelect == 1) ? ']' : ' ',
//            (CurrentSelect == 2) ? '[' : ' ', MyDigits[2], (CurrentSelect == 2) ? ']' : ' ',
//            (CurrentSelect == 3) ? '[' : ' ', MyDigits[3], (CurrentSelect == 3) ? ']' : ' ');
        // ---- 数据实时界面刷新（完全无空格挨着） ----
if (CurrentSelect == 0) {
    OLED_Printf(0, 45, OLED_8X16, "Data: [%d]%d%d%d", MyDigits[0], MyDigits[1], MyDigits[2], MyDigits[3]);
}
else if (CurrentSelect == 1) {
    OLED_Printf(0, 45, OLED_8X16, "Data: %d[%d]%d%d", MyDigits[0], MyDigits[1], MyDigits[2], MyDigits[3]);
}
else if (CurrentSelect == 2) {
    OLED_Printf(0, 45, OLED_8X16, "Data: %d%d[%d]%d", MyDigits[0], MyDigits[1], MyDigits[2], MyDigits[3]);
}
else if (CurrentSelect == 3) {
    // 选在个位时
    OLED_Printf(0, 45, OLED_8X16, "Data: %d%d%d[%d]", MyDigits[0], MyDigits[1], MyDigits[2], MyDigits[3]);
}

OLED_Update(); // 统一刷入物理屏幕
		
		
		
		
		
        OLED_Update(); // 将上述后台显存数据统一刷入物理屏幕
    }
}


