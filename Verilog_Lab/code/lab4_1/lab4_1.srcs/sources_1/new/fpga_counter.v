`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 13:06:46
// Design Name: 
// Module Name: counter_sim
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


module fpga_counter(
    input clk_count,
    input rst,
    input en,
    output [3:0]dout,
    output cout
    );
    
    reg [3:0]data;//load data
    reg load;     //choose load
    
    counter #(2,9) mycounter(clk_count,rst,en,data,load,dout,cout);
    
    
endmodule
