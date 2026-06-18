// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Thu Jun 18 17:09:04 2026
// Host        : LAPTOP-JO00M47A running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               d:/fpga/AM_Decoder/AM_Decoder.srcs/sources_1/ip/mult_gen_2/mult_gen_2_sim_netlist.v
// Design      : mult_gen_2
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg484-2
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "mult_gen_2,mult_gen_v12_0_14,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "mult_gen_v12_0_14,Vivado 2018.3" *) 
(* NotValidForBitStream *)
module mult_gen_2
   (CLK,
    A,
    B,
    P);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk_intf CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk_intf, ASSOCIATED_BUSIF p_intf:b_intf:a_intf, ASSOCIATED_RESET sclr, ASSOCIATED_CLKEN ce, FREQ_HZ 10000000, PHASE 0.000, INSERT_VIP 0" *) input CLK;
  (* x_interface_info = "xilinx.com:signal:data:1.0 a_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME a_intf, LAYERED_METADATA undef" *) input [11:0]A;
  (* x_interface_info = "xilinx.com:signal:data:1.0 b_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME b_intf, LAYERED_METADATA undef" *) input [1:0]B;
  (* x_interface_info = "xilinx.com:signal:data:1.0 p_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME p_intf, LAYERED_METADATA undef" *) output [13:0]P;

  wire [11:0]A;
  wire [1:0]B;
  wire CLK;
  wire [13:0]P;
  wire [47:0]NLW_U0_PCASC_UNCONNECTED;
  wire [1:0]NLW_U0_ZERO_DETECT_UNCONNECTED;

  (* C_A_TYPE = "0" *) 
  (* C_A_WIDTH = "12" *) 
  (* C_B_TYPE = "0" *) 
  (* C_B_VALUE = "10000001" *) 
  (* C_B_WIDTH = "2" *) 
  (* C_CCM_IMP = "0" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_ZERO_DETECT = "0" *) 
  (* C_LATENCY = "1" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_MULT_TYPE = "0" *) 
  (* C_OUT_HIGH = "13" *) 
  (* C_OUT_LOW = "0" *) 
  (* C_ROUND_OUTPUT = "0" *) 
  (* C_ROUND_PT = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* c_optimize_goal = "1" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  mult_gen_2_mult_gen_v12_0_14 U0
       (.A(A),
        .B(B),
        .CE(1'b1),
        .CLK(CLK),
        .P(P),
        .PCASC(NLW_U0_PCASC_UNCONNECTED[47:0]),
        .SCLR(1'b0),
        .ZERO_DETECT(NLW_U0_ZERO_DETECT_UNCONNECTED[1:0]));
endmodule

(* C_A_TYPE = "0" *) (* C_A_WIDTH = "12" *) (* C_B_TYPE = "0" *) 
(* C_B_VALUE = "10000001" *) (* C_B_WIDTH = "2" *) (* C_CCM_IMP = "0" *) 
(* C_CE_OVERRIDES_SCLR = "0" *) (* C_HAS_CE = "0" *) (* C_HAS_SCLR = "0" *) 
(* C_HAS_ZERO_DETECT = "0" *) (* C_LATENCY = "1" *) (* C_MODEL_TYPE = "0" *) 
(* C_MULT_TYPE = "0" *) (* C_OPTIMIZE_GOAL = "1" *) (* C_OUT_HIGH = "13" *) 
(* C_OUT_LOW = "0" *) (* C_ROUND_OUTPUT = "0" *) (* C_ROUND_PT = "0" *) 
(* C_VERBOSITY = "0" *) (* C_XDEVICEFAMILY = "zynq" *) (* ORIG_REF_NAME = "mult_gen_v12_0_14" *) 
(* downgradeipidentifiedwarnings = "yes" *) 
module mult_gen_2_mult_gen_v12_0_14
   (CLK,
    A,
    B,
    CE,
    SCLR,
    ZERO_DETECT,
    P,
    PCASC);
  input CLK;
  input [11:0]A;
  input [1:0]B;
  input CE;
  input SCLR;
  output [1:0]ZERO_DETECT;
  output [13:0]P;
  output [47:0]PCASC;

  wire \<const0> ;
  wire [11:0]A;
  wire [1:0]B;
  wire CLK;
  wire [13:0]P;
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
  (* C_A_WIDTH = "12" *) 
  (* C_B_TYPE = "0" *) 
  (* C_B_VALUE = "10000001" *) 
  (* C_B_WIDTH = "2" *) 
  (* C_CCM_IMP = "0" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_ZERO_DETECT = "0" *) 
  (* C_LATENCY = "1" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_MULT_TYPE = "0" *) 
  (* C_OUT_HIGH = "13" *) 
  (* C_OUT_LOW = "0" *) 
  (* C_ROUND_OUTPUT = "0" *) 
  (* C_ROUND_PT = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* c_optimize_goal = "1" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  mult_gen_2_mult_gen_v12_0_14_viv i_mult
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
HwUvna0sKLqO2nED940pL2lldvO5l6V+v+BVJxV7KUPDliVodCYRMZkl7Z+MLBK5Wh6o8ePc3MXt
QVFXZDNMrA+z6G2TJseOMbeCcp0gswFWTcEaRAH5CKNJCQJulbwz+m0fiABKEIhtjNzDxVRTnH09
5xlh6GYUsukUOY3nLstR6ax8ZmJL8magDxT/RMb8kqO1CUpmoXGQ8hK9ZXAAEJ0UCs0SnNSXF5cL
Uep+sKk8skicTDzjB4DGlXAbxewUj6SjKlzf1NZVPd+PzuJ4hzKJ3l8XkDY9N1gL+/fQn1mtZNeR
+kILWB9mlTz2rfZZSRx7RqDYRCw/pubD8S67bA==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
aaeFg57ddiuM2ISwJwTFl88wgLnBUID6LVEU+Q7WTneSVpuDeGK7QNmNFeHcBV91PixbvgH+RYsY
pOQbunR0iNIiIXax6xs3pp7kPSN3keXSbjGdqNIDDKFl1bbWYPmUTWVLcwbe01eiAD05TBfO0HJ+
ljwqjiWZl0M9MU/K5OKwyt/XpVZbWpFArJadE1kDgTvgNlT6I+3irdvFoztQFqETvPRnd/DH+1GO
elMd7B8NhK2zDdP9RGBVVebKYXTmv/k0jLpOyCEU575F5oANuJgntB0qJWrn9OE6yYEyq5bgwOeb
+eFdkEQKRfD/0YSD+4nMZGL2bCRnUwRLLSP9fQ==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 20816)
`pragma protect data_block
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
Mx57JJT1xOKjvjM=
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
