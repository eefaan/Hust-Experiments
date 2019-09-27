`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/12 10:31:52
// Design Name: 
// Module Name: seven_seg_disp
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


module seven_seg_disp(
    input       clk100MHZ,
    input       rst_n,
    input [7:0] AN,
    input [3:0] dig0,
    input [3:0] dig1,
    input [3:0] dig2,
    input [3:0] dig3,
    input [3:0] dig4,
    input [3:0] dig5,
    input [3:0] dig6,
    input [3:0] dig7,

);


input            clk,
                     input            resetn,
                     input      [7:0] EN,
                     input      [3:0] DISP0,
                     input      [3:0] DISP1,
                     input      [3:0] DISP2,
                     input      [3:0] DISP3,
                     input      [3:0] DISP4,
                     input      [3:0] DISP5,
                     input      [3:0] DISP6,
                     input      [3:0] DISP7,
                     output     [7:0] DISPENOUT,
                     output     [6:0] DISPOUT);

  wire [16:0] cnt17;
  wire [ 2:0] cntSel;
  wire [ 7:0] en0, en1, en2, en3, en4, en5, en6, en7;
  wire [ 3:0] numout;

  assign en0 = (EN | 8'hfe);
  assign en1 = (EN | 8'hfd);
  assign en2 = (EN | 8'hfb);
  assign en3 = (EN | 8'hf7);
  assign en4 = (EN | 8'hef);
  assign en5 = (EN | 8'hdf);
  assign en6 = (EN | 8'hbf);
  assign en7 = (EN | 8'h7f);


  mipsfpga_ahb_sevensegdec sevensegdec(.data(numout), .segments(DISPOUT));

  counter #(17) counter17(clk, resetn, cnt17);
  counter #(3)  counterSel(cnt17[16], resetn, cntSel);
  mux8 #(8) mux8_7segen(en0, en1, en2, en3, en4, en5, en6, en7,
                        cntSel, DISPENOUT);
  mux8 #(4) mux8_7segval(DISP0, DISP1, DISP2, DISP3, DISP4, DISP5, DISP6, 
                         DISP7, cntSel, numout);

endmodule


// counter
module counter
#(parameter WIDTH=8)
(     input                    clk,
      input                    resetn,
      output reg [(WIDTH-1):0] cnt);

  always @(posedge clk, negedge resetn)
    if (~resetn) cnt <= 0;
    else         cnt <= cnt + 1;

endmodule


module mux8 #(parameter WIDTH = 8)
             (input  [WIDTH-1:0]     d0, d1, d2, d3, d4, d5, d6, d7,
              input  [2:0]           s, 
              output reg [WIDTH-1:0] y);

  always @(*)
    case (s)
      3'b000:    y = d0;
      3'b001:    y = d1;
      3'b010:    y = d2;
      3'b011:    y = d3;
      3'b100:    y = d4;
      3'b101:    y = d5;
      3'b110:    y = d6;
      3'b111:    y = d7;
      default:   y = d0;
    endcase

endmodule
endmodule
