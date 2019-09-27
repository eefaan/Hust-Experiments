`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2019/02/19 11:21:55
// Design Name:
// Module Name: datapath
// Project Name:
// Target Devices:
// Tool Versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////


`ifndef DEBUG_CPU_STAGES
`define DEBUG_CPU_STAGES 0
`endif


module datapath(
    input rst,
    input clk,
    input go,
    input watch,//watch ram
    input [3:0]watch_addr_4,

    output [31:0]led_data,
    output [15:0]all_num,
    output [15:0]no_conditional_branch_num,
    output [15:0]conditional_branch_num,
    output [31:0]dm_out
    );

    wire en;
    wire Ex_Branch;
    wire [31:0]PC_Branch;
    wire LoadUse;

    // PC register
    wire [31:0]PCin;
    wire [31:0]PCout;
    wire PCena;
    PCreg PC(
        .clk(clk), .rst(rst), .ena(PCena),
        .data_in(PCin), .data_out(PCout)
    );

    // instruction memory
    wire [31:0]ins;
    parameter IM_DATA = "C:\\2_19.hex";
    ROM #(.ROM_DATA(IM_DATA)) IR(
        .addr(PCout), .data(ins)
    );

    // IF_ID
    wire [31:0]ins_id;
    wire [31:0]pc_id;
    IF_ID myIF_ID(
        .rst(Ex_Branch|rst),
        .en(PCena),
        .clk(clk),
        .IR_if(ins),
        .PC_if(PCout),
        .IR_id(ins_id),
        .PC_id(pc_id)
    );

	// decode instruction
	wire [5:0]  opcode;
    wire [5:0]  func;
	wire [4:0]  rs;
	wire [4:0]  rt;
	wire [4:0]  rd;
	wire [15:0] imm;
	wire [4:0]  shamt;
	wire [31:0] jaddr;
	assign opcode   = ins_id[31:26];
    assign func     = ins_id[5:0];
	assign rs       = ins_id[25:21];
	assign rt       = ins_id[20:16];
	assign rd       = ins_id[15:11];
	assign imm      = ins_id[15:0];
	assign shamt    = ins_id[10:6];
	assign jaddr    = {pc_id[31:28], ins_id[25:0], {2{1'b0}}};
    // wire [31:0] seimm;  // sign extended immediate
	// assign seimm 	= {{16{inst_s2[15]}}, inst_s2[15:0]};

    // control (opcode, func -> ...)
    wire JMP;                //指令跳转
    wire JR;                 //指令跳转
    wire SignedExt;          //有无符号位拓展选择
    wire Beq;                //指令跳转
    wire Bne;                //指令跳转
    wire MemToReg;           //数据存储器到寄存器堆
    wire MemWrite;           //写数据存储器
    wire [3:0]Aluop;         //Alu运算选择
    wire Alusrc;             //运算器操作数选择
    wire RegWrite;           //寄存器堆写入数据
    wire JAL;
    wire RegDst;
    wire syscall;
    // addtional 4 instructions
    wire SLLV;               //指令跳转
    wire SB;                 //指令跳转
    wire BLTZ;               //指令跳转
    // temp for other's 28ins ctrl
    wire a;
    wire b;
    wire c;
    Ctrl my24control(
        .OpCode(opcode),
        .funct(func),

        .JMP(JMP),
        .JR(JR),
        .SignedExt(SignedExt),
        .Beq(Beq),
        .Bne(Bne),
        .Mem2R(MemToReg),
        .MemW(MemWrite),
        .Aluctrl(Aluop),
        .Alusrc(Alusrc),
        .RegW(RegWrite),
        .JAL(JAL),
        .RegDst(RegDst),
        .syscall(syscall),

        .SLLV(a),
        .LB(b),
        .BLTZ(c)
    );
    Ctrl4 my4control(
        .OpCode(opcode),
        .funct(func),
        .SLLV(SLLV),
        .SB(SB),
        .BLTZ(BLTZ)
    );

    // register file
    wire [4:0]r1_addr;
    wire [4:0]r2_addr;
    wire [4:0]w_addr;
    wire [31:0]w_data;
    wire [31:0]r1;
    wire [31:0]r2;
    wire RegWrite_wb;
    REGFILE myregfile(
        .WE(RegWrite_wb),
        .CLK(clk),
        .R1_ADDR(r1_addr),
        .R2_ADDR(r2_addr),
        .W_ADDR(w_addr),
        .Din(w_data),
        .R1(r1),
        .R2(r2),
        .clr(rst)
    );

    // regfile signal input
    wire [4:0]w_addr_not_jal;
    wire [31:0]w_data_jal;
    wire [31:0]w_back_data_wb;
    assign r1_addr = (syscall) ? 5'h02 : rs;
    assign r2_addr = (syscall) ? 5'h04 : rt;


    // extend the imm
    wire [31:0]zeimm;
    wire [31:0]seimm;
    unsign_extend ue_imm(.unextend(imm), .extended(zeimm));
    sign_extend se_imm(.unextend(imm), .extended(seimm));
    wire [31:0]fin_extend_imm;
    assign fin_extend_imm = (SignedExt) ? seimm : zeimm;

    // ID_EX
    wire [31:0]ins_ex;
    wire [31:0]pc_ex;
    wire JMP_ex;
    wire JR_ex;
    wire JAL_ex;
    wire Beq_ex;
    wire Bne_ex;
    wire Syscall_ex;
    wire RegWrite_ex;
    wire MemToReg_ex;
    wire RegDst_ex;
    wire MemWrite_ex;
    wire [3:0]AluOP_ex;
    wire AluSrc_ex;
    wire [31:0]R1_ex;
    wire [31:0]R2_ex;
    wire [1:0]RD1st_id;
    wire [1:0]RD2st_id;
    wire [1:0]RD1st_ex;
    wire [1:0]RD2st_ex;
    wire SLLV_ex;
    wire SB_ex;
    wire BLTZ_ex;
    wire [31:0]IMM_ex;
    wire [31:0]seIMM_ex;
    ID_EX myID_EX(
        .rst(Ex_Branch|LoadUse|rst),
        .en(en),
        .clk(clk),

        .IR_id(ins_id), .PC_id(pc_id),
        .JMP_id(JMP), .JR_id(JR), .JAL_id(JAL), .Beq_id(Beq), .Bne_id(Bne),
        .Syscall_id(syscall), .RegWrite_id(RegWrite), .MemToReg_id(MemToReg),
        .RegDst_id(RegDst), .MemWrite_id(MemWrite), .AluOP_id(Aluop), .AluSrc_id(Alusrc),
        .R1_id(r1), .R2_id(r2), .RD1st_id(RD1st_id), .RD2st_id(RD2st_id),
        .SLLV_id(SLLV), .SB_id(SB), .BLTZ_id(BLTZ),
        .IMM_id(fin_extend_imm), .seIMM_id(seimm),

        .IR_ex(ins_ex), .PC_ex(pc_ex),
        .JMP_ex(JMP_ex), .JR_ex(JR_ex), .JAL_ex(JAL_ex), .Beq_ex(Beq_ex), .Bne_ex(Bne_ex),
        .Syscall_ex(Syscall_ex), .RegWrite_ex(RegWrite_ex), .MemToReg_ex(MemToReg_ex),
        .RegDst_ex(RegDst_ex), .MemWrite_ex(MemWrite_ex), .AluOP_ex(AluOP_ex), .AluSrc_ex(AluSrc_ex),
        .R1_ex(R1_ex), .R2_ex(R2_ex), .RD1st_ex(RD1st_ex), .RD2st_ex(RD2st_ex),
        .SLLV_ex(SLLV_ex), .SB_ex(SB_ex), .BLTZ_ex(BLTZ_ex),
        .IMM_ex(IMM_ex), .seIMM_ex(seIMM_ex)
    );

    // alu
    wire [31:0]dataAin;
    wire [31:0]dataBin;
    wire [4:0]shamt_alu;
    wire [31:0]aluout;
    wire [31:0]result2;
    wire equal;
    ALU myalu(
        .X(dataAin),
        .Y(dataBin),
        .S(AluOP_ex),
        .shamt(shamt_alu),
        .Result(aluout),
        .Result2(result2),
        .Equal(equal)
    );

    // connect dataAin, dataBin, shamt_alu
    wire [31:0]select_r1_ex;
    wire [31:0]select_r2_ex;
    wire [31:0]aluB_0;
    wire [31:0]aluB_1;
    assign aluB_0 = (AluSrc_ex) ? IMM_ex : select_r2_ex;
    assign aluB_1 = 32'b0;
    assign dataBin = (BLTZ_ex) ? aluB_1 : aluB_0;
    assign dataAin = select_r1_ex;
    assign shamt_alu = (SLLV_ex) ? select_r1_ex : ins_ex[10:6];

    // Branch back
    wire [31:0]JAL_PC;
    wire [31:0]B_PC;
    wire [31:0]JR_PC;
    assign JAL_PC={pc_ex[31:28], ins_ex[25:0], {2{1'b0}}};
    assign B_PC=(seIMM_ex<<2)+pc_ex+4;
    assign JR_PC=select_r1_ex;

    wire dis;
    assign dis=(JR_PC==32'h22) & Syscall_ex;

    wire condition_signal;
    wire no_condition_signal;
    assign condition_signal=(equal&Beq_ex)|(~equal&Bne_ex)|(aluout[0]&BLTZ_ex);
    assign no_condition_signal=JMP_ex;

    assign Ex_Branch=JMP_ex|condition_signal;
    assign PC_Branch=JMP_ex?(JR_ex?JR_PC:JAL_PC):B_PC;

    // EX_MEM
    wire [31:0]ins_mem;
    wire [31:0]pc_mem;
    wire JAL_mem;
    wire Syscall_mem;
    wire RegWrite_mem;
    wire MemToReg_mem;
    wire RegDst_mem;
    wire MemWrite_mem;
    wire [31:0]R1_mem;
    wire [31:0]Aluout_mem;
    wire [31:0]R2_mem;
    wire SB_mem;
    EX_MEM myEX_MEM(
        .rst(rst),
        .en(en),
        .clk(clk),

        .IR_ex(ins_ex), .PC_ex(pc_ex),
        .JAL_ex(JAL_ex), .Syscall_ex(Syscall_ex),
        .RegWrite_ex(RegWrite_ex), .MemToReg_ex(MemToReg_ex), .RegDst_ex(RegDst_ex), .MemWrite_ex(MemWrite_ex),
        .R1_ex(select_r1_ex), .Aluout_ex(aluout), .R2_ex(select_r2_ex),
        .SB_ex(SB_ex),

        .IR_mem(ins_mem), .PC_mem(pc_mem),
        .JAL_mem(JAL_mem), .Syscall_mem(Syscall_mem),
        .RegWrite_mem(RegWrite_mem), .MemToReg_mem(MemToReg_mem), .RegDst_mem(RegDst_mem), .MemWrite_mem(MemWrite_mem),
        .R1_mem(R1_mem), .Aluout_mem(Aluout_mem), .R2_mem(R2_mem),
        .SB_mem(SB_mem)
    );

    // decode aluout
    wire [9:0]dm_addr;
    wire [1:0]dm_sb_sel;
	assign dm_addr = Aluout_mem[11:2];
    assign dm_sb_sel = Aluout_mem[1:0];

    // dm(ram)
    wire [31:0]dm_data_0;
    assign dm_data_0=R2_mem;
    wire [31:0]dm_data_1;
    assign dm_data_1=R2_mem<<(dm_sb_sel*8);
    wire [31:0]dm_data_in;
    assign dm_data_in = (SB_mem) ? dm_data_1 : dm_data_0;

    wire [3:0]dm_sb_sel_out;
    MUX4_32 #(4) dm_sb_sel_mux(
        .sel(dm_sb_sel),
        .Din0(4'b0001),
        .Din1(4'b0010),
        .Din2(4'b0100),
        .Din3(4'b1000),
        .Dout(dm_sb_sel_out)
    );
    wire [3:0]dm_sel;
    assign dm_sel = (SB_mem) ? dm_sb_sel_out : 4'b1111;

    // add ram watcher
    wire [9:0]dm_addr_in;
    wire [9:0]dm_addr_watch;
    assign dm_addr_watch = {{6{1'b0}}, watch_addr_4};
    assign dm_addr_in = (watch) ? dm_addr_watch : dm_addr;

    RAM myram(
        .rst(rst),
        .clk(clk),
        .str(MemWrite_mem),
        .ld(1'b1),
        .sel(dm_sel),
        .addr(dm_addr_in),
        .data_in(dm_data_in),
        .data_out(dm_out)
    );

    // MEM_WB
    wire [31:0]ins_wb;
    wire [31:0]pc_wb;
    wire JAL_wb;
    wire Syscall_wb;
    wire MemToReg_wb;
    wire RegDst_wb;
    wire [31:0]R1_wb;
    wire [31:0]Aluout_wb;
    wire [31:0]DM_wb;
    MEM_WB myMEM_WB(
        .rst(rst),
        .en(en),
        .clk(clk),

        .IR_mem(ins_mem), .PC_mem(pc_mem), .JAL_mem(JAL_mem),
        .Syscall_mem(Syscall_mem), .RegWrite_mem(RegWrite_mem),
        .MemToReg_mem(MemToReg_mem), .RegDst_mem(RegDst_mem),
        .R1_mem(R1_mem), .Aluout_mem(Aluout_mem), .DM_mem(dm_out),

        .IR_wb(ins_wb), .PC_wb(pc_wb), .JAL_wb(JAL_wb),
        .Syscall_wb(Syscall_wb), .RegWrite_wb(RegWrite_wb),
        .MemToReg_wb(MemToReg_wb), .RegDst_wb(RegDst_wb),
        .R1_wb(R1_wb), .Aluout_wb(Aluout_wb), .DM_wb(DM_wb)
    );

    // wb signal
    MUX4_32 r1_ex(RD1st_ex, R1_ex, Aluout_mem, Aluout_wb, DM_wb, select_r1_ex);
    MUX4_32 r2_ex(RD2st_ex, R2_ex, Aluout_mem, Aluout_wb, DM_wb, select_r2_ex);
    assign w_addr_not_jal = (RegDst_wb) ? ins_wb[15:11] : ins_wb[20:16];
    assign w_addr = (JAL_wb) ? 5'h1f : w_addr_not_jal;
    assign w_data_jal = pc_wb + 32'h4;
    assign w_data = (JAL_wb) ? w_data_jal : w_back_data_wb;
    assign w_back_data_wb = (MemToReg_wb) ? DM_wb : Aluout_wb;

    // PC back
    wire dis_wb;
    assign dis_wb = (R1_wb==32'h22) & Syscall_wb;
    assign en = dis_wb | (go&Syscall_wb) | (~Syscall_wb);
    assign PCena = en & ~LoadUse;
    assign PCin = (Ex_Branch) ? PC_Branch : (PCout+4);

    // Forward
    wire [4:0]ex_addr;
    wire [4:0]mem_addr;
    assign ex_addr = JAL_ex ? (5'h1f) : (RegDst_ex ? ins_ex[15:11] : ins_ex[20:16]);
    assign mem_addr = JAL_mem ? (5'h1f) : (RegDst_mem ? ins_mem[15:11] : ins_mem[20:16]);
    wire ex_data_crash;
    forward myforward(
        .op(ins_id[31:26]),
        .func(ins_id[5:0]),
        .r1addr(r1_addr),
        .r2addr(r2_addr),
        .exaddr(ex_addr),
        .memaddr(mem_addr),
        .exRegWrite(RegWrite_ex),
        .memRegWrite(RegWrite_mem),
        .memMemToReg(MemToReg_mem),
        .datacrash(ex_data_crash),
        .RD1st(RD1st_id),
        .RD2st(RD2st_id)
    );
    assign LoadUse = ex_data_crash & (ins_ex[31:26]==6'h23);

    // output signal
    PCreg  led_reg(clk,rst,dis,aluout,led_data);
    counter all_counter(clk,all_num,en,rst);
    counter con_counter(clk,conditional_branch_num,condition_signal,rst);
    counter no_con_counter(clk,no_conditional_branch_num,no_condition_signal,rst);

endmodule
