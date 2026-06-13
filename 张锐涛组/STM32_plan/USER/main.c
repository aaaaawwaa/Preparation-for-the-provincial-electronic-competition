#include "stm32_config.h"
#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stdio.h"
#include "usart.h"
#include "stm32f10x_adc.h"
#include "sys.h"
#include "OLED.h"
#include "delay.h"
#include "ad9851.h"
#include "adf4002.h"
#include "RDA5820.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#include "DC_bias.h"
#include "../SYSTEM/Recognize/recognize.h"
#include "../SYSTEM/ENCODE/encode.h"
#include "../SYSTEM/KEYBOARD/keyboard.h"
#include "../HARDWARE/FPGA_IF/fpga_if.h"
#include "../HARDWARE/AD9833/ad9833.h"
#include "../HARDWARE/74HC595.h"

/*
 * 工作模式选择 (编译时切换)
 *   0 = RX_LEGACY: 原始STM32接收机 (ADC+FFT+FM)
 *   1 = TX_2ASK:   2ASK发送机 (键盘+编码+AD9833)
 *   2 = RX_FPGA:   FPGA双路数字滤波接收机 (FPGA+解码+显示)
 */
#define WORK_MODE               0

/* 发送模式参数 */
#define TX_DATA_INTERVAL_MS     150     /* 发送字符间隔 */
#define TX_SAMPLE_RATE_HZ       100     /* 编码状态机采样率(Hz) */

/* 接收模式参数 */
#define RX_FPGA_POLL_MS         10      /* FPGA轮询间隔 */

/*
 * MCU-to-peripheral mapping used in this project:
 * AD9851: PB5(D7), PB6(RST), PB7(FQ_UD), PB8(CLK)
 * ADF4002: PC13(SCK), PC14(SDI), PC15(SEN)
 * RDA5820 I2C: PB10(SCL), PB11(SDA)
 * OLED I2C: PB12(SCL), PB13(SDA), PA12(RES optional)
 * 74HC595: PB5(SCLK), PB6(RCLK), PB7(DATA)
 * USART1: PA9(TX), PA10(RX)
 * ADC sample: PA4(ADC1_CH4), TIM2 capture: PA0(TIM2_CH1)
 * Mode switch: PA5 (FM/AM path select), DC_BIAS DAC: PA4(CH1), PA5(CH2)
 * Attenuator mapping: source file not found (only OBJ/mcp41xx.* exists).
 */



uint16_t AD_value = 0;                               // ����ԭʼAD������δ��ʹ�ã�
static uint32_t freq_hz = 0;                         // ���²�õ�Ƶ�ʣ�Hz��
static uint32_t raw_freq_hz = 0;                     // δ��������Ƶ�ʣ�Hz��
static uint32_t tim2_counter_hz = 72000000U;         // TIM2����Ƶ��(Hz)��72MHzȫ�ټ���
static uint8_t g_adc_ready = 0;                      // ADC��ʼ��״̬��1�ɹ���0ʧ��/��ʱ
static uint8_t g_adc_is_ask = 0U;                    // ����TIM3����FFTг���ж���1=ASK,0=AM

// ASK�ж��÷֣�+������-�½���
static int8_t g_ask_score = 0;

// �����ã��������µ�peak/RMS����ֵ������OLED��ʾ��
static uint32_t g_peak_rms_ratio_x100 = 100U;

#define FFT_SAMPLES          1024        // FFT������Ƶ�ʷֱ��� ��f = Fs / N
#define FFT_SAMPLE_RATE_HZ   10000U      // ������Fs=10000Hz����Ӧ�������ޡ�Fs/2=5000Hz������300Hz~5kHz��
#define CAPTURE_TIMEOUT_MS   500U        // ���벶��ʱ��ֵ�����±������ж�Ϊ0Hz
#define ADC_INIT_TIMEOUT     1000000U    // ADCУ׼�ȴ���ʱ����
#define ADC_CONV_TIMEOUT     1000000U    // ADC����ת���ȴ���ʱ����
#define FFT_TIMER_WAIT_TIMEOUT 200000U   // FFT�����ȴ�TIM3���³�ʱ����
#define TIM2_USE_IRQ_CAPTURE 0U          // 1:�жϲ�Ƶ, 0:��ѯ��Ƶ(��Ƶ�������)
#define TIM2_USE_IRQ_CAPTURE 0U          // 1:�жϲ�Ƶ, 0:��ѯ��Ƶ(��Ƶ�������)
#define TIM2_POLL_WAIT_LOOPS 200000U     // ��ѯģʽ�µȴ������־��ѭ������
#define NO_CAPTURE_MAX_LOOPS 6U          // �������²��������ֵ
#define OLED_RETRY_LOOP_GAP  5U          // OLEDδ����ʱÿN������һ��
#define TIM2_WINDOW_PERIODS   8U          // ���ڷ��ۼ���������Խ��Խ�ȵ����¸���
#define FREQ_MATCH_PCT        8U          // ���ڷ��봰�ڷ�һ������ֵ(%), ����ֵ���ȴ��ڷ�
#define FILTER_LIMIT_PCT      20U         // �����˲���1���޷��ٷֱ�
#define FILTER_MIN_STEP_HZ    80U         // �޷���С����(Hz)
#define FILTER_TRIM_WIN       10U         // ȥ��ֵƽ�����ڣ�N=10��
#define FILTER_TRIM_DROP      2U          // ��ͷȥβ������ȥ�����2�������2����
#define FILTER_FAST_STEP_PCT  12U         // ͻ���оݣ���Բ���(%)
#define FILTER_FAST_STEP_MIN  100U        // ͻ���оݣ���С����(Hz)
#define FILTER_DIFF_FAST_HZ   120U        // P/W��һ��ʱ�п��ٴ��ڵ���С��ֵ(Hz)
#define FREQ_VAR_WINDOW        8U          // �ο�����Ǩ�ƣ�Ƶ�ʷ���ڳ���
#define FREQ_VAR_THRESHOLD_HZ2 (20000UL * 20000UL) // �ο�����Ǩ�ƣ��ж����ȶ���ֵ
#define KALMAN_Q_FAST         120.0f      // ����ͨ��������Q
#define KALMAN_R_FAST         1200.0f     // ����ͨ��������R
#define KALMAN_Q_STABLE       8.0f        // ��ʾͨ��������Q
#define KALMAN_R_STABLE       5000.0f     // ��ʾͨ��������R
#define CAP_LOOP_DELAY_MS     20U         // ��ѯ���˲�Ƶ����
#define SCHED_OLED_MS         80U         // OLEDˢ������
#define SCHED_LOG_MS          250U        // ������־����
#define SCHED_RDA_MS          20U         // RDA��ȡ���ڣ���һ���ӿ�LK״̬������
#define SCHED_ADC_MS          100U        // ADC��Ƶ�������ڣ�����AM/ASK��Ӧ��
#define RDA_LOCK_DISPLAY_CNT  1U          // OLED��ʾLKΪ�ȶ�����������������
#define RDA_LOCK_AUDIO_CNT    2U          // ��Ƶ��������������������
#define RDA_RELOCK_START_CNT  16U         // ʧ���󴥷��ص�г����ʼ����
#define RDA_RELOCK_STEP_CNT   8U          // ʧ�����ص�г���Լ������
#define SCHED_OLED_RETRY_MS   200U        // OLED��������
#define USE_TIM4_TIMEBASE     0U          // 1:ʹ��TIM4�ж�ʱ��, 0:����ʱ��(��ǰ�Ƽ�)
#define FM_IF_TARGET_HZ       90000000UL  // FMĿ���ز���RDA5820����Ƶ�� = 90MHz
#define FM_IF_TARGET_MHZ      90.0f       // RDA5820��гĿ��
#define AM_IF_TARGET_HZ       10700000UL  // AM��ƵĿ�꣺10.7MHz
#define AM_IF_TARGET_MHZ      10.7f       // AMģʽ��гĿ��
#define MOD_FM_THRESHOLD_HZ   28000000UL  // ���������ж�������28MHz��ΪFM
#define ASK_H3_RATIO_PCT      1U          // ASK�оݣ�����г������ռ��������������ֵ(%) ���˽�����1%
#define MODE_SWITCH_TH_HZ     2500UL      // ģʽ�л���ֵ��2.5kHz
#define PA0_FREQ_VALID_MIN_HZ 1000000UL   // ��Ч��ƵƵ�����ޣ�1MHz��
#define PA0_FREQ_VALID_MAX_HZ 89000000UL  // ��Ч��ƵƵ�����ޣ�89MHz��
#define ADF_R_DIVIDER_VALUE   10000UL     // ��ǰ������·ADF R��Ƶֵ
#define PA0_DIVIDED_MAX_HZ    200000UL    // PA0���ڸ�ֵʱ����Ƶ�������ԭʼ��Ƶ
#define LO_OUTPUT_MIN_HZ      1000000UL   // AD9851����Ƶ������
#define LO_OUTPUT_MAX_HZ      90000000UL  // AD9851����Ƶ������
#define LO_UPDATE_HYST_HZ     3000UL      // ������³��ͣ�����Ƶ����дDDS

