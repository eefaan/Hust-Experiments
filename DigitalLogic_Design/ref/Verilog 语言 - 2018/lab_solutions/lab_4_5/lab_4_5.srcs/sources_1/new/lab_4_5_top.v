`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/21 09:27:20
// Design Name: 
// Module Name: lab_4_5_top
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


module lab_4_5_top(
    input           clk100MHZ,
    input           rst,
    input           start,
    output [7:0]    AN,
    output [7:0]    SEG_N,
    output          done
);
    wire            clk_1HZ;
    wire [31:0]     sum_out;
    
    wire            sum_sel, next_sel, a_sel;
    wire            ld_sum, ld_next;
    wire            next_zero;
      
    divider u_1HZ(.clk(clk100MHZ), .clk_N(clk_1HZ));
    
    lab_4_5datapath u_dp(
        .clk(clk_1HZ),
        //.clk(clk100MHZ),
        .rst(rst),
        .sum_sel(sum_sel),
        .next_sel(next_sel),
        .a_sel(a_sel),
        .ld_sum(ld_sum),
        .ld_next(ld_next),
        .next_zero(next_zero),
        .sum_out(sum_out)    
    );
    
    lab_4_5_FSM u_FSM(
        .clk(clk_1HZ),
        //.clk(clk100MHZ),
        .rst(rst),
        .start(start),
        .next_zero(next_zero),
        .a_sel(a_sel),
        .ld_sum(ld_sum),
        .sum_sel(sum_sel),
        .ld_next(ld_next),
        .next_sel(next_sel),
        .done(done)
    );
    
    seven_seg_display u_disp(
        .clk100MHZ(clk100MHZ),
        .dig(sum_out),
        .SEG(SEG_N),
        .AN(AN)
    );

endmodule
