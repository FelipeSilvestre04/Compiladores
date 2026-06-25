# Compiladores - Felipe Silvestre & Tasso

Projeto integrado de compilador C- e processador custom em Verilog para FPGA.

## Estrutura Ativa

- `src/compiler/`: front-end C-/Flex/Bison, analise semantica e gerador de quadruplas/assembly/binario.
- `src/processor/cpu/`: RTL do processador, projeto Quartus e `programa.txt` carregado pela ROM.
- `tools/`: simulador e utilitarios de apoio.
- `tests/`: programas C- usados em testes.
- `entregavel_final/`: fontes e saidas finais geradas para `fact`, `gcd` e `sort`.
- `old/`: arquivos arquivados, backups, artefatos gerados e entregas antigas.

## Compilador

No WSL/Linux:

```bash
cd src/compiler
flex lexer.l
bison -d parser.y
gcc lex.yy.c parser.tab.c -o compilador
./compilador ../../tests/gcd.txt
```

O compilador gera no diretorio atual:

- `saida.quad`
- `saida.asm`
- `programa.txt`

## Simulador

O simulador RTL-style fica em:

```bash
tools/interactive_sim.py
```

Exemplo para testar o `sort` carregado na ROM:

```bash
python tools/interactive_sim.py src/processor/cpu/programa.txt --inputs 9,2,7,1,8,3,5,0,4,6 --expect 0,1,2,3,4,5,6,7,8,9 --quiet
```

Para ver sinais do datapath:

```bash
python tools/interactive_sim.py entregavel_final/gcd_programa.txt --inputs 48,18 --expect 6 --trace --trace-limit 30
```

## FPGA / Quartus

Abra o projeto:

```text
src/processor/cpu/cpu.qpf
```

O top-level e `cpu`. A ROM le `programa.txt` no diretorio do projeto Quartus.

Antes de programar a FPGA, recompile no Quartus para regenerar `db/`, `incremental_db/` e `output_files/`.

## Enderecamento

- A ROM e enderecada por instrucao: `PC = 0` le a linha 0 de `programa.txt`, `PC = 1` le a linha 1, e assim por diante.
- A RAM e enderecada por palavra de 32 bits: endereco `0` acessa `RAM[0]`, endereco `1` acessa `RAM[1]`, endereco `2` acessa `RAM[2]`.

O compilador gera enderecos de variaveis e arrays nesse mesmo modelo por palavra.
