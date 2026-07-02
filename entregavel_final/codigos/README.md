# Codigos finais

Cada subpasta contem os quatro artefatos finais de um programa C-:

- `original.txt`: codigo-fonte original.
- `compilacao.log`: saida completa do compilador, incluindo arvore sintatica e tabela de simbolos.
- `quadruplas.quad`: codigo intermediario em quadruplas.
- `assembly.asm`: assembly gerado para a ISA do processador.
- `programa.txt`: binario de 32 bits usado pela ROM do processador.
- `Makefile`: regenera os artefatos daquele programa usando `../../compilador_final/bin/compilador`.

Programas:

- `fact`: fatorial, cobre chamada recursiva.
- `gcd`: maximo divisor comum, cobre recursao e e um dos exemplos para executar na FPGA.
- `sort`: ordenacao por selecao crescente, cobre repeticao, selecao, arrays e passagem de vetor como parametro; e um dos exemplos para executar na FPGA.
