// PC.txt - Versão correta sem reset externo
module PC (
    input  wire       clk,
    input  [31:0]    PC_in,
    input  wire       halt,
    output [31:0]    PC_out
);
    reg [31:0] PC_reg = 32'h00000000; // Auto-inicialização em 0

    always @(negedge clk) begin
        if (!halt) begin
            PC_reg <= PC_in;
        end
    end
    assign PC_out = PC_reg;
endmodule