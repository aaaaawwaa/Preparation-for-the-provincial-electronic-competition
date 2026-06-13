#include "RDA5820.h"
#include "delay.h"

/* RDA5820 软件 I2C 引脚映射
 * SCL -> PB10
 * SDA -> PB11
 */
#define RDA_SCL_PORT    GPIOB
#define RDA_SDA_PORT    GPIOB
#define RDA_SCL_PIN     GPIO_Pin_10
#define RDA_SDA_PIN     GPIO_Pin_11

#define RDA_SCL(x)      GPIO_WriteBit(RDA_SCL_PORT, RDA_SCL_PIN, (BitAction)(x))
#define RDA_SDA(x)      GPIO_WriteBit(RDA_SDA_PORT, RDA_SDA_PIN, (BitAction)(x))
#define RDA_SDA_READ()  GPIO_ReadInputDataBit(RDA_SDA_PORT, RDA_SDA_PIN)

// 当前使用的 FM 频段和步进，供调谐计算使用
static uint8_t g_rda_band = 0U;
static uint8_t g_rda_space = 0U;

static void RDA_I2C_Delay(void) {
    volatile uint16_t i = 50; 
    while (i--) { __NOP(); }
}

static void RDA_I2C_SDA_Output(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = RDA_SDA_PIN;
    GPIO_Init(RDA_SDA_PORT, &GPIO_InitStructure);
}

static void RDA_I2C_SDA_Input(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = RDA_SDA_PIN;
    GPIO_Init(RDA_SDA_PORT, &GPIO_InitStructure);
}

static void RDA_I2C_Start(void) {
    RDA_I2C_SDA_Output();
    RDA_SDA(1); RDA_SCL(1); RDA_I2C_Delay();
    RDA_SDA(0); RDA_I2C_Delay();
    RDA_SCL(0);
}

static void RDA_I2C_Stop(void) {
    RDA_I2C_SDA_Output();
    RDA_SCL(0); RDA_SDA(0); RDA_I2C_Delay();
    RDA_SCL(1); RDA_I2C_Delay();
    RDA_SDA(1); RDA_I2C_Delay();
}

static void RDA_I2C_Send_Byte(uint8_t byte) {
    uint8_t i;
    RDA_I2C_SDA_Output();
    for (i = 0; i < 8; i++) {
        RDA_SDA((byte & 0x80) != 0);
        RDA_I2C_Delay(); RDA_SCL(1); RDA_I2C_Delay(); RDA_SCL(0);
        byte <<= 1;
    }
    // Wait ACK
    RDA_I2C_SDA_Input();
    RDA_SCL(1); RDA_I2C_Delay(); RDA_SCL(0);
}

static uint8_t RDA_I2C_Read_Byte(unsigned char ack) {
    uint8_t i, receive = 0;
    RDA_I2C_SDA_Input();
    for (i = 0; i < 8; i++) {
        RDA_SCL(1); RDA_I2C_Delay();
        receive <<= 1;
        if (RDA_SDA_READ()) receive++;
        RDA_SCL(0); RDA_I2C_Delay();
    }
    RDA_I2C_SDA_Output();
    RDA_SDA(!ack); RDA_I2C_Delay();
    RDA_SCL(1); RDA_I2C_Delay(); RDA_SCL(0);
    return receive;
}

static uint16_t RDA_GetBandBottom_10kHz(uint8_t band)
{
    if (band == 0U)
    {
        return 8700U;
    }

    if ((band == 1U) || (band == 2U))
    {
        return 7600U;
    }

    return 8700U;
}

static uint16_t RDA_GetBandTop_10kHz(uint8_t band)
{
    if (band == 1U)
    {
        return 9100U;
    }

    return 10800U;
}

static uint16_t RDA_GetSpaceStep_10kHz(uint8_t space)
{
    switch (space & 0x03U)
    {
        case 0U:
            return 10U;
        case 1U:
            return 20U;
        default:
            return 5U;
    }
}

