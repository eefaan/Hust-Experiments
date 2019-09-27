@echo off
set xv_path=E:\\WIN\\program\\vivado2017.2\\Vivado\\2017.2\\bin
call %xv_path%/xelab  -wto b40f79190e2841328a242ccb88f27f69 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L secureip --snapshot washing_machine_sim_func_synth xil_defaultlib.washing_machine_sim xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
