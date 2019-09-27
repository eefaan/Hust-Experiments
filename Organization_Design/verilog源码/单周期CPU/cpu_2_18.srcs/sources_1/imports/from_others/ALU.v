`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 17:12:46
// Design Name: 
// Module Name: ALU
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


module ALU(input [31:0] X,input [31:0] Y,input [3:0] S,input [4:0] shamt,
           output reg[31:0] Result,output reg[31:0] Result2,output reg Equal
    );
           reg compare_flag;
            initial begin
                Result = 0;
                Result2 = 0;
                Equal = 0;
            end
            always @(*) begin
               if(X==Y) Equal = 1;
               else Equal = 0;
               case(S)
                 4'b0000:begin 
                     Result = Y<<shamt;
                     Result2 = 0;
                 end
                 4'b0001:begin
                     Result =   ( { {31{Y[31]}}, 1'b0 } << (~shamt[4:0]) ) | ( Y >> shamt );
                     Result2 = 0;                 
                 end
                 4'b0010:begin
                     Result = Y>>shamt;
                     Result2 = 0;                   
                 end
                 4'b0011:begin
                     {Result2,Result}=X*Y;
                 end
                 4'b0100:begin
                     Result=X/Y;
                     Result2 = X%Y;
                 end
                 4'b0101:begin
                     Result=X+Y;
                     Result2 = 0;
                 end
                 4'b0110:begin
                     Result=X-Y;
                     Result2 = 0;                    
                 end
                 4'b0111:begin
                     Result=X&Y;
                     Result2 = 0;
                 end
                 4'b1000:begin
                     Result=X|Y;
                     Result2 = 0;
                 end
                 4'b1001:begin
                     Result=X^Y;
                     Result2 = 0;
                 end
                 4'b1010:begin
                     Result=~(X|Y);
                     Result2 = 0;
                 end
                 4'b1011:begin
                     if(X[31]==1&&Y[31]==0)
                       compare_flag=1;
                     else if(X[31]==0&&Y[31]==1)
                       compare_flag=0;
                     else if(X[31]==1&&Y[31]==1)
                        compare_flag = (X>Y) ? 1 : 0;
                     else compare_flag = (X<Y) ? 1 : 0 ;
                    Result={{31{1'b0}},compare_flag};
                    Result2 = 0;
                 end
                 4'b1100:begin
                    Result=(X<Y) ? {{31{1'b0}},1} : {{31{1'b0}},0} ; 
                    Result2 = 0;                 
                 end
                 default:begin
                     Result=0;
                     Result2=0;
                 end  
               endcase
            end
endmodule
