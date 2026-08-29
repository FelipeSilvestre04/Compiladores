// Módulo ControleSinal corrigido para botão ATIVO-BAIXO
module ControleSinal(
    input in, 
    input btn, 
    output reg saida = 1'b0
);
    // Agora sensível à borda de DESCIDA do botão
    always @(negedge btn or negedge in) begin
        if(!in) begin
            saida <= 1'b0; // Reseta a saída quando a instrução IN termina
        end
        else begin 
            // Se 'in' estiver ativo e o botão for pressionado (borda de descida),
            // a saída vai para 1.
            saida <= 1'b1;
        end
    end
endmodule
