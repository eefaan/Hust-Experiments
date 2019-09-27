`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/21 08:12:23
// Design Name: 
// Module Name: combine_logic_top
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


module combine_logic_top(
    input [2:0]     p_sel,
    input [3:0]     d_in1,
    input [3:0]     d_in2,
    input [3:0]     op,
    output [6:0]    seg_out,
    output [7:0]    AN
);
    wire [3:0]  data;

    display_decoder UDD (.sel(p_sel), .out(AN));
    
    sevenseg_dec SSD (.data(data), .segments(seg_out));
    
    digital_dec DGD (.p_sel(p_sel), .d_in1(d_in1), .d_in2(d_in2), .op(op), .d_out(data));
    
endmodule
