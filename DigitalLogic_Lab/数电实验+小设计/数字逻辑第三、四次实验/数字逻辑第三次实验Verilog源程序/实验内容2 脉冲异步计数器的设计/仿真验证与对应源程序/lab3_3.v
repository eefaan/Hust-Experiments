`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/07 16:54:18
// Design Name: 
// Module Name: lab3_3
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


module lab3_3(
    X,Q4,Q3,Q2,Q1,Z
    );
    input X;
    output reg Q4;
    output reg Q3;
    output reg Q2;
    output reg Q1;
    output Z;
        
    
    wire K4,K3,K2,K1;
    wire J4,J3,J2,J1;
    
    initial begin
        Q1<=0;
        Q2<=0;
        Q3<=0;
        Q4<=0;
    end
    
    assign K4=1'b1;
    assign J4=Q3&Q2;
    assign K3=1'b1;
    assign J3=1'b1;
    assign K2=1'b1;
    assign J2=(~Q4);
    assign K1=1'b1;
    assign J1=1'b1;
    
    assign Z=Q4&Q1&X;
    
    always @(negedge X) begin
        if((!K1)&(!J1)) ;
        else if((!K1)&J1) Q1=1;
        else if(K1&(!J1)) Q1=0;
        else Q1=(~Q1);
    end
    
    always @(negedge Q1) begin
        if((!K2)&(!J2)) ;
        else if((!K2)&J2) Q2=1;
        else if(K2&(!J2)) Q2=0;
        else Q2=(~Q2);
    end
        
    always @(negedge Q2) begin
        if((!K3)&(!J3)) ;
        else if((!K3)&J3) Q3=1;
        else if(K3&(!J3)) Q3=0;
        else Q3=(~Q3);
    end    

    always @(negedge Q1) begin
        if((!K4)&(!J4)) ;
        else if((!K4)&J4) Q4=1;
        else if(K4&(!J4)) Q4=0;
        else Q4=(~Q4);
    end
endmodule
