// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Fri Jun 12 20:40:39 2026
// Host        : LAPTOP-JO00M47A running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ mult_gen_1_sim_netlist.v
// Design      : mult_gen_1
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg484-2
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "mult_gen_1,mult_gen_v12_0_14,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "mult_gen_v12_0_14,Vivado 2018.3" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
   (CLK,
    A,
    B,
    P);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk_intf CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk_intf, ASSOCIATED_BUSIF p_intf:b_intf:a_intf, ASSOCIATED_RESET sclr, ASSOCIATED_CLKEN ce, FREQ_HZ 10000000, PHASE 0.000, INSERT_VIP 0" *) input CLK;
  (* x_interface_info = "xilinx.com:signal:data:1.0 a_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME a_intf, LAYERED_METADATA undef" *) input [15:0]A;
  (* x_interface_info = "xilinx.com:signal:data:1.0 b_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME b_intf, LAYERED_METADATA undef" *) input [15:0]B;
  (* x_interface_info = "xilinx.com:signal:data:1.0 p_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME p_intf, LAYERED_METADATA undef" *) output [31:0]P;

  wire [15:0]A;
  wire [15:0]B;
  wire CLK;
  wire [31:0]P;
  wire [47:0]NLW_U0_PCASC_UNCONNECTED;
  wire [1:0]NLW_U0_ZERO_DETECT_UNCONNECTED;

  (* C_A_TYPE = "0" *) 
  (* C_A_WIDTH = "16" *) 
  (* C_B_TYPE = "0" *) 
  (* C_B_VALUE = "10000001" *) 
  (* C_B_WIDTH = "16" *) 
  (* C_CCM_IMP = "0" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_ZERO_DETECT = "0" *) 
  (* C_LATENCY = "1" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_MULT_TYPE = "1" *) 
  (* C_OPTIMIZE_GOAL = "1" *) 
  (* C_OUT_HIGH = "31" *) 
  (* C_OUT_LOW = "0" *) 
  (* C_ROUND_OUTPUT = "0" *) 
  (* C_ROUND_PT = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mult_gen_v12_0_14 U0
       (.A(A),
        .B(B),
        .CE(1'b1),
        .CLK(CLK),
        .P(P),
        .PCASC(NLW_U0_PCASC_UNCONNECTED[47:0]),
        .SCLR(1'b0),
        .ZERO_DETECT(NLW_U0_ZERO_DETECT_UNCONNECTED[1:0]));
endmodule

(* C_A_TYPE = "0" *) (* C_A_WIDTH = "16" *) (* C_B_TYPE = "0" *) 
(* C_B_VALUE = "10000001" *) (* C_B_WIDTH = "16" *) (* C_CCM_IMP = "0" *) 
(* C_CE_OVERRIDES_SCLR = "0" *) (* C_HAS_CE = "0" *) (* C_HAS_SCLR = "0" *) 
(* C_HAS_ZERO_DETECT = "0" *) (* C_LATENCY = "1" *) (* C_MODEL_TYPE = "0" *) 
(* C_MULT_TYPE = "1" *) (* C_OPTIMIZE_GOAL = "1" *) (* C_OUT_HIGH = "31" *) 
(* C_OUT_LOW = "0" *) (* C_ROUND_OUTPUT = "0" *) (* C_ROUND_PT = "0" *) 
(* C_VERBOSITY = "0" *) (* C_XDEVICEFAMILY = "zynq" *) (* downgradeipidentifiedwarnings = "yes" *) 
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mult_gen_v12_0_14
   (CLK,
    A,
    B,
    CE,
    SCLR,
    ZERO_DETECT,
    P,
    PCASC);
  input CLK;
  input [15:0]A;
  input [15:0]B;
  input CE;
  input SCLR;
  output [1:0]ZERO_DETECT;
  output [31:0]P;
  output [47:0]PCASC;

  wire \<const0> ;
  wire [15:0]A;
  wire [15:0]B;
  wire CLK;
  wire [31:0]P;
  wire [47:0]NLW_i_mult_PCASC_UNCONNECTED;
  wire [1:0]NLW_i_mult_ZERO_DETECT_UNCONNECTED;

  assign PCASC[47] = \<const0> ;
  assign PCASC[46] = \<const0> ;
  assign PCASC[45] = \<const0> ;
  assign PCASC[44] = \<const0> ;
  assign PCASC[43] = \<const0> ;
  assign PCASC[42] = \<const0> ;
  assign PCASC[41] = \<const0> ;
  assign PCASC[40] = \<const0> ;
  assign PCASC[39] = \<const0> ;
  assign PCASC[38] = \<const0> ;
  assign PCASC[37] = \<const0> ;
  assign PCASC[36] = \<const0> ;
  assign PCASC[35] = \<const0> ;
  assign PCASC[34] = \<const0> ;
  assign PCASC[33] = \<const0> ;
  assign PCASC[32] = \<const0> ;
  assign PCASC[31] = \<const0> ;
  assign PCASC[30] = \<const0> ;
  assign PCASC[29] = \<const0> ;
  assign PCASC[28] = \<const0> ;
  assign PCASC[27] = \<const0> ;
  assign PCASC[26] = \<const0> ;
  assign PCASC[25] = \<const0> ;
  assign PCASC[24] = \<const0> ;
  assign PCASC[23] = \<const0> ;
  assign PCASC[22] = \<const0> ;
  assign PCASC[21] = \<const0> ;
  assign PCASC[20] = \<const0> ;
  assign PCASC[19] = \<const0> ;
  assign PCASC[18] = \<const0> ;
  assign PCASC[17] = \<const0> ;
  assign PCASC[16] = \<const0> ;
  assign PCASC[15] = \<const0> ;
  assign PCASC[14] = \<const0> ;
  assign PCASC[13] = \<const0> ;
  assign PCASC[12] = \<const0> ;
  assign PCASC[11] = \<const0> ;
  assign PCASC[10] = \<const0> ;
  assign PCASC[9] = \<const0> ;
  assign PCASC[8] = \<const0> ;
  assign PCASC[7] = \<const0> ;
  assign PCASC[6] = \<const0> ;
  assign PCASC[5] = \<const0> ;
  assign PCASC[4] = \<const0> ;
  assign PCASC[3] = \<const0> ;
  assign PCASC[2] = \<const0> ;
  assign PCASC[1] = \<const0> ;
  assign PCASC[0] = \<const0> ;
  assign ZERO_DETECT[1] = \<const0> ;
  assign ZERO_DETECT[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  (* C_A_TYPE = "0" *) 
  (* C_A_WIDTH = "16" *) 
  (* C_B_TYPE = "0" *) 
  (* C_B_VALUE = "10000001" *) 
  (* C_B_WIDTH = "16" *) 
  (* C_CCM_IMP = "0" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_ZERO_DETECT = "0" *) 
  (* C_LATENCY = "1" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_MULT_TYPE = "1" *) 
  (* C_OPTIMIZE_GOAL = "1" *) 
  (* C_OUT_HIGH = "31" *) 
  (* C_OUT_LOW = "0" *) 
  (* C_ROUND_OUTPUT = "0" *) 
  (* C_ROUND_PT = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mult_gen_v12_0_14_viv i_mult
       (.A(A),
        .B(B),
        .CE(1'b0),
        .CLK(CLK),
        .P(P),
        .PCASC(NLW_i_mult_PCASC_UNCONNECTED[47:0]),
        .SCLR(1'b0),
        .ZERO_DETECT(NLW_i_mult_ZERO_DETECT_UNCONNECTED[1:0]));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2015"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
g7azmhtm6FcP7uNFjuXJjN8Z6yccOPk3SSjzvKB27peFKmnPmQmov5+YTGwYqqN9LpdyiUExk8K6
vPnJqontvQ==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
MFrqn2K0Cr7TmQ5al162oDGiY83d+AkTWOgFyXPYrTNznygR/tx44RAp24ytphNK9p6shs2EFMg/
Qqz0l8DCWiVEoJ/T8vMpnAn7Y+poGVGS1qAR3qE2njrl81VcGBZJeFaWIudhfr/DLTuuf2T/dWDU
YpelM3KbfYNPPiPy8PU=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
FZca5XZouG+/BYoQ8qrJTmnJanku4IprIWRkO6VciHehE5WehR0wsZJhfKlqLEeY1oTPA4bXaxmY
NjYkrop4EOwW8t47/hj2kFLI1OKUAE/TAhCGg/aNSOViUbB3dUomG/y+TBuDt9L6g0Arj1vb/5Pt
IChc5ZdEfRr1lJMTpFfP+5qmEH6lePPdzgPZATPB4Zrj0P6EyiEsU1FKBuAKd9iYNGiLCxVomaz0
3/RwK2Nl+/l4mc7PJt5Hso+4s1qHb4s2wD+OgbIwdH26ZkEnKVFpaLiuWQKu9uhDLGnsBMPf7XDE
p29f+mrvP9Zi/3nonA2aBKrTwR7XuH+ZYoakxA==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
jP68OjlYJglq3zpmKrXOhq7Sex8XNW8fQKp4hUNmuw06OOoKhQASNTnjtyVjAIk/VXb64ViBu1ds
cNMJybDSWBhnChfJq4h9PNybShGJXxSm3NDOo5wUHKf10Eti3fSotB9rVks+tNdTEZo4O97kgfdD
G1FNOqlsYcQiShEGLLiEQ2yYtgJBxJ+jc8mFjIEfPhAYy1ElrvtFEpnhkNS2LfE7xdWOQdO/XoKK
ibeY08pgncTI3pvO6TMbXushf0AX2S7hgfk8ysZrT+0gktqFrJnyR6oljS6VVPLtRNW2vo/cC8XQ
Bzvwwt4cpSo5KLS4XxB6qClZipItck2AUEdIbQ==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2017_05", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
o7jAZIoXlFbFtDYmtXhfRBlb07dhBb6Wp03mlT4T0FXtvccSHWhWZgc+VUNwt6TohLihOwvSipPP
XVXpGL4pUVYNdQBCVpFzhMkt6jhyUgsF5t10yI5Of6YEfQrDHigceoBukM3+/zJHPprrPQE6FUvC
wXSGhBCXnHJs1R+n4l0714w8/WftPQhlD9QGQp1qT2VARQXUKBRxcRjxe9TcLfs0P4xnN7uHu0R6
JTmV+MHmhGpetSZGx+B2Wa1MQofUPURqwE70IwBoUhdXH8+39DT5I6x2+wMY6RcVATnhNd2BCgPd
RzAhwfrcqRiU9aB+eNNdFR8ve9M2nGMmV2JxZg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
Cl1Dz+fZIDYEIQuUd0pSg+5jknmtX/JERd+yOZ2SRaVra/4pU/eCTjEXMzhz4VFGYB6dgUxMsGBk
nL2WNdn/uaSPpi6mNF0UHQvZik4pUkYPrnRbFveVqW8i1t95SG0RW96uD19206lWrp5U1lqc4fH7
sfKHi8ZpU3MAg0DOO0E=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Qqp76m2aV9ue8Qai7QUavb+lhRYdu/txrnwYLzwTe0vS0S2OD1vxr8VeIT3bF/ZuXlTGm4S/UCSF
bgOPp7VqEOeGNfsSPK+VpQ+foQMENCQYccwKquBDSg/sLjpPK9uuoGLBLxjw2OwsRzplVFXiPcRN
LYK1/FmCP7RJBNgmhh/ti99a+WSl6i2YIIRGocNplQlG8FXq8ZTTHd/x2Gtdf/zGvJOy/fNsos6S
Oq9yJ0rMmbGeWbri5c04gZM08pUmXBsivgOHm2IVEZZFM4SBqrsi0xa52hs2kelc3iKJcWiTvU3X
0fJP9qNFuIjXBPPZvEYwhVtIh6DwiIC2viSscQ==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
qSUOet+c4Yyyi2yOCDTM4gyByZOaAUF7oOuruaGgwhvt3HCBywMZG75kfjfzdIo6JuECaDO4Ls6U
MMh9XfmwiA7/1K5kd1+UFTGChw5vdSvm73Up8MjAluQ2Tpbsj0/cBNIqcoghhizDdtakrcjHS7ue
ZTKh1oHeKvErOxc7Reetv8/8Lju8NWgVxceIivrESXj4hUoyEH8YiHyNmrlKQ8hWwgp+r7Xf1Osl
UYH/1yLOmc40kfTfSTi/gIO+1fGOa0kD9y0XfFfmMliZb1mjY6DtzVXSR/ZiFZiqv22256wyYBh2
g6qf6aL5mc2GMXtc7jkU7XrZRVShX6d2HZJlaQ==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Z3G/D7AO4XHFsY8ja90axxgRgKmP81jSI4jidCoUhC5KSNDkPtvCcOiS2/qWyJGdE0NPZ4Z7f2oZ
ZOefZ1BaK+Lq9i6LrloVBgkacfmLoUvvIj1MYD55Y3RJN8znXpfMYU5LOSqoIkvw3MN1XkIYlzTe
B84QoZHKDpYIxQmuuHe0cVb4Abufg0Bfut95ZTkNveqTBYTwI/LGpURWdTDk/LQNmC1aGrWo/0uX
qFUPGEw/FUrYK2cTvA7vf8lxvZrw6lDQnqFhv9erq2pTEx2BRwF7L+R4wzKeAoFjU3XKq0Pa+u6b
GNuA0yKzJrhaTJESyfKk9XYoZhNkzOUfOc5kZQ==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 7248)
`pragma protect data_block
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
GLWZAnvkkqX/
`pragma protect end_protected
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
