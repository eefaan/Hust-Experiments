`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/19 20:45:00
// Design Name:
// Module Name: rom_sim
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


module rom_sim(

    );

    parameter file_name = "C:\\2_19.hex";
    reg clk;
    reg [31:0]addr;
    wire [31:0]data;
    ROM #(.ROM_DATA(file_name)) TB_ROM(
        .clk(clk),
        .addr(addr),
        .data(data)
    );

    initial begin
        // data_in initial here
        clk=1'b0;
        addr=0;

        #45 addr=32'h00000004;
        #45 addr=32'h00000008;

    end

    always@(*)begin
        #20 clk<=~clk;
    end


endmodule
