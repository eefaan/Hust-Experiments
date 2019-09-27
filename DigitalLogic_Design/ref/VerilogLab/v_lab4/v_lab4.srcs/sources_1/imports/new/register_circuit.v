`timescale 1ns / 1ps

module register_circuit
#(parameter WIDTH = 8)(
    input clk,
    input rst,
    input ld_name,
    input [WIDTH-1:0] num_in,
    output reg [WIDTH-1:0] num_out
    );    
    
    always @(clk) begin//posedge ÉÏÉıÑØ
        if(rst) num_out=0;
        else if(ld_name) num_out=num_in;
    end
endmodule
