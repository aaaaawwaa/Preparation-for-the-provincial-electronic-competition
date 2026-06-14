# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

基于 **STM32F103VET6/ZET6** + **FPGA** 的 2ASK/AM 混合信号收发系统（全国大学生电子设计竞赛 方案2）。

支持三种工作模式（编译时切换 `WORK_MODE`）：

- **0 (RX_LEGACY)**: 原有 STM32 接收机 (TIM2测频 + ADC/FFT + RDA5820 FM)
- **1 (TX_2ASK)**: 2ASK 发送机 (键盘输入 → 编码 → AD9833 DDS)
- **2 (RX_FPGA)**: FPGA 双路数字滤波接收 (FPGA LPF/BPF → 解码 → 显示)

## 系统架构

```
发送路径 (TX_2ASK):
键盘 → STM32编码 → AD9833(11.5kHz 2ASK) → 合路器NE5532
函数发生器(50Hz-10kHz) → 加法器 ──────────→ AD835(AM载波调制) → PA → 天线

接收路径 (RX_FPGA):
天线 → LNA → BPF → 包络检波 → ADC → FPGA双路FIR滤波
  ├→ LPF(11.5kHz截止) → DAC → 模拟信号恢复
  └→ NBPF(中心11.5kHz,BW80Hz) → 整形 → STM32 → 解码 → 数码管/OLED
```

## 硬件外设映射

| 外设 | 引脚 | 模块 |
|------|------|------|
| AD9851 (DDS) | PB5(D7), PB6(RST), PB7(FQ_UD), PB8(CLK) | HARDWARE/ad9851 |
| AD9833 (DDS) | PA6(FSYNC), PA7(SCLK), PB0(SDATA) | HARDWARE/AD9833 |
| ADF4002 (PLL) | PC13(SCK), PC14(SDI), PC15(SEN) | HARDWARE/adf4002 |
| RDA5820 (FM) | PB10(SCL), PB11(SDA), I2C addr=0x22 | HARDWARE/RDA5820 |
| OLED (SSD1306) | PB12(SCL), PB13(SDA), PA12(RES), I2C addr=0x3C/0x3D | HARDWARE/OLED |
| 74HC595 (数码管) | PB5(SCLK), PB6(RCLK), PB7(DATA) | HARDWARE/74HC595 |
| FPGA 并行接口 | PC0-PC7(DATA), PB2-PB4(ADDR), PC8(CS), PC9(RD), PC10(WR) | HARDWARE/FPGA_IF |
| 矩阵键盘 | PB8(ROW0), PB9(ROW1), PB1(ROW2), PC11(ROW3), PC0-PC3(COL) | SYSTEM/KEYBOARD |
| ADC 采样 | PA4 (ADC1_CH4) | main.c |
| TIM2 捕获 | PA0 (TIM2_CH1) | main.c |
| 模式切换 | PA5 (模拟开关控制) | SYSTEM/Recognize |
| DAC 偏置 | PA4(CH1), PA5(CH2) | SYSTEM/DC_bias |
| USART1 | PA9(TX), PA10(RX), 9600 baud | SYSTEM/usart |

**引脚冲突**: PB5/PB6/PB7 → AD9851与74HC595分时复用。PA5 → 模式切换与DAC CH2分时。PC0-PC3 → 键盘与FPGA数据总线分时（TX/RX模式隔离）。

## 模块结构

```
FPGA/                      FPGA Verilog 源码
  top.v                    顶层模块: 双路FIR滤波 + ADC/DAC接口 + STM32并行总线
  fir_filter.v             通用FIR滤波器 (串行MAC结构, 32阶LPF / 64阶NBPF)
HARDWARE/
  AD9833/                   AD9833 DDS 驱动 (2ASK 11.5kHz载波生成)
  FPGA_IF/                  STM32-FPGA 并行总线通信接口 (8位数据+3位地址)
  ad9851.*                  AD9851 DDS 驱动 (LO频率合成)
  adf4002.*                 ADF4002 PLL 驱动
  RDA5820.*                 RDA5820 FM接收芯片 I2C驱动
  OLED.*                    SSD1306 OLED I2C驱动 (软件I2C)
  74HC595.*                 74HC595 数码管驱动 (4位7段)
  timer.*                   TIM3中断定时器 (备用)
SYSTEM/
  ENCODE/                   2ASK编解码 (100bps UART-like, 11.5kHz载波)
  KEYBOARD/                 4x4矩阵键盘扫描
  Recognize/                自动识别逻辑 (频率预判+MAD+RSSI)
  DC_bias/                  DAC直流偏置控制
  delay/                    延时函数
  sys/                      系统初始化
  usart/                    USART1调试输出
USER/
  main.c                    主程序 (WORK_MODE 0/1/2模式切换)
```

## 2ASK 编码格式

- 波特率: 100 bps (每位10ms)
- 格式: 1 start bit(0) + 8 data bits(LSB first) + 1 stop bit(1)
- 载波: 11.5kHz (AD9833 DDS生成)
- 数据帧: [0xAA帧头][长度][数据][校验和]

## 构建说明

- STM32: 使用 Keil MDK v5 打开 `USER/VirtualCOMPort.uvprojx` 编译
- FPGA: 使用 Quartus II 打开 FPGA 目录进行综合/布局布线
- 芯片: STM32F103VE/ZE + FPGA (Cyclone IV)
- 调试: JLink/STLink (STM32), JTAG (FPGA)

## 调试输出 (USART1 @ 9600)

- 原始接收模式: `CAP=xxx raw=xxx mode=FM/AM RF=xxx LO=xxx RSSI=x LOCK=x`
- FFT波形分析: `Waveform: peak=xxx rms=xxx ratio=x.xx is_sine=x score=x ask=x`
- 发送模式: `TX: data[n]=0xNN`, `TX: send N bytes`
- FPGA接收: `RX: 0xNN ('c')`
