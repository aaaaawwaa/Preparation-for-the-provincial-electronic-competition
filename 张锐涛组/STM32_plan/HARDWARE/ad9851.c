#include "stm32f10x.h"                  // Device header
#include "ad9851.h"
//这代码同样适用于ad9850，只是系统频率改变时需要更改一些参数
//以下代码仅使用串行通信

void ad9851_GPIOInit(void)//管脚初始化
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//开启时钟
	RCC_APB2PeriphClockCmd(ad9851_RCC, ENABLE);
	//管脚选择与配置
	GPIO_InitStruct.GPIO_Pin = ad9851_d7|ad9851_rest|ad9851_fq|ad9851_clk;
	GPIO_InitStruct.GPIO_Speed = ad9851GPIO_spee;
	GPIO_InitStruct.GPIO_Mode = ad9851GPIO_mode; 
	//初始化管脚
	GPIO_Init(ad9851_pin_type, &GPIO_InitStruct);
}
//              ad9851复位（回归并口模式）                //
//---------------------------------------------------//
void ad9851_reset()
{
    clk_ad9851(0);
    fq_ad9851(0);
    //rest信号
    rest_ad9851(0);
    rest_ad9851(1);
    rest_ad9851(0);
}
//***************************************************//
//              ad9851复位（回归串口模式）                 //
//---------------------------------------------------//
void ad9851_reset_serial()
{
    clk_ad9851(0);
    fq_ad9851(0);
    //rest信号
    rest_ad9851(0);
    rest_ad9851(1);
    rest_ad9851(0);
    //clk信号
    clk_ad9851(0);
    clk_ad9851(1);
    clk_ad9851(0);
    //fq_up信号
    fq_ad9851(0);
    fq_ad9851(1);
    fq_ad9851(0);
}

//频率转换3个字节的函数，f_out=(f_reg*f_system)/2^32;
//f_out为我们目标频率；
//f_reg为我们书写进去的频率寄存器的值

uint32_t ad9851_fre_trun(double fre,uint8_t control)//单位Hz
{
    double x;
    uint32_t fre_reg;
    
    x=4294967295;    //2^32;
    
    if(control&0x01)
        fre_reg=(uint32_t)(x*fre/(ad9851f_system*6));
    else
        fre_reg=(uint32_t)(x*fre/ad9851f_system);
    
    return fre_reg;
}


//相位转换，控制字W0，属于高位，串行最后写入，并行最先写入
//相位分辨率：36/32=11.25度，这一点需要注意
uint32_t ad9851_phase_trun(double phase,uint8_t control)//单位Hz,范围0-360,间隔11.25度；
{
    uint8_t phase_reg=0;
    
    for(uint8_t i=0;i<32;i++)
    {
        if(phase >= (double)i * 11.25 && phase < (double)(i + 1U) * 11.25)
        {
            phase_reg=i;
            break;
        }
    }
    
    return ((phase_reg<<3)|control);
}

void ad9851_write(double fre,double phase,uint8_t control)
{
    uint32_t fre_reg;
    uint8_t phase_reg;//控制字也在这一个字节，phase只占5位；
    
    phase_reg =ad9851_phase_trun(phase,control);
    fre_reg   =ad9851_fre_trun(fre,control);
    
    ad9851_reset_serial();
	
	for(int i=0;i<32;i++)
	{
		if(fre_reg>>i&0x00000001)d7_ad9851(1);
		else d7_ad9851(0);
		clk_ad9851(1);
		clk_ad9851(0);
	}
	for(int i=0;i<8;i++)
	{
		if(phase_reg>>i&0x01)d7_ad9851(1);
		else d7_ad9851(0);
		clk_ad9851(1);
		clk_ad9851(0);
	}
	fq_ad9851(1);
    fq_ad9851(0);
}

/*
 * 2ASK符号调制 (用于替代AD9833)
 * bit=1: 输出11.5kHz载波
 * bit=0: 关闭DAC输出
 */
void AD9851_ASK_Symbol(uint8_t bit)
{
    if (bit)
        ad9851_write(AD9851_ASK_CARRIER_HZ, 0.0, ad9851_fd | ad9851_on);
    else
        ad9851_write(AD9851_ASK_CARRIER_HZ, 0.0, ad9851_fd | ad9851_off);
}
