`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/06/13 05:21:02
// Design Name:
// Module Name: counter
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


module counter_16 #(parameter LOW=0, parameter HIGH=15)(
    input clk,      //clock
    input rst,      //reset
    input en,       //choose inc or dec
    input [3:0]data,//load data
    input load,     //choose load
    output [3:0] dout,//4bits output
    output reg cout     //co output
    );

    reg [3:0]Q1;
    assign dout=Q1;

    always @(posedge clk or negedge rst) begin
        if(rst) Q1<=LOW;
        else if (en) begin//add counter
            if(load) Q1<=data;
            else if(Q1<HIGH) Q1<=Q1+1;
            else Q1<=LOW;
        end
        else if(!en) begin//dec counter
            if(load) Q1<=data;
            else if(Q1>LOW) Q1<=Q1-1;
            else Q1<=HIGH;
        end
    end

    always @(Q1) begin
        if(en) begin
            if(Q1==HIGH) cout=1'b1;
            else cout=1'b0;
        end
        else if(!en) begin
            if(Q1==LOW)cout=1'b1;
            else cout=1'b0;
        end
    end

endmodule
