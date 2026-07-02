import argparse
import os
import sys
from dataclasses import dataclass
from pathlib import Path


R_FUNCTS = {
    "0000": "ADD", "0001": "SUB", "0010": "MULT", "0011": "DIV",
    "0100": "AND", "0101": "OR", "0110": "XOR", "0111": "NOT",
}

I_FUNCTS = {
    "0000": "LOAD", "0001": "STORE", "0010": "ADDI", "0011": "SUBI",
    "0100": "ANDI", "0101": "ORI", "0110": "XORI", "0111": "LDA",
    "1000": "MOV",
}

J_FUNCTS = {
    "0000": "JUMP", "0001": "JR", "0010": "JAL", "0011": "JMPL",
}

B_FUNCTS = {
    "0000": "BEQ", "0001": "BNE", "0010": "BLT", "0011": "BLE",
    "0100": "BGT", "0101": "BGE",
}

N_FUNCTS = {
    "0000": "NOP", "0001": "HALT",
}

IO_FUNCTS = {
    "0000": "IN", "0001": "OUT", "0010": "STORE_STACK", "0011": "LOAD_STACK",
}

DIGITS = {
    "0": [" _ ", "| |", "|_|"],
    "1": ["   ", "  |", "  |"],
    "2": [" _ ", " _|", "|_ "],
    "3": [" _ ", " _|", " _|"],
    "4": ["   ", "|_|", "  |"],
    "5": [" _ ", "|_ ", " _|"],
    "6": [" _ ", "|_ ", "|_|"],
    "7": [" _ ", "  |", "  |"],
    "8": [" _ ", "|_|", "|_|"],
    "9": [" _ ", "|_|", " _|"],
    "-": ["   ", " _ ", "   "],
    " ": ["   ", "   ", "   "],
}


@dataclass
class Decoded:
    rs1: int = 0
    rs2: int = 0
    rw: int = 0
    op: int = 0
    funct: int = 0
    imediato_i: int = 0
    imediato_j: int = 0


@dataclass
class Control:
    Jump: int = 0
    Branch: int = 0
    MemtoReg: int = 0
    ALUop: int = 0
    MemWrite: int = 0
    ALUSrc: int = 0
    RegWrite: int = 0
    MemRead: int = 0
    JR: int = 0
    JumpAbs: int = 0
    Halt: int = 0
    WriteToIO: int = 0
    IN_signal: int = 0
    STORE_STACK_en: int = 0
    LOAD_STACK_en: int = 0


def u32(val):
    return val & 0xFFFFFFFF


def to_signed(val, bits):
    if val & (1 << (bits - 1)):
        return val - (1 << bits)
    return val


def to_signed_32(val):
    val &= 0xFFFFFFFF
    if val & 0x80000000:
        return val - 0x100000000
    return val


def sign_extend(val, bits):
    return u32(to_signed(val, bits))


def reg_name(reg):
    if reg == 0:
        return "$zero"
    if reg == 1:
        return "$ra"
    if reg == 2:
        return "$sp"
    if reg == 3:
        return "$at"
    return f"$t{reg - 4}"


def ram_addr_from_alu(alu_result):
    # Verilog usa ula_result[5:0]: a RAM e enderecada por palavra.
    return alu_result & 0x3F


def read_program(programa_path):
    if not os.path.exists(programa_path):
        raise FileNotFoundError(f"{programa_path} not found")

    with open(programa_path, "r", encoding="utf-8") as f:
        instructions = [line.strip() for line in f if line.strip()]

    for idx, inst in enumerate(instructions):
        if len(inst) != 32 or any(bit not in "01" for bit in inst):
            raise ValueError(f"Instrucao invalida na linha {idx + 1}: {inst!r}")

    return instructions


def bits(binary_str, high, low):
    # Indices no estilo Verilog: high..low inclusive.
    start = 31 - high
    end = 32 - low
    return int(binary_str[start:end], 2)


def decoder_instrucao(binary_str):
    inst = int(binary_str, 2)
    d = Decoded()
    d.op = inst & 0b111
    d.funct = (inst >> 3) & 0b1111

    if d.op == 0b000:  # R
        d.rw = bits(binary_str, 12, 7)
        d.rs1 = bits(binary_str, 18, 13)
        d.rs2 = bits(binary_str, 24, 19)
    elif d.op == 0b001:  # I
        d.rs1 = bits(binary_str, 18, 13)
        d.imediato_i = bits(binary_str, 31, 19)
        if d.funct == 0b0001:  # STORE
            d.rs2 = bits(binary_str, 12, 7)
        else:
            d.rw = bits(binary_str, 12, 7)
    elif d.op == 0b010:  # J
        d.rw = bits(binary_str, 12, 7)
        d.imediato_j = bits(binary_str, 31, 13)
    elif d.op == 0b011:  # B
        d.rs1 = bits(binary_str, 12, 7)
        d.rs2 = bits(binary_str, 18, 13)
        d.imediato_i = bits(binary_str, 31, 19)
    elif d.op == 0b110:  # IO
        if d.funct in (0b0000, 0b0011):  # IN / LOAD_STACK
            d.rw = bits(binary_str, 12, 7)
        elif d.funct in (0b0001, 0b0010):  # OUT / STORE_STACK
            d.rs1 = bits(binary_str, 12, 7)

    return d


