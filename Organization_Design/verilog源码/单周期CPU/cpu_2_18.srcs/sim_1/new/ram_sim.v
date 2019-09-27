`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/18 19:58:10
// Design Name:
// Module Name: ram_sim
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


module ram_sim(

    );

    reg clk;
    reg rst;
    reg str; // store data enable
    reg ld; // load data enable
    reg [3:0] sel; // 1bit selector, 0 disables component
    reg [9:0] addr; // 10bits addr
    reg [31:0] data_in; // 32bits data
    wire [31:0] data_out; // 32bits data

    initial begin
        // data_in initial here
        rst=1'b0;
        sel=4'b1111;
        clk=1'b0;
        str=1'b0;
        ld=1'b0;
        data_in=32'h12345678;
        addr=10'b000000001;

        #5 rst=1'b1;
        #20 rst=1'b0;

        // test store
        #10 str=1'b1;

        // test another addr
        #20 addr=10'b0000000010;

        // test sel
        sel=4'b0010;
        #10 addr=10'b0000000011;

    end

    always@(*)begin
        #10 clk<=~clk;
    end

    // RAM is called here
    RAM myram(rst, clk, str, ld, sel, addr, data_in, data_out);

endmodule