// ASK�ж��÷ַ�����
#define ASK_SCORE_MAX         8
#define ASK_SCORE_ENTER       3           // ����ASK��ֵ
#define ASK_SCORE_EXIT        2           // �˳�ASK��ֵ����Ҫ�����߲��F��
#define FUND_RESTORE_PCT      10U         // ��Ƶ����������Ƶ�����ﵽ������������Ϊ����
#define ASK_MIN_ENERGY        100U        // ���������������������ASK�źţ�600-700mVpp��ͨ�����

#if TIM2_USE_IRQ_CAPTURE
#define TIM2_CAP_EDGE_FACTOR  8U
#else
#define TIM2_CAP_EDGE_FACTOR  1U
#endif

static int16_t fft_in[FFT_SAMPLES * 2];
static int16_t fft_out[FFT_SAMPLES * 2];

static void TIM2_InputCapture_Init(void);
static void TIM4_Timebase_Init(void);
static void TIM3_SampleClock_Init(uint32_t sample_rate_hz);
static uint32_t Get_Filtered_Freq(uint32_t new_raw);
static uint32_t Get_Fast_Control_Freq(uint32_t new_raw);
static uint32_t Get_Ms_Tick(void);
static uint32_t TIM2_Capture_ReadPeriodTicks(uint32_t wait_loops);
static uint32_t TIM2_Capture_WindowFreqHz(uint32_t wait_loops, uint8_t periods, uint8_t *ok);
static uint32_t Select_Robust_Freq(uint32_t period_hz, uint32_t window_hz);
static uint32_t Update_Freq_Variance_Hz2(uint32_t sample_hz);
static uint32_t AbsDiffU32(uint32_t a, uint32_t b);
static uint8_t IsElapsed(uint32_t now, uint32_t last, uint32_t period_ms);
static const char *Get_Modulation_Label(uint32_t rf_hz);
static void RDA5820_BuildStatusLine(char *line, uint16_t line_len, uint8_t rda_ready);
static uint8_t Compute_LO_FreqHz(uint32_t pa0_freq_hz, uint32_t if_target_hz, uint8_t dual_side_mix, uint32_t *rf_est_hz, uint32_t *lo_freq_hz);
static uint32_t FFT_Measure_LowFreq_Hz(uint32_t sample_rate_hz);
uint16_t AD_GetValue(uint8_t ADC_Channel);
float Get_Current_Frequency(void);
uint16_t Get_ADC_Average(uint8_t times);

volatile uint32_t g_Update_Cnt = 0;       // ��ʱ���������
volatile uint32_t g_Period_Ticks = 0;     // �ź������ܼ���ֵ
volatile uint8_t  g_New_Freq_Ready = 0;   // ����Ƶ�ʲ���
volatile uint32_t g_ms_tick = 0;          // �������
volatile uint32_t g_cap_poll_ok = 0;      // ��ѯģʽ�ɹ��������
volatile uint32_t g_cap_poll_timeout = 0; // ��ѯģʽ��ʱ����
volatile uint32_t g_cap_last_ticks = 0;   // ���һ�β��񵽵�����ticks
volatile uint32_t g_period_freq_hz = 0;   // ���ڷ�Ƶ�ʹ���
volatile uint32_t g_window_freq_hz = 0;   // ���ڷ�Ƶ�ʹ���
volatile uint32_t g_freq_diff_hz = 0;     // ���ֹ��Ʋ�ֵ
volatile uint8_t  g_filter_avg_win = 0;   // �����������м������ȶ���ָ�꣩

static void RDA5820_BuildStatusLine(char *line, uint16_t line_len, uint8_t rda_ready)
{
	uint16_t rda_freq_10khz;
	uint8_t space;
	const char *step_label;
	uint16_t freq_mhz;

	if ((line == NULL) || (line_len == 0U))
	{
		return;
	}

	if (!rda_ready)
	{
		(void)snprintf(line, line_len, "STEP:-- FQ:--MHz");
		return;
	}

	space = RDA5820_Space_Get();
	switch (space & 0x03U)
	{
		case 0U:
			step_label = "M0";
			break;
		case 1U:
			step_label = "M1";
			break;
		default:
			step_label = "M2";
			break;
	}

	rda_freq_10khz = RDA5820_Freq_Get();
	freq_mhz = (uint16_t)((rda_freq_10khz + 50U) / 100U);
	(void)snprintf(line, line_len, "STEP:%s FQ:%uMHz", step_label, (unsigned int)freq_mhz);
}

static uint32_t g_freq_var_window[FREQ_VAR_WINDOW];
static uint8_t g_freq_var_len = 0U;
static uint8_t g_freq_var_pos = 0U;



/**
  * ��    ����AD��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void AD_Init(void)
{
	uint32_t timeout;
	g_adc_ready = 0U;

	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//����ADC1��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//����GPIOA��ʱ��
	
	/*����ADCʱ��*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);						//ѡ��ʱ��6��Ƶ��ADCCLK = 72MHz / 6 = 12MHz
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA4��ʼ��Ϊģ�����루PA0 �� TIM2 ���벶�� ʹ�ã�
	
	/*���ڴ˴����ù��������У�������ÿ��ADת��ǰ���ã���������������ADת����ͨ��*/
	
	/*ADC��ʼ��*/
	ADC_InitTypeDef ADC_InitStructure;						//����ṹ�����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//ģʽ��ѡ�����ģʽ��������ʹ��ADC1
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//���ݶ��룬ѡ���Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ������ʹ����������������Ҫ�ⲿ����
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//����ת����ʧ�ܣ�ÿת��һ�ι��������к�ֹͣ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			//ɨ��ģʽ��ʧ�ܣ�ֻת�������������1��һ��λ��
	ADC_InitStructure.ADC_NbrOfChannel = 1;					//ͨ������Ϊ1������ɨ��ģʽ�£�����Ҫָ������1�������ڷ�ɨ��ģʽ�£�ֻ����1
	ADC_Init(ADC1, &ADC_InitStructure);						//���ṹ���������ADC_Init������ADC1
	
	/*ADCʹ��*/
	ADC_Cmd(ADC1, ENABLE);									//ʹ��ADC1��ADC��ʼ����
	
	/*ADCУ׼*/
	ADC_ResetCalibration(ADC1);								//�̶����̣��ڲ��е�·���Զ�ִ��У׼
	timeout = ADC_INIT_TIMEOUT;
	while (ADC_GetResetCalibrationStatus(ADC1) == SET)
	{
		if (timeout-- == 0U)
		{
			return;
		}
	}
	ADC_StartCalibration(ADC1);
	timeout = ADC_INIT_TIMEOUT;
	while (ADC_GetCalibrationStatus(ADC1) == SET)
	{
		if (timeout-- == 0U)
		{
			return;
		}
	}

	g_adc_ready = 1U;
}

