`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/08 12:43:03
// Design Name: 
// Module Name: lab4_cal
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module lab4_cal(
    input clk,
    input rst,
    input start,
    output done,
    
    output [6:0] seg,          // 分别对应CA、CB、CC、CD、CE、CF、CG和DP
    output [7:0] an        // 8位数码管片选信号
    );
    
    wire ld_sum;
    wire ld_next;
    wire sum_sel;
    wire next_sel;
    wire a_sel;
    wire next_zero;
    wire clk_N;
    wire [31:0]sum_out;
    wire clk_F;//foever

    divider clk_div(clk,clk_N,clk_F);
    FSM my_fsm(clk_N, rst, start, next_zero, a_sel, ld_sum, sum_sel, ld_next, next_sel, done);
    datapath my_datapath(clk_N, rst, ld_sum, ld_next, sum_sel, next_sel, a_sel, next_zero, sum_out);
    
    
    wire [2:0]num;
    wire [3:0]data;
    sum_rom my_sum(num,sum_out,data);//choose data
    counter my_coun(clk_F,num);//num 0->7->0->...
    decoder3_8 my_3_8(num,an);//choose the lighting seven_seg
    sevenseg_decoder my_seven(data,seg);//show number with seven_seg
    
endmodule
