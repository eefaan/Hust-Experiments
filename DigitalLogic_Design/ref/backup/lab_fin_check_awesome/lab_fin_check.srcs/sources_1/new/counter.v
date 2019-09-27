`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/23 14:51:56
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
    input clk_F,
    output reg [2:0]num// 计数值
    );
    initial begin
        num = 0;
    end
    always @(posedge clk_F)begin  // 在时钟上升沿计数器加1
        num = num + 1;
    end
                       
endmodule
