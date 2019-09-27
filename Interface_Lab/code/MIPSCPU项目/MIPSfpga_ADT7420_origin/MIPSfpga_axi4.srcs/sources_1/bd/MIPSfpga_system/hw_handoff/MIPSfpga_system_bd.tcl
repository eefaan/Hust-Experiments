
################################################################
# This is a generated script based on design: MIPSfpga_system
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2015.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   puts "ERROR: This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source MIPSfpga_system_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7a100tcsg324-1

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
   puts "ERROR: Please open or create a project!"
   return 1
}



# CHANGE DESIGN NAME HERE
set design_name MIPSfpga_system

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "ERROR: Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      puts "INFO: Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   puts "INFO: Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   puts "INFO: Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   puts "INFO: Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

puts "INFO: Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   puts $errMsg
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set TEMP_SENSOR [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:iic_rtl:1.0 TEMP_SENSOR ]

  # Create ports
  set CLK100MHZ [ create_bd_port -dir I CLK100MHZ ]
  set CPU_RESETN [ create_bd_port -dir I CPU_RESETN ]
  set JB1 [ create_bd_port -dir I JB1 ]
  set JB2 [ create_bd_port -dir I JB2 ]
  set JB3 [ create_bd_port -dir O JB3 ]
  set JB4 [ create_bd_port -dir I JB4 ]
  set JB7 [ create_bd_port -dir I JB7 ]
  set JB8 [ create_bd_port -dir I JB8 ]
  set LED [ create_bd_port -dir O -from 15 -to 0 LED ]
  set PWMs [ create_bd_port -dir O -from 1 -to 0 PWMs ]
  set UART_RXD_OUT [ create_bd_port -dir O UART_RXD_OUT ]
  set UART_TXD_IN [ create_bd_port -dir I UART_TXD_IN ]
  set sw [ create_bd_port -dir I -from 15 -to 0 sw ]

  # Create instance: MIPS_MicroAptiv_UP_0, and set properties
  set MIPS_MicroAptiv_UP_0 [ create_bd_cell -type ip -vlnv imgtec.org:user:MIPS_MicroAptiv_UP:1.3.1 MIPS_MicroAptiv_UP_0 ]

  # Create instance: PWM_w_Int_0, and set properties
  set PWM_w_Int_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:PWM_w_Int:1.0 PWM_w_Int_0 ]

  # Create instance: ahblite_axi_bridge_0, and set properties
  set ahblite_axi_bridge_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ahblite_axi_bridge:3.0 ahblite_axi_bridge_0 ]
  set_property -dict [ list CONFIG.C_AHB_AXI_TIMEOUT {256}  ] $ahblite_axi_bridge_0

  # Create instance: axi_bram_ctrl_0, and set properties
  set axi_bram_ctrl_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_bram_ctrl:4.0 axi_bram_ctrl_0 ]
  set_property -dict [ list CONFIG.SINGLE_PORT_BRAM {1}  ] $axi_bram_ctrl_0

  # Create instance: axi_bram_ctrl_1, and set properties
  set axi_bram_ctrl_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_bram_ctrl:4.0 axi_bram_ctrl_1 ]
  set_property -dict [ list CONFIG.SINGLE_PORT_BRAM {1}  ] $axi_bram_ctrl_1

  # Create instance: axi_gpio_0, and set properties
  set axi_gpio_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_0 ]
  set_property -dict [ list CONFIG.C_ALL_INPUTS_2 {1} CONFIG.C_ALL_OUTPUTS {1} CONFIG.C_GPIO2_WIDTH {16} CONFIG.C_GPIO_WIDTH {16} CONFIG.C_IS_DUAL {1}  ] $axi_gpio_0

  # Create instance: axi_iic_0, and set properties
  set axi_iic_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_iic:2.0 axi_iic_0 ]

  # Create instance: axi_interconnect_0, and set properties
  set axi_interconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_interconnect_0 ]
  set_property -dict [ list CONFIG.NUM_MI {6}  ] $axi_interconnect_0

  # Create instance: axi_uart16550_0, and set properties
  set axi_uart16550_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uart16550:2.0 axi_uart16550_0 ]

  # Create instance: blk_mem_gen_0, and set properties
  set blk_mem_gen_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:blk_mem_gen:8.2 blk_mem_gen_0 ]
  set_property -dict [ list CONFIG.Byte_Size {9} CONFIG.Coe_File {../../../../../../../ram_init.coe} CONFIG.Enable_32bit_Address {false} CONFIG.Load_Init_File {true} CONFIG.Register_PortA_Output_of_Memory_Primitives {false} CONFIG.Use_Byte_Write_Enable {false} CONFIG.Use_RSTA_Pin {false} CONFIG.use_bram_block {Stand_Alone}  ] $blk_mem_gen_0

  # Create instance: blk_mem_gen_1, and set properties
  set blk_mem_gen_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:blk_mem_gen:8.2 blk_mem_gen_1 ]
  set_property -dict [ list CONFIG.Byte_Size {9} CONFIG.Enable_32bit_Address {false} CONFIG.Register_PortA_Output_of_Memory_Primitives {false} CONFIG.Use_Byte_Write_Enable {false} CONFIG.Use_RSTA_Pin {false} CONFIG.Write_Depth_A {65536} CONFIG.use_bram_block {Stand_Alone}  ] $blk_mem_gen_1

  # Create instance: clk_wiz_0, and set properties
  set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:5.1 clk_wiz_0 ]
  set_property -dict [ list CONFIG.CLKOUT1_DRIVES {BUFG} CONFIG.CLKOUT1_JITTER {167.017} CONFIG.CLKOUT1_PHASE_ERROR {114.212} CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {50.000} CONFIG.CLKOUT2_DRIVES {BUFG} CONFIG.CLKOUT3_DRIVES {BUFG} CONFIG.CLKOUT4_DRIVES {BUFG} CONFIG.CLKOUT5_DRIVES {BUFG} CONFIG.CLKOUT6_DRIVES {BUFG} CONFIG.CLKOUT7_DRIVES {BUFG} CONFIG.MMCM_CLKFBOUT_MULT_F {8} CONFIG.MMCM_CLKOUT0_DIVIDE_F {16} CONFIG.MMCM_COMPENSATION {ZHOLD} CONFIG.MMCM_DIVCLK_DIVIDE {1} CONFIG.PRIMITIVE {PLL} CONFIG.USE_LOCKED {false} CONFIG.USE_RESET {false}  ] $clk_wiz_0

  # Create instance: util_ds_buf_0, and set properties
  set util_ds_buf_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_ds_buf:2.1 util_ds_buf_0 ]
  set_property -dict [ list CONFIG.C_BUF_TYPE {BUFG}  ] $util_ds_buf_0

  # Create instance: util_vector_logic_0, and set properties
  set util_vector_logic_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_0 ]
  set_property -dict [ list CONFIG.C_OPERATION {not} CONFIG.C_SIZE {1}  ] $util_vector_logic_0

  # Create instance: util_vector_logic_1, and set properties
  set util_vector_logic_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_1 ]
  set_property -dict [ list CONFIG.C_OPERATION {not} CONFIG.C_SIZE {1}  ] $util_vector_logic_1

  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property -dict [ list CONFIG.NUM_PORTS {8}  ] $xlconcat_0

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]

  # Create instance: xlconstant_1, and set properties
  set xlconstant_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_1 ]
  set_property -dict [ list CONFIG.CONST_VAL {0} CONFIG.CONST_WIDTH {1}  ] $xlconstant_1

  # Create instance: xlconstant_2, and set properties
  set xlconstant_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_2 ]
  set_property -dict [ list CONFIG.CONST_VAL {0}  ] $xlconstant_2

  # Create instance: xlconstant_3, and set properties
  set xlconstant_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_3 ]
  set_property -dict [ list CONFIG.CONST_VAL {0}  ] $xlconstant_3

  # Create interface connections
  connect_bd_intf_net -intf_net MIPS_MicroAptiv_UP_0_ahblite [get_bd_intf_pins MIPS_MicroAptiv_UP_0/ahblite] [get_bd_intf_pins ahblite_axi_bridge_0/AHB_INTERFACE]
  connect_bd_intf_net -intf_net ahblite_axi_bridge_0_M_AXI [get_bd_intf_pins ahblite_axi_bridge_0/M_AXI] [get_bd_intf_pins axi_interconnect_0/S00_AXI]
  connect_bd_intf_net -intf_net axi_bram_ctrl_0_BRAM_PORTA [get_bd_intf_pins axi_bram_ctrl_0/BRAM_PORTA] [get_bd_intf_pins blk_mem_gen_0/BRAM_PORTA]
  connect_bd_intf_net -intf_net axi_bram_ctrl_1_BRAM_PORTA [get_bd_intf_pins axi_bram_ctrl_1/BRAM_PORTA] [get_bd_intf_pins blk_mem_gen_1/BRAM_PORTA]
  connect_bd_intf_net -intf_net axi_iic_0_IIC [get_bd_intf_ports TEMP_SENSOR] [get_bd_intf_pins axi_iic_0/IIC]
  connect_bd_intf_net -intf_net axi_interconnect_0_M00_AXI [get_bd_intf_pins axi_gpio_0/S_AXI] [get_bd_intf_pins axi_interconnect_0/M00_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M01_AXI [get_bd_intf_pins axi_bram_ctrl_0/S_AXI] [get_bd_intf_pins axi_interconnect_0/M01_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M02_AXI [get_bd_intf_pins axi_interconnect_0/M02_AXI] [get_bd_intf_pins axi_uart16550_0/S_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M03_AXI [get_bd_intf_pins axi_bram_ctrl_1/S_AXI] [get_bd_intf_pins axi_interconnect_0/M03_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M04_AXI [get_bd_intf_pins PWM_w_Int_0/S00_AXI] [get_bd_intf_pins axi_interconnect_0/M04_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M05_AXI [get_bd_intf_pins axi_iic_0/S_AXI] [get_bd_intf_pins axi_interconnect_0/M05_AXI]

  # Create port connections
  connect_bd_net -net EJ_TCK_1 [get_bd_ports JB4] [get_bd_pins util_ds_buf_0/BUFG_I]
  connect_bd_net -net EJ_TDI_1 [get_bd_ports JB2] [get_bd_pins MIPS_MicroAptiv_UP_0/EJ_TDI]
  connect_bd_net -net EJ_TMS_1 [get_bd_ports JB1] [get_bd_pins MIPS_MicroAptiv_UP_0/EJ_TMS]
  connect_bd_net -net EJ_TRST_N_1 [get_bd_ports JB7] [get_bd_pins MIPS_MicroAptiv_UP_0/EJ_TRST_N]
  connect_bd_net -net MIPS_MicroAptiv_UP_0_EJ_TDO [get_bd_ports JB3] [get_bd_pins MIPS_MicroAptiv_UP_0/EJ_TDO]
  connect_bd_net -net MIPS_MicroAptiv_UP_0_HCLK [get_bd_pins MIPS_MicroAptiv_UP_0/HCLK] [get_bd_pins PWM_w_Int_0/s00_axi_aclk] [get_bd_pins ahblite_axi_bridge_0/s_ahb_hclk] [get_bd_pins axi_bram_ctrl_0/s_axi_aclk] [get_bd_pins axi_bram_ctrl_1/s_axi_aclk] [get_bd_pins axi_gpio_0/s_axi_aclk] [get_bd_pins axi_iic_0/s_axi_aclk] [get_bd_pins axi_interconnect_0/ACLK] [get_bd_pins axi_interconnect_0/M00_ACLK] [get_bd_pins axi_interconnect_0/M01_ACLK] [get_bd_pins axi_interconnect_0/M02_ACLK] [get_bd_pins axi_interconnect_0/M03_ACLK] [get_bd_pins axi_interconnect_0/M04_ACLK] [get_bd_pins axi_interconnect_0/M05_ACLK] [get_bd_pins axi_interconnect_0/S00_ACLK] [get_bd_pins axi_uart16550_0/s_axi_aclk]
  connect_bd_net -net MIPS_MicroAptiv_UP_0_HRESETn [get_bd_pins MIPS_MicroAptiv_UP_0/HRESETn] [get_bd_pins PWM_w_Int_0/s00_axi_aresetn] [get_bd_pins ahblite_axi_bridge_0/s_ahb_hresetn] [get_bd_pins axi_bram_ctrl_0/s_axi_aresetn] [get_bd_pins axi_bram_ctrl_1/s_axi_aresetn] [get_bd_pins axi_gpio_0/s_axi_aresetn] [get_bd_pins axi_iic_0/s_axi_aresetn] [get_bd_pins axi_interconnect_0/ARESETN] [get_bd_pins axi_interconnect_0/M00_ARESETN] [get_bd_pins axi_interconnect_0/M01_ARESETN] [get_bd_pins axi_interconnect_0/M02_ARESETN] [get_bd_pins axi_interconnect_0/M03_ARESETN] [get_bd_pins axi_interconnect_0/M04_ARESETN] [get_bd_pins axi_interconnect_0/M05_ARESETN] [get_bd_pins axi_interconnect_0/S00_ARESETN] [get_bd_pins axi_uart16550_0/s_axi_aresetn]
  connect_bd_net -net PWM_w_Int_0_Interrupt_out [get_bd_pins PWM_w_Int_0/Interrupt_out] [get_bd_pins xlconcat_0/In4]
  connect_bd_net -net PWM_w_Int_0_LEDs [get_bd_ports PWMs] [get_bd_pins PWM_w_Int_0/LEDs]
  connect_bd_net -net SI_ClkIn_1 [get_bd_ports CLK100MHZ] [get_bd_pins clk_wiz_0/clk_in1]
  connect_bd_net -net SI_ColdReset_1 [get_bd_ports JB8] [get_bd_pins util_vector_logic_0/Op1]
  connect_bd_net -net SI_Reset_1 [get_bd_ports CPU_RESETN] [get_bd_pins util_vector_logic_1/Op1]
  connect_bd_net -net ahblite_axi_bridge_0_s_ahb_hready_out [get_bd_pins MIPS_MicroAptiv_UP_0/HREADY] [get_bd_pins ahblite_axi_bridge_0/s_ahb_hready_in] [get_bd_pins ahblite_axi_bridge_0/s_ahb_hready_out]
  connect_bd_net -net axi_gpio_0_gpio_io_o [get_bd_ports LED] [get_bd_pins axi_gpio_0/gpio_io_o]
  connect_bd_net -net axi_iic_0_iic2intc_irpt [get_bd_pins axi_iic_0/iic2intc_irpt] [get_bd_pins xlconcat_0/In3]
  connect_bd_net -net axi_uart16550_0_ip2intc_irpt [get_bd_pins axi_uart16550_0/ip2intc_irpt] [get_bd_pins xlconcat_0/In5]
  connect_bd_net -net axi_uart16550_0_sout [get_bd_ports UART_RXD_OUT] [get_bd_pins axi_uart16550_0/sout]
  connect_bd_net -net clk_wiz_0_clk_out1 [get_bd_pins MIPS_MicroAptiv_UP_0/SI_ClkIn] [get_bd_pins clk_wiz_0/clk_out1]
  connect_bd_net -net gpio2_io_i_1 [get_bd_ports sw] [get_bd_pins axi_gpio_0/gpio2_io_i]
  connect_bd_net -net sin_1 [get_bd_ports UART_TXD_IN] [get_bd_pins axi_uart16550_0/sin]
  connect_bd_net -net util_ds_buf_0_BUFG_O [get_bd_pins MIPS_MicroAptiv_UP_0/EJ_TCK] [get_bd_pins util_ds_buf_0/BUFG_O]
  connect_bd_net -net util_vector_logic_0_Res [get_bd_pins MIPS_MicroAptiv_UP_0/SI_ColdReset] [get_bd_pins util_vector_logic_0/Res]
  connect_bd_net -net util_vector_logic_1_Res [get_bd_pins MIPS_MicroAptiv_UP_0/SI_Reset] [get_bd_pins util_vector_logic_1/Res]
  connect_bd_net -net xlconcat_0_dout [get_bd_pins MIPS_MicroAptiv_UP_0/SI_Int] [get_bd_pins xlconcat_0/dout]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins ahblite_axi_bridge_0/s_ahb_hsel] [get_bd_pins xlconstant_0/dout]
  connect_bd_net -net xlconstant_1_dout [get_bd_pins xlconcat_0/In0] [get_bd_pins xlconcat_0/In1] [get_bd_pins xlconcat_0/In2] [get_bd_pins xlconcat_0/In6] [get_bd_pins xlconcat_0/In7] [get_bd_pins xlconstant_1/dout]
  connect_bd_net -net xlconstant_2_dout [get_bd_pins MIPS_MicroAptiv_UP_0/EJ_DINT] [get_bd_pins xlconstant_2/dout]
  connect_bd_net -net xlconstant_3_dout [get_bd_pins axi_uart16550_0/freeze] [get_bd_pins xlconstant_3/dout]

  # Create address segments
  create_bd_addr_seg -range 0x10000 -offset 0x10C00000 [get_bd_addr_spaces MIPS_MicroAptiv_UP_0/ahblite] [get_bd_addr_segs PWM_w_Int_0/S00_AXI/S00_AXI_reg] SEG_PWM_w_Int_0_S00_AXI_reg
  create_bd_addr_seg -range 0x2000 -offset 0x1FC00000 [get_bd_addr_spaces MIPS_MicroAptiv_UP_0/ahblite] [get_bd_addr_segs axi_bram_ctrl_0/S_AXI/Mem0] SEG_axi_bram_ctrl_0_Mem0
  create_bd_addr_seg -range 0x10000 -offset 0x0 [get_bd_addr_spaces MIPS_MicroAptiv_UP_0/ahblite] [get_bd_addr_segs axi_bram_ctrl_1/S_AXI/Mem0] SEG_axi_bram_ctrl_1_Mem0
  create_bd_addr_seg -range 0x10000 -offset 0x10600000 [get_bd_addr_spaces MIPS_MicroAptiv_UP_0/ahblite] [get_bd_addr_segs axi_gpio_0/S_AXI/Reg] SEG_axi_gpio_0_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x10A00000 [get_bd_addr_spaces MIPS_MicroAptiv_UP_0/ahblite] [get_bd_addr_segs axi_iic_0/S_AXI/Reg] SEG_axi_iic_0_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x10400000 [get_bd_addr_spaces MIPS_MicroAptiv_UP_0/ahblite] [get_bd_addr_segs axi_uart16550_0/S_AXI/Reg] SEG_axi_uart16550_0_Reg
  

  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


