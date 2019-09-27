`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/06/14 04:33:48
// Design Name:
// Module Name: compare_3
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


module compare_3#(parameter WIDTH=3)(
    input [WIDTH-1:0]num1,
    input [WIDTH-1:0]num2,
    output reg [2:0]sign
    );

    initial begin
        sign=0;
    end

    always @(*) begin
        if(num1>num2) sign=3'b100;
        else if(num1==num2) sign=3'b010;
        else sign=3'b001;
    end

endmodule
