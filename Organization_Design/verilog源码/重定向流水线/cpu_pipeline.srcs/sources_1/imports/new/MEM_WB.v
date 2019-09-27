module MEM_WB(
    input rst,
    input en,
    input clk,

    input [31:0]IR_mem,
    input [31:0]PC_mem,
    input JAL_mem,
    input Syscall_mem,
    input RegWrite_mem,
    input MemToReg_mem,
    input RegDst_mem,
    input [31:0]R1_mem,
    input [31:0]Aluout_mem,
    input [31:0]DM_mem,

    output reg[31:0]IR_wb,
    output reg[31:0]PC_wb,
    output reg JAL_wb,
    output reg Syscall_wb,
    output reg RegWrite_wb,
    output reg MemToReg_wb,
    output reg RegDst_wb,
    output reg [31:0]R1_wb,
    output reg [31:0]Aluout_wb,
    output reg [31:0]DM_wb
    );

    always @(posedge clk)begin
        if(rst) begin
            IR_wb=0;
            PC_wb=0;
            JAL_wb=0;
            Syscall_wb=0;
            RegWrite_wb=0;
            MemToReg_wb=0;
            RegDst_wb=0;
            R1_wb=0;
            Aluout_wb=0;
            DM_wb=0;
        end
        else if(en) begin
            IR_wb=IR_mem;
            PC_wb=PC_mem;
            JAL_wb=JAL_mem;
            Syscall_wb=Syscall_mem;
            RegWrite_wb=RegWrite_mem;
            MemToReg_wb=MemToReg_mem;
            RegDst_wb=RegDst_mem;
            R1_wb=R1_mem;
            Aluout_wb=Aluout_mem;
            DM_wb=DM_mem;
        end
    end

endmodule
