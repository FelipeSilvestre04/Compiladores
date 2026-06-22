module mux_pc(
    input  wire       sign,     // Sinal sinal_desvio
    input  [31:0]    addr1,    // PC_next (PC+1)
    input  [31:0]    addr2,    // PC_desvio
    output [31:0]    PC        // Saída para PC_final
);
    // Se sign=1 (desvio/salto), seleciona addr2. Senão, addr1.
    assign PC = (sign == 1'b1) ? addr2 : addr1;
endmodule