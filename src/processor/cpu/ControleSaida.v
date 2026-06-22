// Módulo sequencial que controla os 8 displays e "lembra" o último valor.
module ControleSaida(
    input        clk,         // <<< ADICIONADO: Conectar ao clock lento da CPU
    input        enable,      // Ativa a ATUALIZAÇÃO do display
    input [31:0] data_in,     // Dado a ser exibido
    output [6:0] Hex0,
    output [6:0] Hex1,
    output [6:0] Hex2,
    output [6:0] Hex3,
    output [6:0] Hex4,
    output [6:0] Hex5,
    output [6:0] Hex6,
    output [6:0] Hex7
);

    // <<< ADICIONADO: Registrador para armazenar o valor a ser exibido >>>
    // Ele manterá o valor mesmo quando 'enable' for para 0.
    reg [31:0] valor_exibido = 0;

    // <<< ADICIONADO: Lógica sequencial para "lembrar" o dado >>>
    // Na borda de subida do clock, se 'enable' estiver ativo,
    // o registrador interno captura o novo valor de 'data_in'.
    always @(posedge clk) begin
        if (enable) begin
            valor_exibido <= data_in;
        end
    end

    // Fios para os dígitos decimais.
    wire [3:0] digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7;

    // <<< ALTERADO: A lógica de extração de dígitos agora usa o registrador 'valor_exibido' >>>
    assign digit0 = (valor_exibido / 1) % 10;
    assign digit1 = (valor_exibido / 10) % 10;
    assign digit2 = (valor_exibido / 100) % 10;
    assign digit3 = (valor_exibido / 1000) % 10;
    assign digit4 = (valor_exibido / 10000) % 10;
    assign digit5 = (valor_exibido / 100000) % 10;
    assign digit6 = (valor_exibido / 1000000) % 10;
    assign digit7 = (valor_exibido / 10000000) % 10;
    
    // Fios para os sinais decodificados.
    wire [6:0] s0, s1, s2, s3, s4, s5, s6, s7;

    // Instâncias do decodificador (sem alteração)
    Decode7seg D0 (.entrada(digit0), .saida(s0));
    Decode7seg D1 (.entrada(digit1), .saida(s1));
    Decode7seg D2 (.entrada(digit2), .saida(s2));
    Decode7seg D3 (.entrada(digit3), .saida(s3));
    Decode7seg D4 (.entrada(digit4), .saida(s4));
    Decode7seg D5 (.entrada(digit5), .saida(s5));
    Decode7seg D6 (.entrada(digit6), .saida(s6));
    Decode7seg D7 (.entrada(digit7), .saida(s7));

    // <<< ALTERADO: A lógica de exibição agora depende apenas do valor armazenado >>>
    // Uma vez que um valor é salvo, ele permanece nos displays.
    assign Hex0 = (valor_exibido >= 0)          ? s0 : 7'b1111111;
    assign Hex1 = (valor_exibido >= 10)         ? s1 : 7'b1111111;
    assign Hex2 = (valor_exibido >= 100)        ? s2 : 7'b1111111;
    assign Hex3 = (valor_exibido >= 1000)       ? s3 : 7'b1111111;
    assign Hex4 = (valor_exibido >= 10000)      ? s4 : 7'b1111111;
    assign Hex5 = (valor_exibido >= 100000)     ? s5 : 7'b1111111;
    assign Hex6 = (valor_exibido >= 1000000)    ? s6 : 7'b1111111;
    assign Hex7 = (valor_exibido >= 10000000)   ? s7 : 7'b1111111;

endmodule