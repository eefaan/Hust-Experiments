`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/18 20:44:15
// Design Name:
// Module Name: extend
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

module sign_extend # (parameter in_width = 16)(
    input [in_width-1:0]unextend,
    output [31:0]extended
    );

    assign extended = {{(32-in_width){unextend[in_width-1]}}, unextend};

endmodule

module unsign_extend # (parameter in_width = 16)(
    input [in_width-1:0]unextend,
    output [31:0]extended
    );

    assign extended = {{(32-in_width){1'b0}}, unextend};

endmodule
