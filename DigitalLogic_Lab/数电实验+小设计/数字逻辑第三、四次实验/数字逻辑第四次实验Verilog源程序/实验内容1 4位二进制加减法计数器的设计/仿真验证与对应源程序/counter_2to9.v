module counter_2to9(
   input clk,
   input rst,
   input en,
   input [3:0]data,
   input load,
   output [3:0]dout,
   output cout
   );

   counter_16 #(2,9) mycounter(clk,rst,en,data,load,dout,cout);

endmodule
