`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/09/27 10:44:31
// Design Name:
// Module Name: FSM_sim
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


module FSM_sim(

    );
    //FSM�е�����
    reg rst,pause_con,mode_change,weight_change;
    //ģ��Ĺ���ʱ������ʱ��
    reg clk_N,clk_S;

    wire light_running;//the sign of running
    wire power_out;//will be changed with posedge of pause button
    wire shut;//affect when finish
    wire [2:0]status_mode;//change between six modes
    wire [1:0]status_weight;//change between four kinds of weight
    wire [31:0]display_out;//drive seven_seg
    wire [3:0]state;//state of FSM

    initial begin
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

        //����״̬�³����л�����������ϴ��ģʽ
        #10 weight_change=1'b1;
        #10 weight_change=1'b0;
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;

        //��ͣϴ��
        #40 pause_con=1'b1;
        #10 pause_con=1'b0;

        //��ͣ״̬�³����л�����������ϴ��ģʽ
        #10 weight_change=1'b1;
        #10 weight_change=1'b0;
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;

        //����ϴ��
        #10 pause_con=1'b1;
        #10 pause_con=1'b0;

        //����10���ڰ���
        #20000 pause_con=1'b1;
        #10 pause_con=1'b0;

        //�л�ϴ��ģʽ����������
        #100 weight_change=1'b1;
        #10 weight_change=1'b0;
        #10 mode_change=1'b1;
        #10 mode_change=1'b0;

        //�ٴ�����
        #100 pause_con=1'b1;
        #10 pause_con=1'b0;

        //�ػ�������
        #20000 rst=1'b1;
        #10 rst=1'b0;

        //�л�ϴ��ģʽΪ����
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

        //�л���������Ϊ4kg
        #10 weight_change=1'b1;
        #10 weight_change=1'b0;
        #10 weight_change=1'b1;
        #10 weight_change=1'b0;

        //�ٴ��������ˮλ�仯
        #10 pause_con=1'b1;
        #10 pause_con=1'b0;

    end

    always @(*) begin
        #21  clk_S <= ~clk_S;
        #21  clk_S <= ~clk_S;
    end

    always @(*) begin
        #4  clk_N <= ~clk_N;
        #4  clk_N <= ~clk_N;
    end

    //FSM is called here
    FSM my_machine_fsm(clk_N,clk_S,rst,pause_con,mode_change,weight_change,
      light_running,power_out,shut,status_mode,status_weight,
      display_out,state);

endmodule
