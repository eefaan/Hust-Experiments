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
    input clk;                      // 系统时钟
    input sw;
    output reg clk_N;                   // 分频后的时钟
    parameter N = 10_000_000;      // 1Hz的时钟,N=fclk/fclk_N
    reg [31:0] counter;             /* 计数器变量，通过计数实现分频。
                                       当计数器从0计数到(N/2-1)时，
                                       输出时钟翻转，计数器清零 */


    always @(posedge clk)  begin    // 时钟上升沿
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
