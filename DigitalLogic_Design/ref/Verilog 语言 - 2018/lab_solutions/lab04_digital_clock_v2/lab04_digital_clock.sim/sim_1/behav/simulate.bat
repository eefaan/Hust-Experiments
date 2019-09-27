@echo off
set xv_path=C:\\Xilinx\\Vivado\\2015.2\\bin
call %xv_path%/xsim digital_clock_tb_behav -key {Behavioral:sim_1:Functional:digital_clock_tb} -tclbatch digital_clock_tb.tcl -view C:/Temp/lab04_digital_clock_v2/digital_clock_tb_behav.wcfg -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
