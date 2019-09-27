module forward_decode(
    input ex_crash,
    input mem_crash,
    input memMemToReg,
    output [1:0]RDst
    );

    wire st1;
    wire st0;
    assign RDst[1]=st1;
    assign RDst[0]=st0;
    
    assign st1 = ~ex_crash & mem_crash;
    assign st0 = ex_crash | (mem_crash&memMemToReg);

endmodule