static void RDA5820_LnaPort_Set(uint8_t lna_port)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R05);
    temp &= (uint16_t)~(0x3U << 6);
    temp |= (uint16_t)((lna_port & 0x03U) << 6);
    RDA5820_WriteReg(RDA5820_R05, temp);
}

static uint8_t RDA5820_SelectBestLnaPort(uint16_t freq_10khz)
{
    static const uint8_t candidate_ports[3] = {1U, 2U, 3U};
    uint8_t best_port = 1U;
    uint8_t best_score = 0U;
    uint8_t i;

    for (i = 0U; i < 3U; i++)
    {
        uint8_t port = candidate_ports[i];
        uint8_t rssi;
        uint8_t locked;
        uint8_t score;

        RDA5820_LnaPort_Set(port);
        RDA5820_Freq_Set(freq_10khz);
        delay_ms(8);

        rssi = RDA5820_Read_RSSI();
        locked = RDA5820_Check_Lock();
        score = (uint8_t)(rssi + ((locked != 0U) ? 64U : 0U));

        if (score > best_score)
        {
            best_score = score;
            best_port = port;
        }
    }

    RDA5820_LnaPort_Set(best_port);
    RDA5820_Freq_Set(freq_10khz);
    return best_port;
}

/**
 * @brief  向 RDA5820 写入指定寄存器
 */
void RDA5820_WriteReg(uint8_t reg, uint16_t val) {
    RDA_I2C_Start();
    RDA_I2C_Send_Byte(RDA5820_I2C_ADDR); // 发送写地址
    RDA_I2C_Send_Byte(reg);
    RDA_I2C_Send_Byte((uint8_t)(val >> 8)); // 高字节
    RDA_I2C_Send_Byte((uint8_t)(val & 0xFF)); // 低字节
    RDA_I2C_Stop();
}

/**
 * @brief  读取 RDA5820 指定寄存器
 */
uint16_t RDA5820_ReadReg(uint8_t reg) {
    uint8_t high, low;
    RDA_I2C_Start();
    RDA_I2C_Send_Byte(RDA5820_I2C_ADDR); 
    RDA_I2C_Send_Byte(reg);
    RDA_I2C_Start(); // 重新起始，切换到读操作
    RDA_I2C_Send_Byte(RDA5820_I2C_ADDR | 0x01); // 读地址
    high = RDA_I2C_Read_Byte(1); // ACK
    low = RDA_I2C_Read_Byte(0); // NACK
    RDA_I2C_Stop();
    return (uint16_t)((high << 8) | low);
}

/**
 * @brief  RDA5820 初始化，按参考工程进入 FM 接收模式
 */
uint8_t RDA5820_Init(void) {
    // GPIO Init for I2C
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = RDA_SCL_PIN | RDA_SDA_PIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 先读芯片 ID，确认器件和总线正常
    if (RDA5820_ReadReg(RDA5820_R00) != 0x5820U)
    {
        return 1U;
    }

    // 1. 软件复位
    RDA5820_WriteReg(RDA5820_R02, 0x0002);
    delay_ms(50);
    
    // 2. 上电、解除静音、正常音频输出
    RDA5820_WriteReg(RDA5820_R02, 0xC001);
    delay_ms(150);

    // 3. 按 RDA5820NS 的 FM 接收寄存器习惯初始化，默认落在 90MHz 附近
    g_rda_band = 0U;
    g_rda_space = 2U;
    RDA5820_Band_Set(0U);
    RDA5820_Space_Set(2U);
    RDA5820_WriteReg(RDA5820_R05, 0x884FU);
    RDA5820_RX_Mode();
    RDA5820_SetFreq(90.0f);
    (void)RDA5820_SelectBestLnaPort(9000U);

    return 0;
}

void RDA5820_RX_Mode(void)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R40);
    temp &= 0xFFF0U;
    RDA5820_WriteReg(RDA5820_R40, temp);
}

