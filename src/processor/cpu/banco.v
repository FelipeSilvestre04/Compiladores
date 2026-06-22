module banco (
    input         clk,         // Clock
    input         we,          // Write Enable (habilita escrita)
    input  [5:0]  rs1_addr,    // Endereço do registrador fonte 1 
    input  [5:0]  rs2_addr,    // Endereço do registrador fonte 2
    input  [5:0]  rd_addr,     // Endereço do registrador destino
    input  [31:0] rd_data,     // Dados a serem escritos
    output [31:0] rs1_data,    // Dados lidos do registrador fonte 1
    output [31:0] rs2_data     // Dados lidos do registrador fonte 2
);

    // Array de 64 registradores de 32 bits cada
    reg [31:0] registradores [0:63];
    
    // Escrita síncrona
    always @(posedge clk) begin
        if (we) begin
            if (rd_addr != 6'b0) begin  // r0 sempre é 0 
                registradores[rd_addr] <= rd_data;
            end
        end
    end
    
  
    // Registrador r0 sempre retorna 0
    assign rs1_data = (rs1_addr == 6'b0) ? 32'b0 : registradores[rs1_addr];
    assign rs2_data = (rs2_addr == 6'b0) ? 32'b0 : registradores[rs2_addr];

endmodule