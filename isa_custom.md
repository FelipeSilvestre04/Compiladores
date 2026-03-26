# ESPECIFICAÇÃO DA ISA: RISC-V CUSTOMIZADO (RV32I SUBSET)

Este documento resume a arquitetura de instruções que o Assembler deve gerar para o processador Verilog.

## 1. Formatos de Instrução (32 bits)

| Tipo | 31 ... | ... | ... | ... | ... | 0 |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **R** | null (7) | rs2 (6) | rs1 (6) | rd (6) | funct (4) | opcode (3) |
| **I** | imm (13) | - | rs1 (6) | rd (6) | funct (4) | opcode (3) |
| **J** | imm (19) | - | - | rd (6) | funct (4) | opcode (3) |
| **B** | imm (13) | - | rs1 (6) | rd (6) | funct (4) | opcode (3) |
| **N** | null (25) | - | - | - | funct (4) | opcode (3) |
| **IO**| null (19) | - | - | rd/rs1 (6)| funct (4) | opcode (3) |

---

## 2. Tabela de Opcodes e Funct

### Tipo R (Opcode: 000)
| Instrução | Funct | Descrição |
| :--- | :---: | :--- |
| **ADD** | 0000 | rd = rs1 + rs2 |
| **SUB** | 0001 | rd = rs1 - rs2 |
| **MULT** | 0010 | rd = rs1 * rs2 |
| **DIV** | 0011 | rd = rs1 / rs2 |
| **AND** | 0100 | rd = rs1 & rs2 |
| **OR** | 0101 | rd = rs1 \| rs2 |
| **XOR** | 0110 | rd = rs1 ^ rs2 |
| **NOT** | 0111 | rd = ~rs1 |

### Tipo I (Opcode: 001)
| Instrução | Funct | Descrição |
| :--- | :---: | :--- |
| **LOAD** | 0000 | rd = MEM[rs1 + imm] |
| **STORE** | 0001 | MEM[rs1 + imm] = rs2* |
| **ADDI** | 0010 | rd = rs1 + imm |
| **SUBI** | 0011 | rd = rs1 - imm |
| **ANDI** | 0100 | rd = rs1 & imm |
| **ORI** | 0101 | rd = rs1 \| imm |
| **XORI** | 0110 | rd = rs1 ^ imm |
| **LDA** | 0111 | rd = endereço(label) |
| **MOV** | 1000 | rd = rs1 |
**Nota*: No Tipo I do usuário, o campo `rd` parece ser usado como `rs2` em instruções de Store.

### Tipo J (Opcode: 010)
| Instrução | Funct | Descrição |
| :--- | :---: | :--- |
| **JUMP** | 0000 | PC = label |
| **JR** | 0001 | PC = rs1 |
| **JAL** | 0010 | rd = PC + 1; PC = label |

### Tipo B (Opcode: 011)
| Instrução | Funct | Descrição |
| :--- | :---: | :--- |
| **BEQ** | 0000 | Desvia se rs1 == rd |
| **BNE** | 0001 | Desvia se rs1 != rd |
| **BLT** | 0010 | Desvia se rs1 < rd |
| **BLE** | 0011 | Desvia se rs1 <= rd |
| **BGT** | 0100 | Desvia se rs1 > rd |
| **BGE** | 0101 | Desvia se rs1 >= rd |

### Tipo N (Opcode: 100)
| Instrução | Funct | Descrição |
| :--- | :---: | :--- |
| **NOP** | 0000 | Nenhuma operação |
| **HALT** | 0001 | Para o processador |

### Tipo IO (Opcode: 110)
| Instrução | Funct | Descrição |
| :--- | :---: | :--- |
| **IN** | 0000 | rd = Entrada externa |
| **OUT** | 0001 | Saída externa = rs1 |

---

## 3. Mapeamento de Registradores Sugerido
Dado que os campos `rs1`, `rs2` e `rd` têm **6 bits**, o processador suporta até 64 registradores. Usaremos o mapeamento padrão de 32 para compatibilidade:
- `$zero` -> `x0`
- `$t0...$t9` -> `x5...x14`
- `$sp` -> `x2`
- `$ra` -> `x1`
