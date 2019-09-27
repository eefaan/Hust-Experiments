`timescale 1ns / 1ps

module compare_circuit
#(parameter WIDTH = 8)(
    input  [WIDTH-1:0] in,
    output reg out
    );    

    always @(in) begin
        if(in ==0)
            out = 1'b1;
        else
            out = 1'b0;
        end
        
endmodule
