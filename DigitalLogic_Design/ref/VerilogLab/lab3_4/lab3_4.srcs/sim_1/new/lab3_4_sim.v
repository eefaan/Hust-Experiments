`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/07 17:38:34
// Design Name: 
// Module Name: lab3_4_sim
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


module lab3_4_sim(
    );
    reg clk_sim;
    reg sig_nsyn;
    wire q1;
    wire q2;
    wire sig_syn;
        
    pipe3b mypipe(sig_nsyn,clk_sim,q1,q2,sig_syn);
    
    always begin
        clk_sim<=0;
        #10;
        clk_sim<=1;
        #10;
    end
    
    always begin
       sig_nsyn <= 0;
       @(posedge clk_sim);
       @(posedge clk_sim);
       #5 sig_nsyn <= 1;
       @(posedge clk_sim);
       #5 sig_nsyn <= 0;
       @(posedge clk_sim);
       @(posedge clk_sim);
       @(posedge clk_sim);
       @(posedge clk_sim);
       @(posedge clk_sim);
//       $stop;
    end
endmodule
