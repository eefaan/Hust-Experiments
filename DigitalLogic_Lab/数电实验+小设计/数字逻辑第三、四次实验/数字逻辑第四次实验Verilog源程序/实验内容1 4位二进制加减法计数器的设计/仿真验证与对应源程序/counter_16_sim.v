`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/06/13 13:06:46
// Design Name:
// Module Name: counter_sim
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


module counter_sim(

    );

    reg clk_sim;      //clock
    reg rst;      //reset
    reg en;       //choose inc or dec
    reg [3:0]data;//load data
    reg load;     //choose load
    wire [3:0] dout;//4bits output
    wire cout;     //co output


    counter_16 #(0,15) mycounter(clk_sim,rst,en,data,load,dout,cout);

    always begin
        clk_sim<=0;
        #10;
        clk_sim<=1;
        #10;
    end

    always begin
        en=1;
        #1000;
        en=0;
        #1000;
    end

    initial begin
        clk_sim=0;
        rst=0;
        data=4'b0010;

        load=0;
        #7;
        load=1;
        #20;
        load=~load;

        #50;
        rst=1;
        #20;
        rst=0;
    end

endmodule
