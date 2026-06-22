#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

char* processa_arvore(Node* node, int* regs_vetor, int* ptr_l, char* escopo);
void salvar_arquivo(char* OP, char* ARG1, char* ARG2, char* RES);
void salvar_quad(char* OP, char* ARG1, char* ARG2, char* RES);
void salvar_asm_line(char* OP, char* ARG1, char* ARG2, char* ARG3);
char* alocar_reg(int* regs_vetor);
void liberar_reg(char* reg, int* regs_vetor);
char* return_label(int* l);
char* int_to_char(int val);
void iniciar_compilador(Node* raiz);

char* branch_invertido(int tipo_rel) {
    switch(tipo_rel) {
        case NODE_REL_IGL:    return "BNE";
        case NODE_REL_DIF:    return "BEQ";
        case NODE_REL_MENOR:  return "BGE";
        case NODE_REL_LEQUAL: return "BGT";
        case NODE_REL_HIGHER: return "BLE";
        case NODE_REL_HEQUAL: return "BLT";
        default: return "BEQ";
    }
}

void empilhar_parametros_reverso(Node* arg, int* regs_vetor, int* ptr_l, char* escopo, int* count) {
    if (arg == NULL) return;
    empilhar_parametros_reverso(arg->sibling, regs_vetor, ptr_l, escopo, count);
    char* res_arg = processa_arvore(arg, regs_vetor, ptr_l, escopo);
    salvar_arquivo("PARAM", res_arg, "-", "-");
    liberar_reg(res_arg, regs_vetor);
    (*count)++;
}

