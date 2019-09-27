`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/21 09:55:26
// Design Name: 
// Module Name: seven_seg_display
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


module seven_seg_display(
    input             clk100MHZ,
    input [31:0]      dig,
    output  [7:0]     SEG,
    output  [7:0]     AN
);
    wire        clk_N;
    wire [2:0]  num;
    wire [3:0]  data;
    
    divider #(5000) u_divider(.clk(clk100MHZ), .clk_N(clk_N));

    Counter u_counter(.clk(clk_N), .out(num));

    decoder3_8 u_d38(.num(num), .sel(AN));

    display_sel u_ds(.num(num), .dig(dig), .code(data));

    sevenseg_dec u_sd(.data(data), .segments(SEG));


endmodule
