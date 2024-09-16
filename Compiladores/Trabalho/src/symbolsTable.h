#ifndef __SYMBOLS_TABLE_H__
#define __SYMBOLS_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

#define MAX_SYMBOLS_QTY 1024

typedef enum categories { simple_var } categories;
typedef enum types { t_integer, t_boolean, t_undefined } types;

typedef struct simpleVarAttributes {
  int displacement;
  types type;
} simpleVarAttributes_t;

typedef struct symbolDescriber {
  char identifier[TOKEN_SIZE];
  categories category;
  int lexicalLevel;
  void *attributes;
} symbolDescriber_t;

typedef struct symbolsTable {
  symbolDescriber_t *symbols[MAX_SYMBOLS_QTY];
  int sp;
} symbolsTable_t;

// Setting the table globally
extern symbolsTable_t symbolsTable;
extern int lexicalLevel;
extern int displacement;

void initSymbolsTable();
void cleanSymbolsTable();

// Simple variables
void insertSimpleVar(char *identifier, int lexicalLevel, int displacement);
void removeSimpleVar(symbolDescriber_t *symbol);

// Routine functions
int searchSymbol(char *identifier);
void removeSymbols(size_t n);
void setSimpleVariableType(types type);

// Debug functions
void printSymbolsTable();

#endif