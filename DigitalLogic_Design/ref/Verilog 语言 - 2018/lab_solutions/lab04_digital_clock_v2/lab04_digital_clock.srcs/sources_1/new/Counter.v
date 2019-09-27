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
    input                   clk;                    // 计数时钟
    output reg [2:0]        out;             // 计数值
    
    always @(posedge clk)  begin  // 在时钟上升沿计数器加1
        out <= out + 1;
    end                           

endmodule