/*
 * ��    ����TIM2���벶���ʼ����PA0��TIM2_CH1��
 * Ŀ    �ģ��������������ؼ��������<10MHzƵ��
 */
static void TIM2_InputCapture_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	RCC_ClocksTypeDef clocks;
	uint32_t tim2_clk_hz;
	uint16_t prescaler;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// ����Ĭ������ӳ�䣨��λĬ�ϼ�TIM2_CH1��PA0�������ⲿ�ֿ���Կ���
	// PA0 ����Ϊ�������룬�������ź�ʱ�����������ж�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// ����TIM2ʱ�Ӳ�����Ϊ���Ƶ�ʼ�������߷ֱ���
	RCC_GetClocksFreq(&clocks);
	if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1)
	{
		tim2_clk_hz = clocks.PCLK1_Frequency * 2U;
	}
	else
	{
		tim2_clk_hz = clocks.PCLK1_Frequency;
	}
	// ȷ��Ŀ�����Ƶ�ʲ���������ʱ��
	if (tim2_counter_hz > tim2_clk_hz)
	{
		tim2_counter_hz = tim2_clk_hz;
	}
	if (tim2_counter_hz == 0U)
	{
		tim2_counter_hz = 1000000U;
	}
	prescaler = (uint16_t)((tim2_clk_hz / tim2_counter_hz) - 1U);

	// ��ʱ������Ƶ�ʣ�tim2_counter_hz��TIM2Ϊ16λ������
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	// ͨ��1�����ز���
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;

#if TIM2_USE_IRQ_CAPTURE
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV8;
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;
#else
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
#endif
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1 | TIM_IT_Update);
	TIM_ClearFlag(TIM2, TIM_FLAG_CC1 | TIM_FLAG_Update | TIM_FLAG_CC1OF);

#if TIM2_USE_IRQ_CAPTURE
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1 | TIM_IT_Update);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#else
	TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_Update, DISABLE);
#endif

	TIM_Cmd(TIM2, ENABLE);
}

static void TIM4_Timebase_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 999;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM4, ENABLE);
}

static void TIM3_SampleClock_Init(uint32_t sample_rate_hz)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_ClocksTypeDef clocks;
	uint32_t tim3_clk_hz;
	uint32_t tick_hz;
	uint16_t prescaler;
	uint16_t period;

	if (sample_rate_hz == 0U)
	{
		sample_rate_hz = FFT_SAMPLE_RATE_HZ;
	}

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_Cmd(TIM3, DISABLE);

	RCC_GetClocksFreq(&clocks);
	if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1)
	{
		tim3_clk_hz = clocks.PCLK1_Frequency * 2U;
	}
	else
	{
		tim3_clk_hz = clocks.PCLK1_Frequency;
	}

	tick_hz = 1000000U;
	if (tick_hz > tim3_clk_hz)
	{
		tick_hz = tim3_clk_hz;
	}
	if (tick_hz == 0U)
	{
		tick_hz = sample_rate_hz;
	}

	prescaler = (uint16_t)((tim3_clk_hz / tick_hz) - 1U);
	period = (uint16_t)((tick_hz / sample_rate_hz) - 1U);

	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_SetCounter(TIM3, 0U);
	TIM_Cmd(TIM3, ENABLE);
}

static uint32_t Get_Filtered_Freq(uint32_t new_raw)
{
	uint32_t limited;
	uint32_t filtered;
	uint32_t sum;
	uint32_t limit_step;
	uint8_t used_count;
	uint8_t start_idx;
	uint8_t end_idx;
	uint8_t i;
	uint8_t j;
	static uint32_t last_limited = 0U;
	static uint32_t trim_buf[FILTER_TRIM_WIN];
	static uint8_t trim_idx = 0U;
	static uint8_t trim_count = 0U;

	// Stage-1: �޷�����ֹë�̵��µ��ν�Ծ
	limited = new_raw;
	if (last_limited > 0U)
	{
		limit_step = (last_limited * FILTER_LIMIT_PCT) / 100U;
		if (limit_step < FILTER_MIN_STEP_HZ)
		{
			limit_step = FILTER_MIN_STEP_HZ;
		}

		if (new_raw > last_limited)
		{
			if ((new_raw - last_limited) > limit_step)
			{
				limited = last_limited + limit_step;
			}
		}
		else if ((last_limited - new_raw) > limit_step)
		{
			limited = last_limited - limit_step;
		}
	}
	last_limited = limited;

	// Stage-2: ���������ƽ����ȥ��ֵƽ����
	trim_buf[trim_idx] = limited;
	trim_idx = (uint8_t)((trim_idx + 1U) % FILTER_TRIM_WIN);
	if (trim_count < FILTER_TRIM_WIN)
	{
		trim_count++;
	}

	{
		uint32_t tmp[FILTER_TRIM_WIN];

		for (i = 0U; i < trim_count; i++)
		{
			tmp[i] = trim_buf[i];
		}
		for (i = 1U; i < trim_count; i++)
		{
			uint32_t key = tmp[i];
			j = i;
			while ((j > 0U) && (tmp[j - 1U] > key))
			{
				tmp[j] = tmp[j - 1U];
				j--;
			}
			tmp[j] = key;
		}

		if (trim_count > (2U * FILTER_TRIM_DROP))
		{
			start_idx = FILTER_TRIM_DROP;
			end_idx = (uint8_t)(trim_count - FILTER_TRIM_DROP);
		}
		else
		{
			start_idx = 0U;
			end_idx = trim_count;
		}

		sum = 0U;
		used_count = 0U;
		for (i = start_idx; i < end_idx; i++)
		{
			sum += tmp[i];
			used_count++;
		}

		if (used_count == 0U)
		{
			filtered = limited;
		}
		else
		{
			filtered = sum / used_count;
		}
	}

	g_filter_avg_win = used_count;

	if (g_filter_avg_win == 0U)
	{
		g_filter_avg_win = 1U;
	}

	return filtered;
}

static uint32_t Get_Fast_Control_Freq(uint32_t new_raw)
{
	float k_gain;
	float meas;
	static float k_x = 0.0f;
	static float k_p = 10.0f;
	static uint8_t k_init = 0U;

	meas = (float)new_raw;
	if (k_init == 0U)
	{
		k_x = meas;
		k_p = 10.0f;
		k_init = 1U;
		return new_raw;
	}

	k_p += KALMAN_Q_FAST;
	k_gain = k_p / (k_p + KALMAN_R_FAST);
	k_x = k_x + k_gain * (meas - k_x);
	k_p = (1.0f - k_gain) * k_p;
	if (k_x < 0.0f)
	{
		k_x = 0.0f;
	}

	return (uint32_t)(k_x + 0.5f);
}

static uint32_t Get_Ms_Tick(void)
{
	return g_ms_tick;
}

static uint8_t IsElapsed(uint32_t now, uint32_t last, uint32_t period_ms)
{
	return ((uint32_t)(now - last) >= period_ms) ? 1U : 0U;
}

