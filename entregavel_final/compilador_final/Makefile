CC := gcc
CFLAGS := -std=gnu11
FLEX := flex
BISON := bison

SRC_DIR := src
GEN_DIR := generated
BIN_DIR := bin
COMPILADOR := $(BIN_DIR)/compilador

.PHONY: all clean

all: $(COMPILADOR)

$(GEN_DIR):
	mkdir -p $(GEN_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(GEN_DIR)/parser.tab.c $(GEN_DIR)/parser.tab.h: $(SRC_DIR)/parser.y $(SRC_DIR)/ast.h $(SRC_DIR)/gerador_quaduplas.c | $(GEN_DIR)
	$(BISON) -d -o $(GEN_DIR)/parser.tab.c $(SRC_DIR)/parser.y

$(GEN_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l $(GEN_DIR)/parser.tab.h | $(GEN_DIR)
	$(FLEX) -o $(GEN_DIR)/lex.yy.c $(SRC_DIR)/lexer.l

$(COMPILADOR): $(GEN_DIR)/lex.yy.c $(GEN_DIR)/parser.tab.c $(SRC_DIR)/ast.h $(SRC_DIR)/gerador_quaduplas.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(GEN_DIR) $(GEN_DIR)/lex.yy.c $(GEN_DIR)/parser.tab.c -o $(COMPILADOR)

clean:
	rm -f $(COMPILADOR) $(GEN_DIR)/lex.yy.c $(GEN_DIR)/parser.tab.c $(GEN_DIR)/parser.tab.h
