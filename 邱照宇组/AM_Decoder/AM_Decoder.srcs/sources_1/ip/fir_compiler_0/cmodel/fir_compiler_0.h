
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
// C Model configuration for the "fir_compiler_0" instance.
//
//------------------------------------------------------------------------------
//
// coefficients: 403,-32,-52,-85,-129,-181,-239,-299,-359,-414,-460,-494,-512,-513,-493,-454,-395,-318,-227,-126,-20,85,183,268,335,379,397,386,348,283,195,89,-27,-148,-263,-365,-446,-500,-522,-508,-458,-373,-259,-120,34,193,346,482,592,666,697,681,616,506,354,171,-34,-246,-452,-637,-786,-888,-933,-915,-833,-688,-487,-243,32,318,597,849,1054,1197,1264,1245,1138,946,677,345,-29,-423,-809,-1162,-1453,-1659,-1761,-1745,-1606,-1345,-972,-506,27,593,1157,1679,2119,2442,2617,2619,2435,2062,1512,804,-24,-929,-1856,-2744,-3529,-4146,-4535,-4643,-4427,-3858,-2921,-1620,23,1969,4164,6536,9005,11482,13873,16087,18035,19640,20836,21573,21823,21573,20836,19640,18035,16087,13873,11482,9005,6536,4164,1969,23,-1620,-2921,-3858,-4427,-4643,-4535,-4146,-3529,-2744,-1856,-929,-24,804,1512,2062,2435,2619,2617,2442,2119,1679,1157,593,27,-506,-972,-1345,-1606,-1745,-1761,-1659,-1453,-1162,-809,-423,-29,345,677,946,1138,1245,1264,1197,1054,849,597,318,32,-243,-487,-688,-833,-915,-933,-888,-786,-637,-452,-246,-34,171,354,506,616,681,697,666,592,482,346,193,34,-120,-259,-373,-458,-508,-522,-500,-446,-365,-263,-148,-27,89,195,283,348,386,397,379,335,268,183,85,-20,-126,-227,-318,-395,-454,-493,-513,-512,-494,-460,-414,-359,-299,-239,-181,-129,-85,-52,-32,403
// chanpats: 173
// name: fir_compiler_0
// filter_type: 0
// rate_change: 0
// interp_rate: 1
// decim_rate: 1
// zero_pack_factor: 1
// coeff_padding: 0
// num_coeffs: 257
// coeff_sets: 1
// reloadable: 0
// is_halfband: 0
// quantization: 0
// coeff_width: 16
// coeff_fract_width: 0
// chan_seq: 0
// num_channels: 1
// num_paths: 1
// data_width: 28
// data_fract_width: 0
// output_rounding_mode: 4
// output_width: 16
// output_fract_width: 0
// config_method: 0

const double fir_compiler_0_coefficients[257] = {403,-32,-52,-85,-129,-181,-239,-299,-359,-414,-460,-494,-512,-513,-493,-454,-395,-318,-227,-126,-20,85,183,268,335,379,397,386,348,283,195,89,-27,-148,-263,-365,-446,-500,-522,-508,-458,-373,-259,-120,34,193,346,482,592,666,697,681,616,506,354,171,-34,-246,-452,-637,-786,-888,-933,-915,-833,-688,-487,-243,32,318,597,849,1054,1197,1264,1245,1138,946,677,345,-29,-423,-809,-1162,-1453,-1659,-1761,-1745,-1606,-1345,-972,-506,27,593,1157,1679,2119,2442,2617,2619,2435,2062,1512,804,-24,-929,-1856,-2744,-3529,-4146,-4535,-4643,-4427,-3858,-2921,-1620,23,1969,4164,6536,9005,11482,13873,16087,18035,19640,20836,21573,21823,21573,20836,19640,18035,16087,13873,11482,9005,6536,4164,1969,23,-1620,-2921,-3858,-4427,-4643,-4535,-4146,-3529,-2744,-1856,-929,-24,804,1512,2062,2435,2619,2617,2442,2119,1679,1157,593,27,-506,-972,-1345,-1606,-1745,-1761,-1659,-1453,-1162,-809,-423,-29,345,677,946,1138,1245,1264,1197,1054,849,597,318,32,-243,-487,-688,-833,-915,-933,-888,-786,-637,-452,-246,-34,171,354,506,616,681,697,666,592,482,346,193,34,-120,-259,-373,-458,-508,-522,-500,-446,-365,-263,-148,-27,89,195,283,348,386,397,379,335,268,183,85,-20,-126,-227,-318,-395,-454,-493,-513,-512,-494,-460,-414,-359,-299,-239,-181,-129,-85,-52,-32,403};

const xip_fir_v7_2_pattern fir_compiler_0_chanpats[1] = {P_BASIC};

static xip_fir_v7_2_config gen_fir_compiler_0_config() {
  xip_fir_v7_2_config config;
  config.name                = "fir_compiler_0";
  config.filter_type         = 0;
  config.rate_change         = XIP_FIR_INTEGER_RATE;
  config.interp_rate         = 1;
  config.decim_rate          = 1;
  config.zero_pack_factor    = 1;
  config.coeff               = &fir_compiler_0_coefficients[0];
  config.coeff_padding       = 0;
  config.num_coeffs          = 257;
  config.coeff_sets          = 1;
  config.reloadable          = 0;
  config.is_halfband         = 0;
  config.quantization        = XIP_FIR_INTEGER_COEFF;
  config.coeff_width         = 16;
  config.coeff_fract_width   = 0;
  config.chan_seq            = XIP_FIR_BASIC_CHAN_SEQ;
  config.num_channels        = 1;
  config.init_pattern        = fir_compiler_0_chanpats[0];
  config.num_paths           = 1;
  config.data_width          = 28;
  config.data_fract_width    = 0;
  config.output_rounding_mode= XIP_FIR_CONVERGENT_EVEN;
  config.output_width        = 16;
  config.output_fract_width  = 0,
  config.config_method       = XIP_FIR_CONFIG_SINGLE;
  return config;
}

const xip_fir_v7_2_config fir_compiler_0_config = gen_fir_compiler_0_config();

