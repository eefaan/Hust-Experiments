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
    input           clk;                      // 系统时钟
    output reg      clk_N;                    // 分频后的时钟
    parameter      N = 50_000_000;          // 1Hz的时钟,N=fclk/fclk_N
    reg [31:0]      counter;                 /* 计数器变量，通过计数实现分频。
                                                当计数器从0计数到(N/2-1)时，
                                                输出时钟翻转，计数器清零 */
    always @(posedge clk)  begin              // 时钟上升沿
        if(counter==N) begin
            clk_N <= ~clk_N;
            counter <= 32'h0;
        end   
            
        else
            counter <= counter + 1;
    end
                                   
endmodule
