# Compilador C-

## Conteudo

- `bin/compilador`: executavel Linux/WSL atual.
- `src/`: codigo fonte principal do compilador.
  - `lexer.l`: analisador lexico Flex.
  - `parser.y`: parser Bison, AST, analise semantica, tabela de simbolos e `main`.
  - `ast.h`: definicoes da AST.
  - `gerador_quaduplas.c`: geracao de quadruplas, assembly e binario.
- `generated/`: fontes gerados por Flex/Bison incluidos para rastreabilidade.
- `Makefile`: recompila o compilador a partir de `src/`.

O arquivo de entrada do build e `parser.y`: ele contem o `int main(int argc, char *argv[])`. O arquivo `gerador_quaduplas.c` e incluido por `parser.y`, entao nao e compilado como um executavel separado.

## Como executar

No WSL/Linux, a partir de `entregavel_final`:

```bash
make sort
make gcd
```

O compilador imprime no terminal:

- arvore sintatica abstrata;
- tabela de simbolos;
- mensagens de analise sintatica e semantica.

E gera no diretorio atual:

- `saida.quad`;
- `saida.asm`;
- `programa.txt`.

## Como recompilar

No WSL/Linux:

```bash
cd entregavel_final/compilador_final
make
```
