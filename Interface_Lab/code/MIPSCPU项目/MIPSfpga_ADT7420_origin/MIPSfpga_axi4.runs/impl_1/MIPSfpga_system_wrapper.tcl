proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000

start_step init_design
set rc [catch {
  create_msg_db init_design.pb
  debug::add_scope template.lib 1
  set_property design_mode GateLvl [current_fileset]
  set_property webtalk.parent_dir C:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.cache/wt [current_project]
  set_property parent.project_path C:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.xpr [current_project]
  set_property ip_repo_paths {
  c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.cache/ip
  C:/MIPSfpga_Peripheral_2017/ip_repo
} [current_project]
  set_property ip_output_repo c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.cache/ip [current_project]
  add_files -quiet C:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.runs/synth_1/MIPSfpga_system_wrapper.dcp
  read_xdc -prop_thru_buffers -ref MIPSfpga_system_axi_gpio_0_0 -cells U0 c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_gpio_0_0/MIPSfpga_system_axi_gpio_0_0_board.xdc
  set_property processing_order EARLY [get_files c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_gpio_0_0/MIPSfpga_system_axi_gpio_0_0_board.xdc]
  read_xdc -ref MIPSfpga_system_axi_gpio_0_0 -cells U0 c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_gpio_0_0/MIPSfpga_system_axi_gpio_0_0.xdc
  set_property processing_order EARLY [get_files c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_gpio_0_0/MIPSfpga_system_axi_gpio_0_0.xdc]
  read_xdc -prop_thru_buffers -ref MIPSfpga_system_clk_wiz_0_0 -cells inst c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_clk_wiz_0_0/MIPSfpga_system_clk_wiz_0_0_board.xdc
  set_property processing_order EARLY [get_files c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_clk_wiz_0_0/MIPSfpga_system_clk_wiz_0_0_board.xdc]
  read_xdc -ref MIPSfpga_system_clk_wiz_0_0 -cells inst c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_clk_wiz_0_0/MIPSfpga_system_clk_wiz_0_0.xdc
  set_property processing_order EARLY [get_files c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_clk_wiz_0_0/MIPSfpga_system_clk_wiz_0_0.xdc]
  read_xdc -prop_thru_buffers -ref MIPSfpga_system_axi_uart16550_0_0 -cells U0 c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_uart16550_0_0/MIPSfpga_system_axi_uart16550_0_0_board.xdc
  set_property processing_order EARLY [get_files c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_uart16550_0_0/MIPSfpga_system_axi_uart16550_0_0_board.xdc]
  read_xdc -ref MIPSfpga_system_axi_uart16550_0_0 -cells U0 c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_uart16550_0_0/MIPSfpga_system_axi_uart16550_0_0.xdc
  set_property processing_order EARLY [get_files c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_uart16550_0_0/MIPSfpga_system_axi_uart16550_0_0.xdc]
  read_xdc -prop_thru_buffers -ref MIPSfpga_system_axi_iic_0_0 c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_iic_0_0/MIPSfpga_system_axi_iic_0_0_board.xdc
  set_property processing_order EARLY [get_files c:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/sources_1/bd/MIPSfpga_system/ip/MIPSfpga_system_axi_iic_0_0/MIPSfpga_system_axi_iic_0_0_board.xdc]
  read_xdc C:/MIPSfpga_Peripheral_2017/MIPSfpga_ADT7420_origin/MIPSfpga_axi4.srcs/constrs_1/imports/MIPSfpga_Peripheral_2017/MIPSfpga_axi4.xdc
  link_design -top MIPSfpga_system_wrapper -part xc7a100tcsg324-1
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
}

start_step opt_design
set rc [catch {
  create_msg_db opt_design.pb
  catch {write_debug_probes -quiet -force debug_nets}
  opt_design 
  write_checkpoint -force MIPSfpga_system_wrapper_opt.dcp
  catch {report_drc -file MIPSfpga_system_wrapper_drc_opted.rpt}
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
}

start_step place_design
set rc [catch {
  create_msg_db place_design.pb
  catch {write_hwdef -file MIPSfpga_system_wrapper.hwdef}
  place_design 
  write_checkpoint -force MIPSfpga_system_wrapper_placed.dcp
  catch { report_io -file MIPSfpga_system_wrapper_io_placed.rpt }
  catch { report_utilization -file MIPSfpga_system_wrapper_utilization_placed.rpt -pb MIPSfpga_system_wrapper_utilization_placed.pb }
  catch { report_control_sets -verbose -file MIPSfpga_system_wrapper_control_sets_placed.rpt }
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
}

start_step route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force MIPSfpga_system_wrapper_routed.dcp
  catch { report_drc -file MIPSfpga_system_wrapper_drc_routed.rpt -pb MIPSfpga_system_wrapper_drc_routed.pb }
  catch { report_timing_summary -warn_on_violation -max_paths 10 -file MIPSfpga_system_wrapper_timing_summary_routed.rpt -rpx MIPSfpga_system_wrapper_timing_summary_routed.rpx }
  catch { report_power -file MIPSfpga_system_wrapper_power_routed.rpt -pb MIPSfpga_system_wrapper_power_summary_routed.pb }
  catch { report_route_status -file MIPSfpga_system_wrapper_route_status.rpt -pb MIPSfpga_system_wrapper_route_status.pb }
  catch { report_clock_utilization -file MIPSfpga_system_wrapper_clock_utilization_routed.rpt }
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
}

start_step write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  write_bitstream -force MIPSfpga_system_wrapper.bit 
  catch { write_sysdef -hwdef MIPSfpga_system_wrapper.hwdef -bitfile MIPSfpga_system_wrapper.bit -meminfo MIPSfpga_system_wrapper.mmi -ltxfile debug_nets.ltx -file MIPSfpga_system_wrapper.sysdef }
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
}