void RDA5820_TX_Mode(void)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R40);
    temp &= 0xFFF0U;
    temp |= 0x0001U;
    RDA5820_WriteReg(RDA5820_R40, temp);
}

// band: 0=87~108MHz, 1=76~91MHz, 2=76~108MHz, 3=自定义
void RDA5820_Band_Set(uint8_t band)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R03);
    g_rda_band = band & 0x03U;
    temp &= (uint16_t)~(1U << 4);
    temp &= 0xFFF3U;
    temp |= (uint16_t)(g_rda_band << 2);
    RDA5820_WriteReg(RDA5820_R03, temp);
}

// spc: 0=100kHz, 1=200kHz, 2=50kHz, 3=保留
void RDA5820_Space_Set(uint8_t spc)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R03);
    g_rda_space = spc & 0x03U;
    temp &= (uint16_t)~(1U << 4);
    temp &= 0xFFFCU;
    temp |= g_rda_space;
    RDA5820_WriteReg(RDA5820_R03, temp);
}

uint8_t RDA5820_Space_Get(void)
{
    return g_rda_space;
}

void RDA5820_SeekTh_Set(uint8_t seek_th)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R05);
    temp &= 0xF0FFU;
    temp |= (uint16_t)(seek_th & 0x0FU) << 8;
    RDA5820_WriteReg(RDA5820_R05, temp);
}

// freq_10khz: 以 10kHz 为单位的目标频率，例如 9360 表示 93.60MHz
void RDA5820_Freq_Set(uint16_t freq_10khz)
{
    uint16_t temp;
    uint16_t step_10khz;
    uint16_t bottom_10khz;
    uint16_t top_10khz;
    uint16_t chan;
    uint32_t guard;

    RDA5820_RX_Mode();

    step_10khz = RDA_GetSpaceStep_10kHz(g_rda_space);
    bottom_10khz = RDA_GetBandBottom_10kHz(g_rda_band);
    top_10khz = RDA_GetBandTop_10kHz(g_rda_band);

    if (freq_10khz < bottom_10khz)
    {
        freq_10khz = bottom_10khz;
    }

    if (freq_10khz > top_10khz)
    {
        freq_10khz = top_10khz;
    }

    temp = RDA5820_ReadReg(RDA5820_R03);
    temp &= 0x000FU;

    chan = (uint16_t)((freq_10khz - bottom_10khz) / step_10khz);
    chan &= 0x03FFU;
    temp |= (uint16_t)(chan << 6);
    temp |= (uint16_t)(1U << 4);
    RDA5820_WriteReg(RDA5820_R03, temp);
    delay_ms(20);

    // 等待调谐完成，带超时上限
    guard = 5000U;
    while (((RDA5820_ReadReg(RDA5820_R0B) & (1U << 7)) == 0U) && (guard-- != 0U))
    {
    }
}

// 返回当前频率，单位 10kHz
uint16_t RDA5820_Freq_Get(void)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R03);
    uint16_t step_10khz = RDA_GetSpaceStep_10kHz(g_rda_space);
    uint16_t bottom_10khz = RDA_GetBandBottom_10kHz(g_rda_band);
    uint16_t chan = (uint16_t)((temp >> 6) & 0x03FFU);

    return (uint16_t)(bottom_10khz + chan * step_10khz);
}

/**
 * @brief  以 MHz 为单位设置接收频率，例如 90.0f
 * @param  freq_mhz 目标频率，单位 MHz
 */
void RDA5820_SetFreq(float freq_mhz) {
    uint16_t freq_10khz;

    if (freq_mhz < 0.0f)
    {
        return;
    }

    freq_10khz = (uint16_t)(freq_mhz * 100.0f + 0.5f);
    if (freq_10khz < 7600U)
    {
        freq_10khz = 7600U;
    }
    if (freq_10khz > 10800U)
    {
        freq_10khz = 10800U;
    }

    RDA5820_Freq_Set(freq_10khz);
}

