%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);
extern int yylineno;
extern char* yytext;
extern FILE *yyin;

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
} Node;

Node* create_node(NodeType type, Node* c1, Node* c2, Node* c3);
Node* create_leaf_val(NodeType type, int ival);
Node* create_leaf_id(NodeType type, char* sval);
void print_tree(Node* node, int indent);

Node* ast_root = NULL;

%}

%union {
    int ival;
    char* sval; 
    struct Node* nptr;
}

%token <ival> NUM
%token <sval> ID
%token IF ELSE INT RET VOI WHI
%token SOM SUB MUL DIV
%token MENOR LEQUAL HIGHER HEQUAL IGL DIF
%token REC
%token PEV VIR
%token APR FPR
%token ACO FCO
%token ACH FCH

%type <nptr> programa declaracao_lista declaracao var_declaracao 
%type <nptr> tipo_especificador fun_declaracao params param_lista param
%type <nptr> composto_decl local_declaracoes statement_lista statement
%type <nptr> expressao_decl selecao_decl iteracao_decl retorno_decl
%type <nptr> expressao var simples_expressao relacional soma_expressao 
%type <nptr> soma termo mult fator ativacao args arg_lista

%nonassoc LEQUAL HEQUAL MENOR HIGHER IGL DIF
%left SOM SUB
%left MUL DIV
%right REC
%nonassoc ELSE 

%start programa

%%

programa:
    declaracao_lista { 
        $$ = create_node(NODE_PROGRAMA, $1, NULL, NULL); 
        ast_root = $$;
    }
    ;

