#define QUADRUPLAS_IMPL
#include "quaduplas.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>

// Protótipos
char* gera_expressao(Node* node, char* escopo);
void gera_declaracao(Node* node, char* escopo);
void gera_comando(Node* node, char* escopo);

char* gera_expressao(Node* node, char* escopo) {
    if (node == NULL) return "-";

    char* t_res = NULL;
    char* t1 = NULL;
    char* t2 = NULL;

    switch (node->type) {
        case NODE_NUM:
            t_res = newTemp();
            char val_str[32];
            sprintf(val_str, "%d", node->ival);
            emit("ADDI", "$zero", val_str, t_res);
            return t_res;

        case NODE_ID:
            t_res = newTemp();
            emit("LOAD", node->sval, "-", t_res);
            return t_res;

        case NODE_VAR_ARRAY:
            t1 = gera_expressao(node->child2, escopo);
            t_res = newTemp();
            // Simplificação: gera um LOAD com offset
            emit("LOAD", node->child1->sval, t1, t_res);
            return t_res;

        case NODE_SOMA:
        case NODE_SUB:
        case NODE_MULT:
        case NODE_DIV:
            t1 = gera_expressao(node->child1, escopo);
            t2 = gera_expressao(node->child2, escopo);
            t_res = newTemp();
            char* op = (node->type == NODE_SOMA) ? "ADD" :
                       (node->type == NODE_SUB) ? "SUB" :
                       (node->type == NODE_MULT) ? "MULT" : "DIV";
            emit(op, t1, t2, t_res);
            return t_res;

        case NODE_RELACIONAL: {
            t1 = gera_expressao(node->child1, escopo);
            t2 = gera_expressao(node->child2, escopo);
            t_res = newTemp();
            char* rel_op = "-";
            switch(node->child3->type) {
                case NODE_REL_IGL: rel_op = "EQ"; break;
                case NODE_REL_DIF: rel_op = "NEQ"; break;
                case NODE_REL_MENOR: rel_op = "LT"; break;
                case NODE_REL_LEQUAL: rel_op = "LE"; break;
                case NODE_REL_HIGHER: rel_op = "GT"; break;
                case NODE_REL_HEQUAL: rel_op = "GE"; break;
            }
            emit(rel_op, t1, t2, t_res);
            return t_res;
        }

        case NODE_EXPRESSAO_REC:
            t1 = gera_expressao(node->child2, escopo);
            if (node->child1->type == NODE_ID) {
                emit("STORE", t1, node->child1->sval, "-");
            } else {
                // Array
                char* t_idx = gera_expressao(node->child1->child2, escopo);
                emit("STORE", t1, node->child1->child1->sval, t_idx);
            }
            return t1; // Retorna o valor atribuído

        case NODE_ATIVACAO: {
            // Caso especial: input()
            if (strcmp(node->child1->sval, "input") == 0) {
                t_res = newTemp();
                emit("IN", "-", "-", t_res);
                return t_res;
            }
            
            // Caso especial: output()
            if (strcmp(node->child1->sval, "output") == 0) {
                t1 = gera_expressao(node->child2, escopo);
                emit("OUT", t1, "-", "-");
                return "-";
            }

            // Chamada de função genérica
            int n_args = 0;
            Node* arg = node->child2;
            while (arg) {
                char* t_arg = gera_expressao(arg, escopo);
                emit("PARAM", t_arg, "-", "-");
                n_args++;
                arg = arg->sibling;
            }
            t_res = newTemp();
            char n_str[16];
            sprintf(n_str, "%d", n_args);
            emit("CALL", node->child1->sval, n_str, t_res);
            return t_res;
        }

        default:
            return "-";
    }
}

void gera_comando(Node* node, char* escopo) {
    if (node == NULL) return;

    char *L1, *L2, *L3;
    char* t_cond;

    switch (node->type) {
        case NODE_COMPOSTO_DECL:
            gera_comando(node->child1, escopo); // declarações locais
            gera_comando(node->child2, escopo); // comandos
            break;

        case NODE_SELECAO_DECL:
            t_cond = gera_expressao(node->child1, escopo);
            L1 = newLabel();
            L2 = newLabel();
            emit("IFF", t_cond, L1, "-");
            gera_comando(node->child2, escopo); // THEN
            emit("JUMP", L2, "-", "-");
            emit("LAB", L1, "-", "-");
            if (node->child3) {
                gera_comando(node->child3, escopo); // ELSE
            }
            emit("LAB", L2, "-", "-");
            break;

        case NODE_ITERACAO_DECL:
            L1 = newLabel();
            L2 = newLabel();
            emit("LAB", L1, "-", "-");
            t_cond = gera_expressao(node->child1, escopo);
            emit("IFF", t_cond, L2, "-");
            gera_comando(node->child2, escopo);
            emit("JUMP", L1, "-", "-");
            emit("LAB", L2, "-", "-");
            break;

        case NODE_RETORNO_DECL:
            if (node->child1) {
                char* t_ret = gera_expressao(node->child1, escopo);
                emit("RET", t_ret, "-", "-");
            } else {
                emit("RET", "-", "-", "-");
            }
            break;

        case NODE_EXPRESSAO_REC:
        case NODE_ATIVACAO:
        case NODE_RELACIONAL:
        case NODE_SOMA:
        case NODE_SUB:
        case NODE_MULT:
        case NODE_DIV:
            gera_expressao(node, escopo);
            break;

        case NODE_VAR_DECLARACAO:
        case NODE_VAR_DECLARACAO_ARRAY:
            gera_declaracao(node, escopo);
            break;

        default:
            // Percorre filhos
            gera_comando(node->child1, escopo);
            gera_comando(node->child2, escopo);
            gera_comando(node->child3, escopo);
            break;
    }
    gera_comando(node->sibling, escopo);
}

void gera_declaracao(Node* node, char* escopo) {
    if (node == NULL) return;

    switch (node->type) {
        case NODE_VAR_DECLARACAO:
            emit("ALLOC", node->child2->sval, escopo, "-");
            break;
        case NODE_VAR_DECLARACAO_ARRAY:
            emit("ALLOC", node->child2->sval, escopo, "-"); // Simplificado
            break;
        case NODE_FUN_DECLARACAO:
            emit("FUN", "int", node->child2->sval, "-");
            // Parâmetros são mapeados em ALLOC internamente se necessário,
            // mas aqui podemos apenas seguir para o corpo.
            gera_comando(node->child3, node->child2->sval);
            emit("END", node->child2->sval, "-", "-");
            break;
        default:
            break;
    }
}

void generate_code(Node* root) {
    if (root == NULL) return;
    
    // Início do programa
    Node* p = root->child1;
    while (p) {
        if (p->type == NODE_FUN_DECLARACAO) {
            gera_declaracao(p, "global");
        } else if (p->type == NODE_VAR_DECLARACAO || p->type == NODE_VAR_DECLARACAO_ARRAY) {
            gera_declaracao(p, "global");
        }
        p = p->sibling;
    }
    
    emit("HALT", "-", "-", "-");
}
