`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/12 10:47:38
// Design Name: 
// Module Name: Counter
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


module Counter(clk, out);
    input                   clk;                    // ����ʱ��
    output reg [2:0]        out;             // ����ֵ
    
    always @(posedge clk)  begin  // ��ʱ�������ؼ�������1
        out <= out + 1;
    end                           

endmodule
