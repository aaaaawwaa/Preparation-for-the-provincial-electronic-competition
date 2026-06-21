# 2ASK 无线接收端 (RX)

基于 STM32F103RCT6 的 2ASK 无线信号接收解调系统，配合 TX 端实现单向无线数据传输。

## 硬件平台

| 项目 | 规格 |
|------|------|
| MCU | STM32F103RCT6 (72MHz) |
| 显示 | SSD1306 128×64 OLED (SPI2) |
| 指示 | LED1(PC4) 帧到达闪烁, LED2(PC5) 载波指示 |
| 接收 | PA1 ADC1 输入, 2ASK 模拟信号 |
| 串口 | UART1 115200bps (调试输出) |

## 引脚分配

| 引脚 | 功能 | 说明 |
|------|------|------|
| PA1 | ADC1_IN1 | 2ASK 模拟信号输入 |
| PB12 | SPI2_CS | OLED 片选 |
| PB13 | SPI2_SCK | OLED 时钟 |
| PB14 | OLED_RES | OLED 复位 |
| PB15 | SPI2_MOSI | OLED 数据 |
| PC3 | OLED_DC | OLED 数据/命令选择 |
| PC4 | LED1 | 帧到达闪烁 (低电平亮) |
| PC5 | LED2 | 载波指示 (低电平亮) |
| PA9 | UART1_TX | 调试串口输出 |
| PA10 | UART1_RX | 调试串口输入 |

## 通信协议

```
载波频率: 20Hz (100采样点/周期 @ 2kHz)
比特率:   20bps (50ms/bit, 100采样点/bit)
每字节:   起始位(0) + 8数据位(LSB) + 停止位(1) = 10bit
帧格式:   0xAA 帧头 + 长度(1B) + N字节数据 + XOR校验和(1B)
帧间静默: 5bit
```

## 功能模块

### 1. 2ASK 信号解调 (App/ASKDemod/)
- **ADC 采样**: ADC1 通道1 (PA1) @ 2kHz, TIM3 触发 + DMA1 循环传输
- **能量检测**: 100 样本窗口, 计算 |sample - 2048| 累加, 阈值 25000
- **位判决**: 能量 > 阈值 → bit 1, 否则 bit 0
- **字节状态机**: 识别起始位(0) → 收 8 数据位(LSB) → 验证停止位(1)
- **帧解析**: 匹配 0xAA 帧头 → 读取长度 → 收集数据 → XOR 校验

### 2. OLED 显示 (HW/OLED/)
- SSD1306 128×64 SPI2 驱动
- 全帧缓冲 g_oled_buf[128][8]
- 6×8 点阵 ASCII 字体 (空格～z, 91 字符)
- 支持功能:
  - `OLED_ShowString(x, y, str)` — 字符串显示
  - `OLED_ShowHex(x, y, data, len)` — 十六进制数据显示
  - `OLED_ShowNum(x, y, num, digits)` — 十进制数字显示
  - `OLED_Refresh()` — 刷新全屏到 OLED

### 3. LED 指示 (Main.c 内置)
- **LED1 (PC4)**: 收到新帧时点亮 100ms 后熄灭
- **LED2 (PC5)**: 有载波信号时常亮, 无载波时熄灭

### 4. 调试串口 (HW/UART1/)
- UART1 115200bps
- printf 输出: 帧内容(HEX)、收包统计、载波状态

### 5. 主机命令协议 (App/ProcHostCmd/ + App/SendDataToHost/ + App/PackUnpack/)
- 数据打包/解包: 10 字节固定长度 (模块ID + 帧头 + 子ID + 6字节数据 + 校验和)
- 支持系统命令 (复位/自检/应答) 和波形数据传输
- 统计帧数、字节数

### 6. 系统基础 (ARM/)
- **SysTick**: 1ms 时基 → 2ms 标志 (LED 闪烁计时) + 1s 标志 (主循环刷新)
- **NVIC**: 中断优先级配置 (TIM3 中断优先级 1.1)
- **RCC**: 72MHz SYSCLK, APB1=36MHz, APB2=72MHz, ADC 时钟 12MHz

### 7. 顶层逻辑 (App/Main/Main.c)
- 初始化: 系统时钟 → NVIC → UART1 → Timer → SysTick → LED → OLED → ASKDemod
- 主循环:
  - `Proc2msTask()`: LED1 闪烁定时器递减
  - `Proc1SecTask()`: 取帧 → 打印 → 存数据 → LED1 闪烁 → 载波检测 → 更新 OLED

## OLED 显示内容

```
┌─────────────────────┐
│ 2ASK RX Ready       │
│ Data:  (hex dump)   │
│       (cont'd)      │
│                     │
│ Frames: NNNNN       │
│                     │
│ SIG: OK  /  SIG:--- │
└─────────────────────┘
```

## 目录结构

```
STM32_plan2_RCT6_rx/
├── App/
│   ├── ASKDemod/       2ASK 解调器
│   ├── Main/           主程序
│   ├── ProcHostCmd/    主机命令处理
│   ├── PackUnpack/     数据包封装/解封装
│   ├── SendDataToHost/ 数据发送协议
│   ├── LED/            LED 基础驱动
│   └── DataType/       全局类型定义 (u8/u16/u32 等)
├── HW/
│   ├── OLED/           SSD1306 OLED 驱动
│   ├── UART1/          串口驱动 + 队列
│   ├── Timer/          通用定时器
│   ├── RCC/            时钟配置
│   ├── ADC/            ADC 驱动 + 队列
│   ├── DAC/            DAC 驱动 (接收端未使用)
│   └── KEYBOARD/       键盘驱动 (接收端未使用)
├── ARM/
│   ├── NVIC/           中断管理
│   ├── SysTick/        系统节拍
│   └── System/         CMSIS + 启动文件
├── FW/                 标准外设库 (SPL)
└── Project/            Keil uVision 工程
```

## 编译说明

- IDE: Keil uVision V5
- 编译器: ARMCC V5.06
- 必须勾选: Options for Target → Code Generation → Use MicroLIB
- 工程文件: `Project/STM32KeilPrj.uvprojx`
