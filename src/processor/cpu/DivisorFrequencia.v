// Divisor de Frequência - Versão Simplificada SEM RESET para teste
module DivisorFrequencia (
    input  clk50,
    output reg clkSaida
);
    reg [24:0] contador = 0;

    always @(posedge clk50) begin
        if (contador == 50) begin
            contador <= 0;
            clkSaida <= ~clkSaida;
        end
        else begin
            contador <= contador + 1;
        end
    end
endmodule