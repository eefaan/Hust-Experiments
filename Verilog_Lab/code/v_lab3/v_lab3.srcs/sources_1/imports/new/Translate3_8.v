`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/18 19:41:07
// Design Name: 
// Module Name: Translate3_8
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


module Translate3_8(sw, seg, an, led, dp);
	input [15:0] sw;       // 16位拨动开关
	output reg [6:0] seg;      // 7段数码管驱动，低电平有效
	output reg [7:0] an;       // 7段数码管片选信号，低电平有效
	output [15:0] led;     // 16位LED显示
	output reg dp;
	
//	always(sw);
    assign led[15:0] = sw[15:0];
    
    
    always @(sw) 
    begin
        case(sw[3:0])
            4'b0000: {dp,seg} = 8'b11000000;
            4'b0001: {dp,seg} = 8'b11111001;
            4'b0010: {dp,seg} = 8'b10100100;
            4'b0011: {dp,seg} = 8'b10110000;
            4'b0100: {dp,seg} = 8'b10011001;
            4'b0101: {dp,seg} = 8'b10010010;
            4'b0110: {dp,seg} = 8'b10000010;
            4'b0111: {dp,seg} = 8'b11111000;
            4'b1000: {dp,seg} = 8'b10000000;
            4'b1001: {dp,seg} = 8'b10011000;
            4'b1010: {dp,seg} = 8'b10001000;
            4'b1011: {dp,seg} = 8'b10000011;
            4'b1100: {dp,seg} = 8'b11000110;
            4'b1101: {dp,seg} = 8'b10100001;
            4'b1110: {dp,seg} = 8'b10000110;
            4'b1111: {dp,seg} = 8'b10001110;
        endcase
    end
    
    always @(sw) 
        begin
            case(sw[14:12])
                3'b000: an = 8'b11111110;
                3'b001: an = 8'b11111101;
                3'b010: an = 8'b11111011;
                3'b011: an = 8'b11110111;
                3'b100: an = 8'b11101111;
                3'b101: an = 8'b11011111;
                3'b110: an = 8'b10111111;
                3'b111: an = 8'b01111111;
            endcase
        end

endmodule
