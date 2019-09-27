@echo off
set xv_path=C:\\Xilinx\\Vivado\\2015.2\\bin
call %xv_path%/xsim lab_4_5_top_tb_behav -key {Behavioral:sim_1:Functional:lab_4_5_top_tb} -tclbatch lab_4_5_top_tb.tcl -view C:/Temp/lab_4_5/lab_4_5_FSM_tb_behav.wcfg -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
