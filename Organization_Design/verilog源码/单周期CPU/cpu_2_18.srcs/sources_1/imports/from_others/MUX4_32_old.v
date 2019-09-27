module 4_32(sel,Din0,Din1,Din2,Din3,Dout);

input [0:1] sel;
input [1:32] Din0,Din1,Din2,Din3;
output [1:32] Dout;

always @(*)
begin  
    case(sel)
    2'b00: Dout<=Din0;
    2'b01: Dout<=Din1;
    2'b10: Dout<=Din2;
    default: ;
    endcase
end
endmodule