static uint8_t Compute_LO_FreqHz(uint32_t pa0_freq_hz, uint32_t if_target_hz, uint8_t dual_side_mix, uint32_t *rf_est_hz, uint32_t *lo_freq_hz)
{
	uint64_t rf_hz;
	uint32_t lo;

	if ((rf_est_hz == 0) || (lo_freq_hz == 0) || (if_target_hz == 0U))
	{
		return 0U;
	}

	// ��PA0��������ADF��Ƶ��ĵ�Ƶ���Ȼ�ԭ��ԭʼ��Ƶ�ٲ���LO����
	rf_hz = (uint64_t)pa0_freq_hz;
	if ((pa0_freq_hz > 0U) && (pa0_freq_hz <= PA0_DIVIDED_MAX_HZ))
	{
		rf_hz = rf_hz * ADF_R_DIVIDER_VALUE;
	}
	if ((rf_hz == 0ULL) || (rf_hz > 0xFFFFFFFFULL))
	{
		return 0U;
	}
	*rf_est_hz = (uint32_t)rf_hz;

	if (((uint32_t)rf_hz < PA0_FREQ_VALID_MIN_HZ) || ((uint32_t)rf_hz > PA0_FREQ_VALID_MAX_HZ))
	{
		return 0U;
	}
	if (dual_side_mix != 0U)
	{
		if ((uint32_t)rf_hz >= if_target_hz)
		{
			lo = (uint32_t)rf_hz - if_target_hz;
		}
		else
		{
			lo = if_target_hz - (uint32_t)rf_hz;
		}
		if (lo == 0U)
		{
			return 0U;
		}
	}
	else
	{
		if ((uint32_t)rf_hz >= if_target_hz)
		{
			return 0U;
		}

		lo = if_target_hz - (uint32_t)rf_hz;
	}

	if (lo < LO_OUTPUT_MIN_HZ)
	{
		lo = LO_OUTPUT_MIN_HZ;
	}
	if (lo > LO_OUTPUT_MAX_HZ)
	{
		lo = LO_OUTPUT_MAX_HZ;
	}

	*lo_freq_hz = lo;
	return 1U;
}

static uint32_t TIM2_Capture_ReadPeriodTicks(uint32_t wait_loops)
{
	uint32_t guard;
	uint16_t cap1;
	uint16_t cap2;
	uint32_t period_ticks;

	// ÿ�β���ǰ�����־�����������һ����������ֵ
	TIM_ClearFlag(TIM2, TIM_FLAG_CC1 | TIM_FLAG_CC1OF);

	guard = wait_loops;
	while (TIM_GetFlagStatus(TIM2, TIM_FLAG_CC1) == RESET)
	{
		if (guard-- == 0U)
		{
			g_cap_poll_timeout++;
			return 0U;
		}
	}
	cap1 = TIM_GetCapture1(TIM2);
	TIM_ClearFlag(TIM2, TIM_FLAG_CC1 | TIM_FLAG_CC1OF);

	guard = wait_loops;
	while (TIM_GetFlagStatus(TIM2, TIM_FLAG_CC1) == RESET)
	{
		if (guard-- == 0U)
		{
			g_cap_poll_timeout++;
			return 0U;
		}
	}
	cap2 = TIM_GetCapture1(TIM2);
	TIM_ClearFlag(TIM2, TIM_FLAG_CC1 | TIM_FLAG_CC1OF);

	if (cap2 >= cap1)
	{
		period_ticks = (uint32_t)(cap2 - cap1);
	}
	else
	{
		period_ticks = (uint32_t)(0x10000U - cap1 + cap2);
	}

	g_cap_poll_ok++;
	g_cap_last_ticks = period_ticks;

	return period_ticks;
}

static uint32_t TIM2_Capture_WindowFreqHz(uint32_t wait_loops, uint8_t periods, uint8_t *ok)
{
	uint8_t i;
	uint8_t valid_periods = 0U;
	uint32_t period_ticks;
	uint32_t ticks_sum = 0U;

	for (i = 0U; i < periods; i++)
	{
		period_ticks = TIM2_Capture_ReadPeriodTicks(wait_loops);
		if (period_ticks == 0U)
		{
			break;
		}
		ticks_sum += period_ticks;
		valid_periods++;
	}

	if (valid_periods < 2U)
	{
		*ok = 0U;
		return 0U;
	}

	*ok = 1U;
	return ((tim2_counter_hz * TIM2_CAP_EDGE_FACTOR * valid_periods) + (ticks_sum / 2U)) / ticks_sum;
}

static uint32_t Select_Robust_Freq(uint32_t period_hz, uint32_t window_hz)
{
	uint32_t diff;
	uint32_t ref;

	if (period_hz == 0U)
	{
		g_freq_diff_hz = 0U;
		return window_hz;
	}
	if (window_hz == 0U)
	{
		g_freq_diff_hz = 0U;
		return period_hz;
	}

	diff = AbsDiffU32(period_hz, window_hz);
	g_freq_diff_hz = diff;
	ref = (window_hz > 0U) ? window_hz : period_hz;

	if ((diff * 100U) <= (ref * FREQ_MATCH_PCT))
	{
		return (period_hz + window_hz) / 2U;
	}

	// ��һ��ʱ���ȴ��ڷ������͵����ڶ����Ŵ�ЧӦ
	return window_hz;
}

// �ο�����Ǩ�ƣ��������ڷ������Ƶ���ȶ����ж�
static uint32_t Update_Freq_Variance_Hz2(uint32_t sample_hz)
{
	uint8_t i;
	uint8_t count;
	uint64_t sum = 0U;
	uint64_t sum_sq = 0U;

	g_freq_var_window[g_freq_var_pos] = sample_hz;
	if (g_freq_var_len < FREQ_VAR_WINDOW)
	{
		g_freq_var_len++;
	}
	g_freq_var_pos = (uint8_t)((g_freq_var_pos + 1U) % FREQ_VAR_WINDOW);

	if (g_freq_var_len < 2U)
	{
		return 0U;
	}

	count = g_freq_var_len;
	for (i = 0U; i < count; i++)
	{
		uint32_t v = g_freq_var_window[i];
		sum += v;
		sum_sq += (uint64_t)v * (uint64_t)v;
	}

	{
		uint64_t mean = sum / count;
		uint64_t variance = (sum_sq / count) - (mean * mean);
		return (variance > 0xFFFFFFFFULL) ? 0xFFFFFFFFU : (uint32_t)variance;
	}
}

static uint32_t AbsDiffU32(uint32_t a, uint32_t b)
{
	return (a >= b) ? (a - b) : (b - a);
}

static const char *Get_Modulation_Label(uint32_t rf_hz)
{
	if (rf_hz > MOD_FM_THRESHOLD_HZ)
	{
		return "FM";
	}

	return (g_adc_is_ask != 0U) ? "ASK" : "AM";
}

/*
 * ��    ����FFT������Ƶ�����ź�Ƶ�ʣ�Hz��
 * ��    ʽ���̶������ʲ���N�㣬FFT�ҷ�ֵƵ��
 * ��    �������300mVС�źţ������˶�̬ȥֱ������������
 */
