`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/09/27 11:29:50
// Design Name:
// Module Name: timer_sim
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


module timer_sim(

    );
    //timer中的输入
    reg rst;
    reg [3:0]state;
    reg [1:0]status_weight;
    reg [2:0]status_mode;
    reg pause_con,mode_change,power_in,power_out;
    //模拟的工作时钟与秒时钟
    reg clk,clk_N;

    wire next_fin;//sign of shutdown
    wire timer_out;//sign of jumping state
    wire [13:0]timer_set;
    wire [13:0]water_line;

    initial begin
        rst=0;
        clk=0;
        clk_N=0;
        state=0;
        status_mode=0;
        status_weight=0;
        pause_con=0;//
        mode_change=0;//
        power_in=0;
        power_out=0;

        //在非START状态下尝试为倒计时赋初值
        #7 state=4'b0001;
        status_mode=1;
        power_in=1;
        power_out=0;

        //跳转到START状态，此时能够为倒计时赋初值
        #10 state=4'b0000;
        status_mode=1;
        power_in = 1;
        power_out = 0;

        //依次更换洗衣模式，倒计时初值变化
        #10 status_mode=2;
        #10 status_mode=3;
        #10 status_mode=4;
        #10 status_mode=5;
        #10 status_mode=6;

        //倒计时开始，按预计输出timer_out脉冲
        #10 state=4'b0111;
        power_out=1;

        //暂停计时
        #1500 power_out=0;
        #100 power_out=1;

        //进行FINISH状态下的十秒倒计时，预计输出next_fin脉冲
        #1500 power_in=0;
        power_out=1;

    end

    always @(*) begin
        #4  clk_N <= ~clk_N;
        #4  clk_N <= ~clk_N;
    end

    always @(*) begin
        #1  clk <= ~clk;
        #1  clk <= ~clk;
    end

    timer my_timer(rst,state,status_weight,status_mode,pause_con,mode_change,
      power_in,power_out,clk,clk_N,next_fin,timer_out,timer_set,water_line);

endmodule
