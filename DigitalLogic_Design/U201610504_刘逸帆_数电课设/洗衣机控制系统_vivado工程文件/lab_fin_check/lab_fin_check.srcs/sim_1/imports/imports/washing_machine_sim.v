//此test bench文件是基于washing_machine.v修改得到的
//需要对washing_machine顶层模块进行仿真测试、观察波形图时，将washing_machine模块disable并启用此模块即可
module washing_machine_sim(
    // input rst,//turn on/off
    // input pause_con,//pause/continue
    // input mode_change,//mode change button
    // input weight_change,//weight change button
    // input clk,//sys clock

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
    output light_buzzer

    //display
    // output [7:0] an
    // output [6:0] seg,
    );
    //washing_machine中的输入
    reg rst,pause_con,mode_change,weight_change,clk;
    //模拟的工作时钟与秒时钟
    reg clk_N,clk_S;

    wire shut;//affect when finish
    wire power_out;//will be changed with posedge of pause button
    wire [3:0]state;//state of FSM
    wire [2:0]status_mode;//change between six modes
    wire [1:0]status_weight;//change between four kinds of weight
    wire [31:0]display_out;//drive seven_seg

    initial begin
        clk=0;
        clk_N=0;
        clk_S=0;
        rst=0;
        pause_con=0;
        mode_change=0;
        weight_change=0;

        //START状态下切换一轮洗衣模式
        #7 mode_change=1'b1;
        #10 mode_change=1'b0;
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;

        //切换衣物重量
        #10 weight_change=1'b1;
        #10 weight_change=1'b0;

        //开始洗衣
        #10 pause_con=1'b1;
        #10 pause_con=1'b0;

        //运行状态下切换衣物重量
        #10 weight_change=1'b1;
        #10 weight_change=1'b0;

        //暂停洗衣
        #20
        #10 pause_con=1'b1;
        #10 pause_con=1'b0;

        //尝试切换洗衣模式
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;

        //继续洗衣
        #10 pause_con=1'b1;
        #10 pause_con=1'b0;

        // //结束10秒内按键
        // #20000 pause_con=1'b1;
        // #10 pause_con=1'b0;
        //
        // //再次启动
        // #100 pause_con=1'b1;
        // #10 pause_con=1'b0;
    end

    always @(*) begin
        #21  clk_S <= ~clk_S;
        #21  clk_S <= ~clk_S;
    end

    always @(*) begin
        #4  clk_N <= ~clk_N;
        #4  clk_N <= ~clk_N;
    end

    always @(*) begin
        #1  clk <= ~clk;
        #1  clk <= ~clk;
    end

    //原先的分频器不再使用
    // divider clk_div(clk,clk_N,clk_F,clk_S);

    //FSM
    FSM my_machine_fsm(clk_N,clk_S,rst,pause_con,mode_change,weight_change,
      light_running,power_out,shut,status_mode,status_weight,
      display_out,state);

    //display seven_seg and leds
    display my_disp(rst,shut,display_out,clk_F,seg,an);
    light_control my_light(rst,shut,clk_S,state,status_mode,
      pause_con,mode_change,weight_change,power_out,
      light_xi_p,light_piao_p,light_tuo_p,
      light_in,light_out,light_xi,light_piao,light_tuo,
      light_buzzer,light_power);

endmodule
