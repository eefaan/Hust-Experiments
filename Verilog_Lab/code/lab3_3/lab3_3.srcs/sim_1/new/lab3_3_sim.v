`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/07 17:21:58
// Design Name: 
// Module Name: lab3_3_sim
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


module lab3_3_sim(
    
    );
    reg X;
    wire Q4,Q3,Q2,Q1,Z;
    
    lab3_3 simlab3_3(X,Q4,Q3,Q2,Q1,Z);

    // Clock Procedure
   always begin
      X <= 0;
      #10;
      X <= 1;
      #10;
   end   // Note: Procedure repeats 

endmodule
