-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
-- Date        : Sun Jun 14 17:14:26 2026
-- Host        : LAPTOP-JO00M47A running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               D:/fpga/AM_Decoder/AM_Decoder.srcs/sources_1/bd/system/ip/system_AM_decoder_0_0/system_AM_decoder_0_0_stub.vhdl
-- Design      : system_AM_decoder_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg484-2
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity system_AM_decoder_0_0 is
  Port ( 
    AM_wave : in STD_LOGIC_VECTOR ( 11 downto 0 );
    CLK_H : in STD_LOGIC;
    Reset : in STD_LOGIC;
    decode : out STD_LOGIC_VECTOR ( 15 downto 0 )
  );

end system_AM_decoder_0_0;

architecture stub of system_AM_decoder_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "AM_wave[11:0],CLK_H,Reset,decode[15:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "AM_decoder,Vivado 2018.3";
begin
end;