char* processa_arvore(Node* node, int* regs_vetor, int* ptr_l, char* escopo) {
    if (node == NULL) return "-";
    
    switch(node->type) {

        case NODE_PROGRAMA: {
            salvar_arquivo("JUMP", "main", "-", "-");
            Node* current = node->child1;
            while (current != NULL) {
                processa_arvore(current, regs_vetor, ptr_l, escopo);
                current = current->sibling;
            }
            salvar_arquivo("HALT", "-", "-", "-");
            break;
        }

        case NODE_COMPOSTO_DECL: {
            Node* current = node->child1; // Variaveis
            while (current != NULL) {
                processa_arvore(current, regs_vetor, ptr_l, escopo);
                current = current->sibling;
            }
            current = node->child2; // Comandos
            while (current != NULL) {
                processa_arvore(current, regs_vetor, ptr_l, escopo);
                current = current->sibling;
            }
            break;
        }

        case NODE_VAR_DECLARACAO: {
            salvar_arquivo("ALLOC", node->child2->sval, escopo, "-");
            break;
        }

        case NODE_VAR_DECLARACAO_ARRAY: {
            char* tam = int_to_char(node->child3->ival);
            salvar_arquivo("ALLOC", node->child2->sval, tam, escopo); 
            break;
        }

        case NODE_FUN_DECLARACAO: {
            char* nome = node->child2->sval;
            salvar_arquivo("FUN", "int", nome, "-");
            Node* p = node->child2->child1;
            while (p != NULL) {
                if (p->type == NODE_PARAM || p->type == NODE_PARAM_ARRAY)
                    salvar_arquivo("ARG", p->child2->sval, "-", "-");
                p = p->sibling;
            }
            salvar_arquivo("SAVE_RA", "-", "-", "-");
            processa_arvore(node->child3, regs_vetor, ptr_l, nome);
            salvar_arquivo("END", nome, "-", "-");
            break;
        }

        case NODE_RETORNO_DECL: {
            if (node->child1 != NULL) {
                char* val = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
                salvar_arquivo("RET", val, "-", "-");
                liberar_reg(val, regs_vetor);
            } else {
                salvar_arquivo("RET", "-", "-", "-"); 
            }
            break;
        }

        case NODE_ATIVACAO: {
            char* nome = node->child1->sval;
            if (strcmp(nome, "input") == 0) {
                char* t = alocar_reg(regs_vetor);
                salvar_arquivo("IN", "-", "-", t);
                return t;
            } 
            else if (strcmp(nome, "output") == 0) {
                char* arg = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
                salvar_arquivo("OUT", arg, "-", "-");
                liberar_reg(arg, regs_vetor);
                return "-";
            }
            int num_args = 0;
            empilhar_parametros_reverso(node->child2, regs_vetor, ptr_l, escopo, &num_args);
            char* t = alocar_reg(regs_vetor);
            salvar_arquivo("CALL", nome, int_to_char(num_args), t);
            return t;
        }

        case NODE_EXPRESSAO_REC: {
            char* val = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            if (node->child1->type == NODE_ID) {
                salvar_arquivo("STORE", val, node->child1->sval, "-");
            } else if (node->child1->type == NODE_VAR_ARRAY) {
                char* idx = processa_arvore(node->child1->child2, regs_vetor, ptr_l, escopo);
                salvar_arquivo("STORE", val, node->child1->child1->sval, idx);
                liberar_reg(idx, regs_vetor);
            }
            liberar_reg(val, regs_vetor);
            return val; 
        }

        case NODE_SOMA: {
            char* v1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* v2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* t = alocar_reg(regs_vetor);
            salvar_arquivo("ADD", v1, v2, t);
            liberar_reg(v1, regs_vetor); liberar_reg(v2, regs_vetor);
            return t;
        }
        case NODE_SUB: {
            char* v1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* v2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* t = alocar_reg(regs_vetor);
            salvar_arquivo("SUB", v1, v2, t);
            liberar_reg(v1, regs_vetor); liberar_reg(v2, regs_vetor);
            return t;
        }
        case NODE_MULT: {
            char* v1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* v2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* t = alocar_reg(regs_vetor);
            salvar_arquivo("MULT", v1, v2, t);
            liberar_reg(v1, regs_vetor); liberar_reg(v2, regs_vetor);
            return t;
        }
        case NODE_DIV: {
            char* v1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* v2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* t = alocar_reg(regs_vetor);
            salvar_arquivo("DIV", v1, v2, t);
            liberar_reg(v1, regs_vetor); liberar_reg(v2, regs_vetor);
            return t;
        }
        
        case NODE_ID: {
            char* t = alocar_reg(regs_vetor);
            salvar_arquivo("LOAD", node->sval, "-", t); 
            return t;
        }

        case NODE_NUM: {
            char* t = alocar_reg(regs_vetor);
            salvar_arquivo("LOADI", int_to_char(node->ival), "-", t);
            return t;
        }

        case NODE_VAR_ARRAY: {
            char* idx = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* t = alocar_reg(regs_vetor);
            salvar_arquivo("LOAD", node->child1->sval, idx, t);
            liberar_reg(idx, regs_vetor);
            return t;
        }

        case NODE_RELACIONAL: {
            char* v1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* v2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* t = alocar_reg(regs_vetor);

            if (node->child3->type == NODE_REL_IGL)    salvar_arquivo("EQ", v1, v2, t);
            if (node->child3->type == NODE_REL_DIF)    salvar_arquivo("NEQ", v1, v2, t);
            if (node->child3->type == NODE_REL_MENOR)  salvar_arquivo("LT", v1, v2, t);
            if (node->child3->type == NODE_REL_LEQUAL) salvar_arquivo("LE", v1, v2, t);
            if (node->child3->type == NODE_REL_HIGHER) salvar_arquivo("GT", v1, v2, t);
            if (node->child3->type == NODE_REL_HEQUAL) salvar_arquivo("GE", v1, v2, t);
            liberar_reg(v1, regs_vetor); 
            liberar_reg(v2, regs_vetor);
            return t; 
        }

        case NODE_SELECAO_DECL: {
            char* lelse = return_label(ptr_l);
            char* lfim = return_label(ptr_l);

            if (node->child1->type == NODE_RELACIONAL) {
                char* v1 = processa_arvore(node->child1->child1, regs_vetor, ptr_l, escopo);
                char* v2 = processa_arvore(node->child1->child2, regs_vetor, ptr_l, escopo);
                char* br = branch_invertido(node->child1->child3->type);
                salvar_arquivo(br, v1, v2, lelse);
                liberar_reg(v1, regs_vetor); 
                liberar_reg(v2, regs_vetor);
            } else {
                char* cond = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
                salvar_arquivo("BEQ", cond, "$zero", lelse);
                liberar_reg(cond, regs_vetor);
            }

            processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            salvar_arquivo("JUMP", lfim, "-", "-");
            salvar_arquivo("LAB", lelse, "-", "-");
            if (node->child3 != NULL)
                processa_arvore(node->child3, regs_vetor, ptr_l, escopo);
            salvar_arquivo("LAB", lfim, "-", "-");
            break; 
        }

        case NODE_ITERACAO_DECL: {
            char* linicio = return_label(ptr_l);
            salvar_arquivo("LAB", linicio, "-", "-");
            char* lfim = return_label(ptr_l);

            if (node->child1->type == NODE_RELACIONAL) {
                char* v1 = processa_arvore(node->child1->child1, regs_vetor, ptr_l, escopo);
                char* v2 = processa_arvore(node->child1->child2, regs_vetor, ptr_l, escopo);
                char* br = branch_invertido(node->child1->child3->type);
                salvar_arquivo(br, v1, v2, lfim);
                liberar_reg(v1, regs_vetor); liberar_reg(v2, regs_vetor);
            } else {
                char* cond = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
                salvar_arquivo("BEQ", cond, "$zero", lfim);
                liberar_reg(cond, regs_vetor);
            }

            processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            salvar_arquivo("JUMP", linicio, "-", "-");
            salvar_arquivo("LAB", lfim, "-", "-");
            break;
        }

        case NODE_PARAM:
        case NODE_PARAM_ARRAY:
            break;
    }
    return "-";
}

