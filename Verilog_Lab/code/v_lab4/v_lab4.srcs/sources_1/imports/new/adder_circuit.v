`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/01 21:25:34
// Design Name: 
// Module Name: adder_circuit
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

module adder_circuit
#(parameter WIDTH = 8)(
    input  [WIDTH-1:0] num1,
    input  [WIDTH-1:0] num2,
    output [WIDTH-1:0] sum
    );    
    
    assign sum = num1 + num2;
endmodule
