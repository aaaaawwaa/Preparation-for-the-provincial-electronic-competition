// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Mon Jun 15 21:59:15 2026
// Host        : LAPTOP-JO00M47A running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ system_c_addsub_0_0_sim_netlist.v
// Design      : system_c_addsub_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg484-2
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "system_c_addsub_0_0,c_addsub_v12_0_12,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "c_addsub_v12_0_12,Vivado 2018.3" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
   (A,
    B,
    CLK,
    S);
  (* x_interface_info = "xilinx.com:signal:data:1.0 a_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME a_intf, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value data} bitwidth {attribs {resolve_type generated dependency bitwidth format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type generated dependency signed format bool minimum {} maximum {}} value TRUE}}}} DATA_WIDTH 32}" *) input [31:0]A;
  (* x_interface_info = "xilinx.com:signal:data:1.0 b_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME b_intf, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value data} bitwidth {attribs {resolve_type generated dependency bitwidth format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type generated dependency signed format bool minimum {} maximum {}} value TRUE}}}} DATA_WIDTH 32}" *) input [31:0]B;
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk_intf CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk_intf, ASSOCIATED_BUSIF s_intf:c_out_intf:sinit_intf:sset_intf:bypass_intf:c_in_intf:add_intf:b_intf:a_intf, ASSOCIATED_RESET SCLR, ASSOCIATED_CLKEN CE, FREQ_HZ 260000000, PHASE 0.0, CLK_DOMAIN /clk_wiz_0_clk_out1, INSERT_VIP 0" *) input CLK;
  (* x_interface_info = "xilinx.com:signal:data:1.0 s_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME s_intf, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value data} bitwidth {attribs {resolve_type generated dependency bitwidth format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type generated dependency signed format bool minimum {} maximum {}} value TRUE}}}} DATA_WIDTH 32}" *) output [31:0]S;

  wire [31:0]A;
  wire [31:0]B;
  wire CLK;
  wire [31:0]S;
  wire NLW_U0_C_OUT_UNCONNECTED;

  (* C_AINIT_VAL = "0" *) 
  (* C_BORROW_LOW = "1" *) 
  (* C_CE_OVERRIDES_BYPASS = "1" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_SINIT = "0" *) 
  (* C_HAS_SSET = "0" *) 
  (* C_IMPLEMENTATION = "0" *) 
  (* C_SCLR_OVERRIDES_SSET = "1" *) 
  (* C_SINIT_VAL = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* c_a_type = "0" *) 
  (* c_a_width = "32" *) 
  (* c_add_mode = "0" *) 
  (* c_b_constant = "0" *) 
  (* c_b_type = "0" *) 
  (* c_b_value = "00000000000000000000000000000000" *) 
  (* c_b_width = "32" *) 
  (* c_bypass_low = "0" *) 
  (* c_has_bypass = "0" *) 
  (* c_has_c_in = "0" *) 
  (* c_has_c_out = "0" *) 
  (* c_latency = "1" *) 
  (* c_out_width = "32" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_c_addsub_v12_0_12 U0
       (.A(A),
        .ADD(1'b1),
        .B(B),
        .BYPASS(1'b0),
        .CE(1'b1),
        .CLK(CLK),
        .C_IN(1'b0),
        .C_OUT(NLW_U0_C_OUT_UNCONNECTED),
        .S(S),
        .SCLR(1'b0),
        .SINIT(1'b0),
        .SSET(1'b0));
endmodule

(* C_ADD_MODE = "0" *) (* C_AINIT_VAL = "0" *) (* C_A_TYPE = "0" *) 
(* C_A_WIDTH = "32" *) (* C_BORROW_LOW = "1" *) (* C_BYPASS_LOW = "0" *) 
(* C_B_CONSTANT = "0" *) (* C_B_TYPE = "0" *) (* C_B_VALUE = "00000000000000000000000000000000" *) 
(* C_B_WIDTH = "32" *) (* C_CE_OVERRIDES_BYPASS = "1" *) (* C_CE_OVERRIDES_SCLR = "0" *) 
(* C_HAS_BYPASS = "0" *) (* C_HAS_CE = "0" *) (* C_HAS_C_IN = "0" *) 
(* C_HAS_C_OUT = "0" *) (* C_HAS_SCLR = "0" *) (* C_HAS_SINIT = "0" *) 
(* C_HAS_SSET = "0" *) (* C_IMPLEMENTATION = "0" *) (* C_LATENCY = "1" *) 
(* C_OUT_WIDTH = "32" *) (* C_SCLR_OVERRIDES_SSET = "1" *) (* C_SINIT_VAL = "0" *) 
(* C_VERBOSITY = "0" *) (* C_XDEVICEFAMILY = "zynq" *) (* downgradeipidentifiedwarnings = "yes" *) 
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_c_addsub_v12_0_12
   (A,
    B,
    CLK,
    ADD,
    C_IN,
    CE,
    BYPASS,
    SCLR,
    SSET,
    SINIT,
    C_OUT,
    S);
  input [31:0]A;
  input [31:0]B;
  input CLK;
  input ADD;
  input C_IN;
  input CE;
  input BYPASS;
  input SCLR;
  input SSET;
  input SINIT;
  output C_OUT;
  output [31:0]S;

  wire \<const0> ;
  wire [31:0]A;
  wire [31:0]B;
  wire CLK;
  wire [31:0]S;
  wire NLW_xst_addsub_C_OUT_UNCONNECTED;

  assign C_OUT = \<const0> ;
  GND GND
       (.G(\<const0> ));
  (* C_AINIT_VAL = "0" *) 
  (* C_BORROW_LOW = "1" *) 
  (* C_CE_OVERRIDES_BYPASS = "1" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_SINIT = "0" *) 
  (* C_HAS_SSET = "0" *) 
  (* C_IMPLEMENTATION = "0" *) 
  (* C_SCLR_OVERRIDES_SSET = "1" *) 
  (* C_SINIT_VAL = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* c_a_type = "0" *) 
  (* c_a_width = "32" *) 
  (* c_add_mode = "0" *) 
  (* c_b_constant = "0" *) 
  (* c_b_type = "0" *) 
  (* c_b_value = "00000000000000000000000000000000" *) 
  (* c_b_width = "32" *) 
  (* c_bypass_low = "0" *) 
  (* c_has_bypass = "0" *) 
  (* c_has_c_in = "0" *) 
  (* c_has_c_out = "0" *) 
  (* c_latency = "1" *) 
  (* c_out_width = "32" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_c_addsub_v12_0_12_viv xst_addsub
       (.A(A),
        .ADD(1'b0),
        .B(B),
        .BYPASS(1'b0),
        .CE(1'b0),
        .CLK(CLK),
        .C_IN(1'b0),
        .C_OUT(NLW_xst_addsub_C_OUT_UNCONNECTED),
        .S(S),
        .SCLR(1'b0),
        .SINIT(1'b0),
        .SSET(1'b0));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2015"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
INaBf8vh5mCmDzf2yp77pxZAxQdyEQiT/vG2dEgvrFjseUnGc6ldwH4JvdnpZSpdf/ihioPyMNjl
u6ooyzv5TA==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
S5XIZZtuFR/MZffuhwdnvE3H9oRWM4uXoaGZTa/Dyk62O+Wa0v41pjmZELCiR7uodZPFQfykZ6K9
2ZDMu8dB3afQRMs5lnd/53M1b9ke+MNEeZ/wzjUcsJghubnEAwzdWeW/0tlqST1WD9B/KCxYqwH5
Gj6IZTTFHAXcaVhnCT8=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
CM6IcdzP0PbD6yMSqylmi4JE2qpmxiNeI+prjGwJiD8e3Xsynu3PbGKJAOpOxtR1hT/3mpBcx1Rz
Fkz0QBh4wtE8fiziv1i+xi8T6cqC8ClamjrpZ//sn6dh7NvwSYik14MlwVuei4DZoZJZF63aoPUn
RXkQ13wtK+MkYKBcPVSZMFZmaCU6jMMBYclXzvRG1JqqZoa7mWFTeFZePUTXG7Wo12QaZ8GUi0AV
UIshoN25yn5e2Xr3FyuEtm5AvsZb+iLsgLeHBtKBnsVaHQphicgqwgwv6MQQF6ZNBgU/aACfibDS
3+n/mMMm8k1cj2bW6VCi7a+c8LmCf81NlJuLww==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
ehl0CusS7+JNGq6HfhyaBMy68nccIdIGqixoEztEZfkCpXuUYsdqw6G9MIJdWdu0Ck2acV7K6IVg
rzb8/bNaDDVWp48kupToegTkOdwDkCejEqppido4BkJ+iEkjPniz+aJHlOlOwmauETy2hCMuuC57
oWDprzGWlsqbCjqzKrXmPYm6fNdcOa2DiOYstQaMFNbPU2ccrbLJAiYMHNDqtPNqWxKBsD67kiGf
2eOneDOmdmy7YkNsL+cx8MJc3BVUsYBrpAEsGyFMkmX8a8nYz8R/wlFQFGQAd/t5XrfxFNI58mj1
AHXbcAMhGKVq9YdKeU/vSXY/NwMqp12xJ1nUaw==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2017_05", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
h/qRAwiPuqY/Zg/QWqbaYm8xWTi9SshYuPzyL0UME9ZDDF+C2CyGAugh9HzMdD0kZmT94TKmBgLR
dKP28nlE8VCCU5rvbjKxfn/wNtNKHCvZ1hns8CF7+pGuelhxGvXNmYKFw5co8+4grYFaDXeoZZR6
S5sjvhqtSVD3+qq4vYWRjT2Y/yes7L9dRsLq2D3iZ4xjgVHuIbOQLT/EUKW+9iYudT9Uy6YTwB+5
mSb0QK3YfZdGwZyXB4S3mdF9vNQHdW/rnACq3yngF+lprNkh3ooQKdGqtxtz8KSQxNZOAFE+koOw
h00o7AKpvDAp3uNguLvnNJH3rugOhh95b8Jatw==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
TsA04vIYHDZne2CBj5bWCBFH4MtNoFDCn/3DNEi0BwutuUf+X+lD9kAO3kl352WHjQbF79Ssm+PT
fCYpODgWdxSVbzaHFpITxCQ4HcIJhUeW5PC5tw09Tand68D6eg84qRguH+llbb5jdGJkJeTCf+Mx
pupkkLiDvNyTYWe+nqw=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
rx9hgQkvaJJTJJcTjGFW1DrrWiT+xanrcMvFn0Z3KRXlZvf+SE7IQgGCiP7ZDA6T5z1Zv5nzS4h5
cVi+CvwC9UMZRWmLDAjzASJ2nx1g9BjbYe2vHAUmyurIiR6LSigTeM/9TlMv+fFwJbqwuH6FJ3/z
Vl4tIMk4NrqkMn/riOG87SjhesepM6kcQOBgDGzLTG14z3qeZG8OPzxgApfyubmX4qdD1oTgGm2u
Q4mQfFxEye6Jqkn4Rzjhifs/ieNYomHlK7R2/72QJj5j0WyYBIhvO+09izz299Z54ZP2ZXaRMfDT
lU4lQNqQU14PX9Yk9p7sy2PnK4vTwwF0CFIgSQ==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
ewmKaoZ5UZ9X4X1q4EKZGzZD21UHxG07V3aPMiv39qlFq2S0cyHLGTmNB0yio/FfaBCH9ZUORMtj
SSwO+h/O5VUs9Kb9BbOczNWaMzp3aczC7aJbUR0NPbhwMSdR15nCo5lIGlNxW1inLvtmxFM4gzcL
VbtfXY2hCczh1rn2cEjdO/FdatKIkuDF9iQSBxY1MpIfkEkhf5igVxAhQ7qyZ907gMa1+HZ0T7CU
f1Ayj23V71d3xJirEYpRn2L2eAJvP9BNewr0OmfYtKLeV2FjYvOMLSELotSpLGN80vJj0xu5WTyW
3gRzpuqnEwhtAlskMGRpwrl2rAn/10rE8LIxrg==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
iHLYqS8q/qC+JQO6BGZFvtJKXoBQqYjqO3r8IYSfIScUEfsHG7GJZQUcYhNBEh4p13tPaJMhE0cs
Ylqn4D9NGoTnz2taDuKupAYyuBMvS426Pu+xj3kle6FJX3ZvZDPL1y112navReej58B/UwPKp1MS
RfDHbSmCnW5hO8bOzFIEp+4w97wsqFaXQ2xV697MZelbGivyhy5JwxgQIt0lGJe6HWbE+nxnrt1M
b4yUxEpL/wuEmjGrOVxeV5/fMJMwfUUTIVUquqnM+gtlfPtgfmX38eiXpa7JCc0RRLc9OD/gosVc
PJ5A4MiMrX9HMkPR8InsZ+1CwSUaZOn5Gur72A==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 23248)
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