#define MAX_INSTRUCTIONS 2000

typedef struct {
    char op[16];
    char arg1[64];
    char arg2[64];
    char arg3[64];
    int is_label;
    char label_name[64];
} AsmInstruction;

typedef struct {
    char name[64];
    int pc;
} LabelMap;

typedef struct {
    char name[64];
    int addr;
} VarMap;

AsmInstruction program[MAX_INSTRUCTIONS];
int instruction_count = 0;

LabelMap labels[200];
int label_count = 0;

VarMap variables[200];
int var_count = 0;
int next_ram_addr = 0;

int get_label_pc(char* name) {
    for (int i = 0; i < label_count; i++) {
        if (strcmp(labels[i].name, name) == 0) {
            return labels[i].pc;
        }
    }
    return 0;
}

int get_var_addr(char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].addr;
        }
    }
    return 0;
}

int get_reg_num(char* name) {
    if (strcmp(name, "$zero") == 0) return 0;
    if (strcmp(name, "$ra") == 0) return 1;
    if (strcmp(name, "$sp") == 0) return 2;
    if (strcmp(name, "$at") == 0) return 3;
    if (name[0] == '$' && name[1] == 't') {
        return atoi(&name[2]) + 4; // $t0 -> 4, $t1 -> 5, etc.
    }
    return 0;
}

void write_binary_instruction(FILE* f, unsigned int val) {
    for (int i = 31; i >= 0; i--) {
        fprintf(f, "%c", (val & (1U << i)) ? '1' : '0');
    }
    fprintf(f, "\n");
}

