`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/09/21 09:15:01
// Design Name:
// Module Name: ssdisp
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


module ssdisp(
    input rst,
    input shut,
    input [3:0]state,
    input [2:0]status_mode,
    input [1:0]status_weight,
    input [7:0]timer_set,
    input [7:0]water_line,
    output reg [31:0]display_out
    );

    reg [7:0]surplus_curr;
    reg [7:0]surplus_all;

    initial begin
        display_out = 0;
        surplus_all = 0;
        surplus_curr = 0;
    end

    //ThreeToEight 31-28 27-24   23-20   19-16 15-12   11-8   7-4 3-0
    wire [3:0] OUT_H_c;
    wire [3:0] OUT_T_c;
    wire [3:0] OUT_O_c;

    wire [3:0] OUT_H_a;
    wire [3:0] OUT_T_a;
    wire [3:0] OUT_O_a;

    wire [3:0] OUT_H_w;
    wire [3:0] OUT_T_w;
    wire [3:0] OUT_O_w;

    bin_to_BCD my_surplus_curr(surplus_curr,OUT_H_c,OUT_T_c,OUT_O_c);
    bin_to_BCD my_surplus_all(timer_set,OUT_H_a,OUT_T_a,OUT_O_a);
    bin_to_BCD my_water_line(water_line,OUT_H_w,OUT_T_w,OUT_O_w);

    always @(*) begin
        if(state==0)
            display_out[31:0] = {OUT_T_a[3:0], OUT_O_a[3:0], 4'b0000,
                             OUT_T_c[3:0], OUT_O_c[3:0], 9'b0000,
                             status_mode[2:0]};
        else
            display_out[31:0] = {OUT_T_a[3:0], OUT_O_a[3:0], 4'b0000,
                             OUT_T_c[3:0], OUT_O_c[3:0], 4'b0000,
                             OUT_T_w[3:0], OUT_O_w[3:0]};
    end

    always @(*) begin
        if(!rst)begin
            case(state)
                4'b0000:begin//start
                    //xi_piao_tuo
                    if(status_mode==1) surplus_curr = timer_set - 3*(status_weight+2)-12;
                    //xi
                    else if(status_mode==2) surplus_curr = timer_set;
                    //xi_piao
                    else if(status_mode==3) surplus_curr = timer_set - 2*(status_weight+2)-9;
                    //piao
                    else if(status_mode==4) surplus_curr = timer_set;
                    //piao_tuo
                    else if(status_mode==5) surplus_curr = timer_set - (status_weight+2)-3;
                    //tuo
                    else if(status_mode==6) surplus_curr = timer_set;
                    else surplus_curr = 0;
                end

                //to be changed
                4'b0001,4'b0010:begin//xi_1, xi_2
                    //xi_piao_tuo
                    if(status_mode==1) surplus_curr = timer_set - 3*(status_weight+2)-12;
                    //xi
                    else if(status_mode==2) surplus_curr = timer_set;
                    //xi_piao
                    else if(status_mode==3) surplus_curr = timer_set - 2*(status_weight+2)-9;
                    else surplus_curr = 0;
                end

                4'b0011,4'b0100,4'b0101,4'b0110:begin//piao_1, piao_2, piao_3, piao_4
                    //xi_piao_tuo
                    if(status_mode==1) surplus_curr = timer_set - (status_weight+2)-3;
                    //xi_piao
                    else if(status_mode==3) surplus_curr = timer_set;
                    //piao
                    else if(status_mode==4) surplus_curr = timer_set;
                    //piao_tuo
                    else if(status_mode==5) surplus_curr = timer_set - (status_weight+2)-3;
                    else surplus_curr = 0;
                end

                4'b0111,4'b1000:begin//tuo_1, tuo_2
                    //xi_piao_tuo
                    if(status_mode==1) surplus_curr = timer_set;
                    //piao_tuo
                    else if(status_mode==5) surplus_curr = timer_set;
                    //tuo
                    else if(status_mode==6) surplus_curr = timer_set;
                    else surplus_curr = 0;
                end

                default:begin
                    surplus_curr=0;
                end
            endcase
        end
    end

endmodule
