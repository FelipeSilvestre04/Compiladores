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
    int lineno;
} Node;

Node* create_node(NodeType type, Node* c1, Node* c2, Node* c3);
Node* create_leaf_val(NodeType type, int ival);
Node* create_leaf_id(NodeType type, char* sval);
void print_tree(Node* node, int indent);
void semantic_analysis(Node* root);

Node* ast_root = NULL;
int syntax_error_count = 0;  // Contador de erros sintaticos

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
%nonassoc LOWER_THAN_ELSE
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
    | error PEV { yyerrok; $$ = NULL; }  /* Recuperacao de erro em declaracao */
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
    | error PEV { yyerrok; $$ = NULL; }  /* Recuperacao de erro em statement */
    ;

expressao_decl:
    expressao PEV { $$ = $1; }
    | PEV { $$ = NULL; }
    ;

selecao_decl:
    IF APR expressao FPR statement %prec LOWER_THAN_ELSE { 
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
        yyerror("Erro: Sem memoria para criar no da arvore");
        exit(1);
    }
    n->type = type;
    n->ival = 0;
    n->sval = NULL;
    n->child1 = c1;
    n->child2 = c2;
    n->child3 = c3;
    n->sibling = NULL;
    n->lineno = yylineno;
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
        default: printf("ERRO: No desconhecido (%d)\n", node->type);
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
    int parse_result = yyparse();
    
    if (parse_result == 0 && syntax_error_count == 0) { 
        printf("Analise Sintatica concluida com SUCESSO!\n");
        printf("\nImprimindo Arvore Sintatica Abstrata:\n");
        print_tree(ast_root, 0);
        
        printf("\nIniciando Analise Semantica...\n");
        semantic_analysis(ast_root);
    } else {
        printf("Analise Sintatica concluida com %d erro(s) sintatico(s).\n", syntax_error_count);
    }

    fclose(f_in);
    return 0;
}

void yyerror(const char *s) {
    syntax_error_count++;  // Incrementa contador
    printf("ERRO SINTATICO: %s LINHA: %d\n", yytext, yylineno);
}

typedef struct Symbol {
    char* name;
    char* type; 
    char* scope; 
    char* kind; 
    int lineno;
    struct Symbol* next;
    struct Symbol* params; 
} Symbol;

int function_has_return(Node* node) {
    if (node == NULL) return 0;
    
    if (node->type == NODE_RETORNO_DECL && node->child1 != NULL) {
        return 1;
    }
    
    if (function_has_return(node->child1)) return 1;
    if (function_has_return(node->child2)) return 1;
    if (function_has_return(node->child3)) return 1;
    if (function_has_return(node->sibling)) return 1;
    
    return 0;
}

Symbol* symbol_table = NULL;
int semantic_error_count = 0;  

void semantic_error(char* msg, char* id, int lineno) {
    semantic_error_count++;  
    if (lineno > 0) {
        if (id)
            printf("ERRO SEMANTICO: %s '%s' LINHA: %d\n", msg, id, lineno);
        else
            printf("ERRO SEMANTICO: %s LINHA: %d\n", msg, lineno);
    } else {
        if (id)
            printf("ERRO SEMANTICO: %s '%s'\n", msg, id);
        else
            printf("ERRO SEMANTICO: %s\n", msg);
    }
}

Symbol* create_symbol(char* name, char* type, char* scope, char* kind, int lineno) {
    Symbol* s = (Symbol*) malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = strdup(type);
    s->scope = strdup(scope);
    s->kind = strdup(kind);
    s->lineno = lineno;
    s->next = NULL;
    s->params = NULL;
    return s;
}

void insert_symbol(char* name, char* type, char* scope, char* kind, int lineno) {
    Symbol* s = create_symbol(name, type, scope, kind, lineno);
    s->next = symbol_table;
    symbol_table = s;
}

Symbol* lookup_symbol(char* name, char* scope) {
    Symbol* s = symbol_table;
    while (s != NULL) {
        if (strcmp(s->name, name) == 0) {
            if (strcmp(s->scope, scope) == 0) {
                return s;
            }
        }
        s = s->next;
    }
    
    s = symbol_table;
    while (s != NULL) {
        if (strcmp(s->name, name) == 0) {
            if (strcmp(s->scope, "global") == 0) {
                return s;
            }
        }
        s = s->next;
    }
    return NULL;
}

