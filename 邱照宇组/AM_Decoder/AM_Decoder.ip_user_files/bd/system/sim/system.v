//Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
//Date        : Mon Jun 15 21:42:42 2026
//Host        : LAPTOP-JO00M47A running 64-bit major release  (build 9200)
//Command     : generate_target system.bd
//Design      : system
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "system,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=system,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=22,numReposBlks=22,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=5,numPkgbdBlks=0,bdsource=USER,da_axi4_cnt=1,da_board_cnt=2,da_ps7_cnt=1,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "system.hwdef" *) 
module system
   (Analog_meg,
    CLK_ADC,
    DDR_addr,
    DDR_ba,
    DDR_cas_n,
    DDR_ck_n,
    DDR_ck_p,
    DDR_cke,
    DDR_cs_n,
    DDR_dm,
    DDR_dq,
    DDR_dqs_n,
    DDR_dqs_p,
    DDR_odt,
    DDR_ras_n,
    DDR_reset_n,
    DDR_we_n,
    FIXED_IO_ddr_vrn,
    FIXED_IO_ddr_vrp,
    FIXED_IO_mio,
    FIXED_IO_ps_clk,
    FIXED_IO_ps_porb,
    FIXED_IO_ps_srstb,
    Meg_input,
    Otr,
    reset_rtl_0);
  output [15:0]Analog_meg;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_ADC CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_ADC, CLK_DOMAIN /clk_wiz_0_clk_out1, FREQ_HZ 65000000, INSERT_VIP 0, PHASE 0.0" *) output CLK_ADC;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR ADDR" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DDR, AXI_ARBITRATION_SCHEME TDM, BURST_LENGTH 8, CAN_DEBUG false, CAS_LATENCY 11, CAS_WRITE_LATENCY 11, CS_ENABLED true, DATA_MASK_ENABLED true, DATA_WIDTH 8, MEMORY_TYPE COMPONENTS, MEM_ADDR_MAP ROW_COLUMN_BANK, SLOT Single, TIMEPERIOD_PS 1250" *) inout [14:0]DDR_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR BA" *) inout [2:0]DDR_ba;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR CAS_N" *) inout DDR_cas_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR CK_N" *) inout DDR_ck_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR CK_P" *) inout DDR_ck_p;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR CKE" *) inout DDR_cke;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR CS_N" *) inout DDR_cs_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR DM" *) inout [3:0]DDR_dm;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR DQ" *) inout [31:0]DDR_dq;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR DQS_N" *) inout [3:0]DDR_dqs_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR DQS_P" *) inout [3:0]DDR_dqs_p;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR ODT" *) inout DDR_odt;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR RAS_N" *) inout DDR_ras_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR RESET_N" *) inout DDR_reset_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:ddrx:1.0 DDR WE_N" *) inout DDR_we_n;
  (* X_INTERFACE_INFO = "xilinx.com:display_processing_system7:fixedio:1.0 FIXED_IO DDR_VRN" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME FIXED_IO, CAN_DEBUG false" *) inout FIXED_IO_ddr_vrn;
  (* X_INTERFACE_INFO = "xilinx.com:display_processing_system7:fixedio:1.0 FIXED_IO DDR_VRP" *) inout FIXED_IO_ddr_vrp;
  (* X_INTERFACE_INFO = "xilinx.com:display_processing_system7:fixedio:1.0 FIXED_IO MIO" *) inout [53:0]FIXED_IO_mio;
  (* X_INTERFACE_INFO = "xilinx.com:display_processing_system7:fixedio:1.0 FIXED_IO PS_CLK" *) inout FIXED_IO_ps_clk;
  (* X_INTERFACE_INFO = "xilinx.com:display_processing_system7:fixedio:1.0 FIXED_IO PS_PORB" *) inout FIXED_IO_ps_porb;
  (* X_INTERFACE_INFO = "xilinx.com:display_processing_system7:fixedio:1.0 FIXED_IO PS_SRSTB" *) inout FIXED_IO_ps_srstb;
  input [11:0]Meg_input;
  input Otr;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESET_RTL_0 RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESET_RTL_0, INSERT_VIP 0, POLARITY ACTIVE_HIGH" *) input reset_rtl_0;

  wire [11:0]AD9226_0_adc_out;
  wire [15:0]AM_decoder_0_decode_out;
  wire [15:0]Valid_logic_0_Out;
  wire [15:0]Valid_logic_1_Out;
  wire [15:0]Valid_logic_2_Out;
  wire [15:0]Valid_logic_3_Out;
  wire [31:0]c_addsub_0_S;
  wire clk_wiz_0_clk_out1;
  wire clk_wiz_0_clk_out3;
  wire [15:0]cordic_0_m_axis_dout_tdata;
  wire cordic_0_m_axis_dout_tvalid;
  wire [15:0]dds_compiler_0_m_axis_data_tdata;
  wire dds_compiler_0_m_axis_data_tvalid;
  wire [15:0]dds_compiler_1_m_axis_data_tdata;
  wire dds_compiler_1_m_axis_data_tvalid;
  wire [15:0]fir_compiler_0_m_axis_data_tdata;
  wire fir_compiler_0_m_axis_data_tvalid;
  wire [15:0]fir_compiler_1_m_axis_data_tdata;
  wire fir_compiler_1_m_axis_data_tvalid;
  wire [27:0]mult_gen_0_P;
  wire [27:0]mult_gen_1_P;
  wire [31:0]mult_gen_2_P;
  wire [31:0]mult_gen_3_P;
  wire [14:0]processing_system7_0_DDR_ADDR;
  wire [2:0]processing_system7_0_DDR_BA;
  wire processing_system7_0_DDR_CAS_N;
  wire processing_system7_0_DDR_CKE;
  wire processing_system7_0_DDR_CK_N;
  wire processing_system7_0_DDR_CK_P;
  wire processing_system7_0_DDR_CS_N;
  wire [3:0]processing_system7_0_DDR_DM;
  wire [31:0]processing_system7_0_DDR_DQ;
  wire [3:0]processing_system7_0_DDR_DQS_N;
  wire [3:0]processing_system7_0_DDR_DQS_P;
  wire processing_system7_0_DDR_ODT;
  wire processing_system7_0_DDR_RAS_N;
  wire processing_system7_0_DDR_RESET_N;
  wire processing_system7_0_DDR_WE_N;
  wire processing_system7_0_FCLK_CLK0;
  wire processing_system7_0_FIXED_IO_DDR_VRN;
  wire processing_system7_0_FIXED_IO_DDR_VRP;
  wire [53:0]processing_system7_0_FIXED_IO_MIO;
  wire processing_system7_0_FIXED_IO_PS_CLK;
  wire processing_system7_0_FIXED_IO_PS_PORB;
  wire processing_system7_0_FIXED_IO_PS_SRSTB;
  wire reset_rtl_0_1;
  wire [0:0]xlconstant_0_dout;
  wire [31:0]xlconstant_1_dout;
  wire [0:0]xlconstant_2_dout;
  wire [0:0]xlconstant_3_dout;

  assign AD9226_0_adc_out = Meg_input[11:0];
  assign Analog_meg[15:0] = AM_decoder_0_decode_out;
  assign CLK_ADC = clk_wiz_0_clk_out3;
  assign reset_rtl_0_1 = reset_rtl_0;
  system_Valid_logic_0_0 Valid_logic_0
       (.CLK(clk_wiz_0_clk_out1),
        .In(dds_compiler_0_m_axis_data_tdata),
        .Out(Valid_logic_0_Out),
        .Reset(reset_rtl_0_1),
        .valid(dds_compiler_0_m_axis_data_tvalid));
  system_Valid_logic_0_1 Valid_logic_1
       (.CLK(clk_wiz_0_clk_out1),
        .In(dds_compiler_1_m_axis_data_tdata),
        .Out(Valid_logic_1_Out),
        .Reset(reset_rtl_0_1),
        .valid(dds_compiler_1_m_axis_data_tvalid));
  system_Valid_logic_1_0 Valid_logic_2
       (.CLK(clk_wiz_0_clk_out1),
        .In(fir_compiler_0_m_axis_data_tdata),
        .Out(Valid_logic_2_Out),
        .Reset(reset_rtl_0_1),
        .valid(fir_compiler_0_m_axis_data_tvalid));
  system_Valid_logic_1_1 Valid_logic_3
       (.CLK(clk_wiz_0_clk_out1),
        .In(fir_compiler_1_m_axis_data_tdata),
        .Out(Valid_logic_3_Out),
        .Reset(reset_rtl_0_1),
        .valid(fir_compiler_1_m_axis_data_tvalid));
  system_Valid_logic_3_0 Valid_logic_4
       (.CLK(clk_wiz_0_clk_out1),
        .In(cordic_0_m_axis_dout_tdata),
        .Out(AM_decoder_0_decode_out),
        .Reset(reset_rtl_0_1),
        .valid(cordic_0_m_axis_dout_tvalid));
  system_c_addsub_0_0 c_addsub_0
       (.A(mult_gen_2_P),
        .B(mult_gen_3_P),
        .CLK(clk_wiz_0_clk_out1),
        .S(c_addsub_0_S));
  system_clk_wiz_0_0 clk_wiz_0
       (.clk_in1(processing_system7_0_FCLK_CLK0),
        .clk_out1(clk_wiz_0_clk_out1),
        .clk_out3(clk_wiz_0_clk_out3));
  system_cordic_0_0 cordic_0
       (.aclk(clk_wiz_0_clk_out1),
        .m_axis_dout_tdata(cordic_0_m_axis_dout_tdata),
        .m_axis_dout_tvalid(cordic_0_m_axis_dout_tvalid),
        .s_axis_cartesian_tdata(c_addsub_0_S),
        .s_axis_cartesian_tvalid(xlconstant_3_dout));
  system_dds_compiler_0_0 dds_compiler_0
       (.aclk(clk_wiz_0_clk_out1),
        .m_axis_data_tdata(dds_compiler_0_m_axis_data_tdata),
        .m_axis_data_tvalid(dds_compiler_0_m_axis_data_tvalid),
        .s_axis_phase_tdata(xlconstant_1_dout[15:0]),
        .s_axis_phase_tvalid(xlconstant_0_dout));
  system_dds_compiler_0_2 dds_compiler_1
       (.aclk(clk_wiz_0_clk_out1),
        .m_axis_data_tdata(dds_compiler_1_m_axis_data_tdata),
        .m_axis_data_tvalid(dds_compiler_1_m_axis_data_tvalid),
        .s_axis_phase_tdata(xlconstant_1_dout[15:0]),
        .s_axis_phase_tvalid(xlconstant_0_dout));
  system_fir_compiler_0_0 fir_compiler_0
       (.aclk(clk_wiz_0_clk_out1),
        .m_axis_data_tdata(fir_compiler_0_m_axis_data_tdata),
        .m_axis_data_tvalid(fir_compiler_0_m_axis_data_tvalid),
        .s_axis_data_tdata(mult_gen_0_P),
        .s_axis_data_tvalid(xlconstant_2_dout));
  system_fir_compiler_0_2 fir_compiler_1
       (.aclk(clk_wiz_0_clk_out1),
        .m_axis_data_tdata(fir_compiler_1_m_axis_data_tdata),
        .m_axis_data_tvalid(fir_compiler_1_m_axis_data_tvalid),
        .s_axis_data_tdata(mult_gen_1_P),
        .s_axis_data_tvalid(xlconstant_2_dout));
  system_ila_0_0 ila_0
       (.clk(clk_wiz_0_clk_out3),
        .probe0(AM_decoder_0_decode_out[13:0]),
        .probe1(AD9226_0_adc_out));
  system_mult_gen_0_0 mult_gen_0
       (.A(AD9226_0_adc_out),
        .B(Valid_logic_0_Out),
        .CLK(clk_wiz_0_clk_out1),
        .P(mult_gen_0_P));
  system_mult_gen_0_1 mult_gen_1
       (.A(AD9226_0_adc_out),
        .B(Valid_logic_1_Out),
        .CLK(clk_wiz_0_clk_out1),
        .P(mult_gen_1_P));
  system_mult_gen_2_0 mult_gen_2
       (.A(Valid_logic_2_Out),
        .B(Valid_logic_2_Out),
        .CLK(clk_wiz_0_clk_out1),
        .P(mult_gen_2_P));
  system_mult_gen_2_1 mult_gen_3
       (.A(Valid_logic_3_Out),
        .B(Valid_logic_3_Out),
        .CLK(clk_wiz_0_clk_out1),
        .P(mult_gen_3_P));
  system_processing_system7_0_0 processing_system7_0
       (.DDR_Addr(DDR_addr[14:0]),
        .DDR_BankAddr(DDR_ba[2:0]),
        .DDR_CAS_n(DDR_cas_n),
        .DDR_CKE(DDR_cke),
        .DDR_CS_n(DDR_cs_n),
        .DDR_Clk(DDR_ck_p),
        .DDR_Clk_n(DDR_ck_n),
        .DDR_DM(DDR_dm[3:0]),
        .DDR_DQ(DDR_dq[31:0]),
        .DDR_DQS(DDR_dqs_p[3:0]),
        .DDR_DQS_n(DDR_dqs_n[3:0]),
        .DDR_DRSTB(DDR_reset_n),
        .DDR_ODT(DDR_odt),
        .DDR_RAS_n(DDR_ras_n),
        .DDR_VRN(FIXED_IO_ddr_vrn),
        .DDR_VRP(FIXED_IO_ddr_vrp),
        .DDR_WEB(DDR_we_n),
        .FCLK_CLK0(processing_system7_0_FCLK_CLK0),
        .MIO(FIXED_IO_mio[53:0]),
        .M_AXI_GP0_ACLK(processing_system7_0_FCLK_CLK0),
        .M_AXI_GP0_ARREADY(1'b0),
        .M_AXI_GP0_AWREADY(1'b0),
        .M_AXI_GP0_BID({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .M_AXI_GP0_BRESP({1'b0,1'b0}),
        .M_AXI_GP0_BVALID(1'b0),
        .M_AXI_GP0_RDATA({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .M_AXI_GP0_RID({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .M_AXI_GP0_RLAST(1'b0),
        .M_AXI_GP0_RRESP({1'b0,1'b0}),
        .M_AXI_GP0_RVALID(1'b0),
        .M_AXI_GP0_WREADY(1'b0),
        .PS_CLK(FIXED_IO_ps_clk),
        .PS_PORB(FIXED_IO_ps_porb),
        .PS_SRSTB(FIXED_IO_ps_srstb));
  system_xlconstant_0_0 xlconstant_0
       (.dout(xlconstant_0_dout));
  system_xlconstant_0_1 xlconstant_1
       (.dout(xlconstant_1_dout));
  system_xlconstant_0_2 xlconstant_2
       (.dout(xlconstant_2_dout));
  system_xlconstant_2_0 xlconstant_3
       (.dout(xlconstant_3_dout));
endmodule
