#include <stdio.h>
#include <stdlib.h>

// Mock da estrutura da Árvore e Tipos (Com todos os nós)
typedef enum { 
    NODE_PROGRAMA,
    NODE_VAR_DECLARACAO, NODE_VAR_DECLARACAO_ARRAY,
    NODE_FUN_DECLARACAO, NODE_PARAM, NODE_PARAM_ARRAY,
    NODE_COMPOSTO_DECL,
    NODE_EXPRESSAO_REC, 
    NODE_SOMA, NODE_SUB, NODE_MULT, NODE_DIV, 
    NODE_NUM, NODE_ID, NODE_VAR_ARRAY,
    NODE_SELECAO_DECL, // IF
    NODE_ITERACAO_DECL, // WHILE
    NODE_RETORNO_DECL,
    NODE_ATIVACAO,     // Chamada de Função
    NODE_RELACIONAL,   // Nó pai de comparação
    NODE_REL_IGL, NODE_REL_DIF, NODE_REL_MENOR, 
    NODE_REL_LEQUAL, NODE_REL_HIGHER, NODE_REL_HEQUAL
} NodeType;

typedef struct Node {
    NodeType type;
    int ival;
    char* sval; 
    struct Node* child1;
    struct Node* child2;
    struct Node* child3; 
    struct Node* sibling;
} Node;

// Declarando as assinaturas das funções
char* processa_arvore(Node* node, int* ptr_k, int* ptr_l, char* escopo);
void salvar_arquivo(char* OP, char* ARG1, char* ARG2, char* RES);
char* return_temp(int* k);
char* return_label(int* l);
char* int_to_char(int val);

// Gatilho inicial
void iniciar_compilador(Node* raiz);

