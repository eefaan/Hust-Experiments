module forward(
    input [5:0]op,
    input [5:0]func,
    input [4:0]r1addr,
    input [4:0]r2addr,
    input [4:0]exaddr,
    input [4:0]memaddr,
    input exRegWrite,
    input memRegWrite,
    input memMemToReg,
    output datacrash,
    output [1:0]RD1st,
    output [1:0]RD2st
    );

    wire r1used;
    wire r2used;

    regUsed myRegUsed(
        .OP(op),
        .F(func),
        .R1used(r1used),
        .R2used(r2used)
    );

    wire ex_crash_1;
    wire mem_crash_1;
    wire ex_crash_2;
    wire mem_crash_2;
    assign ex_crash_1 = exRegWrite & r1used & (r1addr==exaddr) & (r1addr!=0);
    assign mem_crash_1 = memRegWrite & r1used & (r1addr==memaddr) & (r1addr!=0);
    assign ex_crash_2 = exRegWrite & r2used & (r2addr==exaddr) & (r2addr!=0);
    assign mem_crash_2 = memRegWrite & r2used & (r2addr==memaddr) & (r2addr!=0);

    forward_decode myfdecode1(
        .ex_crash(ex_crash_1),
        .mem_crash(mem_crash_1),
        .memMemToReg(memMemToReg),
        .RDst(RD1st)
    );
    forward_decode myfdecode2(
        .ex_crash(ex_crash_2),
        .mem_crash(mem_crash_2),
        .memMemToReg(memMemToReg),
        .RDst(RD2st)
    );

    assign datacrash = ex_crash_1 | ex_crash_2;
endmodule
