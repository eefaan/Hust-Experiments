`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/05/18 20:08:09
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


module counter(
    input clk,
    output reg [15:0] out,
    input enable,
    input rst
    );

    always @(posedge clk)  begin
        if(enable) out =out +1;
        if(rst) out=0;
    end

endmodule
