`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/21 08:40:51
// Design Name: 
// Module Name: lab_4_5_datapath
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


module register_circuit(clk, rst, ld, d, q);
    parameter WIDTH = 8;
    input clk, rst, ld;
    input [WIDTH-1:0] d;
    output reg [WIDTH-1:0] q;
    
    always @(posedge clk) begin
        if(rst) q <= 0;
        else if(ld) q <= d;
    end
endmodule

module adder_circuit(a, b, sum);
    parameter WIDTH = 8;
    input [WIDTH-1:0] a, b;
    output [WIDTH-1:0] sum;
    
    assign sum = a + b;
endmodule

module memory_circuit(clk, we, data, addr);
    parameter DATA_WIDTH=8;
    parameter ADDR_WIDTH=4;

	inout [(DATA_WIDTH-1):0] data;
	input [(ADDR_WIDTH-1):0] addr;
	input we, clk;

	// Declare the RAM variable
	reg [DATA_WIDTH-1:0] ram[2**ADDR_WIDTH-1:0];
	
	initial begin
	   $readmemh("C:/Temp/lab_4_5/rom_init.txt", ram);
	end

	always @ (posedge clk)
	begin
		if (we)
			ram[addr] <= data;
	end
	
	assign data = we? 32'bz : ram[addr];
endmodule

module multiplex_circuit(a, b, sel, out);
    parameter WIDTH = 8;
    input [WIDTH-1:0] a, b;
    input sel;
    output [WIDTH-1:0] out;
    
    assign out = sel? a : b;
endmodule

module compare_circuit(in, out);
    parameter WIDTH = 8;
    input [WIDTH-1:0] in;
    output reg out;
    
    always @(in) begin
        if(in ==0)
            out = 1'b1;
        else
            out = 1'b0;
    end
endmodule


module lab_4_5datapath(
    input           clk,
    input           rst,
    input           sum_sel,
    input           next_sel,
    input           a_sel,
    input           ld_sum,
    input           ld_next,
    output          next_zero,
    output [31:0]   sum_out
);

    wire [31:0] adder1_out, adder2_out, sum_in, next_in, next_out, data;
    wire [31:0]  addr_out;
    
    adder_circuit #(32) A1 (sum_out, data, adder1_out);
    adder_circuit #(32) A2 (1, next_out, adder2_out);
                  
    register_circuit #(32) R1 (clk, rst, ld_sum, sum_in, sum_out);
    register_circuit #(32) R2 (clk, rst, ld_next, next_in, next_out);
    
    multiplex_circuit #(32) M1 (adder1_out, 0, sum_sel, sum_in);
    multiplex_circuit #(32) M2 (data, 0, next_sel, next_in);
    multiplex_circuit #(32) M3 (adder2_out, next_out, a_sel, addr_out);
    
    memory_circuit #(32, 4) MEM (clk, 1'b0, data, addr_out[3:0]);
    
    compare_circuit #(32) COMP (next_in, next_zero);

endmodule