Symbol* lookup_function(char* name) {
    Symbol* s = symbol_table;
    while (s != NULL) {
        if (strcmp(s->name, name) == 0 && strcmp(s->kind, "fun") == 0) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}

int is_declared_in_scope(char* name, char* scope) {
    Symbol* s = symbol_table;
    while (s != NULL) {
        if (strcmp(s->name, name) == 0 && strcmp(s->scope, scope) == 0) {
            return 1;
        }
        s = s->next;
    }
    return 0;
}

void print_symbol_table() {
    printf("\nTABELA DE SIMBOLOS:\n");
    printf("%-20s %-10s %-20s %-10s %-10s\n", "Nome", "Tipo", "Escopo", "Categoria", "Linha");
    Symbol* s = symbol_table;
    while (s != NULL) {
        if (s->name && strlen(s->name) > 0) {
            printf("%-20s %-10s %-20s %-10s %d\n", s->name, s->type, s->scope, s->kind, s->lineno);
        } else {
            printf("%-20s %-10s %-20s %-10s %d\n", "(vazio)", s->type, s->scope, s->kind, s->lineno);
        }
        s = s->next;
    }
}

char* get_type_from_node(Node* node) {
    if (node->type == NODE_TIPO_INT) return "int";
    if (node->type == NODE_TIPO_VOID) return "void";
    return "unknown";
}

char* get_expression_type(Node* node, char* scope) {
    if (!node) return "void";
    
    switch(node->type) {
        case NODE_NUM: return "int";
        case NODE_ID: {
            Symbol* s = lookup_symbol(node->sval, scope);
            return s ? s->type : "unknown";
        }
        case NODE_VAR_ARRAY: {
             Symbol* s = lookup_symbol(node->child1->sval, scope);
             return s ? s->type : "unknown";
        }
        case NODE_ATIVACAO: {
            Symbol* s = lookup_function(node->child1->sval);
            return s ? s->type : "unknown";
        }
        case NODE_SOMA:
        case NODE_SUB:
        case NODE_MULT:
        case NODE_DIV:
            return "int";
        default:
            return "int"; 
    }
}

void analyze_node(Node* node, char* current_scope) {
    if (node == NULL) return;

    switch(node->type) {
        case NODE_PROGRAMA:
            analyze_node(node->child1, current_scope); 
            break;
            
        case NODE_VAR_DECLARACAO:
        case NODE_VAR_DECLARACAO_ARRAY: {
            char* type = get_type_from_node(node->child1);
            char* name = node->child2->sval;
            
            if (strcmp(type, "void") == 0) {
                semantic_error("declaração invalida de variavel", name, node->lineno);
            } 
            else if (is_declared_in_scope(name, current_scope)) {
                semantic_error("declaração invalida de variavel", name, node->lineno); 
            } 
            else if (lookup_function(name)) {
                 semantic_error("declaração invalida", name, node->lineno); 
            } else {
                insert_symbol(name, type, current_scope, (node->type == NODE_VAR_DECLARACAO_ARRAY) ? "array" : "var", node->lineno);
            }
            break;
        }
        
        case NODE_FUN_DECLARACAO: {
            char* type = get_type_from_node(node->child1);
            char* name = node->child2->sval;
            int fun_lineno = node->child1->lineno; 
            
            if (lookup_function(name)) {
                semantic_error("declaração invalida", name, fun_lineno);
            } else {
                insert_symbol(name, type, "global", "fun", fun_lineno);
                Symbol* fun_sym = symbol_table; 
                
                Node* params = node->child2->child1; 
                Node* param_list = params;
                
                if (param_list && param_list->type != NODE_TIPO_VOID) {
                    Node* p = param_list;
                    while (p) {
                        if (p->type == NODE_PARAM || p->type == NODE_PARAM_ARRAY) {
                            char* p_type = get_type_from_node(p->child1);
                            char* p_name = p->child2->sval;
                            
                            if (strcmp(p_type, "void") == 0) {
                                semantic_error("declaração invalida de variavel", p_name, p->lineno);
                            } else {
                                insert_symbol(p_name, p_type, name, "param", p->lineno);
                                
                                Symbol* param_sym = create_symbol(p_name, p_type, name, "param", p->lineno);
                                
                                if (fun_sym->params == NULL) {
                                    fun_sym->params = param_sym;
                                } else {
                                    Symbol* last = fun_sym->params;
                                    while (last->next) last = last->next;
                                    last->next = param_sym;
                                }
                            }
                        }
                        p = p->sibling;
                    }
                }
            }
            
            analyze_node(node->child3, name);
            
            if (strcmp(type, "int") == 0) {
                if (!function_has_return(node->child3)) {
                    semantic_error("função int sem retorno", name, node->lineno);
                }
            }
            break;
        }
        
        case NODE_COMPOSTO_DECL: {
            analyze_node(node->child1, current_scope); 
            analyze_node(node->child2, current_scope); 
            break;
        }
            
        case NODE_ATIVACAO: {
            char* func_name = node->child1->sval;
            Symbol* fun_sym = lookup_function(func_name);
            
            if (!fun_sym) {
                semantic_error("chamada de função não declarada", func_name, node->lineno);
            } else {
                Node* args = node->child2; 
                
                int arg_count = 0;
                Node* arg = args;
                while (arg) {
                    arg_count++;
                    arg = arg->sibling;
                }
                
                int param_count = 0;
                Symbol* p = fun_sym->params;
                while (p) {
                    param_count++;
                    p = p->next;
                }
                
                if (arg_count != param_count) {
                    semantic_error("chamada invalida", "número de parâmetros invalido", node->lineno);
                } else {
                    arg = args;
                    p = fun_sym->params;
                    while (arg && p) {
                        char* arg_type = get_expression_type(arg, current_scope);
                        if (strcmp(arg_type, p->type) != 0) {
                             if (strcmp(arg_type, "unknown") != 0 && strcmp(p->type, "unknown") != 0) {
                                semantic_error("chamada invalida", "tipo de parâmetro invalido", node->lineno);
                             }
                        }
                        arg = arg->sibling;
                        p = p->next;
                    }
                }
            }
            break;
        }
        
        case NODE_ID: {
            char* name = node->sval;
            Symbol* sym = lookup_symbol(name, current_scope);
            if (!sym) {
                semantic_error("variavel não declarada", name, node->lineno);
            }
            break;
        }
        
        case NODE_VAR_ARRAY: {
            char* name = node->child1->sval;
            Symbol* sym = lookup_symbol(name, current_scope);
            if (!sym) {
                semantic_error("variavel não declarada", name, node->lineno);
            }
            analyze_node(node->child2, current_scope); 
            break;
        }
        
        case NODE_EXPRESSAO_REC: {
            Node* var_node = node->child1;
            Node* expr_node = node->child2;
            
            analyze_node(var_node, current_scope);
            analyze_node(expr_node, current_scope);
            
            char* var_type = "unknown";
            char* var_kind = "var";
            
            if (var_node->type == NODE_ID) {
                Symbol* sym = lookup_symbol(var_node->sval, current_scope);
                if (sym) {
                    var_type = sym->type;
                    var_kind = sym->kind;
                }
                
                if (sym && strcmp(sym->kind, "array") == 0) {
                    semantic_error("atribuição invalida a array", var_node->sval, node->lineno);
                }
            } else if (var_node->type == NODE_VAR_ARRAY) {
                 Symbol* sym = lookup_symbol(var_node->child1->sval, current_scope);
                 if (sym) var_type = sym->type;
            }
            
            char* expr_type = get_expression_type(expr_node, current_scope);
            
            if (strcmp(var_type, "int") == 0 && strcmp(expr_type, "void") == 0) {
                 semantic_error("atribuição invalida", NULL, node->lineno);
            }
            break;
        }

        case NODE_RETORNO_DECL: {
            if (strcmp(current_scope, "global") != 0) {
                Symbol* fun_sym = lookup_function(current_scope);
                if (fun_sym) {
                    if (node->child1) { 
                        if (strcmp(fun_sym->type, "void") == 0) {
                            semantic_error("chamada invalida", "parâmetro de retorno da função não previsto", node->lineno);
                        } else {
                        }
                    } else {
                        if (strcmp(fun_sym->type, "int") == 0) {
                        }
                    }
                }
            }
            break;
        }
        
        default:
            analyze_node(node->child1, current_scope);
            analyze_node(node->child2, current_scope);
            analyze_node(node->child3, current_scope);
            break;
    }
    analyze_node(node->sibling, current_scope);
}

void semantic_analysis(Node* root) {
    insert_symbol("input", "int", "global", "fun", 0);
    
    insert_symbol("output", "void", "global", "fun", 0);
    Symbol* out_sym = lookup_function("output");
    Symbol* param = create_symbol("x", "int", "output", "param", 0);
    out_sym->params = param;
    
    analyze_node(root, "global");
    
    Symbol* main_sym = lookup_function("main");
    if (main_sym == NULL) {
        semantic_error("função main() não declarada", NULL, 0); 
    } else {
        if (strcmp(main_sym->type, "void") != 0) {
            semantic_error("função main deve ser do tipo void", "main", main_sym->lineno);
        }
        if (main_sym->params != NULL) {
            semantic_error("função main não deve ter parâmetros", "main", main_sym->lineno);
        }
    }
    
    print_symbol_table();
    
    if (semantic_error_count == 0) {
        printf("\nAnalise Semantica concluida com SUCESSO! Nenhum erro detectado.\n");
    } else {
        printf("\nAnalise Semantica concluida com %d erro(s).\n", semantic_error_count);
    }
}
