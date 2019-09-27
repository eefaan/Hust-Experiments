@echo off
set xv_path=E:\\WIN\\program\\vivado2017.2\\Vivado\\2017.2\\bin
call %xv_path%/xelab  -wto 1bcd33108d3041ada34b315c52d4b519 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot lab4_3_sim_behav xil_defaultlib.lab4_3_sim xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