static uint32_t FFT_Measure_LowFreq_Hz(uint32_t sample_rate_hz)
{
	uint16_t i;
	uint16_t max_bin = 0;
	uint32_t max_mag = 0;
	uint32_t dc_sum = 0;
	int32_t dc_avg = 0;
	uint32_t wait_timeout;
	if (sample_rate_hz == 0U)
	{
		g_adc_is_ask = 0U;
		return 0U;
	}

	// ��һ������TIM3���½��Ĳ������ۼ�ֱ��ƫ��
	// ע�⣺fft_in������ʱ���棬������ǰFFT_SAMPLES��λ�ô��ԭʼADC����
	for (i = 0; i < FFT_SAMPLES; i++)
	{
		uint16_t cur;
		wait_timeout = FFT_TIMER_WAIT_TIMEOUT;
		while (TIM_GetFlagStatus(TIM3, TIM_FLAG_Update) == RESET)
		{
			if (wait_timeout-- == 0U)
			{
				g_adc_is_ask = 0U;
				return 0U;
			}
		}
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		cur = AD_GetValue(ADC_Channel_4);
		fft_in[i] = (int16_t)cur;
		dc_sum += cur;
	}

	dc_avg = dc_sum / FFT_SAMPLES;

	// �ڶ���������ȥֱ�����ʱ���ֵ��RMS�����ڲ��η�ֵ�����ж���
	uint32_t peak_val = 0U;    // ȥֱ����ķ�ֵ
	uint64_t rms_sq = 0ULL;    // RMSƽ���ۼ�
	for (i = 0; i < FFT_SAMPLES; i++)
	{
		int32_t val = (int32_t)fft_in[i] - dc_avg;
		uint32_t abs_val = (val < 0) ? (uint32_t)(-val) : (uint32_t)val;
		if (abs_val > peak_val) {
			peak_val = abs_val;
		}
		rms_sq += (uint64_t)val * val;
	}

	// ��������������Ӧ��Hann���ڽ���FFTƵ�ʼ���
	for (i = FFT_SAMPLES; i > 0; i--)
	{
		uint16_t idx = i - 1;
		int32_t val = (int32_t)fft_in[idx] - dc_avg;
		/* Apply Hann window to reduce spectral leakage */
		float w = 0.5f * (1.0f - cosf(2.0f * 3.14159265358979323846f * (float)idx / (float)(FFT_SAMPLES - 1)));
		int32_t windowed = (int32_t)((val << 6) * w);
		fft_in[2 * idx] = (int16_t)windowed;
		fft_in[2 * idx + 1] = 0;
	}

	// ��������ִ��1024��FFT (����ԭ�������õ�256�㺯��)
	cr4_fft_1024_stm32(fft_out, fft_in, FFT_SAMPLES);

	// ���Ĳ���Ѱ�ҷ������ֵ���ܿ�ֱ������Bin 0��
	for (i = 1; i < (FFT_SAMPLES / 2); i++)
	{
		int16_t re = fft_out[2 * i];
		int16_t im = fft_out[2 * i + 1];
		// ����ԭ������ֱ��תuint32���µĸ���ƽ���������
		uint32_t mag = (uint32_t)(re * re) + (uint32_t)(im * im);
		if (mag > max_mag)
		{
			max_mag = mag;
			max_bin = i;
		}
	}

	if (max_bin == 0)
	{
		g_adc_is_ask = 0U;
		return 0;
	}

	/* ����Ƿ�Ϊ��Ƶ������Ϊ2*f��������Ƶ��������������˵���Ƶ��Ϊ���� */
	{
		uint16_t half_bin = (uint16_t)(max_bin / 2U);
		uint32_t half_mag = 0U;
		if ((max_bin >= 2U) && (half_bin > 0U))
		{
			int16_t reh = fft_out[2U * half_bin];
			int16_t imh = fft_out[2U * half_bin + 1U];
			half_mag = (uint32_t)(reh * reh) + (uint32_t)(imh * imh);
			if ((max_mag > 0U) && ((uint64_t)half_mag * 100ULL >= (uint64_t)max_mag * FUND_RESTORE_PCT))
			{
				max_bin = half_bin; /* ������ѡΪ��Ƶ */
				max_mag = half_mag;
			}
		}
	}

	// ASK�ж����ò��η�ֵ���Ӷ���H3����
	// ���Ҳ���peak / RMS �� 1.414
	// ������peak / RMS �� 1.0
	uint32_t rms_val = 0U;
	uint32_t peak_rms_ratio_x100 = 0U;  // peak/RMS * 100
	
	if (rms_sq > 0ULL)
	{
		// RMS = sqrt(sum(val^2) / N)�����������⸡�㾫������
		// ��ֹ��������
		if (rms_var == 0ULL) rms_var = 1ULL;
		if (x == 0ULL) x = 1ULL;
		if (x > 100000000ULL) x = 100000000ULL; // �������ֵ��ֹ���
		uint64_t rms_var = rms_sq / FFT_SAMPLES;
		// ��sqrtf����ţ�ٷ����ٱƽ�
		uint64_t x = rms_var;
		uint64_t x_next = (x + rms_var / x) / 2ULL;
		while (x_next < x) {
			x = x_next;
			x_next = (x + rms_var / x) / 2ULL;
		}
		rms_val = (uint32_t)x;
		
		if (rms_val > 0U)
		{
			// peak/RMS * 100�����ڱ��⸡��
			peak_rms_ratio_x100 = (peak_val * 100U) / rms_val;
			g_peak_rms_ratio_x100 = peak_rms_ratio_x100;  // ����ȫ�ֱ����Թ�OLED��ʾ
		}
	}
	
	/* �ж�����peak/RMS > 1.2 �� ���Ҳ���AM������1.2 �� ������ASK��
	   �ø����ɺ�³�����ж������ratio > 125����1.25������Ϊ���ң�<125��Ϊ���� */
	uint8_t is_sine_wave;
	if (peak_rms_ratio_x100 >= 125U)  // ��1.25 ��Ϊ���Ҳ�
	{
		is_sine_wave = 1U;
	}
	else if (peak_rms_ratio_x100 <= 105U)  // ��1.05 ��Ϊ����
	{
		is_sine_wave = 0U;
	}
	else
	{
		// 105-125 ֮���򱣳�֮ǰ���ж������ⶶ��
		is_sine_wave = g_adc_is_ask ? 0U : 1U;
	}
	
	if (is_sine_wave)
	{
		// ���Ҳ����� �� AM
		if (g_ask_score > 0) g_ask_score--;
	}
	else
	{
		// �������� �� ASK
		if (g_ask_score < ASK_SCORE_MAX) g_ask_score++;
	}

	/* score-based hysteresis */
	if (g_ask_score >= ASK_SCORE_ENTER)
	{
		g_adc_is_ask = 1U;
	}
	else if (g_ask_score <= ASK_SCORE_EXIT)
	{
		g_adc_is_ask = 0U;
	}
	/* �����������¼��ֵ���ӡ�������ASK״̬��ÿ100�β���Լ100ms1�Σ� */
	static uint32_t debug_cnt = 0U;
	if (++debug_cnt >= 100U) {
		debug_cnt = 0U;
		printf("Waveform: peak=%lu rms=%lu ratio=%.2f is_sine=%u score=%d ask=%u\r\n",
		       (unsigned long)peak_val, (unsigned long)rms_val, 
		       (float)peak_rms_ratio_x100 / 100.0f, (unsigned)is_sine_wave, 
		       (int)g_ask_score, (unsigned)g_adc_is_ask);
	}

	return (sample_rate_hz * max_bin) / FFT_SAMPLES;
}

/**
  * ��    ������ȡADת����ֵ
  * ��    ����ADC_Channel ָ��ADת����ͨ������Χ��ADC_Channel_x������x������0/1/2/3
  * �� �� ֵ��ADת����ֵ����Χ��0~4095
  */
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	uint32_t timeout = ADC_CONV_TIMEOUT;

	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);	//��ÿ��ת��ǰ�����ݺ����β������Ĺ������ͨ��1
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					//��������ADת��һ��
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)	//�ȴ�EOC��־λ�����ȴ�ADת������
	{
		if (timeout-- == 0U)
		{
			return 0U;
		}
	}
	return ADC_GetConversionValue(ADC1);					//�����ݼĴ������õ�ADת���Ľ��
}

float Get_Current_Frequency(void)
{
	// recognizeģ��ʹ�ø�ֵ����ֵ�Ƚϣ����ﰴfreq_hz/100����
	return (float)freq_hz / 100.0f;
}

uint16_t Get_ADC_Average(uint8_t times)
{
	uint32_t sum = 0U;
	uint8_t i;

	if (times == 0U)
	{
		times = 1U;
	}

	for (i = 0U; i < times; i++)
	{
		sum += AD_GetValue(ADC_Channel_4);
	}

	return (uint16_t)(sum / times);
}

