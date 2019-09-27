`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/18 19:38:06
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


module divider(clk,sw,clk_N);
    input clk;                      // ϵͳʱ��
    input sw;
    output reg clk_N;                   // ��Ƶ���ʱ��
    parameter N = 10_000_000;      // 1Hz��ʱ��,N=fclk/fclk_N
    reg [31:0] counter;             /* ������������ͨ������ʵ�ַ�Ƶ��
                                       ����������0������(N/2-1)ʱ��
                                       ���ʱ�ӷ�ת������������ */


    always @(posedge clk)  begin    // ʱ��������
        counter = counter + 1; 
        if(sw) begin
            if(counter > 10000) begin
                counter = 0;
                clk_N = ~clk_N;
            end
        end
        else begin
            if(counter == N/2 -1) begin
                counter = 0;
                clk_N = ~clk_N;
            end
        end
        
    end  

endmodule
