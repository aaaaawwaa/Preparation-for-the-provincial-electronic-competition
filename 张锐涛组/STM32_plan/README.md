# 双制式信号自动识别接收系统

本工程是为全国大学生电子设计竞赛（电赛）开发的“双制式信号自动识别”接收系统源码项目，基于 **STM32F103VET6/ZET6** 开发，支持 **AM** 与 **FM** 信号的宽频带接收、自动识别与解调切换。

## 1. 核心功能模块

### 1.1 自动识别逻辑 (Recognize)
系统采用三维特征融合算法实时判定输入信号制式：
- **频率区间预判**：基于 AD9851 设置频率（5-25MHz 倾向 AM，28-48MHz 倾向 FM）。
- **幅度方差检测 (MAD)**：通过对包络检波后的信号进行 ADC 高速采样，计算平均绝对偏差。AM 幅度剧烈波动，FM 幅度恒定。
- **状态回传确认**：通过 I2C 读取 RDA5820 内部寄存器的 RSSI（信号强度）与锁定状态进行最终仲裁。

### 1.2 频率合成与下变频 (DDS & PLL)
- **AD9851 (DDS)**：生成本振信号。支持 6 倍频模式，提供高分辨率的本振输入。
- **ADF4002 (PLL)**：用于高性能锁相环频率合成，确保本振频率的长期稳定性。

### 1.3 信号解调 (Demodulation)
- **FM 解调**：集成驱动 **RDA5820** 芯片，支持 I2C 控制频率设定、RSSI 读取及数字锁定检测。
- **AM 解调**：通过包络检波硬件电路配合 STM32 的 ADC 采样及 FFT 变换实现。

### 1.3.1 RDA5820 FM 参数与调用顺序
RDA5820 在本工程里作为独立 FM 接收机使用，当前测试信号源参数为：
- 载波频率：90MHz
- 调制频率：1kHz
- 频偏：40kHz

推荐按以下顺序配置：
1. `RDA5820_Init()` 完成软复位、上电、RX 模式切换，并默认落到 90MHz。
2. `RDA5820_Band_Set(0U)` 选择 87~108MHz 频段。
3. `RDA5820_Space_Set(2U)` 选择 50kHz 步进，便于匹配 40kHz 频偏附近的试探。
4. `RDA5820_AutoTuneAround(90.0f)` 在 90MHz 附近按 50kHz 网格试探并选优。
5. 轮询 `RDA5820_Check_Lock()` 和 `RDA5820_Read_RSSI()`，稳定后再 `RDA5820_Vol_Set(15U)`、`RDA5820_Mute_Set(0U)`。

| 函数 | 作用 | 典型参数 | 说明 |
| --- | --- | --- | --- |
| `RDA5820_Band_Set(uint8_t band)` | 设置 FM 频段 | `0`=87~108MHz，`1`=76~91MHz，`2`=76~108MHz | 先设频段，再设频点 |
| `RDA5820_Space_Set(uint8_t spc)` | 设置频点步进 | `0`=100kHz，`1`=200kHz，`2`=50kHz | 动态偏频试探建议用 `2` |
| `RDA5820_Freq_Set(uint16_t freq_10khz)` | 以 10kHz 为单位调频 | `9000`=90.00MHz | 会根据当前 band/space 计算 channel |
| `RDA5820_SetFreq(float freq_mhz)` | 以 MHz 为单位固定调频 | `90.0f` | 适合已知目标频点时直接设置 |
| `RDA5820_AutoTuneAround(float freq_mhz)` | 在中心频点附近自动试探 | `90.0f` | 按 50kHz 网格搜索并用 RSSI/Lock 选优 |
| `RDA5820_Read_RSSI()` / `RDA5820_Rssi_Get()` | 读取信号强度 | 返回 `0~127` | 可用于自动静音或识别门限 |
| `RDA5820_Check_Lock()` | 读取锁台状态 | 返回 `0/1` | `1` 表示 FM 已进入可用锁定状态 |
| `RDA5820_Mute_Set(uint8_t mute)` | 静音控制 | `1` 静音，`0` 取消静音 | 建议在调谐前先静音 |
| `RDA5820_Vol_Set(uint8_t vol)` | 设置音量 | `0~15` | `15` 为最大音量 |

注意：本工程里的 RDA5820 FM 路径是直接接收 90.0MHz 载波，不把 10.7MHz 作为 RDA5820 的调谐目标。

补充说明：1kHz 是信号源的调制频率，40kHz 是信号源频偏；接收端仍然只需要保持 FM RX 模式，并在 90.0MHz 附近做动态试探，优先依据 `RDA5820_Check_Lock()` 和 `RDA5820_Read_RSSI()` 选择最优频点。

补充说明 2：RDA5820 的最小可用调谐步进是 50kHz，所以会以 50kHz 网格逼近 90MHz 附近的最佳锁定点。

## 2. 硬件引脚配置

### 2.1 MCU <-> 外设映射总表

