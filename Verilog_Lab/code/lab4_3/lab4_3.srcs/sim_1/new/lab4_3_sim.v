`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/14 04:37:26
// Design Name: 
// Module Name: lab4_3_sim
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


module lab4_3_sim(
   
    );
    reg [2:0]num1;
    reg [2:0]num2;
    wire [2:0]sign;
    
    compare_3 #(3) mycom(num1,num2,sign);
    
    initial begin
        num1=100;
        num2=011;
        #20;
        num2=100;
        #20;
        num2=101;
    end

endmodule
