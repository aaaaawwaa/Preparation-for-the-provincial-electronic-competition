`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/12 15:51:34
// Design Name: 
// Module Name: phase_creater_bd
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


module phase_creater_bd(

    );

reg CLK_H;
reg [31:0]tdata;
reg Reset;
wire [15:0]phase;


Phase_Creater u_Phase_Creater(
    .CLK_H(CLK_H),
    .phase(phase),
    .tdata(tdata),
    .Reset(Reset)
);


initial begin
    CLK_H=0;
    Reset=0;
    #100;
    Reset=1;
    #100;
    

end

always #5 CLK_H=~CLK_H;

initial tdata=32'b0000_0000_0000_0000_0000_0000_0000_1000;

endmodule
