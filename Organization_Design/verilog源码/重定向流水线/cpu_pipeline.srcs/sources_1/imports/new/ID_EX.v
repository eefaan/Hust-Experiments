module ID_EX(
    input rst,
    input en,
    input clk,

    input [31:0]IR_id,
    input [31:0]PC_id,
    input JMP_id,
    input JR_id,
    input JAL_id,
    input Beq_id,
    input Bne_id,
    input Syscall_id,
    input RegWrite_id,
    input MemToReg_id,
    input RegDst_id,
    input MemWrite_id,
    input [3:0]AluOP_id,
    input AluSrc_id,
    input [31:0]R1_id,
    input [31:0]R2_id,
    input [1:0]RD1st_id,
    input [1:0]RD2st_id,
    input SLLV_id,
    input SB_id,
    input BLTZ_id,
    input [31:0]IMM_id,
    input [31:0]seIMM_id,

    output reg[31:0]IR_ex,
    output reg[31:0]PC_ex,
    output reg JMP_ex,
    output reg JR_ex,
    output reg JAL_ex,
    output reg Beq_ex,
    output reg Bne_ex,
    output reg Syscall_ex,
    output reg RegWrite_ex,
    output reg MemToReg_ex,
    output reg RegDst_ex,
    output reg MemWrite_ex,
    output reg [3:0]AluOP_ex,
    output reg AluSrc_ex,
    output reg [31:0]R1_ex,
    output reg [31:0]R2_ex,
    output reg [1:0]RD1st_ex,
    output reg [1:0]RD2st_ex,
    output reg SLLV_ex,
    output reg SB_ex,
    output reg BLTZ_ex,
    output reg [31:0]IMM_ex,
    output reg [31:0]seIMM_ex
    );

    always @(posedge clk)begin
        if(rst) begin
            IR_ex=0;
            PC_ex=0;
            JMP_ex=0;
            JR_ex=0;
            JAL_ex=0;
            Beq_ex=0;
            Bne_ex=0;
            Syscall_ex=0;
            RegWrite_ex=0;
            MemToReg_ex=0;
            RegDst_ex=0;
            MemWrite_ex=0;
            AluOP_ex=0;
            AluSrc_ex=0;
            R1_ex=0;
            R2_ex=0;
            RD1st_ex=0;
            RD2st_ex=0;
            SLLV_ex=0;
            SB_ex=0;
            BLTZ_ex=0;
            IMM_ex=0;
            seIMM_ex=0;
        end
        else if(en) begin
            IR_ex=IR_id;
            PC_ex=PC_id;
            JMP_ex=JMP_id;
            JR_ex=JR_id;
            JAL_ex=JAL_id;
            Beq_ex=Beq_id;
            Bne_ex=Bne_id;
            Syscall_ex=Syscall_id;
            RegWrite_ex=RegWrite_id;
            MemToReg_ex=MemToReg_id;
            RegDst_ex=RegDst_id;
            MemWrite_ex=MemWrite_id;
            AluOP_ex=AluOP_id;
            AluSrc_ex=AluSrc_id;
            R1_ex=R1_id;
            R2_ex=R2_id;
            RD1st_ex=RD1st_id;
            RD2st_ex=RD2st_id;
            SLLV_ex=SLLV_id;
            SB_ex=SB_id;
            BLTZ_ex=BLTZ_id;
            IMM_ex=IMM_id;
            seIMM_ex=seIMM_id;
        end
    end

endmodule
