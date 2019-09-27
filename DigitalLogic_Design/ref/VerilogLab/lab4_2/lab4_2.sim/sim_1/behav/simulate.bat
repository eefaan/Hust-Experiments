@echo off
set xv_path=E:\\WIN\\program\\vivado2017.2\\Vivado\\2017.2\\bin
call %xv_path%/xsim lab4_2_sim_behav -key {Behavioral:sim_1:Functional:lab4_2_sim} -tclbatch lab4_2_sim.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