declaracao_lista:
    declaracao_lista declaracao {
        Node* head = $1;
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = $2;
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    | declaracao { $$ = $1; }
    ;

declaracao:
    var_declaracao { $$ = $1; }
    | fun_declaracao { $$ = $1; }
    ;

var_declaracao:
    tipo_especificador ID PEV { 
        $$ = create_node(NODE_VAR_DECLARACAO, $1, create_leaf_id(NODE_ID, $2), NULL); 
    }
    | tipo_especificador ID ACO NUM FCO PEV { 
        $$ = create_node(NODE_VAR_DECLARACAO_ARRAY, $1, create_leaf_id(NODE_ID, $2), create_leaf_val(NODE_NUM, $4)); 
    }
    ;

tipo_especificador:
    INT { $$ = create_node(NODE_TIPO_INT, NULL, NULL, NULL); }
    | VOI { $$ = create_node(NODE_TIPO_VOID, NULL, NULL, NULL); }
    ;

fun_declaracao:
    tipo_especificador ID APR params FPR composto_decl {
        Node* id_node = create_leaf_id(NODE_ID, $2);
        id_node->child1 = $4;
        $$ = create_node(NODE_FUN_DECLARACAO, $1, id_node, $6);
    }
    ;

params:
    param_lista { $$ = $1; }
    | VOI { $$ = create_node(NODE_TIPO_VOID, NULL, NULL, NULL); }
    ;

param_lista:
    param_lista VIR param {
        Node* head = $1;
        while (head->sibling) head = head->sibling;
        head->sibling = $3;
        $$ = $1;
    }
    | param { $$ = $1; }
    ;

param:
    tipo_especificador ID { 
        $$ = create_node(NODE_PARAM, $1, create_leaf_id(NODE_ID, $2), NULL); 
    }
    | tipo_especificador ID ACO FCO { 
        $$ = create_node(NODE_PARAM_ARRAY, $1, create_leaf_id(NODE_ID, $2), NULL); 
    }
    ;

composto_decl:
    ACH local_declaracoes statement_lista FCH { 
        $$ = create_node(NODE_COMPOSTO_DECL, $2, $3, NULL); 
    }
    ;

local_declaracoes:
    local_declaracoes var_declaracao {
        Node* head = $1;
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = $2;
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    | { $$ = NULL; }
    ;

statement_lista:
    statement_lista statement {
        Node* head = $1;
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = $2;
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    | { $$ = NULL; }
    ;

statement:
    expressao_decl { $$ = $1; }
    | composto_decl { $$ = $1; }
    | selecao_decl { $$ = $1; }
    | iteracao_decl { $$ = $1; }
    | retorno_decl { $$ = $1; }
    ;

expressao_decl:
    expressao PEV { $$ = $1; }
    | PEV { $$ = NULL; }
    ;

selecao_decl:
    IF APR expressao FPR statement { 
        $$ = create_node(NODE_SELECAO_DECL, $3, $5, NULL); 
    }
    | IF APR expressao FPR statement ELSE statement { 
        $$ = create_node(NODE_SELECAO_DECL, $3, $5, $7); 
    }
    ;

iteracao_decl:
    WHI APR expressao FPR statement { 
        $$ = create_node(NODE_ITERACAO_DECL, $3, $5, NULL); 
    }
    ;

retorno_decl:
    RET PEV { 
        $$ = create_node(NODE_RETORNO_DECL, NULL, NULL, NULL); 
    }
    | RET expressao PEV { 
        $$ = create_node(NODE_RETORNO_DECL, $2, NULL, NULL); 
    }
    ;

expressao:
    var REC expressao { 
        $$ = create_node(NODE_EXPRESSAO_REC, $1, $3, NULL); 
    }
    | simples_expressao { $$ = $1; }
    ;

var:
    ID { $$ = create_leaf_id(NODE_ID, $1); }
    | ID ACO expressao FCO { 
        $$ = create_node(NODE_VAR_ARRAY, create_leaf_id(NODE_ID, $1), $3, NULL); 
    }
    ;

simples_expressao:
    soma_expressao relacional soma_expressao { 
        $$ = create_node(NODE_RELACIONAL, $1, $3, $2); 
    }
    | soma_expressao { $$ = $1; }
    ;

relacional:
    LEQUAL { $$ = create_node(NODE_REL_LEQUAL, NULL, NULL, NULL); }
    | MENOR { $$ = create_node(NODE_REL_MENOR, NULL, NULL, NULL); }
    | HIGHER { $$ = create_node(NODE_REL_HIGHER, NULL, NULL, NULL); }
    | HEQUAL { $$ = create_node(NODE_REL_HEQUAL, NULL, NULL, NULL); }
    | IGL { $$ = create_node(NODE_REL_IGL, NULL, NULL, NULL); }
    | DIF { $$ = create_node(NODE_REL_DIF, NULL, NULL, NULL); }
    ;

soma_expressao:
    soma_expressao soma termo { 
        $$ = create_node($2->type, $1, $3, NULL); 
    }
    | termo { $$ = $1; }
    ;

soma:
    SOM { $$ = create_node(NODE_SOMA, NULL, NULL, NULL); }
    | SUB { $$ = create_node(NODE_SUB, NULL, NULL, NULL); }
    ;

termo:
    termo mult fator { 
        $$ = create_node($2->type, $1, $3, NULL); 
    }
    | fator { $$ = $1; }
    ;

mult:
    MUL { $$ = create_node(NODE_MULT, NULL, NULL, NULL); }
    | DIV { $$ = create_node(NODE_DIV, NULL, NULL, NULL); }
    ;

fator:
    APR expressao FPR { $$ = $2; }
    | var { $$ = $1; }
    | ativacao { $$ = $1; }
    | NUM { $$ = create_leaf_val(NODE_NUM, $1); }
    ;

ativacao:
    ID APR args FPR { 
        $$ = create_node(NODE_ATIVACAO, create_leaf_id(NODE_ID, $1), $3, NULL); 
    }
    ;

args:
    arg_lista { $$ = $1; }
    | { $$ = NULL; }
    ;

arg_lista:
    arg_lista VIR expressao {
        Node* head = $1;
        while (head->sibling) head = head->sibling;
        head->sibling = $3;
        $$ = $1;
    }
    | expressao { $$ = $1; }
    ;
%%

Node* create_node(NodeType type, Node* c1, Node* c2, Node* c3) {
    Node* n = (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        yyerror("Erro: Sem memória para criar nó da árvore");
        exit(1);
    }
    n->type = type;
    n->ival = 0;
    n->sval = NULL;
    n->child1 = c1;
    n->child2 = c2;
    n->child3 = c3;
    n->sibling = NULL;
    return n;
}

Node* create_leaf_val(NodeType type, int ival) {
    Node* n = create_node(type, NULL, NULL, NULL);
    n->ival = ival;
    return n;
}

Node* create_leaf_id(NodeType type, char* sval) {
    Node* n = create_node(type, NULL, NULL, NULL);
    n->sval = strdup(sval); 
    return n;
}

void print_tree(Node* node, int indent) {
    if (node == NULL) {
        return;
    }

    for(int i = 0; i < indent; i++) {
        printf("  ");
    }

    switch(node->type) {
        case NODE_PROGRAMA: printf("PROGRAMA\n"); break;
        case NODE_VAR_DECLARACAO: printf("VAR_DECLARACAO\n"); break;
        case NODE_VAR_DECLARACAO_ARRAY: printf("VAR_DECLARACAO_ARRAY\n"); break;
        case NODE_TIPO_INT: printf("TIPO: INT\n"); break;
        case NODE_TIPO_VOID: printf("TIPO: VOID\n"); break;
        case NODE_FUN_DECLARACAO: printf("FUN_DECLARACAO\n"); break;
        case NODE_PARAM: printf("PARAM\n"); break;
        case NODE_PARAM_ARRAY: printf("PARAM_ARRAY\n"); break;
        case NODE_COMPOSTO_DECL: printf("COMPOSTO_DECL\n"); break;
        case NODE_SELECAO_DECL: printf("SELECAO_DECL (IF)\n"); break;
        case NODE_ITERACAO_DECL: printf("ITERACAO_DECL (WHILE)\n"); break;
        case NODE_RETORNO_DECL: printf("RETORNO_DECL\n"); break;
        case NODE_EXPRESSAO_REC: printf("ATRIBUICAO (=)\n"); break;
        case NODE_VAR_ARRAY: printf("VAR_ARRAY (acesso)\n"); break;
        case NODE_RELACIONAL: printf("RELACIONAL\n"); break;
        case NODE_REL_LEQUAL: printf("RELACIONAL (<=)\n"); break;
        case NODE_REL_MENOR: printf("RELACIONAL (<)\n"); break;
        case NODE_REL_HIGHER: printf("RELACIONAL (>)\n"); break;
        case NODE_REL_HEQUAL: printf("RELACIONAL (>=)\n"); break;
        case NODE_REL_IGL: printf("RELACIONAL (==)\n"); break;
        case NODE_REL_DIF: printf("RELACIONAL (!=)\n"); break;
        case NODE_SOMA: printf("OPERADOR (+)\n"); break;
        case NODE_SUB: printf("OPERADOR (-)\n"); break;
        case NODE_MULT: printf("OPERADOR (*)\n"); break;
        case NODE_DIV: printf("OPERADOR (/)\n"); break;
        case NODE_ATIVACAO: printf("ATIVACAO (call)\n"); break;
        case NODE_ID: printf("ID (%s)\n", node->sval); break;
        case NODE_NUM: printf("NUM (%d)\n", node->ival); break;
        default: printf("ERRO: Nó desconhecido (%d)\n", node->type);
    }

    print_tree(node->child1, indent + 1);
    print_tree(node->child2, indent + 1);
    print_tree(node->child3, indent + 1);
    print_tree(node->sibling, indent);
}

int main(int argc, char *argv[]) {
    FILE *f_in;
    if (argc == 2) {
        if ( !(f_in = fopen(argv[1], "r")) ) {
            perror(argv[1]);
            return 1;
        }
        yyin = f_in;
    } else {
        printf("Uso: ./meu_parser <arquivo_de_entrada>\n");
        return 1;
    }

    printf("Iniciando analise sintatica de: %s\n", argv[1]);
    if (yyparse() == 0) { 
        printf("Analise Sintatica concluida com SUCESSO!\n");
        printf("\nImprimindo Arvore Sintatica Abstrata:\n");
        print_tree(ast_root, 0);
    } else {
        printf("Analise Sintatica falhou.\n");
    }

    fclose(f_in);
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "ERRO SINTATICO: %s na linha %d. Token lido: '%s'\n", 
            s, yylineno, yytext);
}