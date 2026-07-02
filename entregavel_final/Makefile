.PHONY: all compilador fact gcd sort clean

all: compilador fact gcd sort

compilador:
	$(MAKE) -C compilador_final

fact gcd sort: compilador
	$(MAKE) -C codigos/$@

clean:
	$(MAKE) -C compilador_final clean
	$(MAKE) -C codigos/fact clean
	$(MAKE) -C codigos/gcd clean
	$(MAKE) -C codigos/sort clean
