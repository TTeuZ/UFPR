#include "symbolsTable.h"

void initSymbolsTable() { symbolsTable.sp = -1; }

void cleanSymbolsTable() { removeSymbols(symbolsTable.sp + 1); }

void insertSimpleVar(char *identifier, int lexicalLevel, int displacement) {
  symbolDescriber_t *symbol = malloc(sizeof(symbolDescriber_t));
  simpleVarAttributes_t *attributes = malloc(sizeof(simpleVarAttributes_t));

  if (symbol == NULL || attributes == NULL) {
    fprintf(stderr, "Erro allocating simple var memory\n");
    exit(1);
  }

  strncpy(symbol->identifier, identifier, TOKEN_SIZE);
  symbol->lexicalLevel = lexicalLevel;
  symbol->category = simple_variable;

  attributes->displacement = displacement;
  attributes->type = t_undefined;
  symbol->attributes = (void *)attributes;

  symbolsTable.symbols[++symbolsTable.sp] = symbol;
}

void removeSimpleVar(symbolDescriber_t *symbol) {
  free(symbol->attributes);
  free(symbol);
}

int searchSymbol(char *identifier) {
  int count = symbolsTable.sp;

  while (count >= 0) {
    if (strcmp(symbolsTable.symbols[count]->identifier, identifier) == 0) return count;
    --count;
  }
  return count;
}

void removeSymbols(size_t n) {
  symbolDescriber_t *symbol;

  for (size_t i = 0; i < n; ++i) {
    symbol = symbolsTable.symbols[symbolsTable.sp];

    if (symbol->category == simple_variable) removeSimpleVar(symbol);
    --symbolsTable.sp;
  }
}