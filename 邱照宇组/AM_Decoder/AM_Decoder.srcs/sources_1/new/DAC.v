`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/15 21:50:56
// Design Name: 
// Module Name: DAC
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


module DAC(
    input signed [15:0]orign_meg,
    input CLK,
    output reg signed [13:0]DAC_meg
    );
    
    always @(posedge CLK) begin
        
        DAC_meg<=orign_meg[15:2];
    
    end
    
endmodule
