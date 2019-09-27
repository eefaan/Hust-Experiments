`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/21 09:59:58
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


module display_sel(num, dig, code);
    input   [2: 0]    num;       // 数码管编号：0~7
    input   [31:0]    dig;
    output reg [3:0]  code;       // 7段数码管片选信号，低电平有效

    always @* begin
        case(num)
            3'd0: code = dig[3:0];
            3'd1: code = dig[7:4];
            3'd2: code = dig[11:8];
            3'd3: code = dig[15:12];
            3'd4: code = dig[19:16];
            3'd5: code = dig[23:20];
            3'd6: code = dig[27:24];
            3'd7: code = dig[31:28];
            default: code = 4'h0;
        endcase
    end

endmodule
