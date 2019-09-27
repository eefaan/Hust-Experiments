`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/14 08:54:42
// Design Name: 
// Module Name: digital_clock_tb
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


module digital_clock_tb( );
    reg         clk;
    reg         reset;
    reg         start, stop, ss, sm, sh, usel;
    wire        led, tt, sl, ml, hl;
    wire [7:0]  an;
    wire [7:0]  seg;

    digital_clock DUT(
        .clk100MHZ(clk),
        .rst_n(reset),
        .start(start),
        .stop(stop),
        .set_second(ss),
        .set_minute(sm),
        .set_hour(sh),
        .up_sel(usel),
        .led(led),
        .time_tick(tt),
        .second_led(sl),
        .minute_led(ml),
        .hour_led(hl),
        .AN(an),
        .SEG_N(seg)
    );
    
    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk;
    end
    
    initial begin
        reset = 1'b0;
        start = 1'b0;
        stop = 1'b0;
        ss = 1'b0;
        sm = 1'b0;
        sh = 1'b0;
        usel = 1'b0;
        #50 reset = 1'b1;
        #50 start = 1'b1;
        #500 stop = 1'b1;
        #100 stop = 1'b0;
    end
  
endmodule
