#ifndef AST_H
#define AST_H

typedef enum {
    NODE_PROGRAMA,
    NODE_VAR_DECLARACAO,
    NODE_VAR_DECLARACAO_ARRAY,
    NODE_TIPO_INT,
    NODE_TIPO_VOID,
    NODE_FUN_DECLARACAO,
    NODE_PARAM,
    NODE_PARAM_ARRAY,
    NODE_COMPOSTO_DECL,
    NODE_SELECAO_DECL,
    NODE_ITERACAO_DECL,
    NODE_RETORNO_DECL,
    NODE_EXPRESSAO_REC,
    NODE_VAR_ARRAY,
    NODE_RELACIONAL,
    NODE_REL_LEQUAL,
    NODE_REL_MENOR,
    NODE_REL_HIGHER,
    NODE_REL_HEQUAL,
    NODE_REL_IGL,
    NODE_REL_DIF,
    NODE_SOMA,
    NODE_SUB,
    NODE_MULT,
    NODE_DIV,
    NODE_ATIVACAO,
    NODE_ID,
    NODE_NUM
} NodeType;

typedef struct Node {
    NodeType type;
    int ival;
    char* sval;
    struct Node* child1;
    struct Node* child2;
    struct Node* child3;
    struct Node* sibling;
    int lineno;
} Node;

Node* create_node(NodeType type, Node* c1, Node* c2, Node* c3);
Node* create_leaf_val(NodeType type, int ival);
Node* create_leaf_id(NodeType type, char* sval);
void print_tree(Node* node, int indent);
void semantic_analysis(Node* root);
void generate_code(Node* root);
void imprimirQuadruplas();
void salvarQuadruplas(const char* nomeArquivo);

extern int semantic_error_count;

#endif
