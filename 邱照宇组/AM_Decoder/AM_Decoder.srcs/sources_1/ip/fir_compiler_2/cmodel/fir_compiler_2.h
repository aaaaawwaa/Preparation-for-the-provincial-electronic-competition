
//------------------------------------------------------------------------------
// (c) Copyright 2014 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//------------------------------------------------------------------------------ 
//
// C Model configuration for the "fir_compiler_2" instance.
//
//------------------------------------------------------------------------------
//
// coefficients: 44,30,39,50,63,78,95,114,135,158,184,211,241,272,305,339,375,412,449,487,524,560,596,629,660,688,712,732,748,758,762,759,750,733,709,676,635,586,529,463,389,308,219,124,23,-83,-193,-306,-420,-536,-650,-762,-871,-974,-1071,-1159,-1238,-1305,-1361,-1403,-1430,-1441,-1436,-1414,-1374,-1317,-1242,-1150,-1042,-917,-778,-625,-461,-286,-104,85,276,468,659,844,1021,1188,1342,1479,1597,1694,1766,1813,1831,1820,1778,1704,1598,1461,1291,1091,862,605,324,20,-302,-640,-989,-1344,-1701,-2055,-2399,-2730,-3042,-3328,-3583,-3802,-3979,-4110,-4189,-4213,-4177,-4078,-3913,-3680,-3377,-3003,-2558,-2043,-1459,-808,-93,683,1515,2398,3326,4294,5294,6319,7362,8413,9465,10510,11537,12540,13510,14437,15314,16134,16888,17571,18175,18697,19130,19471,19717,19865,19915,19865,19717,19471,19130,18697,18175,17571,16888,16134,15314,14437,13510,12540,11537,10510,9465,8413,7362,6319,5294,4294,3326,2398,1515,683,-93,-808,-1459,-2043,-2558,-3003,-3377,-3680,-3913,-4078,-4177,-4213,-4189,-4110,-3979,-3802,-3583,-3328,-3042,-2730,-2399,-2055,-1701,-1344,-989,-640,-302,20,324,605,862,1091,1291,1461,1598,1704,1778,1820,1831,1813,1766,1694,1597,1479,1342,1188,1021,844,659,468,276,85,-104,-286,-461,-625,-778,-917,-1042,-1150,-1242,-1317,-1374,-1414,-1436,-1441,-1430,-1403,-1361,-1305,-1238,-1159,-1071,-974,-871,-762,-650,-536,-420,-306,-193,-83,23,124,219,308,389,463,529,586,635,676,709,733,750,759,762,758,748,732,712,688,660,629,596,560,524,487,449,412,375,339,305,272,241,211,184,158,135,114,95,78,63,50,39,30,44
// chanpats: 173
// name: fir_compiler_2
// filter_type: 0
// rate_change: 0
// interp_rate: 1
// decim_rate: 1
// zero_pack_factor: 1
// coeff_padding: 1
// num_coeffs: 305
// coeff_sets: 1
// reloadable: 0
// is_halfband: 0
// quantization: 0
// coeff_width: 16
// coeff_fract_width: 0
// chan_seq: 0
// num_channels: 1
// num_paths: 1
// data_width: 12
// data_fract_width: 0
// output_rounding_mode: 4
// output_width: 12
// output_fract_width: 0
// config_method: 0

const double fir_compiler_2_coefficients[305] = {44,30,39,50,63,78,95,114,135,158,184,211,241,272,305,339,375,412,449,487,524,560,596,629,660,688,712,732,748,758,762,759,750,733,709,676,635,586,529,463,389,308,219,124,23,-83,-193,-306,-420,-536,-650,-762,-871,-974,-1071,-1159,-1238,-1305,-1361,-1403,-1430,-1441,-1436,-1414,-1374,-1317,-1242,-1150,-1042,-917,-778,-625,-461,-286,-104,85,276,468,659,844,1021,1188,1342,1479,1597,1694,1766,1813,1831,1820,1778,1704,1598,1461,1291,1091,862,605,324,20,-302,-640,-989,-1344,-1701,-2055,-2399,-2730,-3042,-3328,-3583,-3802,-3979,-4110,-4189,-4213,-4177,-4078,-3913,-3680,-3377,-3003,-2558,-2043,-1459,-808,-93,683,1515,2398,3326,4294,5294,6319,7362,8413,9465,10510,11537,12540,13510,14437,15314,16134,16888,17571,18175,18697,19130,19471,19717,19865,19915,19865,19717,19471,19130,18697,18175,17571,16888,16134,15314,14437,13510,12540,11537,10510,9465,8413,7362,6319,5294,4294,3326,2398,1515,683,-93,-808,-1459,-2043,-2558,-3003,-3377,-3680,-3913,-4078,-4177,-4213,-4189,-4110,-3979,-3802,-3583,-3328,-3042,-2730,-2399,-2055,-1701,-1344,-989,-640,-302,20,324,605,862,1091,1291,1461,1598,1704,1778,1820,1831,1813,1766,1694,1597,1479,1342,1188,1021,844,659,468,276,85,-104,-286,-461,-625,-778,-917,-1042,-1150,-1242,-1317,-1374,-1414,-1436,-1441,-1430,-1403,-1361,-1305,-1238,-1159,-1071,-974,-871,-762,-650,-536,-420,-306,-193,-83,23,124,219,308,389,463,529,586,635,676,709,733,750,759,762,758,748,732,712,688,660,629,596,560,524,487,449,412,375,339,305,272,241,211,184,158,135,114,95,78,63,50,39,30,44};

const xip_fir_v7_2_pattern fir_compiler_2_chanpats[1] = {P_BASIC};

static xip_fir_v7_2_config gen_fir_compiler_2_config() {
  xip_fir_v7_2_config config;
  config.name                = "fir_compiler_2";
  config.filter_type         = 0;
  config.rate_change         = XIP_FIR_INTEGER_RATE;
  config.interp_rate         = 1;
  config.decim_rate          = 1;
  config.zero_pack_factor    = 1;
  config.coeff               = &fir_compiler_2_coefficients[0];
  config.coeff_padding       = 1;
  config.num_coeffs          = 305;
  config.coeff_sets          = 1;
  config.reloadable          = 0;
  config.is_halfband         = 0;
  config.quantization        = XIP_FIR_INTEGER_COEFF;
  config.coeff_width         = 16;
  config.coeff_fract_width   = 0;
  config.chan_seq            = XIP_FIR_BASIC_CHAN_SEQ;
  config.num_channels        = 1;
  config.init_pattern        = fir_compiler_2_chanpats[0];
  config.num_paths           = 1;
  config.data_width          = 12;
  config.data_fract_width    = 0;
  config.output_rounding_mode= XIP_FIR_CONVERGENT_EVEN;
  config.output_width        = 12;
  config.output_fract_width  = 0,
  config.config_method       = XIP_FIR_CONFIG_SINGLE;
  return config;
}

const xip_fir_v7_2_config fir_compiler_2_config = gen_fir_compiler_2_config();

