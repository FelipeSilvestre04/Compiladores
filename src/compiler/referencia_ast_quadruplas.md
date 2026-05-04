# Referência Completa: AST e Quádruplas (C-)

Este documento é o seu manual de consulta rápida para programar a geração de código. Ele lista todos os nós possíveis que a Árvore Sintática Abstrata (AST) pode ter e todas as instruções de Quádruplas que você precisará gerar.

---

## 1. Instruções de Quádruplas (O seu "Assembly Virtual")

Formato padrão: `(OP, ARG1, ARG2, RES)`

### Aritmética
*   **(ADD, arg1, arg2, res)**: `res = arg1 + arg2`
*   **(SUB, arg1, arg2, res)**: `res = arg1 - arg2`
*   **(MULT, arg1, arg2, res)**: `res = arg1 * arg2`
*   **(DIV, arg1, arg2, res)**: `res = arg1 / arg2`

### Memória e Variáveis
*   **(ALLOC, nome_var, escopo, -)**: Reserva memória para uma variável.
*   **(LOAD, nome_var, offset, res)**: Carrega o valor da variável na memória para o registrador `res`. (Se não for array, offset é `-`).
*   **(STORE, val, nome_var, offset)**: Salva o valor `val` no endereço de memória de `nome_var`.

### Operadores Relacionais (Retornam 1 se Verdade, 0 se Falso no RES)
*   **(EQ, arg1, arg2, res)**: Igual (`==`)
*   **(NEQ, arg1, arg2, res)**: Diferente (`!=`)
*   **(LT, arg1, arg2, res)**: Menor que (`<`)
*   **(LE, arg1, arg2, res)**: Menor ou igual (`<=`)
*   **(GT, arg1, arg2, res)**: Maior que (`>`)
*   **(GE, arg1, arg2, res)**: Maior ou igual (`>=`)

### Controle de Fluxo
*   **(LAB, label_nome, -, -)**: Marca uma posição no código (Destino de um pulo).
*   **(JUMP, label_nome, -, -)**: Pulo incondicional. Vai direto para o label.
*   **(IFF, condicao, label_nome, -)**: *If False*. Se `condicao` for 0 (Falso), pula para o label.

### Funções
*   **(FUN, tipo, nome_funcao, -)**: Marca o início de uma função.
*   **(END, nome_funcao, -, -)**: Marca o fim do corpo da função.
*   **(PARAM, arg, -, -)**: Define um argumento antes de chamar uma função.
*   **(CALL, nome_funcao, num_args, res)**: Chama a função e guarda o retorno em `res`.
*   **(RET, val, -, -)**: Retorna de uma função devolvendo `val` (ou `-` se for void).

### Entrada e Saída
*   **(IN, -, -, res)**: Pede um número ao usuário e guarda em `res`.
*   **(OUT, val, -, -)**: Imprime o valor `val` na tela.
*   **(HALT, -, -, -)**: Encerra o programa.

---

## 2. Tipos de Nós da AST (`node->type`)

Estes são os tipos que você vai testar no seu `switch(node->type)`.

### Nós Folha (Valores brutos)
*   `NODE_NUM`: Um número literal. (Acesse `node->ival`).
*   `NODE_ID`: O nome de uma variável ou função. (Acesse `node->sval`).
*   `NODE_TIPO_INT` / `NODE_TIPO_VOID`: Apenas marcam tipos, geralmente ignorados na geração.

### Nós de Expressões
*   `NODE_SOMA`, `NODE_SUB`, `NODE_MULT`, `NODE_DIV`: Operações matemáticas.
*   `NODE_EXPRESSAO_REC`: Atribuição (`=`). Filho 1 é o destino, Filho 2 é o valor.
*   `NODE_VAR_ARRAY`: Acesso a um vetor (`vetor[i]`). Filho 1 é o ID do vetor, Filho 2 é a expressão do índice.

### Nós Relacionais
*   `NODE_RELACIONAL`: Nó pai de uma comparação. O `child3` aponta para qual é a operação exata abaixo:
    *   `NODE_REL_IGL` (`==`)
    *   `NODE_REL_DIF` (`!=`)
    *   `NODE_REL_MENOR` (`<`)
    *   `NODE_REL_LEQUAL` (`<=`)
    *   `NODE_REL_HIGHER` (`>`)
    *   `NODE_REL_HEQUAL` (`>=`)

### Nós de Declaração (Geralmente no topo do arquivo/bloco)
*   `NODE_PROGRAMA`: A raiz de tudo.
*   `NODE_VAR_DECLARACAO`: Declaração de variável simples.
*   `NODE_VAR_DECLARACAO_ARRAY`: Declaração de vetor.
*   `NODE_FUN_DECLARACAO`: Declaração de função.
*   `NODE_PARAM` / `NODE_PARAM_ARRAY`: Parâmetros definidos na assinatura da função.

### Nós de Controle de Fluxo (Comandos)
*   `NODE_COMPOSTO_DECL`: Um bloco delimitado por `{ }`. Filho 1 são as declarações, Filho 2 são os comandos.
*   `NODE_SELECAO_DECL`: O `IF`. Filho 1 é a condição. Filho 2 é o bloco "Then". Filho 3 (se existir) é o bloco "Else".
*   `NODE_ITERACAO_DECL`: O `WHILE`. Filho 1 é a condição. Filho 2 é o corpo do laço.
*   `NODE_RETORNO_DECL`: O `RETURN`. Filho 1 (se existir) é o que será retornado.
*   `NODE_ATIVACAO`: Chamada de função. Filho 1 é o nome da função. Filho 2 são os argumentos (lista de `args`).
