`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/12 16:39:25
// Design Name: 
// Module Name: IQ_FreMix
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


module IQ_FreMix(
    
    CLK_H,
    AM_phase,
    Transed_phase_I,
    Transed_phase_Q,
    Reset,
    CLK_S,
    test,
    test2,
    fre

    );
    
    input CLK_H;
    input CLK_S;
    input signed [11:0]AM_phase;
    input Reset;
    output signed [27:0]test;
    output signed [15:0]test2;
    output signed [15:0]Transed_phase_I;
    output signed [15:0]Transed_phase_Q;

    input [15:0]fre;
    
    reg [31:0]cos_data;
    reg [31:0]sin_data;
    
    wire [15:0]cos_phase;
    wire [15:0]sin_phase;
    
    Phase_Creater cos_gen_1 (
        .CLK_H(CLK_H),
        .phase(cos_phase),
//        .Flag(cos_flag),
        .Reset(Reset),
        .tdata(cos_data)
    );
    
    Phase_Creater sin_gen_1 (
        .CLK_H(CLK_H),
        .phase(sin_phase),
//        .Flag(sin_flag),
        .Reset(Reset),
        .tdata(sin_data)
    );
    
    wire signed [27:0]Transed_phase_I_med;
    wire signed [27:0]Transed_phase_Q_med;
    
    assign test=Transed_phase_Q_med;
    assign test2=cos_phase;
    
    mult_gen_0 mult_I(
        .CLK(CLK_H),
        .A(AM_phase),
        .B(cos_phase),
        .P(Transed_phase_I_med)
    );

    mult_gen_0 mult_Q(
        .CLK(CLK_H),
        .A(AM_phase),
        .B(-sin_phase),
        .P(Transed_phase_Q_med)
    );
    
    
    FIR_130m_5m fir_I(
     .CLK_H(CLK_H),
     .phase_input(Transed_phase_I_med),
     .phase_output(Transed_phase_I),
     .Reset(Reset)
);
    
    FIR_130m_5m fir_Q(
     .CLK_H(CLK_H),
     .phase_input(Transed_phase_Q_med),
     .phase_output(Transed_phase_Q),
     .Reset(Reset)
);

    always @ (posedge CLK_H or negedge Reset)begin
        if(!Reset)begin

            cos_data<=0;
            sin_data<=0;
            
        end
        
        else begin

            cos_data<={16'b0000_0000_0000_0000,fre};
            sin_data<={16'b0000_1100_1011_0010,fre};
            
            
            
        end
    end
    
endmodule
