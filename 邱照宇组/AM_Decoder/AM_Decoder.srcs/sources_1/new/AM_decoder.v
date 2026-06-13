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
// 
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
    decode
    );
    
    input signed [11:0]AM_wave;
    input CLK_H;
    input Reset;
    output signed [15:0]decode;
    
    wire [15:0]fre;
    
    wire [15:0]Trans_I;
    wire [15:0]Trans_Q;
    
    IQ_FreMix task_1(
        .CLK_H(CLK_H),
        .AM_phase(AM_wave),
        .Transed_phase_I(Trans_I),
        .Transed_phase_Q(Trans_Q),
        .Reset(Reset),
        .fre(16'b0000_0101_1101_1100)
    );
    
    detect_AM task_2(
        .Input_I(Trans_I),
        .Input_Q(Trans_Q),
        .CLK_H(CLK_H),
        .Reset(Reset),
        .decode_meg(decode)
    );
    
endmodule
