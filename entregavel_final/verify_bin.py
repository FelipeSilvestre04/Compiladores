import sys
import os

# Custom ISA Specifications
OPCODES = {
    "000": "R",
    "001": "I",
    "010": "J",
    "011": "B",
    "100": "N",
    "110": "IO"
}

R_FUNCTS = {
    "0000": "ADD",
    "0001": "SUB",
    "0010": "MULT",
    "0011": "DIV",
    "0100": "AND",
    "0101": "OR",
    "0110": "XOR",
    "0111": "NOT"
}

I_FUNCTS = {
    "0000": "LOAD",
    "0001": "STORE",
    "0010": "ADDI",
    "0011": "SUBI",
    "0100": "ANDI",
    "0101": "ORI",
    "0110": "XORI",
    "0111": "LDA",
    "1000": "MOV"
}

J_FUNCTS = {
    "0000": "JUMP",
    "0001": "JR",
    "0010": "JAL"
}

B_FUNCTS = {
    "0000": "BEQ",
    "0001": "BNE",
    "0010": "BLT",
    "0011": "BLE",
    "0100": "BGT",
    "0101": "BGE"
}

N_FUNCTS = {
    "0000": "NOP",
    "0001": "HALT"
}

IO_FUNCTS = {
    "0000": "IN",
    "0001": "OUT",
    "0010": "STORE_STACK",
    "0011": "LOAD_STACK"
}

def map_reg(reg_val):
    if reg_val == 0:
        return "$zero"
    elif reg_val == 1:
        return "$ra"
    elif reg_val == 2:
        return "$sp"
    elif reg_val == 3:
        return "$at"
    else:
        return f"$t{reg_val - 4}"

def to_signed(val, bits):
    if val & (1 << (bits - 1)):
        return val - (1 << bits)
    return val

def disassemble_instruction(binary_str, pc):
    binary_str = binary_str.strip()
    if len(binary_str) != 32:
        return f"Error: instruction line length is {len(binary_str)}, expected 32."
        
    opcode = binary_str[-3:]
    funct = binary_str[-7:-3]
    
    type_isa = OPCODES.get(opcode, "UNKNOWN")
    if type_isa == "UNKNOWN":
        return f"Error: Unknown opcode {opcode}"
        
    if type_isa == "R":
        # Format: null(7) | rs2(6) | rs1(6) | rd(6) | funct(4) | opcode(3)
        rs2_val = int(binary_str[7:13], 2)
        rs1_val = int(binary_str[13:19], 2)
        rd_val = int(binary_str[19:25], 2)
        
        op_name = R_FUNCTS.get(funct, f"R_UNKNOWN_{funct}")
        rd = map_reg(rd_val)
        rs1 = map_reg(rs1_val)
        rs2 = map_reg(rs2_val)
        
        return f"{op_name} {rd}, {rs1}, {rs2}"
        
    elif type_isa == "I":
        # Format: imm(13) | rs1(6) | rd(6) | funct(4) | opcode(3)
        imm_val = to_signed(int(binary_str[0:13], 2), 13)
        rs1_val = int(binary_str[13:19], 2)
        rd_val = int(binary_str[19:25], 2)
        
        op_name = I_FUNCTS.get(funct, f"I_UNKNOWN_{funct}")
        rd = map_reg(rd_val)
        rs1 = map_reg(rs1_val)
        
        if op_name == "STORE":
            # For STORE, decoder treats rw/rd field (bits 12..7) as rs2 source
            # So the assembler stored rs2 value in rd_val.
            return f"STORE {rd}, {imm_val}({rs1})"
        elif op_name == "LOAD":
            return f"LOAD {rd}, {imm_val}({rs1})"
        elif op_name in ["MOV", "NOT"]:
            return f"{op_name} {rd}, {rs1}"
        elif op_name == "LDA":
            return f"LDA {rd}, {imm_val}"
        else:
            return f"{op_name} {rd}, {rs1}, {imm_val}"
            
    elif type_isa == "J":
        # Format: imm(19) | rd(6) | funct(4) | opcode(3)
        imm_val = to_signed(int(binary_str[0:19], 2), 19)
        rd_val = int(binary_str[19:25], 2)
        
        op_name = J_FUNCTS.get(funct, f"J_UNKNOWN_{funct}")
        rd = map_reg(rd_val)
        
        if op_name == "JUMP":
            target_pc = pc + 1 + imm_val
            return f"JUMP {target_pc}  # (offset={imm_val})"
        elif op_name == "JAL":
            target_pc = pc + 1 + imm_val
            return f"JAL {rd}, {target_pc}  # (offset={imm_val})"
        elif op_name == "JR":
            return f"JR {rd}"
            
    elif type_isa == "B":
        # Format: imm(13) | rs2(6) | rs1(6) | funct(4) | opcode(3)
        imm_val = to_signed(int(binary_str[0:13], 2), 13)
        rs2_val = int(binary_str[13:19], 2)
        rs1_val = int(binary_str[19:25], 2)
        
        op_name = B_FUNCTS.get(funct, f"B_UNKNOWN_{funct}")
        rs1 = map_reg(rs1_val)
        rs2 = map_reg(rs2_val)
        target_pc = pc + 1 + imm_val
        
        return f"{op_name} {rs1}, {rs2}, {target_pc}  # (offset={imm_val})"
        
    elif type_isa == "N":
        # Format: null(25) | funct(4) | opcode(3)
        op_name = N_FUNCTS.get(funct, f"N_UNKNOWN_{funct}")
        return f"{op_name}"
        
    elif type_isa == "IO":
        # Format: null(19) | rd/rs1(6) | funct(4) | opcode(3)
        reg_val = int(binary_str[19:25], 2)
        reg = map_reg(reg_val)
        
        op_name = IO_FUNCTS.get(funct, f"IO_UNKNOWN_{funct}")
        return f"{op_name} {reg}"

def verify_file(file_path):
    if not os.path.exists(file_path):
        print(f"Error: {file_path} not found.")
        return False
        
    print(f"\n=======================================================")
    print(f" VERIFYING BINARY FILE: {file_path}")
    print(f"=======================================================")
    
    with open(file_path, "r") as f:
        lines = [line.strip() for line in f if line.strip()]
        
    print(f"Total instructions found: {len(lines)}")
    print(f"{'PC':<4} | {'Binary Instruction':<32} | {'Decoded Instruction'}")
    print("-" * 90)
    
    success = True
    for pc, line in enumerate(lines):
        decoded = disassemble_instruction(line, pc)
        if "Error:" in decoded:
            success = False
        print(f"{pc:<4} | {line:<32} | {decoded}")
        
    if success:
        print(f"-------------------------------------------------------")
        print(f"[OK] Binary verification completed successfully!")
    else:
        print(f"-------------------------------------------------------")
        print(f"[ERROR] Verification failed due to decoding errors.")
        
    return success

if __name__ == "__main__":
    target = sys.argv[1] if len(sys.argv) > 1 else "programa.txt"
    verify_file(target)
