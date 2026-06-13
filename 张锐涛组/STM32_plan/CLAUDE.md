# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

双模式信号自动识别接收系统（全国大学生电子设计竞赛），基于 **STM32F103VET6/ZET6**，支持 AM/FM/ASK 信号的接收、自动识别与解调。

## 硬件外设映射

| 外设 | 引脚 | 模块 |
|------|------|------|
| AD9851 (DDS) | PB5(D7), PB6(RST), PB7(FQ_UD), PB8(CLK) | HARDWARE/ad9851 |
| ADF4002 (PLL) | PC13(SCK), PC14(SDI), PC15(SEN) | HARDWARE/adf4002 |
| RDA5820 (FM) | PB10(SCL), PB11(SDA), I2C addr=0x22 | HARDWARE/RDA5820 |
| OLED (SSD1306) | PB12(SCL), PB13(SDA), PA12(RES), I2C addr=0x3C/0x3D | HARDWARE/OLED |
| 74HC595 | PB5(SCLK), PB6(RCLK), PB7(DATA) | HARDWARE/74HC595 |
| ADC 采样 | PA4 (ADC1_CH4) | main.c |
| TIM2 捕获 | PA0 (TIM2_CH1) | main.c |
| 模式切换 | PA5 (模拟开关控制) | SYSTEM/Recognize |
| DAC 偏置 | PA4(CH1), PA5(CH2) | SYSTEM/DC_bias |
| USART1 | PA9(TX), PA10(RX), 9600 baud | SYSTEM/usart |

**注意引脚冲突**: PB5/PB6/PB7 同时被 AD9851 和 74HC595 使用，两者不同时工作。PA5 同时是模式切换输出和 DAC CH2，按运行模式分时使用。

## 系统架构

- **USER/main.c**: 主循环，调度 TIM2 捕获测频 → 模式判断(FM/AM) → LO 计算 → AD9851 写频 → RDA5820 控制 → OLED 显示
- **SYSTEM/Recognize/**: 自动识别逻辑（频率预判 + 包络 MAD 分析 + RDA5820 RSSI/LOCK 状态）
- **HARDWARE/ad9851**: DDS 频率合成器驱动，串行模式编程
- **HARDWARE/adf4002**: PLL 频率合成器驱动
- **HARDWARE/RDA5820**: FM 接收芯片驱动，I2C 接口
- **HARDWARE/OLED**: SSD1306 OLED 驱动，软件 I2C
- **SYSTEM/DC_bias**: DAC 直流偏置控制

## 2ASK/AM 检测方案

通过 STM32 内置 ADC (采样率 10kHz) 采集包络检波后的信号，做 1024 点 FFT 分析：

1. **FFT 测频**: 汉宁窗 + 1024点 FFT，分辨率约 9.77Hz
2. **波形识别**: 计算 peak/RMS 比值区分正弦波(AM)和方波(ASK)，阈值 1.25
   - peak/RMS >= 1.25 → 正弦波 → AM
   - peak/RMS <= 1.05 → 方波 → ASK
   - 中间值带滞回
3. **基频恢复**: 检测二次谐波能量，若基频能量足够则恢复为基频
4. **Score 滞回**: 积分/滞回机制防抖动

## FM 解调方案

通过 RDA5820 芯片完成，I2C 配置为 90MHz 接收，50kHz 步进自动搜台。

## 构建说明

使用 Keil MDK (uVision) 打开 `USER/VirtualCOMPort.uvprojx` 编译。标准 ARMCC/MDK-ARM 工具链。

- 芯片: STM32F103VE/ZE
- 编译: Keil MDK v5
- 调试: JLink / STLink

## 调试输出

USART1 @ 9600 baud，输出格式：
- `CAP=xxx raw=xxx ctrl=xxx var=xxx st=x mode=FM/AM IF=xxx RF=xxx LO=xxx valid=x RSSI=x LOCK=x`
- `Waveform: peak=xxx rms=xxx ratio=x.xx is_sine=x score=x ask=x`
