`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/20 08:23:01
// Design Name:
// Module Name: cpu_sim
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


module cpu_sim(

    );

    reg rst,//reset cpu
    reg clk,//sys clock
    reg go,//go button
    reg button_all,
    reg button_con,
    reg button_nocon,
    reg button_ram,
    reg button_switch_ram,

    //display 7seg
    wire [6:0] seg,
    wire [7:0] an

    cpu28 TB_cpu28(
        .rst(rst),
        .clk(clk),
        .go(1'b0),
        .button_all(button_all),
        .button_con(button_con),
        .button_noncon(button_noncon),
        .button_ram(button_ram),
        .button_switch_ram(button_switch_ram)
    );

    initial begin
        // initial
        rst=1'b0;
        clk=1'b0;

        // reset
        #5 rst=1'b1;
        #20 rst=1'b0;
    end

    always@(*)begin
        #10 clk<=~clk;
    end

endmodule
