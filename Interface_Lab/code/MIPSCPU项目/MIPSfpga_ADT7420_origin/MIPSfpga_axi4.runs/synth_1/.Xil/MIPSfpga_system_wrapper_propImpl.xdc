set_property SRC_FILE_INFO {cfile:c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_clk_wiz_0_0/MIPSfpga_system_clk_wiz_0_0.xdc rfile:../../../MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_clk_wiz_0_0/MIPSfpga_system_clk_wiz_0_0.xdc id:1 order:EARLY scoped_inst:MIPSfpga_system_i/clk_wiz_0/inst} [current_design]
set_property SRC_FILE_INFO {cfile:C:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/constrs_1/imports/MIPSfpga_Peripheral_2017/MIPSfpga_axi4.xdc rfile:../../../MIPSfpga_axi4.srcs/constrs_1/imports/MIPSfpga_Peripheral_2017/MIPSfpga_axi4.xdc id:2} [current_design]
set_property src_info {type:SCOPED_XDC file:1 line:56 export:INPUT save:INPUT read:READ} [current_design]
set_input_jitter [get_clocks -of_objects [get_ports clk_in1]] 0.1
set_property src_info {type:XDC file:2 line:110 export:INPUT save:INPUT read:READ} [current_design]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets JB4_IBUF]
