// Módulo para converter um número de 4 bits (0-9) para o sinal de 7 segmentos.
// Assume um display de anodo comum (1 = apagado, 0 = aceso).
module Decode7seg(
    input  [3:0] entrada, // Dígito em binário (0000 a 1001)
    output reg [6:0] saida   // Saída para o display (g,f,e,d,c,b,a)
);

    always @(*) begin
        case(entrada)
            4'd0: saida = 7'b1000000; // 0
            4'd1: saida = 7'b1111001; // 1
            4'd2: saida = 7'b0100100; // 2
            4'd3: saida = 7'b0110000; // 3
            4'd4: saida = 7'b0011001; // 4
            4'd5: saida = 7'b0010010; // 5
            4'd6: saida = 7'b0000010; // 6
            4'd7: saida = 7'b1111000; // 7
            4'd8: saida = 7'b0000000; // 8
            4'd9: saida = 7'b0010000; // 9
            default: saida = 7'b1111111; // Apagado
        endcase
    end
endmodule