`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/12 16:45:29
// Design Name: 
// Module Name: AM_test_tb
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


module AM_test_tb(

    );

parameter A_degree=16'd512;


reg CLK_H;
reg [31:0]tdata_b;
reg Reset;
wire signed [15:0]phase_b;

Phase_Creater u_Phase_Creater_b(
    .CLK_H(CLK_H),
    .phase(phase_b),
    .tdata(tdata_b),
    .Reset(Reset)
);


reg [31:0]tdata_l;
wire signed [15:0]phase_l;

Phase_Creater u_Phase_Creater_l(
    .CLK_H(CLK_H),
    .phase(phase_l),
    .tdata(tdata_l),
    .Reset(Reset)
);

wire signed [11:0]med_phase;

assign med_phase=(phase_b>>>7)+$signed(A_degree);

wire [27:0]mult_out;

mult_gen_0 u_mult_gen(
    .CLK(CLK_H),
    .B(phase_l),
    .A(med_phase),
    .P(mult_out)
);


wire [11:0]wave_send;

assign wave_send=mult_out[27:16];

wire [15:0]out;

AM_decoder t1(
    .AM_wave(wave_send),
    .CLK_H(CLK_H),
    .Reset(Reset),
    .decode(out)
);

wire [15:0]I;
wire [15:0]Q;

wire [27:0]test;
wire [15:0]test2;

//IQ_FreMix t2(
    
//    .CLK_H(CLK_H),
//    .AM_phase(wave_send),
//    .Transed_phase_I(I),
//    .Transed_phase_Q(Q),
//    .Reset(Reset),
//    .fre(16'b00000_1011_1011_100),
//    .test(test),
//    .test2(test2)
//    );


initial begin
    CLK_H=0;
    Reset=0;
    #100;
    Reset=1;
    #100;

end

always #2.5 CLK_H=~CLK_H;


initial tdata_b=32'b0000_0000_0000_0000_0000_0000_0000_1000;
initial tdata_l=32'b0000_0000_0000_0000_00000_1011_1011_100;



endmodule
