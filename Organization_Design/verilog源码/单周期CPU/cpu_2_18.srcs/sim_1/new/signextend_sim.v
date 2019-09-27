`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/18 20:48:55
// Design Name:
// Module Name: signextend_sim
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


module signextend_sim;
    reg  [15:0] unex;
    wire   [31:0] ext;
    sign_extend TBSIGNEXT(
        .unextend(unex),
        .extended(ext)
    );

    initial begin
        unex = 16'd0;
    end

    initial begin
    #10 unex = 16'b0000_0000_1111_1111;
    #20 unex = 16'b1000_0000_1111_1111;
    end

endmodule
