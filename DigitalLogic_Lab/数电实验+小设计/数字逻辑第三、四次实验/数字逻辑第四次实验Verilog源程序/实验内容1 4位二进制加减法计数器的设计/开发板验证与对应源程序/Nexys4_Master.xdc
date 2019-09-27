# Switches
#Bank = 34, Pin name = IO_L21P_T3_DQS_34,					Sch name = SW0
set_property PACKAGE_PIN U9 [get_ports {clk_count}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {clk_count}]
#Bank = 34, Pin name = IO_25_34,							Sch name = SW1
set_property PACKAGE_PIN U8 [get_ports {rst}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {rst}]
#Bank = 34, Pin name = IO_L23P_T3_34,						Sch name = SW2
set_property PACKAGE_PIN R7 [get_ports {en}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {en}]

# LEDs
#Bank = 34, Pin name = IO_L24N_T3_34,						Sch name = LED0
set_property PACKAGE_PIN T8 [get_ports {dout[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {dout[0]}]
#Bank = 34, Pin name = IO_L21N_T3_DQS_34,					Sch name = LED1
set_property PACKAGE_PIN V9 [get_ports {dout[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {dout[1]}]
#Bank = 34, Pin name = IO_L24P_T3_34,						Sch name = LED2
set_property PACKAGE_PIN R8 [get_ports {dout[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {dout[2]}]
#Bank = 34, Pin name = IO_L23N_T3_34,						Sch name = LED3
set_property PACKAGE_PIN T6 [get_ports {dout[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {dout[3]}]
#Bank = 34, Pin name = IO_L12P_T1_MRCC_34,					Sch name = LED4
set_property PACKAGE_PIN T5 [get_ports {cout}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {cout}]

set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets clk_count_IBUF]
 