| 外设/功能 | 信号 | MCU引脚 | 代码依据 |
| --- | --- | --- | --- |
| AD9851 (DDS) | D7(DATA) | PB5 | HARDWARE/ad9851.h |
| AD9851 (DDS) | RST | PB6 | HARDWARE/ad9851.h |
| AD9851 (DDS) | FQ_UD | PB7 | HARDWARE/ad9851.h |
| AD9851 (DDS) | CLK | PB8 | HARDWARE/ad9851.h |
| ADF4002 (PLL) | SCK | PC13 | HARDWARE/adf4002.h, HARDWARE/adf4002.c |
| ADF4002 (PLL) | SDI | PC14 | HARDWARE/adf4002.h, HARDWARE/adf4002.c |
| ADF4002 (PLL) | SEN | PC15 | HARDWARE/adf4002.h, HARDWARE/adf4002.c |
| RDA5820 (FM) | I2C SCL | PB10 | HARDWARE/RDA5820.c |
| RDA5820 (FM) | I2C SDA | PB11 | HARDWARE/RDA5820.c |
| OLED (UI) | I2C SCL | PB12 | HARDWARE/OLED.c |
| OLED (UI) | I2C SDA | PB13 | HARDWARE/OLED.c |
| OLED (UI, optional) | RES | PA12 | HARDWARE/OLED.c |
| 74HC595 (数码管) | SCLK | PB5 | HARDWARE/74HC595.c |
| 74HC595 (数码管) | RCLK | PB6 | HARDWARE/74HC595.c |
| 74HC595 (数码管) | DATA | PB7 | HARDWARE/74HC595.c |
| 模式切换控制 | Switch CTRL | PA5 | SYSTEM/Recognize/recognize.c |
| 直流偏置DAC | DAC CH1 | PA4 | SYSTEM/DC_bias/DC_bias.h |
| 直流偏置DAC | DAC CH2 | PA5 | SYSTEM/DC_bias/DC_bias.h |
| 包络/音频采样 | ADC1_CH1 | PA1 | USER/main.c |
| 频率输入捕获 | TIM2_CH1 | PA0 | USER/main.c |
| 串口调试 | USART1_TX | PA9 | SYSTEM/usart/usart.c |
| 串口调试 | USART1_RX | PA10 | SYSTEM/usart/usart.c |

### 2.2 ADF4002 分频配置说明

- 主程序初始化流程中，ADF4002 按如下顺序执行：
  - `InitADF4002();`
  - `RDivideTest(10000);`  (R分频=10000，上电默认配置)
- 代码位置：USER/main.c。

### 2.3 复用与冲突说明

- **PB5/PB6/PB7 引脚复用**：
  - AD9851 使用 PB5/PB6/PB7。
  - 74HC595 也使用 PB5/PB6/PB7。
  - 若两模块需同时在线，必须增加硬件隔离或时序互斥控制。
- **PA5 多用途风险**：
  - SYSTEM/Recognize 中 PA5 用于 AM/FM 模式切换控制。
  - SYSTEM/DC_bias 中 PA5 对应 DAC CH2。
  - 两者不能在同一时刻作为独立功能同时使用，需按运行模式进行资源分配。

### 2.4 待补项（衰减器）

- 当前仓库中未找到衰减器驱动源码（仅看到 OBJ/mcp41xx.* 目标文件产物）。
- 因缺少源文件或原理图，暂无法给出“衰减器 <-> MCU引脚”可靠映射，后续补档后再更新。

## 3. 工程结构说明
- `USER/`：主程序入口 `main.c` 及系统中断处理。
- `HARDWARE/`：外设驱动 (AD9851, ADF4002, RDA5820, OLED, 74HC595)。
- `SYSTEM/Recognize/`：自动识别核心算法模块（逻辑切换、MAD 偏差计算）。
- `DSP/`：STM32 DSP 库文件，支持 FFT 相关运算。

## 4. 调试说明
1. **测试模式切换**：通过修改 `main.c` 中的初始化部分，可以分别对 AD9851 和 RDA5820 进行专项功能测试；ADF4002 当前默认执行 `RDivideTest(10000)`。
2. **算法阈值**：识别逻辑中的 `MAD_THRESHOLD` 与 `RSSI_THRESHOLD` 需根据实际硬件电路的增益进行微调。
3. **频率补偿**：主 LO 链路仍按 10.7MHz 中频进行偏移补偿；RDA5820 的 FM 接收测试则直接调到 90.0MHz，不以 10.7MHz 作为调谐目标。

## 5. OLED 黑屏排障（SSD1306）
1. **现象“上电闪烁后熄灭”**通常是初始化中途I2C握手失败，导致 `Display OFF` 已发送但 `Display ON` 未成功。
2. **驱动已加入地址回退**：先尝试 `0x3C`，失败再尝试 `0x3D`。
3. **串口诊断字段**：
  - `ready`：OLED是否初始化成功（1成功，0失败）
  - `err`：初始化失败阶段（见 `HARDWARE/OLED.h` 中 `OLED_ERR_*`）
  - `addr`：最终使用的8位写地址（例如 `0x78` 对应7位 `0x3C`）
  - `nack`：累计I2C ACK失败计数
4. **硬件前提**：
  - SSD1306 使用软件I2C：`PB12(SCL)`、`PB13(SDA)`，并与MCU共地。
  - 需保证 SDA/SCL 具备有效上拉（常见 4.7k~10k）。
  - 若使用 `RES`，确保 `PA12` 与模块复位脚连接并时序稳定。
5. **建议验证流程**：
  - 冷启动后观察串口初始化日志，确认地址与错误码。
  - 示波器查看 SCL/SDA 是否存在完整时序与ACK。
  - 分别在 `0x3C` 与 `0x3D` 模块上复测，确认回退机制生效。

---
*注：本工程部分引脚存在复用（见第 2.3 节），部署前请先核对原理图与运行模式。*


