`include "instruction_def.v"
`include "ctrl_encode_def.v"

module Ctrl(JMP, JR, SignedExt, SLLV, LB, BLTZ, OpCode, funct, Beq, Bne, Mem2R, MemW, Aluctrl, Alusrc, RegW, JAL, RegDst, syscall);
input [5: 0] OpCode;
input [5: 0] funct;

output reg JMP;
output reg JR;
output reg SignedExt;
output reg SLLV;
output reg LB;
output reg BLTZ;
output reg Beq;
output reg Bne;
output reg Mem2R;
output reg MemW;
output reg [3: 0] Aluctrl;
output reg Alusrc;
output reg RegW;
output reg JAL;
output reg RegDst;
output reg syscall;



always@(OpCode or funct)
begin
    case (OpCode)
        `INSTR_RTYPE_OP:
        begin
            Mem2R = 0;
            MemW = 0;
            Alusrc = 0;
            RegW = 1;
            syscall = 0;
            SignedExt = 0;
            RegDst = 1;
            Beq = 0;
            Bne = 0;
            JR = 0;
            JMP = 0;
            JAL = 0;
            SLLV = 0;
            LB = 0;
            BLTZ = 0;

            case (funct)
                `INSTR_ADD_FUNCT:
                    Aluctrl = `ALUOp_ADD;

                `INSTR_ADDU_FUNCT:
                    Aluctrl = `ALUOp_ADDU;

                `INSTR_SUB_FUNCT:
                    Aluctrl = `ALUOp_SUB;

                `INSTR_SUBU_FUNCT:
                    Aluctrl = `ALUOp_SUBU;

                `INSTR_AND_FUNCT:
                    Aluctrl = `ALUOp_AND;

                `INSTR_NOR_FUNCT:
                    Aluctrl = `ALUOp_NOR;

                `INSTR_OR_FUNCT:
                    Aluctrl = `ALUOp_OR;

                `INSTR_XOR_FUNCT:
                    Aluctrl = 4'b1001;

                `INSTR_SLT_FUNCT:
                    Aluctrl = `ALUOp_SLT;

                `INSTR_SLTU_FUNCT:
                    Aluctrl = `ALUOp_SLTU;

                `INSTR_SLL_FUNCT:
                    Aluctrl = `ALUOp_SLL;

                `INSTR_SRL_FUNCT:
                    Aluctrl = `ALUOp_SRL;

                `INSTR_SRA_FUNCT:
                    Aluctrl = `ALUOp_SRA;

                `INSTR_JR_FUNCT:begin
                    Aluctrl = `ALUOp_NOP;
                    RegW = 0;
                    JMP = 1;
                    JR = 1;
                end

                `INSTR_SYSCALL_FUNCT:begin
                    Aluctrl = `ALUOp_NOP;
                    RegW = 0;
                    syscall = 1;
                end

                `INSTR_SLLV_FUNCT:begin
                    Aluctrl = `ALUOp_SLL;
                    SLLV=1;
                end

            endcase
        end


        `INSTR_J_OP:
        begin
            Mem2R = 0;
            MemW = 0;
            Alusrc = 0;
            RegW = 0;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 1;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;

        end

        `INSTR_JAL_OP:
        begin
            Mem2R = 0;
            MemW = 0;
            Alusrc = 0;
            RegW = 1;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 1;
            JAL=1;
            SLLV=0;
            LB=0;
            BLTZ=0;

        end

        `INSTR_BEQ_OP:
        begin
            Mem2R = 0;
            MemW = 0;
            Alusrc = 0;
            RegW = 0;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=1;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end

        `INSTR_BNE_OP:
        begin
            Mem2R = 0;
            MemW = 0;
            Alusrc = 0;
            RegW = 0;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=1;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end

        `INSTR_ADDI_OP:
        begin
            Aluctrl = `ALUOp_ADD;
            Mem2R = 0;
            MemW = 0;
            Alusrc = 1;
            RegW = 1;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end

        `INSTR_ANDI_OP:
        begin
            Aluctrl = `ALUOp_AND;
            Mem2R = 0;
            MemW = 0;
            Alusrc = 1;
            RegW = 1;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end


        `INSTR_ADDIU_OP:
        begin
            Aluctrl = `ALUOp_ADD;
            Mem2R = 0;
            MemW = 0;
            Alusrc = 1;
            RegW = 1;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end

        `INSTR_SLTI_OP:
        begin
            Aluctrl = `ALUOp_SLT;
            Mem2R = 0;
            MemW = 0;
            Alusrc = 1;
            RegW = 1;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end



        `INSTR_ORI_OP:
        begin
            Aluctrl = `ALUOp_OR;
            Mem2R = 0;
            MemW = 0;
            Alusrc = 1;
            RegW = 1;
            syscall=0;
            SignedExt = 0;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end

        `INSTR_LW_OP:
        begin
            Aluctrl = `ALUOp_ADD;
            Mem2R = 1;
            MemW = 0;
            Alusrc = 1;
            RegW = 1;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end


        `INSTR_SW_OP:
        begin
            Aluctrl = `ALUOp_ADD;
            Mem2R = 0;
            MemW = 1;
            Alusrc = 1;
            RegW = 0;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end

        `INSTR_LB_OP:
        begin
            Aluctrl = `ALUOp_ADD;
            Mem2R = 1;
            MemW = 0;
            Alusrc = 1;
            RegW = 1;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=1;
            BLTZ=0;
        end

        `INSTR_BLTZ_OP:
        begin
            Aluctrl = `ALUOp_SLT;
            Mem2R = 0;
            MemW = 0;
            Alusrc = 0;
            RegW = 0;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=1;
        end

        `INSTR_SB_OP: begin
            Aluctrl = `ALUOp_ADD;
            Mem2R = 0;
            MemW = 1;
            Alusrc = 1;
            RegW = 0;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end

        default:
        begin
            Aluctrl = `ALUOp_ADD;
            Mem2R = 0;
            MemW = 0;
            Alusrc = 0;
            RegW = 0;
            syscall=0;
            SignedExt = 1;
            RegDst = 0;
            Beq=0;
            Bne=0;
            JR=0;
            JMP = 0;
            JAL=0;
            SLLV=0;
            LB=0;
            BLTZ=0;
        end

    endcase
end

endmodule











module Ctrl4(SLLV, SB, BLTZ, OpCode, funct);
input [5: 0] OpCode;
input [5: 0] funct;
output reg SLLV;
output reg SB;
output reg BLTZ;

always @(OpCode or funct) begin
    case (OpCode)
        `INSTR_RTYPE_OP:begin
            SLLV=0;
            SB=0;
            BLTZ=0;
            case (funct)
                `INSTR_SLLV_FUNCT: SLLV=1;
                default: ;
            endcase
        end

        `INSTR_SB_OP: begin
            SLLV=0;
            SB=1;
            BLTZ=0;
        end

        `INSTR_BLTZ_OP: begin
            SLLV=0;
            SB=0;
            BLTZ=1;
        end

        default: begin
            SLLV=0;
            SB=0;
            BLTZ=0;
        end

    endcase
end

endmodule
