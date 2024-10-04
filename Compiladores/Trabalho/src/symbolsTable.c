#include "symbolsTable.h"

#include "compiler.h"

symbolsTable_t symbolsTable;
int lexicalLevel;
int displacement;

// ------------------------------------------------ Internal Functions ------------------------------------------------

void verifyBeforeInsert(char *identifier) {
  int temp = searchSymbol(identifier);

  if (temp != -1) {
    symbolDescriber_t *symbol = symbolsTable.symbols[temp];
    if (symbolsTable.symbols[temp]->lexicalLevel == lexicalLevel) {
      printError("Redeclaracao de identificador!");
      exit(1);
    }
  }
}

// ------------------------------------------------ Internal Functions ------------------------------------------------

void initSymbolsTable() { symbolsTable.sp = -1; }

void cleanSymbolsTable() { removeSymbols(symbolsTable.sp + 1); }

// ------------------------------------------------  Simple Variables  ------------------------------------------------

void insertSimpleVar(char *identifier, int lexicalLevel, int displacement) {
  verifyBeforeInsert(identifier);

  symbolDescriber_t *symbol = malloc(sizeof(symbolDescriber_t));
  simpleVarAttributes_t *attributes = malloc(sizeof(simpleVarAttributes_t));
  if (symbol == NULL || attributes == NULL) {
    fprintf(stderr, "Error allocating simple var memory\n");
    exit(1);
  }

  strncpy(symbol->identifier, identifier, TOKEN_SIZE);
  symbol->lexicalLevel = lexicalLevel;
  symbol->category = c_simple_var;

  attributes->displacement = displacement;
  attributes->type = t_undefined;
  symbol->attributes = (void *)attributes;

  symbolsTable.symbols[++symbolsTable.sp] = symbol;
}

void removeSimpleVar(symbolDescriber_t *symbol) {
  free(symbol->attributes);
  free(symbol);
}

void setSimpleVariableType(types type) {
  simpleVarAttributes_t *attributes;
  symbolDescriber_t *symbol;

  for (int i = symbolsTable.sp; i >= 0; --i) {
    symbol = symbolsTable.symbols[i];

    if (symbol->category == c_simple_var) {
      attributes = (simpleVarAttributes_t *)symbolsTable.symbols[i]->attributes;
      if (attributes->type == t_undefined) attributes->type = type;
    }
  }
}

// ------------------------------------------------  Simple Variables  ------------------------------------------------
// ------------------------------------------------     Procedures     ------------------------------------------------

void insertProcedure(char *identifier, int lexicalLevel, int label) {
  verifyBeforeInsert(identifier);

  symbolDescriber_t *symbol = malloc(sizeof(symbolDescriber_t));
  procedureAttributes_t *attributes = malloc(sizeof(procedureAttributes_t));
  if (symbol == NULL || attributes == NULL) {
    fprintf(stderr, "Error allocating procedure memory\n");
    exit(1);
  }

  strncpy(symbol->identifier, identifier, TOKEN_SIZE);
  symbol->lexicalLevel = lexicalLevel;
  symbol->category = c_procedure;

  attributes->label = label;
  attributes->parametersQty = 0;
  symbol->attributes = (void *)attributes;

  symbolsTable.symbols[++symbolsTable.sp] = symbol;
}

void removeProcedure(symbolDescriber_t *symbol) {
  free(symbol->attributes);
  free(symbol);
}

void removeProcedures() {
  symbolDescriber_t *symbol;
  for (int i = symbolsTable.sp; i >= 0; --i) {
    symbol = symbolsTable.symbols[i];

    if (symbol->category == c_simple_var) break;

    if (symbol->category == c_procedure && symbol->lexicalLevel == lexicalLevel + 1) {
      removeProcedure(symbol);
      --symbolsTable.sp;
    }
  }
}

// ------------------------------------------------     Procedures     ------------------------------------------------

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

    if (symbol->category == c_simple_var)
      removeSimpleVar(symbol);
    else if (symbol->category == c_procedure)
      removeProcedure(symbol);

    --symbolsTable.sp;
  }
}

void printSymbolsTable() {
  symbolDescriber_t *symbol;

  for (int i = 0; i <= symbolsTable.sp; ++i) {
    symbol = symbolsTable.symbols[i];
    printf("Symbol: %s - Category: %d - LexicalLevel: %d ", symbol->identifier, symbol->category, symbol->lexicalLevel);

    if (symbol->category == c_simple_var) {
      simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;
      printf("- Displacement: %d - type: %d\n", attributes->displacement, attributes->type);
    } else if (symbol->category == c_procedure) {
      procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;
      printf("- Label: R%02d - paramQty: %d\n", attributes->label, attributes->parametersQty);
    }
  }
}