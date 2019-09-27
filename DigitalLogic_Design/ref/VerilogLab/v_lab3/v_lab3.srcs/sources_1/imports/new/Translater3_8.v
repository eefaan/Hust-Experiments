`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/18 19:29:40
// Design Name: 
// Module Name: Translater3_8
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


module Translater3_8(sw, seg, dp ,an, led);
	input [15:0] sw;                          // 16位拨动开关
    output reg dp;  // 7段数码管驱动，低电平有效
    output reg [6:0] seg;
    output [7:0] an;                          // 7段数码管片选信号，低电平有效
    output [15:0] led;                        // 16位LED显示，高电平有效
    //assign seg[0] = ~sw [7];
    // assign seg[1] = ~sw [6];
    //assign seg[2] = ~sw [5];
    //assign seg[3] = ~sw [4];
    //assign seg[4] = ~sw [3];
    //assign seg[5] = ~sw [2];
    //assign seg[6] = ~sw [1];
    //assign dp = ~sw[0];
    assign an [7:0] = ~sw [15:8];
    assign led [15:0] = sw [15:0];
    always@(*) begin
    case(sw[3:0])
        4 'b0010:{dp , seg[0:6]} = 10100100;
        4 'b0011:{dp , seg[0:6]} = 10110000;
        4 'b0100:{dp , seg[0:6]} = 10011001;
        4 'b0101:{dp , seg[0:6]} = 10010010;
        4 'b0110:{dp , seg[0:6]} = 10000010;
        4 'b0111:{dp , seg[0:6]} = 11111000;
        4 'b1000:{dp , seg[0:6]} = 10000000;
        4 'b1001:{dp , seg[0:6]} = 10011000;
        4 'b1010:{dp , seg[0:6]} = 10001000;
        4 'b1011:{dp , seg[0:6]} = 10000011;
        4 'b1100:{dp , seg[0:6]} = 11000110;
        4 'b1101:{dp , seg[0:6]} = 10100001;
        4 'b1110:{dp , seg[0:6]} = 10000110;
        4 'b1111:{dp , seg[0:6]} = 10001110;
        default: ;
    endcase
    end
endmodule

