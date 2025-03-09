CC = gcc
LEX = flex
YACC = bison
BUILD_DIR = build
SRC_DIR = src
INCLUDES = -g -Wall -I$(SRC_DIR) -I$(BUILD_DIR)
CFLAGS = -g -Wall -I$(SRC_DIR) -I$(BUILD_DIR)


OBJS = \
    $(BUILD_DIR)/lex.yy.o \
    $(BUILD_DIR)/parser.tab.o \
    $(BUILD_DIR)/ast.o \
    $(BUILD_DIR)/symbol.o \
    $(BUILD_DIR)/main.o \
    $(BUILD_DIR)/semantic.o \
    $(BUILD_DIR)/codegen.o

all: $(BUILD_DIR)/compiler

$(BUILD_DIR)/compiler: $(OBJS)
	$(CC) -o $@ $^

$(BUILD_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	$(YACC) -d -o $(BUILD_DIR)/parser.tab.c $(SRC_DIR)/parser.y

$(BUILD_DIR)/lex.yy.o: $(SRC_DIR)/lexer.l $(BUILD_DIR)/parser.tab.h
	$(LEX) -o $(BUILD_DIR)/lex.yy.c $(SRC_DIR)/lexer.l
	$(CC) -c $(INCLUDES) -o $@ $(BUILD_DIR)/lex.yy.c

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.c
	$(CC) -c $(INCLUDES) -o $@ $<  # Critical fix here

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(INCLUDES) -o $@ $<

clean:
	rm -rf $(BUILD_DIR)/*
