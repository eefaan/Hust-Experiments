# Switches
#Bank = 34, Pin name = IO_L21P_T3_DQS_34,					Sch name = SW0
set_property PACKAGE_PIN U9 [get_ports X]					
	set_property IOSTANDARD LVCMOS33 [get_ports X]

# LEDs
#Bank = 34, Pin name = IO_L24N_T3_34,						Sch name = LED0
set_property PACKAGE_PIN T8 [get_ports {Z}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Z}]
#Bank = 34, Pin name = IO_L21N_T3_DQS_34,					Sch name = LED1
set_property PACKAGE_PIN V9 [get_ports {Q1}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Q1}]
#Bank = 34, Pin name = IO_L24P_T3_34,						Sch name = LED2
set_property PACKAGE_PIN R8 [get_ports {Q2}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Q2}]
#Bank = 34, Pin name = IO_L23N_T3_34,						Sch name = LED3
set_property PACKAGE_PIN T6 [get_ports {Q3}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Q3}]
#Bank = 34, Pin name = IO_L12P_T1_MRCC_34,					Sch name = LED4
set_property PACKAGE_PIN T5 [get_ports {Q4}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Q4}]

	
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets X_IBUF] 