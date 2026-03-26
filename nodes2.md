# MAPEAMENTO AST -> QUÁDRUPLAS (VERSÃO REFINADA)

Este documento detalha quais quádruplas do `quaduplas.txt` são ativadas por cada construção da linguagem C- atual.

## 1. Mapeamento Direto

| Construção C- | Nó da AST | Quádruplas Utilizadas |
| :--- | :--- | :--- |
| **Aritmética** | `NODE_SOMA/SUB/MULT/DIV` | `ADD`, `SUB`, `MULT`, `DIV` |
| **Constantes** | `NODE_NUM` | `ADDI` (usando $zero) |
| **Variáveis** | `NODE_ID` / `NODE_EXPRESSAO_REC` | `LOAD`, `STORE` |
| **Vetores** | `NODE_VAR_ARRAY` | `ADDI` (offset) + `LOAD`/`STORE` |
| **Relacional** | `NODE_RELACIONAL` | `EQ`, `NEQ`, `LT`, `LE`, `GT`, `GE` |
| **Controle** | `NODE_SELECAO/ITERACAO` | `IFF`, `GOTO`, `LAB` |
| **Funções** | `NODE_FUN/ATIVACAO/RET/PARAM`| `FUN`, `END`, `ALLOC`, `PARAM`, `CALL`, `RET` |
| **Sistema** | `input()` / `output()` | `IN`, `OUT`, `HALT` |

---

## 2. Por que algumas quádruplas não estão no mapeamento?

Você tem total razão: nem todas as quádruplas do `quaduplas.txt` serão usadas pelo compilador **neste momento**. Isso acontece por dois motivos:

### A. Limitações da Linguagem C-
A gramática atual (em `parser.y`) não possui operadores para as seguintes operações, embora elas existam no "set" de quádruplas:
- **Lógicas Bitwise**: `AND`, `OR`, `XOR`, `NOT`, `ANDI`, `ORI`, `XORI`.
  - *Motivo*: O C- clássico usa apenas os relacionais para controle de fluxo. Se no futuro quisermos adicionar `&`, `|` ou `~`, as quádruplas já estão reservadas.
- **Subtração Imediata**: `SUBI`.
  - *Motivo*: Podemos fazer `ADDI t1, -5, t2` para subtrair 5. O `SUBI` é uma conveniência que o hardware pode ter, mas o compilador pode simplificar usando apenas `ADDI`.

### B. Manutenibilidade do Hardware
O arquivo `quaduplas.txt` foi desenhado para ser um **RISC-V Customizado completo**. Mesmo que o compilador use apenas um subconjunto, o processador em Verilog pode implementar todas para que o sistema seja robusto e suporte expansões futuras sem mudar o formato da instrução.

---

## 3. Detalhes dos Filhos da AST (Para Implementação)

| Nó | Filho 1 | Filho 2 | Filho 3 |
| :--- | :--- | :--- | :--- |
| **IF-ELSE** | Expressão (Condição) | Statement (Corpo IF) | Statement (Corpo ELSE) |
| **WHILE** | Expressão (Condição) | Statement (Corpo) | - |
| **CALL** | ID da Função | Lista de Argumentos | - |
| **Vetor** | ID do Vetor | Expressão (Índice) | - |
| **Atribuição**| Variável Destino | Expressão de Origem | - |
