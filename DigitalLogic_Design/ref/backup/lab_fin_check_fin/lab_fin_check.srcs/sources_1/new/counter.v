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
    output reg [2:0]num// ����ֵ
    );
    initial begin
        num = 0;
    end
    always @(posedge clk_F)begin  // ��ʱ�������ؼ�������1
        num = num + 1;
    end
                       
endmodule
