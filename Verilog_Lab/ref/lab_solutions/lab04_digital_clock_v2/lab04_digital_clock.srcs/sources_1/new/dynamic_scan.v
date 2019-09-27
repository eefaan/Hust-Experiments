`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/12 10:38:50
// Design Name: 
// Module Name: dynamic_scan
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


module dynamic_scan(
    input             clk100MHZ,
    input   [3:0]     dig0,
    input   [3:0]     dig1,
    input   [3:0]     dig2,
    input   [3:0]     dig3,
    input   [3:0]     dig4,
    input   [3:0]     dig5,
    input   [3:0]     dig6,
    input   [3:0]     dig7,
    output  [7:0]     SEG,
    output  [7:0]     AN
);
    
    wire        clk_N;
    wire [2:0]  num;
    wire [3:0]  data;
        
    divider #(5000) u_divider(.clk(clk100MHZ), .clk_N(clk_N));
    
    Counter u_counter(.clk(clk_N), .out(num));
    
    decoder3_8 u_d38(.num(num), .sel(AN));
    
    display_sel u_ds(.num(num), .dig0(dig0), .dig1(dig1), .dig2(dig2), .dig3(dig3), .dig4(dig4), .dig5(dig5), .dig6(dig6), .dig7(dig7), .code(data));
    
    sevenseg_dec u_sd(.data(data), .segments(SEG));

endmodule
