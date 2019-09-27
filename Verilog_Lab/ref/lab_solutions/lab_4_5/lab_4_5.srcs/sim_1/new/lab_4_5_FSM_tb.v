`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/21 09:16:37
// Design Name: 
// Module Name: lab_4_5_FSM_tb
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


module lab_4_5_FSM_tb( );
    reg         clk;
    reg         rst;
    reg         start;
    reg         next_zero;
    wire        a_sel;
    wire        sum_sel;
    wire        next_sel;
    wire        ld_sum;
    wire        ld_next;
    wire        done;
    
    lab_4_5_FSM DUT(
        .clk(clk),
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
    
    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk;
    end
    
    initial begin
        rst = 1'b1;
        start = 1'b0;
        next_zero = 1'b0;
        #50 rst = 1'b0;
        #50 start = 1'b1;
        #500 next_zero = 1'b1;
        #100 start = 1'b0;
    end

endmodule