def unidade_controle(op, funct):
    c = Control()

    if op == 0b000:  # R
        c.RegWrite = 1
        c.ALUop = funct
    elif op == 0b001:  # I
        c.ALUSrc = 1
        if funct == 0b0000:  # LOAD
            c.RegWrite = 1
            c.MemRead = 1
            c.MemtoReg = 0b01
            c.ALUop = 0b0000
        elif funct == 0b0001:  # STORE
            c.MemWrite = 1
            c.ALUop = 0b0000
        elif funct == 0b0010:  # ADDI
            c.RegWrite = 1
            c.ALUop = 0b0000
        elif funct == 0b0011:  # SUBI
            c.RegWrite = 1
            c.ALUop = 0b0001
        elif funct in (0b0100, 0b0101, 0b0110):  # ANDI, ORI, XORI
            c.RegWrite = 1
            c.ALUop = funct
        elif funct in (0b0111, 0b1000):  # LDA, MOV
            c.RegWrite = 1
            c.ALUop = 0b0000
    elif op == 0b010:  # J
        c.Jump = 1
        if funct == 0b0001:  # JR
            c.JR = 1
        elif funct == 0b0010:  # JAL
            c.RegWrite = 1
            c.MemtoReg = 0b10
        elif funct == 0b0011:  # JMPL
            c.JumpAbs = 1
            c.Jump = 0
    elif op == 0b011:  # B
        c.Branch = 1
        c.ALUop = funct
    elif op == 0b100:  # N
        if funct == 0b0001:
            c.Halt = 1
    elif op == 0b110:  # IO
        if funct == 0b0000:  # IN
            c.IN_signal = 1
            c.RegWrite = 1
            c.MemtoReg = 0b11
        elif funct == 0b0001:  # OUT
            c.WriteToIO = 1
        elif funct == 0b0010:  # STORE_STACK
            c.STORE_STACK_en = 1
        elif funct == 0b0011:  # LOAD_STACK
            c.LOAD_STACK_en = 1
            c.RegWrite = 1
            c.MemtoReg = 0b01

    return c


