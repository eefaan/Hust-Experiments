`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/19 08:26:31
// Design Name:
// Module Name: Display
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

/*
    include: display(head file),
             sum_rom(to store the data of led), counter(flash led),
             decoder3_8, sevenseg_decoder
*/

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
    counter_display my_coun(clk_F,num);//num 0->7->0->...
    decoder3_8 my_3_8(rst,shut,num,an);//choose the lighting seven_seg
    sevenseg_decoder my_seven(data,seg);//show data with seven_seg

endmodule


//////////////////////////////////////////////////////////////////////////////////


module sum_rom(addr, sum_out, data);
    input [2:0] addr;           // 地址
    input [31:0] sum_out;
    output reg [3:0] data;          // 地址addr处存储的数据

always @(addr)  begin    //根据addr地址值 用初始化的存储器mem为data赋值
        case(addr)
            3'b000: data = sum_out[3:0];
            3'b001: data = sum_out[7:4];
            3'b010: data = sum_out[11:8];
            3'b011: data = sum_out[15:12];
            3'b100: data = sum_out[19:16];
            3'b101: data = sum_out[23:20];
            3'b110: data = sum_out[27:24];
            3'b111: data = sum_out[31:28];
            default: data = 0;
        endcase
    end
endmodule


//////////////////////////////////////////////////////////////////////////////////


module counter_display(
    input clk_F,
    output reg [2:0]num// 计数值
    );
    initial begin
        num = 0;
    end
    always @(posedge clk_F)begin  // 在时钟上升沿计数器加1
        num = num + 1;
    end

endmodule


//////////////////////////////////////////////////////////////////////////////////


module decoder3_8(rst,shut,num,an);
	input rst;
	input shut;
	input [2: 0] num;       // 16位
	output reg [7:0] an;       // 7段

	always @(num) begin
		if(!rst && !shut)begin
	        case(num)
	            3'b000: an = 8'b11111110;
	            3'b001: an = 8'b11111101;
	            3'b010: an = 8'b11111011;
	            3'b011: an = 8'b11110111;
	            3'b100: an = 8'b11101111;
	            3'b101: an = 8'b11011111;
	            3'b110: an = 8'b10111111;
	            3'b111: an = 8'b01111111;
	            default:an = 8'b11111111;
	        endcase
		end
		else an=8'b11111111;
	end
endmodule


//////////////////////////////////////////////////////////////////////////////////


module sevenseg_decoder(code, seg);
    input [3: 0] code;
    output reg [6:0] seg;      // 7段数码管驱动，低电平有效

always @(code) begin
    case(code)
        4'b0000: {seg} = 7'b1000000;
        4'b0001: {seg} = 7'b1111001;
        4'b0010: {seg} = 7'b0100100;
        4'b0011: {seg} = 7'b0110000;
        4'b0100: {seg} = 7'b0011001;
        4'b0101: {seg} = 7'b0010010;
        4'b0110: {seg} = 7'b0000010;
        4'b0111: {seg} = 7'b1111000;
        4'b1000: {seg} = 7'b0000000;
        4'b1001: {seg} = 7'b0011000;
        4'b1010: {seg} = 7'b0001000;
        4'b1011: {seg} = 7'b0000011;
        4'b1100: {seg} = 7'b1000110;
        4'b1101: {seg} = 7'b0100001;
        4'b1110: {seg} = 7'b0000110;
        4'b1111: {seg} = 7'b0001110;
        default: {seg} = 7'b1000000;
    endcase
end
endmodule
