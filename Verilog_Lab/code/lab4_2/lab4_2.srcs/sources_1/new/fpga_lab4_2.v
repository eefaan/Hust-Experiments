`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/14 04:10:49
// Design Name: 
// Module Name: lab4_2_sim
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


module fpga_lab4_2(
    input clk_x,
    input rst,
    input num,
    output sign,
    output [2:0]state
    );
    
    FSM myfsm(clk,rst,x,sign,state);
    
endmodule
