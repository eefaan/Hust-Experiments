// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.2 (win64) Build 1909853 Thu Jun 15 18:39:09 MDT 2017
// Date        : Thu Sep 27 16:59:38 2018
// Host        : DESKTOP-KM458MG running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               C:/VerilogLab/lab_fin_check/lab_fin_check.sim/sim_1/impl/timing/timer_sim_time_impl.v
// Design      : display
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

module counter
   (an_OBUF,
    seg_OBUF,
    CLK,
    rst_IBUF,
    shut_IBUF,
    display_out_IBUF);
  output [5:0]an_OBUF;
  output [6:0]seg_OBUF;
  input CLK;
  input rst_IBUF;
  input shut_IBUF;
  input [31:0]display_out_IBUF;

  wire CLK;
  wire [5:0]an_OBUF;
  wire [31:0]display_out_IBUF;
  wire [2:0]num;
  wire \num[2]_i_1_n_0 ;
  wire [1:0]p_0_in;
  wire rst_IBUF;
  wire [6:0]seg_OBUF;
  wire \seg_OBUF[6]_inst_i_10_n_0 ;
  wire \seg_OBUF[6]_inst_i_11_n_0 ;
  wire \seg_OBUF[6]_inst_i_12_n_0 ;
  wire \seg_OBUF[6]_inst_i_13_n_0 ;
  wire \seg_OBUF[6]_inst_i_6_n_0 ;
  wire \seg_OBUF[6]_inst_i_7_n_0 ;
  wire \seg_OBUF[6]_inst_i_8_n_0 ;
  wire \seg_OBUF[6]_inst_i_9_n_0 ;
  wire [3:0]sel0;
  wire shut_IBUF;

  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \an_OBUF[0]_inst_i_1 
       (.I0(num[0]),
        .I1(rst_IBUF),
        .I2(shut_IBUF),
        .I3(num[2]),
        .I4(num[1]),
        .O(an_OBUF[0]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'hFFFFFFEF)) 
    \an_OBUF[1]_inst_i_1 
       (.I0(rst_IBUF),
        .I1(shut_IBUF),
        .I2(num[0]),
        .I3(num[2]),
        .I4(num[1]),
        .O(an_OBUF[1]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'hFFFFFFF7)) 
    \an_OBUF[3]_inst_i_1 
       (.I0(num[1]),
        .I1(num[0]),
        .I2(num[2]),
        .I3(rst_IBUF),
        .I4(shut_IBUF),
        .O(an_OBUF[2]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFD)) 
    \an_OBUF[4]_inst_i_1 
       (.I0(num[2]),
        .I1(rst_IBUF),
        .I2(shut_IBUF),
        .I3(num[1]),
        .I4(num[0]),
        .O(an_OBUF[3]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'hFFEFFFFF)) 
    \an_OBUF[6]_inst_i_1 
       (.I0(rst_IBUF),
        .I1(shut_IBUF),
        .I2(num[1]),
        .I3(num[0]),
        .I4(num[2]),
        .O(an_OBUF[4]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'hFFFFFF7F)) 
    \an_OBUF[7]_inst_i_1 
       (.I0(num[1]),
        .I1(num[0]),
        .I2(num[2]),
        .I3(rst_IBUF),
        .I4(shut_IBUF),
        .O(an_OBUF[5]));
  LUT1 #(
    .INIT(2'h1)) 
    \num[0]_i_1 
       (.I0(num[0]),
        .O(p_0_in[0]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \num[1]_i_1 
       (.I0(num[0]),
        .I1(num[1]),
        .O(p_0_in[1]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \num[2]_i_1 
       (.I0(num[1]),
        .I1(num[0]),
        .I2(num[2]),
        .O(\num[2]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \num_reg[0] 
       (.C(CLK),
        .CE(1'b1),
        .D(p_0_in[0]),
        .Q(num[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \num_reg[1] 
       (.C(CLK),
        .CE(1'b1),
        .D(p_0_in[1]),
        .Q(num[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \num_reg[2] 
       (.C(CLK),
        .CE(1'b1),
        .D(\num[2]_i_1_n_0 ),
        .Q(num[2]),
        .R(1'b0));
  LUT4 #(
    .INIT(16'h2094)) 
    \seg_OBUF[0]_inst_i_1 
       (.I0(sel0[3]),
        .I1(sel0[2]),
        .I2(sel0[0]),
        .I3(sel0[1]),
        .O(seg_OBUF[0]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'hA4C8)) 
    \seg_OBUF[1]_inst_i_1 
       (.I0(sel0[3]),
        .I1(sel0[2]),
        .I2(sel0[1]),
        .I3(sel0[0]),
        .O(seg_OBUF[1]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'hA210)) 
    \seg_OBUF[2]_inst_i_1 
       (.I0(sel0[3]),
        .I1(sel0[0]),
        .I2(sel0[1]),
        .I3(sel0[2]),
        .O(seg_OBUF[2]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'hC234)) 
    \seg_OBUF[3]_inst_i_1 
       (.I0(sel0[3]),
        .I1(sel0[2]),
        .I2(sel0[0]),
        .I3(sel0[1]),
        .O(seg_OBUF[3]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'h5710)) 
    \seg_OBUF[4]_inst_i_1 
       (.I0(sel0[3]),
        .I1(sel0[1]),
        .I2(sel0[2]),
        .I3(sel0[0]),
        .O(seg_OBUF[4]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT4 #(
    .INIT(16'h5190)) 
    \seg_OBUF[5]_inst_i_1 
       (.I0(sel0[3]),
        .I1(sel0[2]),
        .I2(sel0[0]),
        .I3(sel0[1]),
        .O(seg_OBUF[5]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT4 #(
    .INIT(16'h4025)) 
    \seg_OBUF[6]_inst_i_1 
       (.I0(sel0[3]),
        .I1(sel0[0]),
        .I2(sel0[2]),
        .I3(sel0[1]),
        .O(seg_OBUF[6]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \seg_OBUF[6]_inst_i_10 
       (.I0(display_out_IBUF[14]),
        .I1(display_out_IBUF[10]),
        .I2(num[1]),
        .I3(display_out_IBUF[6]),
        .I4(num[0]),
        .I5(display_out_IBUF[2]),
        .O(\seg_OBUF[6]_inst_i_10_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \seg_OBUF[6]_inst_i_11 
       (.I0(display_out_IBUF[30]),
        .I1(display_out_IBUF[26]),
        .I2(num[1]),
        .I3(display_out_IBUF[22]),
        .I4(num[0]),
        .I5(display_out_IBUF[18]),
        .O(\seg_OBUF[6]_inst_i_11_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \seg_OBUF[6]_inst_i_12 
       (.I0(display_out_IBUF[13]),
        .I1(display_out_IBUF[9]),
        .I2(num[1]),
        .I3(display_out_IBUF[5]),
        .I4(num[0]),
        .I5(display_out_IBUF[1]),
        .O(\seg_OBUF[6]_inst_i_12_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \seg_OBUF[6]_inst_i_13 
       (.I0(display_out_IBUF[29]),
        .I1(display_out_IBUF[25]),
        .I2(num[1]),
        .I3(display_out_IBUF[21]),
        .I4(num[0]),
        .I5(display_out_IBUF[17]),
        .O(\seg_OBUF[6]_inst_i_13_n_0 ));
  MUXF7 \seg_OBUF[6]_inst_i_2 
       (.I0(\seg_OBUF[6]_inst_i_6_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_7_n_0 ),
        .O(sel0[3]),
        .S(num[2]));
  MUXF7 \seg_OBUF[6]_inst_i_3 
       (.I0(\seg_OBUF[6]_inst_i_8_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_9_n_0 ),
        .O(sel0[0]),
        .S(num[2]));
  MUXF7 \seg_OBUF[6]_inst_i_4 
       (.I0(\seg_OBUF[6]_inst_i_10_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_11_n_0 ),
        .O(sel0[2]),
        .S(num[2]));
  MUXF7 \seg_OBUF[6]_inst_i_5 
       (.I0(\seg_OBUF[6]_inst_i_12_n_0 ),
        .I1(\seg_OBUF[6]_inst_i_13_n_0 ),
        .O(sel0[1]),
        .S(num[2]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \seg_OBUF[6]_inst_i_6 
       (.I0(display_out_IBUF[15]),
        .I1(display_out_IBUF[11]),
        .I2(num[1]),
        .I3(display_out_IBUF[7]),
        .I4(num[0]),
        .I5(display_out_IBUF[3]),
        .O(\seg_OBUF[6]_inst_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \seg_OBUF[6]_inst_i_7 
       (.I0(display_out_IBUF[31]),
        .I1(display_out_IBUF[27]),
        .I2(num[1]),
        .I3(display_out_IBUF[23]),
        .I4(num[0]),
        .I5(display_out_IBUF[19]),
        .O(\seg_OBUF[6]_inst_i_7_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \seg_OBUF[6]_inst_i_8 
       (.I0(display_out_IBUF[12]),
        .I1(display_out_IBUF[8]),
        .I2(num[1]),
        .I3(display_out_IBUF[4]),
        .I4(num[0]),
        .I5(display_out_IBUF[0]),
        .O(\seg_OBUF[6]_inst_i_8_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \seg_OBUF[6]_inst_i_9 
       (.I0(display_out_IBUF[28]),
        .I1(display_out_IBUF[24]),
        .I2(num[1]),
        .I3(display_out_IBUF[20]),
        .I4(num[0]),
        .I5(display_out_IBUF[16]),
        .O(\seg_OBUF[6]_inst_i_9_n_0 ));
endmodule

(* ECO_CHECKSUM = "ac8865e3" *) 
(* NotValidForBitStream *)
module display
   (rst,
    shut,
    display_out,
    clk_F,
    seg,
    an);
  input rst;
  input shut;
  input [31:0]display_out;
  input clk_F;
  output [6:0]seg;
  output [7:0]an;

  wire [7:0]an;
  wire [7:0]an_OBUF;
  wire clk_F;
  wire clk_F_IBUF;
  wire clk_F_IBUF_BUFG;
  wire [31:0]display_out;
  wire [31:0]display_out_IBUF;
  wire rst;
  wire rst_IBUF;
  wire [6:0]seg;
  wire [6:0]seg_OBUF;
  wire shut;
  wire shut_IBUF;

initial begin
 $sdf_annotate("timer_sim_time_impl.sdf",,,,"tool_control");
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
  BUFG clk_F_IBUF_BUFG_inst
       (.I(clk_F_IBUF),
        .O(clk_F_IBUF_BUFG));
  IBUF clk_F_IBUF_inst
       (.I(clk_F),
        .O(clk_F_IBUF));
  IBUF \display_out_IBUF[0]_inst 
       (.I(display_out[0]),
        .O(display_out_IBUF[0]));
  IBUF \display_out_IBUF[10]_inst 
       (.I(display_out[10]),
        .O(display_out_IBUF[10]));
  IBUF \display_out_IBUF[11]_inst 
       (.I(display_out[11]),
        .O(display_out_IBUF[11]));
  IBUF \display_out_IBUF[12]_inst 
       (.I(display_out[12]),
        .O(display_out_IBUF[12]));
  IBUF \display_out_IBUF[13]_inst 
       (.I(display_out[13]),
        .O(display_out_IBUF[13]));
  IBUF \display_out_IBUF[14]_inst 
       (.I(display_out[14]),
        .O(display_out_IBUF[14]));
  IBUF \display_out_IBUF[15]_inst 
       (.I(display_out[15]),
        .O(display_out_IBUF[15]));
  IBUF \display_out_IBUF[16]_inst 
       (.I(display_out[16]),
        .O(display_out_IBUF[16]));
  IBUF \display_out_IBUF[17]_inst 
       (.I(display_out[17]),
        .O(display_out_IBUF[17]));
  IBUF \display_out_IBUF[18]_inst 
       (.I(display_out[18]),
        .O(display_out_IBUF[18]));
  IBUF \display_out_IBUF[19]_inst 
       (.I(display_out[19]),
        .O(display_out_IBUF[19]));
  IBUF \display_out_IBUF[1]_inst 
       (.I(display_out[1]),
        .O(display_out_IBUF[1]));
  IBUF \display_out_IBUF[20]_inst 
       (.I(display_out[20]),
        .O(display_out_IBUF[20]));
  IBUF \display_out_IBUF[21]_inst 
       (.I(display_out[21]),
        .O(display_out_IBUF[21]));
  IBUF \display_out_IBUF[22]_inst 
       (.I(display_out[22]),
        .O(display_out_IBUF[22]));
  IBUF \display_out_IBUF[23]_inst 
       (.I(display_out[23]),
        .O(display_out_IBUF[23]));
  IBUF \display_out_IBUF[24]_inst 
       (.I(display_out[24]),
        .O(display_out_IBUF[24]));
  IBUF \display_out_IBUF[25]_inst 
       (.I(display_out[25]),
        .O(display_out_IBUF[25]));
  IBUF \display_out_IBUF[26]_inst 
       (.I(display_out[26]),
        .O(display_out_IBUF[26]));
  IBUF \display_out_IBUF[27]_inst 
       (.I(display_out[27]),
        .O(display_out_IBUF[27]));
  IBUF \display_out_IBUF[28]_inst 
       (.I(display_out[28]),
        .O(display_out_IBUF[28]));
  IBUF \display_out_IBUF[29]_inst 
       (.I(display_out[29]),
        .O(display_out_IBUF[29]));
  IBUF \display_out_IBUF[2]_inst 
       (.I(display_out[2]),
        .O(display_out_IBUF[2]));
  IBUF \display_out_IBUF[30]_inst 
       (.I(display_out[30]),
        .O(display_out_IBUF[30]));
  IBUF \display_out_IBUF[31]_inst 
       (.I(display_out[31]),
        .O(display_out_IBUF[31]));
  IBUF \display_out_IBUF[3]_inst 
       (.I(display_out[3]),
        .O(display_out_IBUF[3]));
  IBUF \display_out_IBUF[4]_inst 
       (.I(display_out[4]),
        .O(display_out_IBUF[4]));
  IBUF \display_out_IBUF[5]_inst 
       (.I(display_out[5]),
        .O(display_out_IBUF[5]));
  IBUF \display_out_IBUF[6]_inst 
       (.I(display_out[6]),
        .O(display_out_IBUF[6]));
  IBUF \display_out_IBUF[7]_inst 
       (.I(display_out[7]),
        .O(display_out_IBUF[7]));
  IBUF \display_out_IBUF[8]_inst 
       (.I(display_out[8]),
        .O(display_out_IBUF[8]));
  IBUF \display_out_IBUF[9]_inst 
       (.I(display_out[9]),
        .O(display_out_IBUF[9]));
  counter my_coun
       (.CLK(clk_F_IBUF_BUFG),
        .an_OBUF({an_OBUF[7:6],an_OBUF[4:3],an_OBUF[1:0]}),
        .display_out_IBUF(display_out_IBUF),
        .rst_IBUF(rst_IBUF),
        .seg_OBUF(seg_OBUF),
        .shut_IBUF(shut_IBUF));
  IBUF rst_IBUF_inst
       (.I(rst),
        .O(rst_IBUF));
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
  IBUF shut_IBUF_inst
       (.I(shut),
        .O(shut_IBUF));
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