/* ============================================================
 * 模式2: 2ASK 发送机 (TX_2ASK)
 * 键盘输入 → 编码 → AD9833 → 2ASK输出
 * ============================================================ */
#if WORK_MODE == 1
static void main_tx_2ask(void)
{
    uint8_t key;
    uint8_t tx_buffer[8];
    uint8_t tx_len = 0;
    uint32_t last_tx_tick = 0;
    uint32_t now_ms;

    /* 初始化 */
    delay_init(72);
    USARTx_Init(9600);
    OLED_Init();
    KEYBOARD_Init();
    AD9833_Init();
    ENCODE_Init();

    /* 显示空闲界面 */
    if (OLED_IsReady())
    {
        OLED_Clear();
        OLED_ShowString(1, 1, "2ASK TX MODE");
        OLED_ShowString(2, 1, "INPUT:HEX");
        OLED_ShowString(4, 1, "A=Send");
    }
    printf("2ASK TX mode started\r\n");

    now_ms = Get_Ms_Tick();
    last_tx_tick = now_ms;

    while (1)
    {
        now_ms = Get_Ms_Tick();

        /* 扫描键盘 */
        key = KEYBOARD_Scan();
        if (key != KEY_NONE)
        {
            if (key == KEY_A)
            {
                /* A键: 发送当前缓冲区数据 */
                if (tx_len > 0)
                {
                    ENCODE_SendData(tx_buffer, tx_len);
                    printf("TX: send %u bytes\r\n", (unsigned)tx_len);
                    if (OLED_IsReady())
                    {
                        OLED_ShowString(3, 1, "SENDING...   ");
                    }
                }
            }
            else if (key == KEY_B)
            {
                /* B键: 模式切换/退出 */
                printf("TX: mode switch\r\n");
            }
            else if (key == KEY_D)
            {
                /* D键: 清除 */
                tx_len = 0;
                printf("TX: buffer cleared\r\n");
                if (OLED_IsReady())
                {
                    OLED_ShowString(3, 1, "CLR         ");
                }
            }
            else if (tx_len < sizeof(tx_buffer))
            {
                /* 数字/A-F: 输入十六进制数据 */
                tx_buffer[tx_len++] = key;
                printf("TX: data[%u]=0x%01X\r\n", (unsigned)(tx_len-1), (unsigned)key);
                if (OLED_IsReady())
                {
                    char line[17];
                    uint8_t i;
                    for (i = 0; i < tx_len && i < 8; i++)
                    {
                        line[i] = ENCODE_HexToAscii(tx_buffer[i]);
                    }
                    line[i] = '\0';
                    OLED_ShowString(2, 1, "                ");
                    OLED_ShowString(2, 1, line);
                }
            }
        }

        /* 驱动编码状态机 (100Hz) */
        if (IsElapsed(now_ms, last_tx_tick, 10))
        {
            last_tx_tick = now_ms;
            ENCODE_TxTicker();
        }

        delay_ms(5);
    }
}
#endif /* WORK_MODE == 1 */

/* ============================================================
 * 模式3: FPGA双路数字滤波接收机 (RX_FPGA)
 * FPGA LPF/BPF → 解码2ASK → 74HC595/OLED显示
 * ============================================================ */
#if WORK_MODE == 2
static void main_rx_fpga(void)
{
    uint32_t now_ms;
    uint32_t last_fpga_ms = 0;
    uint32_t last_display_ms = 0;
    uint16_t lpf_val = 0;
    uint16_t bpf_val = 0;
    uint8_t fpga_status = 0;
    uint8_t ask_bit = 0;
    uint8_t rx_byte = 0;
    uint8_t data_valid;

    delay_init(72);
    USARTx_Init(9600);
    OLED_Init();
    FPGA_IF_Init();
    DECODE_Init();

    /* 初始化74HC595用于数码管显示 */
    Output_GPIOInit595();

    if (OLED_IsReady())
    {
        OLED_Clear();
        OLED_ShowString(1, 1, "RX FPGA MODE");
        OLED_ShowString(2, 1, "FILTER:ON");
    }
    printf("RX FPGA mode started\r\n");

    now_ms = Get_Ms_Tick();
    last_fpga_ms = now_ms;
    last_display_ms = now_ms;

    while (1)
    {
        now_ms = Get_Ms_Tick();

        /* 轮询FPGA */
        if (IsElapsed(now_ms, last_fpga_ms, RX_FPGA_POLL_MS))
        {
            last_fpga_ms = now_ms;

            /* 读状态 */
            fpga_status = FPGA_IF_Status();
            data_valid = (fpga_status & 0x01) ? 1 : 0;

            if (data_valid)
            {
                /* 读滤波输出 */
                lpf_val = FPGA_IF_ReadLPF();
                bpf_val = FPGA_IF_ReadBPF();

                /* 读2ASK解码数据位 */
                ask_bit = (FPGA_IF_ReadASKData() & 0x80) ? 1 : 0;

                /* 喂给解码器 */
                DECODE_FeedBit(ask_bit);

                /* 检查是否有完整字节 */
                if (DECODE_GetByte(&rx_byte))
                {
                    printf("RX: 0x%02X ('%c')\r\n",
                           (unsigned)rx_byte,
                           (rx_byte >= 0x20 && rx_byte <= 0x7E) ? (char)rx_byte : '.');
                }
            }
        }

        /* OLED/数码管更新 (200ms) */
        if (IsElapsed(now_ms, last_display_ms, 200))
        {
            last_display_ms = now_ms;

            if (OLED_IsReady())
            {
                char line[17];
                (void)snprintf(line, sizeof(line), "LPF:%04u", (unsigned)(lpf_val >> 4));
                OLED_ShowString(3, 1, line);
                (void)snprintf(line, sizeof(line), "BPF:%04u", (unsigned)(bpf_val >> 4));
                OLED_ShowString(4, 1, line);
            }
        }

        delay_ms(5);
    }
}
#endif /* WORK_MODE == 2 */

