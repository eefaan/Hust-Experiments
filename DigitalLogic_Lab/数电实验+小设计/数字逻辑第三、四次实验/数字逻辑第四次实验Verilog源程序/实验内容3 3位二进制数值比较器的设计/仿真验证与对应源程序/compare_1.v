module compare_1#(parameter WIDTH=1)(
    input [WIDTH-1:0]num1,
    input [WIDTH-1:0]num2,
    output reg [2:0]sign
    );

    initial begin
        sign=0;
    end

    always @(*) begin
        if(num1>num2) sign=3'b100;
        else if(num1==num2) sign=3'b010;
        else sign=3'b001;
    end

endmodule
