`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/07 17:32:20
// Design Name: 
// Module Name: lab3_4
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


module pipe3b(
    input sig_nsyn,
    input clk,
    output q1,
    output q2,
    output sig_syn
    );
//    wire clk_N;
//    divider my_divider(clk,clk_N);
    reg q1;
    reg q2;
    reg sig_syn;
    always@(posedge clk) begin 
        sig_syn=q2;  
        q2=q1;
        q1=sig_nsyn;  
    end

endmodule

