`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2018/06/07 06:58:10
// Design Name:
// Module Name: lab3_2_sml
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


module lab3_2_sml(

    );
    reg X;
    reg clk_sim;
    wire Q0;
    wire Q1;
    wire Y;

    lab3 simlab3(X,clk_sim,Q0,Q1,Y);

    // Clock Procedure
   always begin
      clk_sim <= 0;
      #10;
      clk_sim <= 1;
      #10;
   end   // Note: Procedure repeats
   // Vector Procedure
   initial begin
      X <= 0;
      @(posedge clk_sim);
      @(posedge clk_sim);
      #5 X <= 1;
      @(posedge clk_sim);
      #5 X <= 0;
      @(posedge clk_sim);
      $stop;
   end


endmodule
