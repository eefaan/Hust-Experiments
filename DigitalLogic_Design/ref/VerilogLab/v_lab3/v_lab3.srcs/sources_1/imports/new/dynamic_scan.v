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
    input clk;              // ϵͳʱ��
    input [1:0]sw;
    output [6:0] seg;  		// �ֱ��ӦCA��CB��CC��CD��CE��CF��CG��DP
    output [7:0] an;        // 8λ�����Ƭѡ�ź�
    
    wire clk_N;
    wire [2:0]num;
    wire [3:0]data;
    
    divider My_Div (clk,sw[1],clk_N);//��Ƶ
    counter My_Cou (clk_N,sw[0],num);//numѭ��0~7
    decoder3_8(num,an);//3-8numѡ���������λ��ʾ��
    rom8x4(num, data);//numѡ��data
    sevenseg_decoder(data, seg);//data��λ������ʾ����
endmodule
