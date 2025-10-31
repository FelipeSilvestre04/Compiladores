%{
#include <stdlib.h>
#include <stdio.h>

#define NUM 300
#define ID  301
#define SOM 302
#define SUB 303
#define MUL 304
#define DIV 305
#define IGL 306
#define PEV 307
#define APR 308
#define FPR 309
#define FIM 310
#define ERR 311
#define MINOR 313
#define LEQUAL 314
#define HEQUAL 315
#define HIGHER 316
#define REC 317
#define DIF 318
#define VIR 319
#define ACO 320
#define FCO 321
#define ACH 322
#define FCH 323 
#define COM 324
#define BRL 325
#define TAB 326
#define ESP 327
#define IF 328
#define INT 329
#define ELSE 330
#define RET 331
#define VOI 332
#define WHI 333

%}

DIGITO [0-9]
LETRA [a-zA-Z]
OUTRO [^0-9a-zA-Z;/=\-"+*()<>!\[\],{} \t\n]
// para comentarios "/*"([^*]|\*+[^*/])*\*+"/" 
%%
\t			return TAB;
\n 			return BRL;
[ ]+			return ESP;
if return IF;
int return INT;
else return ELSE;
return return RET;
void return VOI;
while return WHI;
"<=" return LEQUAL;
">=" return HEQUAL;
"==" return IGL;
"!=" return DIF;
"<"  return MINOR;
">"  return HIGHER;
"="  return REC;
"+"  return SOM;
"-"  return SUB;
"*"  return MUL;
"/"  return DIV;
";"  return PEV;
","  return VIR;
"("  return APR;
")"  return FPR;
"["  return ACO;
"]"  return FCO;
"{"  return ACH;
"}"  return FCH;
<<EOF>> return FIM;
{DIGITO}+                return NUM;
{LETRA}+		 return ID;
{OUTRO}+                 return ERR;
%%

int main(int argc, char *argv[])
{
    int token, i, buf[100];
    FILE *f_in;

    for (i=0; i<=99; i++) buf[i] = 0;

    if (argc == 2)
    {
        if (f_in = fopen(argv[1], "r")) yyin = f_in;
        else perror(argv[0]);
    }
    else yyin = stdin;

    i = 0;
    while ((token = yylex()) != FIM)
    {
        buf[i] = token;
        i++;
    }

    i = 0;
    while (buf[i] != 0)
    {
        switch(buf[i])
        {
            case NUM:    printf("NUM"); break;
            case ID:     printf("ID");  break;

            case SOM:    printf("+");   break;
            case SUB:    printf("-");   break;
            case MUL:    printf("*");   break;
            case DIV:    printf("/");   break;

            case IGL:    printf("==");  break;
            case REC:    printf("=");   break;

            case MINOR:  printf("<");   break;
            case LEQUAL: printf("<=");  break;
            case HEQUAL: printf(">=");  break;
            case HIGHER: printf(">");   break;
            case DIF:    printf("!=");  break;

            case PEV:    printf(";"); break;
            case VIR:    printf(",");   break;

            case APR:    printf("(");   break;
            case FPR:    printf(")");   break;

            case ACO:    printf("[");   break;
            case FCO:    printf("]");   break;
            case ACH:    printf("{");   break;
            case FCH:    printf("}");   break;
	    case TAB:    printf("\t");   break;
	    case BRL:    printf("\n");   break;
	    case ESP: 	 printf(" ");	 break;
            case ERR:    printf("ERR "); break;
            
            case IF: 	 printf("if"); break;
            case WHI: 	 printf("while"); break;
            case ELSE:	 printf("else"); break;
            case INT: 	 printf("int"); break;
            case RET:	 printf("return"); break;
            case VOI: 	 printf("void"); break;
        }
        i++;
    }

    return 0;
}

