

module cpu2 (
	 input [17:0] switches,
	 input btn_in,
    input  clk,
    input  rst,
    output [31:0] rd_data_test,
    output [31:0] ula_test,
    output [31:0] im_test,
    output [31:0] pc_test,
    
    // Outputs para monitoramento dos registradores
    output [5:0] rs1_out,
    output [5:0] rs2_out,
	 output [5:0] rd_out,
    output [31:0] rs1_data_out,
    output [31:0] rs2_data_out,

    // Outputs para monitoramento dos sinais de controle
    output Jump_out,
    output JR_out,
    output Branch_out,
    output MemRead_out,
    output [1:0] MemtoReg_out,
    output [3:0] ALUop_out,
    output MemWrite_out,
    output ALUSrc_out,
    output RegWrite_out,
	 
 
        // <<< NOVAS SAÍDAS PARA I/O >>>
    output [31:0] io_data_out,
    output        io_write_enable
	 
);
// Adicionar às portas do módulo cpu


// Adicionar aos fios (wires) internos
	wire IN_signal;
	wire io_read_strobe;
	wire stall_for_input;
	wire effective_halt;
	wire [17:0] switch_data;
	wire [31:0] switch_data_extended;

    wire [31:0] PC;
    wire [31:0] PC_next;
    wire WriteToIO;
    wire [31:0] PC_desvio;

    wire [31:0] instrucao;

    wire [5:0]  rs1, rs2, rw;
    wire [2:0]  op;
    wire [3:0]  funct;
    wire [12:0] imediato_I;
    wire [18:0] imediato_J;

    wire Jump;
    wire JR;
    wire Branch;
    wire MemRead;
    wire [1:0] MemtoReg;
    wire [3:0] ALUop;
    wire MemWrite;
    wire ALUSrc;
    wire RegWrite;
    wire branch;
    wire sinal_desvio;
    wire JumpAbs;
    wire Halt;
    wire STORE_STACK_en, LOAD_STACK_en; // <<< SINAIS DE PILHA

    wire [5:0] WriteRegister;
    wire [31:0] Reg2Ula;

    wire [31:0] rd_data, rs1_data, rs2_data;

    wire [31:0] ula_result;
    wire branch_taken;

    wire [31:0] rd;                 
    wire [31:0] imediato_I_ex; 
    wire [31:0] imediato_J_ex; 
    wire [31:0] imediato_destino;     
    wire        halts_sign;          
    wire [31:0] PC_final; 
    wire [31:0] endereco_alvo_salto;
    
    
		// Conecta diretamente os switches quando o sinal IN está ativo
	assign switch_data = IN_signal ? switches : 18'b0;

	// Estende o dado de 18 bits para 32 bits para o datapath
	assign switch_data_extended = {14'b0, switch_data};

    rom ROM (
        .addr(PC),
		  .clk(clk),
        .q(instrucao)
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

    assign imediato_I_ex = 32'b0 + imediato_I;
    assign imediato_J_ex = 32'b0 + imediato_J;

    Unidade_Controle UC (
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
        .JR(JR),
        .JumpAbs(JumpAbs),
        .Halt(Halt),
        .WriteToIO(WriteToIO),
        .IN_signal(IN_signal),
        .STORE_STACK_en(STORE_STACK_en),
        .LOAD_STACK_en(LOAD_STACK_en)
    );


	wire [5:0] rs1_real	= (JR == 1'b1) ? rw : rs1;
    

    banco banco_inst (
        .clk(clk),
        .we(RegWrite),
        .rs1_addr(rs1_real),
        .rs2_addr(rs2),
        .rd_addr(rw),
        .rd_data(rd_data),
        .rs1_data(rs1_data),
        .rs2_data(rs2_data)
    );

    mux_ula mux_ula_inst (
        .sign(ALUSrc),
        .rs2(rs2_data),
        .im(imediato_I_ex),
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

    // --- Controle do Stack Pointer (SP) ---
    reg [5:0] SP;
    wire rst_high = ~rst; // KEYs da placa física são ativas em nível baixo

    always @(posedge clk) begin
        if (rst_high) begin
            SP <= 6'd63; // Inicializa no topo da RAM
        end else if (STORE_STACK_en) begin
            SP <= SP - 6'd1;
        end else if (LOAD_STACK_en) begin
            SP <= SP + 6'd1;
        end
    end

    // --- Multiplexadores da RAM Compartilhada ---
    wire [5:0]  ram_read_addr  = (LOAD_STACK_en)  ? (SP + 6'd1) : ula_result[7:2];
    wire [5:0]  ram_write_addr = (STORE_STACK_en) ? SP          : ula_result[7:2];
    wire [31:0] ram_write_data = (STORE_STACK_en) ? rs1_data    : rs2_data;
    wire        ram_we         = MemWrite | STORE_STACK_en;

    ram #(.DATA_WIDTH(32), .ADDR_WIDTH(6)) ram_inst (
        .data(ram_write_data),
        .read_addr(ram_read_addr),
        .write_addr(ram_write_addr),
        .we(ram_we),
        .clk(clk),
        .q(rd)
    );

    mux_memoria mux_mem_inst (
        .sign(MemtoReg),
        .ula_result(ula_result),
        .mem_result(rd),
        .pc_next(PC_next),
        .io_input_data(switch_data_extended),
        .rd_data(rd_data)
    );

    mux_jump mux_jump_inst (
        .sign(Jump),
        .im1(imediato_J_ex),
        .im2(imediato_I_ex),
        .im(imediato_destino)
    );

    assign PC_next = PC + 1;
    assign PC_desvio = PC_next + imediato_destino;
    
  
    
    
    
    assign branch = branch_taken & Branch;
    

    assign sinal_desvio = Jump |   branch;
   

    mux_pc mux_pc_inst (
        .sign(sinal_desvio),
        .addr1(PC_next),
        .addr2(PC_desvio),
        .PC(PC_final)
    );
    



    // Fio intermediário que calcula o próximo PC com base na lógica de saltos
    wire [31:0] proximo_pc_logico = (JumpAbs == 1'b1) ? imediato_J_ex : ((JR == 1'b1) ? rs1_data : PC_final);
    
    // Lógica final: se Halt=1, o PC recebe seu próprio valor (congela). Senão, usa a lógica normal.
    assign endereco_alvo_salto = (Halt == 1'b1) ? PC : proximo_pc_logico;
	 
	 ControleSinal io_signal_control (
		 .in(IN_signal),      
		 .btn(btn_in),        
		 .saida(io_read_strobe)
	 );

	 // Lógica de Pausa (Stall) do PC
	 assign stall_for_input = IN_signal & !io_read_strobe;
	 assign effective_halt = Halt | stall_for_input;

    PC PC_inst (
        .clk(clk),
        .PC_in(endereco_alvo_salto),
        .PC_out(PC),
        .halt(effective_halt)
    );
    
    assign RegWrite_out = RegWrite;

    // <<< NOVAS ATRIBUIÇÕES PARA I/O >>>
    // O dado a ser exibido é o que está em rs1
    assign io_data_out = rs1_data;
    // O sinal que habilita a escrita externa é o nosso novo sinal de controle
    assign io_write_enable = WriteToIO;

	 assign rd_out = rw;
    assign rd_data_test = rd_data;
    assign pc_test = PC;
    assign ula_test = ula_result;
    assign im_test = imediato_I_ex;

    // Exportando rs1, rs2 e seus dados
    assign rs1_out = rs1;
    assign rs2_out = rs2;
    assign rs1_data_out = rs1_data;
    assign rs2_data_out = rs2_data;

    // Exportando sinais de controle
    assign Jump_out = Jump;
    assign JR_out = JR;
    assign Branch_out = Branch;
    assign MemRead_out = MemRead;
    assign MemtoReg_out = MemtoReg;
    assign ALUop_out = ALUop;
    assign MemWrite_out = MemWrite;
    assign ALUSrc_out = ALUSrc;
    assign RegWrite_out = RegWrite;

endmodule