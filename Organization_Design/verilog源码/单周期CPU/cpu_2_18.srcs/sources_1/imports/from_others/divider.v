`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/19 09:08:10
// Design Name:
// Module Name: divider
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

module divider #(parameter  N = 1250000)(
    input clk,
    input f_sw,
    output reg clk_N,
    output reg clk_F,
    output reg clk_S
);
    reg [31:0]counter;
    reg [31:0]counter_f;
    reg [31:0]counter_s;
    parameter F=20000;
    parameter S=80000000;

    initial begin
        counter <= 0;
        clk_N <= 0;
        counter_f <= 0;
        clk_F <= 0;
        counter_s <= 0;
        clk_S <= 0;
    end

    always @ (posedge clk) begin
        case(f_sw)
            1'b1:clk_N = ~clk_N;
            1'b0:begin
                counter = counter + 1;
                if(counter > N/2)  begin
                    clk_N = ~clk_N;
                    counter = 0;
                end
            end
        endcase
    end

    always @(posedge clk) begin
        counter_f = counter_f + 1;
        if(counter_f > F) begin
            clk_F = ~clk_F;
            counter_f = 0;
        end
    end

    always @(posedge clk) begin
        counter_s = counter_s + 1;
        if(counter_s > S/2) begin
            clk_S = ~clk_S;
            counter_s = 0;
        end
    end

endmodule
