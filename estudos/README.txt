Material de estudo da fase de sintese do compilador.

Documentos de referencia:

- quadruplas_disponiveis.txt: lista das quadruplas usadas pelo gerador, com formato e funcao.
- mapeamento_quadruplas_assembly.txt: explica como cada quadrupla e traduzida para assembly.

Cada subpasta contem:

- original.txt: programa-fonte C- usado como entrada.
- quadruplas.txt: codigo intermediario gerado pelo compilador.
- assembly.txt: codigo assembly simbolico gerado pelo compilador.
- binario.txt: palavras binarias de 32 bits usadas pelo processador.
- compilacao.log: saida textual do compilador, com AST e tabela de simbolos.

Os arquivos quadruplas.txt, assembly.txt e binario.txt foram gerados pelo compilador do projeto.

Exemplos:

01_arrays
Foca em variavel simples, array local, LOAD, STORE e calculo de deslocamento.

02_labels_if_else
Foca em if/else, labels, branch invertido e JUMP para o fim do bloco condicional.

03_funcao_simples
Foca em funcao com parametro simples, PARAM, CALL, ARG, RET, JAL e JR.

04_funcao_array_save_context
Foca em array como parametro, SAVE_CONTEXT, passagem de endereco base, chamada de funcao e if/else.
