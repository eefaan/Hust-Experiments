# Switches
#Bank = 34, Pin name = IO_L21P_T3_DQS_34,					Sch name = SW0
set_property PACKAGE_PIN U9 [get_ports {clk_x}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {clk_x}]
#Bank = 34, Pin name = IO_25_34,							Sch name = SW1
set_property PACKAGE_PIN U8 [get_ports {rst}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {rst}]
#Bank = 34, Pin name = IO_L23P_T3_34,						Sch name = SW2
set_property PACKAGE_PIN R7 [get_ports {num_x}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {num_x}]

# LEDs
#Bank = 34, Pin name = IO_L24N_T3_34,						Sch name = LED0
set_property PACKAGE_PIN T8 [get_ports {sign}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {sign}]

#Bank = 34, Pin name = IO_L7P_T1_34,						Sch name = LED13
set_property PACKAGE_PIN U1 [get_ports {state[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {state[0]}]
#Bank = 34, Pin name = IO_L15N_T2_DQS_34,					Sch name = LED14
set_property PACKAGE_PIN R2 [get_ports {state[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {state[1]}]
#Bank = 34, Pin name = IO_L15P_T2_DQS_34,					Sch name = LED15
set_property PACKAGE_PIN P2 [get_ports {state[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {state[2]}]
	
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets clk_x_IBUF]
