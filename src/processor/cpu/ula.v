module ula (
    input  signed [31:0] rs1,        // Operando 1 
    input  signed [31:0] rs2,        // Operando 2 
    input  [3:0]         op,         // Código da operação
    input                branch_en,  // Sinal de controle de branch
    output reg signed [31:0] rd,     // Resultado da operação aritmética/lógica 
    output reg           branch_taken// Resultado da comparação de branch
);

    

    always @(*) begin
       
        case (op)
            4'b0000: rd = rs1 + rs2;        // ADD
            4'b0001: rd = rs1 - rs2;        // SUB
            4'b0010: rd = rs1 * rs2;        // MULT
            4'b0011: rd = rs1 / rs2;        // DIV 
            4'b0100: rd = rs1 & rs2;        // AND 
            4'b0101: rd = rs1 | rs2;        // OR 
            4'b0110: rd = rs1 ^ rs2;        // XOR 
            4'b0111: rd = ~rs1;             // NOT
            default: rd = 32'b0;            // Padrão
        endcase
        
  
        if (branch_en) begin
            case (op)
                4'b0000: branch_taken = (rs1 == rs2);           // BEQ
                4'b0001: branch_taken = (rs1 != rs2);           // BNE
                4'b0010: branch_taken = (rs1 < rs2);            // BLT
                4'b0011: branch_taken = (rs1 <= rs2);           // BLE
                4'b0100: branch_taken = (rs1 > rs2);            // BGT 
                4'b0101: branch_taken = (rs1 >= rs2);           // BGE
                default: branch_taken = 1'b0;
            endcase
        end else begin
            branch_taken = 1'b0; // Branch não habilitado
        end
    end

endmodule