void gerar_saidas_finais() {
    FILE *f_asm = fopen("saida.asm", "w");
    FILE *f_bin = fopen("programa.txt", "w");
    if (!f_asm || !f_bin) {
        printf("Erro ao criar arquivos de saida.\n");
        return;
    }

    int current_pc = 0;
    label_count = 0;

    // Pass 1: Mapear labels e calcular PC real de cada instrucao
    for (int i = 0; i < instruction_count; i++) {
        if (program[i].is_label) {
            if (label_count < 200) {
                strcpy(labels[label_count].name, program[i].label_name);
                labels[label_count].pc = current_pc;
                label_count++;
            }
        } else {
            char* op = program[i].op;
            // LOAD/STORE com array expande para 3 instrucoes reais
            if (strcmp(op, "LOAD") == 0 && strcmp(program[i].arg3, "-") != 0 && strcmp(program[i].arg3, "0") != 0) {
                current_pc += 3;
            } else if (strcmp(op, "STORE") == 0 && strcmp(program[i].arg1, "-") != 0 && strcmp(program[i].arg3, "0") != 0) {
                current_pc += 3;
            } else {
                current_pc += 1;
            }
        }
    }

    // Pass 2: Escrever saida.asm e programa.txt
    current_pc = 0;
    for (int i = 0; i < instruction_count; i++) {
        if (program[i].is_label) {
            fprintf(f_asm, "%s:\n", program[i].label_name);
        } else {
            char* op = program[i].op;
            char* arg1 = program[i].arg1;
            char* arg2 = program[i].arg2;
            char* arg3 = program[i].arg3;

            // Escreve no saida.asm
            if (strcmp(arg2, "-") == 0 && strcmp(arg3, "-") == 0) {
                fprintf(f_asm, "%s %s\n", op, arg1);
            } else if (strcmp(arg3, "-") == 0) {
                fprintf(f_asm, "%s %s, %s\n", op, arg1, arg2);
            } else {
                fprintf(f_asm, "%s %s, %s, %s\n", op, arg1, arg2, arg3);
            }

            unsigned int bits = 0;

            // Tradução para binário de 32 bits
            if (strcmp(op, "JUMP") == 0) {
                int target = get_label_pc(arg1);
                int offset = target - current_pc - 1;
                bits = ((offset & 0x7FFFF) << 13) | (0 << 7) | (0 << 3) | 2;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "JAL") == 0) {
                int target = get_label_pc(arg2);
                int offset = target - current_pc - 1;
                bits = ((offset & 0x7FFFF) << 13) | (get_reg_num(arg1) << 7) | (2 << 3) | 2;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "JR") == 0) {
                bits = (0 << 13) | (get_reg_num(arg1) << 7) | (1 << 3) | 2;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "BEQ") == 0 || strcmp(op, "BNE") == 0 || strcmp(op, "BLT") == 0 ||
                     strcmp(op, "BLE") == 0 || strcmp(op, "BGT") == 0 || strcmp(op, "BGE") == 0) {
                int funct = 0;
                if (strcmp(op, "BEQ") == 0) funct = 0;
                else if (strcmp(op, "BNE") == 0) funct = 1;
                else if (strcmp(op, "BLT") == 0) funct = 2;
                else if (strcmp(op, "BLE") == 0) funct = 3;
                else if (strcmp(op, "BGT") == 0) funct = 4;
                else if (strcmp(op, "BGE") == 0) funct = 5;

                int target = get_label_pc(arg3);
                int offset = target - current_pc - 1;
                bits = ((offset & 0x1FFF) << 19) | (get_reg_num(arg2) << 13) | (get_reg_num(arg1) << 7) | (funct << 3) | 3;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0 || strcmp(op, "MULT") == 0 ||
                     strcmp(op, "DIV") == 0 || strcmp(op, "AND") == 0 || strcmp(op, "OR") == 0 ||
                     strcmp(op, "XOR") == 0) {
                int funct = 0;
                if (strcmp(op, "ADD") == 0) funct = 0;
                else if (strcmp(op, "SUB") == 0) funct = 1;
                else if (strcmp(op, "MULT") == 0) funct = 2;
                else if (strcmp(op, "DIV") == 0) funct = 3;
                else if (strcmp(op, "AND") == 0) funct = 4;
                else if (strcmp(op, "OR") == 0) funct = 5;
                else if (strcmp(op, "XOR") == 0) funct = 6;

                bits = (0 << 25) | (get_reg_num(arg3) << 19) | (get_reg_num(arg2) << 13) | (get_reg_num(arg1) << 7) | (funct << 3) | 0;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "ADDI") == 0 || strcmp(op, "SUBI") == 0 || strcmp(op, "ANDI") == 0 ||
                     strcmp(op, "ORI") == 0 || strcmp(op, "XORI") == 0) {
                int funct = 2;
                if (strcmp(op, "ADDI") == 0) funct = 2;
                else if (strcmp(op, "SUBI") == 0) funct = 3;
                else if (strcmp(op, "ANDI") == 0) funct = 4;
                else if (strcmp(op, "ORI") == 0) funct = 5;
                else if (strcmp(op, "XORI") == 0) funct = 6;

                int imm = atoi(arg3);
                bits = ((imm & 0x1FFF) << 19) | (get_reg_num(arg2) << 13) | (get_reg_num(arg1) << 7) | (funct << 3) | 1;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "IN") == 0) {
                bits = (get_reg_num(arg1) << 7) | (0 << 3) | 6;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "OUT") == 0) {
                bits = (get_reg_num(arg1) << 7) | (1 << 3) | 6;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "STORE_STACK") == 0) {
                bits = (get_reg_num(arg1) << 7) | (2 << 3) | 6;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "LOAD_STACK") == 0) {
                bits = (get_reg_num(arg1) << 7) | (3 << 3) | 6;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "HALT") == 0) {
                bits = (1 << 3) | 4;
                write_binary_instruction(f_bin, bits);
                current_pc += 1;
            }
            else if (strcmp(op, "LOAD") == 0) {
                // LOAD rd, var, idx
                if (strcmp(arg3, "-") != 0 && strcmp(arg3, "0") != 0) {
                    // Acesso a Array: LOAD rd, a, idx
                    int addr = get_var_addr(arg2);
                    // 1. ADDI rd, $zero, addr
                    bits = ((addr & 0x1FFF) << 19) | (0 << 13) | (get_reg_num(arg1) << 7) | (2 << 3) | 1;
                    write_binary_instruction(f_bin, bits);
                    // 2. ADD rd, rd, idx
                    bits = (0 << 25) | (get_reg_num(arg3) << 19) | (get_reg_num(arg1) << 13) | (get_reg_num(arg1) << 7) | (0 << 3) | 0;
                    write_binary_instruction(f_bin, bits);
                    // 3. LOAD rd, 0, rd
                    bits = (0 << 19) | (get_reg_num(arg1) << 13) | (get_reg_num(arg1) << 7) | (0 << 3) | 1;
                    write_binary_instruction(f_bin, bits);
                    current_pc += 3;
                } else {
                    // Acesso a variavel simples: LOAD rd, var
                    int addr = get_var_addr(arg2);
                    bits = ((addr & 0x1FFF) << 19) | (0 << 13) | (get_reg_num(arg1) << 7) | (0 << 3) | 1;
                    write_binary_instruction(f_bin, bits);
                    current_pc += 1;
                }
            }
            else if (strcmp(op, "STORE") == 0) {
                if (strcmp(arg3, "0") == 0) {
                    // Simple store do ARG: STORE value_reg, var_name, 0
                    int addr = get_var_addr(arg2);
                    bits = ((addr & 0x1FFF) << 19) | (0 << 13) | (get_reg_num(arg1) << 7) | (1 << 3) | 1;
                    write_binary_instruction(f_bin, bits);
                    current_pc += 1;
                } else if (strcmp(arg1, "-") == 0) {
                    // Simple store da atribuicao: STORE -, value_reg, var_name
                    int addr = get_var_addr(arg3);
                    bits = ((addr & 0x1FFF) << 19) | (0 << 13) | (get_reg_num(arg2) << 7) | (1 << 3) | 1;
                    write_binary_instruction(f_bin, bits);
                    current_pc += 1;
                } else {
                    // Acesso a Array: STORE idx_reg, value_reg, array_name
                    int addr = get_var_addr(arg3);
                    // 1. ADDI $at, $zero, addr
                    bits = ((addr & 0x1FFF) << 19) | (0 << 13) | (3 << 7) | (2 << 3) | 1; // 3 is $at
                    write_binary_instruction(f_bin, bits);
                    // 2. ADD $at, $at, idx_reg
                    bits = (0 << 25) | (get_reg_num(arg1) << 19) | (3 << 13) | (3 << 7) | (0 << 3) | 0;
                    write_binary_instruction(f_bin, bits);
                    // 3. STORE value_reg, 0, $at
                    bits = (0 << 19) | (3 << 13) | (get_reg_num(arg2) << 7) | (1 << 3) | 1;
                    write_binary_instruction(f_bin, bits);
                    current_pc += 3;
                }
            }
        }
    }

    fclose(f_asm);
    fclose(f_bin);
}

