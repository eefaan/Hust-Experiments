`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/20 08:46:18
// Design Name:
// Module Name: datapath_sim
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


module datapath_sim(

    );

    reg rst;
    reg clk;
    reg go;

    wire [31:0]led_data;
    wire [15:0]all_num;
    wire [15:0]no_conditional_branch_num;
    wire [15:0]conditional_branch_num;

    datapath TB_datapath(
        .rst(rst),
        .clk(clk),
        .go(1'b0),

        .watch(1'b0),
        .led_data(led_data),
        .all_num(all_num),
        .no_conditional_branch_num(no_conditional_branch_num),
        .conditional_branch_num(conditional_branch_num)
    );

    initial begin
        // initial
        rst=1'b0;
        go=1'b0;
        clk=1'b0;

        // reset
        #5 rst=1'b1;
        #20 rst=1'b0;
    end

    always@(*)begin
        #10 clk<=~clk;
    end
endmodule
