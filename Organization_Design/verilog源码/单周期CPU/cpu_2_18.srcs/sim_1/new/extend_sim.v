`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/19 08:36:42
// Design Name:
// Module Name: extend_sim
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


module extend_sim(

    );

    reg [15:0] unex;
    reg [7:0] unex8;
    wire [31:0] ext_16_32;
    wire [31:0] ext_8_32;
    wire [31:0] ext_16_32_u;
    wire [31:0] ext_8_32_u;
    sign_extend TB_1632_SIGNEXT(
        .unextend(unex),
        .extended(ext_16_32)
    );
    sign_extend #(8) TB_832_SIGNEXT(
        .unextend(unex8),
        .extended(ext_8_32)
    );
    unsign_extend TB_1632_UNSIGNEXT(
        .unextend(unex),
        .extended(ext_16_32_u)
    );
    unsign_extend #(8) TB_832_UNSIGNEXT(
        .unextend(unex8),
        .extended(ext_8_32_u)
    );

    initial begin
        unex = {16{1'b1}};
        unex8 = {8{1'b1}};
    end

    initial begin
    #10 unex = 16'b0000_0000_0000_0000;
    end

endmodule