void iniciar_compilador(Node* raiz) {
    FILE *f1 = fopen("saida.quad", "w"); if (f1) fclose(f1);
    instruction_count = 0;
    var_count = 0;
    next_ram_addr = 0;
    int regs_vetor[64];
    int i;
    for(i = 0; i < 64; i++) regs_vetor[i] = 0;
    int l = 0; 
    processa_arvore(raiz, regs_vetor, &l, "global"); 
    
    // Gera os arquivos saida.asm e programa.txt
    gerar_saidas_finais();
}

void salvar_quad(char* OP, char* A1, char* A2, char* RES) {
    FILE *f = fopen("saida.quad", "a"); 
    if (f) { fprintf(f, "(%s, %s, %s, %s)\n", OP, A1, A2, RES); fclose(f); }
}

void salvar_asm_line(char* OP, char* A1, char* A2, char* A3) {
    if (instruction_count >= MAX_INSTRUCTIONS) return;
    AsmInstruction* inst = &program[instruction_count++];
    strncpy(inst->op, OP, 15); inst->op[15] = '\0';
    strncpy(inst->arg1, A1, 63); inst->arg1[63] = '\0';
    strncpy(inst->arg2, A2, 63); inst->arg2[63] = '\0';
    strncpy(inst->arg3, A3, 63); inst->arg3[63] = '\0';
    inst->is_label = 0;
}

