`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/18 16:19:58
// Design Name: 
// Module Name: ASK_decode
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 这是一个ASK解调模块，ASK_wave是信号输入，CLK_H是时钟信号，out是解调数字信号
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ASK_decode(
    ASK_wave,
    CLK_H,
    Reset,
    out,
    decode_out
    );
    parameter door=9'd350;
    input signed [11:0]ASK_wave;
    input CLK_H;
    input Reset;
    output reg out;
    output [11:0]decode_out;
    wire [23:0]abs_med;
    mult_gen_3 abs_mult(
        .CLK(CLK_H),
        .A(ASK_wave),
        .B(ASK_wave),
        .P(abs_med)
    );
    
    wire sqrt_out_valid;
    reg sqrt_in_valid;
    
    wire [11:0]sqrt_out;
     cordic_1 sqrt(    
        .aclk(CLK_H),
        .s_axis_cartesian_tdata(abs_med),
        .s_axis_cartesian_tvalid(sqrt_in_valid),
        .m_axis_dout_tdata(sqrt_out),
        .m_axis_dout_tvalid(sqrt_out_valid)
    );
    
    reg signed [11:0]abs;
    wire signed [11:0]decode_med;
    wire aver_valid;
    assign decode_out=decode_med;
    FIR_ASK fir(
     .CLK_H(CLK_H),//6.5m
     .phase_input(abs),
     .phase_output(decode_med),
     .Reset(Reset)
    );

    
    always@(posedge CLK_H or negedge Reset)begin
        if(!Reset) begin
            sqrt_in_valid<=1'b0;
            abs<=$signed(16'b0);
        end
        
        else begin
            sqrt_in_valid<=1'b1;
            if(sqrt_out_valid) abs<=sqrt_out;
        end
    end
    
    always@(posedge CLK_H or negedge Reset)begin
        if(!Reset)begin
            out<=1'b1;
        end
        else begin
            if(decode_med>=door&&decode_med<=12'd2000) out<=1'b1;
            else out<=1'b0;
        end
    end
endmodule