import sys

# --- TABELAS DA ISA (Opcodes e Functs conforme especificação) ---
OPCODES = {"R":"000", "I":"001", "J":"010", "B":"011", "N":"100", "IO":"110"}

# Mapeamento: instrucao -> (Tipo_ISA, Funct_bits)
INSTRUCTIONS = {
    "add":  ("R", "0000"), "sub":  ("R", "0001"), "mult": ("R", "0010"), "div":  ("R", "0011"),
    "and":  ("R", "0100"), "or":   ("R", "0101"), "xor":  ("R", "0110"), "not":  ("R", "0111"),
    "load": ("I", "0000"), "store":("I", "0001"), "addi": ("I", "0010"), "subi": ("I", "0011"),
    "andi": ("I", "0100"), "ori":  ("I", "0101"), "xori": ("I", "0110"), "lda":  ("I", "0111"),
    "mov":  ("I", "1000"),
    "jump": ("J", "0000"), "jr":   ("J", "0001"), "jal":  ("J", "0010"),
    "beq":  ("B", "0000"), "bne":  ("B", "0001"), "blt":  ("B", "0010"), "ble":  ("B", "0011"),
    "bgt":  ("B", "0100"), "bge":  ("B", "0101"),
    "nop":  ("N", "0000"), "halt": ("N", "0001"),
    "in":   ("IO", "0000"),"out":  ("IO", "0001")
}

# --- FUNÇÕES AUXILIARES DE BITS ---
def get_reg(name):
    """Converte 'x5' em '000101' (6 bits)."""
    if not name.startswith("x"): return "000000"
    return format(int(name[1:]), "06b")

def get_imm(val, bits):
    """Converte número em string binária de N bits (suporta negativos)."""
    val = int(val)
    if val < 0: val = (1 << bits) + val # Complemento de 2
    return format(val & ((1 << bits) - 1), f"0{bits}b")

# --- O ASSEMBLER ---
def run_assembler():
    asm_file = sys.argv[1] if len(sys.argv) > 1 else "saida.asm"
    
    try:
        with open(asm_file, "r") as f:
            raw_lines = f.readlines()
    except:
        print(f"Erro ao abrir {asm_file}"); return

    # --- PASSAGEM 1: RÓTULOS (LABELS) ---
    labels = {}
    executable_lines = []
    pc = 0
    for line in raw_lines:
        line = line.split("#")[0] # Remove comentários
        line = line.replace(",", " ").replace("(", " ").replace(")", " ").strip()
        if not line: continue
        
        if line.endswith(":"):
            labels[line[:-1]] = pc
        else:
            executable_lines.append(line)
            pc += 1

    # --- PASSAGEM 2: GERAÇÃO DE BITS (O "SWITCH-CASE" FINAL) ---
    binary_program = []
    for pc, line in enumerate(executable_lines):
        parts = line.split()
        instr = parts[0].lower()
        
        if instr not in INSTRUCTIONS:
            print(f"Erro: instrucao '{instr}' desconhecida."); continue
            
        isa_type, funct = INSTRUCTIONS[instr]
        op_code = OPCODES[isa_type]
        bits_32 = ""

        # TIPO R: null(7) | rs2(6) | rs1(6) | rd(6) | funct(4) | opcode(3)
        if isa_type == "R":
            rd  = get_reg(parts[1])
            rs1 = get_reg(parts[2])
            rs2 = get_reg(parts[3]) if len(parts) > 3 else "000000"
            bits_32 = "0"*7 + rs2 + rs1 + rd + funct + op_code

        # TIPO I: imm(13) | rs1(6) | rd(6) | funct(4) | opcode(3)
        elif isa_type == "I":
            rd  = get_reg(parts[1])
            if instr in ["load", "store"]:
                imm_bits = get_imm(parts[2], 13); rs1 = get_reg(parts[3])
            elif instr in ["mov", "not"]:
                imm_bits = "0"*13; rs1 = get_reg(parts[2])
            elif instr == "lda":
                imm_bits = get_imm(labels.get(parts[2], 0), 13); rs1 = "000000"
            else: # addi, subi, andi, etc.
                rs1 = get_reg(parts[2]); imm_bits = get_imm(parts[3], 13)
            bits_32 = imm_bits + rs1 + rd + funct + op_code

        # TIPO J: imm(19) | rd(6) | funct(4) | opcode(3)
        elif isa_type == "J":
            if   instr == "jump": rd = "000000"; imm_bits = get_imm(labels.get(parts[1], 0), 19)
            elif instr == "jal":  rd = get_reg(parts[1]); imm_bits = get_imm(labels.get(parts[2], 0), 19)
            elif instr == "jr":   rd = get_reg(parts[1]); imm_bits = "0"*19
            bits_32 = imm_bits + rd + funct + op_code

        # TIPO B: imm(13) | rs1(6) | rd(6) | funct(4) | opcode(3)
        elif isa_type == "B":
            rs1 = get_reg(parts[1]); rd = get_reg(parts[2])
            imm_bits = get_imm(labels.get(parts[3], 0), 13)
            bits_32 = imm_bits + rs1 + rd + funct + op_code

        # TIPO N: null(25) | funct(4) | opcode(3)
        elif isa_type == "N":
            bits_32 = "0"*25 + funct + op_code

        # TIPO IO: null(19) | rd/rs1(6) | funct(4) | opcode(3)
        elif isa_type == "IO":
            reg = get_reg(parts[1])
            bits_32 = "0"*19 + reg + funct + op_code

        binary_program.append(bits_32)

    # --- SALVAR RESULTADO ---
    with open("programa.txt", "w") as f_out:
        for b in binary_program: f_out.write(f"{b}\n")
    
    print(f"Sucesso! {len(binary_program)} instrucoes geradas em 'programa.txt'.")

if __name__ == "__main__":
    run_assembler()
