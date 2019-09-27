
module REGFILE(WE,CLK,R1_ADDR,R2_ADDR,W_ADDR,Din,R1,R2,clr);
parameter ADDR=5;
parameter NUM=1<<ADDR;
parameter SIZE=32;

input WE;
input CLK;
input [ADDR-1:0]R1_ADDR,R2_ADDR,W_ADDR;
input clr;
input [SIZE-1:0] Din;
output [SIZE-1:0] R1,R2;

reg [SIZE-1:0] REG_FILE[0:NUM-1];
integer i;
initial for(i=0;i<NUM;i=i+1) REG_FILE[i]<=0;

always @(negedge CLK) begin
    if(clr) for(i=0;i<NUM;i=i+1) REG_FILE[i]<=0;
    else if(WE) REG_FILE[W_ADDR]<=Din;
end

assign R1=REG_FILE[R1_ADDR];
assign R2=REG_FILE[R2_ADDR];

endmodule
