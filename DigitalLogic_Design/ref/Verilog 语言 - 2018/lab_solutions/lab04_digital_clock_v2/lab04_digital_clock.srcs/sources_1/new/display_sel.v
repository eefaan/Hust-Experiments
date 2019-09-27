`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/12 10:55:08
// Design Name: 
// Module Name: display_sel
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


module display_sel(num, dig0, dig1, dig2, dig3, dig4, dig5, dig6, dig7, code);
    input   [2: 0]    num;       // 数码管编号：0~7
    input   [3:0]     dig0;
    input   [3:0]     dig1;
    input   [3:0]     dig2;
    input   [3:0]     dig3;
    input   [3:0]     dig4;
    input   [3:0]     dig5;
    input   [3:0]     dig6;
    input   [3:0]     dig7;
    output reg [3:0]  code;       // 7段数码管片选信号，低电平有效

    always @* begin
        case(num)
            3'd0: code = dig0;
            3'd1: code = dig1;
            3'd2: code = dig2;
            3'd3: code = dig3;
            3'd4: code = dig4;
            3'd5: code = dig5;
            3'd6: code = dig6;
            3'd7: code = dig7;
            default: code = dig0;
        endcase
    end

endmodule
