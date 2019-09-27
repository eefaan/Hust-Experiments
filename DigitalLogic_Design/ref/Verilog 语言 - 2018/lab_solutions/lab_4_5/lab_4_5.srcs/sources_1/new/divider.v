`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/21 09:43:02
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


module divider (clk, clk_N);
    input           clk;                      // ϵͳʱ��
    output reg      clk_N;                    // ��Ƶ���ʱ��
    parameter      N = 50_000_000;          // 1Hz��ʱ��,N=fclk/fclk_N
    reg [31:0]      counter;                 /* ������������ͨ������ʵ�ַ�Ƶ��
                                                ����������0������(N/2-1)ʱ��
                                                ���ʱ�ӷ�ת������������ */
    always @(posedge clk)  begin              // ʱ��������
        if(counter==N) begin
            clk_N <= ~clk_N;
            counter <= 32'h0;
        end   
            
        else
            counter <= counter + 1;
    end
                                   
endmodule
