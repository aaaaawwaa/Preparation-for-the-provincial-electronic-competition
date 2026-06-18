`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/12 20:51:05
// Design Name: 
// Module Name: AM_decoder
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// AM解调模块，AM_wave是信号输入，CLK_H是时钟260Mhz,fre是载波频率，decode|_out是解调信号输出
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module AM_decoder(
    AM_wave,
    CLK_H,
    Reset,
    decode_out,
    fre
    );
    
    input signed [11:0]AM_wave;
    input CLK_H;
    input Reset;
    input [15:0]fre;
    output signed [13:0]decode_out;
    
    wire signed [15:0]decode;
    wire [15:0]fre;
    
    
    
    wire [15:0]Trans_I;
    wire [15:0]Trans_Q;
    
    IQ_FreMix task_1(
        .CLK_H(CLK_H),
        .AM_phase(AM_wave),
        .Transed_phase_I(Trans_I),
        .Transed_phase_Q(Trans_Q),
        .Reset(Reset),
        .fre(fre)
    );
    wire [15:0]decode_med;
    detect_AM task_2(
        .Input_I(Trans_I),
        .Input_Q(Trans_Q),
        .CLK_H(CLK_H),
        .Reset(Reset),
        .decode_meg(decode)
    );
    
    
    
//    MovingAvg_Subtractor task_3(
//        .In(decode_med),       // 
//        .valid(1'b1),    // 
//        .CLK_H(CLK_H),    // 
//        .Reset(Reset),    // 
//        .Out(decode)// 
////        valid_out // 
    
//    );
    
    FIR_Sam1m_Fstop35k task_4(
        .CLK_H(CLK_H),
        .phase_input(decode<<6),
        .phase_output(decode_out),
        .Reset(Reset)     
    );
    
endmodule
