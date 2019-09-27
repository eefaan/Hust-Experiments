`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/09/19 09:25:44
// Design Name:
// Module Name: FSM
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


module FSM(
    input clk_N,
    input rst,
    input pause_con,
    input mode_change,
    input weight_change,

    output reg light_power,//to be remove
    output reg light_running,
    output reg light_xi,
    output reg light_piao,
    output reg light_tuo,
    output reg light_in,
    output reg light_out,
    output reg light_buzzer,

    output reg [2:0]status_mode,//0~5
    output reg [1:0]status_weight,//0~3
    output reg [31:0]display_out
    );

    parameter START      = 4'b0000;
    parameter XI_1_IN    = 4'b0001, XI_2_WASH  = 4'b0010;
    parameter PIAO_1_OUT = 4'b0011, PIAO_2_DRY = 4'b0100, PIAO_3_IN = 4'b0101, PIAO_4_RI = 4'b0110;
    parameter TUO_1_OUT  = 4'b0111, TUO_2_DRY  = 4'b1000;
    parameter FINISH     = 4'b1001, SHUT_DOWN  = 4'b1010, PAUSE     = 4'b1011;

    reg [3:0] pre,state, state, next_state;

    //ini
    initial begin
        light_running = 0;
        light_xi = 0;
        light_piao = 0;
        light_tuo = 0;
        light_in = 0;
        light_out = 0;
        light_buzzer = 0;

        status_mode = 0;
        status_weight = 0;
    end

    //switch mode
    always @(posedge mode_change) begin
        status_mode = status_mode + 1;
        if (status_mode == 3'b110) status_mode = 0;
    end

    //switch weight
    always @((!state) and posedge weight_change) begin
        status_weight = status_weight + 1;
    end

    //pause
    always @(posedge pause_con) begin
        light_running = ~light_running;
    end

    //switch FSM mode
    always @(posedge clk_N) begin
        if(rst==1'b1)
            state <= START;
        else
            state <= next_state;
    end

    always @(*) begin
        case(state)
            START: begin
                //start
                if(status_mode==3'b000 or status_mode==3'b001 or status_mode==3'b010) next_state = XI_1_IN;
                else if(status_mode==3'b011 or status_mode==3'b100) next_state = PIAO_1_OUT;
                else if(status_mode==3'b101) next_state = TUO_1_OUT;
                else next_state = START;
                // start_light my_start_light(status_mode,light_xi,light_piao,light_tuo);
            end

            XI_1_IN: begin
                // light
                // time(status_mode,)
                next_state = XI_2_WASH;
            end

            XI_2_WASH: begin
                // light
                // time
                next_state = PIAO_1_OUT;
            end

            PIAO_1_OUT: begin
                // light
                // time
                next_state = PIAO_2_DRY;
            end

            PIAO_2_DRY: begin
                // light
                // time
                next_state = PIAO_3_IN;
            end

            PIAO_3_IN: begin
                // light
                // time
                next_state = PIAO_4_RI;
            end

            PIAO_4_RI: begin
                //light
                //time
                next_state = TUO_1_OUT;
            end

            TUO_1_OUT: begin
                next_state = TUO_2_DRY;
            end

            TUO_2_DRY: begin
                next_state = FINISH;
            end

            FINISH: begin
                next_state = SHUT_DOWN;
            end

            SHUT_DOWN:begin
                next_state = START;
            end

            default: next_state = START;
        endcase
    end
endmodule
