`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/18 16:58:39
// Design Name: 
// Module Name: ASK_tb
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


module ASK_tb();

    reg CLK;
    reg Reset;
    
    reg dig;
    
    wire CLK_H;
    clk_wiz_0 clock(
        .clk_in1(CLK),
        .clk_out4(CLK_H)
    );
    
    
    wire signed [15:0]base;
    wire signed [11:0]wave;

    
    DDS_LOW cos(
        .CLK_H(CLK_H),
        .phase(base),
        .tdata({16'd0,16'd23}),
        .Reset(Reset)
    );
    
    mult_gen_2 mult(
        .CLK(CLK),
        .A(base>>>4),
        .B({1'b0,dig}),
        .P(wave)
    );
    wire out;
    wire [11:0]decode_t;
    ASK_decode t(
    .ASK_wave(wave),
    .CLK_H(CLK_H),
    .Reset(Reset),
    .out(out),
    .decode_out(decode_t)
    );
    
always begin
dig=0;
#10000000;
dig=1;
#10000000;
dig=0;
#10000000;
end

initial begin
    CLK=0;
    Reset=0;
    #100;
    Reset=1;
    #100;

end

always #10 CLK=~CLK;

endmodule
