// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Thu Jun 18 17:08:31 2026
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
  (* x_interface_info = "xilinx.com:signal:data:1.0 a_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME a_intf, LAYERED_METADATA undef" *) input [15:0]A;
  (* x_interface_info = "xilinx.com:signal:data:1.0 b_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME b_intf, LAYERED_METADATA undef" *) input [1:0]B;
  (* x_interface_info = "xilinx.com:signal:data:1.0 p_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME p_intf, LAYERED_METADATA undef" *) output [17:0]P;

  wire [15:0]A;
  wire [1:0]B;
  wire CLK;
  wire [17:0]P;
  wire [47:0]NLW_U0_PCASC_UNCONNECTED;
  wire [1:0]NLW_U0_ZERO_DETECT_UNCONNECTED;

  (* C_A_TYPE = "0" *) 
  (* C_A_WIDTH = "16" *) 
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
  (* C_OUT_HIGH = "17" *) 
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

(* C_A_TYPE = "0" *) (* C_A_WIDTH = "16" *) (* C_B_TYPE = "0" *) 
(* C_B_VALUE = "10000001" *) (* C_B_WIDTH = "2" *) (* C_CCM_IMP = "0" *) 
(* C_CE_OVERRIDES_SCLR = "0" *) (* C_HAS_CE = "0" *) (* C_HAS_SCLR = "0" *) 
(* C_HAS_ZERO_DETECT = "0" *) (* C_LATENCY = "1" *) (* C_MODEL_TYPE = "0" *) 
(* C_MULT_TYPE = "0" *) (* C_OPTIMIZE_GOAL = "1" *) (* C_OUT_HIGH = "17" *) 
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
  input [1:0]B;
  input CE;
  input SCLR;
  output [1:0]ZERO_DETECT;
  output [17:0]P;
  output [47:0]PCASC;

  wire \<const0> ;
  wire [15:0]A;
  wire [1:0]B;
  wire CLK;
  wire [17:0]P;
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
  (* C_B_WIDTH = "2" *) 
  (* C_CCM_IMP = "0" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_ZERO_DETECT = "0" *) 
  (* C_LATENCY = "1" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_MULT_TYPE = "0" *) 
  (* C_OUT_HIGH = "17" *) 
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
m6d9egsYM0LQA0cvaYUmufBLpxTP/c/vN5u4fvGx6z75EgpXv0x3K5QY2ZUxhZrIHMu/8td9OE8I
LUxuOQYheXKnMRaGbuyWWWOuW5L6FwB0fFDWfSyI45hSGPQVc9emDqc39BQe5D8r1Xz7VSjRB/0m
LyzriNuHlazQW6sy5kQqOzd/ApAohTbfm2FEw6v28zCY5dyCEB7KxtV8XTpD+2N2AkXG1CDW13w/
V80cDRNlxDGyRjfC4pQiB+WFfK/VeglHCF+91e6VL8CoQzuS03lNKR0jrlAfXj30bzQPs6Y/48yM
MqZ1D0XeieFqH22kdYi+H6Neg9N29+Irv5Xpag==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
0Ve6NLv9LAgm7X0weIbnwir114p0TIpy3JJr564j/Afzf5+O68OXUTVJBjz67ftYVFGRxdw09ovY
c34Kra02MS4hQDO2oTqq99gVw+EBc6VNIZaIIZUOp4WIlKu8+hYPFprevtq4YHHCanRCW4Ge6fTM
IYunybL+ceNuKEUuB8puWI1sHWaRMvrWrZ/i+S6g+Vumt74rhpaPsNahcxDgJKVejk0LeIh6/X2S
peBUOCGMLiFkcVZ7fI8L8DYH2nhfITqnH1XaXIRd9VJTvzGYhjGQ75o1FpnbjLVy0/RYx3SRc3vv
6Plg/x90BAVoJUmEH2eTD2qrAZLhTX0OpdSdWw==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 26032)
`pragma protect data_block
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
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
