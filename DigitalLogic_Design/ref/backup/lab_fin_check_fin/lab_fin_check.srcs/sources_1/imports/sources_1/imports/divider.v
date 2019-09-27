`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/06/08 12:39:16
// Design Name:
// Module Name: divider
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


module divider #(parameter  N = 80000000)(
    input clk,
    output reg clk_N,
    output reg clk_F
);
    reg [31:0]counter;
    reg [31:0]counter_f;
    parameter M=20000;
    initial begin
        counter <= 0;
        clk_N <= 0;
    end

    always @ (posedge clk) begin
        counter = counter + 1;
        if(counter > N/2)  begin
            clk_N = ~clk_N;
            counter = 0;
        end
    end

    always @(posedge clk) begin
        counter_f = counter_f + 1;
        if(counter_f > M) begin
            clk_F = ~clk_F;
            counter_f = 0;
        end
    end

endmodule
