// src/symbol.c
#include "symbol.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void initSymbolTable(SymbolTable *table) {
    table->count = 0;
    table->stackPointer = 0;
}

void addSymbol(SymbolTable *table, const char *name, DataType type) {
//    if (table->count >= MAX_SYMBOLS) return;
    if (table->count >= MAX_SYMBOLS) {
        fprintf(stderr, "Symbol table overflow\n");
        exit(1);
    }
    table->entries[table->count].name = strdup(name);
    table->entries[table->count].type = type;
    table->entries[table->count].stackOffset = table->stackPointer;
    table->stackPointer += 4;  // Assume 4-byte alignment
    table->count++;
}

SymbolEntry* findSymbol(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->entries[i].name, name) == 0) {
            return &table->entries[i];
        }
    }
    return NULL;
}
