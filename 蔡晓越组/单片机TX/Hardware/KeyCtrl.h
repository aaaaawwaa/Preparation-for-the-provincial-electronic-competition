#ifndef __KEYCTRL_H
#define __KEYCTRL_H

#include "stm32f10x.h"

void KeyCtrl_Init(void);
void KeyCtrl_Process(void);

// 声明全局数字包及状态变量，方便主函数调用及屏幕刷新
extern uint8_t MyDigits[4];
extern uint8_t CurrentSelect;
extern uint8_t IsTransmitting;

#endif

