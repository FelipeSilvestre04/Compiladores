import sys

# --- CONFIGURAÇÕES DO TRADUTOR ---
# O Global Pointer (x3) aponta para o começo da nossa memória de dados.
GP_REG = "x3"

# Variáveis globais para controle de rótulos e memória
label_count = 0
symbol_table = {}
next_mem_pos = 0

def new_label():
    global label_count
    label = f"L_gen_{label_count}"
    label_count += 1
    return label

def get_mem_offset(name):
    global next_mem_pos
    if name not in symbol_table:
        symbol_table[name] = next_mem_pos
        next_mem_pos += 4 # Cada variável ocupa 4 bytes
    return symbol_table[name]

def map_reg(reg):
    if reg == '$zero' or reg == '-': return 'x0'
    if reg.startswith('$t'):
        # Mapeia temporários t0, t1... para os registradores x20, x21...
        # Isso evita conflito com os argumentos de função (x10-x17)
        num = int(reg[2:])
        return f'x{num + 20}'
    return reg

# --- O GRANDE LOOP DE TRADUÇÃO (O "SWITCH-CASE") ---
def translate():
    global param_count
    param_count = 0

    try:
        with open("saida.quad", "r") as f:
            quads = f.readlines()
    except:
        print("Erro: saida.quad não encontrada.")
        return

    with open("saida.asm", "w") as f_asm:
        for line in quads:
            # Limpa a linha: (OP, A1, A2, RES) -> [OP, A1, A2, RES]
            line = line.strip().replace("(", "").replace(")", "")
            if not line: continue
            parts = [p.strip() for p in line.split(",")]
            
            if len(parts) != 4: continue
            op, arg1, arg2, res = parts
            op = op.upper()

            # --- INICIO DA LÓGICA DE DECISÃO ---
            
            # 1. ARITMÉTICA (ADD, SUB, MULT, DIV, AND, OR, XOR)
            if op in ["ADD", "SUB", "MULT", "DIV", "AND", "OR", "XOR"]:
                f_asm.write(f"    {op.lower()} {map_reg(res)}, {map_reg(arg1)}, {map_reg(arg2)}\n")

            # 2. COMPARAÇÕES (EQ, NEQ, LT, LE, GT, GE)
            elif op in ["EQ", "NEQ", "LT", "LE", "GT", "GE"]:
                l_true = new_label()
                l_end = new_label()
                f_asm.write(f"    addi {map_reg(res)}, x0, 0\n") # Assume falso
                f_asm.write(f"    b{op.lower()} {map_reg(arg1)}, {map_reg(arg2)}, {l_true}\n")
                f_asm.write(f"    jump {l_end}\n")
                f_asm.write(f"{l_true}:\n")
                f_asm.write(f"    addi {map_reg(res)}, x0, 1\n") # Seta verdadeiro
                f_asm.write(f"{l_end}:\n")

            # 3. MEMÓRIA (LOAD / STORE)
            elif op == "LOAD":
                offset = get_mem_offset(arg1)
                f_asm.write(f"    load {map_reg(res)}, {offset}({GP_REG})\n")

            elif op == "STORE":
                offset = get_mem_offset(arg2)
                f_asm.write(f"    store {map_reg(arg1)}, {offset}({GP_REG})\n")

            # 4. CONTROLE DE FLUXO (JUMP, IFF, CALL, RET)
            elif op == "JUMP":
                f_asm.write(f"    jump {arg1}\n")

            elif op == "IFF":
                # Se o valor for 0 (falso), pula para o rótulo informado
                f_asm.write(f"    beq {map_reg(arg1)}, x0, {arg2}\n")

            elif op == "CALL":
                f_asm.write(f"    jal x1, {arg1}\n")
                param_count = 0 # Reseta contagem após a chamada

            elif op == "RET":
                f_asm.write(f"    jr x1\n")

            # 5. PARÂMETROS E FUNÇÕES
            elif op == "PARAM":
                # Mapeia para a0, a1 (x10, x11...)
                f_asm.write(f"    mov x{10 + param_count}, {map_reg(arg1)}\n")
                param_count += 1

            elif op == "FUN":
                f_asm.write(f"\n{arg2}:\n")

            elif op == "LAB":
                f_asm.write(f"{arg1}:\n")

            # 6. ENTRADA/SAÍDA E SISTEMA
            elif op == "IN":
                f_asm.write(f"    in {map_reg(res)}\n")

            elif op == "OUT":
                f_asm.write(f"    out {map_reg(arg1)}\n")

            elif op == "HALT":
                f_asm.write(f"    halt\n")

            # Ignora meta-quádruplas (END, ALLOC) para o Assembly ficar limpo
            else:
                pass

    print(f"Sucesso! Assembly gerado em 'saida.asm'.")

if __name__ == "__main__":
    translate()
