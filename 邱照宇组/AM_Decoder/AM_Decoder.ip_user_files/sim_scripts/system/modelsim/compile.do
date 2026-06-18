vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xilinx_vip
vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_vip_v1_1_4
vlib modelsim_lib/msim/processing_system7_vip_v1_0_6
vlib modelsim_lib/msim/xbip_utils_v3_0_9
vlib modelsim_lib/msim/xbip_pipe_v3_0_5
vlib modelsim_lib/msim/xbip_bram18k_v3_0_5
vlib modelsim_lib/msim/mult_gen_v12_0_14
vlib modelsim_lib/msim/axi_utils_v2_0_5
vlib modelsim_lib/msim/xbip_dsp48_wrapper_v3_0_4
vlib modelsim_lib/msim/xbip_dsp48_addsub_v3_0_5
vlib modelsim_lib/msim/xbip_dsp48_multadd_v3_0_5
vlib modelsim_lib/msim/dds_compiler_v6_0_17
vlib modelsim_lib/msim/xlconstant_v1_1_5
vlib modelsim_lib/msim/fir_compiler_v7_2_11
vlib modelsim_lib/msim/c_reg_fd_v12_0_5
vlib modelsim_lib/msim/xbip_addsub_v3_0_5
vlib modelsim_lib/msim/c_addsub_v12_0_12
vlib modelsim_lib/msim/cordic_v6_0_14

vmap xilinx_vip modelsim_lib/msim/xilinx_vip
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap xpm modelsim_lib/msim/xpm
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_4 modelsim_lib/msim/axi_vip_v1_1_4
vmap processing_system7_vip_v1_0_6 modelsim_lib/msim/processing_system7_vip_v1_0_6
vmap xbip_utils_v3_0_9 modelsim_lib/msim/xbip_utils_v3_0_9
vmap xbip_pipe_v3_0_5 modelsim_lib/msim/xbip_pipe_v3_0_5
vmap xbip_bram18k_v3_0_5 modelsim_lib/msim/xbip_bram18k_v3_0_5
vmap mult_gen_v12_0_14 modelsim_lib/msim/mult_gen_v12_0_14
vmap axi_utils_v2_0_5 modelsim_lib/msim/axi_utils_v2_0_5
vmap xbip_dsp48_wrapper_v3_0_4 modelsim_lib/msim/xbip_dsp48_wrapper_v3_0_4
vmap xbip_dsp48_addsub_v3_0_5 modelsim_lib/msim/xbip_dsp48_addsub_v3_0_5
vmap xbip_dsp48_multadd_v3_0_5 modelsim_lib/msim/xbip_dsp48_multadd_v3_0_5
vmap dds_compiler_v6_0_17 modelsim_lib/msim/dds_compiler_v6_0_17
vmap xlconstant_v1_1_5 modelsim_lib/msim/xlconstant_v1_1_5
vmap fir_compiler_v7_2_11 modelsim_lib/msim/fir_compiler_v7_2_11
vmap c_reg_fd_v12_0_5 modelsim_lib/msim/c_reg_fd_v12_0_5
vmap xbip_addsub_v3_0_5 modelsim_lib/msim/xbip_addsub_v3_0_5
vmap c_addsub_v12_0_12 modelsim_lib/msim/c_addsub_v12_0_12
vmap cordic_v6_0_14 modelsim_lib/msim/cordic_v6_0_14

vlog -work xilinx_vip -64 -incr -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L xilinx_vip "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_if.sv" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/clk_vip_if.sv" \
"D:/xlinx/Vivado/2018.3/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xil_defaultlib -64 -incr -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L xilinx_vip "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"D:/xlinx/Vivado/2018.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"D:/xlinx/Vivado/2018.3/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -64 -93 \
"D:/xlinx/Vivado/2018.3/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0 -64 -incr "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_4 -64 -incr -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L xilinx_vip "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/98af/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_6 -64 -incr -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L xilinx_vip "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_processing_system7_0_0/sim/system_processing_system7_0_0.v" \
"../../../bd/system/sim/system.v" \
"../../../bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0.v" \
"../../../bd/system/ip/system_ila_0_0/sim/system_ila_0_0.v" \

