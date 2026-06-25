// MUX de 4 para 1 que seleciona o dado a ser escrito no banco de registradores.
module mux_memoria (
    input [1:0]  sign,          // Sinal de seleção. Conectar ao MemtoReg da UC.

    // As 4 fontes de dados
    input [31:0] ula_result,    // [00] Resultado da ULA
    input [31:0] mem_result,    // [01] Dado lido da memória RAM
    input [31:0] pc_next,       // [10] Endereço PC+1 (para JAL)
    input [31:0] io_input_data, // [11] Dado lido dos switches (para IN)

    output reg [31:0] rd_data  // Saída selecionada
);

    always @(*) begin
        case(sign)
            2'b00:  rd_data = ula_result;    // Seleciona resultado da ULA
            2'b01:  rd_data = mem_result;    // Seleciona resultado da Memória
            2'b10:  rd_data = pc_next;       // Seleciona PC+1
            2'b11:  rd_data = io_input_data; // Seleciona dado do I/O
            default: rd_data = 32'b0;
        endcase
    end

endmodule
