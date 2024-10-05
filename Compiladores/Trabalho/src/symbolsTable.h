#ifndef __SYMBOLS_TABLE_H__
#define __SYMBOLS_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

#define MAX_SYMBOLS_QTY 1024
#define MAX_PARAMS_QTY 10
#define LABEL_SIZE 4

typedef enum categories { c_simple_var, c_procedure, c_formal_param } categories;
typedef enum types { t_integer, t_boolean, t_undefined } types;
typedef enum passTypes { p_value, p_reference } passTypes;

typedef struct formalParamAttributes {
  types type;
  int displacement;
  passTypes passType;
} formalParamAttributes_t;

typedef struct paramItem {
  types type;
  passTypes passType;
} paramItem_t;

typedef struct procedureAttributes {
  int label;
  int paramsQty;
  paramItem_t params[MAX_PARAMS_QTY];
} procedureAttributes_t;

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
void setSimpleVariableType(types type);

// Procedure
void insertProcedure(char *identifier, int lexicalLevel, int label);
void updateProcedure(symbolDescriber_t *symbol, int paramsQty);
void removeProcedures();

// Formal params
void insertFormalParam(char *identifier, int lexicalLevel, passTypes passType);
void setFormalParamType(types type);
void removeFormalParams();

// Routine functions
int searchSymbol(char *identifier);
void removeSymbols(size_t n);
void removeSymbol(symbolDescriber_t *symbol);

// Debug functions
void printSymbolsTable();

#endif