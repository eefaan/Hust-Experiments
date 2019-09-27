`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer: LYF
//
// Create Date: 2019/02/18 19:56:42
// Design Name:
// Module Name: RAM
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


module RAM(
    input rst,// 1 will reset the ram
    input clk,
    input str, // store data enable
    input ld, // load data enable
    input [3:0] sel, // 4bit selectors, 0 disables each component
    input [9:0] addr, // 10bits addr
    input [31:0] data_in, // 32bits data
    output [31:0] data_out // 32bits data
    );

    integer j;
    // ram here
    reg [31:0] state [0:49];

    always@(posedge clk) begin
        // reset
        if(rst) begin
            for (j=0; j<50; j=j+1) begin
                state[j] <= 32'b0; //reset array
            end
        end
        // Store data
        if(str & (~rst)) begin
            if(sel[3]!=0) state[addr][31:24]<=data_in[31:24];
            if(sel[2]!=0) state[addr][23:16]<=data_in[23:16];
            if(sel[1]!=0) state[addr][15:8]<=data_in[15:8];
            if(sel[0]!=0) state[addr][7:0]<=data_in[7:0];
        end
    end

    // Load data
    assign data_out=state[addr];
endmodule
