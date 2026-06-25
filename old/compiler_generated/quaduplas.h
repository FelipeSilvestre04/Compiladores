#ifndef QUADRUPLAS_H
#define QUADRUPLAS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUADS 10000

typedef struct {
    char op[16];
    char arg1[64];
    char arg2[64];
    char res[64];
} Quadrupla;

extern Quadrupla listaQuads[MAX_QUADS];
extern int quadCount;
extern int tempCount;
extern int labelCount;

// Funções de manipulação de quádruplas
void emit(const char* op, const char* arg1, const char* arg2, const char* res);
char* newTemp();
char* newLabel();
void salvarQuadruplas(const char* nomeArquivo);
void imprimirQuadruplas();

// --- Implementação (Pode ser movida para um .c depois se preferir) ---

#ifdef QUADRUPLAS_IMPL
Quadrupla listaQuads[MAX_QUADS];
int quadCount = 0;
int tempCount = 0;
int labelCount = 0;

void emit(const char* op, const char* arg1, const char* arg2, const char* res) {
    if (quadCount >= MAX_QUADS) {
        printf("Erro: Limite de quádruplas excedido!\n");
        return;
    }
    strncpy(listaQuads[quadCount].op, op ? op : "-", 15);
    strncpy(listaQuads[quadCount].arg1, arg1 ? arg1 : "-", 63);
    strncpy(listaQuads[quadCount].arg2, arg2 ? arg2 : "-", 63);
    strncpy(listaQuads[quadCount].res, res ? res : "-", 63);
    quadCount++;
}

char* newTemp() {
    char* t = malloc(16);
    sprintf(t, "$t%d", tempCount++);
    return t;
}

char* newLabel() {
    char* l = malloc(16);
    sprintf(l, "L%d", labelCount++);
    return l;
}

void salvarQuadruplas(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) return;
    for(int i = 0; i < quadCount; i++) {
        fprintf(f, "(%s, %s, %s, %s)\n", 
                listaQuads[i].op, listaQuads[i].arg1, 
                listaQuads[i].arg2, listaQuads[i].res);
    }
    fclose(f);
}

void imprimirQuadruplas() {
    printf("\n--- QUÁDRUPLAS GERADAS ---\n");
    for(int i = 0; i < quadCount; i++) {
        printf("%d: (%s, %s, %s, %s)\n", i,
                listaQuads[i].op, listaQuads[i].arg1, 
                listaQuads[i].arg2, listaQuads[i].res);
    }
}
#endif

#endif
