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

// Retorna o branch INVERTIDO (pois IFF = "se falso, pula")
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

// Empilha parâmetros em ordem REVERSA (Opção A)
void empilhar_parametros_reverso(Node* arg, int* regs_vetor, int* ptr_l, char* escopo, int* count) {
    if (arg == NULL) return;
    empilhar_parametros_reverso(arg->sibling, regs_vetor, ptr_l, escopo, count);
    char* res_arg = processa_arvore(arg, regs_vetor, ptr_l, escopo);
    salvar_arquivo("PARAM", res_arg, "-", "-");
    liberar_reg(res_arg, regs_vetor);
    (*count)++;
}

// --- FUNÇÃO PRINCIPAL ---
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
            Node* current = node->child1;
            while (current != NULL) {
                processa_arvore(current, regs_vetor, ptr_l, escopo);
                current = current->sibling;
            }
            current = node->child2;
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

        // Comparações agora são geradas DIRETAMENTE como branches no IF/WHILE
        case NODE_RELACIONAL: {
            char* v1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* v2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* t = alocar_reg(regs_vetor);
            // Fallback: caso usado fora de IF/WHILE
            if (node->child3->type == NODE_REL_IGL)    salvar_arquivo("EQ", v1, v2, t);
            if (node->child3->type == NODE_REL_DIF)    salvar_arquivo("NEQ", v1, v2, t);
            if (node->child3->type == NODE_REL_MENOR)  salvar_arquivo("LT", v1, v2, t);
            if (node->child3->type == NODE_REL_LEQUAL) salvar_arquivo("LE", v1, v2, t);
            if (node->child3->type == NODE_REL_HIGHER) salvar_arquivo("GT", v1, v2, t);
            if (node->child3->type == NODE_REL_HEQUAL) salvar_arquivo("GE", v1, v2, t);
            liberar_reg(v1, regs_vetor); liberar_reg(v2, regs_vetor);
            return t; 
        }

        case NODE_SELECAO_DECL: {
            char* lelse = return_label(ptr_l);
            char* lfim = return_label(ptr_l);

            // Se o filho é uma comparação, gera branch direto!
            if (node->child1->type == NODE_RELACIONAL) {
                char* v1 = processa_arvore(node->child1->child1, regs_vetor, ptr_l, escopo);
                char* v2 = processa_arvore(node->child1->child2, regs_vetor, ptr_l, escopo);
                char* br = branch_invertido(node->child1->child3->type);
                salvar_arquivo(br, v1, v2, lelse);
                liberar_reg(v1, regs_vetor); liberar_reg(v2, regs_vetor);
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

// --- GATILHO ---
void iniciar_compilador(Node* raiz) {
    FILE *f1 = fopen("saida.quad", "w"); if (f1) fclose(f1);
    FILE *f2 = fopen("saida.asm", "w");  if (f2) fclose(f2);
    int regs_vetor[64];
    int i;
    for(i = 0; i < 64; i++) regs_vetor[i] = 0;
    int l = 0; 
    processa_arvore(raiz, regs_vetor, &l, "global"); 
}

// --- ESCRITA ---

void salvar_quad(char* OP, char* A1, char* A2, char* RES) {
    FILE *f = fopen("saida.quad", "a"); 
    if (f) { fprintf(f, "(%s, %s, %s, %s)\n", OP, A1, A2, RES); fclose(f); }
}

// Escreve uma linha de assembly REAL (não quádrupla)
void salvar_asm_line(char* OP, char* A1, char* A2, char* A3) {
    FILE *f = fopen("saida.asm", "a"); 
    if (f) {
        if (strcmp(A2, "-") == 0 && strcmp(A3, "-") == 0)
            fprintf(f, "%s %s\n", OP, A1);
        else if (strcmp(A3, "-") == 0)
            fprintf(f, "%s %s, %s\n", OP, A1, A2);
        else
            fprintf(f, "%s %s, %s, %s\n", OP, A1, A2, A3);
        fclose(f);
    }
}

void salvar_asm_label(char* nome) {
    FILE *f = fopen("saida.asm", "a"); 
    if (f) { fprintf(f, "%s:\n", nome); fclose(f); }
}

void salvar_asm_raw(char* texto) {
    FILE *f = fopen("saida.asm", "a"); 
    if (f) { fprintf(f, "%s\n", texto); fclose(f); }
}

// --- DISPATCHER ---
void salvar_arquivo(char* OP, char* A1, char* A2, char* RES) {
    // Fase 1: Quádrupla (exceto instruções internas)
    if (strcmp(OP, "SAVE_RA") != 0)
        salvar_quad(OP, A1, A2, RES);
    
    // Fase 2: Assembly real do processador
    
    // --- Branch direto (BEQ, BNE, BLT, BLE, BGT, BGE) ---
    if (strcmp(OP,"BEQ")==0 || strcmp(OP,"BNE")==0 || strcmp(OP,"BLT")==0 ||
        strcmp(OP,"BLE")==0 || strcmp(OP,"BGT")==0 || strcmp(OP,"BGE")==0) {
        salvar_asm_line(OP, A1, A2, RES); // RES = label
    }
    // --- PARAM → Push na pilha ---
    else if (strcmp(OP, "PARAM") == 0) {
        salvar_asm_line("STORE_STACK", A1, "-", "-");
    }
    // --- CALL → JAL + Pop retorno ---
    else if (strcmp(OP, "CALL") == 0) {
        salvar_asm_line("JAL", "$ra", A1, "-");
        if (strcmp(RES, "-") != 0) {
            salvar_asm_line("LOAD_STACK", RES, "-", "-");
        }
    }
    // --- RET → Restaura $ra, empilha resultado, JR ---
    else if (strcmp(OP, "RET") == 0) {
        salvar_asm_line("LOAD_STACK", "$ra", "-", "-");
        if (strcmp(A1, "-") != 0) {
            salvar_asm_line("STORE_STACK", A1, "-", "-");
        }
        salvar_asm_line("JR", "$ra", "-", "-");
    }
    // --- ARG → Pop param da pilha ---
    else if (strcmp(OP, "ARG") == 0) {
        salvar_asm_line("LOAD_STACK", "$at", "-", "-");
        salvar_asm_line("STORE", "$at", A1, "0");
    }
    // --- SAVE_RA → Push $ra ---
    else if (strcmp(OP, "SAVE_RA") == 0) {
        salvar_asm_line("STORE_STACK", "$ra", "-", "-");
    }
    // --- LOADI → ADDI rd, $zero, imm ---
    else if (strcmp(OP, "LOADI") == 0) {
        salvar_asm_line("ADDI", RES, "$zero", A1);
    }
    // --- LAB → Label no assembly ---
    else if (strcmp(OP, "LAB") == 0) {
        salvar_asm_label(A1);
    }
    // --- FUN → Label da função ---
    else if (strcmp(OP, "FUN") == 0) {
        salvar_asm_label(A2); // A2 = nome da função
    }
    // --- JUMP ---
    else if (strcmp(OP, "JUMP") == 0) {
        salvar_asm_line("JUMP", A1, "-", "-");
    }
    // --- IN/OUT (pseudo-instruções de I/O) ---
    else if (strcmp(OP, "IN") == 0) {
        salvar_asm_line("IN", RES, "-", "-");
    }
    else if (strcmp(OP, "OUT") == 0) {
        salvar_asm_line("OUT", A1, "-", "-");
    }
    // --- END, HALT, ALLOC ---
    else if (strcmp(OP, "END") == 0) {
        // Nada no assembly (é só marcação)
    }
    else if (strcmp(OP, "HALT") == 0) {
        salvar_asm_raw("HALT");
    }
    else if (strcmp(OP, "ALLOC") == 0) {
        // Alocação será resolvida pelo linker/loader
    }
    // --- 1:1: ADD, SUB, MULT, DIV, LOAD, STORE ---
    else {
        salvar_asm_line(OP, RES, A1, A2); // Formato: OP rd, rs1, rs2
    }
}

// --- AUXILIARES ---
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