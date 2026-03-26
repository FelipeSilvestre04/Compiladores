// Módulo Unidade de Controle: Gera todos os sinais de controle para o datapath.
module Unidade_Controle(
    // Entradas
    input  [2:0] op,
    input  [3:0] funct,

    // Saídas de Controle
    output reg       Jump,
    output reg       Branch,
    output reg [1:0] MemtoReg,
    output reg [3:0] ALUop,
    output reg       MemWrite,
    output reg       ALUSrc,
    output reg       RegWrite,
	 output reg       MemRead,
	 output reg       JR,
	 output reg       JumpAbs,
	 output reg       Halt ,
	 output reg       WriteToIO, // <<< NOVA SAÍDA
	 output reg IN_signal
    // O sinal MemRead foi omitido pois a RAM implementada lê de forma assíncrona sempre.
);

    // Bloco combinacional que gera os sinais.
    always @(*) begin
        // Passo 1: Inicializa todos os sinais com um valor padrão "inativo".
        // Isso garante que nenhuma operação indesejada ocorra e previne latches.
        Jump     = 1'b0;
        JR     = 1'b0;
        Branch   = 1'b0;
        MemtoReg = 2'b00; // Padrão: seleciona resultado da ULA
        MemWrite = 1'b0;
        ALUSrc   = 1'b0; // Padrão: segunda entrada da ULA vem do registrador (rs2)
        RegWrite = 1'b0;
        JumpAbs  = 1'b0;
        Halt     = 1'b0;
        WriteToIO = 1'b0;
		  IN_signal = 1'b0;
        ALUop    = 4'bxxxx; // "Don't care" por padrão

        // Passo 2: Usa o opcode para determinar a classe da instrução.
        case(op)
            //---------------------------------------------------------
            // Tipo R (opcode 000) - Operações entre registradores
            //---------------------------------------------------------
            3'b000: begin
                RegWrite = 1'b1;   // Instruções Tipo R sempre escrevem um resultado.
                ALUSrc   = 1'b0;   // A segunda entrada da ULA é sempre um registrador (rs2).
                MemtoReg = 2'b00;  // O resultado a ser escrito vem sempre da ULA.
                ALUop    = funct;  // Para o Tipo R, o funct corresponde diretamente ao ALUop.
            end

            //---------------------------------------------------------
            // Tipo I (opcode 001) - Operações com imediato e memória
            //---------------------------------------------------------
            3'b001: begin
                ALUSrc = 1'b1; // Instruções Tipo I sempre usam o imediato como operando da ULA.
                case(funct)
                    // LOAD: rd = MEM[rs1 + imm]
                    4'b0000: begin
                        RegWrite = 1'b1;      // Escreve o dado lido no registrador.
                        MemtoReg = 2'b01;     // O dado a ser escrito vem da memória.
                        ALUop    = 4'b0000;   // A ULA deve somar para calcular o endereço.
                    end
                    // STORE: MEM[rs1 + imm] = rs2
                    4'b0001: begin
                        MemWrite = 1'b1;      // Habilita a escrita na memória.
                        ALUop    = 4'b0000;   // A ULA deve somar para calcular o endereço.
                        // RegWrite permanece 0.
                    end
                    // ADDI: rd = rs1 + imm
                    4'b0010: begin
                        RegWrite = 1'b1;
                        MemtoReg = 2'b00;     // O resultado vem da ULA.
                        ALUop    = 4'b0000;   // ULA deve somar.
                    end
                    // SUBI: rd = rs1 - imm
                    4'b0011: begin
                        RegWrite = 1'b1;
                        MemtoReg = 2'b00;
                        ALUop    = 4'b0001;   // ULA deve subtrair.
                    end
                    // ANDI, ORI, XORI
                    4'b0100: begin RegWrite = 1'b1; ALUop = 4'b0100; end // ANDI
                    4'b0101: begin RegWrite = 1'b1; ALUop = 4'b0101; end // ORI
                    4'b0110: begin RegWrite = 1'b1; ALUop = 4'b0110; end // XORI
                    // LOAD ADDRESS e MOV
                    4'b0111: begin RegWrite = 1'b1; ALUop = 4'b0000; end // LA (rs1=x0)
                    4'b1000: begin RegWrite = 1'b1; ALUop = 4'b0000; end // MOV (imm=0)
                endcase
            end

            //---------------------------------------------------------
            // Tipo J (opcode 010) - Saltos incondicionais
            //---------------------------------------------------------
            3'b010: begin
                Jump = 1'b1; // Todas as instruções Tipo J ativam o sinal de salto.
                case(funct)
                    // JUMP
                    4'b0000: begin 
                        // RegWrite permanece 0.
                    end
                    // JR 
                    4'b0001: begin 
                        JR = 1'b1;
                        
                    end
                    // JAL: rd = PC + 1
                    4'b0010: begin
                        RegWrite = 1'b1;      // Habilita a escrita do endereço de retorno.
                        MemtoReg = 2'b10;     // Seleciona PC+1 como dado a ser escrito.
                        
                    end
                    
                    // JMPL (Jump Label) <<< LÓGICA NOVA
                    4'b0011: begin
                        JumpAbs = 1'b1; // Ativa nosso novo sinal
                        Jump = 1'b0;    // Desativa o sinal de jump relativo para esta instrução
                    end
                    
                endcase
            end
            
            //---------------------------------------------------------
            // Tipo B (opcode 011) - Desvios condicionais
            //---------------------------------------------------------
            3'b011: begin
                Branch = 1'b1;   // Todas as instruções Tipo B ativam o sinal de branch.
                ALUSrc = 1'b0;   // A ULA sempre compara dois registradores.
                ALUop  = funct;  // O funct define o tipo de comparação na ULA.
                // RegWrite permanece 0.
            end
            
            //---------------------------------------------------------
            // Tipo N (opcode 100) - NOP e HALT
            //---------------------------------------------------------
            3'b100: begin
                case(funct)
                    // NOP: funct = 0000
                    4'b0000: begin
                        // Não fazemos NADA.
                        // Todos os sinais de controle (RegWrite, MemWrite, Jumps, etc.)
                        // permanecem em seus valores padrão inativos (0).
                        // O PC irá para PC+1 normalmente.
                    end
    
                    // HALT: funct = 0001
                    4'b0001: begin
                        Halt = 1'b1; // Ativa o sinal para parar o PC.
                    end
                endcase
            end
            
            // <<< CORRIGIDO: Lógica completa para o Tipo IO >>>
            3'b110: begin // Tipo IO
                case(funct)
                    // IN rd
                    4'b0000: begin 
                        IN_signal = 1'b1;     // ATIVA o sinal da instrução IN.
                        RegWrite  = 1'b1;     // Habilita a escrita do valor lido no registrador.
                        MemtoReg  = 2'b11;    // Seleciona o dado vindo dos switches no MUX de escrita.
                    end
                    // OUT rs1
                    4'b0001: begin 
                        WriteToIO = 1'b1;     // Ativa o sinal da instrução OUT.
                    end
                endcase
            end

        endcase
    end

endmodule