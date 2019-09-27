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
    input clk_N,//working clock
    input rst,
    input pause_con,
    input mode_change,
    input weight_change,

    output light_power,
    output light_running,

    output light_xi_p,
    output light_piao_p,
    output light_tuo_p,
    output light_in,
    output light_out,
    output light_xi,
    output light_piao,
    output light_tuo,
    output light_buzzer,

    output reg shut,//turn off light in state finfish

    output reg [2:0]status_mode,//0~5
    output reg [1:0]status_weight,//0~3
    output [31:0]display_out,
    output reg [3:0]state
    );

    wire light_buzzer_1;
    wire light_buzzer_2=pause_con;
    wire light_buzzer_3=mode_change;
    wire light_buzzer_4=weight_change;

    assign light_power = ~(rst)&(~(state[3]&state[1]&(~state[2])&(~state[0])));
    assign light_buzzer = light_buzzer_1 | light_buzzer_2 | light_buzzer_3 | light_buzzer_4;

    reg power_out;
    reg power_in;
    //{power_in,power_out}
    //10 START
    //11 RUNNING
    //10 PAUSE
    //01 FINISH
    //00 TURN TO START -> 10

    // state of FSM
    parameter START      = 4'b0000;
    parameter XI_1_IN    = 4'b0001, XI_2_WASH  = 4'b0010;
    parameter PIAO_1_OUT = 4'b0011, PIAO_2_DRY = 4'b0100, PIAO_3_IN = 4'b0101, PIAO_4_RI = 4'b0110;
    parameter TUO_1_OUT  = 4'b0111, TUO_2_DRY  = 4'b1000;
    parameter FINISH     = 4'b1001, SHUT_DOWN  = 4'b1010, PAUSE     = 4'b1011;

    // reg [3:0]state;
    reg [3:0]next_state;
    reg [3:0]pre_state;

    wire next_fin;
    wire timer_out;
    wire [7:0]timer_set;
    wire [7:0]water_line;

    // ini when simulation
    initial begin
        power_out = 0;
        power_in = 1;
        status_mode = 1;
        status_weight = 0;
        state = 0;
    end

    light_control my_light(rst,clk_N,state,status_mode,
      light_xi_p,light_piao_p,light_tuo_p,
      light_in,light_out,light_xi,light_piao,light_tuo,
      light_buzzer_1);

    timer my_timer(rst,state,status_weight,status_mode,pause_con,mode_change,
      power_in,power_out,clk,clk_N,next_fin,timer_out,timer_set,water_line);

    ssdisp my_ssdisp(rst,shut,state,status_mode,status_weight,timer_set,
      water_line,display_out);

    and(light_running, power_in, power_out);

    //switch mode
    always @(posedge mode_change or posedge rst) begin
        if(rst)status_mode=3'b001;
        else if(state==0)begin
            status_mode = status_mode + 1;
            if (status_mode == 3'b111) status_mode = 3'b001;
        end
    end
    //switch weight
    always @(posedge weight_change or posedge rst) begin
        if(rst)status_weight=0;
        else if(state==0)begin
            status_weight = status_weight + 1;
        end
    end

    //pause
    always @(posedge pause_con or posedge rst) begin
        if(rst) power_out = 0;
        else power_out = ~power_out;
    end


    always @(posedge clk_N) begin
        if(rst==1'b1)
            state <= START;
        else
            state <= next_state;
    end

    always @(*) begin
        if(!rst)begin
            case(state)
                START: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out)begin
                        if(status_mode==3'b001 || status_mode==3'b010 || status_mode==3'b011) next_state = XI_1_IN;
                        else if(status_mode==3'b100 || status_mode==3'b101) next_state = PIAO_1_OUT;
                        else if(status_mode==3'b110) next_state = TUO_1_OUT;
                        else next_state = START;
                    end
                    else next_state = START;
                end

                XI_1_IN: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out && timer_out) next_state = XI_2_WASH;
                    else next_state = XI_1_IN;
                end

                XI_2_WASH: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out && timer_out) begin
                        if(status_mode==3'b001 || status_mode==3'b011) next_state = PIAO_1_OUT;
                        else if(status_mode==3'b010) next_state = FINISH;
                        else next_state = XI_2_WASH;
                    end
                    else next_state = XI_2_WASH;
                end

                PIAO_1_OUT: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out && timer_out) next_state = PIAO_2_DRY;
                    else next_state = PIAO_1_OUT;
                end

                PIAO_2_DRY: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out && timer_out) next_state = PIAO_3_IN;
                    else next_state = PIAO_2_DRY;
                end

                PIAO_3_IN: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out && timer_out) next_state = PIAO_4_RI;
                    else next_state = PIAO_3_IN;
                end

                PIAO_4_RI: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out && timer_out) begin
                        if(status_mode==3'b001 || status_mode==3'b101) next_state = TUO_1_OUT;
                        else if(status_mode==3'b011 || status_mode==3'b100) next_state = FINISH;
                        else next_state = PIAO_4_RI;
                    end
                    else next_state = PIAO_4_RI;
                end

                TUO_1_OUT: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out && timer_out) next_state = TUO_2_DRY;
                    else next_state = TUO_1_OUT;
                end

                TUO_2_DRY: begin
                    shut = 1'b0;
                    power_in=1'b1;
                    if(power_in && power_out && timer_out) next_state = FINISH;
                    else next_state = TUO_2_DRY;
                end

                FINISH: begin
                    shut = 1'b0;
                    power_in = 1'b0;
                    if(pause_con)// touch
                        next_state = START;
                    else if(next_fin)// ten seconds without control
                        next_state = SHUT_DOWN;
                    else next_state = FINISH;
                end

                SHUT_DOWN:begin
                    shut = 1'b1;
                    power_in = 1'b0;
                    next_state = SHUT_DOWN;
                end

                default: begin
                    shut = 1'b0;
                    power_in = 1'b1;
                    next_state = START;
                end
            endcase
        end
        else begin
            next_state = START;
        end
    end

endmodule
