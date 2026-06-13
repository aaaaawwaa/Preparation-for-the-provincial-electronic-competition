#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "74HC595.h"

//不带小数点的4位数码管
const u8 LED_OF1[] = 
{// 0	 1	  2	   3	  4	    5	   6	   7	  8	  9	   A	   b	 C     d	  E    F    -   灭
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xBF,0xFF};

//带小数点的4位数码管
const u8 LED_OF2[] = 
{// 0	 1	  2	   3	  4	    5	   6	   7	  8	  9	   A	   b	 C     d	  E    F    -   灭
	0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x0C,0x3F,0x46,0x21,0x06,0x7F,0x3F,0xFF};
//顺序不对改这里
//const u8 LED_set[4]={0x08,0x04,0x02,0x01};
const u8 LED_set[4]={0x01,0x02,0x04,0x08};


#define mokuai_num 3//外接模块数目
/*
 * 74HC595 GPIO mapping used by this module:
 * PB5 -> SCLK, PB6 -> RCLK, PB7 -> DATA.
 * Note: PB5/PB6/PB7 overlap with AD9851 control pins in this project.
 */
#define SCLK595(x)  GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction)(x)) //定义管脚//上升沿写入数据
#define RCLK595(x)  GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(x)) //上升沿锁存数据，此时数码管数据更换
#define DATA595(x)  GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)(x)) //数据

void Output_GPIOInit595(void)//初始化管脚
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//在某一位置显示某一数字，不熄灭，直至下一次写入改变
void write_bit595(u8 place,u8 num,point mypoint)//num=16表示负号,place左到右0数起
{  
	u8 bit_num=place/4;//确定属于哪一个数码管，分0-3，4-7。。。
	u8 place_num=place%4;//确定在数码管中的位置；
	RCLK595(0);
	DATA595(0);
	SCLK595(0);

	for(u8 i=0;i<mokuai_num;i++)//清0
		for(u8 j=0;j<16;j++)
		{	DATA595(0);
			SCLK595(0);
			SCLK595(1);
}
	
	u8 place_set=LED_set[place_num];//写入数据
	if(mypoint)
	{	
		u8 data=LED_OF2[num];
		
		for(u8 i=0;i<8;i++)//写入数字
		{	if(data&0x80)DATA595(1);
			else DATA595(0);
			SCLK595(0);
			SCLK595(1);
			data<<=1;}
		
		for(u8 i=0;i<8;i++)//写入位置
		{
			if(place_set&0x80)DATA595(1);
			else DATA595(0);
			SCLK595(0);
			SCLK595(1);
			place_set<<=1;}
		
		for(u8 i=0;i<bit_num;i++)//推进位置
			for(u8 j=0;j<16;j++)
			{	DATA595(0);
				SCLK595(0);
				SCLK595(1);	}	
		}
		
		
	else
	{	u8 data=LED_OF1[num];
		
		for(u8 i=0;i<8;i++)//写入数字
		{	if(data&0x80)DATA595(1);
			else DATA595(0);
			SCLK595(0);
			SCLK595(1);
			data<<=1;}
		
		for(u8 i=0;i<8;i++)//写入位置
		{
			if(place_set&0x80)DATA595(1);
			else DATA595(0);
			SCLK595(0);
			SCLK595(1);
			place_set<<=1;}
		
		for(u8 i=0;i<bit_num;i++)//推进位置
			for(u8 j=0;j<16;j++)
			{	DATA595(0);
				SCLK595(0);
				SCLK595(1);}
	}
	
	RCLK595(0);
	RCLK595(1);
}

u8 num_chect(float show_num)
{
	u8 return_num=0;
	
	u32 int_num=(u32)show_num;
	while(int_num>=10)
	{	int_num/=10;
		return_num+=1;
	}
	return return_num;
}

void show_num(float num,u8 precision)//preccision表示保留几位小数字；
{
	float num1;
	uint64_t show_num;
	u8 point_num;
	u8 flat=0;
	u8 num_bit[64];//记录每一位的值

	if(num<0){num1=-num;flat=1;}//取绝对值
	else num1=num;
	point_num=num_chect(num1);//整数位数
	
	for(u8 i=0;i<precision;i++)num1*=10;//小数精度，去尾法
	show_num=(uint64_t)num1;
	
	for(u8 i=0;i<point_num+precision+1;i++)
	{	
		num_bit[i]=show_num%10;
		show_num/=10;
	}//计算每一位的值
	
	if(flat)
	{
		num_bit[point_num+precision+1]=16;
		for(int8_t i=point_num+precision+1;i>=0;i--)
			if(point_num+precision-i==point_num)
				write_bit595(point_num+precision+1-i,num_bit[i],on_point);
			else
				write_bit595(point_num+precision+1-i,num_bit[i],off_point);
	}
	else
	{
		for(int8_t i=point_num+precision;i>=0;i--)
			if(point_num+precision-i==point_num)
				write_bit595(point_num+precision-i,num_bit[i],on_point);
			else
				write_bit595(point_num+precision-i,num_bit[i],off_point);
	}
}
