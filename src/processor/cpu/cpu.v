// Módulo CPU - Top-Level com feedback visual para a entrada
module cpu (
    input        clk_50,
    input        rst,
    input [17:0] switches,
    input        btn_in,
	 output led_clock,
    
    output [6:0] Hex0,
    output [6:0] Hex1,
    output [6:0] Hex2,
    output [6:0] Hex3,
    output [6:0] Hex4,
    output [6:0] Hex5,
    output [6:0] Hex6,
    output [6:0] Hex7,
	 
	 output [5:0] switches_leds,
	 
	 output btn_out,
	 
	 output in_sign_out
);

    // <<< ADICIONADO: Novos fios para a lógica do display >>>
    wire [31:0] display_data_muxed;
    wire        final_display_enable;

    // --- Sinais Internos do Processador (Datapath) ---
    wire [31:0] PC;
    wire [31:0] PC_next;
    wire [31:0] PC_desvio;
    wire [31:0] instrucao;
    wire [5:0]  rs1, rs2, rw;
    wire [2:0]  op;
    wire [3:0]  funct;
    wire [12:0] imediato_I;
    wire [18:0] imediato_J;
    wire [31:0] rd_data, rs1_data, rs2_data;
    wire [31:0] ula_result;
    wire [31:0] rd;             
    wire [31:0] imediato_I_ex; 
    wire [31:0] imediato_J_ex; 
    wire [31:0] imediato_destino;
    wire [31:0] PC_final; 
    wire [31:0] endereco_alvo_salto;
    wire [31:0] proximo_pc_logico;
    wire [31:0] Reg2Ula;
    wire [5:0]  rs1_real;

    // --- Sinais de Controle ---
    wire Jump, JR, Branch, MemRead, MemWrite, ALUSrc, RegWrite, JumpAbs, Halt;
    wire [1:0] MemtoReg;
    wire [3:0] ALUop;
    wire branch_taken;
    wire sinal_desvio, branch;
    wire clk;
    wire STORE_STACK_en, LOAD_STACK_en; // <<< SINAIS DE PILHA
    
    // --- Sinais para Lógica de I/O ---
    wire        IN_signal;         
    wire        WriteToIO;         
    wire        io_read_strobe;    
    wire        stall_for_input;   
    wire        effective_halt;    
    wire [17:0] switch_data;       
    wire [31:0] switch_data_extended;
    wire [31:0] io_data_out;       
    wire        io_write_enable;   

    //-----------------------------------------------------
    //--- INÍCIO DO DATAPATH E CONTROLE DO PROCESSADOR ---
    //-----------------------------------------------------
    
    // <<< MUDANÇA: O nome do módulo PLL/Divisor deve ser o que o Quartus gerou >>>
    DivisorFrequencia Divisor_inst (
        .clk50(clk_50),
        .clkSaida(clk)   
    );

	 assign led_clock = clk;
	 assign btn_out = ~btn_in;
	 assign in_sing_out = IN_signal;
	 
    PC PC_inst (
        .clk(clk),
        .PC_in(endereco_alvo_salto),
        .PC_out(PC),
        .halt(effective_halt)
    );

    rom ROM (
        .addr(PC),
        .clk(clk),
        .q(instrucao)
    );

    decoder_instrucao decoder (
        .instrucao(instrucao),
        .rs1(rs1), .rs2(rs2), .rw(rw),
        .op(op), .funct(funct),
        .imediato_I(imediato_I), .imediato_J(imediato_J)
    );

    assign imediato_I_ex = 32'b0 + imediato_I;
    assign imediato_J_ex = 32'b0 + imediato_J;

    Unidade_Controle UC (
        .op(op), .funct(funct),
        .Jump(Jump), .Branch(Branch), .MemRead(MemRead), .MemtoReg(MemtoReg),
        .ALUop(ALUop), .MemWrite(MemWrite), .ALUSrc(ALUSrc), .RegWrite(RegWrite),
        .JR(JR), .JumpAbs(JumpAbs), .Halt(Halt),
        .WriteToIO(WriteToIO),
        .IN_signal(IN_signal),
        .STORE_STACK_en(STORE_STACK_en),
        .LOAD_STACK_en(LOAD_STACK_en)
    );
    
    assign switch_data = IN_signal ? switches : 18'b0;
    assign switch_data_extended = {14'b0, switch_data};
	 
	 assign switches_leds = switches[5:0];

    ControleSinal io_signal_control (
        .in(IN_signal),
        .btn(btn_in),
        .saida(io_read_strobe)
    );

    assign stall_for_input = IN_signal & !io_read_strobe;
    assign effective_halt = Halt | stall_for_input;

    assign rs1_real	= (JR == 1'b1) ? rw : rs1;

    banco banco_inst (
        .clk(clk), .we(RegWrite),
        .rs1_addr(rs1_real), .rs2_addr(rs2), .rd_addr(rw),
        .rd_data(rd_data),
        .rs1_data(rs1_data), .rs2_data(rs2_data)
    );

    mux_ula mux_ula_inst (
        .sign(ALUSrc), .rs2(rs2_data), .im(imediato_I_ex), .reg_saida(Reg2Ula)
    );

    ula ula_inst (
        .rs1(rs1_data), .rs2(Reg2Ula), .op(ALUop), .branch_en(Branch),
        .rd(ula_result), .branch_taken(branch_taken)
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
        .sign(Jump), .im1(imediato_J_ex), .im2(imediato_I_ex), .im(imediato_destino)
    );

    assign PC_next = PC + 1;
    assign PC_desvio = PC_next + imediato_destino;
    assign branch = branch_taken & Branch;
    assign sinal_desvio = Jump | branch;

    mux_pc mux_pc_inst (
        .sign(sinal_desvio), .addr1(PC_next), .addr2(PC_desvio), .PC(PC_final)
    );

    assign proximo_pc_logico = (JumpAbs == 1'b1) ? imediato_J_ex : ((JR == 1'b1) ? rs1_data : PC_final);
    assign endereco_alvo_salto = (Halt == 1'b1) ? PC : proximo_pc_logico;
    
    // --- Lógica de Saída ---
    assign io_data_out = rs1_data;
    assign io_write_enable = WriteToIO;

    // <<< ADICIONADO: Lógica do MUX do Display >>>
    // Se o processador estiver parado esperando a entrada (stall_for_input = 1),
    // mostre o valor dos switches em tempo real. Caso contrário, mostre o valor da instrução OUT.
    assign display_data_muxed = stall_for_input ? switch_data_extended : io_data_out;

    // O display deve estar ativo durante uma instrução OUT OU enquanto espera pela entrada.
    assign final_display_enable = io_write_enable | stall_for_input;


    // <<< ALTERADO: Instância do display agora usa os novos sinais muxados >>>
// em cpu.txt
    ControleSaida display_controller (
        .clk(clk), // <<< ADICIONADO: Conecta o clock lento da CPU
        .enable(final_display_enable),
        .data_in(display_data_muxed),
        .Hex0(Hex0), .Hex1(Hex1), .Hex2(Hex2), .Hex3(Hex3),
        .Hex4(Hex4), .Hex5(Hex5), .Hex6(Hex6), .Hex7(Hex7)
    );
    
endmodule