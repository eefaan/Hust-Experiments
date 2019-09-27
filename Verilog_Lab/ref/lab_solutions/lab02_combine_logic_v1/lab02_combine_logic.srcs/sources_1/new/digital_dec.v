`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/21 08:28:31
// Design Name: 
// Module Name: digital_dec
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


module digital_dec(
    input [2:0]     p_sel, 
    input [3:0]     d_in1,
    input [3:0]     d_in2,
    input [3:0]     op,
    output reg [3:0]     d_out
);

    reg [3:0]   data1, data2;
        
    always @(*) begin
        case(p_sel)
            3'b000: d_out = data2;
            3'b001: d_out = data1;
            3'b101: d_out = d_in2;
            3'b111: d_out = d_in1;
            default: d_out = 4'b0000;
        endcase
    end
    
    always @(*) begin
        case(op)
            4'd0: begin data1 = 4'b0000; {data1[0],data2} = d_in1 + d_in2; end      // op is add
            4'd1: begin data1 = 4'b0000; data2 =d_in1 - d_in2; end                  // op is unsigned sub
            4'd2: begin data1 = 4'b0000; data2 = d_in1 & d_in2; end                 // op is and
            4'd3: begin data1 = 4'b0000; data2 = d_in1 | d_in2; end                 // op is or
            4'd4: begin data1 = 4'b0000; data2 = d_in1 ^ d_in2; end                 // op is xor
            default: begin data1 = 4'b0000; data2 = 4'b0000; end
        endcase
    end
    
endmodule
