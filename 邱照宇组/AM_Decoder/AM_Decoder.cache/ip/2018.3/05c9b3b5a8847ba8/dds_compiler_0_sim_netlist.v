// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Fri Jun 12 15:44:38 2026
// Host        : LAPTOP-JO00M47A running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ dds_compiler_0_sim_netlist.v
// Design      : dds_compiler_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg484-2
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "dds_compiler_0,dds_compiler_v6_0_17,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "dds_compiler_v6_0_17,Vivado 2018.3" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
   (aclk,
    m_axis_data_tvalid,
    m_axis_data_tdata,
    m_axis_phase_tvalid,
    m_axis_phase_tdata);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 aclk_intf CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME aclk_intf, ASSOCIATED_BUSIF M_AXIS_PHASE:S_AXIS_CONFIG:M_AXIS_DATA:S_AXIS_PHASE, ASSOCIATED_RESET aresetn, ASSOCIATED_CLKEN aclken, FREQ_HZ 100000000, PHASE 0.000, INSERT_VIP 0" *) input aclk;
  (* x_interface_info = "xilinx.com:interface:axis:1.0 M_AXIS_DATA TVALID" *) (* x_interface_parameter = "XIL_INTERFACENAME M_AXIS_DATA, TDATA_NUM_BYTES 2, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 0, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 100000000, PHASE 0.000, LAYERED_METADATA undef, INSERT_VIP 0" *) output m_axis_data_tvalid;
  (* x_interface_info = "xilinx.com:interface:axis:1.0 M_AXIS_DATA TDATA" *) output [15:0]m_axis_data_tdata;
  (* x_interface_info = "xilinx.com:interface:axis:1.0 M_AXIS_PHASE TVALID" *) (* x_interface_parameter = "XIL_INTERFACENAME M_AXIS_PHASE, TDATA_NUM_BYTES 4, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 0, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 100000000, PHASE 0.000, LAYERED_METADATA undef, INSERT_VIP 0" *) output m_axis_phase_tvalid;
  (* x_interface_info = "xilinx.com:interface:axis:1.0 M_AXIS_PHASE TDATA" *) output [31:0]m_axis_phase_tdata;

  wire aclk;
  wire [15:0]m_axis_data_tdata;
  wire m_axis_data_tvalid;
  wire [31:0]m_axis_phase_tdata;
  wire m_axis_phase_tvalid;
  wire NLW_U0_debug_axi_resync_in_UNCONNECTED;
  wire NLW_U0_debug_core_nd_UNCONNECTED;
  wire NLW_U0_debug_phase_nd_UNCONNECTED;
  wire NLW_U0_event_phase_in_invalid_UNCONNECTED;
  wire NLW_U0_event_pinc_invalid_UNCONNECTED;
  wire NLW_U0_event_poff_invalid_UNCONNECTED;
  wire NLW_U0_event_s_config_tlast_missing_UNCONNECTED;
  wire NLW_U0_event_s_config_tlast_unexpected_UNCONNECTED;
  wire NLW_U0_event_s_phase_chanid_incorrect_UNCONNECTED;
  wire NLW_U0_event_s_phase_tlast_missing_UNCONNECTED;
  wire NLW_U0_event_s_phase_tlast_unexpected_UNCONNECTED;
  wire NLW_U0_m_axis_data_tlast_UNCONNECTED;
  wire NLW_U0_m_axis_phase_tlast_UNCONNECTED;
  wire NLW_U0_s_axis_config_tready_UNCONNECTED;
  wire NLW_U0_s_axis_phase_tready_UNCONNECTED;
  wire [0:0]NLW_U0_debug_axi_chan_in_UNCONNECTED;
  wire [27:0]NLW_U0_debug_axi_pinc_in_UNCONNECTED;
  wire [27:0]NLW_U0_debug_axi_poff_in_UNCONNECTED;
  wire [27:0]NLW_U0_debug_phase_UNCONNECTED;
  wire [0:0]NLW_U0_m_axis_data_tuser_UNCONNECTED;
  wire [0:0]NLW_U0_m_axis_phase_tuser_UNCONNECTED;

  (* C_ACCUMULATOR_WIDTH = "28" *) 
  (* C_AMPLITUDE = "0" *) 
  (* C_CHANNELS = "1" *) 
  (* C_CHAN_WIDTH = "1" *) 
  (* C_DEBUG_INTERFACE = "0" *) 
  (* C_HAS_ACLKEN = "0" *) 
  (* C_HAS_ARESETN = "0" *) 
  (* C_HAS_M_DATA = "1" *) 
  (* C_HAS_M_PHASE = "1" *) 
  (* C_HAS_PHASEGEN = "1" *) 
  (* C_HAS_PHASE_OUT = "1" *) 
  (* C_HAS_SINCOS = "1" *) 
  (* C_HAS_S_CONFIG = "0" *) 
  (* C_HAS_S_PHASE = "0" *) 
  (* C_HAS_TLAST = "0" *) 
  (* C_HAS_TREADY = "0" *) 
  (* C_LATENCY = "3" *) 
  (* C_MEM_TYPE = "1" *) 
  (* C_MODE_OF_OPERATION = "0" *) 
  (* C_MODULUS = "9" *) 
  (* C_M_DATA_HAS_TUSER = "0" *) 
  (* C_M_DATA_TDATA_WIDTH = "16" *) 
  (* C_M_DATA_TUSER_WIDTH = "1" *) 
  (* C_M_PHASE_HAS_TUSER = "0" *) 
  (* C_M_PHASE_TDATA_WIDTH = "32" *) 
  (* C_M_PHASE_TUSER_WIDTH = "1" *) 
  (* C_NEGATIVE_COSINE = "0" *) 
  (* C_NEGATIVE_SINE = "0" *) 
  (* C_NOISE_SHAPING = "0" *) 
  (* C_OPTIMISE_GOAL = "0" *) 
  (* C_OUTPUTS_REQUIRED = "2" *) 
  (* C_OUTPUT_FORM = "0" *) 
  (* C_OUTPUT_WIDTH = "8" *) 
  (* C_PHASE_ANGLE_WIDTH = "8" *) 
  (* C_PHASE_INCREMENT = "2" *) 
  (* C_PHASE_INCREMENT_VALUE = "1101000110110111,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0" *) 
  (* C_PHASE_OFFSET = "0" *) 
  (* C_PHASE_OFFSET_VALUE = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0" *) 
  (* C_POR_MODE = "0" *) 
  (* C_RESYNC = "0" *) 
  (* C_S_CONFIG_SYNC_MODE = "0" *) 
  (* C_S_CONFIG_TDATA_WIDTH = "1" *) 
  (* C_S_PHASE_HAS_TUSER = "0" *) 
  (* C_S_PHASE_TDATA_WIDTH = "1" *) 
  (* C_S_PHASE_TUSER_WIDTH = "1" *) 
  (* C_USE_DSP48 = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_dds_compiler_v6_0_17 U0
       (.aclk(aclk),
        .aclken(1'b1),
        .aresetn(1'b1),
        .debug_axi_chan_in(NLW_U0_debug_axi_chan_in_UNCONNECTED[0]),
        .debug_axi_pinc_in(NLW_U0_debug_axi_pinc_in_UNCONNECTED[27:0]),
        .debug_axi_poff_in(NLW_U0_debug_axi_poff_in_UNCONNECTED[27:0]),
        .debug_axi_resync_in(NLW_U0_debug_axi_resync_in_UNCONNECTED),
        .debug_core_nd(NLW_U0_debug_core_nd_UNCONNECTED),
        .debug_phase(NLW_U0_debug_phase_UNCONNECTED[27:0]),
        .debug_phase_nd(NLW_U0_debug_phase_nd_UNCONNECTED),
        .event_phase_in_invalid(NLW_U0_event_phase_in_invalid_UNCONNECTED),
        .event_pinc_invalid(NLW_U0_event_pinc_invalid_UNCONNECTED),
        .event_poff_invalid(NLW_U0_event_poff_invalid_UNCONNECTED),
        .event_s_config_tlast_missing(NLW_U0_event_s_config_tlast_missing_UNCONNECTED),
        .event_s_config_tlast_unexpected(NLW_U0_event_s_config_tlast_unexpected_UNCONNECTED),
        .event_s_phase_chanid_incorrect(NLW_U0_event_s_phase_chanid_incorrect_UNCONNECTED),
        .event_s_phase_tlast_missing(NLW_U0_event_s_phase_tlast_missing_UNCONNECTED),
        .event_s_phase_tlast_unexpected(NLW_U0_event_s_phase_tlast_unexpected_UNCONNECTED),
        .m_axis_data_tdata(m_axis_data_tdata),
        .m_axis_data_tlast(NLW_U0_m_axis_data_tlast_UNCONNECTED),
        .m_axis_data_tready(1'b0),
        .m_axis_data_tuser(NLW_U0_m_axis_data_tuser_UNCONNECTED[0]),
        .m_axis_data_tvalid(m_axis_data_tvalid),
        .m_axis_phase_tdata(m_axis_phase_tdata),
        .m_axis_phase_tlast(NLW_U0_m_axis_phase_tlast_UNCONNECTED),
        .m_axis_phase_tready(1'b0),
        .m_axis_phase_tuser(NLW_U0_m_axis_phase_tuser_UNCONNECTED[0]),
        .m_axis_phase_tvalid(m_axis_phase_tvalid),
        .s_axis_config_tdata(1'b0),
        .s_axis_config_tlast(1'b0),
        .s_axis_config_tready(NLW_U0_s_axis_config_tready_UNCONNECTED),
        .s_axis_config_tvalid(1'b0),
        .s_axis_phase_tdata(1'b0),
        .s_axis_phase_tlast(1'b0),
        .s_axis_phase_tready(NLW_U0_s_axis_phase_tready_UNCONNECTED),
        .s_axis_phase_tuser(1'b0),
        .s_axis_phase_tvalid(1'b0));
endmodule

(* C_ACCUMULATOR_WIDTH = "28" *) (* C_AMPLITUDE = "0" *) (* C_CHANNELS = "1" *) 
(* C_CHAN_WIDTH = "1" *) (* C_DEBUG_INTERFACE = "0" *) (* C_HAS_ACLKEN = "0" *) 
(* C_HAS_ARESETN = "0" *) (* C_HAS_M_DATA = "1" *) (* C_HAS_M_PHASE = "1" *) 
(* C_HAS_PHASEGEN = "1" *) (* C_HAS_PHASE_OUT = "1" *) (* C_HAS_SINCOS = "1" *) 
(* C_HAS_S_CONFIG = "0" *) (* C_HAS_S_PHASE = "0" *) (* C_HAS_TLAST = "0" *) 
(* C_HAS_TREADY = "0" *) (* C_LATENCY = "3" *) (* C_MEM_TYPE = "1" *) 
(* C_MODE_OF_OPERATION = "0" *) (* C_MODULUS = "9" *) (* C_M_DATA_HAS_TUSER = "0" *) 
(* C_M_DATA_TDATA_WIDTH = "16" *) (* C_M_DATA_TUSER_WIDTH = "1" *) (* C_M_PHASE_HAS_TUSER = "0" *) 
(* C_M_PHASE_TDATA_WIDTH = "32" *) (* C_M_PHASE_TUSER_WIDTH = "1" *) (* C_NEGATIVE_COSINE = "0" *) 
(* C_NEGATIVE_SINE = "0" *) (* C_NOISE_SHAPING = "0" *) (* C_OPTIMISE_GOAL = "0" *) 
(* C_OUTPUTS_REQUIRED = "2" *) (* C_OUTPUT_FORM = "0" *) (* C_OUTPUT_WIDTH = "8" *) 
(* C_PHASE_ANGLE_WIDTH = "8" *) (* C_PHASE_INCREMENT = "2" *) (* C_PHASE_INCREMENT_VALUE = "1101000110110111,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0" *) 
(* C_PHASE_OFFSET = "0" *) (* C_PHASE_OFFSET_VALUE = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0" *) (* C_POR_MODE = "0" *) 
(* C_RESYNC = "0" *) (* C_S_CONFIG_SYNC_MODE = "0" *) (* C_S_CONFIG_TDATA_WIDTH = "1" *) 
(* C_S_PHASE_HAS_TUSER = "0" *) (* C_S_PHASE_TDATA_WIDTH = "1" *) (* C_S_PHASE_TUSER_WIDTH = "1" *) 
(* C_USE_DSP48 = "0" *) (* C_XDEVICEFAMILY = "zynq" *) (* downgradeipidentifiedwarnings = "yes" *) 
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_dds_compiler_v6_0_17
   (aclk,
    aclken,
    aresetn,
    s_axis_phase_tvalid,
    s_axis_phase_tready,
    s_axis_phase_tdata,
    s_axis_phase_tlast,
    s_axis_phase_tuser,
    s_axis_config_tvalid,
    s_axis_config_tready,
    s_axis_config_tdata,
    s_axis_config_tlast,
    m_axis_data_tvalid,
    m_axis_data_tready,
    m_axis_data_tdata,
    m_axis_data_tlast,
    m_axis_data_tuser,
    m_axis_phase_tvalid,
    m_axis_phase_tready,
    m_axis_phase_tdata,
    m_axis_phase_tlast,
    m_axis_phase_tuser,
    event_pinc_invalid,
    event_poff_invalid,
    event_phase_in_invalid,
    event_s_phase_tlast_missing,
    event_s_phase_tlast_unexpected,
    event_s_phase_chanid_incorrect,
    event_s_config_tlast_missing,
    event_s_config_tlast_unexpected,
    debug_axi_pinc_in,
    debug_axi_poff_in,
    debug_axi_resync_in,
    debug_axi_chan_in,
    debug_core_nd,
    debug_phase,
    debug_phase_nd);
  input aclk;
  input aclken;
  input aresetn;
  input s_axis_phase_tvalid;
  output s_axis_phase_tready;
  input [0:0]s_axis_phase_tdata;
  input s_axis_phase_tlast;
  input [0:0]s_axis_phase_tuser;
  input s_axis_config_tvalid;
  output s_axis_config_tready;
  input [0:0]s_axis_config_tdata;
  input s_axis_config_tlast;
  output m_axis_data_tvalid;
  input m_axis_data_tready;
  output [15:0]m_axis_data_tdata;
  output m_axis_data_tlast;
  output [0:0]m_axis_data_tuser;
  output m_axis_phase_tvalid;
  input m_axis_phase_tready;
  output [31:0]m_axis_phase_tdata;
  output m_axis_phase_tlast;
  output [0:0]m_axis_phase_tuser;
  output event_pinc_invalid;
  output event_poff_invalid;
  output event_phase_in_invalid;
  output event_s_phase_tlast_missing;
  output event_s_phase_tlast_unexpected;
  output event_s_phase_chanid_incorrect;
  output event_s_config_tlast_missing;
  output event_s_config_tlast_unexpected;
  output [27:0]debug_axi_pinc_in;
  output [27:0]debug_axi_poff_in;
  output debug_axi_resync_in;
  output [0:0]debug_axi_chan_in;
  output debug_core_nd;
  output [27:0]debug_phase;
  output debug_phase_nd;

  wire \<const0> ;
  wire \<const1> ;
  wire aclk;
  wire [15:0]m_axis_data_tdata;
  wire [27:0]\^m_axis_phase_tdata ;
  wire m_axis_phase_tvalid;
  wire NLW_i_synth_debug_axi_resync_in_UNCONNECTED;
  wire NLW_i_synth_debug_core_nd_UNCONNECTED;
  wire NLW_i_synth_debug_phase_nd_UNCONNECTED;
  wire NLW_i_synth_event_phase_in_invalid_UNCONNECTED;
  wire NLW_i_synth_event_pinc_invalid_UNCONNECTED;
  wire NLW_i_synth_event_poff_invalid_UNCONNECTED;
  wire NLW_i_synth_event_s_config_tlast_missing_UNCONNECTED;
  wire NLW_i_synth_event_s_config_tlast_unexpected_UNCONNECTED;
  wire NLW_i_synth_event_s_phase_chanid_incorrect_UNCONNECTED;
  wire NLW_i_synth_event_s_phase_tlast_missing_UNCONNECTED;
  wire NLW_i_synth_event_s_phase_tlast_unexpected_UNCONNECTED;
  wire NLW_i_synth_m_axis_data_tlast_UNCONNECTED;
  wire NLW_i_synth_m_axis_phase_tlast_UNCONNECTED;
  wire NLW_i_synth_m_axis_phase_tvalid_UNCONNECTED;
  wire NLW_i_synth_s_axis_config_tready_UNCONNECTED;
  wire NLW_i_synth_s_axis_phase_tready_UNCONNECTED;
  wire [0:0]NLW_i_synth_debug_axi_chan_in_UNCONNECTED;
  wire [27:0]NLW_i_synth_debug_axi_pinc_in_UNCONNECTED;
  wire [27:0]NLW_i_synth_debug_axi_poff_in_UNCONNECTED;
  wire [27:0]NLW_i_synth_debug_phase_UNCONNECTED;
  wire [0:0]NLW_i_synth_m_axis_data_tuser_UNCONNECTED;
  wire [30:27]NLW_i_synth_m_axis_phase_tdata_UNCONNECTED;
  wire [0:0]NLW_i_synth_m_axis_phase_tuser_UNCONNECTED;

  assign debug_axi_chan_in[0] = \<const0> ;
  assign debug_axi_pinc_in[27] = \<const0> ;
  assign debug_axi_pinc_in[26] = \<const0> ;
  assign debug_axi_pinc_in[25] = \<const0> ;
  assign debug_axi_pinc_in[24] = \<const0> ;
  assign debug_axi_pinc_in[23] = \<const0> ;
  assign debug_axi_pinc_in[22] = \<const0> ;
  assign debug_axi_pinc_in[21] = \<const0> ;
  assign debug_axi_pinc_in[20] = \<const0> ;
  assign debug_axi_pinc_in[19] = \<const0> ;
  assign debug_axi_pinc_in[18] = \<const0> ;
  assign debug_axi_pinc_in[17] = \<const0> ;
  assign debug_axi_pinc_in[16] = \<const0> ;
  assign debug_axi_pinc_in[15] = \<const0> ;
  assign debug_axi_pinc_in[14] = \<const0> ;
  assign debug_axi_pinc_in[13] = \<const0> ;
  assign debug_axi_pinc_in[12] = \<const0> ;
  assign debug_axi_pinc_in[11] = \<const0> ;
  assign debug_axi_pinc_in[10] = \<const0> ;
  assign debug_axi_pinc_in[9] = \<const0> ;
  assign debug_axi_pinc_in[8] = \<const0> ;
  assign debug_axi_pinc_in[7] = \<const0> ;
  assign debug_axi_pinc_in[6] = \<const0> ;
  assign debug_axi_pinc_in[5] = \<const0> ;
  assign debug_axi_pinc_in[4] = \<const0> ;
  assign debug_axi_pinc_in[3] = \<const0> ;
  assign debug_axi_pinc_in[2] = \<const0> ;
  assign debug_axi_pinc_in[1] = \<const0> ;
  assign debug_axi_pinc_in[0] = \<const0> ;
  assign debug_axi_poff_in[27] = \<const0> ;
  assign debug_axi_poff_in[26] = \<const0> ;
  assign debug_axi_poff_in[25] = \<const0> ;
  assign debug_axi_poff_in[24] = \<const0> ;
  assign debug_axi_poff_in[23] = \<const0> ;
  assign debug_axi_poff_in[22] = \<const0> ;
  assign debug_axi_poff_in[21] = \<const0> ;
  assign debug_axi_poff_in[20] = \<const0> ;
  assign debug_axi_poff_in[19] = \<const0> ;
  assign debug_axi_poff_in[18] = \<const0> ;
  assign debug_axi_poff_in[17] = \<const0> ;
  assign debug_axi_poff_in[16] = \<const0> ;
  assign debug_axi_poff_in[15] = \<const0> ;
  assign debug_axi_poff_in[14] = \<const0> ;
  assign debug_axi_poff_in[13] = \<const0> ;
  assign debug_axi_poff_in[12] = \<const0> ;
  assign debug_axi_poff_in[11] = \<const0> ;
  assign debug_axi_poff_in[10] = \<const0> ;
  assign debug_axi_poff_in[9] = \<const0> ;
  assign debug_axi_poff_in[8] = \<const0> ;
  assign debug_axi_poff_in[7] = \<const0> ;
  assign debug_axi_poff_in[6] = \<const0> ;
  assign debug_axi_poff_in[5] = \<const0> ;
  assign debug_axi_poff_in[4] = \<const0> ;
  assign debug_axi_poff_in[3] = \<const0> ;
  assign debug_axi_poff_in[2] = \<const0> ;
  assign debug_axi_poff_in[1] = \<const0> ;
  assign debug_axi_poff_in[0] = \<const0> ;
  assign debug_axi_resync_in = \<const0> ;
  assign debug_core_nd = \<const0> ;
  assign debug_phase[27] = \<const0> ;
  assign debug_phase[26] = \<const0> ;
  assign debug_phase[25] = \<const0> ;
  assign debug_phase[24] = \<const0> ;
  assign debug_phase[23] = \<const0> ;
  assign debug_phase[22] = \<const0> ;
  assign debug_phase[21] = \<const0> ;
  assign debug_phase[20] = \<const0> ;
  assign debug_phase[19] = \<const0> ;
  assign debug_phase[18] = \<const0> ;
  assign debug_phase[17] = \<const0> ;
  assign debug_phase[16] = \<const0> ;
  assign debug_phase[15] = \<const0> ;
  assign debug_phase[14] = \<const0> ;
  assign debug_phase[13] = \<const0> ;
  assign debug_phase[12] = \<const0> ;
  assign debug_phase[11] = \<const0> ;
  assign debug_phase[10] = \<const0> ;
  assign debug_phase[9] = \<const0> ;
  assign debug_phase[8] = \<const0> ;
  assign debug_phase[7] = \<const0> ;
  assign debug_phase[6] = \<const0> ;
  assign debug_phase[5] = \<const0> ;
  assign debug_phase[4] = \<const0> ;
  assign debug_phase[3] = \<const0> ;
  assign debug_phase[2] = \<const0> ;
  assign debug_phase[1] = \<const0> ;
  assign debug_phase[0] = \<const0> ;
  assign debug_phase_nd = \<const0> ;
  assign event_phase_in_invalid = \<const0> ;
  assign event_pinc_invalid = \<const0> ;
  assign event_poff_invalid = \<const0> ;
  assign event_s_config_tlast_missing = \<const0> ;
  assign event_s_config_tlast_unexpected = \<const0> ;
  assign event_s_phase_chanid_incorrect = \<const0> ;
  assign event_s_phase_tlast_missing = \<const0> ;
  assign event_s_phase_tlast_unexpected = \<const0> ;
  assign m_axis_data_tlast = \<const0> ;
  assign m_axis_data_tuser[0] = \<const0> ;
  assign m_axis_data_tvalid = m_axis_phase_tvalid;
  assign m_axis_phase_tdata[31] = \^m_axis_phase_tdata [27];
  assign m_axis_phase_tdata[30] = \^m_axis_phase_tdata [27];
  assign m_axis_phase_tdata[29] = \^m_axis_phase_tdata [27];
  assign m_axis_phase_tdata[28] = \^m_axis_phase_tdata [27];
  assign m_axis_phase_tdata[27:0] = \^m_axis_phase_tdata [27:0];
  assign m_axis_phase_tlast = \<const0> ;
  assign m_axis_phase_tuser[0] = \<const0> ;
  assign s_axis_config_tready = \<const1> ;
  assign s_axis_phase_tready = \<const0> ;
  GND GND
       (.G(\<const0> ));
  VCC VCC
       (.P(\<const1> ));
  (* C_ACCUMULATOR_WIDTH = "28" *) 
  (* C_AMPLITUDE = "0" *) 
  (* C_CHANNELS = "1" *) 
  (* C_CHAN_WIDTH = "1" *) 
  (* C_DEBUG_INTERFACE = "0" *) 
  (* C_HAS_ACLKEN = "0" *) 
  (* C_HAS_ARESETN = "0" *) 
  (* C_HAS_M_DATA = "1" *) 
  (* C_HAS_M_PHASE = "1" *) 
  (* C_HAS_PHASEGEN = "1" *) 
  (* C_HAS_PHASE_OUT = "1" *) 
  (* C_HAS_SINCOS = "1" *) 
  (* C_HAS_S_CONFIG = "0" *) 
  (* C_HAS_S_PHASE = "0" *) 
  (* C_HAS_TLAST = "0" *) 
  (* C_HAS_TREADY = "0" *) 
  (* C_LATENCY = "3" *) 
  (* C_MEM_TYPE = "1" *) 
  (* C_MODE_OF_OPERATION = "0" *) 
  (* C_MODULUS = "9" *) 
  (* C_M_DATA_HAS_TUSER = "0" *) 
  (* C_M_DATA_TDATA_WIDTH = "16" *) 
  (* C_M_DATA_TUSER_WIDTH = "1" *) 
  (* C_M_PHASE_HAS_TUSER = "0" *) 
  (* C_M_PHASE_TDATA_WIDTH = "32" *) 
  (* C_M_PHASE_TUSER_WIDTH = "1" *) 
  (* C_NEGATIVE_COSINE = "0" *) 
  (* C_NEGATIVE_SINE = "0" *) 
  (* C_NOISE_SHAPING = "0" *) 
  (* C_OPTIMISE_GOAL = "0" *) 
  (* C_OUTPUTS_REQUIRED = "2" *) 
  (* C_OUTPUT_FORM = "0" *) 
  (* C_OUTPUT_WIDTH = "8" *) 
  (* C_PHASE_ANGLE_WIDTH = "8" *) 
  (* C_PHASE_INCREMENT = "2" *) 
  (* C_PHASE_INCREMENT_VALUE = "1101000110110111,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0" *) 
  (* C_PHASE_OFFSET = "0" *) 
  (* C_PHASE_OFFSET_VALUE = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0" *) 
  (* C_POR_MODE = "0" *) 
  (* C_RESYNC = "0" *) 
  (* C_S_CONFIG_SYNC_MODE = "0" *) 
  (* C_S_CONFIG_TDATA_WIDTH = "1" *) 
  (* C_S_PHASE_HAS_TUSER = "0" *) 
  (* C_S_PHASE_TDATA_WIDTH = "1" *) 
  (* C_S_PHASE_TUSER_WIDTH = "1" *) 
  (* C_USE_DSP48 = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_dds_compiler_v6_0_17_viv i_synth
       (.aclk(aclk),
        .aclken(1'b0),
        .aresetn(1'b0),
        .debug_axi_chan_in(NLW_i_synth_debug_axi_chan_in_UNCONNECTED[0]),
        .debug_axi_pinc_in(NLW_i_synth_debug_axi_pinc_in_UNCONNECTED[27:0]),
        .debug_axi_poff_in(NLW_i_synth_debug_axi_poff_in_UNCONNECTED[27:0]),
        .debug_axi_resync_in(NLW_i_synth_debug_axi_resync_in_UNCONNECTED),
        .debug_core_nd(NLW_i_synth_debug_core_nd_UNCONNECTED),
        .debug_phase(NLW_i_synth_debug_phase_UNCONNECTED[27:0]),
        .debug_phase_nd(NLW_i_synth_debug_phase_nd_UNCONNECTED),
        .event_phase_in_invalid(NLW_i_synth_event_phase_in_invalid_UNCONNECTED),
        .event_pinc_invalid(NLW_i_synth_event_pinc_invalid_UNCONNECTED),
        .event_poff_invalid(NLW_i_synth_event_poff_invalid_UNCONNECTED),
        .event_s_config_tlast_missing(NLW_i_synth_event_s_config_tlast_missing_UNCONNECTED),
        .event_s_config_tlast_unexpected(NLW_i_synth_event_s_config_tlast_unexpected_UNCONNECTED),
        .event_s_phase_chanid_incorrect(NLW_i_synth_event_s_phase_chanid_incorrect_UNCONNECTED),
        .event_s_phase_tlast_missing(NLW_i_synth_event_s_phase_tlast_missing_UNCONNECTED),
        .event_s_phase_tlast_unexpected(NLW_i_synth_event_s_phase_tlast_unexpected_UNCONNECTED),
        .m_axis_data_tdata(m_axis_data_tdata),
        .m_axis_data_tlast(NLW_i_synth_m_axis_data_tlast_UNCONNECTED),
        .m_axis_data_tready(1'b0),
        .m_axis_data_tuser(NLW_i_synth_m_axis_data_tuser_UNCONNECTED[0]),
        .m_axis_data_tvalid(m_axis_phase_tvalid),
        .m_axis_phase_tdata({\^m_axis_phase_tdata [27],NLW_i_synth_m_axis_phase_tdata_UNCONNECTED[30:27],\^m_axis_phase_tdata [26:0]}),
        .m_axis_phase_tlast(NLW_i_synth_m_axis_phase_tlast_UNCONNECTED),
        .m_axis_phase_tready(1'b0),
        .m_axis_phase_tuser(NLW_i_synth_m_axis_phase_tuser_UNCONNECTED[0]),
        .m_axis_phase_tvalid(NLW_i_synth_m_axis_phase_tvalid_UNCONNECTED),
        .s_axis_config_tdata(1'b0),
        .s_axis_config_tlast(1'b0),
        .s_axis_config_tready(NLW_i_synth_s_axis_config_tready_UNCONNECTED),
        .s_axis_config_tvalid(1'b0),
        .s_axis_phase_tdata(1'b0),
        .s_axis_phase_tlast(1'b0),
        .s_axis_phase_tready(NLW_i_synth_s_axis_phase_tready_UNCONNECTED),
        .s_axis_phase_tuser(1'b0),
        .s_axis_phase_tvalid(1'b0));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2015"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
gl8oTb3yK39LjDQS0B4PYP+vte8cGiBpEmJ9JLxCkI04rBQJe5sCt4dvUGvg1Ga0GoPkN0BTvh6i
v1YMWuZiJg==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
LV5tnIhV6fXU4gAQOLXCxdxya9doivJt+Y+5yV24zJ1I56Mu4gOTYyKzdDBlwz49as5fPNOvHvtM
FEjflUU6R2Yh76tXBr2An7Tc7qdcv/WUX57JWpXSPQfxdtsoJzfNEA5lf9cFyHWa+eE27NH4fCIB
fHvZTqNYCqZpO8hMEWo=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
CtefK+dE5tJYyIkOlXrI1GU3HbXkaFgSREpPJj1NZdNualyVqOHiPJK5xJ71xxO6zkXYtBYfzkxn
9Eqf7SpqFizTSC3YZVNAp0ix3wloJ2xu9/08YGAzwYtrD72s/REOd9GdOS5BW5KfXcLDWxJnWFK3
mjj+cPJfHeoGuNLu6gH6HD/lNP6geaOelYYVD/TVk4P/j6qWfCikFKKuomVo3jbRD7F7QdkJDCeh
d5Xc8VxEXSaKIjFRuMTWZtjAQjFH5UpSMVhxV/fXhvzSM6V5P4QZA+memX692B8GYsTFU76iMlss
d7ocDlaRWbY0BTXFb2HZNfGcl+sqYKs8PYn/UA==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
UTuJ2/FiXz7w8k47LqoJjpB8chaAWEBjYpgn4jj1PBd2l6Nj6avA0We0iYNi5AJkwcUofxaNsFtE
+sVWsmGPk/0vN5Q90wbwbfGu18ni9SqWiSNRSUzzfB9h0bol599BuMG2pbcdYlanUIn9oPi4ZKeJ
2M667aoQ2BTcU/o1U8nn5wuoiboeNIqzcJS0jj+j6J5UYz5aHgwMcFlCGUwSQuAp+2VIulW4T1IV
NW+4iXCF7wife+1/XS6RYcYu+n4km8U2A8z/nLIuNXSO1T2HaR6rR3YxTorPEFUQnfrre1FxRLzT
6pi4dXPFPyG1bXISdn2AleLyNN3VFQjTEgHwsA==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2017_05", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
FMUkchj5p9XvgJ9tR5grSuP9aw5xa30l1YgNWO9WvtYYjYtQnsPBns5ryDL+PXPqQYQ3i0NvbEVZ
mN4H44H269BdOgH+vRRI3SR79goz8NqADp1QSv06wD02bUASlMq9aM6Phdxmqoalzn7A7dWDa+nU
2QokmpYQQylaKE1ZbXrz6loBY1IeoaMxbsQcvxJcI2aG1HO9NfyR9d5i3K9UmO1t9jFA+8k+GsKj
kNnLxX6I0J9fN8wKc7D007S9DgoQs6+WuCL6CudeG25OH6Gy/uLkY2Udzdpodegx89FgRLo92dDh
+0eWKh3H5TN2vtQ9mtD1iH6zm1l1IqnYy2G06A==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
IjA88m1asiYMyCqMLSP/pVhA6mm9v8t5bFtEAMOvlQO8WTy5Vpca8kFPPuhuf6voqy+zwcLXRU9a
5UwLvCxgOEOo68GA3l4AR9WaPmcxPTPUwChO8zkHIDrS0eoDFMY1OTr1Lv8pbJknphtPExopREwk
KuHbtq4Mg3zw+se7q5E=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
nZ0uDa4zhbQfoZoNpOAKrHOsOrOlSYjg5j1zWlifZ7mksZmmo1GUwbu4BrFKsE9nPAJUOa85AaS6
3sPqXGDLUL68TzDI06mN0/idhoIRBSJNinUfJpw4Ro9h/zNx1E//RfaHklSArW0rHrP6JnabQq/E
ywpKofyKtfWBjZrTJqD+xFD3BsXO9W35e9lAY/pTqzN6C7dC2o6xELYMw7a37e+7TEDqEPb1kk1i
VC/DX7v1veomIkT4wlTej+pa1pSQH6uN/huOhLuz4yEz/zZdnoDInKQyuWaZgdQV+2dfYBgbf+po
404pK0Ii/DBBTh6IKooZGzVmsyG/5MKNX6F9vw==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
O9/3rz0xaDu490ngAMseWoWN/PuoP7P6JgMbVwLRmMdaqGOHfuz5jRkC/xsgNk9zWgG2TBNdapoD
oygrYkdq+Wmvf/HjvZdlvKewDPhpW/go7+IfMmhVlF4Srlc5OtERN+JFEOohCMrMfjFLoBa7+WBH
94En5UbhlmFVmUMLdEbCxSvIK8gfeRnFJG5xtme/29X2zizv+S6V5R1IXEkX+HRk2NvJ4+GuGrNS
E7N/VFZSiK0Ts1sn6m6BNkw7ZSFgHnj/+x6Zeg+/CEovNjjfCfo93wXJOF2wirMY8bxGylHGR+7U
ARD/GZkZgpUhCauDwVEZtCvwjSr78JkPuqu9Vw==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
DNfYFkU7pdK1NIg5xARgAhnv9onjbEKbIgqpxpLA1yizTvJ0t7spQFiA8iTex9btcwJTkP5uVFYh
9so1sAQmg6hDlUv5W4X7J9Hk0cS/gjyG/hnwPqCxUMSQnLhf7xvipiGL0FYS/T8neZ9yHBmMqB1D
2mkJro9NT/fswX4ev06Pf4EiysSomCivUL4KSZAoNgHmnwAvPtDnz7m61uNB1wF5yDw+n45MUIH8
jhFt4xofCUn5bSDEbgBrqxacQuKEeGmRCsVMI/GJh8+AKkP53Ws1y10rZqhPtaBG0H3OPNWfi70G
3CMR4C26ZEthkphwQe91l2H1BpOtapWG3M9AYA==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 45024)
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
