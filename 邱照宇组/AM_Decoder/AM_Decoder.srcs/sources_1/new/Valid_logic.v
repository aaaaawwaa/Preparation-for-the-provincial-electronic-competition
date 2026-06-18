`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/06/15 21:05:31
// Design Name: 
// Module Name: Valid_logic
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


module Valid_logic(
    input valid,
    input signed [15:0]In,
    input Reset,
    input CLK,
    
    output reg signed [15:0]Out
     
    );
    
    always@(posedge CLK or negedge Reset)begin
    
        if(!Reset) Out<=16'd0;
        
        else if(valid) Out<=In;
    end
    
endmodule
