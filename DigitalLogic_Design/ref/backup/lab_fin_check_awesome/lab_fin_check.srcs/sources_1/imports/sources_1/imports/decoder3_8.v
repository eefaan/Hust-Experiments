`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/05/18 21:16:05
// Design Name:
// Module Name: decoder3_8
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


module decoder3_8(rst,shut,num,an);
		input rst;
		input shut;
		input [2: 0] num;       // 16λ��������
    output reg [7:0] an;       // 7��������Ƭѡ�źţ��͵�ƽ��Ч

		always @(num) begin
				if(!rst && !shut)begin
		        case(num)
		            3'b000: an = 8'b11111110;
		            3'b001: an = 8'b11111101;
		            // 3'b010: an = 8'b11111011;
		            3'b011: an = 8'b11110111;
		            3'b100: an = 8'b11101111;
		            // 3'b101: an = 8'b11011111;
		            3'b110: an = 8'b10111111;
		            3'b111: an = 8'b01111111;
		            default:an = 8'b11111111;
		        endcase
				end
				else an=8'b11111111;
		end
endmodule
