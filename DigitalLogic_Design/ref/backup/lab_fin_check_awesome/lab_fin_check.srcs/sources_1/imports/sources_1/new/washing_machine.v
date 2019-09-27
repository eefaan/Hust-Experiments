module washing_machine(
    input rst,//turn on/off
    input pause_con,//pause/continue
    input mode_change,//mode change
    input weight_change,//weight change
    input clk,

    //light
    output light_power,//power
    output light_running,//sign of start

    output light_xi_p,
    output light_piao_p,
    output light_tuo_p,
    output light_in,
    output light_out,
    output light_xi,
    output light_piao,
    output light_tuo,
    output light_buzzer,

    //display
    output [6:0] seg,
    output [7:0] an
    );

    wire [3:0]state;

    wire shut;
    wire clk_N;
    wire clk_F;//flush display
    wire clk_S;//second clock

    // assign temp=clk_N;

    wire power_out;
    wire [31:0]display_out;

    wire [2:0]status_mode;//change between six modes
    wire [1:0]status_weight;//change between four kinds of weight

    //div
    divider clk_div(clk,clk_N,clk_F,clk_S);

    //FSM
    FSM my_machine_fsm(clk_N,clk_S,rst,pause_con,mode_change,weight_change,
      light_running,power_out,shut,status_mode,status_weight,
      display_out,state);

    //display
    display my_disp(rst,shut,display_out,clk_F,seg,an);
    light_control my_light(rst,shut,clk_S,state,status_mode,
      pause_con,mode_change,weight_change,power_out,
      light_xi_p,light_piao_p,light_tuo_p,
      light_in,light_out,light_xi,light_piao,light_tuo,
      light_buzzer,light_power);

endmodule