def ula(rs1, rs2, aluop, branch_en):
    a = to_signed_32(rs1)
    b = to_signed_32(rs2)

    if aluop == 0b0000:
        rd = a + b
    elif aluop == 0b0001:
        rd = a - b
    elif aluop == 0b0010:
        rd = a * b
    elif aluop == 0b0011:
        if b == 0:
            rd = 0
        else:
            sign = -1 if (a < 0) ^ (b < 0) else 1
            rd = sign * (abs(a) // abs(b))
    elif aluop == 0b0100:
        rd = a & b
    elif aluop == 0b0101:
        rd = a | b
    elif aluop == 0b0110:
        rd = a ^ b
    elif aluop == 0b0111:
        rd = ~a
    else:
        rd = 0

    branch_taken = 0
    if branch_en:
        if aluop == 0b0000:
            branch_taken = int(a == b)
        elif aluop == 0b0001:
            branch_taken = int(a != b)
        elif aluop == 0b0010:
            branch_taken = int(a < b)
        elif aluop == 0b0011:
            branch_taken = int(a <= b)
        elif aluop == 0b0100:
            branch_taken = int(a > b)
        elif aluop == 0b0101:
            branch_taken = int(a >= b)

    return u32(rd), branch_taken


def decode_for_display(decoded):
    funct_bits = f"{decoded.funct:04b}"
    if decoded.op == 0b000:
        return R_FUNCTS.get(funct_bits, "R_ERR"), f"{reg_name(decoded.rw)}, {reg_name(decoded.rs1)}, {reg_name(decoded.rs2)}"
    if decoded.op == 0b001:
        name = I_FUNCTS.get(funct_bits, "I_ERR")
        if name in ("LOAD", "STORE"):
            return name, f"{reg_name(decoded.rw or decoded.rs2)}, {to_signed(decoded.imediato_i, 13)}({reg_name(decoded.rs1)})"
        return name, f"{reg_name(decoded.rw)}, {reg_name(decoded.rs1)}, {to_signed(decoded.imediato_i, 13)}"
    if decoded.op == 0b010:
        name = J_FUNCTS.get(funct_bits, "J_ERR")
        if name == "JR":
            return name, reg_name(decoded.rw)
        return name, str(to_signed(decoded.imediato_j, 19))
    if decoded.op == 0b011:
        return B_FUNCTS.get(funct_bits, "B_ERR"), f"{reg_name(decoded.rs1)}, {reg_name(decoded.rs2)}, offset({to_signed(decoded.imediato_i, 13)})"
    if decoded.op == 0b100:
        return N_FUNCTS.get(funct_bits, "N_ERR"), ""
    if decoded.op == 0b110:
        return IO_FUNCTS.get(funct_bits, "IO_ERR"), reg_name(decoded.rw or decoded.rs1)
    return "DESCONHECIDO", ""


def print_7seg(val):
    is_neg = val < 0
    abs_val = abs(val)
    chars = []

    for i in range(8):
        threshold = 10 ** i
        if i == 0 or abs_val >= threshold:
            chars.append(str((abs_val // threshold) % 10))
        else:
            chars.append(" ")

    if is_neg:
        for idx in range(8):
            if chars[idx] == " ":
                chars[idx] = "-"
                break

    chars.reverse()
    lines = ["", "", ""]
    for char in chars:
        glyph = DIGITS.get(char, DIGITS[" "])
        lines[0] += glyph[0] + " "
        lines[1] += glyph[1] + " "
        lines[2] += glyph[2] + " "

    print("\n   [ DISPLAY DE 7 SEGMENTOS DA DE2-115 ]")
    print("   +---------------------------------------+")
    for line in lines:
        print(f"   | {line} |")
    print("   +---------------------------------------+")
    print(f"   Valor exibido: {val}\n")


def parse_inputs(value):
    if not value:
        return []
    return [int(part.strip()) for part in value.split(",") if part.strip()]


def trace_line(cycle, pc, fetch_pc, decoded, control, rs1_data, rs2_data, alu_result, branch_taken, rd_data, sp, effective_halt):
    name, details = decode_for_display(decoded)
    return (
        f"cycle={cycle:05d} pc={pc:03d} fetch={fetch_pc:03d} {name:<11} {details:<24} "
        f"rw={reg_name(decoded.rw):>4} rs1={reg_name(decoded.rs1):>4}:{to_signed_32(rs1_data):>5} "
        f"rs2={reg_name(decoded.rs2):>4}:{to_signed_32(rs2_data):>5} alu={to_signed_32(alu_result):>5} "
        f"bt={branch_taken} rd={to_signed_32(rd_data):>5} sp={sp:02d} "
        f"RW={control.RegWrite} MW={control.MemWrite} MT={control.MemtoReg} halt={effective_halt}"
    )


def run_simulation(
    programa_path,
    input_values=None,
    step_mode=False,
    max_steps=100000,
    rom_bits=8,
    quiet=False,
    trace=False,
    trace_limit=200,
    input_latency=0,
    output_latency=0,
):
    instructions = read_program(programa_path)
    input_values = list(input_values or [])
    input_index = 0
    pending_input = None
    pending_wait = 0
    pending_output_active = False
    pending_output_wait = 0
    output_emitted = False

    if not quiet:
        print("=" * 60)
        print("      SIMULADOR RTL-STYLE DA CPU AOC (DE2-115)")
        print("=" * 60)
        print(f"  Instrucoes carregadas: {len(instructions)}")
        print(f"  ROM simulada: {1 << rom_bits} palavras")

        if not step_mode and not input_values:
            print("  Pressione ENTER para executar tudo ou digite 's' para passo-a-passo.")
            mode = input("  Modo: ").strip().lower()
            step_mode = mode == "s"

    regs = [0] * 64
    ram = [0] * 64
    pc = 0
    sp = 63
    display_value = 0
    outputs = []
    steps = 0
    halted = False
    min_sp = sp
    rom_mask = (1 << rom_bits) - 1

    while steps < max_steps:
        fetch_pc = pc & rom_mask
        if fetch_pc >= len(instructions):
            print(f"ERRO: PC {pc} busca endereco {fetch_pc}, fora do programa carregado ({len(instructions)} instrucoes).")
            break

        binary_str = instructions[fetch_pc]
        decoded = decoder_instrucao(binary_str)
        control = unidade_controle(decoded.op, decoded.funct)

        if control.IN_signal and pending_input is None:
            if input_index < len(input_values):
                pending_input = input_values[input_index]
                input_index += 1
                pending_wait = max(0, input_latency)
                if not quiet and input_latency == 0:
                    print(f"\n[IN] valor automatico: {pending_input}")
            else:
                if quiet:
                    raise RuntimeError(f"Entrada insuficiente no PC {pc}")
                print("\n[IN] Solicitacao de entrada")
                while True:
                    try:
                        pending_input = int(input("Digite um numero inteiro: ").strip())
                        break
                    except ValueError:
                        print("Por favor, digite um valor inteiro valido.")
                pending_wait = 0

        if control.WriteToIO and not pending_output_active:
            pending_output_active = True
            pending_output_wait = max(0, output_latency)
            output_emitted = False
        elif not control.WriteToIO:
            pending_output_active = False
            pending_output_wait = 0
            output_emitted = False

        io_read_strobe = int((not control.IN_signal) or pending_wait == 0)
        io_output_strobe = int((not control.WriteToIO) or pending_output_wait == 0)
        switch_data_extended = u32((pending_input or 0) & 0x3FFFF) if control.IN_signal else 0
        stall_for_input = int(control.IN_signal and not io_read_strobe)
        stall_for_output = int(control.WriteToIO and not io_output_strobe)
        effective_halt = int(control.Halt or stall_for_input or stall_for_output)

        rs1_real = decoded.rw if control.JR else decoded.rs1
        rs1_data = 0 if rs1_real == 0 else regs[rs1_real]
        rs2_data = 0 if decoded.rs2 == 0 else regs[decoded.rs2]

        imediato_i_ex = sign_extend(decoded.imediato_i, 13)
        imediato_j_ex = sign_extend(decoded.imediato_j, 19)
        reg2ula = imediato_i_ex if control.ALUSrc else rs2_data
        alu_result, branch_taken = ula(rs1_data, reg2ula, control.ALUop, control.Branch)

        ram_read_addr = ((sp + 1) & 0x3F) if control.LOAD_STACK_en else ram_addr_from_alu(alu_result)
        ram_write_addr = sp if control.STORE_STACK_en else ram_addr_from_alu(alu_result)
        ram_write_data = rs1_data if control.STORE_STACK_en else rs2_data
        ram_q = ram[ram_read_addr]

        pc_next = u32(pc + 1)
        imediato_destino = imediato_j_ex if control.Jump else imediato_i_ex
        pc_desvio = u32(pc_next + imediato_destino)
        branch = int(branch_taken and control.Branch)
        sinal_desvio = int(control.Jump or branch)
        pc_final = pc_desvio if sinal_desvio else pc_next
        proximo_pc_logico = imediato_j_ex if control.JumpAbs else (rs1_data if control.JR else pc_final)
        endereco_alvo_salto = pc if control.Halt else proximo_pc_logico

        if control.MemtoReg == 0b00:
            rd_data = alu_result
        elif control.MemtoReg == 0b01:
            rd_data = ram_q
        elif control.MemtoReg == 0b10:
            rd_data = pc_next
        else:
            rd_data = switch_data_extended

        display_data_muxed = switch_data_extended if stall_for_input else rs1_data
        final_display_enable = int(control.WriteToIO or stall_for_input)

        if trace and steps < trace_limit:
            print(trace_line(steps, pc, fetch_pc, decoded, control, rs1_data, rs2_data, alu_result, branch_taken, rd_data, sp, effective_halt))

        if step_mode and not quiet:
            name, details = decode_for_display(decoded)
            print(f"\n[PC={pc:03d} fetch={fetch_pc:03d}] {name} {details}")
            cmd = input("ENTER proximo ciclo, 'c' continua: ").strip().lower()
            if cmd == "c":
                step_mode = False

        # Posedge: registrador SP, RAM, banco e display.
        if control.STORE_STACK_en:
            sp_next = (sp - 1) & 0x3F
        elif control.LOAD_STACK_en:
            sp_next = (sp + 1) & 0x3F
        else:
            sp_next = sp

        if control.MemWrite or control.STORE_STACK_en:
            ram[ram_write_addr] = u32(ram_write_data)

        if control.RegWrite and decoded.rw != 0:
            regs[decoded.rw] = u32(rd_data)
        regs[0] = 0

        if final_display_enable:
            display_value = to_signed_32(display_data_muxed)

        if control.WriteToIO and not output_emitted:
            out_val = to_signed_32(rs1_data)
            outputs.append(out_val)
            output_emitted = True
            if quiet:
                print(f"OUT {out_val}")
            else:
                print_7seg(out_val)

        sp = sp_next
        min_sp = min(min_sp, sp)

        if control.IN_signal:
            if stall_for_input:
                pending_wait -= 1
                if not quiet:
                    print(f"[IN] aguardando botao, valor nos switches/display: {pending_input}")
            else:
                pending_input = None

        if control.WriteToIO:
            if stall_for_output:
                pending_output_wait -= 1
                if not quiet:
                    print("[OUT] aguardando botao para avancar")

        steps += 1

        if control.Halt:
            halted = True
            if not quiet:
                print(f"\nExecution HALTED at PC={pc} after {steps} cycles.")
            break

        # Negedge: PC atualiza se effective_halt estiver inativo.
        if not effective_halt:
            pc = u32(endereco_alvo_salto)
            if control.WriteToIO:
                pending_output_active = False
                pending_output_wait = 0
                output_emitted = False

    timed_out = steps >= max_steps and not halted

    if not quiet:
        print("\n" + "=" * 60)
        print("      SIMULACAO FINALIZADA")
        print("=" * 60)
        print(f"Halted: {halted}")
        print(f"Timed out: {timed_out}")
        print(f"Steps: {steps}")
        print(f"Menor SP observado: {min_sp}")
        print(f"Display final: {display_value}")
        print(f"Saidas OUT: {outputs}")
        print("Estado final dos registradores principais:")
        for reg in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
            print(f"  {reg_name(reg):>5}: {regs[reg]:08X}")
        print("\nEstado final da RAM (primeiras 16 posicoes):")
        for i in range(0, 16, 4):
            print(
                f"  RAM[{i:02d}]: {ram[i]:08X}   RAM[{i+1:02d}]: {ram[i+1]:08X}   "
                f"RAM[{i+2:02d}]: {ram[i+2]:08X}   RAM[{i+3:02d}]: {ram[i+3]:08X}"
            )

    return {
        "halted": halted,
        "timed_out": timed_out,
        "steps": steps,
        "outputs": outputs,
        "regs": regs,
        "ram": ram,
        "sp": sp,
        "min_sp": min_sp,
        "display": display_value,
    }


def main():
    repo_root = Path(__file__).resolve().parents[1]
    default_program = repo_root / "src" / "processor" / "cpu" / "programa.txt"
    parser = argparse.ArgumentParser(description="Simulador RTL-style da CPU AOC/DE2-115.")
    parser.add_argument("programa", nargs="?", default=str(default_program), help="Arquivo programa.txt a executar.")
    parser.add_argument("--inputs", default="", help="Entradas de IN separadas por virgula. Ex: 9,2,7")
    parser.add_argument("--expect", default="", help="Saidas OUT esperadas, separadas por virgula.")
    parser.add_argument("--step", action="store_true", help="Executa em modo passo-a-passo.")
    parser.add_argument("--quiet", action="store_true", help="Imprime apenas OUTs e resumo minimo.")
    parser.add_argument("--trace", action="store_true", help="Mostra sinais principais do datapath a cada ciclo.")
    parser.add_argument("--trace-limit", type=int, default=200, help="Limite de linhas de trace.")
    parser.add_argument("--max-steps", type=int, default=100000, help="Limite de ciclos simulados.")
    parser.add_argument("--rom-bits", type=int, default=8, help="Bits de endereco da ROM simulada. Use 8 para a ROM atual.")
    parser.add_argument("--input-latency", type=int, default=0, help="Ciclos segurando PC em IN antes do botao/strobe.")
    parser.add_argument("--output-latency", type=int, default=0, help="Ciclos segurando PC em OUT antes do botao/strobe.")
    args = parser.parse_args()

    result = run_simulation(
        args.programa,
        input_values=parse_inputs(args.inputs),
        step_mode=args.step,
        max_steps=args.max_steps,
        rom_bits=args.rom_bits,
        quiet=args.quiet,
        trace=args.trace,
        trace_limit=args.trace_limit,
        input_latency=args.input_latency,
        output_latency=args.output_latency,
    )

    if args.quiet:
        print(f"HALTED {result['halted']}")
        print(f"TIMED_OUT {result['timed_out']}")
        print(f"STEPS {result['steps']}")
        print(f"OUTPUTS {','.join(str(v) for v in result['outputs'])}")

    expected = parse_inputs(args.expect)
    if expected:
        ok = result["halted"] and not result["timed_out"] and result["outputs"] == expected
        print(f"EXPECTED_OK {ok}")
        if not ok:
            print(f"EXPECTED {','.join(str(v) for v in expected)}")
            sys.exit(1)

    if result["timed_out"] or not result["halted"]:
        sys.exit(1)


if __name__ == "__main__":
    main()
