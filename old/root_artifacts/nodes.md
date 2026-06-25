# DOCUMENTAÇÃO DOS NÓS DA ÁRVORE (AST) E MAPEAMENTO PARA QUÁDRUPLAS

Este arquivo descreve a estrutura de cada nó criado pelo parser e como ele deve ser traduzido pelo gerador de código.

## 1. Estrutura dos Nós (AST)

| Tipo de Nó (NodeType) | Filho 1 (child1) | Filho 2 (child2) | Filho 3 (child3) | Observações |
| :--- | :--- | :--- | :--- | :--- |
| **NODE_PROGRAMA** | declaracao_lista | - | - | Raiz da árvore |
| **NODE_VAR_DECLARACAO** | tipo_especificador | NODE_ID | - | Ex: int x; |
| **NODE_VAR_DECLARACAO_ARRAY** | tipo_especificador | NODE_ID | NODE_NUM | Ex: int x[10]; |
| **NODE_TIPO_INT** | - | - | - | Folha de tipo |
| **NODE_TIPO_VOID** | - | - | - | Folha de tipo |
| **NODE_FUN_DECLARACAO** | tipo_especificador | NODE_ID* | composto_decl | *ID tem params no child1 |
| **NODE_PARAM** | tipo_especificador | NODE_ID | - | Parâmetro simples |
| **NODE_PARAM_ARRAY** | tipo_especificador | NODE_ID | - | Parâmetro array |
| **NODE_COMPOSTO_DECL** | local_declaracoes | statement_lista | - | Bloco { ... } |
| **NODE_SELECAO_DECL** | expressao | statement (if) | statement (else) | Estrutura IF-ELSE |
| **NODE_ITERACAO_DECL** | expressao | statement | - | Estrutura WHILE |
| **NODE_RETORNO_DECL** | expressao (opcional)| - | - | Comando return |
| **NODE_EXPRESSAO_REC** | var | expressao | - | Atribuição (=) |
| **NODE_VAR_ARRAY** | NODE_ID | expressao | - | Acesso x[i] |
| **NODE_RELACIONAL** | expr_esq | expr_dir | op_relacional | Operações <, <=, >, etc. |
| **NODE_SOMA / NODE_SUB** | operando_esq | operando_dir | - | Operações + e - |
| **NODE_MULT / NODE_DIV** | operando_esq | operando_dir | - | Operações * e / |
| **NODE_ATIVACAO** | NODE_ID | args | - | Chamada de função |
| **NODE_ID** | - | - | - | Folha: nome (sval) |
| **NODE_NUM** | - | - | - | Folha: valor (ival) |

---

## 2. Mapeamento para Quádruplas

| Elemento C- | Mapeamento para Quádruplas | Conceito de Implementação |
| :--- | :--- | :--- |
| **Variável Simples** | `(LOAD, x, -, t0)` / `(STORE, t0, x, -)` | Acessa memória via nome/label |
| **Vetor (Array)** | `(ADDI, t_id, t_offset, t_addr)` <br> `(LOAD, t_addr, -, t0)` | Calcula endereço base + offset |
| **Constante (NUM)** | `(ADDI, $zero, val, t0)` | Carrega valor imediato |
| **Aritmética (+,-,*,/)**| `(OP, t1, t2, t3)` | Operação entre temporários |
| **Relacional (<, ==, etc)**| `(OP, t1, t2, t3)` | t3 recebe 1 se verdadeiro, 0 se falso |
| **Atribuição (=)** | `(STORE, t_expr, x, -)` | Salva resultado da expressão na var |
| **IF / ELSE** | `(IFF, t_cond, L_else, -)` <br> `... corpo if ...` <br> `(GOTO, L_fim, -, -)` <br> `(LAB, L_else, -, -)` | Desvios condicionais e incondicionais |
| **WHILE** | `(LAB, L_inc, -, -)` <br> `(IFF, t_cond, L_fim, -)` <br> `... corpo ...` <br> `(GOTO, L_inc, -, -)` <br> `(LAB, L_fim, -, -)` | Laço com retorno ao início |
| **Função (Call)** | `(PARAM, t0, -, -)` <br> `(CALL, nome, n_args, t1)` | Pilha de parâmetros e salto com link |
| **Entrada / Saída** | `(IN, -, -, t0)` / `(OUT, t1, -, -)` | Mapeia p/ I/O do hardware |
| **HALT** | `(HALT, -, -, -)` | Gerado ao fim do `main` |
