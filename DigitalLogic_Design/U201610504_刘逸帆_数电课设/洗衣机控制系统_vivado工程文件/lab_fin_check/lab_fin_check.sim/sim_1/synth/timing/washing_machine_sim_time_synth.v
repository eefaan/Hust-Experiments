// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.2 (win64) Build 1909853 Thu Jun 15 18:39:09 MDT 2017
// Date        : Tue Sep 25 15:33:48 2018
// Host        : DESKTOP-KM458MG running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               C:/VerilogLab/lab_fin_check/lab_fin_check.sim/sim_1/synth/timing/washing_machine_sim_time_synth.v
// Design      : FSM
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

(* FINISH = "4'b1001" *) (* PAUSE = "4'b1011" *) (* PIAO_1_OUT = "4'b0011" *) 
(* PIAO_2_DRY = "4'b0100" *) (* PIAO_3_IN = "4'b0101" *) (* PIAO_4_RI = "4'b0110" *) 
(* SHUT_DOWN = "4'b1010" *) (* START = "4'b0000" *) (* TUO_1_OUT = "4'b0111" *) 
(* TUO_2_DRY = "4'b1000" *) (* XI_1_IN = "4'b0001" *) (* XI_2_WASH = "4'b0010" *) 
(* NotValidForBitStream *)
module FSM
   (clk,
    clk_N,
    rst,
    pause_con,
    mode_change,
    weight_change,
    light_power,
    light_running,
    light_xi,
    light_piao,
    light_tuo,
    light_in,
    light_out,
    light_buzzer,
    status_mode,
    status_weight,
    display_out,
    state);
  input clk;
  input clk_N;
  input rst;
  input pause_con;
  input mode_change;
  input weight_change;
  output light_power;
  output light_running;
  output light_xi;
  output light_piao;
  output light_tuo;
  output light_in;
  output light_out;
  output light_buzzer;
  output [2:0]status_mode;
  output [1:0]status_weight;
  output [31:0]display_out;
  output [3:0]state;

  wire \FSM_onehot_state[0]_i_1_n_0 ;
  wire \FSM_onehot_state[0]_i_2_n_0 ;
  wire \FSM_onehot_state[0]_i_3_n_0 ;
  wire \FSM_onehot_state[10]_i_1_n_0 ;
  wire \FSM_onehot_state[10]_i_2_n_0 ;
  wire \FSM_onehot_state[2]_i_3_n_0 ;
  wire \FSM_onehot_state[5]_i_2_n_0 ;
  wire \FSM_onehot_state[6]_i_3_n_0 ;
  wire \FSM_onehot_state[9]_i_2_n_0 ;
  wire \FSM_onehot_state[9]_i_3_n_0 ;
  wire \FSM_onehot_state[9]_i_4_n_0 ;
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
  wire clk;
  wire clk_IBUF;
  wire clk_IBUF_BUFG;
  wire clk_N;
  wire clk_N_IBUF;
  wire clk_N_IBUF_BUFG;
  wire [31:0]display_out;
  wire [30:0]display_out_OBUF;
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
  wire my_ssdisp_n_10;
  wire my_ssdisp_n_11;
  wire my_ssdisp_n_12;
  wire my_ssdisp_n_13;
  wire my_ssdisp_n_4;
  wire my_ssdisp_n_5;
  wire my_ssdisp_n_6;
  wire my_ssdisp_n_7;
  wire my_ssdisp_n_8;
  wire my_ssdisp_n_9;
  wire my_timer_n_0;
  wire my_timer_n_1;
  wire my_timer_n_10;
  wire my_timer_n_11;
  wire my_timer_n_12;
  wire my_timer_n_13;
  wire my_timer_n_2;
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
  wire next_state13_out;
  wire next_state14_out;
  wire p_0_in;
  wire pause_con;
  wire pause_con_IBUF;
  wire pause_con_IBUF_BUFG;
  wire rst;
  wire [3:0]state;
  wire [3:0]state_OBUF;
  wire [2:0]status_mode;
  wire \status_mode[0]_i_1_n_0 ;
  wire \status_mode[1]_i_1_n_0 ;
  wire \status_mode[2]_i_1_n_0 ;
  wire [2:0]status_mode_OBUF;
  wire [1:0]status_weight;
  wire \status_weight[0]_i_1_n_0 ;
  wire \status_weight[1]_i_1_n_0 ;
  wire [1:0]status_weight_OBUF;
  wire surplus_curr13_out;
  wire surplus_curr1__0;
  wire weight_change;
  wire weight_change_IBUF;
  wire weight_change_IBUF_BUFG;

initial begin
 $sdf_annotate("washing_machine_sim_time_synth.sdf",,,,"tool_control");
