//��test bench�ļ��ǻ���washing_machine.v�޸ĵõ���
//��Ҫ��washing_machine����ģ����з�����ԡ��۲첨��ͼʱ����washing_machineģ��disable�����ô�ģ�鼴��
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
    //washing_machine�е�����
    reg rst,pause_con,mode_change,weight_change,clk;
    //ģ��Ĺ���ʱ������ʱ��
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

        //START״̬���л�һ��ϴ��ģʽ
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

        //�л���������
        #10 weight_change=1'b1;
        #10 weight_change=1'b0;

        //��ʼϴ��
        #10 pause_con=1'b1;
        #10 pause_con=1'b0;

        //����״̬���л���������
        #10 weight_change=1'b1;
        #10 weight_change=1'b0;

        //��ͣϴ��
        #20
        #10 pause_con=1'b1;
        #10 pause_con=1'b0;

        //�����л�ϴ��ģʽ
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;

        //����ϴ��
        #10 pause_con=1'b1;
        #10 pause_con=1'b0;

        // //����10���ڰ���
        // #20000 pause_con=1'b1;
        // #10 pause_con=1'b0;
        //
        // //�ٴ�����
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

    //ԭ�ȵķ�Ƶ������ʹ��
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
