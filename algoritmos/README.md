# Algoritmos do PC1

Cada subpasta contem os artefatos de um algoritmo executavel no processador:

- `codigo_c.txt`: programa-fonte na linguagem C-.
- `quadruplas.txt`: codigo intermediario gerado pelo compilador.
- `assembly.txt`: codigo assembly gerado pelo compilador.
- `program.txt`: codigo de maquina de 32 bits carregado na ROM.
- `programa.mif`: inicializacao da ROM utilizada na sintese pelo Quartus.
- `compilacao.log`: saida das analises lexica, sintatica e semantica.
- `testes.txt`: casos executados no simulador e, posteriormente, na FPGA.
- `cpu.sof`: configuracao para a placa fisica DE2-115.
- `cpu_remoto.sof`: configuracao para o laboratorio remoto.

O arquivo `ENTREGA_PC1.txt` reune, em um unico documento, o codigo C- e o
codigo de maquina dos dez algoritmos, conforme solicitado no PC1.

A subpasta `cpu` contem uma copia autocontida do projeto Quartus utilizado
na geracao dos `.sof`. A ROM dessa copia esta inicializada com o algoritmo
`01_fatorial`.

Os arquivos `.sof` incorporam o conteudo de `program.txt` existente no momento
da compilacao do projeto Quartus. Por isso, cada algoritmo precisa de seus
proprios arquivos de configuracao.

## Estado da validacao

- Os 10 programas foram compilados sem erro lexico, sintatico ou semantico.
- Foram aprovados 22 casos no simulador do conjunto de instrucoes.
- Todos os programas possuem menos de 256 instrucoes de 32 bits.
- Os testes na FPGA ainda estao pendentes.
- Os `cpu.sof` locais foram gerados, mas ainda nao foram testados na placa.
- Os `cpu_remoto.sof` foram gerados, mas ainda nao foram testados na placa.

O projeto do processador nao possui o arquivo `cpu.sdc`. Assim, os resultados
de temporizacao emitidos pelo Quartus nao representam restricoes temporais
definidas pelo projeto e a validacao final deve ser feita na FPGA.

## Preparacao para o Quartus

Para compilar manualmente um algoritmo, copie o `program.txt` e o
`programa.mif` da subpasta escolhida para `src/processor/cpu`, mantendo esses
nomes. Em seguida, abra o projeto `cpu.qpf` e execute a compilacao completa.

Os MIFs podem ser recriados sem executar o Quartus:

```powershell
.\algoritmos\gerar_mifs.ps1
```

O arquivo consolidado da entrega pode ser recriado com:

```powershell
.\algoritmos\gerar_entrega.ps1
```

Para gerar automaticamente os `.sof`, use um dos modos:

```powershell
.\algoritmos\gerar_sofs.ps1 -Modo Local
.\algoritmos\gerar_sofs.ps1 -Modo Remoto
.\algoritmos\gerar_sofs.ps1 -Modo Todos
```

## Algoritmos

1. Fatorial recursivo.
2. Maximo divisor comum pelo algoritmo de Euclides.
3. Ordenacao por selecao.
4. Fibonacci iterativo.
5. Potenciacao inteira.
6. Teste de numero primo.
7. Busca linear em vetor.
8. Soma e media inteira de vetor.
9. Produto escalar de dois vetores.
10. Multiplicacao de matrizes 2x2.
