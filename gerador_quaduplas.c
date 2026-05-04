#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// Declarando as assinaturas das funções
char* processa_arvore(Node* node, int* regs_vetor, int* ptr_l, char* escopo);
void salvar_arquivo(char* OP, char* ARG1, char* ARG2, char* RES);
char* alocar_reg(int* regs_vetor);
void liberar_reg(char* reg, int* regs_vetor);
char* return_label(int* l);
char* int_to_char(int val);

// Auxiliar para empilhar parâmetros em ordem REVERSA (Direita para Esquerda)
void empilhar_parametros_reverso(Node* arg, int* regs_vetor, int* ptr_l, char* escopo, int* count) {
    if (arg == NULL) return;
    
    // 1. Primeiro, vai até o último argumento (recursão)
    empilhar_parametros_reverso(arg->sibling, regs_vetor, ptr_l, escopo, count);
    
    // 2. Na volta da recursão, processa e empilha (assim o último é o primeiro a ser empilhado)
    char* res_arg = processa_arvore(arg, regs_vetor, ptr_l, escopo);
    salvar_arquivo("STORE_STACK", res_arg, "-", "-");
    liberar_reg(res_arg, regs_vetor);
    (*count)++;
}

// Gatilho inicial
void iniciar_compilador(Node* raiz);

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
            char* nome_var = node->child2->sval; 
            salvar_arquivo("ALLOC", nome_var, escopo, "-");
            break;
        }

        case NODE_VAR_DECLARACAO_ARRAY: {
            char* nome_var = node->child2->sval;
            char* tamanho = int_to_char(node->child3->ival);
            salvar_arquivo("ALLOC", nome_var, tamanho, escopo); 
            break;
        }

        case NODE_FUN_DECLARACAO: {
            char* nome_funcao = node->child2->sval;
            salvar_arquivo("FUN", "int", nome_funcao, "-");
            
            // --- CARREGA PARÂMETROS DA PILHA (ORDEM NORMAL L->R) ---
            // Como empilhamos R->L, o primeiro parâmetro está no topo!
            Node* p = node->child2->child1;
            while (p != NULL) {
                if (p->type == NODE_PARAM || p->type == NODE_PARAM_ARRAY) {
                    char* nome_param = p->child2->sval;
                    char* t_param = alocar_reg(regs_vetor);
                    
                    salvar_arquivo("LOAD_STACK", "-", "-", t_param);
                    salvar_arquivo("STORE", t_param, nome_param, "-");
                    liberar_reg(t_param, regs_vetor);
                }
                p = p->sibling;
            }

            // Salva o endereço de retorno na pilha (protege contra recursão)
            salvar_arquivo("STORE_STACK", "$ra", "-", "-");

            processa_arvore(node->child3, regs_vetor, ptr_l, nome_funcao);
            salvar_arquivo("END", nome_funcao, "-", "-");
            break;
        }

        case NODE_RETORNO_DECL: {
            if (node->child1 != NULL) {
                // 1. Calcula o valor de retorno (pode conter JALs recursivos!)
                char* valor_retorno = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
                // 2. SÓ AGORA restaura $ra (depois de qualquer JAL interno)
                salvar_arquivo("LOAD_STACK", "-", "-", "$ra");
                // 3. Empilha o resultado para o chamador pegar
                salvar_arquivo("STORE_STACK", valor_retorno, "-", "-");
                liberar_reg(valor_retorno, regs_vetor);
            } else {
                salvar_arquivo("LOAD_STACK", "-", "-", "$ra");
            }
            
            salvar_arquivo("RET", "-", "-", "-");
            break;
        }

        case NODE_ATIVACAO: {
            char* nome_funcao = node->child1->sval;
            
            if (strcmp(nome_funcao, "input") == 0) {
                char* temp = alocar_reg(regs_vetor);
                salvar_arquivo("IN", "-", "-", temp);
                return temp;
            } 
            else if (strcmp(nome_funcao, "output") == 0) {
                char* res_arg = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
                salvar_arquivo("STORE_STACK", res_arg, "-", "-");
                liberar_reg(res_arg, regs_vetor);
                
                salvar_arquivo("JAL", nome_funcao, "1", "-");
                return "-";
            }
            
            // --- EMPILHAMENTO REVERSO (OPÇÃO A) ---
            int num_args = 0;
            empilhar_parametros_reverso(node->child2, regs_vetor, ptr_l, escopo, &num_args);
            
            char* num_args_str = int_to_char(num_args);
            salvar_arquivo("JAL", nome_funcao, num_args_str, "-");
            
            // Após o retorno, o resultado está no topo da pilha
            char* temp = alocar_reg(regs_vetor);
            salvar_arquivo("LOAD_STACK", "-", "-", temp);
            
            return temp;
        }

        case NODE_EXPRESSAO_REC: {
            char* valor = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            
            if (node->child1->type == NODE_ID) {
                salvar_arquivo("STORE", valor, node->child1->sval, "-");
            } else if (node->child1->type == NODE_VAR_ARRAY) {
                char* indice = processa_arvore(node->child1->child2, regs_vetor, ptr_l, escopo);
                salvar_arquivo("STORE", valor, node->child1->child1->sval, indice);
                liberar_reg(indice, regs_vetor);
            }
            
            liberar_reg(valor, regs_vetor);
            return valor; 
        }

        case NODE_SOMA: {
            char* valor1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* temp = alocar_reg(regs_vetor);
            salvar_arquivo("ADD", valor1, valor2, temp);
            
            liberar_reg(valor1, regs_vetor);
            liberar_reg(valor2, regs_vetor);
            return temp;
        }

        case NODE_SUB: {
            char* valor1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* temp = alocar_reg(regs_vetor);
            salvar_arquivo("SUB", valor1, valor2, temp);
            
            liberar_reg(valor1, regs_vetor);
            liberar_reg(valor2, regs_vetor);
            return temp;
        }

        case NODE_MULT: {
            char* valor1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* temp = alocar_reg(regs_vetor);
            salvar_arquivo("MULT", valor1, valor2, temp);
            
            liberar_reg(valor1, regs_vetor);
            liberar_reg(valor2, regs_vetor);
            return temp;
        }

        case NODE_DIV: {
            char* valor1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* temp = alocar_reg(regs_vetor);
            salvar_arquivo("DIV", valor1, valor2, temp);
            
            liberar_reg(valor1, regs_vetor);
            liberar_reg(valor2, regs_vetor);
            return temp;
        }
        
        case NODE_ID: {
            char* var = node->sval;
            char* temp = alocar_reg(regs_vetor);
            salvar_arquivo("LOAD", var, "-", temp); 
            return temp;
        }

        case NODE_NUM: {
            char* num = int_to_char(node->ival);
            char* temp = alocar_reg(regs_vetor);
            salvar_arquivo("ADDI", "$zero", num, temp);
            return temp;
        }

        case NODE_VAR_ARRAY: {
            char* indice_temp = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* temp_resultado = alocar_reg(regs_vetor);
            salvar_arquivo("LOAD", node->child1->sval, indice_temp, temp_resultado);
            
            liberar_reg(indice_temp, regs_vetor);
            return temp_resultado;
        }

        case NODE_RELACIONAL: {
            char* valor1 = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            char* temp = alocar_reg(regs_vetor);
            
            if (node->child3->type == NODE_REL_IGL)    salvar_arquivo("EQ", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_DIF)    salvar_arquivo("NEQ", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_MENOR)  salvar_arquivo("LT", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_LEQUAL) salvar_arquivo("LE", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_HIGHER) salvar_arquivo("GT", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_HEQUAL) salvar_arquivo("GE", valor1, valor2, temp);
            
            liberar_reg(valor1, regs_vetor);
            liberar_reg(valor2, regs_vetor);
            return temp; 
        }

        case NODE_SELECAO_DECL: {
            char* temp_condicao = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* label_else = return_label(ptr_l);
            char* label_fim = return_label(ptr_l);

            salvar_arquivo("IFF", temp_condicao, label_else, "-");
            liberar_reg(temp_condicao, regs_vetor);
            
            processa_arvore(node->child2, regs_vetor, ptr_l, escopo);
            salvar_arquivo("JUMP", label_fim, "-", "-");
            
            salvar_arquivo("LAB", label_else, "-", "-");
            if (node->child3 != NULL) {
                processa_arvore(node->child3, regs_vetor, ptr_l, escopo);
            }
            salvar_arquivo("LAB", label_fim, "-", "-");

            break; 
        }

        case NODE_ITERACAO_DECL: {
            char* label_inicio = return_label(ptr_l);
            salvar_arquivo("LAB", label_inicio, "-", "-");

            char* temp_condicao = processa_arvore(node->child1, regs_vetor, ptr_l, escopo);
            char* label_fim = return_label(ptr_l);
            salvar_arquivo("IFF", temp_condicao, label_fim, "-");
            liberar_reg(temp_condicao, regs_vetor);

            processa_arvore(node->child2, regs_vetor, ptr_l, escopo);

            salvar_arquivo("JUMP", label_inicio, "-", "-");
            salvar_arquivo("LAB", label_fim, "-", "-");
            break;
        }

        case NODE_PARAM:
        case NODE_PARAM_ARRAY:
            break;
    }

    return "-";
}

