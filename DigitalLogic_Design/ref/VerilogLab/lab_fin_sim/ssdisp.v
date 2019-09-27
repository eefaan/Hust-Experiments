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
    input [3:0]state,
    input [2:0]status_mode,
    input [1:0]status_weight,
    input [3:0]timer_set,
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
    bin_to_BCD my_surplus_all(surplus_all,OUT_H_a,OUT_T_a,OUT_O_a);
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
        case(state)
            4'b0000:begin//start
                //11 //14 //6
                if(status_mode==0) begin//xi_piao_tuo
                    if(status_weight==0)begin surplus_curr = 11; surplus_all = 11+14+6; end
                    else if(status_weight==1)begin surplus_curr = 12; surplus_all = 12+15+6; end
                    else if(status_weight==2)begin surplus_curr = 13; surplus_all = 13+16+6; end
                    else begin surplus_curr = 14; surplus_all = 14+17+6; end
                end

                else if(status_mode==1) begin//xi
                    if(status_weight==0)begin surplus_curr = 11; surplus_all = 11; end
                    else if(status_weight==1)begin surplus_curr = 12; surplus_all = 12; end
                    else if(status_weight==2)begin surplus_curr = 13; surplus_all = 13; end
                    else begin surplus_curr = 14; surplus_all = 14; end
                end

                else if(status_mode==2) begin//xi_piao
                    if(status_weight==0)begin surplus_curr = 11; surplus_all = 11+14; end
                    else if(status_weight==1)begin surplus_curr = 12; surplus_all = 12+15; end
                    else if(status_weight==2)begin surplus_curr = 13; surplus_all = 13+16; end
                    else begin surplus_curr = 14; surplus_all = 14+17; end
                end

                else if(status_mode==3) begin//piao
                    if(status_weight==0)begin surplus_curr = 8'he; surplus_all = 14; end
                    else if(status_weight==1)begin surplus_curr = 15; surplus_all = 15; end
                    else if(status_weight==2)begin surplus_curr = 16; surplus_all = 16; end
                    else begin surplus_curr = 17; surplus_all = 17; end
                end

                else if(status_mode==4) begin//piao_tuo
                    if(status_weight==0)begin surplus_curr = 8'he; surplus_all = 14+6; end
                    else if(status_weight==1)begin surplus_curr = 15; surplus_all = 15+6; end
                    else if(status_weight==2)begin surplus_curr = 16; surplus_all = 16+6; end
                    else begin surplus_curr = 17; surplus_all = 17+6; end
                end

                else if(status_mode==5) begin//tuo
                    surplus_curr = 6;
                    surplus_all = 6;
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            4'b0001:begin//xi_1
                if(status_mode==0) begin//xi_piao_tuo
                    surplus_curr = timer_set+9;
                    surplus_all = timer_set+9+14+6;
                end

                else if(status_mode==1) begin//xi
                    surplus_curr = timer_set+9;
                    surplus_all = timer_set+9;
                end

                else if(status_mode==2) begin//xi_piao
                    surplus_curr = timer_set+9;
                    surplus_all = timer_set+9+14;
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            4'b0010:begin//xi_2
                if(status_mode==0) begin//xi_piao_tuo
                   surplus_curr = timer_set;
                    surplus_all = timer_set+14+6;
                end

                else if(status_mode==1) begin//xi
                    surplus_curr = timer_set;
                    surplus_all = timer_set;
                end

                else if(status_mode==2) begin//xi_piao
                    surplus_curr = timer_set;
                    surplus_all = timer_set+14;
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            4'b0011:begin//piao_1
                if(status_mode==0 || status_mode==4) begin//xi_piao_tuo //piao_tuo
                    if(status_weight==0)begin surplus_curr = timer_set+11; surplus_all = timer_set+11+6; end
                    else if(status_weight==1)begin surplus_curr = timer_set+12; surplus_all = timer_set+12+6; end
                    else if(status_weight==2)begin surplus_curr = timer_set+13; surplus_all = timer_set+13+6; end
                    else begin surplus_curr = timer_set+14; surplus_all = timer_set+14+6; end
                end

                else if(status_mode==2 || status_mode==3) begin//xi_piao //piao
                    if(status_weight==0)begin surplus_curr = timer_set+11; surplus_all = timer_set+11; end
                    else if(status_weight==1)begin surplus_curr = timer_set+12; surplus_all = timer_set+12; end
                    else if(status_weight==2)begin surplus_curr = timer_set+13; surplus_all = timer_set+13; end
                    else begin surplus_curr = timer_set+14; surplus_all = timer_set+14; end
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            4'b0100:begin//piao_2
                if(status_mode==0 || status_mode==4) begin//xi_piao_tuo //piao_tuo
                    if(status_weight==0)begin surplus_curr = timer_set+8; surplus_all = timer_set+8+6; end
                    else if(status_weight==1)begin surplus_curr = timer_set+9; surplus_all = timer_set+9+6; end
                    else if(status_weight==2)begin surplus_curr = timer_set+10; surplus_all = timer_set+10+6; end
                    else begin surplus_curr = timer_set+11; surplus_all = timer_set+11+6; end
                end

                else if(status_mode==2 || status_mode==3) begin//xi_piao //piao
                    if(status_weight==0)begin surplus_curr = timer_set+8; surplus_all = timer_set+8; end
                    else if(status_weight==1)begin surplus_curr = timer_set+9; surplus_all = timer_set+9; end
                    else if(status_weight==2)begin surplus_curr = timer_set+10; surplus_all = timer_set+10; end
                    else begin surplus_curr = timer_set+11; surplus_all = timer_set+11; end
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            4'b0101:begin//piao_3
                if(status_mode==0 || status_mode==4) begin//xi_piao_tuo //piao_tuo
                    surplus_curr = timer_set+6;
                    surplus_all = timer_set+6+6;
                end

                else if(status_mode==2 || status_mode==3) begin//xi_piao //piao
                    surplus_curr = timer_set+6;
                    surplus_all = timer_set+6;
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            4'b0110:begin//piao_4
                if(status_mode==0 || status_mode==4) begin//xi_piao_tuo //piao_tuo
                    surplus_curr = timer_set;
                    surplus_all = timer_set+6;
                end

                else if(status_mode==2 || status_mode==3) begin//xi_piao //piao
                    surplus_curr = timer_set;
                    surplus_all = timer_set;
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            4'b0111:begin//tuo_1
                if(status_mode==0) begin//xi_piao_tuo
                    surplus_curr = timer_set+3;
                    surplus_all = timer_set+3;
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            4'b1000:begin//tuo_2
                if(status_mode==0) begin//xi_piao_tuo
                    surplus_curr = timer_set;
                    surplus_all = timer_set;
                end

                else begin
                    surplus_curr=0;
                    surplus_all=0;
                end
            end

            // 4'b1001:begin//finish
            //
            // end
            //
            // 4'b1010:begin//shut_down
            //
            // end
            //
            // 4'b1011:begin//pause
            //
            // end

            default:begin
                surplus_all=surplus_all;
                surplus_curr=surplus_curr;
            end
        endcase
    end

endmodule
