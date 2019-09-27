`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/21 10:28:46
// Design Name: 
// Module Name: lab_4_5_top_tb
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


module lab_4_5_top_tb( );
    reg         clk;
    reg         rst;
    reg         start;
    wire [7:0]  AN;
    wire [7:0]  SEG_N;
    wire        done;
    
    lab_4_5_top DUT(
        .clk100MHZ(clk),
        .rst(rst),
        .start(start),
        .AN(AN),
        .SEG_N(SEG_N),
        .done(done)
    );
    
    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk;
    end
    
    initial begin
        rst = 1'b1;
        start = 1'b0;
        #50 rst = 1'b0;
        #100 start = 1'b1;
        #1000 start = 1'b0;
    end
    
endmodule