// --- FUNÇÃO DE GATILHO ---
void iniciar_compilador(Node* raiz) {
    // Limpa o arquivo de saída antes de começar
    FILE *f = fopen("saida.quad", "w");
    if (f != NULL) {
        fclose(f);
    }

    int regs_vetor[64];
    int i;
    for(i = 0; i < 64; i++) regs_vetor[i] = 0; // Tudo livre

    int l = 0; 
    processa_arvore(raiz, regs_vetor, &l, "global"); 
}

// --- FUNÇÕES AUXILIARES ---

char* alocar_reg(int* regs_vetor) {
    int i;
    for(i = 0; i < 64; i++) {
        if (regs_vetor[i] == 0) {
            regs_vetor[i] = 1; // Ocupa
            char* temp = (char*) malloc(16);
            sprintf(temp, "$t%d", i);
            return temp;
        }
    }
    return "$overflow"; 
}

void liberar_reg(char* reg, int* regs_vetor) {
    if (reg[0] == '$' && reg[1] == 't') {
        int idx = atoi(&reg[2]);
        if (idx >= 0 && idx < 64) {
            regs_vetor[idx] = 0; // Libera
        }
    }
}

char* int_to_char(int val) {
    char* str = (char*) malloc(16);
    sprintf(str, "%d", val);
    return str;
}

void salvar_arquivo(char* OP, char* ARG1, char* ARG2, char* RES) {
    FILE *f = fopen("saida.quad", "a"); 
    if (f != NULL) {
        fprintf(f, "(%s, %s, %s, %s)\n", OP, ARG1, ARG2, RES);
        fclose(f);
    }
}

char* return_label(int* l) {
    char* label = (char*) malloc(16); 
    sprintf(label, "L%d", *l);
    (*l)++; 
    return label;
}