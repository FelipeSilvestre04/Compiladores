# Guia de Estudo: Geração de Código Intermediário (Quádruplas)

Este documento detalha a teoria e a estrutura necessária para implementar o módulo de Geração de Código Intermediário no compilador C-.

---

## 1. Motivação e Conceito
O Código Intermediário (CI) atua como uma ponte entre o **Front-end** (que entende a linguagem humana) e o **Back-end** (que entende o hardware).

### Por que Quádruplas?
As quádruplas são uma forma de **Código de Três Endereços**. Elas forçam operações complexas a serem quebradas. 
- **Exemplo C-**: `x = a + b * c;`
- **Exemplo Quádruplas**:
  1. `MULT, b, c, $t0`
  2. `ADD, a, $t0, $t1`
  3. `STORE, $t1, x, -`

---

## 2. A Estrutura da Árvore Sintática Abstrata (AST)

A AST é a sua "planta baixa". No seu projeto, ela é definida pela struct `Node`:

```c
typedef struct Node {
    NodeType type;       // Tipo do nó (NODE_SOMA, NODE_IF, etc.)
    int ival;            // Usado se o nó for um número (NUM)
    char* sval;          // Usado se o nó for um identificador (ID)
    struct Node* child1; // Primeiro filho
    struct Node* child2; // Segundo filho
    struct Node* child3; // Terceiro filho
    struct Node* sibling;// Próximo comando no mesmo nível (irmão)
} Node;
```

### Como interpretar a árvore:
- **Expressões**: São geralmente profundas. Para gerar código de `5 + x`, você primeiro precisa "descer" até o `5` e o `x`.
- **Comandos**: São sequenciais. O ponteiro `sibling` conecta um comando ao próximo (ex: uma linha de código à próxima).

---

## 3. A Tabela de Símbolos

A Tabela de Símbolos é um dicionário que você consulta sempre que encontra um `ID` na árvore.

### O que ela contém:
- **Nome**: O identificador (ex: "x").
- **Escopo**: Onde ela foi declarada (ex: "global" ou "main"). Isso evita confundir duas variáveis com o mesmo nome em funções diferentes.
- **Categoria (Kind)**: Se é uma variável simples (`var`), um vetor (`array`) ou uma função (`fun`).
- **Tipo**: `int` ou `void`.

### Uso na Geração:
Quando você vê `x = 10`, você olha na tabela: 
1. "Quem é x?" -> "É uma variável global". 
2. Então você emite: `STORE, $t0, x, -`. 
Se a tabela dissesse que `x` é um `array`, você saberia que a instrução precisaria de um índice.

---

## 4. A Lógica do "Caminhante" (Traversal)

Para gerar o código, você implementa funções que percorrem a árvore. A lógica muda dependendo do que você está processando:

### A. Processando Expressões (Bottom-Up)
Para expressões matemáticas, você usa uma lógica **pós-fixa**:
1. Visita o filho esquerdo.
2. Visita o filho direito.
3. **Emite** a operação com os resultados dos filhos.

**Exemplo**: Para um nó `NODE_SOMA`:
- `t1 = gera_codigo(filho1)`
- `t2 = gera_codigo(filho2)`
- `res = novo_temporario()`
- `emitir("ADD", t1, t2, res)`
- `retornar res`

### B. Processando Controle de Fluxo (Top-Down)
Para `IF` e `WHILE`, você precisa gerenciar o "pulo" antes de processar os filhos.

**Exemplo de um IF**:
1. Gera código para a condição (ex: `x > 0`).
2. Cria dois rótulos: `L_ELSE` e `L_FIM`.
3. Emite `IFF` (Se a condição for falsa, pule para `L_ELSE`).
4. Visita o filho do bloco "Verdadeiro".
5. Emite `JUMP, L_FIM`.
6. Emite o rótulo `L_ELSE`.
7. Visita o filho do bloco "Else".
8. Emite o rótulo `L_FIM`.

---

## 5. Resumo do que você precisa implementar

1. **Gerenciador de Temporários**: Uma função que retorna `$t0`, `$t1`, etc., incrementando um contador.
2. **Gerenciador de Rótulos**: Uma função que retorna `L0`, `L1`, etc.
3. **Função `emitir`**: Apenas para formatar e salvar a quádrupla em uma lista ou arquivo.
4. **O Grande Switch-Case**: Uma função recursiva que olha o `node->type` e decide qual das lógicas acima aplicar.

---
**Dica de Ouro**: O segredo da geração de código é a **recursão**. Cada nó da árvore confia que seus filhos saberão gerar seus próprios códigos e retornarão apenas o nome do temporário onde o resultado foi guardado.
