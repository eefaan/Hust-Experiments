`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/07 20:19:46
// Design Name: 
// Module Name: clk_s
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


module divider#(parameter  N = 20000000)(
    input clk,
    output reg clk_N
);
    reg [31:0]counter;
    initial begin
        counter <= 0;
        clk_N <= 0;
    end
    always @ (posedge clk) begin
        counter = counter + 1;
        if(counter == N/2)  begin
            clk_N = ~clk_N;
            counter = 0;
        end
    end
endmodule
