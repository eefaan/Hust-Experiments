module EX_MEM(
    input rst,
    input en,
    input clk,

    input [31:0]IR_ex,
    input [31:0]PC_ex,
    input JAL_ex,
    input Syscall_ex,
    input RegWrite_ex,
    input MemToReg_ex,
    input RegDst_ex,
    input MemWrite_ex,
    input [31:0]R1_ex,
    input [31:0]Aluout_ex,
    input [31:0]R2_ex,
    input SB_ex,

    output reg[31:0]IR_mem,
    output reg[31:0]PC_mem,
    output reg JAL_mem,
    output reg Syscall_mem,
    output reg RegWrite_mem,
    output reg MemToReg_mem,
    output reg RegDst_mem,
    output reg MemWrite_mem,
    output reg [31:0]R1_mem,
    output reg [31:0]Aluout_mem,
    output reg [31:0]R2_mem,
    output reg SB_mem
    );

    always @(posedge clk)begin
        if(rst) begin
            IR_mem=0;
            PC_mem=0;
            JAL_mem=0;
            Syscall_mem=0;
            RegWrite_mem=0;
            MemToReg_mem=0;
            RegDst_mem=0;
            MemWrite_mem=0;
            R1_mem=0;
            Aluout_mem=0;
            R2_mem=0;
            SB_mem=0;
        end
        else if(en) begin
            IR_mem=IR_ex;
            PC_mem=PC_ex;
            JAL_mem=JAL_ex;
            Syscall_mem=Syscall_ex;
            RegWrite_mem=RegWrite_ex;
            MemToReg_mem=MemToReg_ex;
            RegDst_mem=RegDst_ex;
            MemWrite_mem=MemWrite_ex;
            R1_mem=R1_ex;
            Aluout_mem=Aluout_ex;
            R2_mem=R2_ex;
            SB_mem=SB_ex;
        end
    end

endmodule
