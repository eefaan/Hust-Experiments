module timer(
    input rst,
    input [3:0]state,
    input [1:0]status_weight,
    input [2:0]status_mode,
    input pause_con,
    input mode_change,
    input power_in,
    input power_out,
    input clk,
    input clk_N,
    output reg next_fin,
    output reg timer_out,
    output reg [13:0]timer_set,
    output reg [13:0]water_line
    );

    reg [13:0]i;
    reg [13:0]fin_timer;

    initial begin
        i=0;
        timer_out=0;
        water_line=0;
    end

    //count
    always @ (posedge clk_N) begin//mode change right now
    // always @ (posedge clk_N or posedge mode_change) begin//mode change right now
        if(!rst)begin
            //set_time
            if(power_in==1'b1 && power_out==1'b0 && state==4'b0000) begin//Start or Pause, will initial the full_timer
                // water_line=0;
                fin_timer = 64*10;
                i=0;
                if(status_mode==3'b001) begin//xi_piao_tuo
                    timer_set = 64*(4*(status_weight+2)+21);
                end
                else if(status_mode==3'b010) begin//xi
                    timer_set = 64*(status_weight+2+9);
                end
                else if(status_mode==3'b011) begin//xi_piao
                    timer_set = 64*(3*(status_weight+2)+18);
                end
                else if(status_mode==3'b100) begin//piao
                    timer_set = 64*(2*(status_weight+2)+9);
                end
                else if(status_mode==3'b101) begin//piao_tuo
                    timer_set = 64*(3*(status_weight+2)+12);
                end
                else if(status_mode==3'b110) begin//tuo
                    timer_set = 64*6;
                end
                else timer_set = 0;
            end


            else if(power_in==1'b1 && power_out==1'b1)begin//wait for the clock
            // else if(light_running==1'b1 && clk_N==1'b1)begin//wait for the clock
                fin_timer = 64*10;
                i=i+1;
                //timer_set--
                if(timer_set > 0) timer_set = timer_set - 1;
                else timer_set = timer_set;

                //create
                if(timer_set == 1) timer_out = 1'b1;
                else timer_out = 1'b0;

                //water_line+-
                // if(state==0) water_line=0;
                // else
                if(state==4'b0001 || state==4'b0101)begin
                    if(water_line<64*20)
                        water_line = water_line + 1;
                end
                else if(state==4'b0011 || state==4'b0111)begin
                    if(water_line>0)
                        water_line = water_line - 1;
                end
                else water_line = water_line;
            end

            else if(power_in==1'b0 && power_out==1'b1) begin//timer in state FINISH
                if(fin_timer>0) fin_timer = fin_timer - 1;
            end

            else fin_timer=64*10;

            //create next_fin
            if(fin_timer==16) next_fin = 1'b1;
            else next_fin = 0;

            //to switch FSM
            case(status_mode)
                //x_p_t
                3'b001:if(i==64*(status_weight+2) || i==64*(status_weight+2+9) ||
                          i==64*(2*(status_weight+2)+9) || i==64*(2*(status_weight+2)+9+3) || i==64*(3*(status_weight+2)+9+3) || i==64*(3*(status_weight+2)+9+3+6) ||
                          i==64*(4*(status_weight+2)+9+3+6) || i==64*(4*(status_weight+2)+9+3+6+3)) timer_out=1;
                       else timer_out=0;
                //x
                3'b010:if(i==64*(status_weight+2) || i==64*(status_weight+2+9)) timer_out=1;
                       else timer_out=0;
                //x_p
                3'b011:if(i==64*(status_weight+2) || i==64*(status_weight+2+9) ||
                          i==64*(2*(status_weight+2)+9) || i==64*(2*(status_weight+2)+9+3) || i==64*(3*(status_weight+2)+9+3) || i==64*(3*(status_weight+2)+9+3+6)) timer_out=1;
                       else timer_out=0;
                //p
                3'b100:if(i==64*(status_weight+2) || i==64*((status_weight+2)+3) || i==64*(2*(status_weight+2)+3) || i==64*(2*(status_weight+2)+3+6)) timer_out=1;
                       else timer_out=0;
                //p_t
                3'b101:if(i==64*(status_weight+2) || i==64*((status_weight+2)+3) || i==64*(2*(status_weight+2)+3) || i==64*(2*(status_weight+2)+3+6) ||
                          i==64*(3*(status_weight+2)+3+6) || i==64*(3*(status_weight+2)+3+6+3)) timer_out=1;
                       else timer_out=0;
                //t
                3'b110:if(i==64*(status_weight+2) || i==64*((status_weight+2)+3)) timer_out=1;
                       else timer_out=0;
                default:timer_out=0;
            endcase

        end
    end
endmodule
