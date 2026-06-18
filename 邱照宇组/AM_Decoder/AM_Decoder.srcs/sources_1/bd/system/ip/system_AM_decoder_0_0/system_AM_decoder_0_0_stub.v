// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Sun Jun 14 17:14:26 2026
// Host        : LAPTOP-JO00M47A running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               D:/fpga/AM_Decoder/AM_Decoder.srcs/sources_1/bd/system/ip/system_AM_decoder_0_0/system_AM_decoder_0_0_stub.v
// Design      : system_AM_decoder_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg484-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "AM_decoder,Vivado 2018.3" *)
module system_AM_decoder_0_0(AM_wave, CLK_H, Reset, decode)
/* synthesis syn_black_box black_box_pad_pin="AM_wave[11:0],CLK_H,Reset,decode[15:0]" */;
  input [11:0]AM_wave;
  input CLK_H;
  input Reset;
  output [15:0]decode;
endmodule
