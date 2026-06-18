// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Thu Jun 18 17:09:04 2026
// Host        : LAPTOP-JO00M47A running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ mult_gen_2_sim_netlist.v
// Design      : mult_gen_2
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg484-2
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "mult_gen_2,mult_gen_v12_0_14,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "mult_gen_v12_0_14,Vivado 2018.3" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
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

(* C_A_TYPE = "0" *) (* C_A_WIDTH = "12" *) (* C_B_TYPE = "0" *) 
(* C_B_VALUE = "10000001" *) (* C_B_WIDTH = "2" *) (* C_CCM_IMP = "0" *) 
(* C_CE_OVERRIDES_SCLR = "0" *) (* C_HAS_CE = "0" *) (* C_HAS_SCLR = "0" *) 
(* C_HAS_ZERO_DETECT = "0" *) (* C_LATENCY = "1" *) (* C_MODEL_TYPE = "0" *) 
(* C_MULT_TYPE = "0" *) (* C_OPTIMIZE_GOAL = "1" *) (* C_OUT_HIGH = "13" *) 
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
gNelkl+EGLtChjNJ9KPza6CSkyjxwZnENu1PCjKjHOZPcGZhKltuHqwywxyjjYNQTb9AVtnwHBGn
Sh0iF9w6ErraXZzzoTnmHImVaD1Bj85oktEvFhRrHRS9SmgevvP9FMmoC3o7BAu+/9R5Rwqjsm7D
EuXhNDNAC3UykEc2arsyQo01LJbFCq0SDW2WC+6N6q0c/iCiPsOpUwWeoNGM5Nth07zSgJYvtPog
SuW2K6bUgGUsV5NF2a1eFvLoyXSlFSHEA2Ae2P70Qo87cx8zdBF/us6QP/F861HBw4+ui7bA985+
GEIA9Xweu2iQlV1RkG8sc4M123BX2wcDotzI2g==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
6mwiz0iK2GLGoeKzYx+G5tRKba9mOEVvcjY83ZInLUVJiqkXqMWJpiij4q3l3MUdwinuqXoRpgyO
98skQxNkDahjfXbMXdEO5C0auS8xxo/afoWtsAVTj5FosjoLhHminmB6QeD5cJWxp2JnBXYYdKl/
qDHq8PFt575aupDrmZdYtmhOTHZ9M3CMVUqc1oGQ9UW8eO7k6wk4lqlq4FBcovRWvJtYnjAQUXwb
rMyR2+xKz6rqP7iyS5ajwh776BnuQTv977MDQ2SAP/CByNgk9ZPJPqG5GoiAXC8liIxt32BvNVBv
dfu5ti94JUYh16OPrdZlH3Ll8V6kyijumr1lPA==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 20832)
`pragma protect data_block
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
u0YcNkAi5RUskQojhI5aLtD5OFRNDJsY11GI
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
