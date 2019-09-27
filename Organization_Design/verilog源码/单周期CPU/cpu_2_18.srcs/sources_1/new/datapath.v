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

	// decode instruction
	wire [5:0]  opcode;
    wire [5:0]  func;
	wire [4:0]  rs;
	wire [4:0]  rt;
	wire [4:0]  rd;
	wire [15:0] imm;
	wire [4:0]  shamt;
	wire [31:0] jaddr;
	assign opcode   = ins[31:26];
    assign func     = ins[5:0];
	assign rs       = ins[25:21];
	assign rt       = ins[20:16];
	assign rd       = ins[15:11];
	assign imm      = ins[15:0];
	assign shamt    = ins[10:6];
	assign jaddr    = {PCout[31:28], ins[25:0], {2{1'b0}}};
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
    REGFILE myregfile(
        .WE(RegWrite),
        .CLK(clk),
        .R1_ADDR(r1_addr),
        .R2_ADDR(r2_addr),
        .W_ADDR(w_addr),
        .Din(w_data),
        .R1(r1),
        .R2(r2),
        .clr(rst)
    );

    // alu
    wire [31:0]dataAin;
    wire [31:0]dataBin;
    wire [4:0]shamt_alu;
    wire [31:0]aluout;
    wire [31:0]result2;
    wire equal;
    assign dataAin = r1;
    assign shamt_alu = (SLLV) ? r1 :shamt;
    ALU myalu(
        .X(dataAin),
        .Y(dataBin),
        .S(Aluop),
        .shamt(shamt_alu),
        .Result(aluout),
        .Result2(result2),
        .Equal(equal)
    );

    // decode aluout
    wire [9:0]dm_addr;
    wire ltz;
    wire [1:0]dm_sb_sel;
	assign dm_addr = aluout[11:2];
    assign ltz = aluout[0];
    assign dm_sb_sel = aluout[1:0];



    // dm(ram)
    wire [31:0]dm_data_0;
    assign dm_data_0=r2;
    wire [31:0]dm_data_1;
    assign dm_data_1=r2<<(dm_sb_sel*8);
    wire [31:0]dm_data_in;
    assign dm_data_in = (SB) ? dm_data_1 : dm_data_0;

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
    assign dm_sel = (SB) ? dm_sb_sel_out : 4'b1111;

    wire [31:0]dm_out;


    // add ram watcher
    wire [9:0]dm_addr_in;
    wire [9:0]dm_addr_watch;
    assign dm_addr_watch = {{6{1'b0}}, watch_addr_4};
    assign dm_addr_in = (watch) ? dm_addr_watch : dm_addr;

    RAM myram(
        .rst(rst),
        .clk(clk),
        .str(MemWrite),
        .ld(1'b1),
        .sel(dm_sel),
        .addr(dm_addr_in),
        .data_in(dm_data_in),
        .data_out(dm_out)
    );



    // signal branch
    //between ir and regfile
    wire [4:0]w_addr_not_jal;
    wire [31:0]w_data_jal;
    wire [31:0]w_back_data;
    wire dis;

    // assign dis = ((r1==32'h22?)&syscall) ? 1'b1 : 1'b0;
    assign dis = (r1==32'h22) ? 1'b1 : 1'b0;
    assign r1_addr = (syscall) ? 5'h02 : rs;
    assign r2_addr = (r1==32'h22) ? 5'h04 : rt;
    assign w_addr_not_jal = (RegDst) ? rd : rt;
    assign w_addr = (JAL) ? 5'h1f : w_addr_not_jal;
    assign w_data_jal = PCout + 32'h8;
    assign w_data = (JAL) ? w_data_jal : w_back_data;

    assign w_back_data = (MemToReg) ? dm_out : aluout;

    //between regfile and alu
    wire [31:0]zeimm;
    wire [31:0]seimm;
    unsign_extend ue_imm(.unextend(imm), .extended(zeimm));
    sign_extend se_imm(.unextend(imm), .extended(seimm));
    wire [31:0]fin_ex_imm;
    assign fin_ex_imm = (SignedExt) ? seimm : zeimm;

    wire [31:0]aluB_0;
    wire [31:0]aluB_1;
    assign aluB_0 = (Alusrc) ? fin_ex_imm : r2;
    assign aluB_1 = 32'h00000000;
    assign dataBin = (BLTZ) ? aluB_1 : aluB_0;

    //PC back
    wire condition_signal;
    wire [31:0]pc_0;
    wire [31:0]pc_1;
    wire [31:0]pc_2;

    assign pc_0 = PCout + 4;
    assign pc_1 = (seimm<<2) + pc_0;
    assign pc_2 = (JR) ? r1 : jaddr;

    assign condition_signal = (equal & Beq) | (Bne & (~equal)) | (BLTZ & (aluout[0]));

    MUX4_32 pc_mux(
        .sel({JMP,condition_signal}),
        .Din0(pc_0),
        .Din1(pc_1),
        .Din2(pc_2),
        .Din3(32'h00000000),
        .Dout(PCin)
    );

    assign PCena = dis | (~syscall) | (go & syscall);



    // output signal
    PCreg  led_reg(clk,rst,dis,r2,led_data);
    counter all_counter(clk,all_num,PCena,rst);
    counter con_counter(clk,conditional_branch_num,condition_signal,rst);
    counter no_con_counter(clk,no_conditional_branch_num,JMP,rst);

endmodule
