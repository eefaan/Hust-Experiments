`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/09/26 09:05:43
// Design Name:
// Module Name: fin_timer
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


module fin_timer(
    input power_in,
    input clk_N,
    output next_fin,
    output next_start
    );

    reg [7:0]fin_timer;

    initial begin
        fin_timer=0;
    end

    //count
    always @ (posedge clk_N) begin//mode change right now
        //set ten seconds
        if(power_in==1'b1) fin_timer = 10;

        //timer
        else if(power_in==1'b0) fin_timer = fin_timer - 1;

    end

endmodule
