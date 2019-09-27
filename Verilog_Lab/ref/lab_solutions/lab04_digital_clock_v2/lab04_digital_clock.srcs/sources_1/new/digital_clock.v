`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/12 10:20:47
// Design Name: 
// Module Name: digital_clock
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


module digital_clock(
    input           clk100MHZ,
    input           rst_n,
    input           start,
    input           stop,
    input           set_second,
    input           set_minute,
    input           set_hour,
    input           up_sel,
    //input           down_sel,
    output reg      led,
    output          time_tick,
    output reg      second_led,
    output reg      minute_led,
    output reg      hour_led,
    output [7:0]    AN,
    output [7:0]    SEG_N
);

    wire            clk_1HZ;
    reg  [3:0]      second_cnt1;
    reg  [3:0]      second_cnt2;
    reg  [3:0]      minute_cnt1;
    reg  [3:0]      minute_cnt2;
    reg  [3:0]      hour_cnt1;
    reg  [3:0]      hour_cnt2;
    wire [7:0]      an;
    
    parameter S_reset = 3'b000, S_run = 3'b001, S_stop = 3'b010, S_set = 3'b011, S_second = 3'b100, S_minute = 3'b101, S_hour = 3'b110;
    reg  [2:0]  state;
    
    assign AN = {an[7:6], 1'b1, an[4:3], 1'b1, an[1:0]};
    
    assign time_tick = (start==1'b1)? clk_1HZ : 1'b0;
    
    divider u_1HZ(.clk(clk100MHZ), .clk_N(clk_1HZ));
    //divider #(5000) u_1HZ(.clk(clk100MHZ), .clk_N(clk_1HZ));
    
    dynamic_scan u_dscan (
        .clk100MHZ(clk100MHZ),
        .dig0(second_cnt1),
        .dig1(second_cnt2),
        .dig2(4'hf),
        .dig3(minute_cnt1),
        .dig4(minute_cnt2),
        .dig5(4'hf),
        .dig6(hour_cnt1),
        .dig7(hour_cnt2),
        .SEG(SEG_N),
        .AN(an)
    );
   
/*
    dynamic_scan u_dscan (
        .clk100MHZ(clk100MHZ),
        .dig0(second_cnt[3:0]),
        .dig1(second_cnt[7:4]),
        .dig2(4'hf),
        .dig3(second_cnt[11:8]),
        .dig4(second_cnt[15:12]),
        .dig5(4'hf),
        .dig6(second_cnt[19:16]),
        .dig7(second_cnt[23:20]),
        .SEG(SEG_N),
        .AN(an)
    );
*/    
    always @(posedge clk_1HZ) begin
        if(rst_n==1'b0) begin
            state <= S_reset;
            second_cnt1 <= 4'h0;
            second_cnt2 <= 4'h0;
            minute_cnt1 <= 4'h0;
            minute_cnt2 <= 4'h0;
            hour_cnt1 <= 4'h0;
            hour_cnt2 <= 4'h0;
            led <= 1'b0;
            second_led <= 1'b0;
            minute_led <= 1'b0;
            hour_led <= 1'b0;
        end
        
        else begin
            case(state)
                S_reset: begin
                    if(start==1'b1)
                        state <= S_run;
                end
                
                S_run: begin
                    if(second_cnt1==4'd4) begin
                        led <= 1'b0;
                    end
                        
                    if(second_cnt1==4'd9) begin
                        second_cnt1 <= 4'h0;
                        second_cnt2 <= second_cnt2 + 1;
                    end
                
                    else
                        second_cnt1 <= second_cnt1 + 1;
                
                    if(second_cnt2==4'd5 && second_cnt1==4'd9) begin
                        second_cnt2 <= 4'h0;
                        minute_cnt1 <= minute_cnt1 + 1;
                    end     
                
                    if(minute_cnt1==4'd9 && second_cnt2==4'd5 && second_cnt1==4'd9) begin
                        minute_cnt1 <= 4'h0;
                        minute_cnt2 <= minute_cnt2 + 1;
                    end
                    
                    if(minute_cnt2==4'd5 && minute_cnt1==4'd9 && second_cnt2==4'd5 && second_cnt1==4'd9) begin
                        minute_cnt2 <= 4'h0;
                        hour_cnt1 <= hour_cnt1 + 1;
                        led <= 1'b1;
                    end
                
                    if(hour_cnt1==4'd9 && minute_cnt2==4'd5 && minute_cnt1==4'd9 && second_cnt2==4'd5 && second_cnt1==4'd9) begin
                        hour_cnt1 <= 4'h0;
                        hour_cnt2 <= hour_cnt2 + 1;
                    end
                
                    if(hour_cnt2==4'd2 && hour_cnt1==4'd3 && minute_cnt2==4'd5 && minute_cnt1==4'd9 && second_cnt2==4'd5 && second_cnt1==4'd9) begin
                        hour_cnt1 <= 4'h0;
                        hour_cnt2 <= 4'h0;
                    end
                    
                    if(stop==1'b1)
                        state <= S_stop;
                end
                
                S_stop: begin
                    second_led <= 1'b0;
                    minute_led <= 1'b0;
                    hour_led <= 1'b0;
                            
                    if(stop==1'b0)
                        state <= S_run;
                    else if(set_second==1'b1)
                        state <= S_second;
                    else if(set_minute==1'b1)
                        state <= S_minute;
                    else if(set_hour==1'b1)
                        state <= S_hour;
                    else
                        state <= S_stop;
                end
                
                S_second: begin
                    second_led <= 1'b1;
                    if(set_second==1'b0)
                        state <= S_stop;
                    else if(up_sel==1'b1) begin
                        second_cnt1 <= second_cnt1 + 1;
                    end

                    if(second_cnt1==4'd9) begin
                        second_cnt1 <= 4'h0;
                        second_cnt2 <= second_cnt2 + 1;
                    end
                    
                    if(second_cnt2==4'd5 && second_cnt1==4'd9) begin
                        second_cnt2 <= 4'h0;
                    end
                end
                
                S_minute: begin
                    minute_led <= 1'b1;
                    if(set_minute==1'b0)
                        state <= S_stop;
                    else if(up_sel==1'b1) begin
                        minute_cnt1 <= minute_cnt1 + 1;
                    end

                    if(minute_cnt1==4'd9) begin
                        minute_cnt1 <= 4'h0;
                        minute_cnt2 <= minute_cnt2 + 1;
                    end
                
                    if(minute_cnt2==4'd5 && minute_cnt1==4'd9) begin
                        minute_cnt2 <= 4'h0;
                    end
                end
                
                S_hour: begin
                    hour_led <= 1'b1;
                    if(set_hour==1'b0)
                        state <= S_stop;
                    else if(up_sel==1'b1) begin
                        hour_cnt1 <= hour_cnt1 + 1;
                    end

                    if(hour_cnt1==4'd9) begin
                        hour_cnt1 <= 4'h0;
                        hour_cnt2 <= hour_cnt2 + 1;
                    end
                
                    if(hour_cnt2==4'd2 && hour_cnt1==4'd3) begin
                        hour_cnt1 <= 4'h0;
                        hour_cnt2 <= 4'h0;
                    end       
                end
                
                default: state <= S_run;
            endcase
        end
    end
    
endmodule
