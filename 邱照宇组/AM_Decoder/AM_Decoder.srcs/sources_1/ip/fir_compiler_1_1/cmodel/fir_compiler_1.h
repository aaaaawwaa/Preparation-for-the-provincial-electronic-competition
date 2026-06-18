
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
// C Model configuration for the "fir_compiler_1" instance.
//
//------------------------------------------------------------------------------
//
// coefficients: 109,36,42,48,55,62,69,78,86,96,105,116,126,138,149,161,174,186,199,213,226,240,254,267,281,295,308,321,334,346,358,369,379,388,396,404,409,414,417,418,418,415,411,404,396,384,371,354,335,313,288,260,228,194,156,114,70,21,-31,-86,-145,-208,-274,-343,-417,-493,-573,-656,-742,-831,-923,-1018,-1115,-1215,-1316,-1420,-1525,-1631,-1738,-1846,-1954,-2062,-2170,-2277,-2383,-2488,-2590,-2690,-2788,-2882,-2972,-3058,-3139,-3215,-3286,-3350,-3408,-3459,-3502,-3537,-3563,-3580,-3588,-3586,-3574,-3551,-3516,-3470,-3412,-3342,-3260,-3164,-3055,-2933,-2797,-2647,-2484,-2306,-2114,-1908,-1687,-1453,-1204,-941,-664,-374,-69,248,578,921,1277,1644,2023,2412,2812,3222,3641,4069,4505,4948,5397,5852,6313,6777,7245,7715,8187,8660,9132,9604,10073,10540,11002,11460,11912,12357,12795,13224,13644,14054,14452,14838,15211,15570,15915,16245,16558,16855,17134,17395,17638,17861,18065,18249,18412,18554,18674,18773,18851,18906,18939,18951,18939,18906,18851,18773,18674,18554,18412,18249,18065,17861,17638,17395,17134,16855,16558,16245,15915,15570,15211,14838,14452,14054,13644,13224,12795,12357,11912,11460,11002,10540,10073,9604,9132,8660,8187,7715,7245,6777,6313,5852,5397,4948,4505,4069,3641,3222,2812,2412,2023,1644,1277,921,578,248,-69,-374,-664,-941,-1204,-1453,-1687,-1908,-2114,-2306,-2484,-2647,-2797,-2933,-3055,-3164,-3260,-3342,-3412,-3470,-3516,-3551,-3574,-3586,-3588,-3580,-3563,-3537,-3502,-3459,-3408,-3350,-3286,-3215,-3139,-3058,-2972,-2882,-2788,-2690,-2590,-2488,-2383,-2277,-2170,-2062,-1954,-1846,-1738,-1631,-1525,-1420,-1316,-1215,-1115,-1018,-923,-831,-742,-656,-573,-493,-417,-343,-274,-208,-145,-86,-31,21,70,114,156,194,228,260,288,313,335,354,371,384,396,404,411,415,418,418,417,414,409,404,396,388,379,369,358,346,334,321,308,295,281,267,254,240,226,213,199,186,174,161,149,138,126,116,105,96,86,78,69,62,55,48,42,36,109
// chanpats: 173
// name: fir_compiler_1
// filter_type: 0
// rate_change: 0
// interp_rate: 1
// decim_rate: 1
// zero_pack_factor: 1
// coeff_padding: 2
// num_coeffs: 363
// coeff_sets: 1
// reloadable: 0
// is_halfband: 0
// quantization: 0
// coeff_width: 16
// coeff_fract_width: 0
// chan_seq: 0
// num_channels: 1
// num_paths: 1
// data_width: 16
// data_fract_width: 0
// output_rounding_mode: 4
// output_width: 14
// output_fract_width: 0
// config_method: 0

