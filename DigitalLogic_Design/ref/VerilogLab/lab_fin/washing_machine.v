module washing_machine(
    input rst,//turn on/off
    input pause_con,//pause/continue
    input mode_change,//mode change
    input weight_change,//weight change
    input clk,

    //light
    output light_power,//power
    output light_running,//sign of start
    output light_xi,
    output light_piao,
    output light_tuo,
    output light_in,
    output light_out,
    output light_buzzer,

    //display
    output [6:0] seg,
    output [7:0] an
    );

    wire clk_N;
    wire clk_F;//flush display

    wire [31:0]display_out;
    wire [2:0]status_mode;//change between six modes
    wire [1:0]status_weight;//change between three kinds of weight

    divider clk_div(clk,clk_N,clk_F);
    FSM my_machine_fsm(clk_N,rst,pause_con,mode_change,weight_change,
      light_power,light_running,light_xi,light_piao,light_tuo,
      light_in,light_out,light_buzzer,
      status_mode,status_weight,
      display_out);


    //display
    wire [2:0]num;
    wire [3:0]data;
    sum_rom my_sum(num,display_out,data);//choose data, data = part of display_out
    counter my_coun(clk_F,num);//num 0->7->0->...
    decoder3_8 my_3_8(num,an);//choose the lighting seven_seg
    sevenseg_decoder my_seven(data,seg);//show data with seven_seg

endmodule
