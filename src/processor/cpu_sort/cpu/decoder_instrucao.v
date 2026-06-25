// Decoder combinacional das instrucoes de 32 bits da ISA custom.
module decoder_instrucao(
    input  [31:0] instrucao,

    output reg [5:0]  rs1,
    output reg [5:0]  rs2,
    output reg [5:0]  rw,
    output reg [2:0]  op,
    output reg [3:0]  funct,
    output reg [12:0] imediato_I,
    output reg [18:0] imediato_J
);

    always @(*) begin
        rs1        = 6'b0;
        rs2        = 6'b0;
        rw         = 6'b0;
        imediato_I = 13'b0;
        imediato_J = 19'b0;

        op    = instrucao[2:0];
        funct = instrucao[6:3];

        case (instrucao[2:0])
            // R: null(7) | rs2(6) | rs1(6) | rw(6) | funct(4) | op(3)
            3'b000: begin
                rw  = instrucao[12:7];
                rs1 = instrucao[18:13];
                rs2 = instrucao[24:19];
            end

            // I: imm(13) | rs1(6) | rw/rs2(6) | funct(4) | op(3)
            3'b001: begin
                rs1        = instrucao[18:13];
                imediato_I = instrucao[31:19];

                if (instrucao[6:3] == 4'b0001) begin
                    rs2 = instrucao[12:7]; // STORE usa este campo como fonte.
                end else begin
                    rw = instrucao[12:7];
                end
            end

            // J: imm(19) | rw(6) | funct(4) | op(3)
            3'b010: begin
                rw         = instrucao[12:7];
                imediato_J = instrucao[31:13];
            end

            // B: imm(13) | rs2(6) | rs1(6) | funct(4) | op(3)
            3'b011: begin
                rs1        = instrucao[12:7];
                rs2        = instrucao[18:13];
                imediato_I = instrucao[31:19];
            end

            // IO: null(19) | rw/rs1(6) | funct(4) | op(3)
            3'b110: begin
                case (instrucao[6:3])
                    4'b0000: rw  = instrucao[12:7]; // IN rd
                    4'b0001: rs1 = instrucao[12:7]; // OUT rs1
                    4'b0010: rs1 = instrucao[12:7]; // STORE_STACK rs1
                    4'b0011: rw  = instrucao[12:7]; // LOAD_STACK rd
                endcase
            end
        endcase
    end

endmodule
