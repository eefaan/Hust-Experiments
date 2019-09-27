`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/01 20:42:35
// Design Name: 
// Module Name: datapath
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


module datapath(
    input clk,
    input rst,
    input ld_sum,
    input ld_next,
    input sum_sel,
    input next_sel,
    input a_sel,
    output next_zero,
    output [31:0]sum_out
    );
    
    wire [31:0] adder1_out, adder2_out, sum_in, next_in, next_out, data;
    wire [31:0] addr_out;
    
    adder_circuit #(32) Adder_1 (sum_out, data, adder1_out);
    adder_circuit #(32) Adder_2 (1, next_out, adder2_out);
    
    multiplexer_circuit #(32) Mul_1 (sum_sel, adder1_out, 0, sum_in);
    multiplexer_circuit #(32) Mul_2 (next_sel, data, 0, next_in);
    multiplexer_circuit #(32) Mul_3 (a_sel, adder2_out, next_out, addr_out);
        
    register_circuit #(32) Reg_1 (clk, rst, ld_sum, sum_in, sum_out);
    register_circuit #(32) Reg_2 (clk, rst, ld_next, next_in, next_out);

    memory_circuit #(32, 4) Mem (clk, 1'b0, data, addr_out[3:0]);
    
    compare_circuit #(32) Com (next_in, next_zero);
endmodule
