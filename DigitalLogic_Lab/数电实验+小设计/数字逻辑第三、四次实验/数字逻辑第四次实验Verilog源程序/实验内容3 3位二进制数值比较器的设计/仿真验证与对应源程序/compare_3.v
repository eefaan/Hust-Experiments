module compare_3(
    input [2:0]num1,
    input [2:0]num2,
    output [2:0]sign
    );

    compare_1 #(3) mycom(num1,num2,sign);

endmodule