int main(void)
{
#if WORK_MODE == 1
    main_tx_2ask();
    return 0;
#elif WORK_MODE == 2
    main_rx_fpga();
    return 0;
#endif
    /* WORK_MODE == 0: legacy RX mode (original code) */

	uint8_t alive = 0U;
	uint8_t freq_updated = 0U;
	uint8_t oled_retry_count = 0;
	uint8_t no_capture_loops = 0;
	uint8_t lo_valid = 0;
	uint8_t rda_lock = 0;
	uint8_t rda_init_ok = 0;
	uint8_t rda_rssi = 0;
	uint32_t now_ms = 0U;
	uint32_t last_capture_ms = 0U;
	uint32_t last_oled_ms = 0U;
	uint32_t last_log_ms = 0U;
	uint32_t last_rda_ms = 0U;
	uint32_t last_oled_retry_ms = 0U;
	uint32_t last_adc_ms = 0U;
	uint32_t adc_freq_hz = 0U;
	uint32_t freq_ctrl_hz = 0U;
	uint32_t freq_disp_hz = 0U;
	uint32_t freq_var_hz2 = 0U;
	uint32_t rf_est_hz = 0U;
	uint32_t lo_freq_hz = 0U;
	uint32_t lo_source_hz = 0U;
	uint32_t last_lo_freq_hz = 0U;
	uint32_t lo_show_khz = 0U;
	uint32_t if_target_hz = FM_IF_TARGET_HZ;
	float if_target_mhz = FM_IF_TARGET_MHZ;
	uint8_t mode_is_fm = 1U;
	uint8_t mode_changed = 0U;
	uint8_t rda_audio_muted = 1U;
	uint8_t rda_lock_ok_cnt = 0U;
	uint8_t rda_lock_lost_cnt = 0U;
	uint8_t rda_rssi_prev = 0U;
	uint8_t rda_rssi_stable_cnt = 0U;
	uint8_t rda_rssi_stable = 0U;
	uint8_t freq_unstable = 0U;

	delay_init(72);
	AD_Init();
	TIM3_SampleClock_Init(FFT_SAMPLE_RATE_HZ);
	USARTx_Init(9600);
	OLED_Init();
	if (!OLED_IsReady())
	{
		printf("OLED init failed: err=%u, addr=0x%02X, nack=%u\r\n",
		       (unsigned int)OLED_GetInitError(),
		       (unsigned int)(OLED_GetI2CAddress() << 1),
		       (unsigned int)OLED_GetAckFailCount());
		for (oled_retry_count = 0; oled_retry_count < 3U && !OLED_IsReady(); oled_retry_count++)
		{
			delay_ms(1000);
			OLED_Init();
		}
		printf("OLED retry done: ready=%u, err=%u, addr=0x%02X, nack=%u\r\n",
		       (unsigned int)OLED_IsReady(),
		       (unsigned int)OLED_GetInitError(),
		       (unsigned int)(OLED_GetI2CAddress() << 1),
		       (unsigned int)OLED_GetAckFailCount());
	}
	else
	{
		printf("OLED ready at addr=0x%02X\r\n", (unsigned int)(OLED_GetI2CAddress() << 1));
	}

	Recognize_Init();
	Recognize_SetMode(MODE_FM);
	ad9851_GPIOInit();
	ad9851_reset_serial();
	rda_init_ok = (RDA5820_Init() == 0U) ? 1U : 0U;
	if (rda_init_ok)
	{
		RDA5820_Vol_Set(0U);
		RDA5820_Mute_Set(1U);
		RDA5820_SetFreq(FM_IF_TARGET_MHZ);
	}
	printf("FM RX test: carrier=90MHz, mod=1kHz, dev=40kHz, RDA tune=90.0MHz\r\n");
	printf("Path select PA5 set to FM\r\n");

	InitADF4002();
	RDivideTest(10000);	// ADF4002 R counter divider = 10000
	printf("ADF4002 divider configured: R=10000\r\n");
	if (OLED_IsReady())
	{
		OLED_ShowString(1, 1, "BOOT:TIM2 CAP   ");
		OLED_ShowString(2, 1, "STEP:TIM2 INIT  ");
	}
	printf("TIM2 capture display mode enabled\r\n");
#if USE_TIM4_TIMEBASE
	TIM4_Timebase_Init();
#else
	// ʹ������ʱ�������⹤���ж��������쵼�³�ʼ������
	g_ms_tick = 0U;
#endif
	TIM2_InputCapture_Init();
#if TIM2_USE_IRQ_CAPTURE
	printf("TIM2 mode: IRQ capture\r\n");
#else
	printf("TIM2 mode: polling capture\r\n");
#endif
	if (OLED_IsReady())
	{
		OLED_ShowString(2, 1, "STEP:RUN MODE   ");
	}

	if (OLED_IsReady())
	{
		OLED_Clear();
		OLED_ShowString(1, 1, "CAP:00000000Hz");
		OLED_ShowString(2, 1, "LO:00000kHz   ");
		OLED_ShowString(3, 1, "ADC:00000Hz    ");
		OLED_ShowString(4, 1, "LK:- RS:- M:---");
	}
	printf("TIM2 capture + LO auto set + RDA demod mode start\r\n");
	now_ms = Get_Ms_Tick();
	last_capture_ms = now_ms;
	last_oled_ms = now_ms;
	last_log_ms = now_ms;
	last_rda_ms = now_ms;
	last_oled_retry_ms = now_ms;
	last_adc_ms = now_ms;

	while (1)
	{
		now_ms = Get_Ms_Tick();
		freq_updated = 0U;

#if TIM2_USE_IRQ_CAPTURE
		if (g_New_Freq_Ready)
		{
			uint32_t period_ticks = g_Period_Ticks;
			g_New_Freq_Ready = 0;

			if (period_ticks > 0U)
			{
				no_capture_loops = 0;
				last_capture_ms = now_ms;
				g_period_freq_hz = ((tim2_counter_hz * TIM2_CAP_EDGE_FACTOR) + (period_ticks / 2U)) / period_ticks;
				g_window_freq_hz = 0U;
				g_freq_diff_hz = 0U;
				raw_freq_hz = g_period_freq_hz;
				freq_updated = 1U;
			}
		}
		if (IsElapsed(now_ms, last_capture_ms, CAPTURE_TIMEOUT_MS))
		{
			last_capture_ms = now_ms;
			if (no_capture_loops < 255U)
			{
				no_capture_loops++;
			}
		}
#else
		if (IsElapsed(now_ms, last_capture_ms, CAP_LOOP_DELAY_MS))
		{
			uint8_t window_ok = 0U;
			uint32_t period_ticks = TIM2_Capture_ReadPeriodTicks(TIM2_POLL_WAIT_LOOPS);
			last_capture_ms = now_ms;
			if (period_ticks > 0U)
			{
				no_capture_loops = 0;
				g_period_freq_hz = ((tim2_counter_hz * TIM2_CAP_EDGE_FACTOR) + (period_ticks / 2U)) / period_ticks;
				g_window_freq_hz = TIM2_Capture_WindowFreqHz(TIM2_POLL_WAIT_LOOPS, TIM2_WINDOW_PERIODS, &window_ok);
				if (!window_ok)
				{
					g_window_freq_hz = 0U;
				}
				raw_freq_hz = Select_Robust_Freq(g_period_freq_hz, g_window_freq_hz);
				freq_updated = 1U;
			}
			else if (no_capture_loops < 255U)
			{
				g_period_freq_hz = 0U;
				g_window_freq_hz = 0U;
				g_freq_diff_hz = 0U;
				no_capture_loops++;
			}
		}
#endif

		if (freq_updated)
		{
			freq_ctrl_hz = Get_Fast_Control_Freq(raw_freq_hz);
			freq_disp_hz = Get_Filtered_Freq(raw_freq_hz);
			freq_hz = freq_disp_hz;
			freq_var_hz2 = Update_Freq_Variance_Hz2(freq_ctrl_hz);
			freq_unstable = (freq_var_hz2 > FREQ_VAR_THRESHOLD_HZ2) ? 1U : 0U;
		}

		if (no_capture_loops >= NO_CAPTURE_MAX_LOOPS)
		{
			g_period_freq_hz = 0U;
			g_window_freq_hz = 0U;
			g_freq_diff_hz = 0U;
			raw_freq_hz = 0U;
			freq_hz = 0U;
			freq_ctrl_hz = 0U;
			freq_disp_hz = 0U;
			freq_var_hz2 = 0U;
			freq_unstable = 0U;
		}

		mode_changed = 0U;
		if (freq_hz > MODE_SWITCH_TH_HZ)
		{
			if (mode_is_fm == 0U)
			{
				mode_is_fm = 1U;
				mode_changed = 1U;
			}
			if_target_hz = FM_IF_TARGET_HZ;
			if_target_mhz = FM_IF_TARGET_MHZ;
		}
		else
		{
			if (mode_is_fm != 0U)
			{
				mode_is_fm = 0U;
				mode_changed = 1U;
			}
			if_target_hz = AM_IF_TARGET_HZ;
			if_target_mhz = AM_IF_TARGET_MHZ;
		}

		if (mode_changed)
		{
			last_lo_freq_hz = 0U;
			Recognize_SetMode((mode_is_fm != 0U) ? MODE_FM : MODE_AM);
			if (rda_init_ok && (mode_is_fm != 0U))
			{
				RDA5820_SetFreq(FM_IF_TARGET_MHZ);
			}
			printf("Mode switch: %s, target=%.1fMHz\r\n", (mode_is_fm != 0U) ? "FM" : "AM", if_target_mhz);
		}

		lo_source_hz = (freq_unstable != 0U) ? freq_disp_hz : freq_ctrl_hz;
		lo_valid = Compute_LO_FreqHz(lo_source_hz, if_target_hz, (mode_is_fm != 0U) ? 0U : 1U, &rf_est_hz, &lo_freq_hz);
		if (lo_valid)
		{
			if ((last_lo_freq_hz == 0U) || (AbsDiffU32(lo_freq_hz, last_lo_freq_hz) >= LO_UPDATE_HYST_HZ))
			{
				ad9851_write((double)lo_freq_hz, 0.0, (uint8_t)(ad9851_fd | ad9851_on));
				last_lo_freq_hz = lo_freq_hz;
			}
			lo_show_khz = lo_freq_hz / 1000U;
		}
		else
		{
			rf_est_hz = 0U;
			lo_show_khz = (last_lo_freq_hz > 0U) ? (last_lo_freq_hz / 1000U) : 0U;
		}

		if (rda_init_ok && IsElapsed(now_ms, last_rda_ms, SCHED_RDA_MS))
		{
			uint8_t rssi_diff;
			last_rda_ms = now_ms;
			rda_rssi = RDA5820_Read_RSSI();
			rda_lock = RDA5820_Check_Lock();

			rssi_diff = (rda_rssi >= rda_rssi_prev) ? (uint8_t)(rda_rssi - rda_rssi_prev) : (uint8_t)(rda_rssi_prev - rda_rssi);
			rda_rssi_prev = rda_rssi;
			if (rssi_diff <= 3U)
			{
				if (rda_rssi_stable_cnt < 255U)
				{
					rda_rssi_stable_cnt++;
				}
			}
			else
			{
				rda_rssi_stable_cnt = 0U;
			}
			rda_rssi_stable = (rda_rssi_stable_cnt >= 3U) ? 1U : 0U;

			if (rda_lock != 0U)
			{
				if (rda_lock_ok_cnt < 255U)
				{
					rda_lock_ok_cnt++;
				}
				rda_lock_lost_cnt = 0U;
				if ((rda_audio_muted != 0U) && (rda_lock_ok_cnt >= RDA_LOCK_AUDIO_CNT))
				{
					RDA5820_Vol_Set(15U);
					RDA5820_Mute_Set(0U);
					rda_audio_muted = 0U;
				}
			}
			else
			{
				if (rda_lock_lost_cnt < 255U)
				{
					rda_lock_lost_cnt++;
				}
				rda_lock_ok_cnt = 0U;

				if ((rda_audio_muted == 0U) && (rda_lock_lost_cnt >= 5U))
				{
					RDA5820_Mute_Set(1U);
					RDA5820_Vol_Set(0U);
					rda_audio_muted = 1U;
				}

				if ((mode_is_fm != 0U) && (rda_lock_lost_cnt >= RDA_RELOCK_START_CNT) && ((rda_lock_lost_cnt % RDA_RELOCK_STEP_CNT) == 0U))
				{
					RDA5820_SetFreq(FM_IF_TARGET_MHZ);
				}
			}
		}

		if (IsElapsed(now_ms, last_adc_ms, SCHED_ADC_MS))
		{
			last_adc_ms = now_ms;
			adc_freq_hz = FFT_Measure_LowFreq_Hz(FFT_SAMPLE_RATE_HZ);
			if (adc_freq_hz > 5000U)
			{
				adc_freq_hz = 0U;
			}
		}

		if (!OLED_IsReady())
		{
			if (IsElapsed(now_ms, last_oled_retry_ms, SCHED_OLED_RETRY_MS))
			{
				last_oled_retry_ms = now_ms;
				OLED_Init();
				printf("OLED retry: ready=%u, err=%u, addr=0x%02X, nack=%u\r\n",
				       (unsigned int)OLED_IsReady(),
				       (unsigned int)OLED_GetInitError(),
				       (unsigned int)(OLED_GetI2CAddress() << 1),
				       (unsigned int)OLED_GetAckFailCount());
				if (OLED_IsReady())
				{
					char lock_rssi_status[17];
					char lk = '-';
					char rs = '-';
					const char *mod_label = "---";
					OLED_Clear();
					OLED_ShowString(1, 1, "CAP:00000000Hz");
					OLED_ShowString(2, 1, "LO:00000kHz   ");
					{
						char adc_line[17];
						(void)snprintf(adc_line, sizeof(adc_line), "ADC:%5luHz    ", (unsigned long)adc_freq_hz);
						OLED_ShowString(3, 1, adc_line);
					}
					if (rda_init_ok)
					{
						lk = (rda_lock_ok_cnt >= RDA_LOCK_DISPLAY_CNT) ? 'S' : 'U';
						rs = (rda_rssi_stable != 0U) ? 'S' : 'U';
						mod_label = Get_Modulation_Label(rf_est_hz);
						(void)snprintf(lock_rssi_status, sizeof(lock_rssi_status), "R:%d.%02d C:%c", 
						              g_peak_rms_ratio_x100 / 100U, g_peak_rms_ratio_x100 % 100U,
						              g_adc_is_ask ? 'A' : 'M');
					}
					else
					{
						(void)snprintf(lock_rssi_status, sizeof(lock_rssi_status), "R:--.-- C:-");
					}
					OLED_ShowString(4, 1, lock_rssi_status);
				}
			}
		}
		else if (IsElapsed(now_ms, last_oled_ms, SCHED_OLED_MS))
		{
			char lock_rssi_status[17];
			char lk = '-';
			char rs = '-';
			const char *mod_label = "---";
			last_oled_ms = now_ms;
			alive ^= 1U;
			OLED_ShowNum(1, 5, freq_hz, 8);
			OLED_ShowNum(2, 4, (lo_show_khz % 100000U), 5);
			{
				char adc_line[17];
				(void)snprintf(adc_line, sizeof(adc_line), "ADC:%5luHz    ", (unsigned long)adc_freq_hz);
				OLED_ShowString(3, 1, adc_line);
			}
			if (rda_init_ok)
			{
				lk = (rda_lock_ok_cnt >= RDA_LOCK_DISPLAY_CNT) ? 'S' : 'U';
				rs = (rda_rssi_stable != 0U) ? 'S' : 'U';
				mod_label = Get_Modulation_Label(rf_est_hz);
				(void)snprintf(lock_rssi_status, sizeof(lock_rssi_status), "R:%d.%02d C:%c", 
				              g_peak_rms_ratio_x100 / 100U, g_peak_rms_ratio_x100 % 100U,
				              g_adc_is_ask ? 'A' : 'M');
			}
			else
			{
				(void)snprintf(lock_rssi_status, sizeof(lock_rssi_status), "LK:- RS:- M:---");
			}
			OLED_ShowString(4, 1, lock_rssi_status);
		}

		if (IsElapsed(now_ms, last_log_ms, SCHED_LOG_MS))
		{
			last_log_ms = now_ms;
			printf("CAP=%lu raw=%lu ctrl=%lu var=%lu st=%u mode=%s IF=%luHz RF=%luHz LO=%luHz valid=%u RSSI=%u LOCK=%u\r\n",
			       (unsigned long)freq_hz,
			       (unsigned long)raw_freq_hz,
			       (unsigned long)freq_ctrl_hz,
			       (unsigned long)freq_var_hz2,
			       (unsigned int)freq_unstable,
			       (mode_is_fm != 0U) ? "FM" : "AM",
			       (unsigned long)if_target_hz,
			       (unsigned long)rf_est_hz,
			       (unsigned long)last_lo_freq_hz,
			       (unsigned int)lo_valid,
			       (unsigned int)rda_rssi,
			       (unsigned int)rda_lock);
		}

#if USE_TIM4_TIMEBASE
		/* TIM4�ж�ά��g_ms_tick */
#else
		delay_ms(5);
		g_ms_tick += 5U;
#endif
	}
}