void salvar_asm_label(char* nome) {
    if (instruction_count >= MAX_INSTRUCTIONS) return;
    AsmInstruction* inst = &program[instruction_count++];
    inst->is_label = 1;
    strncpy(inst->label_name, nome, 63); inst->label_name[63] = '\0';
}

void salvar_asm_raw(char* texto) {
    if (instruction_count >= MAX_INSTRUCTIONS) return;
    AsmInstruction* inst = &program[instruction_count++];
    strncpy(inst->op, texto, 15); inst->op[15] = '\0';
    strcpy(inst->arg1, "-");
    strcpy(inst->arg2, "-");
    strcpy(inst->arg3, "-");
    inst->is_label = 0;
}

void salvar_arquivo(char* OP, char* A1, char* A2, char* RES) {
    // Registra variáveis alocadas estaticamente
    if (strcmp(OP, "ALLOC") == 0) {
        int found = 0;
        for (int i = 0; i < var_count; i++) {
            if (strcmp(variables[i].name, A1) == 0) {
                found = 1;
                break;
            }
        }
        if (!found && var_count < 200) {
            strcpy(variables[var_count].name, A1);
            variables[var_count].addr = next_ram_addr;
            int size = 1;
            if (A2[0] >= '0' && A2[0] <= '9') {
                size = atoi(A2);
            }
            next_ram_addr += size * 4;
            var_count++;
        }
        // ALLOC não gera quádrupla nem assembly
        return;
    }

    // Registra parâmetros de funções como variáveis
    if (strcmp(OP, "ARG") == 0) {
        int found = 0;
        for (int i = 0; i < var_count; i++) {
            if (strcmp(variables[i].name, A1) == 0) {
                found = 1;
                break;
            }
        }
        if (!found && var_count < 200) {
            strcpy(variables[var_count].name, A1);
            variables[var_count].addr = next_ram_addr;
            next_ram_addr += 4;
            var_count++;
        }
    }

    if (strcmp(OP, "SAVE_RA") != 0)
        salvar_quad(OP, A1, A2, RES);
    
    if (strcmp(OP,"BEQ")==0 || strcmp(OP,"BNE")==0 || strcmp(OP,"BLT")==0 ||
        strcmp(OP,"BLE")==0 || strcmp(OP,"BGT")==0 || strcmp(OP,"BGE")==0) {
        salvar_asm_line(OP, A1, A2, RES); // RES = label
    }
    else if (strcmp(OP, "PARAM") == 0) {
        salvar_asm_line("STORE_STACK", A1, "-", "-");
    }
    else if (strcmp(OP, "CALL") == 0) {
        salvar_asm_line("JAL", "$ra", A1, "-");
        if (strcmp(RES, "-") != 0) {
            salvar_asm_line("LOAD_STACK", RES, "-", "-");
        }
    }
    else if (strcmp(OP, "RET") == 0) {
        salvar_asm_line("LOAD_STACK", "$ra", "-", "-");
        if (strcmp(A1, "-") != 0) {
            salvar_asm_line("STORE_STACK", A1, "-", "-");
        }
        salvar_asm_line("JR", "$ra", "-", "-");
    }
    else if (strcmp(OP, "ARG") == 0) {
        salvar_asm_line("LOAD_STACK", "$at", "-", "-");
        salvar_asm_line("STORE", "$at", A1, "0");
    }
    else if (strcmp(OP, "SAVE_RA") == 0) {
        salvar_asm_line("STORE_STACK", "$ra", "-", "-");
    }
    else if (strcmp(OP, "LOADI") == 0) {
        salvar_asm_line("ADDI", RES, "$zero", A1);
    }
    else if (strcmp(OP, "LAB") == 0) {
        salvar_asm_label(A1);
    }
    else if (strcmp(OP, "FUN") == 0) {
        salvar_asm_label(A2); 
    }
    else if (strcmp(OP, "JUMP") == 0) {
        salvar_asm_line("JUMP", A1, "-", "-");
    }
    else if (strcmp(OP, "IN") == 0) {
        salvar_asm_line("IN", RES, "-", "-");
    }
    else if (strcmp(OP, "OUT") == 0) {
        salvar_asm_line("OUT", A1, "-", "-");
    }
    else if (strcmp(OP, "END") == 0) {
    }
    else if (strcmp(OP, "HALT") == 0) {
        salvar_asm_raw("HALT");
    }
    else {
        salvar_asm_line(OP, RES, A1, A2); 
    }
}

char* alocar_reg(int* regs_vetor) {
    int i;
    for(i = 0; i < 64; i++) {
        if (regs_vetor[i] == 0) {
            regs_vetor[i] = 1;
            char* t = (char*) malloc(16);
            sprintf(t, "$t%d", i);
            return t;
        }
    }
    return "$overflow"; 
}

void liberar_reg(char* reg, int* regs_vetor) {
    if (reg[0] == '$' && reg[1] == 't') {
        int idx = atoi(&reg[2]);
        if (idx >= 0 && idx < 64) regs_vetor[idx] = 0;
    }
}

char* int_to_char(int val) {
    char* s = (char*) malloc(16);
    sprintf(s, "%d", val);
    return s;
}

char* return_label(int* l) {
    char* lb = (char*) malloc(16); 
    sprintf(lb, "L%d", *l);
    (*l)++; 
    return lb;
}