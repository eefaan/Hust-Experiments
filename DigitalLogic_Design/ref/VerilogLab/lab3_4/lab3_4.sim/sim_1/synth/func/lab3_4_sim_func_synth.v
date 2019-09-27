// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.2 (win64) Build 1909853 Thu Jun 15 18:39:09 MDT 2017
// Date        : Thu Jun  7 21:00:49 2018
// Host        : DESKTOP-KM458MG running 64-bit major release  (build 9200)
// Command     : write_verilog -mode funcsim -nolib -force -file
//               C:/VerilogLab/lab3_4/lab3_4.sim/sim_1/synth/func/lab3_4_sim_func_synth.v
// Design      : pipe3b
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module Divider
   (clk_N,
    clk);
  output clk_N;
  input clk;

  wire clear;
  wire clk;
  wire clk_N;
  wire clk_N_i_1_n_0;
  wire \counter[0]_i_10_n_0 ;
  wire \counter[0]_i_11_n_0 ;
  wire \counter[0]_i_21_n_0 ;
  wire \counter[0]_i_22_n_0 ;
  wire \counter[0]_i_23_n_0 ;
  wire \counter[0]_i_24_n_0 ;
  wire \counter[0]_i_25_n_0 ;
  wire \counter[0]_i_26_n_0 ;
  wire \counter[0]_i_27_n_0 ;
  wire \counter[0]_i_28_n_0 ;
  wire \counter[0]_i_29_n_0 ;
  wire \counter[0]_i_30_n_0 ;
  wire \counter[0]_i_31_n_0 ;
  wire \counter[0]_i_32_n_0 ;
  wire \counter[0]_i_33_n_0 ;
  wire \counter[0]_i_34_n_0 ;
  wire \counter[0]_i_35_n_0 ;
  wire \counter[0]_i_36_n_0 ;
  wire \counter[0]_i_37_n_0 ;
  wire \counter[0]_i_38_n_0 ;
  wire \counter[0]_i_39_n_0 ;
  wire \counter[0]_i_3_n_0 ;
  wire \counter[0]_i_40_n_0 ;
  wire \counter[0]_i_41_n_0 ;
  wire \counter[0]_i_42_n_0 ;
  wire \counter[0]_i_43_n_0 ;
  wire \counter[0]_i_44_n_0 ;
  wire \counter[0]_i_45_n_0 ;
  wire \counter[0]_i_46_n_0 ;
  wire \counter[0]_i_47_n_0 ;
  wire \counter[0]_i_48_n_0 ;
  wire \counter[0]_i_49_n_0 ;
  wire \counter[0]_i_4_n_0 ;
  wire \counter[0]_i_50_n_0 ;
  wire \counter[0]_i_51_n_0 ;
  wire \counter[0]_i_5_n_0 ;
  wire \counter[0]_i_6_n_0 ;
  wire \counter[0]_i_7_n_0 ;
  wire \counter[0]_i_8_n_0 ;
  wire \counter[0]_i_9_n_0 ;
  wire \counter[12]_i_2_n_0 ;
  wire \counter[12]_i_3_n_0 ;
  wire \counter[12]_i_4_n_0 ;
  wire \counter[12]_i_5_n_0 ;
  wire \counter[16]_i_2_n_0 ;
  wire \counter[16]_i_3_n_0 ;
  wire \counter[16]_i_4_n_0 ;
  wire \counter[16]_i_5_n_0 ;
  wire \counter[20]_i_2_n_0 ;
  wire \counter[20]_i_3_n_0 ;
  wire \counter[20]_i_4_n_0 ;
  wire \counter[20]_i_5_n_0 ;
  wire \counter[24]_i_2_n_0 ;
  wire \counter[24]_i_3_n_0 ;
  wire \counter[24]_i_4_n_0 ;
  wire \counter[24]_i_5_n_0 ;
  wire \counter[28]_i_2_n_0 ;
  wire \counter[28]_i_3_n_0 ;
  wire \counter[28]_i_4_n_0 ;
  wire \counter[28]_i_5_n_0 ;
  wire \counter[4]_i_2_n_0 ;
  wire \counter[4]_i_3_n_0 ;
  wire \counter[4]_i_4_n_0 ;
  wire \counter[4]_i_5_n_0 ;
  wire \counter[8]_i_2_n_0 ;
  wire \counter[8]_i_3_n_0 ;
  wire \counter[8]_i_4_n_0 ;
  wire \counter[8]_i_5_n_0 ;
  wire [31:0]counter_reg;
  wire \counter_reg[0]_i_13_n_0 ;
  wire \counter_reg[0]_i_13_n_1 ;
  wire \counter_reg[0]_i_13_n_2 ;
  wire \counter_reg[0]_i_13_n_3 ;
  wire \counter_reg[0]_i_14_n_0 ;
  wire \counter_reg[0]_i_14_n_1 ;
  wire \counter_reg[0]_i_14_n_2 ;
  wire \counter_reg[0]_i_14_n_3 ;
  wire \counter_reg[0]_i_15_n_0 ;
  wire \counter_reg[0]_i_15_n_1 ;
  wire \counter_reg[0]_i_15_n_2 ;
  wire \counter_reg[0]_i_15_n_3 ;
  wire \counter_reg[0]_i_16_n_0 ;
  wire \counter_reg[0]_i_16_n_1 ;
  wire \counter_reg[0]_i_16_n_2 ;
  wire \counter_reg[0]_i_16_n_3 ;
  wire \counter_reg[0]_i_17_n_0 ;
  wire \counter_reg[0]_i_17_n_1 ;
  wire \counter_reg[0]_i_17_n_2 ;
  wire \counter_reg[0]_i_17_n_3 ;
  wire \counter_reg[0]_i_18_n_0 ;
  wire \counter_reg[0]_i_18_n_1 ;
  wire \counter_reg[0]_i_18_n_2 ;
  wire \counter_reg[0]_i_18_n_3 ;
  wire \counter_reg[0]_i_19_n_0 ;
  wire \counter_reg[0]_i_19_n_1 ;
  wire \counter_reg[0]_i_19_n_2 ;
  wire \counter_reg[0]_i_19_n_3 ;
  wire \counter_reg[0]_i_20_n_2 ;
  wire \counter_reg[0]_i_20_n_3 ;
  wire \counter_reg[0]_i_2_n_0 ;
  wire \counter_reg[0]_i_2_n_1 ;
  wire \counter_reg[0]_i_2_n_2 ;
  wire \counter_reg[0]_i_2_n_3 ;
  wire \counter_reg[0]_i_2_n_4 ;
  wire \counter_reg[0]_i_2_n_5 ;
  wire \counter_reg[0]_i_2_n_6 ;
  wire \counter_reg[0]_i_2_n_7 ;
  wire \counter_reg[12]_i_1_n_0 ;
  wire \counter_reg[12]_i_1_n_1 ;
  wire \counter_reg[12]_i_1_n_2 ;
  wire \counter_reg[12]_i_1_n_3 ;
  wire \counter_reg[12]_i_1_n_4 ;
  wire \counter_reg[12]_i_1_n_5 ;
  wire \counter_reg[12]_i_1_n_6 ;
  wire \counter_reg[12]_i_1_n_7 ;
  wire \counter_reg[16]_i_1_n_0 ;
  wire \counter_reg[16]_i_1_n_1 ;
  wire \counter_reg[16]_i_1_n_2 ;
  wire \counter_reg[16]_i_1_n_3 ;
  wire \counter_reg[16]_i_1_n_4 ;
  wire \counter_reg[16]_i_1_n_5 ;
  wire \counter_reg[16]_i_1_n_6 ;
  wire \counter_reg[16]_i_1_n_7 ;
  wire \counter_reg[20]_i_1_n_0 ;
  wire \counter_reg[20]_i_1_n_1 ;
  wire \counter_reg[20]_i_1_n_2 ;
  wire \counter_reg[20]_i_1_n_3 ;
  wire \counter_reg[20]_i_1_n_4 ;
  wire \counter_reg[20]_i_1_n_5 ;
  wire \counter_reg[20]_i_1_n_6 ;
  wire \counter_reg[20]_i_1_n_7 ;
  wire \counter_reg[24]_i_1_n_0 ;
  wire \counter_reg[24]_i_1_n_1 ;
  wire \counter_reg[24]_i_1_n_2 ;
  wire \counter_reg[24]_i_1_n_3 ;
  wire \counter_reg[24]_i_1_n_4 ;
  wire \counter_reg[24]_i_1_n_5 ;
  wire \counter_reg[24]_i_1_n_6 ;
  wire \counter_reg[24]_i_1_n_7 ;
  wire \counter_reg[28]_i_1_n_1 ;
  wire \counter_reg[28]_i_1_n_2 ;
  wire \counter_reg[28]_i_1_n_3 ;
  wire \counter_reg[28]_i_1_n_4 ;
  wire \counter_reg[28]_i_1_n_5 ;
  wire \counter_reg[28]_i_1_n_6 ;
  wire \counter_reg[28]_i_1_n_7 ;
  wire \counter_reg[4]_i_1_n_0 ;
  wire \counter_reg[4]_i_1_n_1 ;
  wire \counter_reg[4]_i_1_n_2 ;
  wire \counter_reg[4]_i_1_n_3 ;
  wire \counter_reg[4]_i_1_n_4 ;
  wire \counter_reg[4]_i_1_n_5 ;
  wire \counter_reg[4]_i_1_n_6 ;
  wire \counter_reg[4]_i_1_n_7 ;
  wire \counter_reg[8]_i_1_n_0 ;
  wire \counter_reg[8]_i_1_n_1 ;
  wire \counter_reg[8]_i_1_n_2 ;
  wire \counter_reg[8]_i_1_n_3 ;
  wire \counter_reg[8]_i_1_n_4 ;
  wire \counter_reg[8]_i_1_n_5 ;
  wire \counter_reg[8]_i_1_n_6 ;
  wire \counter_reg[8]_i_1_n_7 ;
  wire [31:0]p_0_in;
  wire [3:2]\NLW_counter_reg[0]_i_20_CO_UNCONNECTED ;
  wire [3:3]\NLW_counter_reg[0]_i_20_O_UNCONNECTED ;
  wire [3:3]\NLW_counter_reg[28]_i_1_CO_UNCONNECTED ;

  LUT2 #(
    .INIT(4'h6)) 
    clk_N_i_1
       (.I0(clear),
        .I1(clk_N),
        .O(clk_N_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    clk_N_reg
       (.C(clk),
        .CE(1'b1),
        .D(clk_N_i_1_n_0),
        .Q(clk_N),
        .R(1'b0));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \counter[0]_i_1 
       (.I0(\counter[0]_i_3_n_0 ),
        .I1(\counter[0]_i_4_n_0 ),
        .I2(\counter[0]_i_5_n_0 ),
        .I3(\counter[0]_i_6_n_0 ),
        .I4(\counter[0]_i_7_n_0 ),
        .I5(\counter[0]_i_8_n_0 ),
        .O(clear));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_10 
       (.I0(counter_reg[2]),
        .O(\counter[0]_i_10_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_11 
       (.I0(counter_reg[1]),
        .O(\counter[0]_i_11_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \counter[0]_i_12 
       (.I0(counter_reg[0]),
        .O(p_0_in[0]));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_21 
       (.I0(counter_reg[4]),
        .O(\counter[0]_i_21_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_22 
       (.I0(counter_reg[3]),
        .O(\counter[0]_i_22_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_23 
       (.I0(counter_reg[2]),
        .O(\counter[0]_i_23_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_24 
       (.I0(counter_reg[1]),
        .O(\counter[0]_i_24_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_25 
       (.I0(counter_reg[8]),
        .O(\counter[0]_i_25_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_26 
       (.I0(counter_reg[7]),
        .O(\counter[0]_i_26_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_27 
       (.I0(counter_reg[6]),
        .O(\counter[0]_i_27_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_28 
       (.I0(counter_reg[5]),
        .O(\counter[0]_i_28_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_29 
       (.I0(counter_reg[12]),
        .O(\counter[0]_i_29_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \counter[0]_i_3 
       (.I0(p_0_in[1]),
        .I1(p_0_in[2]),
        .O(\counter[0]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_30 
       (.I0(counter_reg[11]),
        .O(\counter[0]_i_30_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_31 
       (.I0(counter_reg[10]),
        .O(\counter[0]_i_31_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_32 
       (.I0(counter_reg[9]),
        .O(\counter[0]_i_32_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_33 
       (.I0(counter_reg[16]),
        .O(\counter[0]_i_33_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_34 
       (.I0(counter_reg[15]),
        .O(\counter[0]_i_34_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_35 
       (.I0(counter_reg[14]),
        .O(\counter[0]_i_35_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_36 
       (.I0(counter_reg[13]),
        .O(\counter[0]_i_36_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_37 
       (.I0(counter_reg[20]),
        .O(\counter[0]_i_37_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_38 
       (.I0(counter_reg[19]),
        .O(\counter[0]_i_38_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_39 
       (.I0(counter_reg[18]),
        .O(\counter[0]_i_39_n_0 ));
  LUT6 #(
    .INIT(64'h0000000100000000)) 
    \counter[0]_i_4 
       (.I0(p_0_in[5]),
        .I1(p_0_in[6]),
        .I2(p_0_in[3]),
        .I3(p_0_in[4]),
        .I4(p_0_in[8]),
        .I5(p_0_in[7]),
        .O(\counter[0]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_40 
       (.I0(counter_reg[17]),
        .O(\counter[0]_i_40_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_41 
       (.I0(counter_reg[24]),
        .O(\counter[0]_i_41_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_42 
       (.I0(counter_reg[23]),
        .O(\counter[0]_i_42_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_43 
       (.I0(counter_reg[22]),
        .O(\counter[0]_i_43_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_44 
       (.I0(counter_reg[21]),
        .O(\counter[0]_i_44_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_45 
       (.I0(counter_reg[28]),
        .O(\counter[0]_i_45_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_46 
       (.I0(counter_reg[27]),
        .O(\counter[0]_i_46_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_47 
       (.I0(counter_reg[26]),
        .O(\counter[0]_i_47_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_48 
       (.I0(counter_reg[25]),
        .O(\counter[0]_i_48_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_49 
       (.I0(counter_reg[31]),
        .O(\counter[0]_i_49_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000002000)) 
    \counter[0]_i_5 
       (.I0(p_0_in[12]),
        .I1(p_0_in[11]),
        .I2(p_0_in[9]),
        .I3(p_0_in[10]),
        .I4(p_0_in[14]),
        .I5(p_0_in[13]),
        .O(\counter[0]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_50 
       (.I0(counter_reg[30]),
        .O(\counter[0]_i_50_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_51 
       (.I0(counter_reg[29]),
        .O(\counter[0]_i_51_n_0 ));
  LUT6 #(
    .INIT(64'h0010000000000000)) 
    \counter[0]_i_6 
       (.I0(p_0_in[17]),
        .I1(p_0_in[18]),
        .I2(p_0_in[15]),
        .I3(p_0_in[16]),
        .I4(p_0_in[20]),
        .I5(p_0_in[19]),
        .O(\counter[0]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    \counter[0]_i_7 
       (.I0(p_0_in[23]),
        .I1(p_0_in[24]),
        .I2(p_0_in[21]),
        .I3(p_0_in[22]),
        .I4(p_0_in[26]),
        .I5(p_0_in[25]),
        .O(\counter[0]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0000000100000000)) 
    \counter[0]_i_8 
       (.I0(p_0_in[29]),
        .I1(p_0_in[30]),
        .I2(p_0_in[27]),
        .I3(p_0_in[28]),
        .I4(p_0_in[31]),
        .I5(counter_reg[0]),
        .O(\counter[0]_i_8_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[0]_i_9 
       (.I0(counter_reg[3]),
        .O(\counter[0]_i_9_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[12]_i_2 
       (.I0(counter_reg[15]),
        .O(\counter[12]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[12]_i_3 
       (.I0(counter_reg[14]),
        .O(\counter[12]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[12]_i_4 
       (.I0(counter_reg[13]),
        .O(\counter[12]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[12]_i_5 
       (.I0(counter_reg[12]),
        .O(\counter[12]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[16]_i_2 
       (.I0(counter_reg[19]),
        .O(\counter[16]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[16]_i_3 
       (.I0(counter_reg[18]),
        .O(\counter[16]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[16]_i_4 
       (.I0(counter_reg[17]),
        .O(\counter[16]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[16]_i_5 
       (.I0(counter_reg[16]),
        .O(\counter[16]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[20]_i_2 
       (.I0(counter_reg[23]),
        .O(\counter[20]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[20]_i_3 
       (.I0(counter_reg[22]),
        .O(\counter[20]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[20]_i_4 
       (.I0(counter_reg[21]),
        .O(\counter[20]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[20]_i_5 
       (.I0(counter_reg[20]),
        .O(\counter[20]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[24]_i_2 
       (.I0(counter_reg[27]),
        .O(\counter[24]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[24]_i_3 
       (.I0(counter_reg[26]),
        .O(\counter[24]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[24]_i_4 
       (.I0(counter_reg[25]),
        .O(\counter[24]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[24]_i_5 
       (.I0(counter_reg[24]),
        .O(\counter[24]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[28]_i_2 
       (.I0(counter_reg[31]),
        .O(\counter[28]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[28]_i_3 
       (.I0(counter_reg[30]),
        .O(\counter[28]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[28]_i_4 
       (.I0(counter_reg[29]),
        .O(\counter[28]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[28]_i_5 
       (.I0(counter_reg[28]),
        .O(\counter[28]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[4]_i_2 
       (.I0(counter_reg[7]),
        .O(\counter[4]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[4]_i_3 
       (.I0(counter_reg[6]),
        .O(\counter[4]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[4]_i_4 
       (.I0(counter_reg[5]),
        .O(\counter[4]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[4]_i_5 
       (.I0(counter_reg[4]),
        .O(\counter[4]_i_5_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[8]_i_2 
       (.I0(counter_reg[11]),
        .O(\counter[8]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[8]_i_3 
       (.I0(counter_reg[10]),
        .O(\counter[8]_i_3_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[8]_i_4 
       (.I0(counter_reg[9]),
        .O(\counter[8]_i_4_n_0 ));
  LUT1 #(
    .INIT(2'h2)) 
    \counter[8]_i_5 
       (.I0(counter_reg[8]),
        .O(\counter[8]_i_5_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[0] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[0]_i_2_n_7 ),
        .Q(counter_reg[0]),
        .R(clear));
  CARRY4 \counter_reg[0]_i_13 
       (.CI(1'b0),
        .CO({\counter_reg[0]_i_13_n_0 ,\counter_reg[0]_i_13_n_1 ,\counter_reg[0]_i_13_n_2 ,\counter_reg[0]_i_13_n_3 }),
        .CYINIT(counter_reg[0]),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[4:1]),
        .S({\counter[0]_i_21_n_0 ,\counter[0]_i_22_n_0 ,\counter[0]_i_23_n_0 ,\counter[0]_i_24_n_0 }));
  CARRY4 \counter_reg[0]_i_14 
       (.CI(\counter_reg[0]_i_13_n_0 ),
        .CO({\counter_reg[0]_i_14_n_0 ,\counter_reg[0]_i_14_n_1 ,\counter_reg[0]_i_14_n_2 ,\counter_reg[0]_i_14_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[8:5]),
        .S({\counter[0]_i_25_n_0 ,\counter[0]_i_26_n_0 ,\counter[0]_i_27_n_0 ,\counter[0]_i_28_n_0 }));
  CARRY4 \counter_reg[0]_i_15 
       (.CI(\counter_reg[0]_i_14_n_0 ),
        .CO({\counter_reg[0]_i_15_n_0 ,\counter_reg[0]_i_15_n_1 ,\counter_reg[0]_i_15_n_2 ,\counter_reg[0]_i_15_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[12:9]),
        .S({\counter[0]_i_29_n_0 ,\counter[0]_i_30_n_0 ,\counter[0]_i_31_n_0 ,\counter[0]_i_32_n_0 }));
  CARRY4 \counter_reg[0]_i_16 
       (.CI(\counter_reg[0]_i_15_n_0 ),
        .CO({\counter_reg[0]_i_16_n_0 ,\counter_reg[0]_i_16_n_1 ,\counter_reg[0]_i_16_n_2 ,\counter_reg[0]_i_16_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[16:13]),
        .S({\counter[0]_i_33_n_0 ,\counter[0]_i_34_n_0 ,\counter[0]_i_35_n_0 ,\counter[0]_i_36_n_0 }));
  CARRY4 \counter_reg[0]_i_17 
       (.CI(\counter_reg[0]_i_16_n_0 ),
        .CO({\counter_reg[0]_i_17_n_0 ,\counter_reg[0]_i_17_n_1 ,\counter_reg[0]_i_17_n_2 ,\counter_reg[0]_i_17_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[20:17]),
        .S({\counter[0]_i_37_n_0 ,\counter[0]_i_38_n_0 ,\counter[0]_i_39_n_0 ,\counter[0]_i_40_n_0 }));
  CARRY4 \counter_reg[0]_i_18 
       (.CI(\counter_reg[0]_i_17_n_0 ),
        .CO({\counter_reg[0]_i_18_n_0 ,\counter_reg[0]_i_18_n_1 ,\counter_reg[0]_i_18_n_2 ,\counter_reg[0]_i_18_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[24:21]),
        .S({\counter[0]_i_41_n_0 ,\counter[0]_i_42_n_0 ,\counter[0]_i_43_n_0 ,\counter[0]_i_44_n_0 }));
  CARRY4 \counter_reg[0]_i_19 
       (.CI(\counter_reg[0]_i_18_n_0 ),
        .CO({\counter_reg[0]_i_19_n_0 ,\counter_reg[0]_i_19_n_1 ,\counter_reg[0]_i_19_n_2 ,\counter_reg[0]_i_19_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[28:25]),
        .S({\counter[0]_i_45_n_0 ,\counter[0]_i_46_n_0 ,\counter[0]_i_47_n_0 ,\counter[0]_i_48_n_0 }));
  CARRY4 \counter_reg[0]_i_2 
       (.CI(1'b0),
        .CO({\counter_reg[0]_i_2_n_0 ,\counter_reg[0]_i_2_n_1 ,\counter_reg[0]_i_2_n_2 ,\counter_reg[0]_i_2_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b1}),
        .O({\counter_reg[0]_i_2_n_4 ,\counter_reg[0]_i_2_n_5 ,\counter_reg[0]_i_2_n_6 ,\counter_reg[0]_i_2_n_7 }),
        .S({\counter[0]_i_9_n_0 ,\counter[0]_i_10_n_0 ,\counter[0]_i_11_n_0 ,p_0_in[0]}));
  CARRY4 \counter_reg[0]_i_20 
       (.CI(\counter_reg[0]_i_19_n_0 ),
        .CO({\NLW_counter_reg[0]_i_20_CO_UNCONNECTED [3:2],\counter_reg[0]_i_20_n_2 ,\counter_reg[0]_i_20_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_counter_reg[0]_i_20_O_UNCONNECTED [3],p_0_in[31:29]}),
        .S({1'b0,\counter[0]_i_49_n_0 ,\counter[0]_i_50_n_0 ,\counter[0]_i_51_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[10] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[8]_i_1_n_5 ),
        .Q(counter_reg[10]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[11] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[8]_i_1_n_4 ),
        .Q(counter_reg[11]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[12] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[12]_i_1_n_7 ),
        .Q(counter_reg[12]),
        .R(clear));
  CARRY4 \counter_reg[12]_i_1 
       (.CI(\counter_reg[8]_i_1_n_0 ),
        .CO({\counter_reg[12]_i_1_n_0 ,\counter_reg[12]_i_1_n_1 ,\counter_reg[12]_i_1_n_2 ,\counter_reg[12]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[12]_i_1_n_4 ,\counter_reg[12]_i_1_n_5 ,\counter_reg[12]_i_1_n_6 ,\counter_reg[12]_i_1_n_7 }),
        .S({\counter[12]_i_2_n_0 ,\counter[12]_i_3_n_0 ,\counter[12]_i_4_n_0 ,\counter[12]_i_5_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[13] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[12]_i_1_n_6 ),
        .Q(counter_reg[13]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[14] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[12]_i_1_n_5 ),
        .Q(counter_reg[14]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[15] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[12]_i_1_n_4 ),
        .Q(counter_reg[15]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[16] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[16]_i_1_n_7 ),
        .Q(counter_reg[16]),
        .R(clear));
  CARRY4 \counter_reg[16]_i_1 
       (.CI(\counter_reg[12]_i_1_n_0 ),
        .CO({\counter_reg[16]_i_1_n_0 ,\counter_reg[16]_i_1_n_1 ,\counter_reg[16]_i_1_n_2 ,\counter_reg[16]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[16]_i_1_n_4 ,\counter_reg[16]_i_1_n_5 ,\counter_reg[16]_i_1_n_6 ,\counter_reg[16]_i_1_n_7 }),
        .S({\counter[16]_i_2_n_0 ,\counter[16]_i_3_n_0 ,\counter[16]_i_4_n_0 ,\counter[16]_i_5_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[17] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[16]_i_1_n_6 ),
        .Q(counter_reg[17]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[18] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[16]_i_1_n_5 ),
        .Q(counter_reg[18]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[19] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[16]_i_1_n_4 ),
        .Q(counter_reg[19]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[1] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[0]_i_2_n_6 ),
        .Q(counter_reg[1]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[20] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[20]_i_1_n_7 ),
        .Q(counter_reg[20]),
        .R(clear));
  CARRY4 \counter_reg[20]_i_1 
       (.CI(\counter_reg[16]_i_1_n_0 ),
        .CO({\counter_reg[20]_i_1_n_0 ,\counter_reg[20]_i_1_n_1 ,\counter_reg[20]_i_1_n_2 ,\counter_reg[20]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[20]_i_1_n_4 ,\counter_reg[20]_i_1_n_5 ,\counter_reg[20]_i_1_n_6 ,\counter_reg[20]_i_1_n_7 }),
        .S({\counter[20]_i_2_n_0 ,\counter[20]_i_3_n_0 ,\counter[20]_i_4_n_0 ,\counter[20]_i_5_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[21] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[20]_i_1_n_6 ),
        .Q(counter_reg[21]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[22] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[20]_i_1_n_5 ),
        .Q(counter_reg[22]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[23] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[20]_i_1_n_4 ),
        .Q(counter_reg[23]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[24] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[24]_i_1_n_7 ),
        .Q(counter_reg[24]),
        .R(clear));
  CARRY4 \counter_reg[24]_i_1 
       (.CI(\counter_reg[20]_i_1_n_0 ),
        .CO({\counter_reg[24]_i_1_n_0 ,\counter_reg[24]_i_1_n_1 ,\counter_reg[24]_i_1_n_2 ,\counter_reg[24]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[24]_i_1_n_4 ,\counter_reg[24]_i_1_n_5 ,\counter_reg[24]_i_1_n_6 ,\counter_reg[24]_i_1_n_7 }),
        .S({\counter[24]_i_2_n_0 ,\counter[24]_i_3_n_0 ,\counter[24]_i_4_n_0 ,\counter[24]_i_5_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[25] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[24]_i_1_n_6 ),
        .Q(counter_reg[25]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[26] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[24]_i_1_n_5 ),
        .Q(counter_reg[26]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[27] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[24]_i_1_n_4 ),
        .Q(counter_reg[27]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[28] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[28]_i_1_n_7 ),
        .Q(counter_reg[28]),
        .R(clear));
  CARRY4 \counter_reg[28]_i_1 
       (.CI(\counter_reg[24]_i_1_n_0 ),
        .CO({\NLW_counter_reg[28]_i_1_CO_UNCONNECTED [3],\counter_reg[28]_i_1_n_1 ,\counter_reg[28]_i_1_n_2 ,\counter_reg[28]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[28]_i_1_n_4 ,\counter_reg[28]_i_1_n_5 ,\counter_reg[28]_i_1_n_6 ,\counter_reg[28]_i_1_n_7 }),
        .S({\counter[28]_i_2_n_0 ,\counter[28]_i_3_n_0 ,\counter[28]_i_4_n_0 ,\counter[28]_i_5_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[29] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[28]_i_1_n_6 ),
        .Q(counter_reg[29]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[2] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[0]_i_2_n_5 ),
        .Q(counter_reg[2]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[30] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[28]_i_1_n_5 ),
        .Q(counter_reg[30]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[31] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[28]_i_1_n_4 ),
        .Q(counter_reg[31]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[3] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[0]_i_2_n_4 ),
        .Q(counter_reg[3]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[4] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[4]_i_1_n_7 ),
        .Q(counter_reg[4]),
        .R(clear));
  CARRY4 \counter_reg[4]_i_1 
       (.CI(\counter_reg[0]_i_2_n_0 ),
        .CO({\counter_reg[4]_i_1_n_0 ,\counter_reg[4]_i_1_n_1 ,\counter_reg[4]_i_1_n_2 ,\counter_reg[4]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[4]_i_1_n_4 ,\counter_reg[4]_i_1_n_5 ,\counter_reg[4]_i_1_n_6 ,\counter_reg[4]_i_1_n_7 }),
        .S({\counter[4]_i_2_n_0 ,\counter[4]_i_3_n_0 ,\counter[4]_i_4_n_0 ,\counter[4]_i_5_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[5] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[4]_i_1_n_6 ),
        .Q(counter_reg[5]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[6] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[4]_i_1_n_5 ),
        .Q(counter_reg[6]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[7] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[4]_i_1_n_4 ),
        .Q(counter_reg[7]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[8] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[8]_i_1_n_7 ),
        .Q(counter_reg[8]),
        .R(clear));
  CARRY4 \counter_reg[8]_i_1 
       (.CI(\counter_reg[4]_i_1_n_0 ),
        .CO({\counter_reg[8]_i_1_n_0 ,\counter_reg[8]_i_1_n_1 ,\counter_reg[8]_i_1_n_2 ,\counter_reg[8]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[8]_i_1_n_4 ,\counter_reg[8]_i_1_n_5 ,\counter_reg[8]_i_1_n_6 ,\counter_reg[8]_i_1_n_7 }),
        .S({\counter[8]_i_2_n_0 ,\counter[8]_i_3_n_0 ,\counter[8]_i_4_n_0 ,\counter[8]_i_5_n_0 }));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[9] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[8]_i_1_n_6 ),
        .Q(counter_reg[9]),
        .R(clear));
endmodule

(* NotValidForBitStream *)
module pipe3b
   (sig_nsyn,
    clk,
    q1,
    q2,
    sig_syn);
  input sig_nsyn;
  input clk;
  output q1;
  output q2;
  output sig_syn;

  wire clk;
  wire clk_IBUF;
  wire clk_IBUF_BUFG;
  wire clk_N;
  wire q1;
  wire q1_OBUF;
  wire q2;
  wire q2_OBUF;
  wire sig_nsyn;
  wire sig_nsyn_IBUF;
  wire sig_syn;
  wire sig_syn_OBUF;

  BUFG clk_IBUF_BUFG_inst
       (.I(clk_IBUF),
        .O(clk_IBUF_BUFG));
  IBUF clk_IBUF_inst
       (.I(clk),
        .O(clk_IBUF));
  Divider my_divider
       (.clk(clk_IBUF_BUFG),
        .clk_N(clk_N));
  OBUF q1_OBUF_inst
       (.I(q1_OBUF),
        .O(q1));
  FDRE #(
    .INIT(1'b0)) 
    q1_reg
       (.C(clk_N),
        .CE(1'b1),
        .D(sig_nsyn_IBUF),
        .Q(q1_OBUF),
        .R(1'b0));
  OBUF q2_OBUF_inst
       (.I(q2_OBUF),
        .O(q2));
  FDRE #(
    .INIT(1'b0)) 
    q2_reg
       (.C(clk_N),
        .CE(1'b1),
        .D(q1_OBUF),
        .Q(q2_OBUF),
        .R(1'b0));
  IBUF sig_nsyn_IBUF_inst
       (.I(sig_nsyn),
        .O(sig_nsyn_IBUF));
  OBUF sig_syn_OBUF_inst
       (.I(sig_syn_OBUF),
        .O(sig_syn));
  FDRE #(
    .INIT(1'b0)) 
    sig_syn_reg
       (.C(clk_N),
        .CE(1'b1),
        .D(q2_OBUF),
        .Q(sig_syn_OBUF),
        .R(1'b0));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
