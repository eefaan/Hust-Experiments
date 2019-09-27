//Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2015.2 (win64) Build 1266856 Fri Jun 26 16:35:25 MDT 2015
//Date        : Tue Jun 11 19:35:16 2019
//Host        : YIFANLIUE31D running 64-bit major release  (build 9200)
//Command     : generate_target MIPSfpga_system_wrapper.bd
//Design      : MIPSfpga_system_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module MIPSfpga_system_wrapper
   (CLK100MHZ,
    CPU_RESETN,
    JB1,
    JB2,
    JB3,
    JB4,
    JB7,
    JB8,
    LED,
    PWMs,
    UART_RXD_OUT,
    UART_TXD_IN,
    sw,
    temp_sensor_scl_io,
    temp_sensor_sda_io);
  input CLK100MHZ;
  input CPU_RESETN;
  input JB1;
  input JB2;
  output JB3;
  input JB4;
  input JB7;
  input JB8;
  output [15:0]LED;
  output [1:0]PWMs;
  output UART_RXD_OUT;
  input UART_TXD_IN;
  input [15:0]sw;
  inout temp_sensor_scl_io;
  inout temp_sensor_sda_io;

  wire CLK100MHZ;
  wire CPU_RESETN;
  wire JB1;
  wire JB2;
  wire JB3;
  wire JB4;
  wire JB7;
  wire JB8;
  wire [15:0]LED;
  wire [1:0]PWMs;
  wire UART_RXD_OUT;
  wire UART_TXD_IN;
  wire [15:0]sw;
  wire temp_sensor_scl_i;
  wire temp_sensor_scl_io;
  wire temp_sensor_scl_o;
  wire temp_sensor_scl_t;
  wire temp_sensor_sda_i;
  wire temp_sensor_sda_io;
  wire temp_sensor_sda_o;
  wire temp_sensor_sda_t;

  MIPSfpga_system MIPSfpga_system_i
       (.CLK100MHZ(CLK100MHZ),
        .CPU_RESETN(CPU_RESETN),
        .JB1(JB1),
        .JB2(JB2),
        .JB3(JB3),
        .JB4(JB4),
        .JB7(JB7),
        .JB8(JB8),
        .LED(LED),
        .PWMs(PWMs),
        .TEMP_SENSOR_scl_i(temp_sensor_scl_i),
        .TEMP_SENSOR_scl_o(temp_sensor_scl_o),
        .TEMP_SENSOR_scl_t(temp_sensor_scl_t),
        .TEMP_SENSOR_sda_i(temp_sensor_sda_i),
        .TEMP_SENSOR_sda_o(temp_sensor_sda_o),
        .TEMP_SENSOR_sda_t(temp_sensor_sda_t),
        .UART_RXD_OUT(UART_RXD_OUT),
        .UART_TXD_IN(UART_TXD_IN),
        .sw(sw));
  IOBUF temp_sensor_scl_iobuf
       (.I(temp_sensor_scl_o),
        .IO(temp_sensor_scl_io),
        .O(temp_sensor_scl_i),
        .T(temp_sensor_scl_t));
  IOBUF temp_sensor_sda_iobuf
       (.I(temp_sensor_sda_o),
        .IO(temp_sensor_sda_io),
        .O(temp_sensor_sda_i),
        .T(temp_sensor_sda_t));
endmodule
