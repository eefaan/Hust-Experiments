`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/18 21:19:24
// Design Name: 
// Module Name: dynamic_scan
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


module dynamic_scan(clk,sw,  seg, an);
    input clk;              // 系统时钟
    input [1:0]sw;
    output [6:0] seg;  		// 分别对应CA、CB、CC、CD、CE、CF、CG和DP
    output [7:0] an;        // 8位数码管片选信号
    
    wire clk_N;
    wire [2:0]num;
    wire [3:0]data;
    
    divider My_Div (clk,sw[1],clk_N);//分频
    counter My_Cou (clk_N,sw[0],num);//num循环0~7
    decoder3_8(num,an);//3-8num选择亮起的七位显示管
    rom8x4(num, data);//num选择data
    sevenseg_decoder(data, seg);//data七位译码显示数字
endmodule
