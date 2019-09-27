`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/21 08:18:23
// Design Name: 
// Module Name: display_decoder
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


module display_decoder(
    input  [2:0]        sel,
    output reg [7:0]    out
);

    always @(sel) begin
        case(sel)
            3'd0: out=8'b11111110;
            3'd1: out=8'b11111101;
            //3'd2: out=8'b11111011;
            //3'd3: out=8'b11110111;
            //3'd4: out=8'b11101111;
            3'd5: out=8'b11011111;
            //3'd6: out=8'b10111111;
            3'd7: out=8'b01111111;
            default: out = 8'b11111111;
        endcase
    end
    
endmodule
