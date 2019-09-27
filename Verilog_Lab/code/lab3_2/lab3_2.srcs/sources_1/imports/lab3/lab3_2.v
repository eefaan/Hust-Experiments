module lab3(
    input   X,
    input   clk,
    output  Q0,
    output  Q1,
    output  Y
);

reg  Q0;
reg  Q1;

initial begin
    Q0=1'b0;
    Q1=1'b0;
end

assign Y = ~(X&(~Q1));

always @(negedge clk) begin
    Q0 <= ~Q0;
    if(X^Q0) Q1<=~Q1;
end
endmodule
