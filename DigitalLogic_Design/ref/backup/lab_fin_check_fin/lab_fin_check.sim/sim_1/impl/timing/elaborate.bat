@echo off
set xv_path=E:\\WIN\\program\\vivado2017.2\\Vivado\\2017.2\\bin
call %xv_path%/xelab  -wto b40f79190e2841328a242ccb88f27f69 -m64 --debug typical --relax --mt 2 --maxdelay -L xil_defaultlib -L simprims_ver -L secureip --snapshot washing_machine_sim_time_impl -transport_int_delays -pulse_r 0 -pulse_int_r 0 -pulse_e 0 -pulse_int_e 0 xil_defaultlib.washing_machine_sim xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
