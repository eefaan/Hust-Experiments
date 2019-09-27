`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/18 20:08:09
// Design Name: 
// Module Name: counter
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

module counter(clk, out, enable, rst);
    
    input clk,enable,rst;                    // ???ʱ?
    output reg [15:0] out;             // ???ֵ
    
    initial out<=16'b0;
    always @(posedge clk)  begin  // ?ʱ??????????
                                // ???ʵ?
        if(enable) out <=out +1;
        if(rst) out<=0;
        //if(out == 3'b011) out[2:0]=3'b000;
    end                           
endmodule
