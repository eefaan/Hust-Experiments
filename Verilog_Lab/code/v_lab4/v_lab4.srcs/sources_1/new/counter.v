`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/18 20:16:37
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


module counter(clk_N, out);
input clk_N;
output reg [2:0] out;             // 计数值 
    always @(posedge clk_N)  begin  // 在时钟上升沿计数器加1
        out = out+1;
    end                           
endmodule
