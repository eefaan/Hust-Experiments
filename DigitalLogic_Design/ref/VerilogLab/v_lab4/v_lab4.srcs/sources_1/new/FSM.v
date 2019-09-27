`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/08 12:31:39
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
    input           clk,
    input           rst,
    input           start,
    input           next_zero,
    output reg      a_sel,
    output reg      ld_sum,
    output reg      sum_sel,
    output reg      ld_next,
    output reg      next_sel,
    output reg      done
);

    parameter START = 2'b00, COMPUTE_SUM = 2'b01, GET_NEXT = 2'b10, DONE = 2'b11;
    
    reg [1:0] state, next_state;
    
    always @(posedge clk) begin
        if(rst==1'b1)
            state <= START;
        else
            state <= next_state;
    end
    
    always @(*) begin
        case(state)
            START:  begin
                ld_sum   = 1'b0;
                ld_next  = 1'b0;
                sum_sel  = 1'b0;
                next_sel = 1'b0;
                a_sel    = 1'b0;
                done     = 1'b0;
                if(start==1'b1)
                    next_state = COMPUTE_SUM;
            end
            
            COMPUTE_SUM: begin
                ld_sum   = 1'b1;
                ld_next  = 1'b0;
                sum_sel  = 1'b1;
                next_sel = 1'b1;
                a_sel    = 1'b1;
                done     = 1'b0;
                next_state = GET_NEXT;
            end
            
            GET_NEXT: begin
                ld_sum   = 1'b0;
                ld_next  = 1'b1;
                sum_sel  = 1'b1;
                next_sel = 1'b1;
                a_sel    = 1'b0;
                done     = 1'b0;
                if(next_zero==1'b1)
                    next_state = DONE;
                else
                    next_state = COMPUTE_SUM;
            end
            
            DONE: begin
                ld_sum   = 1'b0;
                ld_next  = 1'b0;
                sum_sel  = 1'b0;
                next_sel = 1'b0;
                a_sel    = 1'b0;
                done     = 1'b1;
                if(start==1'b0)
                    next_state = START;
            end
            
            default: next_state = START;
        endcase
    end
    
endmodule