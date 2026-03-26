# Compiladores - Felipe Silvestre & Tasso

Este repositório contém o desenvolvimento de um compilador e a implementação de um processador em Verilog para execução do código gerado.

## Estrutura do Repositório

- **src/compiler/**: Contém o código fonte do compilador (arquivos `.l` para o Flex e `.y` para o Bison), além da lógica de geração de código.
- **src/processor/**: Espaço destinado aos arquivos RTL (Verilog) do processador.
- **tests/**: Exemplos de código fonte na linguagem do compilador (ex: `gcd.txt`, `sort.txt`) e saídas geradas durante os testes.
- **archive/**: Backups de versões anteriores, arquivos compactados (.zip, .rar) e atividades passadas.

## Como Compilar (Compilador)

Para gerar o executável do compilador (no Linux/WSL):
```bash
flex lexer.l
bison -d parser.y
gcc lex.yy.c parser.tab.c -o compilador
```

Para rodar um teste:
```bash
./compilador < tests/gcd.txt
```
