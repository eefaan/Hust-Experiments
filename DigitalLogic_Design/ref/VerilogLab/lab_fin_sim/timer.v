module timer(
    input [3:0]state,
    input [1:0]status_weight,
    input light_running,
    input clk,
    output reg timer_out,
    output reg [3:0]timer_set,
    output reg [7:0]water_line
    );

    reg [3:0]state_pre;
    reg [3:0]state_next;
    reg [3:0]timer_ini;

    initial begin
        state_pre=0;
        state_next=0;
        timer_ini=0;

        timer_set=0;
        timer_out=0;
        water_line=0;
    end

    always @ (posedge clk) begin
        if(light_running) begin
            if(state_next!=state_pre)begin
                state_pre=state_next;
                timer_set=timer_ini;
            end
            if(timer_set >= 1) timer_set = timer_set - 1;
            if(timer_set == 1) timer_out = 1'b1;
            else timer_out = 1'b0;
            if(state==4'b0001 || state==4'b0101) water_line = water_line + 1;
            else if(state==4'b0011 || state==4'b0111) water_line = water_line - 1;
        end
    end

    // set_time
    always @ (state) begin
        state_next=state;
        if(light_running) begin
            //XI_1_IN || PIAO_3_IN
            if(state==4'b0001 || state==4'b0101) timer_ini=status_weight+3;

            //XI_2_WASH
            else if(state==4'b0010)timer_ini=10;

            //PIAO_1_OUT || TUO_1_OUT
            else if(state==4'b0011 || state==4'b0111) begin
                if(status_weight==2'b00)timer_ini=3;
                else if(status_weight==2'b01)timer_ini=4;
                else if(status_weight==2'b10)timer_ini=5;
                else if(status_weight==2'b11)timer_ini=6;
                else timer_ini=0;
            end

            //PIAO_2_DRY || TUO_2_DRY
            else if(state==4'b0100 || state==4'b1000)timer_ini=4;

            //PIAO_4_RI
            else if(state==4'b0110)timer_ini=7;

            else timer_ini=0;

        end
    end

endmodule
