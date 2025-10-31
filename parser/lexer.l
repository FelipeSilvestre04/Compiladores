%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "parser.tab.h"
%}

DIGITO [0-9]
LETRA  [a-zA-Z]
ID_REGRA {LETRA}({LETRA}|{DIGITO})*
NOVALINHA \n
COMENTARIO_BLOCO "/*"([^*]|\*+[^*/])*\*+"/"

%%
{COMENTARIO_BLOCO} {
    for(int i = 0; i < yyleng; i++) {
        if(yytext[i] == '\n') {
            yylineno++;
        }
    }
}
{NOVALINHA}        { yylineno++; }
[ \t]+             { }

"if"     { return IF; }
"int"    { return INT; }
"else"   { return ELSE; }
"return" { return RET; }
"void"   { return VOI; }
"while"  { return WHI; }

"<="     { return LEQUAL; }
">="     { return HEQUAL; }
"=="     { return IGL; }
"!="     { return DIF; }
"<"      { return MENOR; }
">"      { return HIGHER; }
"="      { return REC; }
"+"      { return SOM; }
"-"      { return SUB; }
"*"      { return MUL; }
"/"      { return DIV; }

";"      { return PEV; }
","      { return VIR; }
"("      { return APR; }
")"      { return FPR; }
"["      { return ACO; }
"]"      { return FCO; }
"{"      { return ACH; }
"}"      { return FCH; }

{DIGITO}+ { 
    yylval.ival = atoi(yytext); 
    return NUM; 
}

{ID_REGRA} { 
    yylval.sval = strdup(yytext); 
    return ID; 
}

. { 
    fprintf(stderr, "ERRO LEXICO: Caractere invalido '%s' na linha %d\n", 
            yytext, yylineno);
}

<<EOF>> { return 0; } 

%%

int yywrap() {
    return 1;
}