#ifndef __74HC595_H
#define __74HC595_H
typedef enum{off_point=0,on_point=1}point;

void Output_GPIOInit595(void);
void show_num(float num,u8 precision);//preccision表示保留几位小数字；
void write_bit595(u8 place,u8 num,point mypoint);

#endif
