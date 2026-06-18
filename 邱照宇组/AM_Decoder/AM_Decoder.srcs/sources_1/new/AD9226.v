`timescale 1ns / 1ps


module AD9226(

	input Clk_Read,				//系统时钟
	input Otr,					//超出范围
	input [11:0] Adc_In,		//输入数据
	output [11:0]adc_out
);





wire [11:0]out_med;
    
reg [11:0] Adc_Out;

assign adc_out=Adc_Out;


assign out_med=(Adc_In^12'hFFF);

reg [11:0]out_reg;

reg [3:0]s_cnt;



always @(posedge Clk_Read) begin 
	  if(out_med>=12'd2047) out_reg<=out_med-12'd2047;
	  else out_reg<=out_med+12'd2048;
	  
	  if(out_reg<=12'd100||out_reg>=12'd3996) Adc_Out<=out_reg;
end   
endmodule