const double fir_compiler_1_coefficients[363] = {109,36,42,48,55,62,69,78,86,96,105,116,126,138,149,161,174,186,199,213,226,240,254,267,281,295,308,321,334,346,358,369,379,388,396,404,409,414,417,418,418,415,411,404,396,384,371,354,335,313,288,260,228,194,156,114,70,21,-31,-86,-145,-208,-274,-343,-417,-493,-573,-656,-742,-831,-923,-1018,-1115,-1215,-1316,-1420,-1525,-1631,-1738,-1846,-1954,-2062,-2170,-2277,-2383,-2488,-2590,-2690,-2788,-2882,-2972,-3058,-3139,-3215,-3286,-3350,-3408,-3459,-3502,-3537,-3563,-3580,-3588,-3586,-3574,-3551,-3516,-3470,-3412,-3342,-3260,-3164,-3055,-2933,-2797,-2647,-2484,-2306,-2114,-1908,-1687,-1453,-1204,-941,-664,-374,-69,248,578,921,1277,1644,2023,2412,2812,3222,3641,4069,4505,4948,5397,5852,6313,6777,7245,7715,8187,8660,9132,9604,10073,10540,11002,11460,11912,12357,12795,13224,13644,14054,14452,14838,15211,15570,15915,16245,16558,16855,17134,17395,17638,17861,18065,18249,18412,18554,18674,18773,18851,18906,18939,18951,18939,18906,18851,18773,18674,18554,18412,18249,18065,17861,17638,17395,17134,16855,16558,16245,15915,15570,15211,14838,14452,14054,13644,13224,12795,12357,11912,11460,11002,10540,10073,9604,9132,8660,8187,7715,7245,6777,6313,5852,5397,4948,4505,4069,3641,3222,2812,2412,2023,1644,1277,921,578,248,-69,-374,-664,-941,-1204,-1453,-1687,-1908,-2114,-2306,-2484,-2647,-2797,-2933,-3055,-3164,-3260,-3342,-3412,-3470,-3516,-3551,-3574,-3586,-3588,-3580,-3563,-3537,-3502,-3459,-3408,-3350,-3286,-3215,-3139,-3058,-2972,-2882,-2788,-2690,-2590,-2488,-2383,-2277,-2170,-2062,-1954,-1846,-1738,-1631,-1525,-1420,-1316,-1215,-1115,-1018,-923,-831,-742,-656,-573,-493,-417,-343,-274,-208,-145,-86,-31,21,70,114,156,194,228,260,288,313,335,354,371,384,396,404,411,415,418,418,417,414,409,404,396,388,379,369,358,346,334,321,308,295,281,267,254,240,226,213,199,186,174,161,149,138,126,116,105,96,86,78,69,62,55,48,42,36,109};

const xip_fir_v7_2_pattern fir_compiler_1_chanpats[1] = {P_BASIC};

static xip_fir_v7_2_config gen_fir_compiler_1_config() {
  xip_fir_v7_2_config config;
  config.name                = "fir_compiler_1";
  config.filter_type         = 0;
  config.rate_change         = XIP_FIR_INTEGER_RATE;
  config.interp_rate         = 1;
  config.decim_rate          = 1;
  config.zero_pack_factor    = 1;
  config.coeff               = &fir_compiler_1_coefficients[0];
  config.coeff_padding       = 2;
  config.num_coeffs          = 363;
  config.coeff_sets          = 1;
  config.reloadable          = 0;
  config.is_halfband         = 0;
  config.quantization        = XIP_FIR_INTEGER_COEFF;
  config.coeff_width         = 16;
  config.coeff_fract_width   = 0;
  config.chan_seq            = XIP_FIR_BASIC_CHAN_SEQ;
  config.num_channels        = 1;
  config.init_pattern        = fir_compiler_1_chanpats[0];
  config.num_paths           = 1;
  config.data_width          = 16;
  config.data_fract_width    = 0;
  config.output_rounding_mode= XIP_FIR_CONVERGENT_EVEN;
  config.output_width        = 14;
  config.output_fract_width  = 0,
  config.config_method       = XIP_FIR_CONFIG_SINGLE;
  return config;
}

const xip_fir_v7_2_config fir_compiler_1_config = gen_fir_compiler_1_config();

