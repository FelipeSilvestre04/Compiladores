# RELATÓRIO TÉCNICO: PIPELINE DO COMPILADOR C- PARA RISC-V CUSTOMIZADO

Este relatório descreve a jornada teórica e prática da transformação de um código em linguagem de alto nível (**C-**) até os bits executáveis pelo seu **Processador Verilog**.

---

## 1. Do Texto à Estrutura (Análise Léxica e Sintática)
O processo começa com o **Flex** e o **Bison**. O objetivo aqui é entender a "gramática" do código.
- **Resultado**: Uma **Árvore Sintática Abstrata (AST)**. 
- **Por que isso é importante?** A árvore organiza o código em uma hierarquia (ex: uma soma tem dois filhos: os números operados). É muito mais fácil percorrer uma árvore do que tentar entender um arquivo de texto puro.

## 2. O Código Intermediário (Quádruplas)
A AST é rica em detalhes, mas os processadores são lineares. Criamos o `codegen.c` para transformar a árvore em uma lista de instruções simples chamadas **Quádruplas** `(OP, Arg1, Arg2, Res)`.
- **Inovação**: Introduzimos **Temporários (`$t0`, `$t1`...)** para guardar resultados parciais e **Rótulos (`L0`, `L1`...)** para marcar destinos de desvios.
- **Vantagem**: As quádruplas são independentes de hardware. Se você decidisse mudar para um processador ARM amanhã, as quádruplas continuariam as mesmas; apenas o tradutor de assembly mudaria.

## 3. A Tradução para Assembly (`asm_gen.py`)
Aqui a teoria encontra a realidade do seu processador. O script lê as quádruplas e as mapeia para as mnemônicas do **RISC-V**.
- **Mapeamento de Registradores**: Fizemos uma distinção clara entre registradores de argumento (`x10-x11`) e temporários (`x20-x31`) para evitar que cálculos complexos sobrescrevessem os dados das funções.
- **Abstração de Memória**: Criamos uma **Tabela de Símbolos** que atribui a cada variável um endereço real (offset) na RAM, usando o `Global Pointer (x3)` como base.

## 4. O Assembler Binário e o Formato da ISA (`bin_assembler.py`)
O passo final é transformar texto (`add`, `beq`) em 0s e 1s. Seguimos rigorosamente a sua especificação de 32 bits dividida em:
- **Opcode (3 bits)**: Identifica o tipo (R, I, J, B, N, IO).
- **Funct (4 bits)**: Identifica a operação específica dentro do tipo (ex: ADD vs SUB).
- **Campos de Registradores (6 bits)**: Permite até 64 registradores.
- **Imediatos**: Deslocamentos para memória e saltos.

O Assembler usa **duas passagens**: a primeira descobre onde cada Rótulo (`L1:`) mora na memória, e a segunda substitui o nome do rótulo pelo número da linha correspondente, garantindo que os saltos (`jump`, `beq`) caiam no lugar certo.

## 5. Integração com o Hardware (Verilog)
A análise dos seus módulos Verilog confirmou que:
- O **Decoder** está perfeitamente alinhado com o Assembler.
- A **Unidade de Controle** sabe como acionar os sinais de leitura/escrita para todas as instruções.
- O arquivo `programa.txt` gerado é o "alimento" que a sua `rom.v` consome via `$readmemb`.

---

### Resumo do Fluxo Total:
1.  **Entrada**: `gcd.txt` (Código C-)
2.  **Compilador**: Gera `saida.quad` (Lógica Pura)
3.  **Tradutor de ASM**: Gera `saida.asm` (Instruções RISC-V + Registradores)
4.  **Assembler**: Gera `programa.txt` (Bits da Memória)
5.  **Hardware**: Executa os bits e produz o resultado do MDC.

---
**Documento gerado como guia de estudo e referência técnica.**
