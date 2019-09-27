`timescale 1ns / 1ps

module multiplexer_circuit
#(parameter WIDTH = 8)(
    input selector,
    input [WIDTH-1:0] a,
    input [WIDTH-1:0] b,
    output [WIDTH-1:0] out
    );        
    
    assign out = selector? a : b;
endmodule
