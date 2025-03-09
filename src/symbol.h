#ifndef SYMBOL_H
#define SYMBOL_H


#include <stdlib.h>  // Add this for size_t
#include <string.h>  // Add this for strdup


#define MAX_SYMBOLS 100

typedef enum { INT_TYPE, FLOAT_TYPE } DataType;

typedef struct {
    char *name;
    DataType type;
    int stackOffset;
} SymbolEntry;

typedef struct {
    SymbolEntry entries[MAX_SYMBOLS];
    int count;
    int stackPointer;
} SymbolTable;

void initSymbolTable(SymbolTable *table);
void addSymbol(SymbolTable *table, const char *name, DataType type);
SymbolEntry* findSymbol(SymbolTable *table, const char *name);

#endif
