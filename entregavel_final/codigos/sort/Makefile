COMPILADOR := ../../compilador_final/bin/compilador

.PHONY: all clean

all: programa.txt

$(COMPILADOR):
	$(MAKE) -C ../../compilador_final

programa.txt: original.txt $(COMPILADOR)
	$(COMPILADOR) original.txt > compilacao.log
	mv -f saida.quad quadruplas.quad
	mv -f saida.asm assembly.asm

clean:
	rm -f compilacao.log quadruplas.quad assembly.asm programa.txt saida.quad saida.asm
