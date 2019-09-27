`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/09/26 08:35:13
// Design Name:
// Module Name: light_control
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


module light_control(
    input rst,
    input clk_N,
    input [3:0]state,
    input [2:0]status_mode,
    output reg light_xi_p,
    output reg light_piao_p,
    output reg light_tuo_p,

    output reg light_in,
    output reg light_out,
    output reg light_xi,
    output reg light_piao,
    output reg light_tuo,

    output reg light_buzzer
    );

    reg [1:0]cir;//0->5->0
    always @(posedge clk_N) cir=cir+1;

    always @(*) begin
    if(!rst)begin
        case(state)
            //start
            4'b0000:begin
                light_in=0;
                light_out=0;
                light_xi=0;
                light_piao=0;
                light_tuo=0;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=1;
                    light_piao_p=1;
                    light_tuo_p=1;
                end
                //xi
                else if(status_mode==3'b010)begin
                    light_xi_p=1;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
                //xi_piao
                else if(status_mode==3'b011)begin
                    light_xi_p=1;
                    light_piao_p=1;
                    light_tuo_p=0;
                end
                //piao
                else if(status_mode==3'b100)begin
                    light_xi_p=0;
                    light_piao_p=1;
                    light_tuo_p=0;
                end
                //piao_tuo
                else if(status_mode==3'b101)begin
                    light_xi_p=0;
                    light_piao_p=1;
                    light_tuo_p=1;
                end
                //tuo
                else if(status_mode==3'b110)begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=1;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //xi_1
            4'b0001:begin
                light_in=1;
                light_out=0;
                light_xi=0;
                light_piao=0;
                light_tuo=0;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=1&clk_N;
                    light_piao_p=1;
                    light_tuo_p=1;
                end
                //xi
                else if(status_mode==3'b010)begin
                    light_xi_p=1&clk_N;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
                //xi_piao
                else if(status_mode==3'b011)begin
                    light_xi_p=1&clk_N;
                    light_piao_p=1;
                    light_tuo_p=0;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //xi_2
            4'b0010:begin
                light_in=0;
                light_out=0;
                light_xi=1;
                light_piao=0;
                light_tuo=0;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=1&clk_N;
                    light_piao_p=1;
                    light_tuo_p=1;
                end
                //xi
                else if(status_mode==3'b010)begin
                    light_xi_p=1&clk_N;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
                //xi_piao
                else if(status_mode==3'b011)begin
                    light_xi_p=1&clk_N;
                    light_piao_p=1;
                    light_tuo_p=0;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //piao_1
            4'b0011:begin
                light_in=0;
                light_out=1;
                light_xi=0;
                light_piao=0;
                light_tuo=0;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=1;
                end
                //xi_piao
                else if(status_mode==3'b011)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=0;
                end
                //piao
                else if(status_mode==3'b100)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=0;
                end
                //piao_tuo
                else if(status_mode==3'b101)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=1;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //piao_2
            4'b0100:begin
                light_in=0;
                light_out=0;
                light_xi=0;
                light_piao=0;
                light_tuo=1;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=1;
                end
                //xi_piao
                else if(status_mode==3'b011)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=0;
                end
                //piao
                else if(status_mode==3'b100)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=0;
                end
                //piao_tuo
                else if(status_mode==3'b101)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=1;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //piao_3
            4'b0101:begin
                light_in=1;
                light_out=0;
                light_xi=0;
                light_piao=0;
                light_tuo=0;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=1;
                end
                //xi_piao
                else if(status_mode==3'b011)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=0;
                end
                //piao
                else if(status_mode==3'b100)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=0;
                end
                //piao_tuo
                else if(status_mode==3'b101)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=1;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //piao_4
            4'b0110:begin
                light_in=0;
                light_out=0;
                light_xi=0;
                light_piao=1;
                light_tuo=0;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=1;
                end
                //xi_piao
                else if(status_mode==3'b011)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=0;
                end
                //piao
                else if(status_mode==3'b100)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=0;
                end
                //piao_tuo
                else if(status_mode==3'b101)begin
                    light_xi_p=0;
                    light_piao_p=1&clk_N;
                    light_tuo_p=1;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //tuo_1
            4'b0111:begin
                light_in=0;
                light_out=1;
                light_xi=0;
                light_piao=0;
                light_tuo=0;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=1&clk_N;
                end
                //piao_tuo
                else if(status_mode==3'b101)begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=1&clk_N;
                end
                //tuo
                else if(status_mode==3'b110)begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=1&clk_N;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //tuo_2
            4'b1000:begin
                light_in=0;
                light_out=0;
                light_xi=0;
                light_piao=0;
                light_tuo=1;
                light_buzzer=0;
                //xi_piao_tuo
                if(status_mode==3'b001)begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=1&clk_N;
                end
                //piao_tuo
                else if(status_mode==3'b101)begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=1&clk_N;
                end
                //tuo
                else if(status_mode==3'b110)begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=1&clk_N;
                end
                else begin
                    light_xi_p=0;
                    light_piao_p=0;
                    light_tuo_p=0;
                end
            end

            //Finish
            4'b1001:begin
                light_in=0;
                light_out=0;
                light_xi=0;
                light_piao=0;
                light_tuo=0;
                light_xi_p=0;
                light_piao_p=0;
                light_tuo_p=0;
                if(cir>0)light_buzzer=1&clk_N;
                else light_buzzer=0;
            end

            default:begin
                light_in=0;
                light_out=0;
                light_xi=0;
                light_piao=0;
                light_tuo=0;
                light_xi_p=0;
                light_piao_p=0;
                light_tuo_p=0;
                light_buzzer=0;
            end
        endcase
    end
    else begin
        light_in=0;
        light_out=0;
        light_xi=0;
        light_piao=0;
        light_tuo=0;
        light_xi_p=0;
        light_piao_p=0;
        light_tuo_p=0;
        light_buzzer=0;
    end
    end

endmodule
