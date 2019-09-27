module washing_machine_sim(
//    input rst,//turn on/off
//    input pause_con,//pause/continue
//    input mode_change,//mode change
//    input weight_change,//weight change
//    input clk,

    //light
    output light_power,//power
    output light_running,//sign of start
    output light_xi,
    output light_piao,
    output light_tuo,
    output light_in,
    output light_out,
    output light_buzzer,
    // output [3:0]state,

    //display
    output [6:0] seg,
    output [7:0] an
    );
    reg rst,pause_con,mode_change,weight_change,clk,clk_N,clk_F;

    wire [3:0]state;
    initial begin
        clk=0;
        clk_N=0;
        clk_F=0;
        rst=0;
        pause_con=0;
        mode_change=0;
        weight_change=0;

        #17 mode_change=1'b1;
        #20 mode_change=1'b0;
        #20 mode_change=1'b1;
        #20 mode_change=1'b0;
        #20 mode_change=1'b1;
        #20 mode_change=1'b0;
        #20 mode_change=1'b1;
        #20 mode_change=1'b0;
        #20 mode_change=1'b1;
        #20 mode_change=1'b0;
        #20 mode_change=1'b1;
        #20 mode_change=1'b0;
        #20 mode_change=1'b1;
        #20 mode_change=1'b0;

        #20 weight_change=1'b1;
        #20 weight_change=1'b0;

        #10 pause_con=1'b1;
        #10 pause_con=1'b0;
    end

    always @(*) begin
        #21  clk_N <= ~clk_N;
        #21  clk_N <= ~clk_N;
    end

    always @(*) begin
        #4  clk_F <= ~clk_F;
        #4  clk_F <= ~clk_F;
    end

    always @(*) begin
        #1  clk <= ~clk;
        #1  clk <= ~clk;
    end

    wire [31:0]display_out;
    wire [2:0]status_mode;//change between six modes
    wire [1:0]status_weight;//change between three kinds of weight

    wire [2:0]num;
    wire [3:0]data;



    //divider clk_div(clk,clk_N,clk_F);
    FSM my_machine_fsm(clk,clk_N,rst,pause_con,mode_change,weight_change,
      light_power,light_running,light_xi,light_piao,light_tuo,
      light_in,light_out,light_buzzer,
      status_mode,status_weight,
      display_out,state);


    //display
    sum_rom my_sum(num,display_out,data);//choose data, data = part of display_out
    counter my_coun(clk_F,num);//num 0->7->0->...
    decoder3_8 my_3_8(num,an);//choose the lighting seven_seg
    sevenseg_decoder my_seven(data,seg);//show data with seven_seg

endmodule
