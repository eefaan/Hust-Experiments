
module  mux2_5(Din1,Din2,sel,Dout);
parameter SIZE=5;

input [1:SIZE] Din1,Din2;
input sel;
output  reg [1:SIZE] Dout;
always@(*)begin
    case(sel)
        1'b0: Dout<=Din1;
        1'b1: Dout<=Din2;
        default;
    endcase    
end

endmodule