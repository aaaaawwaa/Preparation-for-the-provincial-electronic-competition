`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/16 16:56:14
// Design Name: 
// Module Name: main
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 经过板上测试，AM模块和fft模块均能正常使用
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module main(
    input [11:0]ADC_meg,
    input ADC_Otr,
    output ADC_CLK,
    
    output [13:0]DAC_meg,
    output DAC_CLK,
    
    input Reset
    );
    
    wire System_CLK;
    system_wrapper system(
        .System_CLK(System_CLK)
    );
    
    wire CLK_260M;
    wire CLK_65M;
    wire CLK_65M_Read;
    wire CLK_6p5M;
    clk_wiz_0 global_clock(
        .clk_in1(System_CLK),
        .clk_out1(CLK_260M),
        .clk_out2(CLK_65M),
        .clk_out3(CLK_65M_Read),
        .clk_out4(CLK_6p5M)
    );
    
    
    assign ADC_CLK=CLK_65M;
    
    wire signed [11:0]meg;
    AD9226 ADC(
       .Clk_Read(CLK_65M_Read),				//系统时钟
	   .Otr(ADC_Otr),					//超出范围
	   .Adc_In(ADC_meg),		//输入数据
	   .adc_out(meg)
    );
    
    wire [15:0]Decode_out;
//    AM_decoder decode(
//        .AM_wave(meg),
//        .CLK_H(CLK_260M),
//        .Reset(Reset),
//        .decode_out(Decode_out),
//        .fre(16'd535)
//    );
    
    ASK_decode decode_ASK(
        .ASK_wave(meg),
        .CLK_H(CLK_6p5M),
        .Reset(Reset),
        .decode_out(Decode_out),
        .fre(16'd23)
    );
    
    wire [16:0]range;
    wire [12:0]sample;
//    fre_detect fft(
//        .wave(Decode_out[13:2]<<2),
//        .CLK_H(CLK_65M),
//        .Reset(Reset),
//        .range(range),
//        .sample(sample)
//    );
    
    ila_0 ila(
        .clk(CLK_65M),    
        .probe0(meg),
        .probe1(Decode_out),
        .probe2(decode_ASK.decode)
//        .probe3(fft.Max_range),
//        .probe4(fft.Max_sample),
//        .probe5(fft.fft_task.s_cnt),
//        .probe6(fft.fft_task.data_finish_flag)
    );
        
endmodule
