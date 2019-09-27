`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/19 10:40:48
// Design Name:
// Module Name: cpu28
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


module cpu28(
    input rst,//reset cpu
    input clk,//sys clock
    input go,//go button
    input [1:0] display_code,//2'b00 for leddata
                            //2'b01 for all cycle count
                            //2'b10 for con/no_con branch count
                            //2'b11 for ram watch
    input [3:0]watch_addr,//ram watching addr
    input f_sw,//swicht f
    //display 7seg
    output [6:0] seg,
    output [7:0] an
    );

    wire clk_N;//work clock
    wire clk_F;//flush display
    wire clk_S;//second clock
    wire[31:0]led_data;
    wire[15:0]all_num;
    wire[15:0]no_conditional_branch_num;
    wire[15:0]conditional_branch_num;
    wire[31:0]ram_data_out;
    wire shut;

    // display
    reg [31:0]display_out;
    always@(*)begin
        case(display_code)
            2'b00:display_out = led_data;
            2'b01:display_out = {{16{1'b0}},all_num};
            2'b10:display_out = {no_conditional_branch_num,conditional_branch_num};
            //TODO: watch ram
            2'b11:display_out = ram_data_out;
            default: display_out = 32'hffffffff;
        endcase
    end


    //div
    divider #(3000000) clk_div(clk,f_sw,clk_N,clk_F,clk_S);

    //display
    assign shut=0;
    display my_disp(rst,shut,display_out,clk_F,seg,an);

    //datapath
    wire watch;
    assign watch = display_code[0] & display_code[1];
    datapath my_datapath(
        .rst(rst),
        .clk(clk_N),
        .go(go),
        .watch(watch),
        .watch_addr_4(watch_addr),
        .led_data(led_data),
        .all_num(all_num),
        .no_conditional_branch_num(no_conditional_branch_num),
        .conditional_branch_num(conditional_branch_num),
        .dm_out(ram_data_out)
    );

endmodule
