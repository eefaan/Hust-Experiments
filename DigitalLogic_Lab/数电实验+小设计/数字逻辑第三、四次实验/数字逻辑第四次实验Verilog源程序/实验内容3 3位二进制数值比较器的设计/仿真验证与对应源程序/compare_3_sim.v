module compare_3_sim(

    );
    reg [2:0]num1;
    reg [2:0]num2;
    wire [2:0]sign;

    compare_3 mycom(num1,num2,sign);

    initial begin
        num1=100;
        num2=011;
        #20;
        num2=100;
        #20;
        num2=101;
    end

endmodule
