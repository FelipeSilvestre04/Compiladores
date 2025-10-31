%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);
extern int yylineno;
extern char* yytext;
extern FILE *yyin;
%}

%union {
    int ival;
    char* sval; 
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

%nonassoc LEQUAL HEQUAL MENOR HIGHER IGL DIF
%left SOM SUB
%left MUL DIV
%right REC
%nonassoc ELSE 

%start programa

%%

programa:
    declaracao_lista
    ;

declaracao_lista:
    declaracao_lista declaracao
    | declaracao
    ;

declaracao:
    var_declaracao
    | fun_declaracao
    ;

var_declaracao:
    tipo_especificador ID PEV
    | tipo_especificador ID ACO NUM FCO PEV
    ;

tipo_especificador:
    INT
    | VOI
    ;

fun_declaracao:
    tipo_especificador ID APR params FPR composto_decl
    ;

params:
    param_lista
    | VOI
    ;

param_lista:
    param_lista VIR param
    | param
    ;

param:
    tipo_especificador ID
    | tipo_especificador ID ACO FCO
    ;

composto_decl:
    ACH local_declaracoes statement_lista FCH
    ;

local_declaracoes:
    local_declaracoes var_declaracao
    | 
    ;

statement_lista:
    statement_lista statement
    | 
    ;

statement:
    expressao_decl
    | composto_decl
    | selecao_decl
    | iteracao_decl
    | retorno_decl
    ;

expressao_decl:
    expressao PEV
    | PEV
    ;

selecao_decl:
    IF APR expressao FPR statement
    | IF APR expressao FPR statement ELSE statement
    ;

iteracao_decl:
    WHI APR expressao FPR statement
    ;

retorno_decl:
    RET PEV
    | RET expressao PEV
    ;

expressao:
    var REC expressao
    | simples_expressao
    ;

var:
    ID
    | ID ACO expressao FCO
    ;

simples_expressao:
    soma_expressao relacional soma_expressao
    | soma_expressao
    ;

relacional:
    LEQUAL | MENOR | HIGHER | HEQUAL | IGL | DIF
    ;

soma_expressao:
    soma_expressao soma termo
    | termo
    ;

soma:
    SOM | SUB
    ;

termo:
    termo mult fator
    | fator
    ;

mult:
    MUL | DIV
    ;

fator:
    APR expressao FPR
    | var
    | ativacao
    | NUM
    ;

ativacao:
    ID APR args FPR
    ;

args:
    arg_lista
    | 
    ;

arg_lista:
    arg_lista VIR expressao
    | expressao
    ;

%%

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