vcom -work xbip_utils_v3_0_9 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/0da8/hdl/xbip_utils_v3_0_vh_rfs.vhd" \

vcom -work xbip_pipe_v3_0_5 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/442e/hdl/xbip_pipe_v3_0_vh_rfs.vhd" \

vcom -work xbip_bram18k_v3_0_5 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c08f/hdl/xbip_bram18k_v3_0_vh_rfs.vhd" \

vcom -work mult_gen_v12_0_14 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/6bb5/hdl/mult_gen_v12_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_mult_gen_0_0/sim/system_mult_gen_0_0.vhd" \
"../../../bd/system/ip/system_mult_gen_0_1/sim/system_mult_gen_0_1.vhd" \

vcom -work axi_utils_v2_0_5 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec8e/hdl/axi_utils_v2_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_wrapper_v3_0_4 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/cdbf/hdl/xbip_dsp48_wrapper_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_addsub_v3_0_5 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/a04b/hdl/xbip_dsp48_addsub_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_multadd_v3_0_5 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/b226/hdl/xbip_dsp48_multadd_v3_0_vh_rfs.vhd" \

vcom -work dds_compiler_v6_0_17 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/018d/hdl/dds_compiler_v6_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_dds_compiler_0_0/sim/system_dds_compiler_0_0.vhd" \
"../../../bd/system/ip/system_dds_compiler_0_2/sim/system_dds_compiler_0_2.vhd" \

vlog -work xlconstant_v1_1_5 -64 -incr "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/4649/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_xlconstant_0_0/sim/system_xlconstant_0_0.v" \
"../../../bd/system/ip/system_xlconstant_0_1/sim/system_xlconstant_0_1.v" \
"../../../bd/system/ip/system_Valid_logic_0_0/sim/system_Valid_logic_0_0.v" \
"../../../bd/system/ip/system_Valid_logic_0_1/sim/system_Valid_logic_0_1.v" \

vcom -work fir_compiler_v7_2_11 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/3697/hdl/fir_compiler_v7_2_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_fir_compiler_0_0/sim/system_fir_compiler_0_0.vhd" \
"../../../bd/system/ip/system_fir_compiler_0_2/sim/system_fir_compiler_0_2.vhd" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_xlconstant_0_2/sim/system_xlconstant_0_2.v" \
"../../../bd/system/ip/system_Valid_logic_1_0/sim/system_Valid_logic_1_0.v" \
"../../../bd/system/ip/system_Valid_logic_1_1/sim/system_Valid_logic_1_1.v" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_mult_gen_2_0/sim/system_mult_gen_2_0.vhd" \
"../../../bd/system/ip/system_mult_gen_2_1/sim/system_mult_gen_2_1.vhd" \

vcom -work c_reg_fd_v12_0_5 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/cbdd/hdl/c_reg_fd_v12_0_vh_rfs.vhd" \

vcom -work xbip_addsub_v3_0_5 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/87fb/hdl/xbip_addsub_v3_0_vh_rfs.vhd" \

vcom -work c_addsub_v12_0_12 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/6b5f/hdl/c_addsub_v12_0_vh_rfs.vhd" \

vcom -work cordic_v6_0_14 -64 -93 \
"../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7bb6/hdl/cordic_v6_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_cordic_0_0/sim/system_cordic_0_0.vhd" \
"../../../bd/system/ip/system_c_addsub_0_0/sim/system_c_addsub_0_0.vhd" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/85a3" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/7d3c/hdl/verilog" "+incdir+../../../../AM_Decoder.srcs/sources_1/bd/system/ipshared/c45e/hdl/verilog" "+incdir+D:/xlinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_xlconstant_2_0/sim/system_xlconstant_2_0.v" \
"../../../bd/system/ip/system_Valid_logic_3_0/sim/system_Valid_logic_3_0.v" \

vlog -work xil_defaultlib \
"glbl.v"

