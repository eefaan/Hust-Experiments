`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/14 03:57:22
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
    input           clk_x,
    input           rst,
    input           num_x,
    output reg      sign,
    output reg      [2:0]state
);
    
    parameter START = 3'b000, NEXT_1 = 3'b001, NEXT_2 = 3'b010, NEXT_3 = 3'b011, END = 3'b100, LIGHT = 3'b101;
    reg [2:0] next_state;
    
    always @(posedge clk_x) begin
        if(rst==1'b1)
            state <= START;
        else
            state <= next_state;
    end
    
    always @(*) begin
        case(state)
            START:  begin
                sign=1'b0;
                if(num_x==1'b1) next_state = NEXT_1; //check first sign '1'
                else next_state = START;
            end
            
            NEXT_1: begin
                sign=1'b0;
                if(num_x==1'b0) next_state = NEXT_2; //check second sign '2'
                else next_state = START;
            end
            
            NEXT_2: begin
                sign=1'b0;
                if(num_x==1'b1) next_state = NEXT_3; //check third sign '1'
                else next_state = START;
            end
            
            NEXT_3: begin
                sign=1'b0;
                if(num_x==1'b1) next_state = END; //check fourth sign '1'
                else next_state = START;
            end
            
            END: begin
                sign=1'b0;
                if(num_x==1'b0) next_state = LIGHT; //check the last sign '1'
                else next_state = START;
            end
            
            LIGHT: begin
                sign=1'b1;
                if(num_x==1'b1) next_state = NEXT_1; //check the last sign '1'
                else next_state = START;
            end
                
            default: next_state = START;
        endcase
    end
    
endmodule