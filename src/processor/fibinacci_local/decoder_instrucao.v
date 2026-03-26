// Módulo Decoder: Decodifica a instrução de 32 bits em seus campos constituintes.
module decoder_instrucao(
    // Entrada
    input  [31:0] instrucao,

    // Saídas para os outros módulos
    output reg [5:0]  rs1, 
    output reg [5:0]  rs2,
    output reg [5:0]  rw,         // Registrador de destino (rd)
    output reg [2:0]  op,
    output reg [3:0]  funct,
    output reg [12:0] imediato_I,
    output reg [18:0] imediato_J
);

    // Bloco combinacional para decodificar a instrução.
    always @(*) begin
        // Passo 1: Inicializa todas as saídas com 0 (boa prática para evitar latches).
        rs1        <= 6'b0;
        rs2        <= 6'b0;
        rw         <= 6'b0;
        
        
        imediato_I <= 13'b0;
        imediato_J <= 19'b0;

        // Extrai o opcode, que está sempre na mesma posição [2:0].
        op <= instrucao[2:0];
        funct <= instrucao[6:3];

        // Passo 2: Decodifica o resto da instrução com base no opcode.
        case(op)
            // Tipo R (opcode 000) - ADD, SUB, etc.
            // Formato assumido: | ... | rs2 | rs1 | rw/rd | funct | opcode |
            3'b000: begin
                funct <= instrucao[6:3];
                rw    <= instrucao[12:7];
                rs1   <= instrucao[18:13];
                rs2   <= instrucao[24:19];
            end

            // Tipo I (opcode 001) - ADDI, LOAD, STORE
            3'b001: begin
                funct      <= instrucao[6:3];
                rs1        <= instrucao[18:13];
                imediato_I <= instrucao[31:19];

                // --- AQUI ESTÁ A LÓGICA INTELIGENTE ---
                // Se a instrução for um STORE (funct = 0001)...
                if (funct == 4'b0001) begin
                    // ...trate o campo de destino (rd) como a segunda origem (rs2).
                    rs2 <= instrucao[12:7];
                     // Não há registrador de destino no STORE
                end
                // Para todas as outras instruções Tipo I...
                else begin
                    // ...trate o campo de destino (rd) normalmente.
                    rw  <= instrucao[12:7];
                    rs2 <= 6'b0; // Não há segunda origem (rs2)
                end
            end

            // Tipo J (opcode 010) - JUMP, JAL
            // Formato (Tabela 5): | imediato_J | rw/rd | funct | opcode |
            3'b010: begin
                funct      <= instrucao[6:3];
                rw         <= instrucao[12:7];
                imediato_J <= instrucao[31:13];
            end
            
            // Tipo B (opcode 011) - BEQ, BNE
            // Formato (Tabela 7 corrigida): | imediato_I | rs2 | rs1 | funct | opcode |
            3'b011: begin
                funct      <= instrucao[6:3];
                rs1        <= instrucao[12:7];
                rs2        <= instrucao[18:13];
                imediato_I <= instrucao[31:19];
            end
            
                       

        
				3'b110: begin
					 funct <= instrucao[6:3];
					 case(funct)
						  4'b0000: begin // IN rd
								rw <= instrucao[12:7];  // O campo é um destino
						  end
						  4'b0001: begin // OUT rs1
								rs1 <= instrucao[12:7]; // O campo é uma fonte
						  end
					 endcase
				end
            

        endcase
    end

endmodule