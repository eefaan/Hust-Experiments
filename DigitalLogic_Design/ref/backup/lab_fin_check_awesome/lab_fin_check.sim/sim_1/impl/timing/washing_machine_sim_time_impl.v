// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.2 (win64) Build 1909853 Thu Jun 15 18:39:09 MDT 2017
// Date        : Tue Sep 25 17:07:29 2018
// Host        : DESKTOP-KM458MG running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               C:/VerilogLab/lab_fin_check/lab_fin_check.sim/sim_1/impl/timing/washing_machine_sim_time_impl.v
// Design      : washing_machine
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

module FSM
   (light_running_OBUF,
    state_OBUF,
    \water_line_reg[0] ,
    \FSM_onehot_state_reg[2]_0 ,
    \timer_set_reg[3] ,
    seg_OBUF,
    \seg[0] ,
    pause_con_IBUF_BUFG,
    CLK,
    Q,
    an_OBUF,
    \num_reg[0] ,
    \num_reg[0]_0 ,
    \num_reg[2] ,
    \num_reg[0]_1 ,
    \num_reg[0]_2 ,
    \num_reg[1] ,
    weight_change,
    mode_change_IBUF_BUFG,
    in1);
  output light_running_OBUF;
  output [3:0]state_OBUF;
  output \water_line_reg[0] ;
  output \FSM_onehot_state_reg[2]_0 ;
  output \timer_set_reg[3] ;
  output [6:0]seg_OBUF;
  output [0:0]\seg[0] ;
  input pause_con_IBUF_BUFG;
  input CLK;
  input [2:0]Q;
  input [1:0]an_OBUF;
  input \num_reg[0] ;
  input \num_reg[0]_0 ;
  input \num_reg[2] ;
  input \num_reg[0]_1 ;
  input \num_reg[0]_2 ;
  input \num_reg[1] ;
  input weight_change;
  input mode_change_IBUF_BUFG;
  input in1;

  wire CLK;
  wire \FSM_onehot_state[0]_i_1_n_0 ;
  wire \FSM_onehot_state[0]_i_2_n_0 ;
  wire \FSM_onehot_state[0]_i_3_n_0 ;
  wire \FSM_onehot_state[10]_i_1_n_0 ;
  wire \FSM_onehot_state[10]_i_2_n_0 ;
  wire \FSM_onehot_state[1]_i_2_n_0 ;
  wire \FSM_onehot_state[2]_i_3_n_0 ;
  wire \FSM_onehot_state[5]_i_2_n_0 ;
  wire \FSM_onehot_state[7]_i_3_n_0 ;
  wire \FSM_onehot_state[9]_i_2_n_0 ;
  wire \FSM_onehot_state[9]_i_3_n_0 ;
  wire \FSM_onehot_state[9]_i_4_n_0 ;
  wire \FSM_onehot_state_reg[2]_0 ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[0] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[10] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[1] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[2] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[3] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[4] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[5] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[6] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[7] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[8] ;
  (* RTL_KEEP = "yes" *) wire \FSM_onehot_state_reg_n_0_[9] ;
  wire [2:0]Q;
  wire [1:0]an_OBUF;
  wire in1;
  wire light_running_OBUF;
  wire light_running_i_1_n_0;
  wire mode_change_IBUF_BUFG;
  wire my_ssdisp_n_0;
  wire my_ssdisp_n_1;
  wire my_ssdisp_n_10;
  wire my_ssdisp_n_11;
  wire my_ssdisp_n_12;
  wire my_ssdisp_n_13;
  wire my_ssdisp_n_14;
  wire my_ssdisp_n_15;
  wire my_ssdisp_n_16;
  wire my_ssdisp_n_17;
  wire my_ssdisp_n_18;
  wire my_ssdisp_n_20;
  wire my_ssdisp_n_21;
  wire my_ssdisp_n_22;
  wire my_ssdisp_n_23;
  wire my_ssdisp_n_26;
  wire my_ssdisp_n_27;
  wire my_ssdisp_n_28;
  wire my_ssdisp_n_29;
  wire my_ssdisp_n_30;
  wire my_ssdisp_n_31;
  wire my_ssdisp_n_32;
  wire my_ssdisp_n_33;
  wire my_ssdisp_n_34;
  wire my_ssdisp_n_7;
  wire my_ssdisp_n_8;
  wire my_ssdisp_n_9;
  wire my_timer_n_0;
  wire my_timer_n_1;
  wire my_timer_n_10;
  wire my_timer_n_19;
  wire my_timer_n_2;
  wire my_timer_n_20;
  wire my_timer_n_21;
  wire my_timer_n_22;
  wire my_timer_n_23;
  wire my_timer_n_24;
  wire my_timer_n_25;
  wire my_timer_n_26;
  wire my_timer_n_27;
  wire my_timer_n_3;
  wire my_timer_n_4;
  wire my_timer_n_5;
  wire my_timer_n_6;
  wire my_timer_n_7;
  wire my_timer_n_8;
  wire my_timer_n_9;
  wire next_state1;
  wire next_state10_out;
  wire next_state15_out;
  wire \num_reg[0] ;
  wire \num_reg[0]_0 ;
  wire \num_reg[0]_1 ;
  wire \num_reg[0]_2 ;
  wire \num_reg[1] ;
  wire \num_reg[2] ;
  wire pause_con_IBUF_BUFG;
  wire [0:0]\seg[0] ;
  wire [6:0]seg_OBUF;
  wire \seg_OBUF[6]_inst_i_9_n_0 ;
  wire [3:0]state_1;
  wire [3:0]state_2;
  wire [3:0]state_OBUF;
  wire \status_mode[0]_i_1_n_0 ;
  wire \status_mode[1]_i_1_n_0 ;
  wire \status_mode[2]_i_1_n_0 ;
  wire \status_mode_reg_n_0_[0] ;
  wire \status_mode_reg_n_0_[1] ;
  wire \status_weight[0]_i_1_n_0 ;
  wire \status_weight[1]_i_1_n_0 ;
  wire \status_weight_reg_n_0_[0] ;
  wire \status_weight_reg_n_0_[1] ;
  wire \timer_set_reg[3] ;
  wire \water_line_reg[0] ;
  wire weight_change;

  LUT6 #(
    .INIT(64'hEE2AFFFFAAAAAAAA)) 
    \FSM_onehot_state[0]_i_1 
       (.I0(\FSM_onehot_state[0]_i_2_n_0 ),
        .I1(\FSM_onehot_state_reg[2]_0 ),
        .I2(\status_mode_reg_n_0_[0] ),
        .I3(\status_mode_reg_n_0_[1] ),
        .I4(light_running_OBUF),
        .I5(\FSM_onehot_state_reg_n_0_[0] ),
        .O(\FSM_onehot_state[0]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \FSM_onehot_state[0]_i_2 
       (.I0(\FSM_onehot_state_reg_n_0_[2] ),
        .I1(\FSM_onehot_state[5]_i_2_n_0 ),
        .I2(\FSM_onehot_state_reg_n_0_[8] ),
        .I3(\FSM_onehot_state_reg_n_0_[3] ),
        .I4(\FSM_onehot_state_reg_n_0_[4] ),
        .I5(\FSM_onehot_state[0]_i_3_n_0 ),
        .O(\FSM_onehot_state[0]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \FSM_onehot_state[0]_i_3 
       (.I0(\FSM_onehot_state_reg_n_0_[6] ),
        .I1(\FSM_onehot_state_reg_n_0_[5] ),
        .I2(\FSM_onehot_state_reg_n_0_[7] ),
        .I3(\FSM_onehot_state_reg_n_0_[9] ),
        .O(\FSM_onehot_state[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000010000)) 
    \FSM_onehot_state[10]_i_1 
       (.I0(\FSM_onehot_state[10]_i_2_n_0 ),
        .I1(\FSM_onehot_state_reg_n_0_[5] ),
        .I2(\FSM_onehot_state_reg_n_0_[6] ),
        .I3(\FSM_onehot_state_reg_n_0_[7] ),
        .I4(\FSM_onehot_state_reg_n_0_[9] ),
        .I5(\FSM_onehot_state_reg_n_0_[8] ),
        .O(\FSM_onehot_state[10]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \FSM_onehot_state[10]_i_2 
       (.I0(\FSM_onehot_state_reg_n_0_[3] ),
        .I1(\FSM_onehot_state_reg_n_0_[4] ),
        .I2(\FSM_onehot_state_reg_n_0_[0] ),
        .I3(\FSM_onehot_state_reg_n_0_[1] ),
        .I4(\FSM_onehot_state_reg_n_0_[2] ),
        .O(\FSM_onehot_state[10]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'h15)) 
    \FSM_onehot_state[1]_i_2 
       (.I0(\FSM_onehot_state_reg[2]_0 ),
        .I1(\status_mode_reg_n_0_[0] ),
        .I2(\status_mode_reg_n_0_[1] ),
        .O(\FSM_onehot_state[1]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'hB)) 
    \FSM_onehot_state[2]_i_3 
       (.I0(\status_mode_reg_n_0_[1] ),
        .I1(\status_mode_reg_n_0_[0] ),
        .O(\FSM_onehot_state[2]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \FSM_onehot_state[5]_i_2 
       (.I0(\FSM_onehot_state_reg_n_0_[0] ),
        .I1(\FSM_onehot_state_reg_n_0_[1] ),
        .O(\FSM_onehot_state[5]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hFE)) 
    \FSM_onehot_state[7]_i_3 
       (.I0(\FSM_onehot_state_reg_n_0_[2] ),
        .I1(\FSM_onehot_state_reg_n_0_[1] ),
        .I2(\FSM_onehot_state_reg_n_0_[0] ),
        .O(\FSM_onehot_state[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h1000100010FF1000)) 
    \FSM_onehot_state[9]_i_2 
       (.I0(\status_mode_reg_n_0_[1] ),
        .I1(\FSM_onehot_state_reg[2]_0 ),
        .I2(\status_mode_reg_n_0_[0] ),
        .I3(\FSM_onehot_state_reg_n_0_[2] ),
        .I4(\FSM_onehot_state[9]_i_3_n_0 ),
        .I5(\FSM_onehot_state[9]_i_4_n_0 ),
        .O(\FSM_onehot_state[9]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'h01)) 
    \FSM_onehot_state[9]_i_3 
       (.I0(\FSM_onehot_state_reg_n_0_[3] ),
        .I1(\FSM_onehot_state_reg_n_0_[5] ),
        .I2(\FSM_onehot_state_reg_n_0_[4] ),
        .O(\FSM_onehot_state[9]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hBFB0BFBF)) 
    \FSM_onehot_state[9]_i_4 
       (.I0(\FSM_onehot_state_reg[2]_0 ),
        .I1(\status_mode_reg_n_0_[1] ),
        .I2(\FSM_onehot_state_reg_n_0_[6] ),
        .I3(\FSM_onehot_state_reg_n_0_[7] ),
        .I4(\FSM_onehot_state_reg_n_0_[8] ),
        .O(\FSM_onehot_state[9]_i_4_n_0 ));
  (* KEEP = "yes" *) 
  FDSE #(
    .INIT(1'b1)) 
    \FSM_onehot_state_reg[0] 
       (.C(CLK),
        .CE(1'b1),
        .D(\FSM_onehot_state[0]_i_1_n_0 ),
        .Q(\FSM_onehot_state_reg_n_0_[0] ),
        .S(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[10] 
       (.C(CLK),
        .CE(1'b1),
        .D(\FSM_onehot_state[10]_i_1_n_0 ),
        .Q(\FSM_onehot_state_reg_n_0_[10] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[1] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_27),
        .Q(\FSM_onehot_state_reg_n_0_[1] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[2] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_26),
        .Q(\FSM_onehot_state_reg_n_0_[2] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[3] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_25),
        .Q(\FSM_onehot_state_reg_n_0_[3] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[4] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_24),
        .Q(\FSM_onehot_state_reg_n_0_[4] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[5] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_23),
        .Q(\FSM_onehot_state_reg_n_0_[5] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[6] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_22),
        .Q(\FSM_onehot_state_reg_n_0_[6] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[7] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_21),
        .Q(\FSM_onehot_state_reg_n_0_[7] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[8] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_20),
        .Q(\FSM_onehot_state_reg_n_0_[8] ),
        .R(in1));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[9] 
       (.C(CLK),
        .CE(1'b1),
        .D(my_timer_n_19),
        .Q(\FSM_onehot_state_reg_n_0_[9] ),
        .R(in1));
  LUT1 #(
    .INIT(2'h1)) 
    light_running_i_1
       (.I0(light_running_OBUF),
        .O(light_running_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    light_running_reg
       (.C(pause_con_IBUF_BUFG),
        .CE(1'b1),
        .D(light_running_i_1_n_0),
        .Q(light_running_OBUF),
        .R(1'b0));
  ssdisp my_ssdisp
       (.D(state_OBUF),
        .Q({\status_weight_reg_n_0_[1] ,\status_weight_reg_n_0_[0] }),
        .an_OBUF(an_OBUF[1]),
        .next_state1(next_state1),
        .next_state10_out(next_state10_out),
        .next_state15_out(next_state15_out),
        .\num_reg[0] (\num_reg[0]_2 ),
        .\num_reg[1] (\num_reg[1] ),
        .\num_reg[2] (Q),
        .out({\FSM_onehot_state_reg_n_0_[10] ,\FSM_onehot_state_reg_n_0_[9] ,\FSM_onehot_state_reg_n_0_[8] ,\FSM_onehot_state_reg_n_0_[7] ,\FSM_onehot_state_reg_n_0_[6] ,\FSM_onehot_state_reg_n_0_[5] ,\FSM_onehot_state_reg_n_0_[4] ,\FSM_onehot_state_reg_n_0_[3] ,\FSM_onehot_state_reg_n_0_[2] ,\FSM_onehot_state_reg_n_0_[1] }),
        .\seg[0] (my_ssdisp_n_14),
        .\seg[0]_0 (my_ssdisp_n_26),
        .\seg[0]_1 (my_ssdisp_n_28),
        .\seg[0]_2 (my_ssdisp_n_29),
        .\seg[0]_3 (my_ssdisp_n_30),
        .\seg[0]_4 (\seg[0] ),
        .\seg[2] (my_ssdisp_n_16),
        .\seg[2]_0 (my_ssdisp_n_20),
        .\seg[2]_1 (my_ssdisp_n_22),
        .\seg[4] (my_ssdisp_n_0),
        .\seg[4]_0 (my_ssdisp_n_1),
        .\seg[4]_1 (my_ssdisp_n_7),
        .\seg[4]_10 (my_ssdisp_n_18),
        .\seg[4]_11 (my_ssdisp_n_21),
        .\seg[4]_12 (my_ssdisp_n_23),
        .\seg[4]_13 (my_ssdisp_n_27),
        .\seg[4]_14 (my_ssdisp_n_31),
        .\seg[4]_15 (my_ssdisp_n_32),
        .\seg[4]_16 (my_ssdisp_n_33),
        .\seg[4]_17 (my_ssdisp_n_34),
        .\seg[4]_2 (my_ssdisp_n_8),
        .\seg[4]_3 (my_ssdisp_n_9),
        .\seg[4]_4 (my_ssdisp_n_10),
        .\seg[4]_5 (my_ssdisp_n_11),
        .\seg[4]_6 (my_ssdisp_n_12),
        .\seg[4]_7 (my_ssdisp_n_13),
        .\seg[4]_8 (my_ssdisp_n_15),
        .\seg[4]_9 (my_ssdisp_n_17),
        .\status_mode_reg[0] (\status_mode_reg_n_0_[0] ),
        .\status_mode_reg[0]_0 ({my_timer_n_6,my_timer_n_7,my_timer_n_8,my_timer_n_9,my_timer_n_10}),
        .\status_mode_reg[1] (\status_mode_reg_n_0_[1] ),
        .\status_mode_reg[2] (\FSM_onehot_state_reg[2]_0 ),
        .\status_weight_reg[1] ({my_timer_n_0,my_timer_n_1,my_timer_n_2,my_timer_n_3,my_timer_n_4,my_timer_n_5}),
        .\water_line_reg[0] (\water_line_reg[0] ));
  timer my_timer
       (.CLK(CLK),
        .D(state_OBUF),
        .\FSM_onehot_state_reg[0] (\FSM_onehot_state[5]_i_2_n_0 ),
        .\FSM_onehot_state_reg[2] (\FSM_onehot_state[7]_i_3_n_0 ),
        .\FSM_onehot_state_reg[3] (\FSM_onehot_state[9]_i_3_n_0 ),
        .\FSM_onehot_state_reg[3]_0 (\FSM_onehot_state[10]_i_2_n_0 ),
        .\FSM_onehot_state_reg[5] (\seg_OBUF[6]_inst_i_9_n_0 ),
        .\FSM_onehot_state_reg[6] (\water_line_reg[0] ),
        .\FSM_onehot_state_reg[6]_0 (my_ssdisp_n_8),
        .\FSM_onehot_state_reg[6]_1 (my_ssdisp_n_12),
        .\FSM_onehot_state_reg[9] ({my_timer_n_19,my_timer_n_20,my_timer_n_21,my_timer_n_22,my_timer_n_23,my_timer_n_24,my_timer_n_25,my_timer_n_26,my_timer_n_27}),
        .\FSM_onehot_state_reg[9]_0 (my_ssdisp_n_0),
        .Q({\status_weight_reg_n_0_[1] ,\status_weight_reg_n_0_[0] }),
        .an_OBUF(an_OBUF[0]),
        .light_running_reg(light_running_OBUF),
        .next_state1(next_state1),
        .next_state10_out(next_state10_out),
        .next_state15_out(next_state15_out),
        .\num_reg[0] (\num_reg[0] ),
        .\num_reg[0]_0 (\num_reg[0]_0 ),
        .\num_reg[0]_1 (\num_reg[0]_1 ),
        .\num_reg[1] (my_ssdisp_n_27),
        .\num_reg[1]_0 (my_ssdisp_n_30),
        .\num_reg[1]_1 (my_ssdisp_n_26),
        .\num_reg[2] (Q),
        .\num_reg[2]_0 (my_ssdisp_n_28),
        .\num_reg[2]_1 (my_ssdisp_n_29),
        .\num_reg[2]_2 (\num_reg[2] ),
        .out({\FSM_onehot_state_reg_n_0_[10] ,\FSM_onehot_state_reg_n_0_[9] ,\FSM_onehot_state_reg_n_0_[8] ,\FSM_onehot_state_reg_n_0_[7] ,\FSM_onehot_state_reg_n_0_[6] ,\FSM_onehot_state_reg_n_0_[5] ,\FSM_onehot_state_reg_n_0_[4] ,\FSM_onehot_state_reg_n_0_[3] ,\FSM_onehot_state_reg_n_0_[2] ,\FSM_onehot_state_reg_n_0_[1] ,\FSM_onehot_state_reg_n_0_[0] }),
        .\seg[4] ({my_timer_n_0,my_timer_n_1,my_timer_n_2,my_timer_n_3,my_timer_n_4,my_timer_n_5}),
        .\seg[4]_0 ({my_timer_n_6,my_timer_n_7,my_timer_n_8,my_timer_n_9,my_timer_n_10}),
        .seg_OBUF(seg_OBUF),
        .\state_1_reg[3] (state_1),
        .\state_2_reg[3] (state_2),
        .\status_mode_reg[0] (\status_mode_reg_n_0_[0] ),
        .\status_mode_reg[0]_0 (my_ssdisp_n_22),
        .\status_mode_reg[0]_1 (my_ssdisp_n_32),
        .\status_mode_reg[0]_2 (my_ssdisp_n_21),
        .\status_mode_reg[0]_3 (my_ssdisp_n_23),
        .\status_mode_reg[0]_4 (my_ssdisp_n_11),
        .\status_mode_reg[1] (\status_mode_reg_n_0_[1] ),
        .\status_mode_reg[1]_0 (my_ssdisp_n_13),
        .\status_mode_reg[1]_1 (my_ssdisp_n_14),
        .\status_mode_reg[1]_2 (my_ssdisp_n_20),
        .\status_mode_reg[1]_3 (\FSM_onehot_state[9]_i_2_n_0 ),
        .\status_mode_reg[1]_4 (\FSM_onehot_state[2]_i_3_n_0 ),
        .\status_mode_reg[2] (\FSM_onehot_state_reg[2]_0 ),
        .\status_mode_reg[2]_0 (my_ssdisp_n_7),
        .\status_mode_reg[2]_1 (my_ssdisp_n_16),
        .\status_mode_reg[2]_2 (my_ssdisp_n_18),
        .\status_mode_reg[2]_3 (my_ssdisp_n_15),
        .\status_mode_reg[2]_4 (my_ssdisp_n_31),
        .\status_mode_reg[2]_5 (my_ssdisp_n_9),
        .\status_mode_reg[2]_6 (my_ssdisp_n_34),
        .\status_mode_reg[2]_7 (\FSM_onehot_state[1]_i_2_n_0 ),
        .\status_weight_reg[0] (my_ssdisp_n_17),
        .\status_weight_reg[0]_0 (my_ssdisp_n_10),
        .\status_weight_reg[1] (my_ssdisp_n_1),
        .\status_weight_reg[1]_0 (my_ssdisp_n_33),
        .\timer_set_reg[3]_0 (\timer_set_reg[3] ));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    \seg_OBUF[6]_inst_i_9 
       (.I0(\water_line_reg[0] ),
        .I1(\FSM_onehot_state_reg_n_0_[5] ),
        .I2(\FSM_onehot_state_reg_n_0_[4] ),
        .I3(\FSM_onehot_state_reg_n_0_[6] ),
        .I4(\FSM_onehot_state_reg_n_0_[7] ),
        .I5(state_OBUF[3]),
        .O(\seg_OBUF[6]_inst_i_9_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \state_1_reg[0] 
       (.C(CLK),
        .CE(1'b1),
        .D(state_OBUF[0]),
        .Q(state_1[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_1_reg[1] 
       (.C(CLK),
        .CE(1'b1),
        .D(state_OBUF[1]),
        .Q(state_1[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_1_reg[2] 
       (.C(CLK),
        .CE(1'b1),
        .D(state_OBUF[2]),
        .Q(state_1[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_1_reg[3] 
       (.C(CLK),
        .CE(1'b1),
        .D(state_OBUF[3]),
        .Q(state_1[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_2_reg[0] 
       (.C(CLK),
        .CE(1'b1),
        .D(state_1[0]),
        .Q(state_2[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_2_reg[1] 
       (.C(CLK),
        .CE(1'b1),
        .D(state_1[1]),
        .Q(state_2[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_2_reg[2] 
       (.C(CLK),
        .CE(1'b1),
        .D(state_1[2]),
        .Q(state_2[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_2_reg[3] 
       (.C(CLK),
        .CE(1'b1),
        .D(state_1[3]),
        .Q(state_2[3]),
        .R(1'b0));
  LUT2 #(
    .INIT(4'h6)) 
    \status_mode[0]_i_1 
       (.I0(\FSM_onehot_state_reg_n_0_[0] ),
        .I1(\status_mode_reg_n_0_[0] ),
        .O(\status_mode[0]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h4C6C)) 
    \status_mode[1]_i_1 
       (.I0(\FSM_onehot_state_reg_n_0_[0] ),
        .I1(\status_mode_reg_n_0_[1] ),
        .I2(\status_mode_reg_n_0_[0] ),
        .I3(\FSM_onehot_state_reg[2]_0 ),
        .O(\status_mode[1]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h5F80)) 
    \status_mode[2]_i_1 
       (.I0(\FSM_onehot_state_reg_n_0_[0] ),
        .I1(\status_mode_reg_n_0_[1] ),
        .I2(\status_mode_reg_n_0_[0] ),
        .I3(\FSM_onehot_state_reg[2]_0 ),
        .O(\status_mode[2]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \status_mode_reg[0] 
       (.C(mode_change_IBUF_BUFG),
        .CE(1'b1),
        .D(\status_mode[0]_i_1_n_0 ),
        .Q(\status_mode_reg_n_0_[0] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \status_mode_reg[1] 
       (.C(mode_change_IBUF_BUFG),
        .CE(1'b1),
        .D(\status_mode[1]_i_1_n_0 ),
        .Q(\status_mode_reg_n_0_[1] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \status_mode_reg[2] 
       (.C(mode_change_IBUF_BUFG),
        .CE(1'b1),
        .D(\status_mode[2]_i_1_n_0 ),
        .Q(\FSM_onehot_state_reg[2]_0 ),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \status_weight[0]_i_1 
       (.I0(\status_weight_reg_n_0_[0] ),
        .O(\status_weight[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \status_weight[1]_i_1 
       (.I0(\status_weight_reg_n_0_[1] ),
        .I1(\status_weight_reg_n_0_[0] ),
        .O(\status_weight[1]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \status_weight_reg[0] 
       (.C(weight_change),
        .CE(\FSM_onehot_state_reg_n_0_[0] ),
        .D(\status_weight[0]_i_1_n_0 ),
        .Q(\status_weight_reg_n_0_[0] ),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \status_weight_reg[1] 
       (.C(weight_change),
        .CE(\FSM_onehot_state_reg_n_0_[0] ),
        .D(\status_weight[1]_i_1_n_0 ),
        .Q(\status_weight_reg_n_0_[1] ),
        .R(1'b0));
endmodule

module counter
   (\seg[0] ,
    Q,
    \seg[0]_0 ,
    an_OBUF,
    \seg[0]_1 ,
    \seg[0]_2 ,
    \seg[0]_3 ,
    \seg[0]_4 ,
    \status_mode_reg[2] ,
    \FSM_onehot_state_reg[6] ,
    \FSM_onehot_state_reg[7] ,
    \FSM_onehot_state_reg[9] ,
    CLK);
  output \seg[0] ;
  output [2:0]Q;
  output \seg[0]_0 ;
  output [5:0]an_OBUF;
  output \seg[0]_1 ;
  output \seg[0]_2 ;
  output \seg[0]_3 ;
  output \seg[0]_4 ;
  input \status_mode_reg[2] ;
  input \FSM_onehot_state_reg[6] ;
  input \FSM_onehot_state_reg[7] ;
  input [0:0]\FSM_onehot_state_reg[9] ;
  input CLK;

  wire CLK;
  wire \FSM_onehot_state_reg[6] ;
  wire \FSM_onehot_state_reg[7] ;
  wire [0:0]\FSM_onehot_state_reg[9] ;
  wire [2:0]Q;
  wire [5:0]an_OBUF;
  wire \num[0]_i_1_n_0 ;
  wire \num[1]_i_1_n_0 ;
  wire \num[2]_i_1_n_0 ;
  wire \seg[0] ;
  wire \seg[0]_0 ;
  wire \seg[0]_1 ;
  wire \seg[0]_2 ;
  wire \seg[0]_3 ;
  wire \seg[0]_4 ;
  wire \status_mode_reg[2] ;

  LUT3 #(
    .INIT(8'hFE)) 
    \an_OBUF[0]_inst_i_1 
       (.I0(Q[2]),
        .I1(Q[1]),
        .I2(Q[0]),
        .O(an_OBUF[0]));
  LUT3 #(
    .INIT(8'hFB)) 
    \an_OBUF[1]_inst_i_1 
       (.I0(Q[2]),
        .I1(Q[0]),
        .I2(Q[1]),
        .O(an_OBUF[1]));
  LUT3 #(
    .INIT(8'hBF)) 
    \an_OBUF[3]_inst_i_1 
       (.I0(Q[2]),
        .I1(Q[0]),
        .I2(Q[1]),
        .O(an_OBUF[2]));
  LUT3 #(
    .INIT(8'hFD)) 
    \an_OBUF[4]_inst_i_1 
       (.I0(Q[2]),
        .I1(Q[1]),
        .I2(Q[0]),
        .O(an_OBUF[3]));
  LUT3 #(
    .INIT(8'hDF)) 
    \an_OBUF[6]_inst_i_1 
       (.I0(Q[2]),
        .I1(Q[0]),
        .I2(Q[1]),
        .O(an_OBUF[4]));
  LUT3 #(
    .INIT(8'h7F)) 
    \an_OBUF[7]_inst_i_1 
       (.I0(Q[2]),
        .I1(Q[0]),
        .I2(Q[1]),
        .O(an_OBUF[5]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \num[0]_i_1 
       (.I0(Q[0]),
        .O(\num[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \num[1]_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(\num[1]_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h6A)) 
    \num[2]_i_1 
       (.I0(Q[2]),
        .I1(Q[1]),
        .I2(Q[0]),
        .O(\num[2]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \num_reg[0] 
       (.C(CLK),
        .CE(1'b1),
        .D(\num[0]_i_1_n_0 ),
        .Q(Q[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \num_reg[1] 
       (.C(CLK),
        .CE(1'b1),
        .D(\num[1]_i_1_n_0 ),
        .Q(Q[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \num_reg[2] 
       (.C(CLK),
        .CE(1'b1),
        .D(\num[2]_i_1_n_0 ),
        .Q(Q[2]),
        .R(1'b0));
  LUT6 #(
    .INIT(64'hFEFFFEFEFEFEFEFE)) 
    \seg_OBUF[6]_inst_i_19 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(\status_mode_reg[2] ),
        .I4(\FSM_onehot_state_reg[6] ),
        .I5(\FSM_onehot_state_reg[7] ),
        .O(\seg[0] ));
  LUT2 #(
    .INIT(4'h1)) 
    \seg_OBUF[6]_inst_i_21 
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(\seg[0]_4 ));
  LUT4 #(
    .INIT(16'hEAAA)) 
    \seg_OBUF[6]_inst_i_22 
       (.I0(Q[2]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(\FSM_onehot_state_reg[9] ),
        .O(\seg[0]_1 ));
  LUT4 #(
    .INIT(16'h002A)) 
    \seg_OBUF[6]_inst_i_23 
       (.I0(Q[0]),
        .I1(\FSM_onehot_state_reg[6] ),
        .I2(\FSM_onehot_state_reg[7] ),
        .I3(Q[1]),
        .O(\seg[0]_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \seg_OBUF[6]_inst_i_30 
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(\seg[0]_3 ));
  LUT3 #(
    .INIT(8'h08)) 
    \seg_OBUF[6]_inst_i_36 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(Q[2]),
        .O(\seg[0]_2 ));
endmodule

module divider
   (temp_OBUF,
    CLK,
    clk);
  output temp_OBUF;
  output CLK;
  input clk;

  wire CLK;
  wire clear;
  wire clk;
  wire clk_F_i_1_n_0;
  wire clk_N_i_1_n_0;
  wire clk_N_i_2_n_0;
  wire \counter[0]_i_14_n_0 ;
  wire \counter[0]_i_22_n_0 ;
  wire \counter[0]_i_23_n_0 ;
  wire \counter[0]_i_3_n_0 ;
  wire \counter[0]_i_4_n_0 ;
  wire \counter[0]_i_5_n_0 ;
  wire \counter[0]_i_6_n_0 ;
  wire \counter[0]_i_7_n_0 ;
  wire \counter[0]_i_8_n_0 ;
  wire \counter_f[0]_i_10_n_0 ;
  wire \counter_f[0]_i_11_n_0 ;
  wire \counter_f[0]_i_12_n_0 ;
  wire \counter_f[0]_i_13_n_0 ;
  wire \counter_f[0]_i_1_n_0 ;
  wire \counter_f[0]_i_26_n_0 ;
  wire \counter_f[0]_i_27_n_0 ;
  wire \counter_f[0]_i_3_n_0 ;
  wire \counter_f[0]_i_6_n_0 ;
  wire [31:0]counter_f_reg;
  wire \counter_f_reg[0]_i_14_n_0 ;
  wire \counter_f_reg[0]_i_14_n_4 ;
  wire \counter_f_reg[0]_i_14_n_5 ;
  wire \counter_f_reg[0]_i_14_n_6 ;
  wire \counter_f_reg[0]_i_14_n_7 ;
  wire \counter_f_reg[0]_i_15_n_0 ;
  wire \counter_f_reg[0]_i_15_n_4 ;
  wire \counter_f_reg[0]_i_15_n_5 ;
  wire \counter_f_reg[0]_i_15_n_6 ;
  wire \counter_f_reg[0]_i_15_n_7 ;
  wire \counter_f_reg[0]_i_16_n_0 ;
  wire \counter_f_reg[0]_i_16_n_4 ;
  wire \counter_f_reg[0]_i_16_n_5 ;
  wire \counter_f_reg[0]_i_16_n_6 ;
  wire \counter_f_reg[0]_i_16_n_7 ;
  wire \counter_f_reg[0]_i_17_n_0 ;
  wire \counter_f_reg[0]_i_17_n_4 ;
  wire \counter_f_reg[0]_i_17_n_5 ;
  wire \counter_f_reg[0]_i_17_n_6 ;
  wire \counter_f_reg[0]_i_17_n_7 ;
  wire \counter_f_reg[0]_i_28_n_5 ;
  wire \counter_f_reg[0]_i_28_n_6 ;
  wire \counter_f_reg[0]_i_28_n_7 ;
  wire \counter_f_reg[0]_i_2_n_0 ;
  wire \counter_f_reg[0]_i_2_n_4 ;
  wire \counter_f_reg[0]_i_2_n_5 ;
  wire \counter_f_reg[0]_i_2_n_6 ;
  wire \counter_f_reg[0]_i_2_n_7 ;
  wire \counter_f_reg[0]_i_41_n_0 ;
  wire \counter_f_reg[0]_i_41_n_4 ;
  wire \counter_f_reg[0]_i_41_n_5 ;
  wire \counter_f_reg[0]_i_41_n_6 ;
  wire \counter_f_reg[0]_i_41_n_7 ;
  wire \counter_f_reg[0]_i_4_n_0 ;
  wire \counter_f_reg[0]_i_4_n_4 ;
  wire \counter_f_reg[0]_i_4_n_5 ;
  wire \counter_f_reg[0]_i_4_n_6 ;
  wire \counter_f_reg[0]_i_4_n_7 ;
  wire \counter_f_reg[0]_i_5_n_0 ;
  wire \counter_f_reg[0]_i_5_n_4 ;
  wire \counter_f_reg[0]_i_5_n_5 ;
  wire \counter_f_reg[0]_i_5_n_6 ;
  wire \counter_f_reg[0]_i_5_n_7 ;
  wire \counter_f_reg[12]_i_1_n_0 ;
  wire \counter_f_reg[12]_i_1_n_4 ;
  wire \counter_f_reg[12]_i_1_n_5 ;
  wire \counter_f_reg[12]_i_1_n_6 ;
  wire \counter_f_reg[12]_i_1_n_7 ;
  wire \counter_f_reg[16]_i_1_n_0 ;
  wire \counter_f_reg[16]_i_1_n_4 ;
  wire \counter_f_reg[16]_i_1_n_5 ;
  wire \counter_f_reg[16]_i_1_n_6 ;
  wire \counter_f_reg[16]_i_1_n_7 ;
  wire \counter_f_reg[20]_i_1_n_0 ;
  wire \counter_f_reg[20]_i_1_n_4 ;
  wire \counter_f_reg[20]_i_1_n_5 ;
  wire \counter_f_reg[20]_i_1_n_6 ;
  wire \counter_f_reg[20]_i_1_n_7 ;
  wire \counter_f_reg[24]_i_1_n_0 ;
  wire \counter_f_reg[24]_i_1_n_4 ;
  wire \counter_f_reg[24]_i_1_n_5 ;
  wire \counter_f_reg[24]_i_1_n_6 ;
  wire \counter_f_reg[24]_i_1_n_7 ;
  wire \counter_f_reg[28]_i_1_n_4 ;
  wire \counter_f_reg[28]_i_1_n_5 ;
  wire \counter_f_reg[28]_i_1_n_6 ;
  wire \counter_f_reg[28]_i_1_n_7 ;
  wire \counter_f_reg[4]_i_1_n_0 ;
  wire \counter_f_reg[4]_i_1_n_4 ;
  wire \counter_f_reg[4]_i_1_n_5 ;
  wire \counter_f_reg[4]_i_1_n_6 ;
  wire \counter_f_reg[4]_i_1_n_7 ;
  wire \counter_f_reg[8]_i_1_n_0 ;
  wire \counter_f_reg[8]_i_1_n_4 ;
  wire \counter_f_reg[8]_i_1_n_5 ;
  wire \counter_f_reg[8]_i_1_n_6 ;
  wire \counter_f_reg[8]_i_1_n_7 ;
  wire [31:0]counter_reg;
  wire \counter_reg[0]_i_13_n_0 ;
  wire \counter_reg[0]_i_15_n_0 ;
  wire \counter_reg[0]_i_16_n_0 ;
  wire \counter_reg[0]_i_17_n_0 ;
  wire \counter_reg[0]_i_18_n_0 ;
  wire \counter_reg[0]_i_19_n_0 ;
  wire \counter_reg[0]_i_21_n_0 ;
  wire \counter_reg[0]_i_2_n_0 ;
  wire \counter_reg[0]_i_2_n_4 ;
  wire \counter_reg[0]_i_2_n_5 ;
  wire \counter_reg[0]_i_2_n_6 ;
  wire \counter_reg[0]_i_2_n_7 ;
  wire \counter_reg[12]_i_1_n_0 ;
  wire \counter_reg[12]_i_1_n_4 ;
  wire \counter_reg[12]_i_1_n_5 ;
  wire \counter_reg[12]_i_1_n_6 ;
  wire \counter_reg[12]_i_1_n_7 ;
  wire \counter_reg[16]_i_1_n_0 ;
  wire \counter_reg[16]_i_1_n_4 ;
  wire \counter_reg[16]_i_1_n_5 ;
  wire \counter_reg[16]_i_1_n_6 ;
  wire \counter_reg[16]_i_1_n_7 ;
  wire \counter_reg[20]_i_1_n_0 ;
  wire \counter_reg[20]_i_1_n_4 ;
  wire \counter_reg[20]_i_1_n_5 ;
  wire \counter_reg[20]_i_1_n_6 ;
  wire \counter_reg[20]_i_1_n_7 ;
  wire \counter_reg[24]_i_1_n_0 ;
  wire \counter_reg[24]_i_1_n_4 ;
  wire \counter_reg[24]_i_1_n_5 ;
  wire \counter_reg[24]_i_1_n_6 ;
  wire \counter_reg[24]_i_1_n_7 ;
  wire \counter_reg[28]_i_1_n_4 ;
  wire \counter_reg[28]_i_1_n_5 ;
  wire \counter_reg[28]_i_1_n_6 ;
  wire \counter_reg[28]_i_1_n_7 ;
  wire \counter_reg[4]_i_1_n_0 ;
  wire \counter_reg[4]_i_1_n_4 ;
  wire \counter_reg[4]_i_1_n_5 ;
  wire \counter_reg[4]_i_1_n_6 ;
  wire \counter_reg[4]_i_1_n_7 ;
  wire \counter_reg[8]_i_1_n_0 ;
  wire \counter_reg[8]_i_1_n_4 ;
  wire \counter_reg[8]_i_1_n_5 ;
  wire \counter_reg[8]_i_1_n_6 ;
  wire \counter_reg[8]_i_1_n_7 ;
  wire [31:0]p_0_in;
  wire temp_OBUF;
  wire [2:0]\NLW_counter_f_reg[0]_i_14_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[0]_i_15_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[0]_i_16_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[0]_i_17_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[0]_i_2_CO_UNCONNECTED ;
  wire [3:0]\NLW_counter_f_reg[0]_i_28_CO_UNCONNECTED ;
  wire [3:3]\NLW_counter_f_reg[0]_i_28_O_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[0]_i_4_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[0]_i_41_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[0]_i_5_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[12]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[16]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[20]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[24]_i_1_CO_UNCONNECTED ;
  wire [3:0]\NLW_counter_f_reg[28]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[4]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_f_reg[8]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[0]_i_13_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[0]_i_15_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[0]_i_16_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[0]_i_17_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[0]_i_18_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[0]_i_19_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[0]_i_2_CO_UNCONNECTED ;
  wire [3:0]\NLW_counter_reg[0]_i_20_CO_UNCONNECTED ;
  wire [3:3]\NLW_counter_reg[0]_i_20_O_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[0]_i_21_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[12]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[16]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[20]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[24]_i_1_CO_UNCONNECTED ;
  wire [3:0]\NLW_counter_reg[28]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[4]_i_1_CO_UNCONNECTED ;
  wire [2:0]\NLW_counter_reg[8]_i_1_CO_UNCONNECTED ;

  LUT6 #(
    .INIT(64'h00005557FFFFAAA8)) 
    clk_F_i_1
       (.I0(\counter_f_reg[0]_i_5_n_6 ),
        .I1(\counter_f[0]_i_6_n_0 ),
        .I2(\counter_f_reg[0]_i_5_n_7 ),
        .I3(\counter_f_reg[0]_i_4_n_4 ),
        .I4(\counter_f[0]_i_3_n_0 ),
        .I5(CLK),
        .O(clk_F_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    clk_F_reg
       (.C(clk),
        .CE(1'b1),
        .D(clk_F_i_1_n_0),
        .Q(CLK),
        .R(1'b0));
  LUT6 #(
    .INIT(64'h0202020FFDFDFDF0)) 
    clk_N_i_1
       (.I0(\counter[0]_i_8_n_0 ),
        .I1(\counter[0]_i_7_n_0 ),
        .I2(\counter[0]_i_6_n_0 ),
        .I3(clk_N_i_2_n_0),
        .I4(\counter[0]_i_3_n_0 ),
        .I5(temp_OBUF),
        .O(clk_N_i_1_n_0));
  LUT4 #(
    .INIT(16'hFEFF)) 
    clk_N_i_2
       (.I0(p_0_in[20]),
        .I1(p_0_in[19]),
        .I2(p_0_in[18]),
        .I3(\counter[0]_i_4_n_0 ),
        .O(clk_N_i_2_n_0));
  FDRE #(
    .INIT(1'b0)) 
    clk_N_reg
       (.C(clk),
        .CE(1'b1),
        .D(clk_N_i_1_n_0),
        .Q(temp_OBUF),
        .R(1'b0));
  LUT6 #(
    .INIT(64'hFFBFFF00FFBFFFBF)) 
    \counter[0]_i_1 
       (.I0(\counter[0]_i_3_n_0 ),
        .I1(\counter[0]_i_4_n_0 ),
        .I2(\counter[0]_i_5_n_0 ),
        .I3(\counter[0]_i_6_n_0 ),
        .I4(\counter[0]_i_7_n_0 ),
        .I5(\counter[0]_i_8_n_0 ),
        .O(clear));
  LUT1 #(
    .INIT(2'h1)) 
    \counter[0]_i_12 
       (.I0(counter_reg[0]),
        .O(p_0_in[0]));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \counter[0]_i_14 
       (.I0(p_0_in[1]),
        .I1(p_0_in[4]),
        .I2(p_0_in[3]),
        .I3(p_0_in[5]),
        .I4(p_0_in[8]),
        .I5(p_0_in[7]),
        .O(\counter[0]_i_14_n_0 ));
  LUT5 #(
    .INIT(32'hFFFEFEFE)) 
    \counter[0]_i_22 
       (.I0(p_0_in[16]),
        .I1(p_0_in[15]),
        .I2(p_0_in[13]),
        .I3(p_0_in[12]),
        .I4(p_0_in[11]),
        .O(\counter[0]_i_22_n_0 ));
  LUT4 #(
    .INIT(16'h5557)) 
    \counter[0]_i_23 
       (.I0(p_0_in[17]),
        .I1(p_0_in[16]),
        .I2(p_0_in[15]),
        .I3(p_0_in[14]),
        .O(\counter[0]_i_23_n_0 ));
  LUT5 #(
    .INIT(32'hAAAAA8AA)) 
    \counter[0]_i_3 
       (.I0(p_0_in[9]),
        .I1(\counter[0]_i_14_n_0 ),
        .I2(p_0_in[2]),
        .I3(counter_reg[0]),
        .I4(p_0_in[6]),
        .O(\counter[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \counter[0]_i_4 
       (.I0(p_0_in[16]),
        .I1(p_0_in[15]),
        .I2(p_0_in[13]),
        .I3(p_0_in[24]),
        .I4(p_0_in[23]),
        .I5(p_0_in[10]),
        .O(\counter[0]_i_4_n_0 ));
  LUT3 #(
    .INIT(8'h01)) 
    \counter[0]_i_5 
       (.I0(p_0_in[18]),
        .I1(p_0_in[19]),
        .I2(p_0_in[20]),
        .O(\counter[0]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \counter[0]_i_6 
       (.I0(p_0_in[30]),
        .I1(p_0_in[29]),
        .I2(p_0_in[27]),
        .I3(p_0_in[31]),
        .I4(p_0_in[26]),
        .I5(p_0_in[28]),
        .O(\counter[0]_i_6_n_0 ));
  LUT3 #(
    .INIT(8'hA8)) 
    \counter[0]_i_7 
       (.I0(p_0_in[25]),
        .I1(p_0_in[23]),
        .I2(p_0_in[24]),
        .O(\counter[0]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hD0FFFFFFFFFFFFFF)) 
    \counter[0]_i_8 
       (.I0(\counter[0]_i_22_n_0 ),
        .I1(\counter[0]_i_23_n_0 ),
        .I2(\counter[0]_i_5_n_0 ),
        .I3(p_0_in[25]),
        .I4(p_0_in[21]),
        .I5(p_0_in[22]),
        .O(\counter[0]_i_8_n_0 ));
  LUT5 #(
    .INIT(32'hFFFEAAAA)) 
    \counter_f[0]_i_1 
       (.I0(\counter_f[0]_i_3_n_0 ),
        .I1(\counter_f_reg[0]_i_4_n_4 ),
        .I2(\counter_f_reg[0]_i_5_n_7 ),
        .I3(\counter_f[0]_i_6_n_0 ),
        .I4(\counter_f_reg[0]_i_5_n_6 ),
        .O(\counter_f[0]_i_1_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \counter_f[0]_i_10 
       (.I0(counter_f_reg[0]),
        .O(\counter_f[0]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \counter_f[0]_i_11 
       (.I0(\counter_f_reg[0]_i_14_n_5 ),
        .I1(\counter_f_reg[0]_i_14_n_7 ),
        .I2(\counter_f_reg[0]_i_16_n_7 ),
        .I3(\counter_f_reg[0]_i_16_n_5 ),
        .I4(\counter_f_reg[0]_i_5_n_4 ),
        .I5(\counter_f_reg[0]_i_5_n_5 ),
        .O(\counter_f[0]_i_11_n_0 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \counter_f[0]_i_12 
       (.I0(\counter_f_reg[0]_i_28_n_5 ),
        .I1(\counter_f_reg[0]_i_14_n_4 ),
        .I2(\counter_f_reg[0]_i_28_n_6 ),
        .I3(\counter_f_reg[0]_i_15_n_7 ),
        .O(\counter_f[0]_i_12_n_0 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \counter_f[0]_i_13 
       (.I0(\counter_f_reg[0]_i_28_n_7 ),
        .I1(\counter_f_reg[0]_i_15_n_5 ),
        .I2(\counter_f_reg[0]_i_15_n_4 ),
        .I3(\counter_f_reg[0]_i_16_n_4 ),
        .O(\counter_f[0]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAAAAA8A)) 
    \counter_f[0]_i_26 
       (.I0(\counter_f_reg[0]_i_17_n_7 ),
        .I1(\counter_f_reg[0]_i_41_n_5 ),
        .I2(counter_f_reg[0]),
        .I3(\counter_f_reg[0]_i_41_n_4 ),
        .I4(\counter_f_reg[0]_i_41_n_7 ),
        .I5(\counter_f_reg[0]_i_41_n_6 ),
        .O(\counter_f[0]_i_26_n_0 ));
  LUT3 #(
    .INIT(8'h7F)) 
    \counter_f[0]_i_27 
       (.I0(\counter_f_reg[0]_i_4_n_7 ),
        .I1(\counter_f_reg[0]_i_4_n_5 ),
        .I2(\counter_f_reg[0]_i_4_n_6 ),
        .O(\counter_f[0]_i_27_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \counter_f[0]_i_3 
       (.I0(\counter_f[0]_i_11_n_0 ),
        .I1(\counter_f[0]_i_12_n_0 ),
        .I2(\counter_f[0]_i_13_n_0 ),
        .I3(\counter_f_reg[0]_i_14_n_6 ),
        .I4(\counter_f_reg[0]_i_15_n_6 ),
        .I5(\counter_f_reg[0]_i_16_n_6 ),
        .O(\counter_f[0]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h0000FFFE)) 
    \counter_f[0]_i_6 
       (.I0(\counter_f[0]_i_26_n_0 ),
        .I1(\counter_f_reg[0]_i_17_n_5 ),
        .I2(\counter_f_reg[0]_i_17_n_4 ),
        .I3(\counter_f_reg[0]_i_17_n_6 ),
        .I4(\counter_f[0]_i_27_n_0 ),
        .O(\counter_f[0]_i_6_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[0] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[0]_i_2_n_7 ),
        .Q(counter_f_reg[0]),
        .R(\counter_f[0]_i_1_n_0 ));
  CARRY4 \counter_f_reg[0]_i_14 
       (.CI(\counter_f_reg[0]_i_16_n_0 ),
        .CO({\counter_f_reg[0]_i_14_n_0 ,\NLW_counter_f_reg[0]_i_14_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[0]_i_14_n_4 ,\counter_f_reg[0]_i_14_n_5 ,\counter_f_reg[0]_i_14_n_6 ,\counter_f_reg[0]_i_14_n_7 }),
        .S(counter_f_reg[24:21]));
  CARRY4 \counter_f_reg[0]_i_15 
       (.CI(\counter_f_reg[0]_i_14_n_0 ),
        .CO({\counter_f_reg[0]_i_15_n_0 ,\NLW_counter_f_reg[0]_i_15_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[0]_i_15_n_4 ,\counter_f_reg[0]_i_15_n_5 ,\counter_f_reg[0]_i_15_n_6 ,\counter_f_reg[0]_i_15_n_7 }),
        .S(counter_f_reg[28:25]));
  CARRY4 \counter_f_reg[0]_i_16 
       (.CI(\counter_f_reg[0]_i_5_n_0 ),
        .CO({\counter_f_reg[0]_i_16_n_0 ,\NLW_counter_f_reg[0]_i_16_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[0]_i_16_n_4 ,\counter_f_reg[0]_i_16_n_5 ,\counter_f_reg[0]_i_16_n_6 ,\counter_f_reg[0]_i_16_n_7 }),
        .S(counter_f_reg[20:17]));
  CARRY4 \counter_f_reg[0]_i_17 
       (.CI(\counter_f_reg[0]_i_41_n_0 ),
        .CO({\counter_f_reg[0]_i_17_n_0 ,\NLW_counter_f_reg[0]_i_17_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[0]_i_17_n_4 ,\counter_f_reg[0]_i_17_n_5 ,\counter_f_reg[0]_i_17_n_6 ,\counter_f_reg[0]_i_17_n_7 }),
        .S(counter_f_reg[8:5]));
  CARRY4 \counter_f_reg[0]_i_2 
       (.CI(1'b0),
        .CO({\counter_f_reg[0]_i_2_n_0 ,\NLW_counter_f_reg[0]_i_2_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b1}),
        .O({\counter_f_reg[0]_i_2_n_4 ,\counter_f_reg[0]_i_2_n_5 ,\counter_f_reg[0]_i_2_n_6 ,\counter_f_reg[0]_i_2_n_7 }),
        .S({counter_f_reg[3:1],\counter_f[0]_i_10_n_0 }));
  CARRY4 \counter_f_reg[0]_i_28 
       (.CI(\counter_f_reg[0]_i_15_n_0 ),
        .CO(\NLW_counter_f_reg[0]_i_28_CO_UNCONNECTED [3:0]),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_counter_f_reg[0]_i_28_O_UNCONNECTED [3],\counter_f_reg[0]_i_28_n_5 ,\counter_f_reg[0]_i_28_n_6 ,\counter_f_reg[0]_i_28_n_7 }),
        .S({1'b0,counter_f_reg[31:29]}));
  CARRY4 \counter_f_reg[0]_i_4 
       (.CI(\counter_f_reg[0]_i_17_n_0 ),
        .CO({\counter_f_reg[0]_i_4_n_0 ,\NLW_counter_f_reg[0]_i_4_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[0]_i_4_n_4 ,\counter_f_reg[0]_i_4_n_5 ,\counter_f_reg[0]_i_4_n_6 ,\counter_f_reg[0]_i_4_n_7 }),
        .S(counter_f_reg[12:9]));
  CARRY4 \counter_f_reg[0]_i_41 
       (.CI(1'b0),
        .CO({\counter_f_reg[0]_i_41_n_0 ,\NLW_counter_f_reg[0]_i_41_CO_UNCONNECTED [2:0]}),
        .CYINIT(counter_f_reg[0]),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[0]_i_41_n_4 ,\counter_f_reg[0]_i_41_n_5 ,\counter_f_reg[0]_i_41_n_6 ,\counter_f_reg[0]_i_41_n_7 }),
        .S(counter_f_reg[4:1]));
  CARRY4 \counter_f_reg[0]_i_5 
       (.CI(\counter_f_reg[0]_i_4_n_0 ),
        .CO({\counter_f_reg[0]_i_5_n_0 ,\NLW_counter_f_reg[0]_i_5_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[0]_i_5_n_4 ,\counter_f_reg[0]_i_5_n_5 ,\counter_f_reg[0]_i_5_n_6 ,\counter_f_reg[0]_i_5_n_7 }),
        .S(counter_f_reg[16:13]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[10] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[8]_i_1_n_5 ),
        .Q(counter_f_reg[10]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[11] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[8]_i_1_n_4 ),
        .Q(counter_f_reg[11]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[12] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[12]_i_1_n_7 ),
        .Q(counter_f_reg[12]),
        .R(\counter_f[0]_i_1_n_0 ));
  CARRY4 \counter_f_reg[12]_i_1 
       (.CI(\counter_f_reg[8]_i_1_n_0 ),
        .CO({\counter_f_reg[12]_i_1_n_0 ,\NLW_counter_f_reg[12]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[12]_i_1_n_4 ,\counter_f_reg[12]_i_1_n_5 ,\counter_f_reg[12]_i_1_n_6 ,\counter_f_reg[12]_i_1_n_7 }),
        .S(counter_f_reg[15:12]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[13] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[12]_i_1_n_6 ),
        .Q(counter_f_reg[13]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[14] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[12]_i_1_n_5 ),
        .Q(counter_f_reg[14]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[15] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[12]_i_1_n_4 ),
        .Q(counter_f_reg[15]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[16] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[16]_i_1_n_7 ),
        .Q(counter_f_reg[16]),
        .R(\counter_f[0]_i_1_n_0 ));
  CARRY4 \counter_f_reg[16]_i_1 
       (.CI(\counter_f_reg[12]_i_1_n_0 ),
        .CO({\counter_f_reg[16]_i_1_n_0 ,\NLW_counter_f_reg[16]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[16]_i_1_n_4 ,\counter_f_reg[16]_i_1_n_5 ,\counter_f_reg[16]_i_1_n_6 ,\counter_f_reg[16]_i_1_n_7 }),
        .S(counter_f_reg[19:16]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[17] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[16]_i_1_n_6 ),
        .Q(counter_f_reg[17]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[18] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[16]_i_1_n_5 ),
        .Q(counter_f_reg[18]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[19] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[16]_i_1_n_4 ),
        .Q(counter_f_reg[19]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[1] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[0]_i_2_n_6 ),
        .Q(counter_f_reg[1]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[20] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[20]_i_1_n_7 ),
        .Q(counter_f_reg[20]),
        .R(\counter_f[0]_i_1_n_0 ));
  CARRY4 \counter_f_reg[20]_i_1 
       (.CI(\counter_f_reg[16]_i_1_n_0 ),
        .CO({\counter_f_reg[20]_i_1_n_0 ,\NLW_counter_f_reg[20]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[20]_i_1_n_4 ,\counter_f_reg[20]_i_1_n_5 ,\counter_f_reg[20]_i_1_n_6 ,\counter_f_reg[20]_i_1_n_7 }),
        .S(counter_f_reg[23:20]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[21] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[20]_i_1_n_6 ),
        .Q(counter_f_reg[21]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[22] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[20]_i_1_n_5 ),
        .Q(counter_f_reg[22]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[23] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[20]_i_1_n_4 ),
        .Q(counter_f_reg[23]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[24] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[24]_i_1_n_7 ),
        .Q(counter_f_reg[24]),
        .R(\counter_f[0]_i_1_n_0 ));
  CARRY4 \counter_f_reg[24]_i_1 
       (.CI(\counter_f_reg[20]_i_1_n_0 ),
        .CO({\counter_f_reg[24]_i_1_n_0 ,\NLW_counter_f_reg[24]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[24]_i_1_n_4 ,\counter_f_reg[24]_i_1_n_5 ,\counter_f_reg[24]_i_1_n_6 ,\counter_f_reg[24]_i_1_n_7 }),
        .S(counter_f_reg[27:24]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[25] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[24]_i_1_n_6 ),
        .Q(counter_f_reg[25]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[26] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[24]_i_1_n_5 ),
        .Q(counter_f_reg[26]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[27] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[24]_i_1_n_4 ),
        .Q(counter_f_reg[27]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[28] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[28]_i_1_n_7 ),
        .Q(counter_f_reg[28]),
        .R(\counter_f[0]_i_1_n_0 ));
  CARRY4 \counter_f_reg[28]_i_1 
       (.CI(\counter_f_reg[24]_i_1_n_0 ),
        .CO(\NLW_counter_f_reg[28]_i_1_CO_UNCONNECTED [3:0]),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[28]_i_1_n_4 ,\counter_f_reg[28]_i_1_n_5 ,\counter_f_reg[28]_i_1_n_6 ,\counter_f_reg[28]_i_1_n_7 }),
        .S(counter_f_reg[31:28]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[29] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[28]_i_1_n_6 ),
        .Q(counter_f_reg[29]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[2] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[0]_i_2_n_5 ),
        .Q(counter_f_reg[2]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[30] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[28]_i_1_n_5 ),
        .Q(counter_f_reg[30]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[31] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[28]_i_1_n_4 ),
        .Q(counter_f_reg[31]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[3] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[0]_i_2_n_4 ),
        .Q(counter_f_reg[3]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[4] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[4]_i_1_n_7 ),
        .Q(counter_f_reg[4]),
        .R(\counter_f[0]_i_1_n_0 ));
  CARRY4 \counter_f_reg[4]_i_1 
       (.CI(\counter_f_reg[0]_i_2_n_0 ),
        .CO({\counter_f_reg[4]_i_1_n_0 ,\NLW_counter_f_reg[4]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[4]_i_1_n_4 ,\counter_f_reg[4]_i_1_n_5 ,\counter_f_reg[4]_i_1_n_6 ,\counter_f_reg[4]_i_1_n_7 }),
        .S(counter_f_reg[7:4]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[5] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[4]_i_1_n_6 ),
        .Q(counter_f_reg[5]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[6] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[4]_i_1_n_5 ),
        .Q(counter_f_reg[6]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[7] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[4]_i_1_n_4 ),
        .Q(counter_f_reg[7]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[8] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[8]_i_1_n_7 ),
        .Q(counter_f_reg[8]),
        .R(\counter_f[0]_i_1_n_0 ));
  CARRY4 \counter_f_reg[8]_i_1 
       (.CI(\counter_f_reg[4]_i_1_n_0 ),
        .CO({\counter_f_reg[8]_i_1_n_0 ,\NLW_counter_f_reg[8]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_f_reg[8]_i_1_n_4 ,\counter_f_reg[8]_i_1_n_5 ,\counter_f_reg[8]_i_1_n_6 ,\counter_f_reg[8]_i_1_n_7 }),
        .S(counter_f_reg[11:8]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_f_reg[9] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_f_reg[8]_i_1_n_6 ),
        .Q(counter_f_reg[9]),
        .R(\counter_f[0]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[0] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[0]_i_2_n_7 ),
        .Q(counter_reg[0]),
        .R(clear));
  CARRY4 \counter_reg[0]_i_13 
       (.CI(\counter_reg[0]_i_16_n_0 ),
        .CO({\counter_reg[0]_i_13_n_0 ,\NLW_counter_reg[0]_i_13_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[12:9]),
        .S(counter_reg[12:9]));
  CARRY4 \counter_reg[0]_i_15 
       (.CI(1'b0),
        .CO({\counter_reg[0]_i_15_n_0 ,\NLW_counter_reg[0]_i_15_CO_UNCONNECTED [2:0]}),
        .CYINIT(counter_reg[0]),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[4:1]),
        .S(counter_reg[4:1]));
  CARRY4 \counter_reg[0]_i_16 
       (.CI(\counter_reg[0]_i_15_n_0 ),
        .CO({\counter_reg[0]_i_16_n_0 ,\NLW_counter_reg[0]_i_16_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[8:5]),
        .S(counter_reg[8:5]));
  CARRY4 \counter_reg[0]_i_17 
       (.CI(\counter_reg[0]_i_13_n_0 ),
        .CO({\counter_reg[0]_i_17_n_0 ,\NLW_counter_reg[0]_i_17_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[16:13]),
        .S(counter_reg[16:13]));
  CARRY4 \counter_reg[0]_i_18 
       (.CI(\counter_reg[0]_i_19_n_0 ),
        .CO({\counter_reg[0]_i_18_n_0 ,\NLW_counter_reg[0]_i_18_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[24:21]),
        .S(counter_reg[24:21]));
  CARRY4 \counter_reg[0]_i_19 
       (.CI(\counter_reg[0]_i_17_n_0 ),
        .CO({\counter_reg[0]_i_19_n_0 ,\NLW_counter_reg[0]_i_19_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[20:17]),
        .S(counter_reg[20:17]));
  CARRY4 \counter_reg[0]_i_2 
       (.CI(1'b0),
        .CO({\counter_reg[0]_i_2_n_0 ,\NLW_counter_reg[0]_i_2_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b1}),
        .O({\counter_reg[0]_i_2_n_4 ,\counter_reg[0]_i_2_n_5 ,\counter_reg[0]_i_2_n_6 ,\counter_reg[0]_i_2_n_7 }),
        .S({counter_reg[3:1],p_0_in[0]}));
  CARRY4 \counter_reg[0]_i_20 
       (.CI(\counter_reg[0]_i_21_n_0 ),
        .CO(\NLW_counter_reg[0]_i_20_CO_UNCONNECTED [3:0]),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_counter_reg[0]_i_20_O_UNCONNECTED [3],p_0_in[31:29]}),
        .S({1'b0,counter_reg[31:29]}));
  CARRY4 \counter_reg[0]_i_21 
       (.CI(\counter_reg[0]_i_18_n_0 ),
        .CO({\counter_reg[0]_i_21_n_0 ,\NLW_counter_reg[0]_i_21_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O(p_0_in[28:25]),
        .S(counter_reg[28:25]));
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
        .CO({\counter_reg[12]_i_1_n_0 ,\NLW_counter_reg[12]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[12]_i_1_n_4 ,\counter_reg[12]_i_1_n_5 ,\counter_reg[12]_i_1_n_6 ,\counter_reg[12]_i_1_n_7 }),
        .S(counter_reg[15:12]));
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
        .CO({\counter_reg[16]_i_1_n_0 ,\NLW_counter_reg[16]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[16]_i_1_n_4 ,\counter_reg[16]_i_1_n_5 ,\counter_reg[16]_i_1_n_6 ,\counter_reg[16]_i_1_n_7 }),
        .S(counter_reg[19:16]));
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
        .CO({\counter_reg[20]_i_1_n_0 ,\NLW_counter_reg[20]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[20]_i_1_n_4 ,\counter_reg[20]_i_1_n_5 ,\counter_reg[20]_i_1_n_6 ,\counter_reg[20]_i_1_n_7 }),
        .S(counter_reg[23:20]));
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
        .CO({\counter_reg[24]_i_1_n_0 ,\NLW_counter_reg[24]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[24]_i_1_n_4 ,\counter_reg[24]_i_1_n_5 ,\counter_reg[24]_i_1_n_6 ,\counter_reg[24]_i_1_n_7 }),
        .S(counter_reg[27:24]));
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
        .CO(\NLW_counter_reg[28]_i_1_CO_UNCONNECTED [3:0]),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[28]_i_1_n_4 ,\counter_reg[28]_i_1_n_5 ,\counter_reg[28]_i_1_n_6 ,\counter_reg[28]_i_1_n_7 }),
        .S(counter_reg[31:28]));
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
        .CO({\counter_reg[4]_i_1_n_0 ,\NLW_counter_reg[4]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[4]_i_1_n_4 ,\counter_reg[4]_i_1_n_5 ,\counter_reg[4]_i_1_n_6 ,\counter_reg[4]_i_1_n_7 }),
        .S(counter_reg[7:4]));
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
        .CO({\counter_reg[8]_i_1_n_0 ,\NLW_counter_reg[8]_i_1_CO_UNCONNECTED [2:0]}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\counter_reg[8]_i_1_n_4 ,\counter_reg[8]_i_1_n_5 ,\counter_reg[8]_i_1_n_6 ,\counter_reg[8]_i_1_n_7 }),
        .S(counter_reg[11:8]));
  FDRE #(
    .INIT(1'b0)) 
    \counter_reg[9] 
       (.C(clk),
        .CE(1'b1),
        .D(\counter_reg[8]_i_1_n_6 ),
        .Q(counter_reg[9]),
        .R(clear));
endmodule

module ssdisp
   (\seg[4] ,
    \seg[4]_0 ,
    \water_line_reg[0] ,
    D,
    \seg[4]_1 ,
    \seg[4]_2 ,
    \seg[4]_3 ,
    \seg[4]_4 ,
    \seg[4]_5 ,
    \seg[4]_6 ,
    \seg[4]_7 ,
    \seg[0] ,
    \seg[4]_8 ,
    \seg[2] ,
    \seg[4]_9 ,
    \seg[4]_10 ,
    next_state10_out,
    \seg[2]_0 ,
    \seg[4]_11 ,
    \seg[2]_1 ,
    \seg[4]_12 ,
    next_state1,
    next_state15_out,
    \seg[0]_0 ,
    \seg[4]_13 ,
    \seg[0]_1 ,
    \seg[0]_2 ,
    \seg[0]_3 ,
    \seg[4]_14 ,
    \seg[4]_15 ,
    \seg[4]_16 ,
    \seg[4]_17 ,
    \seg[0]_4 ,
    out,
    \status_mode_reg[2] ,
    \status_mode_reg[1] ,
    \status_mode_reg[0] ,
    Q,
    \num_reg[2] ,
    \num_reg[0] ,
    \num_reg[1] ,
    an_OBUF,
    \status_mode_reg[0]_0 ,
    \status_weight_reg[1] );
  output \seg[4] ;
  output \seg[4]_0 ;
  output \water_line_reg[0] ;
  output [3:0]D;
  output \seg[4]_1 ;
  output \seg[4]_2 ;
  output \seg[4]_3 ;
  output \seg[4]_4 ;
  output \seg[4]_5 ;
  output \seg[4]_6 ;
  output \seg[4]_7 ;
  output \seg[0] ;
  output \seg[4]_8 ;
  output \seg[2] ;
  output \seg[4]_9 ;
  output \seg[4]_10 ;
  output next_state10_out;
  output \seg[2]_0 ;
  output \seg[4]_11 ;
  output \seg[2]_1 ;
  output \seg[4]_12 ;
  output next_state1;
  output next_state15_out;
  output \seg[0]_0 ;
  output \seg[4]_13 ;
  output \seg[0]_1 ;
  output \seg[0]_2 ;
  output \seg[0]_3 ;
  output \seg[4]_14 ;
  output \seg[4]_15 ;
  output \seg[4]_16 ;
  output \seg[4]_17 ;
  output [0:0]\seg[0]_4 ;
  input [9:0]out;
  input \status_mode_reg[2] ;
  input \status_mode_reg[1] ;
  input \status_mode_reg[0] ;
  input [1:0]Q;
  input [2:0]\num_reg[2] ;
  input \num_reg[0] ;
  input \num_reg[1] ;
  input [0:0]an_OBUF;
  input [4:0]\status_mode_reg[0]_0 ;
  input [5:0]\status_weight_reg[1] ;

  wire [3:0]D;
  wire [1:0]Q;
  wire [0:0]an_OBUF;
  wire next_state1;
  wire next_state10_out;
  wire next_state15_out;
  wire \num_reg[0] ;
  wire \num_reg[1] ;
  wire [2:0]\num_reg[2] ;
  wire [9:0]out;
  wire \seg[0] ;
  wire \seg[0]_0 ;
  wire \seg[0]_1 ;
  wire \seg[0]_2 ;
  wire \seg[0]_3 ;
  wire [0:0]\seg[0]_4 ;
  wire \seg[2] ;
  wire \seg[2]_0 ;
  wire \seg[2]_1 ;
  wire \seg[4] ;
  wire \seg[4]_0 ;
  wire \seg[4]_1 ;
  wire \seg[4]_10 ;
  wire \seg[4]_11 ;
  wire \seg[4]_12 ;
  wire \seg[4]_13 ;
  wire \seg[4]_14 ;
  wire \seg[4]_15 ;
  wire \seg[4]_16 ;
  wire \seg[4]_17 ;
  wire \seg[4]_2 ;
  wire \seg[4]_3 ;
  wire \seg[4]_4 ;
  wire \seg[4]_5 ;
  wire \seg[4]_6 ;
  wire \seg[4]_7 ;
  wire \seg[4]_8 ;
  wire \seg[4]_9 ;
  wire \seg_OBUF[6]_inst_i_13_n_0 ;
  wire \seg_OBUF[6]_inst_i_14_n_0 ;
  wire \seg_OBUF[6]_inst_i_15_n_0 ;
  wire \seg_OBUF[6]_inst_i_31_n_0 ;
  wire \seg_OBUF[6]_inst_i_32_n_0 ;
  wire \seg_OBUF[6]_inst_i_33_n_0 ;
  wire \seg_OBUF[6]_inst_i_34_n_0 ;
  wire \seg_OBUF[6]_inst_i_35_n_0 ;
  wire \status_mode_reg[0] ;
  wire [4:0]\status_mode_reg[0]_0 ;
  wire \status_mode_reg[1] ;
  wire \status_mode_reg[2] ;
  wire [5:0]\status_weight_reg[1] ;
  wire [5:0]surplus_all;
  wire \surplus_all_reg[5]_i_9_n_0 ;
  wire [4:1]surplus_curr;
  wire \surplus_curr_reg[4]_i_2_n_0 ;
  wire \water_line_reg[0] ;

  LUT2 #(
    .INIT(4'h1)) 
    \FSM_onehot_state[6]_i_2 
       (.I0(\status_mode_reg[1] ),
        .I1(\status_mode_reg[0] ),
        .O(next_state1));
  LUT2 #(
    .INIT(4'h2)) 
    \FSM_onehot_state[6]_i_3 
       (.I0(\status_mode_reg[1] ),
        .I1(\status_mode_reg[2] ),
        .O(next_state15_out));
  LUT6 #(
    .INIT(64'hAEEBBEAEAAAAAAAA)) 
    \seg_OBUF[6]_inst_i_10 
       (.I0(\num_reg[2] [2]),
        .I1(surplus_curr[1]),
        .I2(surplus_curr[3]),
        .I3(surplus_curr[2]),
        .I4(surplus_curr[4]),
        .I5(\num_reg[0] ),
        .O(\seg[0]_2 ));
  LUT5 #(
    .INIT(32'h92C3B6D3)) 
    \seg_OBUF[6]_inst_i_13 
       (.I0(surplus_all[2]),
        .I1(surplus_all[5]),
        .I2(surplus_all[3]),
        .I3(surplus_all[4]),
        .I4(surplus_all[1]),
        .O(\seg_OBUF[6]_inst_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h000000A8FFFFFFFF)) 
    \seg_OBUF[6]_inst_i_14 
       (.I0(surplus_curr[4]),
        .I1(surplus_curr[2]),
        .I2(surplus_curr[3]),
        .I3(\num_reg[2] [0]),
        .I4(\num_reg[2] [1]),
        .I5(\num_reg[2] [2]),
        .O(\seg_OBUF[6]_inst_i_14_n_0 ));
  LUT4 #(
    .INIT(16'h4DF3)) 
    \seg_OBUF[6]_inst_i_15 
       (.I0(surplus_all[2]),
        .I1(surplus_all[5]),
        .I2(surplus_all[3]),
        .I3(surplus_all[4]),
        .O(\seg_OBUF[6]_inst_i_15_n_0 ));
  LUT6 #(
    .INIT(64'hC400F40004003400)) 
    \seg_OBUF[6]_inst_i_16 
       (.I0(\seg_OBUF[6]_inst_i_31_n_0 ),
        .I1(\num_reg[2] [2]),
        .I2(\num_reg[2] [0]),
        .I3(\num_reg[2] [1]),
        .I4(\seg_OBUF[6]_inst_i_32_n_0 ),
        .I5(\seg_OBUF[6]_inst_i_33_n_0 ),
        .O(\seg[0]_1 ));
  LUT6 #(
    .INIT(64'hB3BF0000B0BC0000)) 
    \seg_OBUF[6]_inst_i_24 
       (.I0(\seg_OBUF[6]_inst_i_13_n_0 ),
        .I1(\num_reg[2] [1]),
        .I2(\num_reg[2] [0]),
        .I3(surplus_all[0]),
        .I4(\num_reg[2] [2]),
        .I5(\seg_OBUF[6]_inst_i_34_n_0 ),
        .O(\seg[0]_0 ));
  LUT6 #(
    .INIT(64'hABAAEAAEAAAAAAAA)) 
    \seg_OBUF[6]_inst_i_25 
       (.I0(\seg_OBUF[6]_inst_i_35_n_0 ),
        .I1(surplus_curr[3]),
        .I2(surplus_curr[2]),
        .I3(surplus_curr[4]),
        .I4(surplus_curr[1]),
        .I5(\num_reg[1] ),
        .O(\seg[0]_3 ));
  LUT5 #(
    .INIT(32'hE759AE75)) 
    \seg_OBUF[6]_inst_i_31 
       (.I0(surplus_all[2]),
        .I1(surplus_all[5]),
        .I2(surplus_all[3]),
        .I3(surplus_all[4]),
        .I4(surplus_all[1]),
        .O(\seg_OBUF[6]_inst_i_31_n_0 ));
  LUT4 #(
    .INIT(16'h9BD9)) 
    \seg_OBUF[6]_inst_i_32 
       (.I0(surplus_curr[4]),
        .I1(surplus_curr[2]),
        .I2(surplus_curr[3]),
        .I3(surplus_curr[1]),
        .O(\seg_OBUF[6]_inst_i_32_n_0 ));
  LUT3 #(
    .INIT(8'hA8)) 
    \seg_OBUF[6]_inst_i_33 
       (.I0(surplus_all[5]),
        .I1(surplus_all[3]),
        .I2(surplus_all[4]),
        .O(\seg_OBUF[6]_inst_i_33_n_0 ));
  LUT4 #(
    .INIT(16'h2DBD)) 
    \seg_OBUF[6]_inst_i_34 
       (.I0(surplus_curr[4]),
        .I1(surplus_curr[2]),
        .I2(surplus_curr[3]),
        .I3(surplus_curr[1]),
        .O(\seg_OBUF[6]_inst_i_34_n_0 ));
  LUT6 #(
    .INIT(64'h0000000002408418)) 
    \seg_OBUF[6]_inst_i_35 
       (.I0(surplus_all[1]),
        .I1(surplus_all[4]),
        .I2(surplus_all[3]),
        .I3(surplus_all[5]),
        .I4(surplus_all[2]),
        .I5(an_OBUF),
        .O(\seg_OBUF[6]_inst_i_35_n_0 ));
  LUT6 #(
    .INIT(64'h0F0F060F000F060F)) 
    \seg_OBUF[6]_inst_i_4 
       (.I0(surplus_all[1]),
        .I1(\seg_OBUF[6]_inst_i_13_n_0 ),
        .I2(\seg_OBUF[6]_inst_i_14_n_0 ),
        .I3(\num_reg[2] [1]),
        .I4(\num_reg[2] [0]),
        .I5(\seg_OBUF[6]_inst_i_15_n_0 ),
        .O(\seg[4]_13 ));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \state_OBUF[0]_inst_i_1 
       (.I0(out[6]),
        .I1(out[8]),
        .I2(out[4]),
        .I3(out[0]),
        .I4(out[2]),
        .O(D[0]));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \state_OBUF[1]_inst_i_1 
       (.I0(out[2]),
        .I1(out[1]),
        .I2(out[9]),
        .I3(out[6]),
        .I4(out[5]),
        .O(D[1]));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \state_OBUF[2]_inst_i_1 
       (.I0(out[4]),
        .I1(out[3]),
        .I2(out[5]),
        .I3(out[6]),
        .O(D[2]));
  LUT3 #(
    .INIT(8'hFE)) 
    \state_OBUF[3]_inst_i_1 
       (.I0(out[7]),
        .I1(out[9]),
        .I2(out[8]),
        .O(D[3]));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[0] 
       (.CLR(1'b0),
        .D(\status_weight_reg[1] [0]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[0]));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[1] 
       (.CLR(1'b0),
        .D(\status_weight_reg[1] [1]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[1]));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFF01)) 
    \surplus_all_reg[1]_i_2 
       (.I0(out[8]),
        .I1(out[9]),
        .I2(out[7]),
        .I3(\status_mode_reg[2] ),
        .I4(\status_mode_reg[1] ),
        .I5(\status_mode_reg[0] ),
        .O(\seg[4] ));
  LUT6 #(
    .INIT(64'h00AA00A00882A822)) 
    \surplus_all_reg[1]_i_8 
       (.I0(\water_line_reg[0] ),
        .I1(Q[0]),
        .I2(\status_mode_reg[0] ),
        .I3(\status_mode_reg[1] ),
        .I4(Q[1]),
        .I5(\status_mode_reg[2] ),
        .O(\seg[4]_4 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[2] 
       (.CLR(1'b0),
        .D(\status_weight_reg[1] [2]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[2]));
  LUT6 #(
    .INIT(64'h0101555410105445)) 
    \surplus_all_reg[2]_i_11 
       (.I0(D[0]),
        .I1(\status_mode_reg[2] ),
        .I2(Q[1]),
        .I3(Q[0]),
        .I4(\status_mode_reg[1] ),
        .I5(\status_mode_reg[0] ),
        .O(\seg[4]_17 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[3] 
       (.CLR(1'b0),
        .D(\status_weight_reg[1] [3]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[3]));
  LUT6 #(
    .INIT(64'hFF83FF82FFFFFFFF)) 
    \surplus_all_reg[3]_i_10 
       (.I0(Q[1]),
        .I1(\status_mode_reg[1] ),
        .I2(\status_mode_reg[0] ),
        .I3(\status_mode_reg[2] ),
        .I4(Q[0]),
        .I5(\water_line_reg[0] ),
        .O(\seg[4]_16 ));
  LUT3 #(
    .INIT(8'h04)) 
    \surplus_all_reg[3]_i_9 
       (.I0(D[1]),
        .I1(D[0]),
        .I2(\status_mode_reg[2] ),
        .O(\seg[4]_14 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[4] 
       (.CLR(1'b0),
        .D(\status_weight_reg[1] [4]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[4]));
  LUT5 #(
    .INIT(32'hFEFFFFFF)) 
    \surplus_all_reg[4]_i_12 
       (.I0(\status_mode_reg[2] ),
        .I1(\status_mode_reg[1] ),
        .I2(\status_mode_reg[0] ),
        .I3(D[0]),
        .I4(D[1]),
        .O(\seg[4]_3 ));
  LUT6 #(
    .INIT(64'h00000000FFFFFFFE)) 
    \surplus_all_reg[4]_i_13 
       (.I0(out[5]),
        .I1(out[6]),
        .I2(out[9]),
        .I3(out[1]),
        .I4(out[2]),
        .I5(D[0]),
        .O(\seg[4]_2 ));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    \surplus_all_reg[4]_i_14 
       (.I0(D[0]),
        .I1(out[5]),
        .I2(out[6]),
        .I3(out[9]),
        .I4(out[1]),
        .I5(out[2]),
        .O(\seg[4]_6 ));
  LUT6 #(
    .INIT(64'h0022A2000022A202)) 
    \surplus_all_reg[4]_i_8 
       (.I0(\water_line_reg[0] ),
        .I1(\status_mode_reg[0] ),
        .I2(Q[1]),
        .I3(\status_mode_reg[1] ),
        .I4(\status_mode_reg[2] ),
        .I5(Q[0]),
        .O(\seg[4]_5 ));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAAAAAAB)) 
    \surplus_all_reg[4]_i_9 
       (.I0(\status_mode_reg[2] ),
        .I1(out[2]),
        .I2(out[0]),
        .I3(out[4]),
        .I4(out[8]),
        .I5(out[6]),
        .O(\seg[4]_8 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[5] 
       (.CLR(1'b0),
        .D(\status_weight_reg[1] [5]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[5]));
  LUT6 #(
    .INIT(64'hFFFFFFFFFF7FFFFF)) 
    \surplus_all_reg[5]_i_4 
       (.I0(\water_line_reg[0] ),
        .I1(Q[1]),
        .I2(\surplus_all_reg[5]_i_9_n_0 ),
        .I3(\status_mode_reg[0] ),
        .I4(Q[0]),
        .I5(\status_mode_reg[1] ),
        .O(\seg[4]_0 ));
  LUT5 #(
    .INIT(32'h0000FFFE)) 
    \surplus_all_reg[5]_i_9 
       (.I0(out[6]),
        .I1(out[5]),
        .I2(out[3]),
        .I3(out[4]),
        .I4(D[3]),
        .O(\surplus_all_reg[5]_i_9_n_0 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[0] 
       (.CLR(1'b0),
        .D(\status_mode_reg[0]_0 [0]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(\seg[0]_4 ));
  LUT4 #(
    .INIT(16'h082A)) 
    \surplus_curr_reg[0]_i_6 
       (.I0(D[0]),
        .I1(\status_mode_reg[1] ),
        .I2(\status_mode_reg[2] ),
        .I3(\status_mode_reg[0] ),
        .O(\seg[0] ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[1] 
       (.CLR(1'b0),
        .D(\status_mode_reg[0]_0 [1]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_curr[1]));
  LUT5 #(
    .INIT(32'hE1B9E4EC)) 
    \surplus_curr_reg[1]_i_6 
       (.I0(\status_mode_reg[2] ),
        .I1(Q[1]),
        .I2(\status_mode_reg[1] ),
        .I3(\status_mode_reg[0] ),
        .I4(Q[0]),
        .O(\seg[2] ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[2] 
       (.CLR(1'b0),
        .D(\status_mode_reg[0]_0 [2]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_curr[2]));
  LUT5 #(
    .INIT(32'hFFC10C11)) 
    \surplus_curr_reg[2]_i_10 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(\status_mode_reg[0] ),
        .I3(\status_mode_reg[2] ),
        .I4(\status_mode_reg[1] ),
        .O(\seg[4]_9 ));
  LUT4 #(
    .INIT(16'h0007)) 
    \surplus_curr_reg[2]_i_11 
       (.I0(\status_mode_reg[1] ),
        .I1(\status_mode_reg[0] ),
        .I2(\status_mode_reg[2] ),
        .I3(D[0]),
        .O(\seg[4]_7 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[3] 
       (.CLR(1'b0),
        .D(\status_mode_reg[0]_0 [3]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_curr[3]));
  LUT4 #(
    .INIT(16'hEAAA)) 
    \surplus_curr_reg[3]_i_10 
       (.I0(\status_mode_reg[2] ),
        .I1(Q[1]),
        .I2(\status_mode_reg[1] ),
        .I3(\status_mode_reg[0] ),
        .O(\seg[4]_10 ));
  LUT2 #(
    .INIT(4'h8)) 
    \surplus_curr_reg[3]_i_13 
       (.I0(\status_mode_reg[1] ),
        .I1(\status_mode_reg[0] ),
        .O(\seg[2]_0 ));
  LUT3 #(
    .INIT(8'h01)) 
    \surplus_curr_reg[3]_i_3 
       (.I0(\status_mode_reg[0] ),
        .I1(\status_mode_reg[1] ),
        .I2(\status_mode_reg[2] ),
        .O(\seg[2]_1 ));
  LUT3 #(
    .INIT(8'h01)) 
    \surplus_curr_reg[3]_i_9 
       (.I0(\status_mode_reg[0] ),
        .I1(\status_mode_reg[1] ),
        .I2(Q[1]),
        .O(\seg[4]_12 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[4] 
       (.CLR(1'b0),
        .D(\status_mode_reg[0]_0 [4]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_curr[4]));
  LUT5 #(
    .INIT(32'h00040404)) 
    \surplus_curr_reg[4]_i_10 
       (.I0(\status_mode_reg[2] ),
        .I1(D[0]),
        .I2(D[1]),
        .I3(\status_mode_reg[0] ),
        .I4(\status_mode_reg[1] ),
        .O(\seg[4]_1 ));
  LUT3 #(
    .INIT(8'hCA)) 
    \surplus_curr_reg[4]_i_12 
       (.I0(\status_mode_reg[0] ),
        .I1(\status_mode_reg[2] ),
        .I2(\status_mode_reg[1] ),
        .O(\seg[4]_11 ));
  LUT6 #(
    .INIT(64'h5555555755555555)) 
    \surplus_curr_reg[4]_i_2 
       (.I0(D[3]),
        .I1(out[6]),
        .I2(out[5]),
        .I3(out[3]),
        .I4(out[4]),
        .I5(\water_line_reg[0] ),
        .O(\surplus_curr_reg[4]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h35000000)) 
    \surplus_curr_reg[4]_i_3 
       (.I0(\status_mode_reg[0] ),
        .I1(\status_mode_reg[2] ),
        .I2(\status_mode_reg[1] ),
        .I3(D[0]),
        .I4(D[1]),
        .O(\seg[4]_15 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \surplus_curr_reg[4]_i_7 
       (.I0(D[0]),
        .I1(out[5]),
        .I2(out[6]),
        .I3(out[9]),
        .I4(out[1]),
        .I5(out[2]),
        .O(\water_line_reg[0] ));
  LUT3 #(
    .INIT(8'h18)) 
    \surplus_curr_reg[4]_i_8 
       (.I0(\status_mode_reg[1] ),
        .I1(\status_mode_reg[0] ),
        .I2(\status_mode_reg[2] ),
        .O(next_state10_out));
endmodule

module timer
   (\seg[4] ,
    \seg[4]_0 ,
    \timer_set_reg[3]_0 ,
    seg_OBUF,
    \FSM_onehot_state_reg[9] ,
    CLK,
    D,
    Q,
    \FSM_onehot_state_reg[9]_0 ,
    \FSM_onehot_state_reg[6] ,
    \status_mode_reg[2] ,
    \status_mode_reg[1] ,
    \status_mode_reg[0] ,
    out,
    next_state1,
    \status_mode_reg[0]_0 ,
    \status_mode_reg[0]_1 ,
    \status_weight_reg[1] ,
    \num_reg[1] ,
    \num_reg[2] ,
    \FSM_onehot_state_reg[5] ,
    \num_reg[2]_0 ,
    an_OBUF,
    \num_reg[0] ,
    \num_reg[1]_0 ,
    \num_reg[2]_1 ,
    \num_reg[0]_0 ,
    \num_reg[2]_2 ,
    \num_reg[0]_1 ,
    \num_reg[1]_1 ,
    \status_mode_reg[0]_2 ,
    \status_weight_reg[0] ,
    \status_mode_reg[1]_0 ,
    \status_mode_reg[2]_0 ,
    \status_weight_reg[0]_0 ,
    \status_mode_reg[1]_1 ,
    \status_mode_reg[2]_1 ,
    \status_mode_reg[1]_2 ,
    \status_mode_reg[0]_3 ,
    \status_mode_reg[2]_2 ,
    next_state10_out,
    \status_mode_reg[0]_4 ,
    \status_mode_reg[2]_3 ,
    \status_mode_reg[2]_4 ,
    \status_weight_reg[1]_0 ,
    \status_mode_reg[2]_5 ,
    \FSM_onehot_state_reg[6]_0 ,
    next_state15_out,
    \FSM_onehot_state_reg[6]_1 ,
    \status_mode_reg[2]_6 ,
    \state_2_reg[3] ,
    \state_1_reg[3] ,
    light_running_reg,
    \FSM_onehot_state_reg[3] ,
    \FSM_onehot_state_reg[2] ,
    \status_mode_reg[1]_3 ,
    \FSM_onehot_state_reg[0] ,
    \FSM_onehot_state_reg[3]_0 ,
    \status_mode_reg[1]_4 ,
    \status_mode_reg[2]_7 );
  output [5:0]\seg[4] ;
  output [4:0]\seg[4]_0 ;
  output \timer_set_reg[3]_0 ;
  output [6:0]seg_OBUF;
  output [8:0]\FSM_onehot_state_reg[9] ;
  input CLK;
  input [3:0]D;
  input [1:0]Q;
  input \FSM_onehot_state_reg[9]_0 ;
  input \FSM_onehot_state_reg[6] ;
  input \status_mode_reg[2] ;
  input \status_mode_reg[1] ;
  input \status_mode_reg[0] ;
  input [10:0]out;
  input next_state1;
  input \status_mode_reg[0]_0 ;
  input \status_mode_reg[0]_1 ;
  input \status_weight_reg[1] ;
  input \num_reg[1] ;
  input [2:0]\num_reg[2] ;
  input \FSM_onehot_state_reg[5] ;
  input \num_reg[2]_0 ;
  input [0:0]an_OBUF;
  input \num_reg[0] ;
  input \num_reg[1]_0 ;
  input \num_reg[2]_1 ;
  input \num_reg[0]_0 ;
  input \num_reg[2]_2 ;
  input \num_reg[0]_1 ;
  input \num_reg[1]_1 ;
  input \status_mode_reg[0]_2 ;
  input \status_weight_reg[0] ;
  input \status_mode_reg[1]_0 ;
  input \status_mode_reg[2]_0 ;
  input \status_weight_reg[0]_0 ;
  input \status_mode_reg[1]_1 ;
  input \status_mode_reg[2]_1 ;
  input \status_mode_reg[1]_2 ;
  input \status_mode_reg[0]_3 ;
  input \status_mode_reg[2]_2 ;
  input next_state10_out;
  input \status_mode_reg[0]_4 ;
  input \status_mode_reg[2]_3 ;
  input \status_mode_reg[2]_4 ;
  input \status_weight_reg[1]_0 ;
  input \status_mode_reg[2]_5 ;
  input \FSM_onehot_state_reg[6]_0 ;
  input next_state15_out;
  input \FSM_onehot_state_reg[6]_1 ;
  input \status_mode_reg[2]_6 ;
  input [3:0]\state_2_reg[3] ;
  input [3:0]\state_1_reg[3] ;
  input light_running_reg;
  input \FSM_onehot_state_reg[3] ;
  input \FSM_onehot_state_reg[2] ;
  input \status_mode_reg[1]_3 ;
  input \FSM_onehot_state_reg[0] ;
  input \FSM_onehot_state_reg[3]_0 ;
  input \status_mode_reg[1]_4 ;
  input \status_mode_reg[2]_7 ;

  wire CLK;
  wire [3:0]D;
  wire \FSM_onehot_state[2]_i_2_n_0 ;
  wire \FSM_onehot_state[3]_i_2_n_0 ;
  wire \FSM_onehot_state[7]_i_2_n_0 ;
  wire \FSM_onehot_state[8]_i_2_n_0 ;
  wire \FSM_onehot_state_reg[0] ;
  wire \FSM_onehot_state_reg[2] ;
  wire \FSM_onehot_state_reg[3] ;
  wire \FSM_onehot_state_reg[3]_0 ;
  wire \FSM_onehot_state_reg[5] ;
  wire \FSM_onehot_state_reg[6] ;
  wire \FSM_onehot_state_reg[6]_0 ;
  wire \FSM_onehot_state_reg[6]_1 ;
  wire [8:0]\FSM_onehot_state_reg[9] ;
  wire \FSM_onehot_state_reg[9]_0 ;
  wire [1:0]Q;
  wire [0:0]an_OBUF;
  wire light_running_reg;
  wire next_state1;
  wire next_state10_out;
  wire next_state15_out;
  wire \num_reg[0] ;
  wire \num_reg[0]_0 ;
  wire \num_reg[0]_1 ;
  wire \num_reg[1] ;
  wire \num_reg[1]_0 ;
  wire \num_reg[1]_1 ;
  wire [2:0]\num_reg[2] ;
  wire \num_reg[2]_0 ;
  wire \num_reg[2]_1 ;
  wire \num_reg[2]_2 ;
  wire [10:0]out;
  wire [5:0]\seg[4] ;
  wire [4:0]\seg[4]_0 ;
  wire [6:0]seg_OBUF;
  wire \seg_OBUF[6]_inst_i_11_n_0 ;
  wire \seg_OBUF[6]_inst_i_12_n_0 ;
  wire \seg_OBUF[6]_inst_i_17_n_0 ;
  wire \seg_OBUF[6]_inst_i_18_n_0 ;
  wire \seg_OBUF[6]_inst_i_20_n_0 ;
  wire \seg_OBUF[6]_inst_i_26_n_0 ;
  wire \seg_OBUF[6]_inst_i_27_n_0 ;
  wire \seg_OBUF[6]_inst_i_28_n_0 ;
  wire \seg_OBUF[6]_inst_i_29_n_0 ;
  wire \seg_OBUF[6]_inst_i_2_n_0 ;
  wire \seg_OBUF[6]_inst_i_37_n_0 ;
  wire \seg_OBUF[6]_inst_i_38_n_0 ;
  wire \seg_OBUF[6]_inst_i_39_n_0 ;
  wire \seg_OBUF[6]_inst_i_3_n_0 ;
  wire \seg_OBUF[6]_inst_i_5_n_0 ;
  wire \seg_OBUF[6]_inst_i_6_n_0 ;
  wire \seg_OBUF[6]_inst_i_7_n_0 ;
  wire \seg_OBUF[6]_inst_i_8_n_0 ;
  wire [3:0]\state_1_reg[3] ;
  wire [3:0]\state_2_reg[3] ;
  wire \status_mode_reg[0] ;
  wire \status_mode_reg[0]_0 ;
  wire \status_mode_reg[0]_1 ;
  wire \status_mode_reg[0]_2 ;
  wire \status_mode_reg[0]_3 ;
  wire \status_mode_reg[0]_4 ;
  wire \status_mode_reg[1] ;
  wire \status_mode_reg[1]_0 ;
  wire \status_mode_reg[1]_1 ;
  wire \status_mode_reg[1]_2 ;
  wire \status_mode_reg[1]_3 ;
  wire \status_mode_reg[1]_4 ;
  wire \status_mode_reg[2] ;
  wire \status_mode_reg[2]_0 ;
  wire \status_mode_reg[2]_1 ;
  wire \status_mode_reg[2]_2 ;
  wire \status_mode_reg[2]_3 ;
  wire \status_mode_reg[2]_4 ;
  wire \status_mode_reg[2]_5 ;
  wire \status_mode_reg[2]_6 ;
  wire \status_mode_reg[2]_7 ;
  wire \status_weight_reg[0] ;
  wire \status_weight_reg[0]_0 ;
  wire \status_weight_reg[1] ;
  wire \status_weight_reg[1]_0 ;
  wire \surplus_all_reg[0]_i_2_n_0 ;
  wire \surplus_all_reg[1]_i_3_n_0 ;
  wire \surplus_all_reg[1]_i_4_n_0 ;
  wire \surplus_all_reg[1]_i_5_n_0 ;
  wire \surplus_all_reg[1]_i_6_n_0 ;
  wire \surplus_all_reg[1]_i_7_n_0 ;
  wire \surplus_all_reg[2]_i_10_n_0 ;
  wire \surplus_all_reg[2]_i_2_n_0 ;
  wire \surplus_all_reg[2]_i_3_n_0 ;
  wire \surplus_all_reg[2]_i_4_n_0 ;
  wire \surplus_all_reg[2]_i_5_n_0 ;
  wire \surplus_all_reg[2]_i_6_n_0 ;
  wire \surplus_all_reg[2]_i_7_n_0 ;
  wire \surplus_all_reg[2]_i_8_n_0 ;
  wire \surplus_all_reg[2]_i_9_n_0 ;
  wire \surplus_all_reg[3]_i_11_n_0 ;
  wire \surplus_all_reg[3]_i_12_n_0 ;
  wire \surplus_all_reg[3]_i_13_n_0 ;
  wire \surplus_all_reg[3]_i_14_n_0 ;
  wire \surplus_all_reg[3]_i_15_n_0 ;
  wire \surplus_all_reg[3]_i_2_n_0 ;
  wire \surplus_all_reg[3]_i_3_n_0 ;
  wire \surplus_all_reg[3]_i_4_n_0 ;
  wire \surplus_all_reg[3]_i_5_n_0 ;
  wire \surplus_all_reg[3]_i_6_n_0 ;
  wire \surplus_all_reg[3]_i_7_n_0 ;
  wire \surplus_all_reg[3]_i_8_n_0 ;
  wire \surplus_all_reg[4]_i_10_n_0 ;
  wire \surplus_all_reg[4]_i_11_n_0 ;
  wire \surplus_all_reg[4]_i_15_n_0 ;
  wire \surplus_all_reg[4]_i_16_n_0 ;
  wire \surplus_all_reg[4]_i_17_n_0 ;
  wire \surplus_all_reg[4]_i_2_n_0 ;
  wire \surplus_all_reg[4]_i_3_n_0 ;
  wire \surplus_all_reg[4]_i_4_n_0 ;
  wire \surplus_all_reg[4]_i_5_n_0 ;
  wire \surplus_all_reg[4]_i_6_n_0 ;
  wire \surplus_all_reg[4]_i_7_n_0 ;
  wire \surplus_all_reg[5]_i_2_n_0 ;
  wire \surplus_all_reg[5]_i_3_n_0 ;
  wire \surplus_all_reg[5]_i_5_n_0 ;
  wire \surplus_all_reg[5]_i_6_n_0 ;
  wire \surplus_all_reg[5]_i_7_n_0 ;
  wire \surplus_all_reg[5]_i_8_n_0 ;
  wire \surplus_curr_reg[0]_i_2_n_0 ;
  wire \surplus_curr_reg[0]_i_3_n_0 ;
  wire \surplus_curr_reg[0]_i_4_n_0 ;
  wire \surplus_curr_reg[0]_i_5_n_0 ;
  wire \surplus_curr_reg[1]_i_2_n_0 ;
  wire \surplus_curr_reg[1]_i_3_n_0 ;
  wire \surplus_curr_reg[1]_i_4_n_0 ;
  wire \surplus_curr_reg[1]_i_5_n_0 ;
  wire \surplus_curr_reg[1]_i_7_n_0 ;
  wire \surplus_curr_reg[1]_i_8_n_0 ;
  wire \surplus_curr_reg[2]_i_12_n_0 ;
  wire \surplus_curr_reg[2]_i_2_n_0 ;
  wire \surplus_curr_reg[2]_i_3_n_0 ;
  wire \surplus_curr_reg[2]_i_4_n_0 ;
  wire \surplus_curr_reg[2]_i_5_n_0 ;
  wire \surplus_curr_reg[2]_i_6_n_0 ;
  wire \surplus_curr_reg[2]_i_7_n_0 ;
  wire \surplus_curr_reg[2]_i_8_n_0 ;
  wire \surplus_curr_reg[2]_i_9_n_0 ;
  wire \surplus_curr_reg[3]_i_11_n_0 ;
  wire \surplus_curr_reg[3]_i_12_n_0 ;
  wire \surplus_curr_reg[3]_i_2_n_0 ;
  wire \surplus_curr_reg[3]_i_4_n_0 ;
  wire \surplus_curr_reg[3]_i_5_n_0 ;
  wire \surplus_curr_reg[3]_i_6_n_0 ;
  wire \surplus_curr_reg[3]_i_7_n_0 ;
  wire \surplus_curr_reg[3]_i_8_n_0 ;
  wire \surplus_curr_reg[4]_i_11_n_0 ;
  wire \surplus_curr_reg[4]_i_13_n_0 ;
  wire \surplus_curr_reg[4]_i_4_n_0 ;
  wire \surplus_curr_reg[4]_i_5_n_0 ;
  wire \surplus_curr_reg[4]_i_6_n_0 ;
  wire \surplus_curr_reg[4]_i_9_n_0 ;
  wire timer_out;
  wire timer_out_i_1_n_0;
  wire [3:0]timer_set;
  wire \timer_set[0]_i_1_n_0 ;
  wire \timer_set[0]_i_2_n_0 ;
  wire \timer_set[1]_i_1_n_0 ;
  wire \timer_set[1]_i_2_n_0 ;
  wire \timer_set[2]_i_1_n_0 ;
  wire \timer_set[2]_i_2_n_0 ;
  wire \timer_set[3]_i_1_n_0 ;
  wire \timer_set[3]_i_3_n_0 ;
  wire \timer_set[3]_i_4_n_0 ;
  wire \timer_set[3]_i_5_n_0 ;
  wire \timer_set_reg[3]_0 ;
  wire [7:1]water_line;
  wire \water_line[0]_i_1_n_0 ;
  wire \water_line[7]_i_1_n_0 ;
  wire \water_line[7]_i_2_n_0 ;
  wire [0:0]water_line_reg__0;
  wire water_line_reg__0_carry__0_i_1_n_0;
  wire water_line_reg__0_carry__0_i_2_n_0;
  wire water_line_reg__0_carry__0_i_3_n_0;
  wire water_line_reg__0_carry__0_n_5;
  wire water_line_reg__0_carry__0_n_6;
  wire water_line_reg__0_carry__0_n_7;
  wire water_line_reg__0_carry_i_1_n_0;
  wire water_line_reg__0_carry_i_2_n_0;
  wire water_line_reg__0_carry_i_3_n_0;
  wire water_line_reg__0_carry_i_4_n_0;
  wire water_line_reg__0_carry_i_5_n_0;
  wire water_line_reg__0_carry_n_0;
  wire water_line_reg__0_carry_n_4;
  wire water_line_reg__0_carry_n_5;
  wire water_line_reg__0_carry_n_6;
  wire water_line_reg__0_carry_n_7;
  wire [2:0]NLW_water_line_reg__0_carry_CO_UNCONNECTED;
  wire [3:0]NLW_water_line_reg__0_carry__0_CO_UNCONNECTED;
  wire [3:3]NLW_water_line_reg__0_carry__0_O_UNCONNECTED;

  LUT5 #(
    .INIT(32'h88B83030)) 
    \FSM_onehot_state[1]_i_1 
       (.I0(\status_mode_reg[2]_7 ),
        .I1(out[0]),
        .I2(out[1]),
        .I3(timer_out),
        .I4(light_running_reg),
        .O(\FSM_onehot_state_reg[9] [0]));
  LUT6 #(
    .INIT(64'h00000000FFA800AA)) 
    \FSM_onehot_state[2]_i_1 
       (.I0(\FSM_onehot_state[2]_i_2_n_0 ),
        .I1(\status_mode_reg[2] ),
        .I2(\status_mode_reg[1]_4 ),
        .I3(out[1]),
        .I4(\FSM_onehot_state[8]_i_2_n_0 ),
        .I5(out[0]),
        .O(\FSM_onehot_state_reg[9] [1]));
  LUT5 #(
    .INIT(32'hA8AAAAAA)) 
    \FSM_onehot_state[2]_i_2 
       (.I0(out[2]),
        .I1(\status_mode_reg[2] ),
        .I2(\status_mode_reg[0] ),
        .I3(light_running_reg),
        .I4(timer_out),
        .O(\FSM_onehot_state[2]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hBAAEAAAAAAAAAAAA)) 
    \FSM_onehot_state[3]_i_1 
       (.I0(\FSM_onehot_state[3]_i_2_n_0 ),
        .I1(\status_mode_reg[2] ),
        .I2(\status_mode_reg[0] ),
        .I3(\status_mode_reg[1] ),
        .I4(out[0]),
        .I5(light_running_reg),
        .O(\FSM_onehot_state_reg[9] [2]));
  LUT6 #(
    .INIT(64'h00000000000C2222)) 
    \FSM_onehot_state[3]_i_2 
       (.I0(out[3]),
        .I1(out[2]),
        .I2(\status_mode_reg[2] ),
        .I3(\status_mode_reg[0] ),
        .I4(\FSM_onehot_state[8]_i_2_n_0 ),
        .I5(\FSM_onehot_state_reg[0] ),
        .O(\FSM_onehot_state[3]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0101000000000100)) 
    \FSM_onehot_state[4]_i_1 
       (.I0(out[2]),
        .I1(out[1]),
        .I2(out[0]),
        .I3(out[4]),
        .I4(out[3]),
        .I5(\FSM_onehot_state[8]_i_2_n_0 ),
        .O(\FSM_onehot_state_reg[9] [3]));
  LUT6 #(
    .INIT(64'h00000000000000A4)) 
    \FSM_onehot_state[5]_i_1 
       (.I0(out[4]),
        .I1(out[5]),
        .I2(\FSM_onehot_state[8]_i_2_n_0 ),
        .I3(out[2]),
        .I4(out[3]),
        .I5(\FSM_onehot_state_reg[0] ),
        .O(\FSM_onehot_state_reg[9] [4]));
  LUT6 #(
    .INIT(64'h00000000FF0400CC)) 
    \FSM_onehot_state[6]_i_1 
       (.I0(next_state1),
        .I1(out[6]),
        .I2(next_state15_out),
        .I3(out[5]),
        .I4(\FSM_onehot_state[8]_i_2_n_0 ),
        .I5(\FSM_onehot_state_reg[3]_0 ),
        .O(\FSM_onehot_state_reg[9] [5]));
  LUT6 #(
    .INIT(64'hFFFFFFFF00800000)) 
    \FSM_onehot_state[7]_i_1 
       (.I0(light_running_reg),
        .I1(out[0]),
        .I2(\status_mode_reg[0] ),
        .I3(\status_mode_reg[1] ),
        .I4(\status_mode_reg[2] ),
        .I5(\FSM_onehot_state[7]_i_2_n_0 ),
        .O(\FSM_onehot_state_reg[9] [6]));
  LUT6 #(
    .INIT(64'h00000000C0000808)) 
    \FSM_onehot_state[7]_i_2 
       (.I0(out[7]),
        .I1(\FSM_onehot_state_reg[3] ),
        .I2(out[6]),
        .I3(next_state1),
        .I4(\FSM_onehot_state[8]_i_2_n_0 ),
        .I5(\FSM_onehot_state_reg[2] ),
        .O(\FSM_onehot_state[7]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0100000101000000)) 
    \FSM_onehot_state[8]_i_1 
       (.I0(\FSM_onehot_state_reg[3]_0 ),
        .I1(out[5]),
        .I2(out[6]),
        .I3(out[7]),
        .I4(\FSM_onehot_state[8]_i_2_n_0 ),
        .I5(out[8]),
        .O(\FSM_onehot_state_reg[9] [7]));
  LUT2 #(
    .INIT(4'h8)) 
    \FSM_onehot_state[8]_i_2 
       (.I0(light_running_reg),
        .I1(timer_out),
        .O(\FSM_onehot_state[8]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h00000080)) 
    \FSM_onehot_state[9]_i_1 
       (.I0(\status_mode_reg[1]_3 ),
        .I1(light_running_reg),
        .I2(timer_out),
        .I3(out[0]),
        .I4(out[1]),
        .O(\FSM_onehot_state_reg[9] [8]));
  LUT6 #(
    .INIT(64'h0000000000F2F200)) 
    \seg_OBUF[0]_inst_i_1 
       (.I0(\seg_OBUF[6]_inst_i_2_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_3_n_0 ),
        .I2(\num_reg[1] ),
        .I3(\seg_OBUF[6]_inst_i_6_n_0 ),
        .I4(\seg_OBUF[6]_inst_i_5_n_0 ),
        .I5(\seg_OBUF[6]_inst_i_7_n_0 ),
        .O(seg_OBUF[0]));
  LUT5 #(
    .INIT(32'h88882282)) 
    \seg_OBUF[1]_inst_i_1 
       (.I0(\seg_OBUF[6]_inst_i_5_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_6_n_0 ),
        .I2(\seg_OBUF[6]_inst_i_2_n_0 ),
        .I3(\seg_OBUF[6]_inst_i_3_n_0 ),
        .I4(\num_reg[1] ),
        .O(seg_OBUF[1]));
  LUT5 #(
    .INIT(32'h00000051)) 
    \seg_OBUF[2]_inst_i_1 
       (.I0(\seg_OBUF[6]_inst_i_5_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_2_n_0 ),
        .I2(\seg_OBUF[6]_inst_i_3_n_0 ),
        .I3(\num_reg[1] ),
        .I4(\seg_OBUF[6]_inst_i_6_n_0 ),
        .O(seg_OBUF[2]));
  LUT5 #(
    .INIT(32'h68666868)) 
    \seg_OBUF[3]_inst_i_1 
       (.I0(\seg_OBUF[6]_inst_i_5_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_6_n_0 ),
        .I2(\num_reg[1] ),
        .I3(\seg_OBUF[6]_inst_i_3_n_0 ),
        .I4(\seg_OBUF[6]_inst_i_2_n_0 ),
        .O(seg_OBUF[3]));
  LUT5 #(
    .INIT(32'hFFFFF200)) 
    \seg_OBUF[4]_inst_i_1 
       (.I0(\seg_OBUF[6]_inst_i_2_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_3_n_0 ),
        .I2(\num_reg[1] ),
        .I3(\seg_OBUF[6]_inst_i_5_n_0 ),
        .I4(\seg_OBUF[6]_inst_i_6_n_0 ),
        .O(seg_OBUF[4]));
  LUT6 #(
    .INIT(64'h0223020202230223)) 
    \seg_OBUF[5]_inst_i_1 
       (.I0(\seg_OBUF[6]_inst_i_6_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_7_n_0 ),
        .I2(\seg_OBUF[6]_inst_i_5_n_0 ),
        .I3(\num_reg[1] ),
        .I4(\seg_OBUF[6]_inst_i_3_n_0 ),
        .I5(\seg_OBUF[6]_inst_i_2_n_0 ),
        .O(seg_OBUF[5]));
  LUT6 #(
    .INIT(64'h000000000DF200F2)) 
    \seg_OBUF[6]_inst_i_1 
       (.I0(\seg_OBUF[6]_inst_i_2_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_3_n_0 ),
        .I2(\num_reg[1] ),
        .I3(\seg_OBUF[6]_inst_i_5_n_0 ),
        .I4(\seg_OBUF[6]_inst_i_6_n_0 ),
        .I5(\seg_OBUF[6]_inst_i_7_n_0 ),
        .O(seg_OBUF[6]));
  LUT6 #(
    .INIT(64'h0F3E830FE083F8E0)) 
    \seg_OBUF[6]_inst_i_11 
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .I2(water_line[4]),
        .I3(water_line[7]),
        .I4(water_line[5]),
        .I5(water_line[6]),
        .O(\seg_OBUF[6]_inst_i_11_n_0 ));
  LUT6 #(
    .INIT(64'hA7A7A787A7A7A78F)) 
    \seg_OBUF[6]_inst_i_12 
       (.I0(water_line[6]),
        .I1(water_line[5]),
        .I2(water_line[7]),
        .I3(water_line[3]),
        .I4(water_line[4]),
        .I5(water_line[2]),
        .O(\seg_OBUF[6]_inst_i_12_n_0 ));
  LUT6 #(
    .INIT(64'h9494564294D44642)) 
    \seg_OBUF[6]_inst_i_17 
       (.I0(water_line[6]),
        .I1(water_line[5]),
        .I2(water_line[7]),
        .I3(water_line[3]),
        .I4(water_line[4]),
        .I5(water_line[2]),
        .O(\seg_OBUF[6]_inst_i_17_n_0 ));
  LUT6 #(
    .INIT(64'h0F00F0F9F0F60F00)) 
    \seg_OBUF[6]_inst_i_18 
       (.I0(water_line[3]),
        .I1(\seg_OBUF[6]_inst_i_28_n_0 ),
        .I2(water_line[1]),
        .I3(\seg_OBUF[6]_inst_i_29_n_0 ),
        .I4(water_line[2]),
        .I5(\seg_OBUF[6]_inst_i_11_n_0 ),
        .O(\seg_OBUF[6]_inst_i_18_n_0 ));
  LUT6 #(
    .INIT(64'hFDFDFDFDFFFCFCFF)) 
    \seg_OBUF[6]_inst_i_2 
       (.I0(\status_mode_reg[1] ),
        .I1(\num_reg[2] [0]),
        .I2(\num_reg[2] [1]),
        .I3(water_line[1]),
        .I4(\seg_OBUF[6]_inst_i_8_n_0 ),
        .I5(\FSM_onehot_state_reg[5] ),
        .O(\seg_OBUF[6]_inst_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h407F)) 
    \seg_OBUF[6]_inst_i_20 
       (.I0(\status_mode_reg[0] ),
        .I1(\FSM_onehot_state_reg[6] ),
        .I2(\timer_set_reg[3]_0 ),
        .I3(water_line_reg__0),
        .O(\seg_OBUF[6]_inst_i_20_n_0 ));
  LUT6 #(
    .INIT(64'hEFEEEEEFEAEEEEEA)) 
    \seg_OBUF[6]_inst_i_26 
       (.I0(\num_reg[2] [0]),
        .I1(\seg_OBUF[6]_inst_i_29_n_0 ),
        .I2(water_line[1]),
        .I3(water_line[2]),
        .I4(\seg_OBUF[6]_inst_i_11_n_0 ),
        .I5(\seg_OBUF[6]_inst_i_37_n_0 ),
        .O(\seg_OBUF[6]_inst_i_26_n_0 ));
  LUT5 #(
    .INIT(32'hAA2A8AA8)) 
    \seg_OBUF[6]_inst_i_27 
       (.I0(\num_reg[2] [0]),
        .I1(\seg_OBUF[6]_inst_i_11_n_0 ),
        .I2(\seg_OBUF[6]_inst_i_28_n_0 ),
        .I3(\seg_OBUF[6]_inst_i_38_n_0 ),
        .I4(\seg_OBUF[6]_inst_i_39_n_0 ),
        .O(\seg_OBUF[6]_inst_i_27_n_0 ));
  LUT5 #(
    .INIT(32'hC71CF10F)) 
    \seg_OBUF[6]_inst_i_28 
       (.I0(water_line[3]),
        .I1(water_line[4]),
        .I2(water_line[7]),
        .I3(water_line[5]),
        .I4(water_line[6]),
        .O(\seg_OBUF[6]_inst_i_28_n_0 ));
  LUT6 #(
    .INIT(64'h0821420810428410)) 
    \seg_OBUF[6]_inst_i_29 
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .I2(water_line[4]),
        .I3(water_line[7]),
        .I4(water_line[5]),
        .I5(water_line[6]),
        .O(\seg_OBUF[6]_inst_i_29_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAAAEBAA)) 
    \seg_OBUF[6]_inst_i_3 
       (.I0(\num_reg[2]_1 ),
        .I1(\seg_OBUF[6]_inst_i_11_n_0 ),
        .I2(\seg_OBUF[6]_inst_i_12_n_0 ),
        .I3(\num_reg[2] [0]),
        .I4(\FSM_onehot_state_reg[5] ),
        .I5(\num_reg[2] [1]),
        .O(\seg_OBUF[6]_inst_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hC3493492)) 
    \seg_OBUF[6]_inst_i_37 
       (.I0(water_line[6]),
        .I1(water_line[5]),
        .I2(water_line[7]),
        .I3(water_line[4]),
        .I4(water_line[3]),
        .O(\seg_OBUF[6]_inst_i_37_n_0 ));
  LUT3 #(
    .INIT(8'h1F)) 
    \seg_OBUF[6]_inst_i_38 
       (.I0(water_line[6]),
        .I1(water_line[5]),
        .I2(water_line[7]),
        .O(\seg_OBUF[6]_inst_i_38_n_0 ));
  LUT4 #(
    .INIT(16'h73C7)) 
    \seg_OBUF[6]_inst_i_39 
       (.I0(water_line[4]),
        .I1(water_line[6]),
        .I2(water_line[7]),
        .I3(water_line[5]),
        .O(\seg_OBUF[6]_inst_i_39_n_0 ));
  LUT6 #(
    .INIT(64'hAAAEAAAEFFFFFFAE)) 
    \seg_OBUF[6]_inst_i_5 
       (.I0(\num_reg[2]_0 ),
        .I1(\seg_OBUF[6]_inst_i_17_n_0 ),
        .I2(an_OBUF),
        .I3(\FSM_onehot_state_reg[5] ),
        .I4(\seg_OBUF[6]_inst_i_18_n_0 ),
        .I5(\num_reg[0] ),
        .O(\seg_OBUF[6]_inst_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h00000000FFF4F4F4)) 
    \seg_OBUF[6]_inst_i_6 
       (.I0(\seg_OBUF[6]_inst_i_20_n_0 ),
        .I1(\num_reg[0]_0 ),
        .I2(\num_reg[2]_2 ),
        .I3(\seg_OBUF[6]_inst_i_8_n_0 ),
        .I4(\num_reg[0]_1 ),
        .I5(\num_reg[1]_1 ),
        .O(\seg_OBUF[6]_inst_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAAAAAAE)) 
    \seg_OBUF[6]_inst_i_7 
       (.I0(\num_reg[1]_0 ),
        .I1(\seg_OBUF[6]_inst_i_26_n_0 ),
        .I2(\seg_OBUF[6]_inst_i_27_n_0 ),
        .I3(\num_reg[2] [1]),
        .I4(\FSM_onehot_state_reg[5] ),
        .I5(\num_reg[2] [2]),
        .O(\seg_OBUF[6]_inst_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hFF90FF66FF99FF90)) 
    \seg_OBUF[6]_inst_i_8 
       (.I0(water_line[3]),
        .I1(\seg_OBUF[6]_inst_i_28_n_0 ),
        .I2(water_line[1]),
        .I3(\seg_OBUF[6]_inst_i_29_n_0 ),
        .I4(water_line[2]),
        .I5(\seg_OBUF[6]_inst_i_11_n_0 ),
        .O(\seg_OBUF[6]_inst_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAAAAAAB)) 
    \surplus_all_reg[0]_i_1 
       (.I0(\surplus_curr_reg[0]_i_3_n_0 ),
        .I1(\surplus_all_reg[0]_i_2_n_0 ),
        .I2(out[9]),
        .I3(out[10]),
        .I4(out[8]),
        .I5(D[2]),
        .O(\seg[4] [0]));
  LUT6 #(
    .INIT(64'hAA28AAAAA200AAAA)) 
    \surplus_all_reg[0]_i_2 
       (.I0(\surplus_curr_reg[0]_i_4_n_0 ),
        .I1(Q[0]),
        .I2(\status_mode_reg[1] ),
        .I3(\status_mode_reg[2] ),
        .I4(\FSM_onehot_state_reg[6] ),
        .I5(\status_mode_reg[0] ),
        .O(\surplus_all_reg[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h4F4F4F4F444F4444)) 
    \surplus_all_reg[1]_i_1 
       (.I0(\FSM_onehot_state_reg[9]_0 ),
        .I1(timer_set[1]),
        .I2(\surplus_all_reg[1]_i_3_n_0 ),
        .I3(\surplus_all_reg[1]_i_4_n_0 ),
        .I4(D[1]),
        .I5(\surplus_all_reg[1]_i_5_n_0 ),
        .O(\seg[4] [1]));
  LUT6 #(
    .INIT(64'hAABAAAAAAABAAABA)) 
    \surplus_all_reg[1]_i_3 
       (.I0(D[3]),
        .I1(\surplus_all_reg[1]_i_6_n_0 ),
        .I2(D[2]),
        .I3(\surplus_curr_reg[1]_i_4_n_0 ),
        .I4(\surplus_all_reg[1]_i_7_n_0 ),
        .I5(\FSM_onehot_state_reg[6] ),
        .O(\surplus_all_reg[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFF0CFCFFFEEFF55)) 
    \surplus_all_reg[1]_i_4 
       (.I0(timer_set[1]),
        .I1(\status_mode_reg[0] ),
        .I2(\surplus_curr_reg[1]_i_8_n_0 ),
        .I3(\status_mode_reg[2] ),
        .I4(\status_mode_reg[1] ),
        .I5(D[0]),
        .O(\surplus_all_reg[1]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFEAAEAEEA)) 
    \surplus_all_reg[1]_i_5 
       (.I0(\status_weight_reg[0]_0 ),
        .I1(\status_mode_reg[2]_0 ),
        .I2(timer_set[0]),
        .I3(timer_set[1]),
        .I4(\status_mode_reg[1] ),
        .I5(D[2]),
        .O(\surplus_all_reg[1]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0000420000244224)) 
    \surplus_all_reg[1]_i_6 
       (.I0(D[0]),
        .I1(D[1]),
        .I2(timer_set[1]),
        .I3(\status_mode_reg[1] ),
        .I4(\status_mode_reg[2] ),
        .I5(\status_mode_reg[0] ),
        .O(\surplus_all_reg[1]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h14414141D77D7D7D)) 
    \surplus_all_reg[1]_i_7 
       (.I0(next_state1),
        .I1(Q[1]),
        .I2(timer_set[1]),
        .I3(Q[0]),
        .I4(timer_set[0]),
        .I5(next_state15_out),
        .O(\surplus_all_reg[1]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0100FFFF01000000)) 
    \surplus_all_reg[2]_i_1 
       (.I0(\status_mode_reg[2] ),
        .I1(\status_mode_reg[1] ),
        .I2(\status_mode_reg[0] ),
        .I3(timer_set[2]),
        .I4(D[3]),
        .I5(\surplus_all_reg[2]_i_2_n_0 ),
        .O(\seg[4] [2]));
  LUT5 #(
    .INIT(32'hFFFFF63C)) 
    \surplus_all_reg[2]_i_10 
       (.I0(timer_set[1]),
        .I1(timer_set[2]),
        .I2(\status_mode_reg[0] ),
        .I3(\status_mode_reg[1] ),
        .I4(\status_mode_reg[2] ),
        .O(\surplus_all_reg[2]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'hC0CFC0CFD0D0DFDF)) 
    \surplus_all_reg[2]_i_2 
       (.I0(\surplus_all_reg[2]_i_3_n_0 ),
        .I1(\surplus_all_reg[2]_i_4_n_0 ),
        .I2(D[2]),
        .I3(\surplus_all_reg[2]_i_5_n_0 ),
        .I4(\surplus_all_reg[2]_i_6_n_0 ),
        .I5(D[1]),
        .O(\surplus_all_reg[2]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h88888888BBBBBB8B)) 
    \surplus_all_reg[2]_i_3 
       (.I0(\surplus_all_reg[2]_i_7_n_0 ),
        .I1(D[0]),
        .I2(\status_mode_reg[1] ),
        .I3(\status_mode_reg[2] ),
        .I4(\surplus_curr_reg[2]_i_6_n_0 ),
        .I5(\surplus_all_reg[2]_i_8_n_0 ),
        .O(\surplus_all_reg[2]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFAEEAAEAAAAAAAA)) 
    \surplus_all_reg[2]_i_4 
       (.I0(\surplus_curr_reg[2]_i_4_n_0 ),
        .I1(next_state1),
        .I2(timer_set[1]),
        .I3(timer_set[2]),
        .I4(next_state15_out),
        .I5(\FSM_onehot_state_reg[6]_0 ),
        .O(\surplus_all_reg[2]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h00FDFFFF00FD0000)) 
    \surplus_all_reg[2]_i_5 
       (.I0(\status_mode_reg[1] ),
        .I1(\status_mode_reg[2] ),
        .I2(\surplus_curr_reg[2]_i_8_n_0 ),
        .I3(\surplus_all_reg[2]_i_9_n_0 ),
        .I4(D[0]),
        .I5(\surplus_all_reg[2]_i_10_n_0 ),
        .O(\surplus_all_reg[2]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h00000000FFFFC6F6)) 
    \surplus_all_reg[2]_i_6 
       (.I0(\surplus_curr_reg[2]_i_12_n_0 ),
        .I1(\status_mode_reg[0] ),
        .I2(\status_mode_reg[1] ),
        .I3(\surplus_curr_reg[2]_i_7_n_0 ),
        .I4(\status_mode_reg[2]_3 ),
        .I5(\status_mode_reg[2]_6 ),
        .O(\surplus_all_reg[2]_i_6_n_0 ));
  LUT5 #(
    .INIT(32'hDEFFDEF0)) 
    \surplus_all_reg[2]_i_7 
       (.I0(timer_set[1]),
        .I1(\status_mode_reg[2] ),
        .I2(timer_set[2]),
        .I3(\status_mode_reg[1] ),
        .I4(\status_mode_reg[0] ),
        .O(\surplus_all_reg[2]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h2888888288828882)) 
    \surplus_all_reg[2]_i_8 
       (.I0(next_state1),
        .I1(timer_set[2]),
        .I2(timer_set[1]),
        .I3(Q[1]),
        .I4(Q[0]),
        .I5(timer_set[0]),
        .O(\surplus_all_reg[2]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h0002AAA802AAA800)) 
    \surplus_all_reg[2]_i_9 
       (.I0(next_state1),
        .I1(timer_set[0]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(timer_set[2]),
        .I5(timer_set[1]),
        .O(\surplus_all_reg[2]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hBABBBAAABABBBABB)) 
    \surplus_all_reg[3]_i_1 
       (.I0(\surplus_all_reg[3]_i_2_n_0 ),
        .I1(D[3]),
        .I2(\surplus_all_reg[3]_i_3_n_0 ),
        .I3(D[2]),
        .I4(\surplus_all_reg[3]_i_4_n_0 ),
        .I5(\surplus_all_reg[3]_i_5_n_0 ),
        .O(\seg[4] [3]));
  LUT3 #(
    .INIT(8'h56)) 
    \surplus_all_reg[3]_i_11 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .I2(timer_set[1]),
        .O(\surplus_all_reg[3]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'hFFCFCFEFFFCFFFDF)) 
    \surplus_all_reg[3]_i_12 
       (.I0(timer_set[2]),
        .I1(\status_mode_reg[2] ),
        .I2(\FSM_onehot_state_reg[6]_0 ),
        .I3(\status_mode_reg[0] ),
        .I4(\status_mode_reg[1] ),
        .I5(timer_set[3]),
        .O(\surplus_all_reg[3]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'hF00FC30FE10F870F)) 
    \surplus_all_reg[3]_i_13 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(timer_set[3]),
        .I3(timer_set[2]),
        .I4(timer_set[1]),
        .I5(timer_set[0]),
        .O(\surplus_all_reg[3]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h051400000514F00F)) 
    \surplus_all_reg[3]_i_14 
       (.I0(\status_mode_reg[2] ),
        .I1(timer_set[1]),
        .I2(timer_set[3]),
        .I3(timer_set[2]),
        .I4(\status_mode_reg[1] ),
        .I5(\status_mode_reg[0] ),
        .O(\surplus_all_reg[3]_i_14_n_0 ));
  LUT6 #(
    .INIT(64'h807F00FF01FE05FA)) 
    \surplus_all_reg[3]_i_15 
       (.I0(timer_set[1]),
        .I1(timer_set[0]),
        .I2(timer_set[2]),
        .I3(timer_set[3]),
        .I4(Q[0]),
        .I5(Q[1]),
        .O(\surplus_all_reg[3]_i_15_n_0 ));
  LUT6 #(
    .INIT(64'h0808080808080800)) 
    \surplus_all_reg[3]_i_2 
       (.I0(timer_set[3]),
        .I1(next_state1),
        .I2(\status_mode_reg[2] ),
        .I3(out[8]),
        .I4(out[10]),
        .I5(out[9]),
        .O(\surplus_all_reg[3]_i_2_n_0 ));
  MUXF7 \surplus_all_reg[3]_i_3 
       (.I0(\surplus_all_reg[3]_i_6_n_0 ),
        .I1(\surplus_all_reg[3]_i_7_n_0 ),
        .O(\surplus_all_reg[3]_i_3_n_0 ),
        .S(D[1]));
  LUT6 #(
    .INIT(64'h4F4F4F4F4FFFFFFF)) 
    \surplus_all_reg[3]_i_4 
       (.I0(\surplus_all_reg[3]_i_8_n_0 ),
        .I1(\status_mode_reg[2]_4 ),
        .I2(\status_weight_reg[1]_0 ),
        .I3(\status_mode_reg[1] ),
        .I4(\surplus_all_reg[3]_i_11_n_0 ),
        .I5(\surplus_all_reg[3]_i_12_n_0 ),
        .O(\surplus_all_reg[3]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFF7F7777FF7FFF7F)) 
    \surplus_all_reg[3]_i_5 
       (.I0(D[1]),
        .I1(D[0]),
        .I2(next_state1),
        .I3(\surplus_all_reg[3]_i_13_n_0 ),
        .I4(\surplus_curr_reg[3]_i_7_n_0 ),
        .I5(next_state15_out),
        .O(\surplus_all_reg[3]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h8B88BBBB8B888B88)) 
    \surplus_all_reg[3]_i_6 
       (.I0(\surplus_all_reg[3]_i_14_n_0 ),
        .I1(D[0]),
        .I2(\surplus_curr_reg[3]_i_11_n_0 ),
        .I3(next_state15_out),
        .I4(\surplus_all_reg[3]_i_15_n_0 ),
        .I5(next_state1),
        .O(\surplus_all_reg[3]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAAAAFFEAEAEA)) 
    \surplus_all_reg[3]_i_7 
       (.I0(\surplus_curr_reg[3]_i_6_n_0 ),
        .I1(\surplus_all_reg[3]_i_11_n_0 ),
        .I2(next_state1),
        .I3(timer_set[3]),
        .I4(next_state15_out),
        .I5(D[0]),
        .O(\surplus_all_reg[3]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hCEEFEFEBB998989C)) 
    \surplus_all_reg[3]_i_8 
       (.I0(\status_mode_reg[0] ),
        .I1(\status_mode_reg[1] ),
        .I2(timer_set[2]),
        .I3(timer_set[1]),
        .I4(timer_set[0]),
        .I5(timer_set[3]),
        .O(\surplus_all_reg[3]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h00000000AAAAAAA2)) 
    \surplus_all_reg[4]_i_1 
       (.I0(\surplus_all_reg[4]_i_2_n_0 ),
        .I1(\surplus_all_reg[4]_i_3_n_0 ),
        .I2(\surplus_all_reg[4]_i_4_n_0 ),
        .I3(\surplus_all_reg[4]_i_5_n_0 ),
        .I4(\surplus_all_reg[4]_i_6_n_0 ),
        .I5(D[3]),
        .O(\seg[4] [4]));
  LUT6 #(
    .INIT(64'hFFFFF0E0070FFFF8)) 
    \surplus_all_reg[4]_i_10 
       (.I0(timer_set[0]),
        .I1(timer_set[1]),
        .I2(timer_set[3]),
        .I3(timer_set[2]),
        .I4(\status_mode_reg[0] ),
        .I5(\status_mode_reg[1] ),
        .O(\surplus_all_reg[4]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h0D00F500FD00F500)) 
    \surplus_all_reg[4]_i_11 
       (.I0(\surplus_all_reg[4]_i_17_n_0 ),
        .I1(timer_set[0]),
        .I2(Q[1]),
        .I3(next_state1),
        .I4(Q[0]),
        .I5(\surplus_all_reg[5]_i_5_n_0 ),
        .O(\surplus_all_reg[4]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFF01FF88)) 
    \surplus_all_reg[4]_i_15 
       (.I0(timer_set[2]),
        .I1(timer_set[3]),
        .I2(timer_set[1]),
        .I3(\status_mode_reg[2] ),
        .I4(\status_mode_reg[1] ),
        .I5(\status_mode_reg[0] ),
        .O(\surplus_all_reg[4]_i_15_n_0 ));
  LUT5 #(
    .INIT(32'hEFE0EFEF)) 
    \surplus_all_reg[4]_i_16 
       (.I0(\surplus_curr_reg[4]_i_4_n_0 ),
        .I1(\status_mode_reg[2] ),
        .I2(\status_mode_reg[1] ),
        .I3(\status_mode_reg[0] ),
        .I4(\surplus_all_reg[5]_i_7_n_0 ),
        .O(\surplus_all_reg[4]_i_16_n_0 ));
  LUT3 #(
    .INIT(8'h01)) 
    \surplus_all_reg[4]_i_17 
       (.I0(timer_set[2]),
        .I1(timer_set[3]),
        .I2(timer_set[1]),
        .O(\surplus_all_reg[4]_i_17_n_0 ));
  LUT6 #(
    .INIT(64'hFDFDFCFCFDFDFCFF)) 
    \surplus_all_reg[4]_i_2 
       (.I0(\surplus_all_reg[4]_i_7_n_0 ),
        .I1(D[2]),
        .I2(\status_mode_reg[0]_4 ),
        .I3(\status_mode_reg[2]_3 ),
        .I4(D[1]),
        .I5(\surplus_all_reg[4]_i_10_n_0 ),
        .O(\surplus_all_reg[4]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h5455FFFF)) 
    \surplus_all_reg[4]_i_3 
       (.I0(\surplus_all_reg[4]_i_11_n_0 ),
        .I1(\surplus_curr_reg[4]_i_13_n_0 ),
        .I2(\status_mode_reg[2] ),
        .I3(\status_mode_reg[1] ),
        .I4(\FSM_onehot_state_reg[6] ),
        .O(\surplus_all_reg[4]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h0000E000)) 
    \surplus_all_reg[4]_i_4 
       (.I0(timer_set[0]),
        .I1(timer_set[1]),
        .I2(timer_set[3]),
        .I3(timer_set[2]),
        .I4(\status_mode_reg[2]_5 ),
        .O(\surplus_all_reg[4]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h80808000FFFFFFFF)) 
    \surplus_all_reg[4]_i_5 
       (.I0(timer_set[3]),
        .I1(\FSM_onehot_state_reg[6]_0 ),
        .I2(next_state1),
        .I3(timer_set[2]),
        .I4(timer_set[1]),
        .I5(D[2]),
        .O(\surplus_all_reg[4]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAA808880A8808880)) 
    \surplus_all_reg[4]_i_6 
       (.I0(\FSM_onehot_state_reg[6]_1 ),
        .I1(next_state1),
        .I2(timer_set[2]),
        .I3(timer_set[3]),
        .I4(next_state15_out),
        .I5(timer_set[1]),
        .O(\surplus_all_reg[4]_i_6_n_0 ));
  MUXF7 \surplus_all_reg[4]_i_7 
       (.I0(\surplus_all_reg[4]_i_15_n_0 ),
        .I1(\surplus_all_reg[4]_i_16_n_0 ),
        .O(\surplus_all_reg[4]_i_7_n_0 ),
        .S(D[0]));
  LUT6 #(
    .INIT(64'hF100FFFFF100F100)) 
    \surplus_all_reg[5]_i_1 
       (.I0(\surplus_all_reg[5]_i_2_n_0 ),
        .I1(D[1]),
        .I2(\surplus_all_reg[5]_i_3_n_0 ),
        .I3(\timer_set_reg[3]_0 ),
        .I4(\status_weight_reg[1] ),
        .I5(\surplus_all_reg[5]_i_5_n_0 ),
        .O(\seg[4] [5]));
  LUT6 #(
    .INIT(64'hFFFFFF00FFFF5757)) 
    \surplus_all_reg[5]_i_2 
       (.I0(next_state1),
        .I1(Q[1]),
        .I2(Q[0]),
        .I3(\surplus_all_reg[5]_i_6_n_0 ),
        .I4(\status_mode_reg[2] ),
        .I5(D[0]),
        .O(\surplus_all_reg[5]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h500000005C000000)) 
    \surplus_all_reg[5]_i_3 
       (.I0(\surplus_all_reg[5]_i_7_n_0 ),
        .I1(\surplus_all_reg[5]_i_8_n_0 ),
        .I2(D[0]),
        .I3(D[1]),
        .I4(next_state1),
        .I5(\status_mode_reg[2] ),
        .O(\surplus_all_reg[5]_i_3_n_0 ));
  LUT4 #(
    .INIT(16'h8000)) 
    \surplus_all_reg[5]_i_5 
       (.I0(timer_set[2]),
        .I1(timer_set[0]),
        .I2(timer_set[1]),
        .I3(timer_set[3]),
        .O(\surplus_all_reg[5]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF33370111)) 
    \surplus_all_reg[5]_i_6 
       (.I0(timer_set[2]),
        .I1(timer_set[3]),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(\status_mode_reg[1] ),
        .I5(\status_mode_reg[0] ),
        .O(\surplus_all_reg[5]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h0137FFFFFFFFFFFF)) 
    \surplus_all_reg[5]_i_7 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(timer_set[0]),
        .I3(timer_set[1]),
        .I4(timer_set[3]),
        .I5(timer_set[2]),
        .O(\surplus_all_reg[5]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \surplus_all_reg[5]_i_8 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .O(\surplus_all_reg[5]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF00000001)) 
    \surplus_curr_reg[0]_i_1 
       (.I0(\surplus_curr_reg[0]_i_2_n_0 ),
        .I1(out[9]),
        .I2(out[10]),
        .I3(out[8]),
        .I4(D[2]),
        .I5(\surplus_curr_reg[0]_i_3_n_0 ),
        .O(\seg[4]_0 [0]));
  LUT6 #(
    .INIT(64'h8AA2A888AAAAAAAA)) 
    \surplus_curr_reg[0]_i_2 
       (.I0(\surplus_curr_reg[0]_i_4_n_0 ),
        .I1(\status_mode_reg[2] ),
        .I2(\status_mode_reg[0] ),
        .I3(\status_mode_reg[1] ),
        .I4(Q[0]),
        .I5(\FSM_onehot_state_reg[6] ),
        .O(\surplus_curr_reg[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h04F4040404040404)) 
    \surplus_curr_reg[0]_i_3 
       (.I0(\surplus_curr_reg[0]_i_5_n_0 ),
        .I1(D[2]),
        .I2(D[3]),
        .I3(\status_mode_reg[2] ),
        .I4(next_state1),
        .I5(timer_set[0]),
        .O(\surplus_curr_reg[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h577700005777F5FF)) 
    \surplus_curr_reg[0]_i_4 
       (.I0(D[1]),
        .I1(\status_mode_reg[1]_0 ),
        .I2(Q[0]),
        .I3(\status_mode_reg[1]_1 ),
        .I4(timer_set[0]),
        .I5(\status_mode_reg[2]_0 ),
        .O(\surplus_curr_reg[0]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFAFAFAFAFA0A0AC2)) 
    \surplus_curr_reg[0]_i_5 
       (.I0(\status_mode_reg[2]_5 ),
        .I1(Q[0]),
        .I2(timer_set[0]),
        .I3(D[0]),
        .I4(D[1]),
        .I5(\status_mode_reg[0]_2 ),
        .O(\surplus_curr_reg[0]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hC0AAC0AAC0FFC000)) 
    \surplus_curr_reg[1]_i_1 
       (.I0(\surplus_curr_reg[1]_i_2_n_0 ),
        .I1(timer_set[1]),
        .I2(\status_mode_reg[0]_0 ),
        .I3(D[3]),
        .I4(\surplus_curr_reg[1]_i_3_n_0 ),
        .I5(D[2]),
        .O(\seg[4]_0 [1]));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAFBAFAB)) 
    \surplus_curr_reg[1]_i_2 
       (.I0(\surplus_curr_reg[1]_i_4_n_0 ),
        .I1(\surplus_curr_reg[1]_i_5_n_0 ),
        .I2(D[1]),
        .I3(D[0]),
        .I4(timer_set[1]),
        .I5(\status_mode_reg[0]_2 ),
        .O(\surplus_curr_reg[1]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hCCCDCCCDCCCDFCCD)) 
    \surplus_curr_reg[1]_i_3 
       (.I0(\status_mode_reg[2]_1 ),
        .I1(\surplus_curr_reg[1]_i_7_n_0 ),
        .I2(D[1]),
        .I3(D[0]),
        .I4(\status_mode_reg[0]_2 ),
        .I5(\surplus_curr_reg[1]_i_8_n_0 ),
        .O(\surplus_curr_reg[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000000090000000)) 
    \surplus_curr_reg[1]_i_4 
       (.I0(timer_set[1]),
        .I1(timer_set[0]),
        .I2(D[1]),
        .I3(D[0]),
        .I4(next_state1),
        .I5(\status_mode_reg[2] ),
        .O(\surplus_curr_reg[1]_i_4_n_0 ));
  LUT4 #(
    .INIT(16'h6999)) 
    \surplus_curr_reg[1]_i_5 
       (.I0(Q[1]),
        .I1(timer_set[1]),
        .I2(Q[0]),
        .I3(timer_set[0]),
        .O(\surplus_curr_reg[1]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h00000012000000C0)) 
    \surplus_curr_reg[1]_i_7 
       (.I0(timer_set[0]),
        .I1(D[1]),
        .I2(timer_set[1]),
        .I3(\status_mode_reg[1]_2 ),
        .I4(\status_mode_reg[2] ),
        .I5(D[0]),
        .O(\surplus_curr_reg[1]_i_7_n_0 ));
  LUT4 #(
    .INIT(16'h9996)) 
    \surplus_curr_reg[1]_i_8 
       (.I0(Q[1]),
        .I1(timer_set[1]),
        .I2(Q[0]),
        .I3(timer_set[0]),
        .O(\surplus_curr_reg[1]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h88888888BBB8BBBB)) 
    \surplus_curr_reg[2]_i_1 
       (.I0(\surplus_curr_reg[2]_i_2_n_0 ),
        .I1(D[3]),
        .I2(\surplus_curr_reg[2]_i_3_n_0 ),
        .I3(\surplus_curr_reg[2]_i_4_n_0 ),
        .I4(D[2]),
        .I5(\surplus_curr_reg[2]_i_5_n_0 ),
        .O(\seg[4]_0 [2]));
  LUT3 #(
    .INIT(8'h6A)) 
    \surplus_curr_reg[2]_i_12 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(timer_set[0]),
        .O(\surplus_curr_reg[2]_i_12_n_0 ));
  LUT4 #(
    .INIT(16'h0100)) 
    \surplus_curr_reg[2]_i_2 
       (.I0(\status_mode_reg[2] ),
        .I1(\status_mode_reg[1] ),
        .I2(\status_mode_reg[0] ),
        .I3(timer_set[2]),
        .O(\surplus_curr_reg[2]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0041500000415055)) 
    \surplus_curr_reg[2]_i_3 
       (.I0(\status_mode_reg[0]_2 ),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .I3(D[1]),
        .I4(D[0]),
        .I5(\surplus_curr_reg[2]_i_6_n_0 ),
        .O(\surplus_curr_reg[2]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000040)) 
    \surplus_curr_reg[2]_i_4 
       (.I0(\surplus_curr_reg[2]_i_7_n_0 ),
        .I1(D[1]),
        .I2(D[0]),
        .I3(\status_mode_reg[0] ),
        .I4(\status_mode_reg[1] ),
        .I5(\status_mode_reg[2] ),
        .O(\surplus_curr_reg[2]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hE0E0F0F0F0F0F000)) 
    \surplus_curr_reg[2]_i_5 
       (.I0(\status_mode_reg[0]_2 ),
        .I1(\surplus_curr_reg[2]_i_8_n_0 ),
        .I2(\surplus_curr_reg[2]_i_9_n_0 ),
        .I3(\status_weight_reg[0] ),
        .I4(D[1]),
        .I5(D[0]),
        .O(\surplus_curr_reg[2]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'hC9939393)) 
    \surplus_curr_reg[2]_i_6 
       (.I0(timer_set[1]),
        .I1(timer_set[2]),
        .I2(Q[1]),
        .I3(Q[0]),
        .I4(timer_set[0]),
        .O(\surplus_curr_reg[2]_i_6_n_0 ));
  LUT3 #(
    .INIT(8'hA9)) 
    \surplus_curr_reg[2]_i_7 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(timer_set[0]),
        .O(\surplus_curr_reg[2]_i_7_n_0 ));
  LUT5 #(
    .INIT(32'h6C6C6CC9)) 
    \surplus_curr_reg[2]_i_8 
       (.I0(timer_set[1]),
        .I1(timer_set[2]),
        .I2(Q[1]),
        .I3(Q[0]),
        .I4(timer_set[0]),
        .O(\surplus_curr_reg[2]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h00000000007F7F7F)) 
    \surplus_curr_reg[2]_i_9 
       (.I0(D[1]),
        .I1(timer_set[2]),
        .I2(\status_mode_reg[1]_0 ),
        .I3(\status_mode_reg[2]_0 ),
        .I4(\surplus_curr_reg[2]_i_12_n_0 ),
        .I5(D[2]),
        .O(\surplus_curr_reg[2]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hC055C000C055C0FF)) 
    \surplus_curr_reg[3]_i_1 
       (.I0(\surplus_curr_reg[3]_i_2_n_0 ),
        .I1(timer_set[3]),
        .I2(\status_mode_reg[0]_0 ),
        .I3(D[3]),
        .I4(D[2]),
        .I5(\surplus_curr_reg[3]_i_4_n_0 ),
        .O(\seg[4]_0 [3]));
  LUT6 #(
    .INIT(64'h5A7878F078F078F0)) 
    \surplus_curr_reg[3]_i_11 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(timer_set[3]),
        .I3(Q[1]),
        .I4(Q[0]),
        .I5(timer_set[0]),
        .O(\surplus_curr_reg[3]_i_11_n_0 ));
  LUT4 #(
    .INIT(16'h6AAA)) 
    \surplus_curr_reg[3]_i_12 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .I2(timer_set[0]),
        .I3(timer_set[1]),
        .O(\surplus_curr_reg[3]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'h2A2A2A0A2A2A2A2A)) 
    \surplus_curr_reg[3]_i_2 
       (.I0(\surplus_curr_reg[3]_i_5_n_0 ),
        .I1(\surplus_curr_reg[3]_i_6_n_0 ),
        .I2(D[1]),
        .I3(\status_mode_reg[0]_2 ),
        .I4(D[0]),
        .I5(timer_set[3]),
        .O(\surplus_curr_reg[3]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h000D0D0D000D000D)) 
    \surplus_curr_reg[3]_i_4 
       (.I0(\status_mode_reg[0]_1 ),
        .I1(\surplus_curr_reg[3]_i_7_n_0 ),
        .I2(\surplus_curr_reg[3]_i_8_n_0 ),
        .I3(\FSM_onehot_state_reg[6] ),
        .I4(\status_mode_reg[0]_3 ),
        .I5(\status_mode_reg[2]_2 ),
        .O(\surplus_curr_reg[3]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFF2EFF2EFF2EFFFF)) 
    \surplus_curr_reg[3]_i_5 
       (.I0(\surplus_curr_reg[3]_i_11_n_0 ),
        .I1(D[0]),
        .I2(\surplus_all_reg[3]_i_11_n_0 ),
        .I3(D[1]),
        .I4(next_state15_out),
        .I5(next_state1),
        .O(\surplus_curr_reg[3]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h00000000666C0000)) 
    \surplus_curr_reg[3]_i_6 
       (.I0(timer_set[2]),
        .I1(timer_set[3]),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(next_state1),
        .I5(\status_mode_reg[2]_3 ),
        .O(\surplus_curr_reg[3]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h36363C3C363C3C6C)) 
    \surplus_curr_reg[3]_i_7 
       (.I0(timer_set[1]),
        .I1(timer_set[3]),
        .I2(timer_set[2]),
        .I3(Q[0]),
        .I4(Q[1]),
        .I5(timer_set[0]),
        .O(\surplus_curr_reg[3]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000C50)) 
    \surplus_curr_reg[3]_i_8 
       (.I0(\surplus_curr_reg[3]_i_12_n_0 ),
        .I1(timer_set[3]),
        .I2(D[0]),
        .I3(D[1]),
        .I4(\status_mode_reg[2] ),
        .I5(\status_mode_reg[1]_2 ),
        .O(\surplus_curr_reg[3]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h0000FFF2000000F2)) 
    \surplus_curr_reg[4]_i_1 
       (.I0(\status_mode_reg[0]_1 ),
        .I1(\surplus_curr_reg[4]_i_4_n_0 ),
        .I2(\surplus_curr_reg[4]_i_5_n_0 ),
        .I3(D[2]),
        .I4(D[3]),
        .I5(\surplus_curr_reg[4]_i_6_n_0 ),
        .O(\seg[4]_0 [4]));
  LUT3 #(
    .INIT(8'hA8)) 
    \surplus_curr_reg[4]_i_11 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .I2(timer_set[1]),
        .O(\surplus_curr_reg[4]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h0515155515551555)) 
    \surplus_curr_reg[4]_i_13 
       (.I0(timer_set[3]),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .I3(Q[1]),
        .I4(Q[0]),
        .I5(timer_set[0]),
        .O(\surplus_curr_reg[4]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h00050007000F010F)) 
    \surplus_curr_reg[4]_i_4 
       (.I0(timer_set[1]),
        .I1(timer_set[0]),
        .I2(timer_set[3]),
        .I3(timer_set[2]),
        .I4(Q[0]),
        .I5(Q[1]),
        .O(\surplus_curr_reg[4]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h80FF8080)) 
    \surplus_curr_reg[4]_i_5 
       (.I0(Q[1]),
        .I1(\FSM_onehot_state_reg[6] ),
        .I2(next_state10_out),
        .I3(\surplus_curr_reg[4]_i_9_n_0 ),
        .I4(\status_mode_reg[2]_0 ),
        .O(\surplus_curr_reg[4]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF0008000B)) 
    \surplus_curr_reg[4]_i_6 
       (.I0(\surplus_curr_reg[4]_i_11_n_0 ),
        .I1(D[0]),
        .I2(\status_mode_reg[0]_2 ),
        .I3(D[1]),
        .I4(\surplus_curr_reg[4]_i_13_n_0 ),
        .I5(\surplus_all_reg[4]_i_4_n_0 ),
        .O(\surplus_curr_reg[4]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'h1555)) 
    \surplus_curr_reg[4]_i_9 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .I2(timer_set[0]),
        .I3(timer_set[1]),
        .O(\surplus_curr_reg[4]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h8888888888888B88)) 
    timer_out_i_1
       (.I0(timer_out),
        .I1(\timer_set[3]_i_3_n_0 ),
        .I2(timer_set[0]),
        .I3(timer_set[1]),
        .I4(timer_set[2]),
        .I5(timer_set[3]),
        .O(timer_out_i_1_n_0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    timer_out_reg
       (.C(CLK),
        .CE(1'b1),
        .D(timer_out_i_1_n_0),
        .Q(timer_out),
        .R(1'b0));
  LUT6 #(
    .INIT(64'h8B8B8B8B8B8B8B88)) 
    \timer_set[0]_i_1 
       (.I0(\timer_set[0]_i_2_n_0 ),
        .I1(\timer_set[3]_i_3_n_0 ),
        .I2(timer_set[0]),
        .I3(timer_set[1]),
        .I4(timer_set[3]),
        .I5(timer_set[2]),
        .O(\timer_set[0]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h2203223C)) 
    \timer_set[0]_i_2 
       (.I0(Q[0]),
        .I1(D[3]),
        .I2(D[2]),
        .I3(D[0]),
        .I4(D[1]),
        .O(\timer_set[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hBBBB88888888BBB8)) 
    \timer_set[1]_i_1 
       (.I0(\timer_set[1]_i_2_n_0 ),
        .I1(\timer_set[3]_i_3_n_0 ),
        .I2(timer_set[3]),
        .I3(timer_set[2]),
        .I4(timer_set[1]),
        .I5(timer_set[0]),
        .O(\timer_set[1]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h00263326)) 
    \timer_set[1]_i_2 
       (.I0(D[2]),
        .I1(D[3]),
        .I2(D[1]),
        .I3(D[0]),
        .I4(Q[1]),
        .O(\timer_set[1]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hBBBBBB88888888B8)) 
    \timer_set[2]_i_1 
       (.I0(\timer_set[2]_i_2_n_0 ),
        .I1(\timer_set[3]_i_3_n_0 ),
        .I2(timer_set[3]),
        .I3(timer_set[0]),
        .I4(timer_set[1]),
        .I5(timer_set[2]),
        .O(\timer_set[2]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h0000CCA0)) 
    \timer_set[2]_i_2 
       (.I0(D[2]),
        .I1(Q[1]),
        .I2(D[1]),
        .I3(D[0]),
        .I4(D[3]),
        .O(\timer_set[2]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h20FF2000)) 
    \timer_set[3]_i_1 
       (.I0(\timer_set_reg[3]_0 ),
        .I1(D[0]),
        .I2(D[1]),
        .I3(\timer_set[3]_i_3_n_0 ),
        .I4(\timer_set[3]_i_4_n_0 ),
        .O(\timer_set[3]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h00000001)) 
    \timer_set[3]_i_2 
       (.I0(D[3]),
        .I1(out[7]),
        .I2(out[6]),
        .I3(out[4]),
        .I4(out[5]),
        .O(\timer_set_reg[3]_0 ));
  LUT5 #(
    .INIT(32'h0000FFFE)) 
    \timer_set[3]_i_3 
       (.I0(\state_2_reg[3] [0]),
        .I1(\state_2_reg[3] [2]),
        .I2(\state_2_reg[3] [1]),
        .I3(\state_2_reg[3] [3]),
        .I4(\timer_set[3]_i_5_n_0 ),
        .O(\timer_set[3]_i_3_n_0 ));
  LUT4 #(
    .INIT(16'hAAA8)) 
    \timer_set[3]_i_4 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .I2(timer_set[0]),
        .I3(timer_set[1]),
        .O(\timer_set[3]_i_4_n_0 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \timer_set[3]_i_5 
       (.I0(\state_1_reg[3] [3]),
        .I1(\state_1_reg[3] [2]),
        .I2(\state_1_reg[3] [0]),
        .I3(\state_1_reg[3] [1]),
        .O(\timer_set[3]_i_5_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \timer_set_reg[0] 
       (.C(CLK),
        .CE(1'b1),
        .D(\timer_set[0]_i_1_n_0 ),
        .Q(timer_set[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \timer_set_reg[1] 
       (.C(CLK),
        .CE(1'b1),
        .D(\timer_set[1]_i_1_n_0 ),
        .Q(timer_set[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \timer_set_reg[2] 
       (.C(CLK),
        .CE(1'b1),
        .D(\timer_set[2]_i_1_n_0 ),
        .Q(timer_set[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \timer_set_reg[3] 
       (.C(CLK),
        .CE(1'b1),
        .D(\timer_set[3]_i_1_n_0 ),
        .Q(timer_set[3]),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \water_line[0]_i_1 
       (.I0(water_line_reg__0),
        .O(\water_line[0]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000010000)) 
    \water_line[7]_i_1 
       (.I0(out[9]),
        .I1(out[10]),
        .I2(out[8]),
        .I3(D[2]),
        .I4(\FSM_onehot_state_reg[6] ),
        .I5(\timer_set[3]_i_3_n_0 ),
        .O(\water_line[7]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h00000002)) 
    \water_line[7]_i_2 
       (.I0(D[0]),
        .I1(out[8]),
        .I2(out[10]),
        .I3(out[9]),
        .I4(\timer_set[3]_i_3_n_0 ),
        .O(\water_line[7]_i_2_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \water_line_reg[0] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(\water_line[0]_i_1_n_0 ),
        .Q(water_line_reg__0),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \water_line_reg[1] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(water_line_reg__0_carry_n_7),
        .Q(water_line[1]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \water_line_reg[2] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(water_line_reg__0_carry_n_6),
        .Q(water_line[2]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \water_line_reg[3] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(water_line_reg__0_carry_n_5),
        .Q(water_line[3]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \water_line_reg[4] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(water_line_reg__0_carry_n_4),
        .Q(water_line[4]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \water_line_reg[5] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(water_line_reg__0_carry__0_n_7),
        .Q(water_line[5]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \water_line_reg[6] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(water_line_reg__0_carry__0_n_6),
        .Q(water_line[6]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0),
    .IS_C_INVERTED(1'b1)) 
    \water_line_reg[7] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(water_line_reg__0_carry__0_n_5),
        .Q(water_line[7]),
        .R(\water_line[7]_i_1_n_0 ));
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY4 water_line_reg__0_carry
       (.CI(1'b0),
        .CO({water_line_reg__0_carry_n_0,NLW_water_line_reg__0_carry_CO_UNCONNECTED[2:0]}),
        .CYINIT(water_line_reg__0),
        .DI({water_line[3:1],water_line_reg__0_carry_i_1_n_0}),
        .O({water_line_reg__0_carry_n_4,water_line_reg__0_carry_n_5,water_line_reg__0_carry_n_6,water_line_reg__0_carry_n_7}),
        .S({water_line_reg__0_carry_i_2_n_0,water_line_reg__0_carry_i_3_n_0,water_line_reg__0_carry_i_4_n_0,water_line_reg__0_carry_i_5_n_0}));
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY4 water_line_reg__0_carry__0
       (.CI(water_line_reg__0_carry_n_0),
        .CO(NLW_water_line_reg__0_carry__0_CO_UNCONNECTED[3:0]),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,water_line[5:4]}),
        .O({NLW_water_line_reg__0_carry__0_O_UNCONNECTED[3],water_line_reg__0_carry__0_n_5,water_line_reg__0_carry__0_n_6,water_line_reg__0_carry__0_n_7}),
        .S({1'b0,water_line_reg__0_carry__0_i_1_n_0,water_line_reg__0_carry__0_i_2_n_0,water_line_reg__0_carry__0_i_3_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    water_line_reg__0_carry__0_i_1
       (.I0(water_line[6]),
        .I1(water_line[7]),
        .O(water_line_reg__0_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line_reg__0_carry__0_i_2
       (.I0(water_line[5]),
        .I1(water_line[6]),
        .O(water_line_reg__0_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line_reg__0_carry__0_i_3
       (.I0(water_line[4]),
        .I1(water_line[5]),
        .O(water_line_reg__0_carry__0_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    water_line_reg__0_carry_i_1
       (.I0(water_line[1]),
        .O(water_line_reg__0_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line_reg__0_carry_i_2
       (.I0(water_line[3]),
        .I1(water_line[4]),
        .O(water_line_reg__0_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line_reg__0_carry_i_3
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .O(water_line_reg__0_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line_reg__0_carry_i_4
       (.I0(water_line[1]),
        .I1(water_line[2]),
        .O(water_line_reg__0_carry_i_4_n_0));
  LUT6 #(
    .INIT(64'h5555555555565555)) 
    water_line_reg__0_carry_i_5
       (.I0(water_line[1]),
        .I1(out[8]),
        .I2(out[10]),
        .I3(out[9]),
        .I4(D[0]),
        .I5(D[1]),
        .O(water_line_reg__0_carry_i_5_n_0));
endmodule

(* ECO_CHECKSUM = "68ca584" *) 
(* NotValidForBitStream *)
module washing_machine
   (rst,
    pause_con,
    mode_change,
    weight_change,
    clk,
    light_power,
    light_running,
    light_xi,
    light_piao,
    light_tuo,
    light_in,
    light_out,
    light_buzzer,
    seg,
    an,
    temp,
    state);
  input rst;
  input pause_con;
  input mode_change;
  input weight_change;
  input clk;
  output light_power;
  output light_running;
  output light_xi;
  output light_piao;
  output light_tuo;
  output light_in;
  output light_out;
  output light_buzzer;
  output [6:0]seg;
  output [7:0]an;
  output temp;
  output [3:0]state;

  wire [7:0]an;
  wire [7:0]an_OBUF;
  wire clk;
  wire clk_F;
  wire clk_IBUF;
  wire clk_IBUF_BUFG;
  wire light_buzzer;
  wire light_in;
  wire light_out;
  wire light_piao;
  wire light_power;
  wire light_power_OBUF;
  wire light_running;
  wire light_running_OBUF;
  wire light_tuo;
  wire light_xi;
  wire mode_change;
  wire mode_change_IBUF;
  wire mode_change_IBUF_BUFG;
  wire my_coun_n_0;
  wire my_coun_n_11;
  wire my_coun_n_12;
  wire my_coun_n_13;
  wire my_coun_n_14;
  wire my_coun_n_4;
  wire my_machine_fsm_n_5;
  wire my_machine_fsm_n_6;
  wire my_machine_fsm_n_7;
  wire [0:0]\my_ssdisp/surplus_curr ;
  wire [2:0]num;
  wire pause_con;
  wire pause_con_IBUF;
  wire pause_con_IBUF_BUFG;
  wire rst;
  wire [6:0]seg;
  wire [6:0]seg_OBUF;
  wire [3:0]state;
  wire [3:0]state_OBUF;
  wire temp;
  wire temp_OBUF;
  wire temp_OBUF_BUFG;
  wire weight_change;
  wire weight_change_IBUF;
  wire weight_change_IBUF_BUFG;

initial begin
 $sdf_annotate("washing_machine_sim_time_impl.sdf",,,,"tool_control");
end
  OBUF \an_OBUF[0]_inst 
       (.I(an_OBUF[0]),
        .O(an[0]));
  OBUF \an_OBUF[1]_inst 
       (.I(an_OBUF[1]),
        .O(an[1]));
  OBUF \an_OBUF[2]_inst 
       (.I(1'b1),
        .O(an[2]));
  OBUF \an_OBUF[3]_inst 
       (.I(an_OBUF[3]),
        .O(an[3]));
  OBUF \an_OBUF[4]_inst 
       (.I(an_OBUF[4]),
        .O(an[4]));
  OBUF \an_OBUF[5]_inst 
       (.I(1'b1),
        .O(an[5]));
  OBUF \an_OBUF[6]_inst 
       (.I(an_OBUF[6]),
        .O(an[6]));
  OBUF \an_OBUF[7]_inst 
       (.I(an_OBUF[7]),
        .O(an[7]));
  BUFG clk_IBUF_BUFG_inst
       (.I(clk_IBUF),
        .O(clk_IBUF_BUFG));
  IBUF clk_IBUF_inst
       (.I(clk),
        .O(clk_IBUF));
  divider clk_div
       (.CLK(clk_F),
        .clk(clk_IBUF_BUFG),
        .temp_OBUF(temp_OBUF));
  OBUFT light_buzzer_OBUF_inst
       (.I(1'b0),
        .O(light_buzzer),
        .T(1'b1));
  OBUFT light_in_OBUF_inst
       (.I(1'b0),
        .O(light_in),
        .T(1'b1));
  OBUFT light_out_OBUF_inst
       (.I(1'b0),
        .O(light_out),
        .T(1'b1));
  OBUFT light_piao_OBUF_inst
       (.I(1'b0),
        .O(light_piao),
        .T(1'b1));
  OBUF light_power_OBUF_inst
       (.I(light_power_OBUF),
        .O(light_power));
  OBUF light_running_OBUF_inst
       (.I(light_running_OBUF),
        .O(light_running));
  OBUFT light_tuo_OBUF_inst
       (.I(1'b0),
        .O(light_tuo),
        .T(1'b1));
  OBUFT light_xi_OBUF_inst
       (.I(1'b0),
        .O(light_xi),
        .T(1'b1));
  BUFG mode_change_IBUF_BUFG_inst
       (.I(mode_change_IBUF),
        .O(mode_change_IBUF_BUFG));
  IBUF mode_change_IBUF_inst
       (.I(mode_change),
        .O(mode_change_IBUF));
  counter my_coun
       (.CLK(clk_F),
        .\FSM_onehot_state_reg[6] (my_machine_fsm_n_5),
        .\FSM_onehot_state_reg[7] (my_machine_fsm_n_7),
        .\FSM_onehot_state_reg[9] (\my_ssdisp/surplus_curr ),
        .Q(num),
        .an_OBUF({an_OBUF[7:6],an_OBUF[4:3],an_OBUF[1:0]}),
        .\seg[0] (my_coun_n_0),
        .\seg[0]_0 (my_coun_n_4),
        .\seg[0]_1 (my_coun_n_11),
        .\seg[0]_2 (my_coun_n_12),
        .\seg[0]_3 (my_coun_n_13),
        .\seg[0]_4 (my_coun_n_14),
        .\status_mode_reg[2] (my_machine_fsm_n_6));
  FSM my_machine_fsm
       (.CLK(temp_OBUF_BUFG),
        .\FSM_onehot_state_reg[2]_0 (my_machine_fsm_n_6),
        .Q(num),
        .an_OBUF({an_OBUF[6],an_OBUF[1]}),
        .in1(light_power_OBUF),
        .light_running_OBUF(light_running_OBUF),
        .mode_change_IBUF_BUFG(mode_change_IBUF_BUFG),
        .\num_reg[0] (my_coun_n_0),
        .\num_reg[0]_0 (my_coun_n_14),
        .\num_reg[0]_1 (my_coun_n_4),
        .\num_reg[0]_2 (my_coun_n_13),
        .\num_reg[1] (my_coun_n_12),
        .\num_reg[2] (my_coun_n_11),
        .pause_con_IBUF_BUFG(pause_con_IBUF_BUFG),
        .\seg[0] (\my_ssdisp/surplus_curr ),
        .seg_OBUF(seg_OBUF),
        .state_OBUF(state_OBUF),
        .\timer_set_reg[3] (my_machine_fsm_n_7),
        .\water_line_reg[0] (my_machine_fsm_n_5),
        .weight_change(weight_change_IBUF_BUFG));
  BUFG pause_con_IBUF_BUFG_inst
       (.I(pause_con_IBUF),
        .O(pause_con_IBUF_BUFG));
  IBUF pause_con_IBUF_inst
       (.I(pause_con),
        .O(pause_con_IBUF));
  IBUF rst_IBUF_inst
       (.I(rst),
        .O(light_power_OBUF));
  OBUF \seg_OBUF[0]_inst 
       (.I(seg_OBUF[0]),
        .O(seg[0]));
  OBUF \seg_OBUF[1]_inst 
       (.I(seg_OBUF[1]),
        .O(seg[1]));
  OBUF \seg_OBUF[2]_inst 
       (.I(seg_OBUF[2]),
        .O(seg[2]));
  OBUF \seg_OBUF[3]_inst 
       (.I(seg_OBUF[3]),
        .O(seg[3]));
  OBUF \seg_OBUF[4]_inst 
       (.I(seg_OBUF[4]),
        .O(seg[4]));
  OBUF \seg_OBUF[5]_inst 
       (.I(seg_OBUF[5]),
        .O(seg[5]));
  OBUF \seg_OBUF[6]_inst 
       (.I(seg_OBUF[6]),
        .O(seg[6]));
  OBUF \state_OBUF[0]_inst 
       (.I(state_OBUF[0]),
        .O(state[0]));
  OBUF \state_OBUF[1]_inst 
       (.I(state_OBUF[1]),
        .O(state[1]));
  OBUF \state_OBUF[2]_inst 
       (.I(state_OBUF[2]),
        .O(state[2]));
  OBUF \state_OBUF[3]_inst 
       (.I(state_OBUF[3]),
        .O(state[3]));
  BUFG temp_OBUF_BUFG_inst
       (.I(temp_OBUF),
        .O(temp_OBUF_BUFG));
  OBUF temp_OBUF_inst
       (.I(temp_OBUF_BUFG),
        .O(temp));
  BUFG weight_change_IBUF_BUFG_inst
       (.I(weight_change_IBUF),
        .O(weight_change_IBUF_BUFG));
  IBUF weight_change_IBUF_inst
       (.I(weight_change),
        .O(weight_change_IBUF));
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
