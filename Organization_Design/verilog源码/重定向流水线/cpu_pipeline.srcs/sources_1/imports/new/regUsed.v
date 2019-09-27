module regUsed(
    input [5:0]OP,
    input [5:0]F,
    output R1used,
    output R2used
    );

    wire OP0 = OP[0];
    wire OP1 = OP[1];
    wire OP2 = OP[2];
    wire OP3 = OP[3];
    wire OP4 = OP[4];
    wire OP5 = OP[5];
    wire F0 = F[0];
    wire F1 = F[1];
    wire F2 = F[2];
    wire F3 = F[3];
    wire F4 = F[4];
    wire F5 = F[5];

    assign R1used = (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & ~F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & ~F2 & ~F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & ~F2 & F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & F2 & ~F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & F2 & F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & F3 & ~F2 & F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & F3 & ~F2 & F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & ~F5 & ~F4 & F3 & ~F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & ~F5 & ~F4 & F3 & F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & OP2 & ~OP1 & ~OP0) |
                    (~OP5 & ~OP4 & ~OP3 & OP2 & ~OP1 & OP0) |
                    (~OP5 & ~OP4 & OP3 & ~OP2 & ~OP1 & ~OP0) |
                    (~OP5 & ~OP4 & OP3 & OP2 & ~OP1 & ~OP0) |
                    (~OP5 & ~OP4 & OP3 & ~OP2 & ~OP1 & OP0) |
                    (~OP5 & ~OP4 & OP3 & ~OP2 & OP1 & ~OP0) |
                    (~OP5 & ~OP4 & OP3 & OP2 & ~OP1 & OP0) |
                    (OP5 & ~OP4 & ~OP3 & ~OP2 & OP1 & OP0) |
                    (OP5 & ~OP4 & OP3 & ~OP2 & OP1 & OP0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & ~F5 & ~F4 & ~F3 & F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & F2 & F1 & ~F0) |
                    (OP5 & ~OP4 & OP3 & ~OP2 & ~OP1 & ~OP0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & OP0);

    assign R2used = (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & ~F5 & ~F4 & ~F3 & ~F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & ~F5 & ~F4 & ~F3 & ~F2 & F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & ~F5 & ~F4 & ~F3 & ~F2 & F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & ~F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & ~F2 & ~F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & ~F2 & F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & F2 & ~F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & F2 & F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & F3 & ~F2 & F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & F3 & ~F2 & F1 & F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & ~F5 & ~F4 & F3 & F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & OP2 & ~OP1 & ~OP0) |
                    (~OP5 & ~OP4 & ~OP3 & OP2 & ~OP1 & OP0) |
                    (OP5 & ~OP4 & OP3 & ~OP2 & OP1 & OP0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & ~F5 & ~F4 & ~F3 & F2 & ~F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & ~OP0 & F5 & ~F4 & ~F3 & F2 & F1 & ~F0) |
                    (~OP5 & ~OP4 & ~OP3 & ~OP2 & ~OP1 & OP0);

endmodule