/**
 * @brief  在给定中心频点附近进行自动试探，按 50kHz 网格选择锁定/RSSI 最优点
 * @param  freq_mhz 目标中心频率，单位 MHz
 * @return 1 表示最终选中的频点已锁定，0 表示仅完成最佳 RSSI 选择
 */
uint8_t RDA5820_AutoTuneAround(float freq_mhz)
{
    static const int16_t offset_10khz[3] = {0, 50, -50};
    uint16_t center_10khz;
    uint16_t bottom_10khz;
    uint16_t top_10khz;
    uint16_t best_freq_10khz;
    uint16_t best_score;
    int32_t candidate_10khz;
    uint16_t score;
    uint8_t locked;
    uint8_t rssi;
    uint8_t i;

    if (freq_mhz < 0.0f)
    {
        return 0U;
    }

    center_10khz = (uint16_t)(freq_mhz * 100.0f + 0.5f);
    bottom_10khz = RDA_GetBandBottom_10kHz(g_rda_band);
    top_10khz = RDA_GetBandTop_10kHz(g_rda_band);

    if (center_10khz < bottom_10khz)
    {
        center_10khz = bottom_10khz;
    }
    if (center_10khz > top_10khz)
    {
        center_10khz = top_10khz;
    }

    // 先用较粗步进锁到中心点，再切回 50kHz 做附近试探。
    RDA5820_Space_Set(0U);
    RDA5820_Freq_Set(center_10khz);
    RDA5820_Space_Set(2U);

    best_freq_10khz = center_10khz;
    best_score = 0U;

    for (i = 0; i < 3U; i++)
    {
        candidate_10khz = (int32_t)center_10khz + (int32_t)offset_10khz[i];
        if ((candidate_10khz < (int32_t)bottom_10khz) || (candidate_10khz > (int32_t)top_10khz))
        {
            continue;
        }

        RDA5820_Freq_Set((uint16_t)candidate_10khz);
        locked = RDA5820_Check_Lock();
        rssi = RDA5820_Read_RSSI();
        score = (uint16_t)(((locked != 0U) ? 0x8000U : 0x0000U) | rssi);

        if (score > best_score)
        {
            best_score = score;
            best_freq_10khz = (uint16_t)candidate_10khz;
        }
    }

    if (best_freq_10khz != center_10khz)
    {
        RDA5820_Freq_Set(best_freq_10khz);
    }

    return (uint8_t)((best_score & 0x8000U) != 0U);
}

/**
 * @brief  读取接收信号强度指示 RSSI
 */
uint8_t RDA5820_Read_RSSI(void) {
    uint16_t res = RDA5820_ReadReg(RDA5820_R0B);
    return (uint8_t)(res >> 9);
}

// 兼容参考工程的命名
uint8_t RDA5820_Rssi_Get(void)
{
    return RDA5820_Read_RSSI();
}

/**
 * @brief  判断当前是否完成调谐并锁台
 */
uint8_t RDA5820_Check_Lock(void) {
    uint16_t res = RDA5820_ReadReg(RDA5820_R0B);
    if (((res & (1U << 7)) != 0U) && ((res & (1U << 8)) != 0U)) {
        return 1;
    }
    return 0;
}

/**
 * @brief  设置静音状态，mute=1 为静音，mute=0 为正常输出
 */
void RDA5820_Mute_Set(uint8_t mute)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R02);

    if (mute != 0U)
    {
        temp &= (uint16_t)~(1U << 14);
    }
    else
    {
        temp |= (uint16_t)(1U << 14);
    }

    RDA5820_WriteReg(RDA5820_R02, temp);
}

/**
 * @brief  设置音量，范围 0~15
 */
void RDA5820_Vol_Set(uint8_t vol)
{
    uint16_t temp = RDA5820_ReadReg(RDA5820_R05);
    temp &= 0xFFF0U;
    temp |= (uint16_t)(vol & 0x0FU);
    RDA5820_WriteReg(RDA5820_R05, temp);
}