end
  LUT6 #(
    .INIT(64'hF2AAFFFFAAAAAAAA)) 
    \FSM_onehot_state[0]_i_1 
       (.I0(\FSM_onehot_state[0]_i_2_n_0 ),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[2]),
        .I4(light_running_OBUF),
        .I5(\FSM_onehot_state_reg_n_0_[0] ),
        .O(\FSM_onehot_state[0]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \FSM_onehot_state[0]_i_2 
       (.I0(\FSM_onehot_state_reg_n_0_[2] ),
        .I1(\FSM_onehot_state[5]_i_2_n_0 ),
        .I2(\FSM_onehot_state_reg_n_0_[8] ),
        .I3(\FSM_onehot_state_reg_n_0_[4] ),
        .I4(\FSM_onehot_state_reg_n_0_[3] ),
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
       (.I0(\FSM_onehot_state_reg_n_0_[4] ),
        .I1(\FSM_onehot_state_reg_n_0_[3] ),
        .I2(\FSM_onehot_state_reg_n_0_[0] ),
        .I3(\FSM_onehot_state_reg_n_0_[1] ),
        .I4(\FSM_onehot_state_reg_n_0_[2] ),
        .O(\FSM_onehot_state[10]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'h15)) 
    \FSM_onehot_state[1]_i_2 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[1]),
        .I2(status_mode_OBUF[0]),
        .O(next_state13_out));
  LUT2 #(
    .INIT(4'hB)) 
    \FSM_onehot_state[2]_i_3 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .O(\FSM_onehot_state[2]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \FSM_onehot_state[3]_i_3 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[2]),
        .O(next_state14_out));
  LUT2 #(
    .INIT(4'hE)) 
    \FSM_onehot_state[5]_i_2 
       (.I0(\FSM_onehot_state_reg_n_0_[0] ),
        .I1(\FSM_onehot_state_reg_n_0_[1] ),
        .O(\FSM_onehot_state[5]_i_2_n_0 ));
  LUT3 #(
    .INIT(8'hFE)) 
    \FSM_onehot_state[6]_i_3 
       (.I0(\FSM_onehot_state_reg_n_0_[2] ),
        .I1(\FSM_onehot_state_reg_n_0_[1] ),
        .I2(\FSM_onehot_state_reg_n_0_[0] ),
        .O(\FSM_onehot_state[6]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0200020002FF0200)) 
    \FSM_onehot_state[9]_i_2 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[1]),
        .I2(status_mode_OBUF[2]),
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
    .INIT(32'hDFD0DFDF)) 
    \FSM_onehot_state[9]_i_4 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[2]),
        .I2(\FSM_onehot_state_reg_n_0_[6] ),
        .I3(\FSM_onehot_state_reg_n_0_[7] ),
        .I4(\FSM_onehot_state_reg_n_0_[8] ),
        .O(\FSM_onehot_state[9]_i_4_n_0 ));
  (* KEEP = "yes" *) 
  FDSE #(
    .INIT(1'b1)) 
    \FSM_onehot_state_reg[0] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(\FSM_onehot_state[0]_i_1_n_0 ),
        .Q(\FSM_onehot_state_reg_n_0_[0] ),
        .S(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[10] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(\FSM_onehot_state[10]_i_1_n_0 ),
        .Q(\FSM_onehot_state_reg_n_0_[10] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[1] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_8),
        .Q(\FSM_onehot_state_reg_n_0_[1] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[2] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_7),
        .Q(\FSM_onehot_state_reg_n_0_[2] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[3] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_6),
        .Q(\FSM_onehot_state_reg_n_0_[3] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[4] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_5),
        .Q(\FSM_onehot_state_reg_n_0_[4] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[5] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_4),
        .Q(\FSM_onehot_state_reg_n_0_[5] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[6] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_3),
        .Q(\FSM_onehot_state_reg_n_0_[6] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[7] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_2),
        .Q(\FSM_onehot_state_reg_n_0_[7] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[8] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_1),
        .Q(\FSM_onehot_state_reg_n_0_[8] ),
        .R(light_power_OBUF));
  (* KEEP = "yes" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_state_reg[9] 
       (.C(clk_N_IBUF_BUFG),
        .CE(1'b1),
        .D(my_timer_n_0),
        .Q(\FSM_onehot_state_reg_n_0_[9] ),
        .R(light_power_OBUF));
  BUFG clk_IBUF_BUFG_inst
       (.I(clk_IBUF),
        .O(clk_IBUF_BUFG));
  IBUF clk_IBUF_inst
       (.I(clk),
        .O(clk_IBUF));
  BUFG clk_N_IBUF_BUFG_inst
       (.I(clk_N_IBUF),
        .O(clk_N_IBUF_BUFG));
  IBUF clk_N_IBUF_inst
       (.I(clk_N),
        .O(clk_N_IBUF));
  OBUF \display_out_OBUF[0]_inst 
       (.I(display_out_OBUF[0]),
        .O(display_out[0]));
  OBUF \display_out_OBUF[10]_inst 
       (.I(1'b0),
        .O(display_out[10]));
  OBUF \display_out_OBUF[11]_inst 
       (.I(1'b0),
        .O(display_out[11]));
  OBUF \display_out_OBUF[12]_inst 
       (.I(display_out_OBUF[12]),
        .O(display_out[12]));
  OBUF \display_out_OBUF[13]_inst 
       (.I(display_out_OBUF[13]),
        .O(display_out[13]));
  OBUF \display_out_OBUF[14]_inst 
       (.I(display_out_OBUF[14]),
        .O(display_out[14]));
  OBUF \display_out_OBUF[15]_inst 
       (.I(display_out_OBUF[15]),
        .O(display_out[15]));
  OBUF \display_out_OBUF[16]_inst 
       (.I(display_out_OBUF[16]),
        .O(display_out[16]));
  OBUF \display_out_OBUF[17]_inst 
       (.I(display_out_OBUF[17]),
        .O(display_out[17]));
  OBUF \display_out_OBUF[18]_inst 
       (.I(1'b0),
        .O(display_out[18]));
  OBUF \display_out_OBUF[19]_inst 
       (.I(1'b0),
        .O(display_out[19]));
  OBUF \display_out_OBUF[1]_inst 
       (.I(display_out_OBUF[1]),
        .O(display_out[1]));
  OBUF \display_out_OBUF[20]_inst 
       (.I(1'b0),
        .O(display_out[20]));
  OBUF \display_out_OBUF[21]_inst 
       (.I(1'b0),
        .O(display_out[21]));
  OBUF \display_out_OBUF[22]_inst 
       (.I(1'b0),
        .O(display_out[22]));
  OBUF \display_out_OBUF[23]_inst 
       (.I(1'b0),
        .O(display_out[23]));
  OBUF \display_out_OBUF[24]_inst 
       (.I(display_out_OBUF[24]),
        .O(display_out[24]));
  OBUF \display_out_OBUF[25]_inst 
       (.I(display_out_OBUF[25]),
        .O(display_out[25]));
  OBUF \display_out_OBUF[26]_inst 
       (.I(display_out_OBUF[26]),
        .O(display_out[26]));
  OBUF \display_out_OBUF[27]_inst 
       (.I(display_out_OBUF[27]),
        .O(display_out[27]));
  OBUF \display_out_OBUF[28]_inst 
       (.I(display_out_OBUF[28]),
        .O(display_out[28]));
  OBUF \display_out_OBUF[29]_inst 
       (.I(display_out_OBUF[29]),
        .O(display_out[29]));
  OBUF \display_out_OBUF[2]_inst 
       (.I(display_out_OBUF[2]),
        .O(display_out[2]));
  OBUF \display_out_OBUF[30]_inst 
       (.I(display_out_OBUF[30]),
        .O(display_out[30]));
  OBUF \display_out_OBUF[31]_inst 
       (.I(1'b0),
        .O(display_out[31]));
  OBUF \display_out_OBUF[3]_inst 
       (.I(display_out_OBUF[3]),
        .O(display_out[3]));
  OBUF \display_out_OBUF[4]_inst 
       (.I(display_out_OBUF[4]),
        .O(display_out[4]));
  OBUF \display_out_OBUF[5]_inst 
       (.I(display_out_OBUF[5]),
        .O(display_out[5]));
  OBUF \display_out_OBUF[6]_inst 
       (.I(display_out_OBUF[6]),
        .O(display_out[6]));
  OBUF \display_out_OBUF[7]_inst 
       (.I(display_out_OBUF[7]),
        .O(display_out[7]));
  OBUF \display_out_OBUF[8]_inst 
       (.I(1'b0),
        .O(display_out[8]));
  OBUF \display_out_OBUF[9]_inst 
       (.I(1'b0),
        .O(display_out[9]));
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
  LUT1 #(
    .INIT(2'h1)) 
    light_running_i_1
       (.I0(light_running_OBUF),
        .O(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    light_running_reg
       (.C(pause_con_IBUF_BUFG),
        .CE(1'b1),
        .D(p_0_in),
        .Q(light_running_OBUF),
        .R(1'b0));
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
  ssdisp my_ssdisp
       (.D({my_timer_n_9,my_timer_n_10,my_timer_n_11,my_timer_n_12,my_timer_n_13}),
        .Q(status_weight_OBUF),
        .\display_out[12] (my_ssdisp_n_7),
        .\display_out[13] (my_ssdisp_n_5),
        .\display_out[17] (my_ssdisp_n_8),
        .\display_out[24] (my_ssdisp_n_11),
        .\display_out[24]_0 (my_ssdisp_n_12),
        .\display_out[25] (my_ssdisp_n_4),
        .\display_out[29] (my_ssdisp_n_6),
        .\display_out[30] (my_ssdisp_n_9),
        .\display_out[30]_0 (my_ssdisp_n_10),
        .\display_out[30]_1 (my_ssdisp_n_13),
        .display_out_OBUF({display_out_OBUF[30:24],display_out_OBUF[17:12]}),
        .out({\FSM_onehot_state_reg_n_0_[10] ,\FSM_onehot_state_reg_n_0_[9] ,\FSM_onehot_state_reg_n_0_[8] ,\FSM_onehot_state_reg_n_0_[7] ,\FSM_onehot_state_reg_n_0_[6] ,\FSM_onehot_state_reg_n_0_[5] ,\FSM_onehot_state_reg_n_0_[4] ,\FSM_onehot_state_reg_n_0_[3] ,\FSM_onehot_state_reg_n_0_[2] ,\FSM_onehot_state_reg_n_0_[1] }),
        .state_OBUF(state_OBUF),
        .status_mode_OBUF(status_mode_OBUF),
        .\status_mode_reg[2] ({my_timer_n_22,my_timer_n_23,my_timer_n_24,my_timer_n_25,my_timer_n_26,my_timer_n_27}),
        .surplus_curr13_out(surplus_curr13_out),
        .surplus_curr1__0(surplus_curr1__0));
  timer my_timer
       (.CLK(clk_N_IBUF_BUFG),
        .D({my_timer_n_0,my_timer_n_1,my_timer_n_2,my_timer_n_3,my_timer_n_4,my_timer_n_5,my_timer_n_6,my_timer_n_7,my_timer_n_8}),
        .\FSM_onehot_state_reg[0] (\FSM_onehot_state[5]_i_2_n_0 ),
        .\FSM_onehot_state_reg[2] (\FSM_onehot_state[6]_i_3_n_0 ),
        .\FSM_onehot_state_reg[3] (\FSM_onehot_state[9]_i_3_n_0 ),
        .\FSM_onehot_state_reg[4] (\FSM_onehot_state[10]_i_2_n_0 ),
        .Q(status_weight_OBUF),
        .clk_IBUF_BUFG(clk_IBUF_BUFG),
        .\display_out[17] ({my_timer_n_9,my_timer_n_10,my_timer_n_11,my_timer_n_12,my_timer_n_13}),
        .\display_out[30] ({my_timer_n_22,my_timer_n_23,my_timer_n_24,my_timer_n_25,my_timer_n_26,my_timer_n_27}),
        .display_out_OBUF(display_out_OBUF[7:0]),
        .light_running_OBUF(light_running_OBUF),
        .next_state13_out(next_state13_out),
        .next_state14_out(next_state14_out),
        .out({\FSM_onehot_state_reg_n_0_[10] ,\FSM_onehot_state_reg_n_0_[9] ,\FSM_onehot_state_reg_n_0_[8] ,\FSM_onehot_state_reg_n_0_[7] ,\FSM_onehot_state_reg_n_0_[6] ,\FSM_onehot_state_reg_n_0_[5] ,\FSM_onehot_state_reg_n_0_[4] ,\FSM_onehot_state_reg_n_0_[3] ,\FSM_onehot_state_reg_n_0_[2] ,\FSM_onehot_state_reg_n_0_[1] ,\FSM_onehot_state_reg_n_0_[0] }),
        .state_OBUF(state_OBUF),
        .status_mode_OBUF(status_mode_OBUF),
        .\status_mode_reg[0] (\FSM_onehot_state[9]_i_2_n_0 ),
        .\status_mode_reg[0]_0 (my_ssdisp_n_7),
        .\status_mode_reg[1] (\FSM_onehot_state[2]_i_3_n_0 ),
        .\status_mode_reg[1]_0 (my_ssdisp_n_6),
        .\status_mode_reg[1]_1 (my_ssdisp_n_4),
        .\status_mode_reg[2] (my_ssdisp_n_12),
        .\status_mode_reg[2]_0 (my_ssdisp_n_5),
        .\status_mode_reg[2]_1 (my_ssdisp_n_8),
        .\status_weight_reg[0] (my_ssdisp_n_11),
        .\status_weight_reg[0]_0 (my_ssdisp_n_13),
        .\status_weight_reg[1] (my_ssdisp_n_10),
        .\status_weight_reg[1]_0 (my_ssdisp_n_9),
        .surplus_curr13_out(surplus_curr13_out),
        .surplus_curr1__0(surplus_curr1__0));
  BUFG pause_con_IBUF_BUFG_inst
       (.I(pause_con_IBUF),
        .O(pause_con_IBUF_BUFG));
  IBUF pause_con_IBUF_inst
       (.I(pause_con),
        .O(pause_con_IBUF));
  IBUF rst_IBUF_inst
       (.I(rst),
        .O(light_power_OBUF));
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
  LUT2 #(
    .INIT(4'h6)) 
    \status_mode[0]_i_1 
       (.I0(\FSM_onehot_state_reg_n_0_[0] ),
        .I1(status_mode_OBUF[0]),
        .O(\status_mode[0]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h7078)) 
    \status_mode[1]_i_1 
       (.I0(\FSM_onehot_state_reg_n_0_[0] ),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[2]),
        .O(\status_mode[1]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h7780)) 
    \status_mode[2]_i_1 
       (.I0(\FSM_onehot_state_reg_n_0_[0] ),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[2]),
        .O(\status_mode[2]_i_1_n_0 ));
  OBUF \status_mode_OBUF[0]_inst 
       (.I(status_mode_OBUF[0]),
        .O(status_mode[0]));
  OBUF \status_mode_OBUF[1]_inst 
       (.I(status_mode_OBUF[1]),
        .O(status_mode[1]));
  OBUF \status_mode_OBUF[2]_inst 
       (.I(status_mode_OBUF[2]),
        .O(status_mode[2]));
  FDRE #(
    .INIT(1'b0)) 
    \status_mode_reg[0] 
       (.C(mode_change_IBUF_BUFG),
        .CE(1'b1),
        .D(\status_mode[0]_i_1_n_0 ),
        .Q(status_mode_OBUF[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \status_mode_reg[1] 
       (.C(mode_change_IBUF_BUFG),
        .CE(1'b1),
        .D(\status_mode[1]_i_1_n_0 ),
        .Q(status_mode_OBUF[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \status_mode_reg[2] 
       (.C(mode_change_IBUF_BUFG),
        .CE(1'b1),
        .D(\status_mode[2]_i_1_n_0 ),
        .Q(status_mode_OBUF[2]),
        .R(1'b0));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \status_weight[0]_i_1 
       (.I0(status_weight_OBUF[0]),
        .O(\status_weight[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \status_weight[1]_i_1 
       (.I0(status_weight_OBUF[0]),
        .I1(status_weight_OBUF[1]),
        .O(\status_weight[1]_i_1_n_0 ));
  OBUF \status_weight_OBUF[0]_inst 
       (.I(status_weight_OBUF[0]),
        .O(status_weight[0]));
  OBUF \status_weight_OBUF[1]_inst 
       (.I(status_weight_OBUF[1]),
        .O(status_weight[1]));
  FDRE #(
    .INIT(1'b0)) 
    \status_weight_reg[0] 
       (.C(weight_change_IBUF_BUFG),
        .CE(\FSM_onehot_state_reg_n_0_[0] ),
        .D(\status_weight[0]_i_1_n_0 ),
        .Q(status_weight_OBUF[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \status_weight_reg[1] 
       (.C(weight_change_IBUF_BUFG),
        .CE(\FSM_onehot_state_reg_n_0_[0] ),
        .D(\status_weight[1]_i_1_n_0 ),
        .Q(status_weight_OBUF[1]),
        .R(1'b0));
  BUFG weight_change_IBUF_BUFG_inst
       (.I(weight_change_IBUF),
        .O(weight_change_IBUF_BUFG));
  IBUF weight_change_IBUF_inst
       (.I(weight_change),
        .O(weight_change_IBUF));
endmodule

module bin_to_BCD
   (display_out_OBUF,
    Q);
  output [5:0]display_out_OBUF;
  input [4:0]Q;

  wire [4:0]Q;
  wire [5:0]display_out_OBUF;

  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'hE0)) 
    \Ones_inferred__1/i_ 
       (.I0(Q[2]),
        .I1(Q[3]),
        .I2(Q[4]),
        .O(display_out_OBUF[5]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'h83E0)) 
    \Ones_inferred__2/i_ 
       (.I0(Q[1]),
        .I1(Q[2]),
        .I2(Q[3]),
        .I3(Q[4]),
        .O(display_out_OBUF[4]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'hA5611A86)) 
    \display_out_OBUF[25]_inst_i_1 
       (.I0(Q[4]),
        .I1(Q[3]),
        .I2(Q[2]),
        .I3(Q[1]),
        .I4(Q[0]),
        .O(display_out_OBUF[0]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h18C6318C)) 
    \display_out_OBUF[26]_inst_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(Q[3]),
        .I4(Q[4]),
        .O(display_out_OBUF[1]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h21084210)) 
    \display_out_OBUF[27]_inst_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(Q[3]),
        .I4(Q[4]),
        .O(display_out_OBUF[2]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h3E0F83E0)) 
    \display_out_OBUF[28]_inst_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(Q[3]),
        .I4(Q[4]),
        .O(display_out_OBUF[3]));
endmodule

(* ORIG_REF_NAME = "bin_to_BCD" *) 
module bin_to_BCD_0
   (display_out_OBUF,
    Q);
  output [4:0]display_out_OBUF;
  input [3:0]Q;

  wire [3:0]Q;
  wire [4:0]display_out_OBUF;

  LUT3 #(
    .INIT(8'hE0)) 
    \Ones_inferred__2/i_ 
       (.I0(Q[1]),
        .I1(Q[2]),
        .I2(Q[3]),
        .O(display_out_OBUF[4]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'h3942)) 
    \display_out_OBUF[13]_inst_i_1 
       (.I0(Q[3]),
        .I1(Q[2]),
        .I2(Q[1]),
        .I3(Q[0]),
        .O(display_out_OBUF[0]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'h318C)) 
    \display_out_OBUF[14]_inst_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(Q[3]),
        .O(display_out_OBUF[1]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'h4210)) 
    \display_out_OBUF[15]_inst_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(Q[3]),
        .O(display_out_OBUF[2]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'h83E0)) 
    \display_out_OBUF[16]_inst_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(Q[3]),
        .O(display_out_OBUF[3]));
endmodule

module ssdisp
   (state_OBUF,
    \display_out[25] ,
    \display_out[13] ,
    \display_out[29] ,
    \display_out[12] ,
    \display_out[17] ,
    \display_out[30] ,
    \display_out[30]_0 ,
    \display_out[24] ,
    \display_out[24]_0 ,
    \display_out[30]_1 ,
    surplus_curr1__0,
    surplus_curr13_out,
    display_out_OBUF,
    out,
    status_mode_OBUF,
    Q,
    D,
    \status_mode_reg[2] );
  output [3:0]state_OBUF;
  output \display_out[25] ;
  output \display_out[13] ;
  output \display_out[29] ;
  output \display_out[12] ;
  output \display_out[17] ;
  output \display_out[30] ;
  output \display_out[30]_0 ;
  output \display_out[24] ;
  output \display_out[24]_0 ;
  output \display_out[30]_1 ;
  output surplus_curr1__0;
  output surplus_curr13_out;
  output [12:0]display_out_OBUF;
  input [9:0]out;
  input [2:0]status_mode_OBUF;
  input [1:0]Q;
  input [4:0]D;
  input [5:0]\status_mode_reg[2] ;

  wire [4:0]D;
  wire [1:0]Q;
  wire \display_out[12] ;
  wire \display_out[13] ;
  wire \display_out[17] ;
  wire \display_out[24] ;
  wire \display_out[24]_0 ;
  wire \display_out[25] ;
  wire \display_out[29] ;
  wire \display_out[30] ;
  wire \display_out[30]_0 ;
  wire \display_out[30]_1 ;
  wire [12:0]display_out_OBUF;
  wire [9:0]out;
  wire [3:0]state_OBUF;
  wire [2:0]status_mode_OBUF;
  wire [5:0]\status_mode_reg[2] ;
  wire [5:1]surplus_all;
  wire [4:1]surplus_curr;
  wire surplus_curr13_out;
  wire surplus_curr1__0;
  wire \surplus_curr_reg[4]_i_2_n_0 ;

  bin_to_BCD my_surplus_all
       (.Q(surplus_all),
        .display_out_OBUF(display_out_OBUF[12:7]));
  bin_to_BCD_0 my_surplus_curr
       (.Q(surplus_curr),
        .display_out_OBUF(display_out_OBUF[5:1]));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \state_OBUF[0]_inst_i_1 
       (.I0(out[6]),
        .I1(out[8]),
        .I2(out[2]),
        .I3(out[0]),
        .I4(out[4]),
        .O(state_OBUF[0]));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \state_OBUF[1]_inst_i_1 
       (.I0(out[2]),
        .I1(out[1]),
        .I2(out[9]),
        .I3(out[6]),
        .I4(out[5]),
        .O(state_OBUF[1]));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \state_OBUF[2]_inst_i_1 
       (.I0(out[4]),
        .I1(out[3]),
        .I2(out[5]),
        .I3(out[6]),
        .O(state_OBUF[2]));
  LUT3 #(
    .INIT(8'hFE)) 
    \state_OBUF[3]_inst_i_1 
       (.I0(out[7]),
        .I1(out[9]),
        .I2(out[8]),
        .O(state_OBUF[3]));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[0] 
       (.CLR(1'b0),
        .D(\status_mode_reg[2] [0]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(display_out_OBUF[6]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT4 #(
    .INIT(16'h231B)) 
    \surplus_all_reg[0]_i_5 
       (.I0(Q[0]),
        .I1(status_mode_OBUF[2]),
        .I2(status_mode_OBUF[0]),
        .I3(status_mode_OBUF[1]),
        .O(\display_out[24] ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[1] 
       (.CLR(1'b0),
        .D(\status_mode_reg[2] [1]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[1]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h56514A4D)) 
    \surplus_all_reg[1]_i_9 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(Q[0]),
        .I4(Q[1]),
        .O(\display_out[25] ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[2] 
       (.CLR(1'b0),
        .D(\status_mode_reg[2] [2]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[2]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'h57565C59)) 
    \surplus_all_reg[2]_i_12 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(Q[0]),
        .I4(Q[1]),
        .O(\display_out[29] ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[3] 
       (.CLR(1'b0),
        .D(\status_mode_reg[2] [3]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[3]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT5 #(
    .INIT(32'h00005FF1)) 
    \surplus_all_reg[3]_i_12 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[2]),
        .O(\display_out[30] ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[4] 
       (.CLR(1'b0),
        .D(\status_mode_reg[2] [4]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[4]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT5 #(
    .INIT(32'h000FA0F1)) 
    \surplus_all_reg[4]_i_12 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[2]),
        .O(\display_out[30]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \surplus_all_reg[4]_i_9 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[2]),
        .O(surplus_curr1__0));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_all_reg[5] 
       (.CLR(1'b0),
        .D(\status_mode_reg[2] [5]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_all[5]));
  LUT2 #(
    .INIT(4'h1)) 
    \surplus_all_reg[5]_i_10 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[1]),
        .O(surplus_curr13_out));
  LUT2 #(
    .INIT(4'h1)) 
    \surplus_all_reg[5]_i_6 
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(\display_out[30]_1 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[0] 
       (.CLR(1'b0),
        .D(D[0]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(display_out_OBUF[0]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT4 #(
    .INIT(16'h2413)) 
    \surplus_curr_reg[0]_i_12 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[2]),
        .I2(status_mode_OBUF[1]),
        .I3(Q[0]),
        .O(\display_out[12] ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \surplus_curr_reg[0]_i_5 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .O(\display_out[24]_0 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[1] 
       (.CLR(1'b0),
        .D(D[1]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_curr[1]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'h1D4A085F)) 
    \surplus_curr_reg[1]_i_11 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(Q[1]),
        .I4(Q[0]),
        .O(\display_out[13] ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[2] 
       (.CLR(1'b0),
        .D(D[2]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_curr[2]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h1D1D5F4A)) 
    \surplus_curr_reg[2]_i_12 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(Q[0]),
        .I4(Q[1]),
        .O(\display_out[17] ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[3] 
       (.CLR(1'b0),
        .D(D[3]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_curr[3]));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \surplus_curr_reg[4] 
       (.CLR(1'b0),
        .D(D[4]),
        .G(\surplus_curr_reg[4]_i_2_n_0 ),
        .GE(1'b1),
        .Q(surplus_curr[4]));
  LUT6 #(
    .INIT(64'h01010101010101FF)) 
    \surplus_curr_reg[4]_i_2 
       (.I0(out[8]),
        .I1(out[9]),
        .I2(out[7]),
        .I3(state_OBUF[2]),
        .I4(state_OBUF[0]),
        .I5(state_OBUF[1]),
        .O(\surplus_curr_reg[4]_i_2_n_0 ));
endmodule

module timer
   (D,
    \display_out[17] ,
    display_out_OBUF,
    \display_out[30] ,
    CLK,
    light_running_OBUF,
    out,
    status_mode_OBUF,
    \FSM_onehot_state_reg[3] ,
    \FSM_onehot_state_reg[2] ,
    \status_mode_reg[0] ,
    \FSM_onehot_state_reg[0] ,
    next_state14_out,
    \FSM_onehot_state_reg[4] ,
    \status_mode_reg[1] ,
    next_state13_out,
    state_OBUF,
    Q,
    \status_mode_reg[0]_0 ,
    \status_mode_reg[2] ,
    \status_weight_reg[0] ,
    \status_mode_reg[2]_0 ,
    \status_mode_reg[2]_1 ,
    surplus_curr13_out,
    surplus_curr1__0,
    \status_weight_reg[0]_0 ,
    \status_weight_reg[1] ,
    \status_weight_reg[1]_0 ,
    \status_mode_reg[1]_0 ,
    \status_mode_reg[1]_1 ,
    clk_IBUF_BUFG);
  output [8:0]D;
  output [4:0]\display_out[17] ;
  output [7:0]display_out_OBUF;
  output [5:0]\display_out[30] ;
  input CLK;
  input light_running_OBUF;
  input [10:0]out;
  input [2:0]status_mode_OBUF;
  input \FSM_onehot_state_reg[3] ;
  input \FSM_onehot_state_reg[2] ;
  input \status_mode_reg[0] ;
  input \FSM_onehot_state_reg[0] ;
  input next_state14_out;
  input \FSM_onehot_state_reg[4] ;
  input \status_mode_reg[1] ;
  input next_state13_out;
  input [3:0]state_OBUF;
  input [1:0]Q;
  input \status_mode_reg[0]_0 ;
  input \status_mode_reg[2] ;
  input \status_weight_reg[0] ;
  input \status_mode_reg[2]_0 ;
  input \status_mode_reg[2]_1 ;
  input surplus_curr13_out;
  input surplus_curr1__0;
  input \status_weight_reg[0]_0 ;
  input \status_weight_reg[1] ;
  input \status_weight_reg[1]_0 ;
  input \status_mode_reg[1]_0 ;
  input \status_mode_reg[1]_1 ;
  input clk_IBUF_BUFG;

  wire CLK;
  wire [8:0]D;
  wire \FSM_onehot_state[2]_i_2_n_0 ;
  wire \FSM_onehot_state[3]_i_2_n_0 ;
  wire \FSM_onehot_state[6]_i_2_n_0 ;
  wire \FSM_onehot_state[7]_i_2_n_0 ;
  wire \FSM_onehot_state[7]_i_3_n_0 ;
  wire \FSM_onehot_state[8]_i_2_n_0 ;
  wire \FSM_onehot_state_reg[0] ;
  wire \FSM_onehot_state_reg[2] ;
  wire \FSM_onehot_state_reg[3] ;
  wire \FSM_onehot_state_reg[4] ;
  wire [1:0]Q;
  wire clk_IBUF_BUFG;
  wire [4:0]\display_out[17] ;
  wire [5:0]\display_out[30] ;
  wire [7:0]display_out_OBUF;
  wire \display_out_OBUF[4]_inst_i_2_n_0 ;
  wire \display_out_OBUF[4]_inst_i_3_n_0 ;
  wire \display_out_OBUF[4]_inst_i_4_n_0 ;
  wire \display_out_OBUF[6]_inst_i_2_n_0 ;
  wire \display_out_OBUF[6]_inst_i_3_n_0 ;
  wire \display_out_OBUF[6]_inst_i_4_n_0 ;
  wire \display_out_OBUF[7]_inst_i_3_n_0 ;
  wire light_running_OBUF;
  wire [3:3]\my_ssdisp/OUT_T_w ;
  wire next_state13_out;
  wire next_state14_out;
  wire [10:0]out;
  wire [7:0]p_0_in__0;
  wire [3:2]sign__3;
  wire [3:0]state_1;
  wire [3:0]state_OBUF;
  wire [2:0]status_mode_OBUF;
  wire \status_mode_reg[0] ;
  wire \status_mode_reg[0]_0 ;
  wire \status_mode_reg[1] ;
  wire \status_mode_reg[1]_0 ;
  wire \status_mode_reg[1]_1 ;
  wire \status_mode_reg[2] ;
  wire \status_mode_reg[2]_0 ;
  wire \status_mode_reg[2]_1 ;
  wire \status_weight_reg[0] ;
  wire \status_weight_reg[0]_0 ;
  wire \status_weight_reg[1] ;
  wire \status_weight_reg[1]_0 ;
  wire \surplus_all_reg[0]_i_2_n_0 ;
  wire \surplus_all_reg[0]_i_3_n_0 ;
  wire \surplus_all_reg[0]_i_4_n_0 ;
  wire \surplus_all_reg[1]_i_10_n_0 ;
  wire \surplus_all_reg[1]_i_11_n_0 ;
  wire \surplus_all_reg[1]_i_2_n_0 ;
  wire \surplus_all_reg[1]_i_3_n_0 ;
  wire \surplus_all_reg[1]_i_4_n_0 ;
  wire \surplus_all_reg[1]_i_5_n_0 ;
  wire \surplus_all_reg[1]_i_6_n_0 ;
  wire \surplus_all_reg[1]_i_7_n_0 ;
  wire \surplus_all_reg[1]_i_8_n_0 ;
  wire \surplus_all_reg[2]_i_10_n_0 ;
  wire \surplus_all_reg[2]_i_11_n_0 ;
  wire \surplus_all_reg[2]_i_13_n_0 ;
  wire \surplus_all_reg[2]_i_14_n_0 ;
  wire \surplus_all_reg[2]_i_2_n_0 ;
  wire \surplus_all_reg[2]_i_3_n_0 ;
  wire \surplus_all_reg[2]_i_4_n_0 ;
  wire \surplus_all_reg[2]_i_5_n_0 ;
  wire \surplus_all_reg[2]_i_6_n_0 ;
  wire \surplus_all_reg[2]_i_7_n_0 ;
  wire \surplus_all_reg[2]_i_8_n_0 ;
  wire \surplus_all_reg[2]_i_9_n_0 ;
  wire \surplus_all_reg[3]_i_10_n_0 ;
  wire \surplus_all_reg[3]_i_11_n_0 ;
  wire \surplus_all_reg[3]_i_13_n_0 ;
  wire \surplus_all_reg[3]_i_14_n_0 ;
  wire \surplus_all_reg[3]_i_2_n_0 ;
  wire \surplus_all_reg[3]_i_3_n_0 ;
  wire \surplus_all_reg[3]_i_4_n_0 ;
  wire \surplus_all_reg[3]_i_5_n_0 ;
  wire \surplus_all_reg[3]_i_6_n_0 ;
  wire \surplus_all_reg[3]_i_7_n_0 ;
  wire \surplus_all_reg[3]_i_8_n_0 ;
  wire \surplus_all_reg[3]_i_9_n_0 ;
  wire \surplus_all_reg[4]_i_10_n_0 ;
  wire \surplus_all_reg[4]_i_11_n_0 ;
  wire \surplus_all_reg[4]_i_13_n_0 ;
  wire \surplus_all_reg[4]_i_14_n_0 ;
  wire \surplus_all_reg[4]_i_2_n_0 ;
  wire \surplus_all_reg[4]_i_3_n_0 ;
  wire \surplus_all_reg[4]_i_4_n_0 ;
  wire \surplus_all_reg[4]_i_5_n_0 ;
  wire \surplus_all_reg[4]_i_6_n_0 ;
  wire \surplus_all_reg[4]_i_7_n_0 ;
  wire \surplus_all_reg[4]_i_8_n_0 ;
  wire \surplus_all_reg[5]_i_2_n_0 ;
  wire \surplus_all_reg[5]_i_3_n_0 ;
  wire \surplus_all_reg[5]_i_4_n_0 ;
  wire \surplus_all_reg[5]_i_5_n_0 ;
  wire \surplus_all_reg[5]_i_7_n_0 ;
  wire \surplus_all_reg[5]_i_8_n_0 ;
  wire \surplus_all_reg[5]_i_9_n_0 ;
  wire surplus_curr13_out;
  wire surplus_curr1__0;
  wire \surplus_curr_reg[0]_i_10_n_0 ;
  wire \surplus_curr_reg[0]_i_11_n_0 ;
  wire \surplus_curr_reg[0]_i_2_n_0 ;
  wire \surplus_curr_reg[0]_i_3_n_0 ;
  wire \surplus_curr_reg[0]_i_4_n_0 ;
  wire \surplus_curr_reg[0]_i_6_n_0 ;
  wire \surplus_curr_reg[0]_i_7_n_0 ;
  wire \surplus_curr_reg[0]_i_8_n_0 ;
  wire \surplus_curr_reg[0]_i_9_n_0 ;
  wire \surplus_curr_reg[1]_i_10_n_0 ;
  wire \surplus_curr_reg[1]_i_12_n_0 ;
  wire \surplus_curr_reg[1]_i_2_n_0 ;
  wire \surplus_curr_reg[1]_i_3_n_0 ;
  wire \surplus_curr_reg[1]_i_4_n_0 ;
  wire \surplus_curr_reg[1]_i_5_n_0 ;
  wire \surplus_curr_reg[1]_i_6_n_0 ;
  wire \surplus_curr_reg[1]_i_7_n_0 ;
  wire \surplus_curr_reg[1]_i_8_n_0 ;
  wire \surplus_curr_reg[1]_i_9_n_0 ;
  wire \surplus_curr_reg[2]_i_10_n_0 ;
  wire \surplus_curr_reg[2]_i_11_n_0 ;
  wire \surplus_curr_reg[2]_i_13_n_0 ;
  wire \surplus_curr_reg[2]_i_2_n_0 ;
  wire \surplus_curr_reg[2]_i_3_n_0 ;
  wire \surplus_curr_reg[2]_i_4_n_0 ;
  wire \surplus_curr_reg[2]_i_5_n_0 ;
  wire \surplus_curr_reg[2]_i_6_n_0 ;
  wire \surplus_curr_reg[2]_i_7_n_0 ;
  wire \surplus_curr_reg[2]_i_8_n_0 ;
  wire \surplus_curr_reg[2]_i_9_n_0 ;
  wire \surplus_curr_reg[3]_i_10_n_0 ;
  wire \surplus_curr_reg[3]_i_11_n_0 ;
  wire \surplus_curr_reg[3]_i_12_n_0 ;
  wire \surplus_curr_reg[3]_i_13_n_0 ;
  wire \surplus_curr_reg[3]_i_2_n_0 ;
  wire \surplus_curr_reg[3]_i_3_n_0 ;
  wire \surplus_curr_reg[3]_i_4_n_0 ;
  wire \surplus_curr_reg[3]_i_5_n_0 ;
  wire \surplus_curr_reg[3]_i_6_n_0 ;
  wire \surplus_curr_reg[3]_i_7_n_0 ;
  wire \surplus_curr_reg[3]_i_8_n_0 ;
  wire \surplus_curr_reg[3]_i_9_n_0 ;
  wire \surplus_curr_reg[4]_i_10_n_0 ;
  wire \surplus_curr_reg[4]_i_11_n_0 ;
  wire \surplus_curr_reg[4]_i_12_n_0 ;
  wire \surplus_curr_reg[4]_i_3_n_0 ;
  wire \surplus_curr_reg[4]_i_4_n_0 ;
  wire \surplus_curr_reg[4]_i_5_n_0 ;
  wire \surplus_curr_reg[4]_i_6_n_0 ;
  wire \surplus_curr_reg[4]_i_7_n_0 ;
  wire \surplus_curr_reg[4]_i_8_n_0 ;
  wire \surplus_curr_reg[4]_i_9_n_0 ;
  wire [3:0]timer_ini;
  wire \timer_ini_reg[0]_i_1_n_0 ;
  wire \timer_ini_reg[1]_i_1_n_0 ;
  wire \timer_ini_reg[2]_i_1_n_0 ;
  wire \timer_ini_reg[3]_i_1_n_0 ;
  wire timer_out;
  wire timer_out_i_1_n_0;
  wire [3:0]timer_set;
  wire \timer_set[0]_i_1_n_0 ;
  wire \timer_set[1]_i_1_n_0 ;
  wire \timer_set[2]_i_1_n_0 ;
  wire \timer_set[3]_i_1_n_0 ;
  wire \timer_set[3]_i_2_n_0 ;
  wire [7:1]water_line;
  wire water_line0_carry__0_i_1_n_0;
  wire water_line0_carry__0_i_2_n_0;
  wire water_line0_carry__0_i_3_n_0;
  wire water_line0_carry__0_n_2;
  wire water_line0_carry__0_n_3;
  wire water_line0_carry_i_1_n_0;
  wire water_line0_carry_i_2_n_0;
  wire water_line0_carry_i_3_n_0;
  wire water_line0_carry_i_4_n_0;
  wire water_line0_carry_i_5_n_0;
  wire water_line0_carry_n_0;
  wire water_line0_carry_n_1;
  wire water_line0_carry_n_2;
  wire water_line0_carry_n_3;
  wire \water_line[7]_i_1_n_0 ;
  wire \water_line[7]_i_2_n_0 ;
  wire [0:0]water_line_reg__0;
  wire [3:2]NLW_water_line0_carry__0_CO_UNCONNECTED;
  wire [3:3]NLW_water_line0_carry__0_O_UNCONNECTED;

  LUT5 #(
    .INIT(32'h8830B830)) 
    \FSM_onehot_state[1]_i_1 
       (.I0(next_state13_out),
        .I1(out[0]),
        .I2(out[1]),
        .I3(light_running_OBUF),
        .I4(timer_out),
        .O(D[0]));
  LUT6 #(
    .INIT(64'h00000000FFA800AA)) 
    \FSM_onehot_state[2]_i_1 
       (.I0(\FSM_onehot_state[2]_i_2_n_0 ),
        .I1(status_mode_OBUF[2]),
        .I2(\status_mode_reg[1] ),
        .I3(out[1]),
        .I4(\FSM_onehot_state[8]_i_2_n_0 ),
        .I5(out[0]),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT5 #(
    .INIT(32'hA8AAAAAA)) 
    \FSM_onehot_state[2]_i_2 
       (.I0(out[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(timer_out),
        .I4(light_running_OBUF),
        .O(\FSM_onehot_state[2]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hABEAAAAAAAAAAAAA)) 
    \FSM_onehot_state[3]_i_1 
       (.I0(\FSM_onehot_state[3]_i_2_n_0 ),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[2]),
        .I4(out[0]),
        .I5(light_running_OBUF),
        .O(D[2]));
  LUT6 #(
    .INIT(64'h000000000000C022)) 
    \FSM_onehot_state[3]_i_2 
       (.I0(out[3]),
        .I1(out[2]),
        .I2(next_state14_out),
        .I3(\FSM_onehot_state[8]_i_2_n_0 ),
        .I4(out[0]),
        .I5(out[1]),
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
        .O(D[3]));
  LUT6 #(
    .INIT(64'h00000000000000A4)) 
    \FSM_onehot_state[5]_i_1 
       (.I0(out[4]),
        .I1(out[5]),
        .I2(\FSM_onehot_state[8]_i_2_n_0 ),
        .I3(out[2]),
        .I4(out[3]),
        .I5(\FSM_onehot_state_reg[0] ),
        .O(D[4]));
  LUT6 #(
    .INIT(64'h00000000000000E2)) 
    \FSM_onehot_state[6]_i_1 
       (.I0(\FSM_onehot_state[6]_i_2_n_0 ),
        .I1(out[5]),
        .I2(\FSM_onehot_state[8]_i_2_n_0 ),
        .I3(out[4]),
        .I4(out[3]),
        .I5(\FSM_onehot_state_reg[2] ),
        .O(D[5]));
  LUT6 #(
    .INIT(64'h8A80AAAAAAAAAAAA)) 
    \FSM_onehot_state[6]_i_2 
       (.I0(out[6]),
        .I1(status_mode_OBUF[2]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[0]),
        .I4(timer_out),
        .I5(light_running_OBUF),
        .O(\FSM_onehot_state[6]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFF00800000)) 
    \FSM_onehot_state[7]_i_1 
       (.I0(light_running_OBUF),
        .I1(out[0]),
        .I2(status_mode_OBUF[0]),
        .I3(status_mode_OBUF[1]),
        .I4(status_mode_OBUF[2]),
        .I5(\FSM_onehot_state[7]_i_2_n_0 ),
        .O(D[6]));
  LUT6 #(
    .INIT(64'h000000000000CE00)) 
    \FSM_onehot_state[7]_i_2 
       (.I0(out[7]),
        .I1(out[6]),
        .I2(\FSM_onehot_state[8]_i_2_n_0 ),
        .I3(\FSM_onehot_state_reg[3] ),
        .I4(\FSM_onehot_state[7]_i_3_n_0 ),
        .I5(\FSM_onehot_state_reg[2] ),
        .O(\FSM_onehot_state[7]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hA8AAAAAA)) 
    \FSM_onehot_state[7]_i_3 
       (.I0(out[6]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(timer_out),
        .I4(light_running_OBUF),
        .O(\FSM_onehot_state[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0100000101000000)) 
    \FSM_onehot_state[8]_i_1 
       (.I0(\FSM_onehot_state_reg[4] ),
        .I1(out[5]),
        .I2(out[6]),
        .I3(out[7]),
        .I4(\FSM_onehot_state[8]_i_2_n_0 ),
        .I5(out[8]),
        .O(D[7]));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \FSM_onehot_state[8]_i_2 
       (.I0(timer_out),
        .I1(light_running_OBUF),
        .O(\FSM_onehot_state[8]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h00000080)) 
    \FSM_onehot_state[9]_i_1 
       (.I0(\status_mode_reg[0] ),
        .I1(timer_out),
        .I2(light_running_OBUF),
        .I3(out[0]),
        .I4(out[1]),
        .O(D[8]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \display_out_OBUF[0]_inst_i_1 
       (.I0(water_line_reg__0),
        .I1(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .I2(status_mode_OBUF[0]),
        .O(display_out_OBUF[0]));
  LUT6 #(
    .INIT(64'h554AFFFF554A0000)) 
    \display_out_OBUF[1]_inst_i_1 
       (.I0(water_line[1]),
        .I1(\display_out_OBUF[4]_inst_i_4_n_0 ),
        .I2(\display_out_OBUF[4]_inst_i_3_n_0 ),
        .I3(\display_out_OBUF[4]_inst_i_2_n_0 ),
        .I4(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .I5(status_mode_OBUF[1]),
        .O(display_out_OBUF[1]));
  LUT6 #(
    .INIT(64'h998CFFFF998C0000)) 
    \display_out_OBUF[2]_inst_i_1 
       (.I0(water_line[1]),
        .I1(\display_out_OBUF[4]_inst_i_4_n_0 ),
        .I2(\display_out_OBUF[4]_inst_i_3_n_0 ),
        .I3(\display_out_OBUF[4]_inst_i_2_n_0 ),
        .I4(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .I5(status_mode_OBUF[2]),
        .O(display_out_OBUF[2]));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT5 #(
    .INIT(32'h222C0000)) 
    \display_out_OBUF[3]_inst_i_1 
       (.I0(\display_out_OBUF[4]_inst_i_2_n_0 ),
        .I1(\display_out_OBUF[4]_inst_i_3_n_0 ),
        .I2(\display_out_OBUF[4]_inst_i_4_n_0 ),
        .I3(water_line[1]),
        .I4(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .O(display_out_OBUF[3]));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT5 #(
    .INIT(32'h666A0000)) 
    \display_out_OBUF[4]_inst_i_1 
       (.I0(\display_out_OBUF[4]_inst_i_2_n_0 ),
        .I1(\display_out_OBUF[4]_inst_i_3_n_0 ),
        .I2(\display_out_OBUF[4]_inst_i_4_n_0 ),
        .I3(water_line[1]),
        .I4(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .O(display_out_OBUF[4]));
  LUT6 #(
    .INIT(64'h0821420810428410)) 
    \display_out_OBUF[4]_inst_i_2 
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .I2(water_line[4]),
        .I3(water_line[7]),
        .I4(water_line[5]),
        .I5(water_line[6]),
        .O(\display_out_OBUF[4]_inst_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hC61831C68C31638C)) 
    \display_out_OBUF[4]_inst_i_3 
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .I2(water_line[4]),
        .I3(water_line[7]),
        .I4(water_line[5]),
        .I5(water_line[6]),
        .O(\display_out_OBUF[4]_inst_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h8A65A651518A18A6)) 
    \display_out_OBUF[4]_inst_i_4 
       (.I0(water_line[6]),
        .I1(water_line[5]),
        .I2(water_line[7]),
        .I3(water_line[4]),
        .I4(water_line[3]),
        .I5(water_line[2]),
        .O(\display_out_OBUF[4]_inst_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'h60)) 
    \display_out_OBUF[5]_inst_i_1 
       (.I0(\display_out_OBUF[6]_inst_i_4_n_0 ),
        .I1(\display_out_OBUF[6]_inst_i_3_n_0 ),
        .I2(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .O(display_out_OBUF[5]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT4 #(
    .INIT(16'hA600)) 
    \display_out_OBUF[6]_inst_i_1 
       (.I0(\display_out_OBUF[6]_inst_i_2_n_0 ),
        .I1(\display_out_OBUF[6]_inst_i_3_n_0 ),
        .I2(\display_out_OBUF[6]_inst_i_4_n_0 ),
        .I3(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .O(display_out_OBUF[6]));
  LUT5 #(
    .INIT(32'h9C169412)) 
    \display_out_OBUF[6]_inst_i_2 
       (.I0(water_line[6]),
        .I1(water_line[5]),
        .I2(water_line[7]),
        .I3(water_line[4]),
        .I4(water_line[3]),
        .O(\display_out_OBUF[6]_inst_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00FE0300FF00FF00)) 
    \display_out_OBUF[6]_inst_i_3 
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .I2(water_line[4]),
        .I3(water_line[7]),
        .I4(water_line[5]),
        .I5(water_line[6]),
        .O(\display_out_OBUF[6]_inst_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0F3E830FE083F8E0)) 
    \display_out_OBUF[6]_inst_i_4 
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .I2(water_line[4]),
        .I3(water_line[7]),
        .I4(water_line[5]),
        .I5(water_line[6]),
        .O(\display_out_OBUF[6]_inst_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \display_out_OBUF[7]_inst_i_1 
       (.I0(\my_ssdisp/OUT_T_w ),
        .I1(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .O(display_out_OBUF[7]));
  LUT6 #(
    .INIT(64'h000103F0E0000000)) 
    \display_out_OBUF[7]_inst_i_2 
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .I2(water_line[4]),
        .I3(water_line[7]),
        .I4(water_line[5]),
        .I5(water_line[6]),
        .O(\my_ssdisp/OUT_T_w ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \display_out_OBUF[7]_inst_i_3 
       (.I0(out[8]),
        .I1(out[10]),
        .I2(out[9]),
        .I3(state_OBUF[2]),
        .I4(state_OBUF[0]),
        .I5(state_OBUF[1]),
        .O(\display_out_OBUF[7]_inst_i_3_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \state_1_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(state_OBUF[0]),
        .Q(state_1[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_1_reg[1] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(state_OBUF[1]),
        .Q(state_1[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_1_reg[2] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(state_OBUF[2]),
        .Q(state_1[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \state_1_reg[3] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(state_OBUF[3]),
        .Q(state_1[3]),
        .R(1'b0));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \surplus_all_reg[0]_i_1 
       (.I0(\surplus_curr_reg[0]_i_2_n_0 ),
        .I1(state_OBUF[3]),
        .I2(\surplus_curr_reg[0]_i_3_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_all_reg[0]_i_2_n_0 ),
        .O(\display_out[30] [0]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \surplus_all_reg[0]_i_2 
       (.I0(\surplus_curr_reg[0]_i_9_n_0 ),
        .I1(\surplus_all_reg[0]_i_3_n_0 ),
        .I2(state_OBUF[1]),
        .I3(\surplus_all_reg[0]_i_4_n_0 ),
        .I4(state_OBUF[0]),
        .I5(\status_weight_reg[0] ),
        .O(\surplus_all_reg[0]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT4 #(
    .INIT(16'h0700)) 
    \surplus_all_reg[0]_i_3 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(timer_set[0]),
        .O(\surplus_all_reg[0]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT4 #(
    .INIT(16'h0015)) 
    \surplus_all_reg[0]_i_4 
       (.I0(timer_set[0]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[2]),
        .O(\surplus_all_reg[0]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \surplus_all_reg[1]_i_1 
       (.I0(\surplus_curr_reg[1]_i_2_n_0 ),
        .I1(state_OBUF[3]),
        .I2(\surplus_all_reg[1]_i_2_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_all_reg[1]_i_3_n_0 ),
        .O(\display_out[30] [1]));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT4 #(
    .INIT(16'hA596)) 
    \surplus_all_reg[1]_i_10 
       (.I0(timer_set[1]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(timer_set[0]),
        .O(\surplus_all_reg[1]_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT4 #(
    .INIT(16'h0502)) 
    \surplus_all_reg[1]_i_11 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(timer_set[1]),
        .O(\surplus_all_reg[1]_i_11_n_0 ));
  MUXF7 \surplus_all_reg[1]_i_2 
       (.I0(\surplus_all_reg[1]_i_4_n_0 ),
        .I1(\surplus_all_reg[1]_i_5_n_0 ),
        .O(\surplus_all_reg[1]_i_2_n_0 ),
        .S(state_OBUF[1]));
  MUXF7 \surplus_all_reg[1]_i_3 
       (.I0(\surplus_all_reg[1]_i_6_n_0 ),
        .I1(\surplus_all_reg[1]_i_7_n_0 ),
        .O(\surplus_all_reg[1]_i_3_n_0 ),
        .S(state_OBUF[1]));
  LUT6 #(
    .INIT(64'hB877B800B844B800)) 
    \surplus_all_reg[1]_i_4 
       (.I0(timer_set[1]),
        .I1(state_OBUF[0]),
        .I2(\surplus_all_reg[1]_i_8_n_0 ),
        .I3(surplus_curr13_out),
        .I4(surplus_curr1__0),
        .I5(\surplus_curr_reg[1]_i_9_n_0 ),
        .O(\surplus_all_reg[1]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h0303000800000037)) 
    \surplus_all_reg[1]_i_5 
       (.I0(timer_set[0]),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[1]),
        .I5(timer_set[1]),
        .O(\surplus_all_reg[1]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0026FFFF00260000)) 
    \surplus_all_reg[1]_i_6 
       (.I0(\surplus_curr_reg[1]_i_10_n_0 ),
        .I1(status_mode_OBUF[1]),
        .I2(status_mode_OBUF[0]),
        .I3(status_mode_OBUF[2]),
        .I4(state_OBUF[0]),
        .I5(\status_mode_reg[1]_1 ),
        .O(\surplus_all_reg[1]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hB888FFFFB8880000)) 
    \surplus_all_reg[1]_i_7 
       (.I0(\surplus_all_reg[1]_i_10_n_0 ),
        .I1(surplus_curr13_out),
        .I2(surplus_curr1__0),
        .I3(\surplus_curr_reg[1]_i_12_n_0 ),
        .I4(state_OBUF[0]),
        .I5(\surplus_all_reg[1]_i_11_n_0 ),
        .O(\surplus_all_reg[1]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT4 #(
    .INIT(16'h7887)) 
    \surplus_all_reg[1]_i_8 
       (.I0(timer_set[0]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(timer_set[1]),
        .O(\surplus_all_reg[1]_i_8_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \surplus_all_reg[2]_i_1 
       (.I0(\surplus_curr_reg[2]_i_2_n_0 ),
        .I1(state_OBUF[3]),
        .I2(\surplus_all_reg[2]_i_2_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_all_reg[2]_i_3_n_0 ),
        .O(\display_out[30] [2]));
  LUT6 #(
    .INIT(64'h0000000000011110)) 
    \surplus_all_reg[2]_i_10 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[2]),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(timer_set[2]),
        .I5(status_mode_OBUF[1]),
        .O(\surplus_all_reg[2]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h000000000078E187)) 
    \surplus_all_reg[2]_i_11 
       (.I0(timer_set[0]),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .I3(status_mode_OBUF[1]),
        .I4(status_mode_OBUF[0]),
        .I5(status_mode_OBUF[2]),
        .O(\surplus_all_reg[2]_i_11_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT5 #(
    .INIT(32'h3366366C)) 
    \surplus_all_reg[2]_i_13 
       (.I0(timer_set[1]),
        .I1(timer_set[2]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(timer_set[0]),
        .O(\surplus_all_reg[2]_i_13_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT5 #(
    .INIT(32'h06040103)) 
    \surplus_all_reg[2]_i_14 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(timer_set[1]),
        .I4(timer_set[2]),
        .O(\surplus_all_reg[2]_i_14_n_0 ));
  MUXF7 \surplus_all_reg[2]_i_2 
       (.I0(\surplus_all_reg[2]_i_4_n_0 ),
        .I1(\surplus_all_reg[2]_i_5_n_0 ),
        .O(\surplus_all_reg[2]_i_2_n_0 ),
        .S(state_OBUF[1]));
  MUXF7 \surplus_all_reg[2]_i_3 
       (.I0(\surplus_all_reg[2]_i_6_n_0 ),
        .I1(\surplus_all_reg[2]_i_7_n_0 ),
        .O(\surplus_all_reg[2]_i_3_n_0 ),
        .S(state_OBUF[1]));
  LUT6 #(
    .INIT(64'hB8BBB888B888B888)) 
    \surplus_all_reg[2]_i_4 
       (.I0(\surplus_all_reg[2]_i_8_n_0 ),
        .I1(state_OBUF[0]),
        .I2(\surplus_all_reg[2]_i_9_n_0 ),
        .I3(surplus_curr13_out),
        .I4(surplus_curr1__0),
        .I5(\surplus_curr_reg[2]_i_9_n_0 ),
        .O(\surplus_all_reg[2]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hB8BBB8888B888B88)) 
    \surplus_all_reg[2]_i_5 
       (.I0(\surplus_all_reg[2]_i_10_n_0 ),
        .I1(state_OBUF[0]),
        .I2(timer_set[1]),
        .I3(surplus_curr13_out),
        .I4(surplus_curr1__0),
        .I5(timer_set[2]),
        .O(\surplus_all_reg[2]_i_5_n_0 ));
  LUT3 #(
    .INIT(8'hB8)) 
    \surplus_all_reg[2]_i_6 
       (.I0(\surplus_all_reg[2]_i_11_n_0 ),
        .I1(state_OBUF[0]),
        .I2(\status_mode_reg[1]_0 ),
        .O(\surplus_all_reg[2]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hB888FFFFB8880000)) 
    \surplus_all_reg[2]_i_7 
       (.I0(\surplus_all_reg[2]_i_13_n_0 ),
        .I1(surplus_curr13_out),
        .I2(surplus_curr1__0),
        .I3(\surplus_curr_reg[2]_i_13_n_0 ),
        .I4(state_OBUF[0]),
        .I5(\surplus_all_reg[2]_i_14_n_0 ),
        .O(\surplus_all_reg[2]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT5 #(
    .INIT(32'h50030053)) 
    \surplus_all_reg[2]_i_8 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(timer_set[2]),
        .I4(timer_set[1]),
        .O(\surplus_all_reg[2]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT5 #(
    .INIT(32'h7F80F807)) 
    \surplus_all_reg[2]_i_9 
       (.I0(timer_set[0]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(timer_set[2]),
        .I4(timer_set[1]),
        .O(\surplus_all_reg[2]_i_9_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \surplus_all_reg[3]_i_1 
       (.I0(\surplus_curr_reg[3]_i_2_n_0 ),
        .I1(state_OBUF[3]),
        .I2(\surplus_all_reg[3]_i_2_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_all_reg[3]_i_3_n_0 ),
        .O(\display_out[30] [3]));
  LUT6 #(
    .INIT(64'h0F0F0011000000EE)) 
    \surplus_all_reg[3]_i_10 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[1]),
        .I5(timer_set[3]),
        .O(\surplus_all_reg[3]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h3416160716071643)) 
    \surplus_all_reg[3]_i_11 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[1]),
        .I2(timer_set[3]),
        .I3(timer_set[2]),
        .I4(timer_set[0]),
        .I5(timer_set[1]),
        .O(\surplus_all_reg[3]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h5A5A78785A7878F0)) 
    \surplus_all_reg[3]_i_13 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(timer_set[3]),
        .I3(Q[0]),
        .I4(Q[1]),
        .I5(timer_set[0]),
        .O(\surplus_all_reg[3]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h0607060501000102)) 
    \surplus_all_reg[3]_i_14 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(timer_set[2]),
        .I4(timer_set[1]),
        .I5(timer_set[3]),
        .O(\surplus_all_reg[3]_i_14_n_0 ));
  MUXF7 \surplus_all_reg[3]_i_2 
       (.I0(\surplus_all_reg[3]_i_4_n_0 ),
        .I1(\surplus_all_reg[3]_i_5_n_0 ),
        .O(\surplus_all_reg[3]_i_2_n_0 ),
        .S(state_OBUF[1]));
  MUXF7 \surplus_all_reg[3]_i_3 
       (.I0(\surplus_all_reg[3]_i_6_n_0 ),
        .I1(\surplus_all_reg[3]_i_7_n_0 ),
        .O(\surplus_all_reg[3]_i_3_n_0 ),
        .S(state_OBUF[1]));
  LUT6 #(
    .INIT(64'hB8BBB888B888B888)) 
    \surplus_all_reg[3]_i_4 
       (.I0(\surplus_all_reg[3]_i_8_n_0 ),
        .I1(state_OBUF[0]),
        .I2(\surplus_all_reg[3]_i_9_n_0 ),
        .I3(surplus_curr13_out),
        .I4(surplus_curr1__0),
        .I5(\surplus_curr_reg[3]_i_10_n_0 ),
        .O(\surplus_all_reg[3]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h0010FFFF00100000)) 
    \surplus_all_reg[3]_i_5 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[2]),
        .I2(\surplus_curr_reg[3]_i_11_n_0 ),
        .I3(status_mode_OBUF[1]),
        .I4(state_OBUF[0]),
        .I5(\surplus_all_reg[3]_i_10_n_0 ),
        .O(\surplus_all_reg[3]_i_5_n_0 ));
  LUT4 #(
    .INIT(16'h2F20)) 
    \surplus_all_reg[3]_i_6 
       (.I0(\surplus_all_reg[3]_i_11_n_0 ),
        .I1(status_mode_OBUF[2]),
        .I2(state_OBUF[0]),
        .I3(\status_weight_reg[1]_0 ),
        .O(\surplus_all_reg[3]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hB888FFFFB8880000)) 
    \surplus_all_reg[3]_i_7 
       (.I0(\surplus_all_reg[3]_i_13_n_0 ),
        .I1(surplus_curr13_out),
        .I2(surplus_curr1__0),
        .I3(\surplus_curr_reg[3]_i_13_n_0 ),
        .I4(state_OBUF[0]),
        .I5(\surplus_all_reg[3]_i_14_n_0 ),
        .O(\surplus_all_reg[3]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0350035000535003)) 
    \surplus_all_reg[3]_i_8 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(timer_set[3]),
        .I4(timer_set[1]),
        .I5(timer_set[2]),
        .O(\surplus_all_reg[3]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h7F80FF00FF00F807)) 
    \surplus_all_reg[3]_i_9 
       (.I0(timer_set[0]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(timer_set[3]),
        .I4(timer_set[1]),
        .I5(timer_set[2]),
        .O(\surplus_all_reg[3]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h00000000EEE222E2)) 
    \surplus_all_reg[4]_i_1 
       (.I0(\surplus_all_reg[4]_i_2_n_0 ),
        .I1(state_OBUF[2]),
        .I2(\surplus_all_reg[4]_i_3_n_0 ),
        .I3(state_OBUF[1]),
        .I4(\surplus_all_reg[4]_i_4_n_0 ),
        .I5(state_OBUF[3]),
        .O(\display_out[30] [4]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT5 #(
    .INIT(32'hBBBFFFFF)) 
    \surplus_all_reg[4]_i_10 
       (.I0(status_mode_OBUF[1]),
        .I1(timer_set[2]),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(timer_set[3]),
        .O(\surplus_all_reg[4]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h2624242524252465)) 
    \surplus_all_reg[4]_i_11 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[1]),
        .I2(timer_set[3]),
        .I3(timer_set[2]),
        .I4(timer_set[0]),
        .I5(timer_set[1]),
        .O(\surplus_all_reg[4]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h5F5F7F7F5F7F7FFF)) 
    \surplus_all_reg[4]_i_13 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(timer_set[3]),
        .I3(Q[0]),
        .I4(Q[1]),
        .I5(timer_set[0]),
        .O(\surplus_all_reg[4]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h0203020303030301)) 
    \surplus_all_reg[4]_i_14 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(timer_set[3]),
        .I4(timer_set[1]),
        .I5(timer_set[2]),
        .O(\surplus_all_reg[4]_i_14_n_0 ));
  MUXF7 \surplus_all_reg[4]_i_2 
       (.I0(\surplus_all_reg[4]_i_5_n_0 ),
        .I1(\surplus_all_reg[4]_i_6_n_0 ),
        .O(\surplus_all_reg[4]_i_2_n_0 ),
        .S(state_OBUF[1]));
  LUT6 #(
    .INIT(64'hB8BBB888B888B888)) 
    \surplus_all_reg[4]_i_3 
       (.I0(\surplus_all_reg[4]_i_7_n_0 ),
        .I1(state_OBUF[0]),
        .I2(\surplus_all_reg[4]_i_8_n_0 ),
        .I3(surplus_curr13_out),
        .I4(surplus_curr1__0),
        .I5(\surplus_curr_reg[4]_i_9_n_0 ),
        .O(\surplus_all_reg[4]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0003004700000044)) 
    \surplus_all_reg[4]_i_4 
       (.I0(\surplus_all_reg[4]_i_10_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[2]),
        .I5(\surplus_curr_reg[4]_i_8_n_0 ),
        .O(\surplus_all_reg[4]_i_4_n_0 ));
  LUT4 #(
    .INIT(16'h2F20)) 
    \surplus_all_reg[4]_i_5 
       (.I0(\surplus_all_reg[4]_i_11_n_0 ),
        .I1(status_mode_OBUF[2]),
        .I2(state_OBUF[0]),
        .I3(\status_weight_reg[1] ),
        .O(\surplus_all_reg[4]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hB888FFFFB8880000)) 
    \surplus_all_reg[4]_i_6 
       (.I0(\surplus_all_reg[4]_i_13_n_0 ),
        .I1(surplus_curr13_out),
        .I2(surplus_curr1__0),
        .I3(\surplus_curr_reg[4]_i_12_n_0 ),
        .I4(state_OBUF[0]),
        .I5(\surplus_all_reg[4]_i_14_n_0 ),
        .O(\surplus_all_reg[4]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h5353530303030000)) 
    \surplus_all_reg[4]_i_7 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(timer_set[1]),
        .I4(timer_set[2]),
        .I5(timer_set[3]),
        .O(\surplus_all_reg[4]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h7FFFFFFEFFFEFFFE)) 
    \surplus_all_reg[4]_i_8 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(timer_set[3]),
        .I3(Q[1]),
        .I4(Q[0]),
        .I5(timer_set[0]),
        .O(\surplus_all_reg[4]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h0000000033E200E2)) 
    \surplus_all_reg[5]_i_1 
       (.I0(\surplus_all_reg[5]_i_2_n_0 ),
        .I1(state_OBUF[1]),
        .I2(\surplus_all_reg[5]_i_3_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_all_reg[5]_i_4_n_0 ),
        .I5(state_OBUF[3]),
        .O(\display_out[30] [5]));
  LUT6 #(
    .INIT(64'h080808080808080B)) 
    \surplus_all_reg[5]_i_2 
       (.I0(\surplus_all_reg[5]_i_5_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[1]),
        .I4(\status_weight_reg[0]_0 ),
        .I5(status_mode_OBUF[0]),
        .O(\surplus_all_reg[5]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000080B0808)) 
    \surplus_all_reg[5]_i_3 
       (.I0(\surplus_all_reg[5]_i_7_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[0]),
        .I3(status_mode_OBUF[2]),
        .I4(\surplus_all_reg[5]_i_8_n_0 ),
        .I5(status_mode_OBUF[1]),
        .O(\surplus_all_reg[5]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h00008000)) 
    \surplus_all_reg[5]_i_4 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(\surplus_all_reg[5]_i_9_n_0 ),
        .I3(surplus_curr13_out),
        .I4(state_OBUF[0]),
        .O(\surplus_all_reg[5]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h00000000FE00FFF8)) 
    \surplus_all_reg[5]_i_5 
       (.I0(timer_set[1]),
        .I1(timer_set[0]),
        .I2(timer_set[2]),
        .I3(timer_set[3]),
        .I4(status_mode_OBUF[1]),
        .I5(status_mode_OBUF[0]),
        .O(\surplus_all_reg[5]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hA0A08080A0808000)) 
    \surplus_all_reg[5]_i_7 
       (.I0(timer_set[3]),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .I3(Q[0]),
        .I4(Q[1]),
        .I5(timer_set[0]),
        .O(\surplus_all_reg[5]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \surplus_all_reg[5]_i_8 
       (.I0(timer_set[2]),
        .I1(timer_set[3]),
        .O(\surplus_all_reg[5]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT4 #(
    .INIT(16'h8000)) 
    \surplus_all_reg[5]_i_9 
       (.I0(timer_set[0]),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .I3(timer_set[3]),
        .O(\surplus_all_reg[5]_i_9_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \surplus_curr_reg[0]_i_1 
       (.I0(\surplus_curr_reg[0]_i_2_n_0 ),
        .I1(state_OBUF[3]),
        .I2(\surplus_curr_reg[0]_i_3_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_curr_reg[0]_i_4_n_0 ),
        .O(\display_out[17] [0]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT4 #(
    .INIT(16'h0070)) 
    \surplus_curr_reg[0]_i_10 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(timer_set[0]),
        .I3(status_mode_OBUF[2]),
        .O(\surplus_curr_reg[0]_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT4 #(
    .INIT(16'h0007)) 
    \surplus_curr_reg[0]_i_11 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(timer_set[0]),
        .I3(status_mode_OBUF[2]),
        .O(\surplus_curr_reg[0]_i_11_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT4 #(
    .INIT(16'h0010)) 
    \surplus_curr_reg[0]_i_2 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[2]),
        .I2(timer_set[0]),
        .I3(status_mode_OBUF[1]),
        .O(\surplus_curr_reg[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h4F40FF0F4F40F000)) 
    \surplus_curr_reg[0]_i_3 
       (.I0(\status_mode_reg[2] ),
        .I1(\surplus_curr_reg[0]_i_6_n_0 ),
        .I2(state_OBUF[1]),
        .I3(\surplus_curr_reg[0]_i_7_n_0 ),
        .I4(state_OBUF[0]),
        .I5(\surplus_curr_reg[0]_i_8_n_0 ),
        .O(\surplus_curr_reg[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \surplus_curr_reg[0]_i_4 
       (.I0(\surplus_curr_reg[0]_i_9_n_0 ),
        .I1(\surplus_curr_reg[0]_i_10_n_0 ),
        .I2(state_OBUF[1]),
        .I3(\surplus_curr_reg[0]_i_11_n_0 ),
        .I4(state_OBUF[0]),
        .I5(\status_mode_reg[0]_0 ),
        .O(\surplus_curr_reg[0]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h1)) 
    \surplus_curr_reg[0]_i_6 
       (.I0(status_mode_OBUF[1]),
        .I1(timer_set[0]),
        .O(\surplus_curr_reg[0]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT4 #(
    .INIT(16'h5300)) 
    \surplus_curr_reg[0]_i_7 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(timer_set[0]),
        .O(\surplus_curr_reg[0]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT5 #(
    .INIT(32'h00535300)) 
    \surplus_curr_reg[0]_i_8 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(Q[0]),
        .I4(timer_set[0]),
        .O(\surplus_curr_reg[0]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT5 #(
    .INIT(32'h53000053)) 
    \surplus_curr_reg[0]_i_9 
       (.I0(status_mode_OBUF[2]),
        .I1(status_mode_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(Q[0]),
        .I4(timer_set[0]),
        .O(\surplus_curr_reg[0]_i_9_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \surplus_curr_reg[1]_i_1 
       (.I0(\surplus_curr_reg[1]_i_2_n_0 ),
        .I1(state_OBUF[3]),
        .I2(\surplus_curr_reg[1]_i_3_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_curr_reg[1]_i_4_n_0 ),
        .O(\display_out[17] [1]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \surplus_curr_reg[1]_i_10 
       (.I0(timer_set[0]),
        .I1(timer_set[1]),
        .O(\surplus_curr_reg[1]_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT4 #(
    .INIT(16'h5A69)) 
    \surplus_curr_reg[1]_i_12 
       (.I0(timer_set[1]),
        .I1(Q[0]),
        .I2(Q[1]),
        .I3(timer_set[0]),
        .O(\surplus_curr_reg[1]_i_12_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT4 #(
    .INIT(16'h0010)) 
    \surplus_curr_reg[1]_i_2 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[2]),
        .I2(timer_set[1]),
        .I3(status_mode_OBUF[1]),
        .O(\surplus_curr_reg[1]_i_2_n_0 ));
  MUXF7 \surplus_curr_reg[1]_i_3 
       (.I0(\surplus_curr_reg[1]_i_5_n_0 ),
        .I1(\surplus_curr_reg[1]_i_6_n_0 ),
        .O(\surplus_curr_reg[1]_i_3_n_0 ),
        .S(state_OBUF[1]));
  MUXF7 \surplus_curr_reg[1]_i_4 
       (.I0(\surplus_curr_reg[1]_i_7_n_0 ),
        .I1(\surplus_curr_reg[1]_i_8_n_0 ),
        .O(\surplus_curr_reg[1]_i_4_n_0 ),
        .S(state_OBUF[1]));
  LUT6 #(
    .INIT(64'h0707007704040044)) 
    \surplus_curr_reg[1]_i_5 
       (.I0(timer_set[1]),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[1]),
        .I5(\surplus_curr_reg[1]_i_9_n_0 ),
        .O(\surplus_curr_reg[1]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0303003B00000004)) 
    \surplus_curr_reg[1]_i_6 
       (.I0(timer_set[0]),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[1]),
        .I5(timer_set[1]),
        .O(\surplus_curr_reg[1]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h0070FFFF00700000)) 
    \surplus_curr_reg[1]_i_7 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(\surplus_curr_reg[1]_i_10_n_0 ),
        .I3(status_mode_OBUF[2]),
        .I4(state_OBUF[0]),
        .I5(\status_mode_reg[2]_0 ),
        .O(\surplus_curr_reg[1]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0008000883BB8088)) 
    \surplus_curr_reg[1]_i_8 
       (.I0(\surplus_curr_reg[1]_i_12_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[0]),
        .I4(timer_set[1]),
        .I5(status_mode_OBUF[2]),
        .O(\surplus_curr_reg[1]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT4 #(
    .INIT(16'h956A)) 
    \surplus_curr_reg[1]_i_9 
       (.I0(timer_set[1]),
        .I1(timer_set[0]),
        .I2(Q[0]),
        .I3(Q[1]),
        .O(\surplus_curr_reg[1]_i_9_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \surplus_curr_reg[2]_i_1 
       (.I0(\surplus_curr_reg[2]_i_2_n_0 ),
        .I1(state_OBUF[3]),
        .I2(\surplus_curr_reg[2]_i_3_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_curr_reg[2]_i_4_n_0 ),
        .O(\display_out[17] [2]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'h1E)) 
    \surplus_curr_reg[2]_i_10 
       (.I0(timer_set[1]),
        .I1(timer_set[0]),
        .I2(timer_set[2]),
        .O(\surplus_curr_reg[2]_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \surplus_curr_reg[2]_i_11 
       (.I0(timer_set[0]),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .O(\surplus_curr_reg[2]_i_11_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT5 #(
    .INIT(32'h99559556)) 
    \surplus_curr_reg[2]_i_13 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(Q[0]),
        .I3(Q[1]),
        .I4(timer_set[0]),
        .O(\surplus_curr_reg[2]_i_13_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT4 #(
    .INIT(16'h0010)) 
    \surplus_curr_reg[2]_i_2 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[2]),
        .I2(timer_set[2]),
        .I3(status_mode_OBUF[1]),
        .O(\surplus_curr_reg[2]_i_2_n_0 ));
  MUXF7 \surplus_curr_reg[2]_i_3 
       (.I0(\surplus_curr_reg[2]_i_5_n_0 ),
        .I1(\surplus_curr_reg[2]_i_6_n_0 ),
        .O(\surplus_curr_reg[2]_i_3_n_0 ),
        .S(state_OBUF[1]));
  MUXF7 \surplus_curr_reg[2]_i_4 
       (.I0(\surplus_curr_reg[2]_i_7_n_0 ),
        .I1(\surplus_curr_reg[2]_i_8_n_0 ),
        .O(\surplus_curr_reg[2]_i_4_n_0 ),
        .S(state_OBUF[1]));
  LUT6 #(
    .INIT(64'h9F9F9F0090909000)) 
    \surplus_curr_reg[2]_i_5 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(state_OBUF[0]),
        .I3(surplus_curr13_out),
        .I4(surplus_curr1__0),
        .I5(\surplus_curr_reg[2]_i_9_n_0 ),
        .O(\surplus_curr_reg[2]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0303003B00000008)) 
    \surplus_curr_reg[2]_i_6 
       (.I0(\surplus_curr_reg[2]_i_10_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[1]),
        .I5(timer_set[2]),
        .O(\surplus_curr_reg[2]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h0070FFFF00700000)) 
    \surplus_curr_reg[2]_i_7 
       (.I0(status_mode_OBUF[1]),
        .I1(status_mode_OBUF[0]),
        .I2(\surplus_curr_reg[2]_i_11_n_0 ),
        .I3(status_mode_OBUF[2]),
        .I4(state_OBUF[0]),
        .I5(\status_mode_reg[2]_1 ),
        .O(\surplus_curr_reg[2]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0008000883BB8088)) 
    \surplus_curr_reg[2]_i_8 
       (.I0(\surplus_curr_reg[2]_i_13_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[0]),
        .I4(timer_set[2]),
        .I5(status_mode_OBUF[2]),
        .O(\surplus_curr_reg[2]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT5 #(
    .INIT(32'h565A6AAA)) 
    \surplus_curr_reg[2]_i_9 
       (.I0(timer_set[2]),
        .I1(timer_set[0]),
        .I2(timer_set[1]),
        .I3(Q[0]),
        .I4(Q[1]),
        .O(\surplus_curr_reg[2]_i_9_n_0 ));
  LUT5 #(
    .INIT(32'hB8BBB888)) 
    \surplus_curr_reg[3]_i_1 
       (.I0(\surplus_curr_reg[3]_i_2_n_0 ),
        .I1(state_OBUF[3]),
        .I2(\surplus_curr_reg[3]_i_3_n_0 ),
        .I3(state_OBUF[2]),
        .I4(\surplus_curr_reg[3]_i_4_n_0 ),
        .O(\display_out[17] [3]));
  LUT6 #(
    .INIT(64'h9995959595555555)) 
    \surplus_curr_reg[3]_i_10 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(Q[0]),
        .I5(Q[1]),
        .O(\surplus_curr_reg[3]_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT4 #(
    .INIT(16'h1FE0)) 
    \surplus_curr_reg[3]_i_11 
       (.I0(timer_set[0]),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .I3(timer_set[3]),
        .O(\surplus_curr_reg[3]_i_11_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \surplus_curr_reg[3]_i_12 
       (.I0(timer_set[1]),
        .I1(timer_set[0]),
        .I2(timer_set[2]),
        .I3(timer_set[3]),
        .O(\surplus_curr_reg[3]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'hA9A9A5A5A9A5A595)) 
    \surplus_curr_reg[3]_i_13 
       (.I0(timer_set[3]),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .I3(Q[0]),
        .I4(Q[1]),
        .I5(timer_set[0]),
        .O(\surplus_curr_reg[3]_i_13_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT4 #(
    .INIT(16'h0010)) 
    \surplus_curr_reg[3]_i_2 
       (.I0(status_mode_OBUF[0]),
        .I1(status_mode_OBUF[2]),
        .I2(timer_set[3]),
        .I3(status_mode_OBUF[1]),
        .O(\surplus_curr_reg[3]_i_2_n_0 ));
  MUXF7 \surplus_curr_reg[3]_i_3 
       (.I0(\surplus_curr_reg[3]_i_5_n_0 ),
        .I1(\surplus_curr_reg[3]_i_6_n_0 ),
        .O(\surplus_curr_reg[3]_i_3_n_0 ),
        .S(state_OBUF[1]));
  MUXF7 \surplus_curr_reg[3]_i_4 
       (.I0(\surplus_curr_reg[3]_i_7_n_0 ),
        .I1(\surplus_curr_reg[3]_i_8_n_0 ),
        .O(\surplus_curr_reg[3]_i_4_n_0 ),
        .S(state_OBUF[1]));
  LUT6 #(
    .INIT(64'h0B0B00BB08080088)) 
    \surplus_curr_reg[3]_i_5 
       (.I0(\surplus_curr_reg[3]_i_9_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[1]),
        .I5(\surplus_curr_reg[3]_i_10_n_0 ),
        .O(\surplus_curr_reg[3]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0303003B00000008)) 
    \surplus_curr_reg[3]_i_6 
       (.I0(\surplus_curr_reg[3]_i_11_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[1]),
        .I5(timer_set[3]),
        .O(\surplus_curr_reg[3]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h0003070707070737)) 
    \surplus_curr_reg[3]_i_7 
       (.I0(\surplus_curr_reg[3]_i_12_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(Q[1]),
        .I4(status_mode_OBUF[1]),
        .I5(status_mode_OBUF[0]),
        .O(\surplus_curr_reg[3]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0008000883BB8088)) 
    \surplus_curr_reg[3]_i_8 
       (.I0(\surplus_curr_reg[3]_i_13_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[0]),
        .I4(timer_set[3]),
        .I5(status_mode_OBUF[2]),
        .O(\surplus_curr_reg[3]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'h1E)) 
    \surplus_curr_reg[3]_i_9 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(timer_set[3]),
        .O(\surplus_curr_reg[3]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h00000000EEE222E2)) 
    \surplus_curr_reg[4]_i_1 
       (.I0(\surplus_curr_reg[4]_i_3_n_0 ),
        .I1(state_OBUF[2]),
        .I2(\surplus_curr_reg[4]_i_4_n_0 ),
        .I3(state_OBUF[1]),
        .I4(\surplus_curr_reg[4]_i_5_n_0 ),
        .I5(state_OBUF[3]),
        .O(\display_out[17] [4]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'hA8)) 
    \surplus_curr_reg[4]_i_10 
       (.I0(timer_set[2]),
        .I1(timer_set[1]),
        .I2(timer_set[0]),
        .O(\surplus_curr_reg[4]_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT4 #(
    .INIT(16'hFF80)) 
    \surplus_curr_reg[4]_i_11 
       (.I0(timer_set[1]),
        .I1(timer_set[0]),
        .I2(timer_set[2]),
        .I3(timer_set[3]),
        .O(\surplus_curr_reg[4]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'hFEFEFAFAFEFAFAEA)) 
    \surplus_curr_reg[4]_i_12 
       (.I0(timer_set[3]),
        .I1(timer_set[1]),
        .I2(timer_set[2]),
        .I3(Q[0]),
        .I4(Q[1]),
        .I5(timer_set[0]),
        .O(\surplus_curr_reg[4]_i_12_n_0 ));
  MUXF7 \surplus_curr_reg[4]_i_3 
       (.I0(\surplus_curr_reg[4]_i_6_n_0 ),
        .I1(\surplus_curr_reg[4]_i_7_n_0 ),
        .O(\surplus_curr_reg[4]_i_3_n_0 ),
        .S(state_OBUF[1]));
  LUT6 #(
    .INIT(64'h0B0B00BB08080088)) 
    \surplus_curr_reg[4]_i_4 
       (.I0(\surplus_curr_reg[4]_i_8_n_0 ),
        .I1(state_OBUF[0]),
        .I2(status_mode_OBUF[2]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[1]),
        .I5(\surplus_curr_reg[4]_i_9_n_0 ),
        .O(\surplus_curr_reg[4]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000002000)) 
    \surplus_curr_reg[4]_i_5 
       (.I0(state_OBUF[0]),
        .I1(status_mode_OBUF[1]),
        .I2(\surplus_curr_reg[4]_i_10_n_0 ),
        .I3(timer_set[3]),
        .I4(status_mode_OBUF[2]),
        .I5(status_mode_OBUF[0]),
        .O(\surplus_curr_reg[4]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0000308800308888)) 
    \surplus_curr_reg[4]_i_6 
       (.I0(\surplus_curr_reg[4]_i_11_n_0 ),
        .I1(state_OBUF[0]),
        .I2(Q[1]),
        .I3(status_mode_OBUF[1]),
        .I4(status_mode_OBUF[2]),
        .I5(status_mode_OBUF[0]),
        .O(\surplus_curr_reg[4]_i_6_n_0 ));
  LUT5 #(
    .INIT(32'h00088088)) 
    \surplus_curr_reg[4]_i_7 
       (.I0(state_OBUF[0]),
        .I1(\surplus_curr_reg[4]_i_12_n_0 ),
        .I2(status_mode_OBUF[1]),
        .I3(status_mode_OBUF[0]),
        .I4(status_mode_OBUF[2]),
        .O(\surplus_curr_reg[4]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'hA8)) 
    \surplus_curr_reg[4]_i_8 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .I2(timer_set[1]),
        .O(\surplus_curr_reg[4]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hEEEAEAEAEAAAAAAA)) 
    \surplus_curr_reg[4]_i_9 
       (.I0(timer_set[3]),
        .I1(timer_set[2]),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(Q[0]),
        .I5(Q[1]),
        .O(\surplus_curr_reg[4]_i_9_n_0 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \timer_ini_reg[0] 
       (.CLR(1'b0),
        .D(\timer_ini_reg[0]_i_1_n_0 ),
        .G(light_running_OBUF),
        .GE(1'b1),
        .Q(timer_ini[0]));
  LUT5 #(
    .INIT(32'h23360114)) 
    \timer_ini_reg[0]_i_1 
       (.I0(state_OBUF[0]),
        .I1(state_OBUF[3]),
        .I2(state_OBUF[1]),
        .I3(state_OBUF[2]),
        .I4(Q[0]),
        .O(\timer_ini_reg[0]_i_1_n_0 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \timer_ini_reg[1] 
       (.CLR(1'b0),
        .D(\timer_ini_reg[1]_i_1_n_0 ),
        .G(light_running_OBUF),
        .GE(1'b1),
        .Q(timer_ini[1]));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT5 #(
    .INIT(32'h11043326)) 
    \timer_ini_reg[1]_i_1 
       (.I0(state_OBUF[0]),
        .I1(state_OBUF[3]),
        .I2(state_OBUF[1]),
        .I3(state_OBUF[2]),
        .I4(Q[1]),
        .O(\timer_ini_reg[1]_i_1_n_0 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \timer_ini_reg[2] 
       (.CLR(1'b0),
        .D(\timer_ini_reg[2]_i_1_n_0 ),
        .G(light_running_OBUF),
        .GE(1'b1),
        .Q(timer_ini[2]));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT5 #(
    .INIT(32'h32221000)) 
    \timer_ini_reg[2]_i_1 
       (.I0(state_OBUF[0]),
        .I1(state_OBUF[3]),
        .I2(state_OBUF[1]),
        .I3(state_OBUF[2]),
        .I4(Q[1]),
        .O(\timer_ini_reg[2]_i_1_n_0 ));
  (* XILINX_LEGACY_PRIM = "LD" *) 
  LDCE #(
    .INIT(1'b0)) 
    \timer_ini_reg[3] 
       (.CLR(1'b0),
        .D(\timer_ini_reg[3]_i_1_n_0 ),
        .G(light_running_OBUF),
        .GE(1'b1),
        .Q(timer_ini[3]));
  LUT6 #(
    .INIT(64'h0000000000000004)) 
    \timer_ini_reg[3]_i_1 
       (.I0(state_OBUF[2]),
        .I1(state_OBUF[1]),
        .I2(out[9]),
        .I3(out[10]),
        .I4(out[8]),
        .I5(state_OBUF[0]),
        .O(\timer_ini_reg[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT5 #(
    .INIT(32'h00000020)) 
    timer_out_i_1
       (.I0(light_running_OBUF),
        .I1(timer_set[0]),
        .I2(timer_set[1]),
        .I3(timer_set[3]),
        .I4(timer_set[2]),
        .O(timer_out_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    timer_out_reg
       (.C(CLK),
        .CE(1'b1),
        .D(timer_out_i_1_n_0),
        .Q(timer_out),
        .R(1'b0));
  LUT6 #(
    .INIT(64'h88888888BBBBBBB8)) 
    \timer_set[0]_i_1 
       (.I0(timer_ini[0]),
        .I1(\timer_set[3]_i_2_n_0 ),
        .I2(timer_set[2]),
        .I3(timer_set[3]),
        .I4(timer_set[1]),
        .I5(timer_set[0]),
        .O(\timer_set[0]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hB88BB88BB88BB888)) 
    \timer_set[1]_i_1 
       (.I0(timer_ini[1]),
        .I1(\timer_set[3]_i_2_n_0 ),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(timer_set[3]),
        .I5(timer_set[2]),
        .O(\timer_set[1]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hBBB8BBB8888B8888)) 
    \timer_set[2]_i_1 
       (.I0(timer_ini[2]),
        .I1(\timer_set[3]_i_2_n_0 ),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(timer_set[3]),
        .I5(timer_set[2]),
        .O(\timer_set[2]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hBBBB8888BBB88888)) 
    \timer_set[3]_i_1 
       (.I0(timer_ini[3]),
        .I1(\timer_set[3]_i_2_n_0 ),
        .I2(timer_set[1]),
        .I3(timer_set[0]),
        .I4(timer_set[3]),
        .I5(timer_set[2]),
        .O(\timer_set[3]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF6FF6)) 
    \timer_set[3]_i_2 
       (.I0(state_OBUF[1]),
        .I1(state_1[1]),
        .I2(state_OBUF[0]),
        .I3(state_1[0]),
        .I4(sign__3[2]),
        .I5(sign__3[3]),
        .O(\timer_set[3]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h0001FFFE)) 
    \timer_set[3]_i_3 
       (.I0(out[7]),
        .I1(out[6]),
        .I2(out[4]),
        .I3(out[5]),
        .I4(state_1[2]),
        .O(sign__3[2]));
  LUT4 #(
    .INIT(16'h01FE)) 
    \timer_set[3]_i_4 
       (.I0(out[9]),
        .I1(out[10]),
        .I2(out[8]),
        .I3(state_1[3]),
        .O(sign__3[3]));
  FDRE #(
    .INIT(1'b0)) 
    \timer_set_reg[0] 
       (.C(CLK),
        .CE(light_running_OBUF),
        .D(\timer_set[0]_i_1_n_0 ),
        .Q(timer_set[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \timer_set_reg[1] 
       (.C(CLK),
        .CE(light_running_OBUF),
        .D(\timer_set[1]_i_1_n_0 ),
        .Q(timer_set[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \timer_set_reg[2] 
       (.C(CLK),
        .CE(light_running_OBUF),
        .D(\timer_set[2]_i_1_n_0 ),
        .Q(timer_set[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \timer_set_reg[3] 
       (.C(CLK),
        .CE(light_running_OBUF),
        .D(\timer_set[3]_i_1_n_0 ),
        .Q(timer_set[3]),
        .R(1'b0));
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY4 water_line0_carry
       (.CI(1'b0),
        .CO({water_line0_carry_n_0,water_line0_carry_n_1,water_line0_carry_n_2,water_line0_carry_n_3}),
        .CYINIT(water_line_reg__0),
        .DI({water_line[3:1],water_line0_carry_i_1_n_0}),
        .O(p_0_in__0[4:1]),
        .S({water_line0_carry_i_2_n_0,water_line0_carry_i_3_n_0,water_line0_carry_i_4_n_0,water_line0_carry_i_5_n_0}));
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-8 {cell *THIS*}}" *) 
  CARRY4 water_line0_carry__0
       (.CI(water_line0_carry_n_0),
        .CO({NLW_water_line0_carry__0_CO_UNCONNECTED[3:2],water_line0_carry__0_n_2,water_line0_carry__0_n_3}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,water_line[5:4]}),
        .O({NLW_water_line0_carry__0_O_UNCONNECTED[3],p_0_in__0[7:5]}),
        .S({1'b0,water_line0_carry__0_i_1_n_0,water_line0_carry__0_i_2_n_0,water_line0_carry__0_i_3_n_0}));
  LUT2 #(
    .INIT(4'h9)) 
    water_line0_carry__0_i_1
       (.I0(water_line[6]),
        .I1(water_line[7]),
        .O(water_line0_carry__0_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line0_carry__0_i_2
       (.I0(water_line[5]),
        .I1(water_line[6]),
        .O(water_line0_carry__0_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line0_carry__0_i_3
       (.I0(water_line[4]),
        .I1(water_line[5]),
        .O(water_line0_carry__0_i_3_n_0));
  LUT1 #(
    .INIT(2'h1)) 
    water_line0_carry_i_1
       (.I0(water_line[1]),
        .O(water_line0_carry_i_1_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line0_carry_i_2
       (.I0(water_line[3]),
        .I1(water_line[4]),
        .O(water_line0_carry_i_2_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line0_carry_i_3
       (.I0(water_line[2]),
        .I1(water_line[3]),
        .O(water_line0_carry_i_3_n_0));
  LUT2 #(
    .INIT(4'h9)) 
    water_line0_carry_i_4
       (.I0(water_line[1]),
        .I1(water_line[2]),
        .O(water_line0_carry_i_4_n_0));
  LUT4 #(
    .INIT(16'h5655)) 
    water_line0_carry_i_5
       (.I0(water_line[1]),
        .I1(state_OBUF[1]),
        .I2(state_OBUF[3]),
        .I3(state_OBUF[0]),
        .O(water_line0_carry_i_5_n_0));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \water_line[0]_i_1 
       (.I0(water_line_reg__0),
        .O(p_0_in__0[0]));
  LUT2 #(
    .INIT(4'h2)) 
    \water_line[7]_i_1 
       (.I0(light_running_OBUF),
        .I1(\display_out_OBUF[7]_inst_i_3_n_0 ),
        .O(\water_line[7]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0008)) 
    \water_line[7]_i_2 
       (.I0(light_running_OBUF),
        .I1(state_OBUF[0]),
        .I2(state_OBUF[3]),
        .I3(\timer_set[3]_i_2_n_0 ),
        .O(\water_line[7]_i_2_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \water_line_reg[0] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(p_0_in__0[0]),
        .Q(water_line_reg__0),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \water_line_reg[1] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(p_0_in__0[1]),
        .Q(water_line[1]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \water_line_reg[2] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(p_0_in__0[2]),
        .Q(water_line[2]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \water_line_reg[3] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(p_0_in__0[3]),
        .Q(water_line[3]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \water_line_reg[4] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(p_0_in__0[4]),
        .Q(water_line[4]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \water_line_reg[5] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(p_0_in__0[5]),
        .Q(water_line[5]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \water_line_reg[6] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(p_0_in__0[6]),
        .Q(water_line[6]),
        .R(\water_line[7]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \water_line_reg[7] 
       (.C(CLK),
        .CE(\water_line[7]_i_2_n_0 ),
        .D(p_0_in__0[7]),
        .Q(water_line[7]),
        .R(\water_line[7]_i_1_n_0 ));
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
