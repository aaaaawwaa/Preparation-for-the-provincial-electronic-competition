`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/18 16:18:52
// Design Name: 
// Module Name: detect_ASK
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


module detect_ASK(
    Input_I,
    Input_Q,
    CLK_H,
    Reset,
    decode_meg
    );
    
    input signed [15:0]Input_I;
    input signed [15:0]Input_Q;
    input CLK_H;
    input Reset;
    
    output reg signed [15:0]decode_meg;
    
    wire [31:0]I_med;
    wire [31:0]Q_med;
    
    mult_gen_1 mult_I(
        .CLK(CLK_H),
        .A(Input_I),
        .B(Input_I),
        .P(I_med)
    );
     
    mult_gen_1 mult_Q(
        .CLK(CLK_H),
        .A(Input_Q),
        .B(Input_Q),
        .P(Q_med)
    );
    
    wire sqrt_out_valid;
    reg sqrt_in_valid;
    
    wire signed [16:0]sqrt_out;
    
    cordic_0 sqrt(
    
        .aclk(CLK_H),
        
        .s_axis_cartesian_tdata({2'b0,Q_med+I_med}),
        .s_axis_cartesian_tvalid(sqrt_in_valid),

        
        .m_axis_dout_tdata(sqrt_out),
        .m_axis_dout_tvalid(sqrt_out_valid)

    );
    
    always@(posedge CLK_H or negedge Reset)begin
        if(!Reset) begin
            sqrt_in_valid<=1'b0;
            decode_meg<=$signed(16'b0);
        end
        
        else begin
            sqrt_in_valid<=1'b1;
            if(sqrt_out_valid) decode_meg<=sqrt_out[16:1];
        end
    end
       
endmodule