// --- FUNÇÃO PRINCIPAL ---
char* processa_arvore(Node* node, int* ptr_k, int* ptr_l, char* escopo) {
    if (node == NULL) return "-";
    
    switch(node->type) {

        case NODE_PROGRAMA: {
            Node* current = node->child1;
            while (current != NULL) {
                processa_arvore(current, ptr_k, ptr_l, escopo);
                current = current->sibling;
            }
            break;
        }

        case NODE_COMPOSTO_DECL: {
            Node* current = node->child1;
            while (current != NULL) {
                processa_arvore(current, ptr_k, ptr_l, escopo);
                current = current->sibling;
            }
            
            current = node->child2;
            while (current != NULL) {
                processa_arvore(current, ptr_k, ptr_l, escopo);
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
            // Salva o tamanho no ARG2 e o escopo no RES (ou vice-versa, dependendo do seu padrão)
            salvar_arquivo("ALLOC", nome_var, tamanho, escopo); 
            break;
        }

        case NODE_FUN_DECLARACAO: {
            char* nome_funcao = node->child2->sval;
            salvar_arquivo("FUN", "int", nome_funcao, "-");
            
            // A MÁGICA DO ESCOPO: Aqui nós passamos 'nome_funcao' para os filhos em vez do 'escopo' velho!
            processa_arvore(node->child3, ptr_k, ptr_l, nome_funcao);
            
            salvar_arquivo("END", nome_funcao, "-", "-");
            break;
        }

        case NODE_RETORNO_DECL: {
            if (node->child1 != NULL) {
                char* valor_retorno = processa_arvore(node->child1, ptr_k, ptr_l, escopo);
                salvar_arquivo("RET", valor_retorno, "-", "-");
            } else {
                salvar_arquivo("RET", "-", "-", "-"); 
            }
            break;
        }

        case NODE_ATIVACAO: {
            char* nome_funcao = node->child1->sval;
            
            Node* arg = node->child2;
            int num_args = 0;
            while (arg != NULL) {
                char* res_arg = processa_arvore(arg, ptr_k, ptr_l, escopo);
                salvar_arquivo("PARAM", res_arg, "-", "-");
                num_args++;
                arg = arg->sibling; 
            }
            
            char* temp = return_temp(ptr_k);
            char* num_args_str = int_to_char(num_args);
            salvar_arquivo("CALL", nome_funcao, num_args_str, temp);
            
            return temp;
        }

        case NODE_EXPRESSAO_REC: {
            char* destino = processa_arvore(node->child1, ptr_k, ptr_l, escopo);
            char* valor = processa_arvore(node->child2, ptr_k, ptr_l, escopo);
            salvar_arquivo("STORE", valor, destino, "-");
            break; 
        }

        case NODE_SOMA: {
            char* valor1 = processa_arvore(node->child1, ptr_k, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, ptr_k, ptr_l, escopo);
            char* temp = return_temp(ptr_k);
            salvar_arquivo("ADD", valor1, valor2, temp);
            return temp;
        }

        case NODE_SUB: {
            char* valor1 = processa_arvore(node->child1, ptr_k, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, ptr_k, ptr_l, escopo);
            char* temp = return_temp(ptr_k);
            salvar_arquivo("SUB", valor1, valor2, temp);
            return temp;
        }

        case NODE_MULT: {
            char* valor1 = processa_arvore(node->child1, ptr_k, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, ptr_k, ptr_l, escopo);
            char* temp = return_temp(ptr_k);
            salvar_arquivo("MULT", valor1, valor2, temp);
            return temp;
        }

        case NODE_DIV: {
            char* valor1 = processa_arvore(node->child1, ptr_k, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, ptr_k, ptr_l, escopo);
            char* temp = return_temp(ptr_k);
            salvar_arquivo("DIV", valor1, valor2, temp);
            return temp;
        }
        
        case NODE_ID: {
            char* var = node->sval;
            char* temp = return_temp(ptr_k);
            // O LOAD pode usar o escopo futuramente para procurar na tabela de símbolos!
            salvar_arquivo("LOAD", var, "-", temp); 
            return temp;
        }

        case NODE_NUM: {
            char* num = int_to_char(node->ival);
            char* temp = return_temp(ptr_k);
            salvar_arquivo("ADDI", "$zero", num, temp);
            return temp;
        }

        case NODE_VAR_ARRAY: {
            // Lendo de um vetor: vetor[i]
            char* indice_temp = processa_arvore(node->child2, ptr_k, ptr_l, escopo);
            char* temp_resultado = return_temp(ptr_k);
            
            // Lemos a memória passando o nome do vetor e o temporário que contém a posição [i]
            salvar_arquivo("LOAD", node->child1->sval, indice_temp, temp_resultado);
            return temp_resultado;
        }

        case NODE_RELACIONAL: {
            char* valor1 = processa_arvore(node->child1, ptr_k, ptr_l, escopo);
            char* valor2 = processa_arvore(node->child2, ptr_k, ptr_l, escopo);
            char* temp = return_temp(ptr_k);
            
            if (node->child3->type == NODE_REL_IGL)    salvar_arquivo("EQ", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_DIF)    salvar_arquivo("NEQ", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_MENOR)  salvar_arquivo("LT", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_LEQUAL) salvar_arquivo("LE", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_HIGHER) salvar_arquivo("GT", valor1, valor2, temp);
            if (node->child3->type == NODE_REL_HEQUAL) salvar_arquivo("GE", valor1, valor2, temp);
            
            return temp; 
        }

        case NODE_SELECAO_DECL: {
            char* temp_condicao = processa_arvore(node->child1, ptr_k, ptr_l, escopo);
            char* label_else = return_label(ptr_l);
            char* label_fim = return_label(ptr_l);

            salvar_arquivo("IFF", temp_condicao, label_else, "-");
            processa_arvore(node->child2, ptr_k, ptr_l, escopo);
            salvar_arquivo("JUMP", label_fim, "-", "-");
            
            salvar_arquivo("LAB", label_else, "-", "-");
            if (node->child3 != NULL) {
                processa_arvore(node->child3, ptr_k, ptr_l, escopo);
            }
            salvar_arquivo("LAB", label_fim, "-", "-");

            break; 
        }

        case NODE_ITERACAO_DECL: {
            char* label_inicio = return_label(ptr_l);
            salvar_arquivo("LAB", label_inicio, "-", "-");

            char* temp_condicao = processa_arvore(node->child1, ptr_k, ptr_l, escopo);

            char* label_fim = return_label(ptr_l);
            salvar_arquivo("IFF", temp_condicao, label_fim, "-");

            processa_arvore(node->child2, ptr_k, ptr_l, escopo);

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
    int k = 0; // Inicia os temporários em $t0
    int l = 0; // Inicia as labels em L0
    
    // O compilador sempre começa no escopo global!
    processa_arvore(raiz, &k, &l, "global"); 
}

// --- FUNÇÕES AUXILIARES ---

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

char* return_temp(int* k) {
    char* temp = (char*) malloc(16); 
    sprintf(temp, "$t%d", *k);
    (*k)++; 
    return temp;
}

char* return_label(int* l) {
    char* label = (char*) malloc(16); 
    sprintf(label, "L%d", *l);
    (*l)++; 
    return label;
}