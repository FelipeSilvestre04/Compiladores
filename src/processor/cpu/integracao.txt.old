module cpu (
    input  logic clk,
    input  logic rst
);

    wire [31:0] PC;
    wire [31:0] PC_desvio;

    wire [31:0] instrucao;

    wire [5:0]  rs1, rs2, rw;
    wire [2:0]  op;
    wire [3:0]  funct;
    wire [12:0] imediato_I;
    wire [18:0] imediato_J;

    logic Jump;
    logic Branch;
    logic MemRead;
    logic MemtoReg;
    logic ALUop;
    logic MemWrite;
    logic ALUSrc;
    logic RegWrite;
    logic RegDst;
    logic branch;

    wire [5:0] WriteRegister;
    wire [31:0] Reg2Ula;

    wire [31:0] rd_data, rs1_data, rs2_data;

    wire [31:0] ula_result;
    logic branch_taken;
 

    memoria_ROM ROM (
        .endereco(PC),
        .saida(instrucao)
    );

    decoder_instrucao decoder (
        .instrucao(instrucao),
        .rs1(rs1),
        .rs2(rs2),
        .rw(rw),
        .op(op),
        .funct(funct),
        .imediato_I(imediato_I),
        .imediato_J(imediato_J)
    );

    unidade_de_controle UC (
        .op(op),
        .funct(funct),
        .Jump(Jump),
        .Branch(Branch),
        .MemRead(MemRead),
        .MemtoReg(MemtoReg),
        .ALUop(ALUop),
        .MemWrite(MemWrite),
        .ALUSrc(ALUSrc),
        .RegWrite(RegWrite),
        .RegDst(RegDst)
    );

    mux_branco mux_banco_inst (
        .sign(RegDst),
        .rs2(rs2),
        .rw(rw),
        .wr(WriteRegister)
    );

    banco banco_inst (
        .clk(clk),
        .we(RegWrite),
        .rs1_addr(rs1),
        .rs2_addr(rs2),
        .rd_addr(WriteRegister),
        .rd_data(rd_data),
        .rs1_data(rs1_data),
        .rs2_data(rs2_data)
    );

    mux_ula mux_ula_inst (
        .sign(ALUSrc),
        .rs2(rs2_data),
        .im(imediato_J),
        .reg_saida(Reg2Ula)
    );

    ula ula_inst (
        .rs1(rs1_data),
        .rs2(Reg2Ula),
        .op(ALUop),
        .branch_en(Branch),
        .rd(ula_result),
        .branch_taken(branch_taken)
    );

    memoria_ram ram_inst (
        .data(ula_result),
        .read_addr(rs1),
        .write_addr(rs1),
        .we(MemWrite),
        .clk(clk),
        .q(rd)
    );

    mux_memoria mux_mem_inst (
        .sign(MemtoReg),
        .ula_result(ula_result),
        .mem_result(rd),
        .rd_data(rd_data)
    );

    mux_jump mux_jump_inst (
        .sign(Jump),
        .im1(imediato_J_ex),
        .im2(imediato_I_ex),
        .im(imediato_destino)
    );

    PC_ADD PC_add_inst (
        .PC_in(PC),
        .desvio(imediato_destino),
        .halts(halts_sign),
        .PC_out(PC),
        .PC_desvio(PC_desvio)
    );

    and and_jump_inst (
        .sign1(Branch),
        .sign2(branch_taken),
        .branch(branch)
    );

    mux_pc mux_pc_inst (
        .sign(branch),
        .addr1(PC),
        .addr2(PC_desvio),
        .PC(PC)
    );

endmodule