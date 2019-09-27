`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/09/26 17:15:57
// Design Name:
// Module Name: display
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


module display(
    input rst,
    input shut,
    input [31:0]display_out,
    input clk_F,
    output [6:0]seg,
    output [7:0]an
    );

    wire [2:0]num;
    wire [3:0]data;
    sum_rom my_sum(num,display_out,data);//choose data, data = part of display_out
    counter my_coun(clk_F,num);//num 0->7->0->...
    decoder3_8 my_3_8(rst,shut,num,an);//choose the lighting seven_seg
    sevenseg_decoder my_seven(data,seg);//show data with seven_seg

endmodule
