#include "symbolsTable.h"

#include "compiler.h"

symbolsTable_t symbolsTable;
int lexicalLevel;
int displacement;

// ------------------------------------------------ Internal Functions ------------------------------------------------

void verifyBeforeInsert(char *identifier, categories category) {
  int temp = searchSymbol(identifier);

  if (temp != -1) {
    symbolDescriber_t *symbol = symbolsTable.symbols[temp];
    if (symbolsTable.symbols[temp]->category == category && symbolsTable.symbols[temp]->lexicalLevel == lexicalLevel) {
      printError("Redeclaracao de identificador!");
      exit(1);
    }
  }
}

// ------------------------------------------------ Internal Functions ------------------------------------------------

void initSymbolsTable() { symbolsTable.sp = -1; }

void cleanSymbolsTable() { removeSymbols(symbolsTable.sp + 1); }

void insertSimpleVar(char *identifier, int lexicalLevel, int displacement) {
  verifyBeforeInsert(identifier, simple_var);

  symbolDescriber_t *symbol = malloc(sizeof(symbolDescriber_t));
  simpleVarAttributes_t *attributes = malloc(sizeof(simpleVarAttributes_t));
  if (symbol == NULL || attributes == NULL) {
    fprintf(stderr, "Erro allocating simple var memory\n");
    exit(1);
  }

  strncpy(symbol->identifier, identifier, TOKEN_SIZE);
  symbol->lexicalLevel = lexicalLevel;
  symbol->category = simple_var;

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

    if (symbol->category == simple_var) removeSimpleVar(symbol);
    --symbolsTable.sp;
  }
}

void setSimpleVariableType(types type) {
  simpleVarAttributes_t *attributes;
  symbolDescriber_t *symbol;

  for (int i = symbolsTable.sp; i >= 0; --i) {
    symbol = symbolsTable.symbols[i];

    if (symbol->category == simple_var) {
      attributes = (simpleVarAttributes_t *)symbolsTable.symbols[i]->attributes;
      if (attributes->type == t_undefined) attributes->type = type;
    }
  }
}

void printSymbolsTable() {
  simpleVarAttributes_t *attributes;
  symbolDescriber_t *symbol;

  for (size_t i = 0; i <= symbolsTable.sp; ++i) {
    symbol = symbolsTable.symbols[i];
    printf("Symbol: %s - Category: %d - LexicalLevel: %d ", symbol->identifier, symbol->category, symbol->lexicalLevel);

    if (symbol->category == simple_var) {
      attributes = (simpleVarAttributes_t *)symbol->attributes;
      printf("- Displacement: %d - type: %d\n", attributes->displacement, attributes->type);
    }
  }
}