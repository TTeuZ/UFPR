#include "symbolsTable.h"

#include "compiler.h"

symbolsTable_t symbolsTable;

// ------------------------------------------------ Internal Functions ------------------------------------------------

void verifyBeforeInsert(char *identifier, int lexicalLevel) {
  int temp = searchSymbol(identifier);

  if (temp != -1) {
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
  verifyBeforeInsert(identifier, lexicalLevel);

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

void setSimpleVariableType(types type) {
  simpleVarAttributes_t *attributes;

  for (int i = symbolsTable.sp; i >= 0; --i) {
    if (symbolsTable.symbols[i]->category == c_simple_var) {
      attributes = (simpleVarAttributes_t *)symbolsTable.symbols[i]->attributes;

      if (attributes->type == t_undefined) attributes->type = type;
    }
  }
}

// ------------------------------------------------  Simple Variables  ------------------------------------------------
// ------------------------------------------------     Procedures     ------------------------------------------------

void insertProcedure(char *identifier, int lexicalLevel, int label) {
  verifyBeforeInsert(identifier, lexicalLevel);

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
  attributes->paramsQty = 0;
  memset(attributes->params, 0, sizeof(paramItem_t) * MAX_PARAMS_QTY);
  symbol->attributes = (void *)attributes;

  symbolsTable.symbols[++symbolsTable.sp] = symbol;
}

void updateProcedure(symbolDescriber_t *symbol, int paramsQty) {
  procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;
  formalParamAttributes_t *param_attributes;

  attributes->paramsQty = paramsQty;

  int displacement = -4;
  int count = symbolsTable.sp;
  for (int i = (paramsQty - 1); i >= 0; --i) {
    param_attributes = (formalParamAttributes_t *)symbolsTable.symbols[count--]->attributes;
    param_attributes->displacement = displacement--;

    attributes->params[i].passType = param_attributes->passType;
    attributes->params[i].type = param_attributes->type;
  }
}

// ------------------------------------------------     Procedures     ------------------------------------------------
// ------------------------------------------------     Functions      ------------------------------------------------

void insertFunction(char *identifier, int lexicalLevel, int label) {
  verifyBeforeInsert(identifier, lexicalLevel);

  symbolDescriber_t *symbol = malloc(sizeof(symbolDescriber_t));
  functionAttributes_t *attributes = malloc(sizeof(functionAttributes_t));
  if (symbol == NULL || attributes == NULL) {
    fprintf(stderr, "Error allocating function memory\n");
    exit(1);
  }

  strncpy(symbol->identifier, identifier, TOKEN_SIZE);
  symbol->lexicalLevel = lexicalLevel;
  symbol->category = c_function;

  attributes->label = label;
  attributes->paramsQty = 0;
  attributes->displacement = 0;
  attributes->type = t_undefined;
  memset(attributes->params, 0, sizeof(paramItem_t) * MAX_PARAMS_QTY);
  symbol->attributes = (void *)attributes;

  symbolsTable.symbols[++symbolsTable.sp] = symbol;
}

void updateFunction(symbolDescriber_t *symbol, int paramsQty, types type) {
  functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;
  formalParamAttributes_t *param_attributes;

  attributes->paramsQty = paramsQty;
  attributes->type = type;

  int displacement = -4;
  int count = symbolsTable.sp;
  for (int i = (paramsQty - 1); i >= 0; --i) {
    param_attributes = (formalParamAttributes_t *)symbolsTable.symbols[count--]->attributes;
    param_attributes->displacement = displacement--;

    attributes->params[i].passType = param_attributes->passType;
    attributes->params[i].type = param_attributes->type;
  }
  attributes->displacement = displacement;
}

// ------------------------------------------------     Functions      ------------------------------------------------
// ------------------------------------------------   Formal Params    ------------------------------------------------

void insertFormalParam(char *identifier, int lexicalLevel, passTypes passType) {
  // verifyBeforeInsert(identifier, lexicalLevel);

  symbolDescriber_t *symbol = malloc(sizeof(symbolDescriber_t));
  formalParamAttributes_t *attributes = malloc(sizeof(formalParamAttributes_t));
  if (symbol == NULL || attributes == NULL) {
    fprintf(stderr, "Error allocating formal param memory\n");
    exit(1);
  }

  strncpy(symbol->identifier, identifier, TOKEN_SIZE);
  symbol->lexicalLevel = lexicalLevel;
  symbol->category = c_formal_param;

  attributes->type = t_undefined;
  attributes->displacement = 0;
  attributes->passType = passType;
  symbol->attributes = (void *)attributes;

  symbolsTable.symbols[++symbolsTable.sp] = symbol;
}

void setFormalParamType(types type) {
  formalParamAttributes_t *attributes;

  for (int i = symbolsTable.sp; i >= 0; --i) {
    if (symbolsTable.symbols[i]->category == c_formal_param) {
      attributes = (formalParamAttributes_t *)symbolsTable.symbols[i]->attributes;

      if (attributes->type == t_undefined) attributes->type = type;
    }
  }
}

void removeFormalParams() {
  symbolDescriber_t *symbol;
  for (int i = symbolsTable.sp; i >= 0; --i) {
    symbol = symbolsTable.symbols[i];
    if (symbol->category != c_formal_param) break;

    removeSymbol(symbol);
    --symbolsTable.sp;
  }
}

// ------------------------------------------------   Formal Params    ------------------------------------------------

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
    symbol = symbolsTable.symbols[symbolsTable.sp--];
    removeSymbol(symbol);
  }
}

void removeSymbol(symbolDescriber_t *symbol) {
  free(symbol->attributes);
  free(symbol);
}

void removeSubroutines(int lexicalLevel) {
  symbolDescriber_t *symbol;
  for (int i = symbolsTable.sp; i >= 0; --i) {
    symbol = symbolsTable.symbols[i];
    if (symbol->category != c_procedure && symbol->category != c_function) break;

    if (symbol->lexicalLevel == lexicalLevel + 1) {
      removeSymbol(symbol);
      --symbolsTable.sp;
    }
  }
}

void printSymbolsTable() {
  symbolDescriber_t *symbol;

  for (int i = 0; i <= symbolsTable.sp; ++i) {
    symbol = symbolsTable.symbols[i];
    printf("Symbol: %s - Category: %d - LexicalLevel: %d ", symbol->identifier, symbol->category, symbol->lexicalLevel);

    if (symbol->category == c_simple_var) {
      simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;
      printf("- Displacement: %d - Type: %d\n", attributes->displacement, attributes->type);
    } else if (symbol->category == c_procedure) {
      procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;
      printf("- Label: R%02d - ParamQty: %d\n", attributes->label, attributes->paramsQty);
    } else if (symbol->category == c_formal_param) {
      formalParamAttributes_t *attributes = (formalParamAttributes_t *)symbol->attributes;
      printf("- Type: %d - Displacement: %d - PassType: %d\n", attributes->type, attributes->displacement, attributes->passType);
    } else if (symbol->category == c_function) {
      functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;
      printf("- Label: R%02d - ParamQty: %d - Type: %d - Displacement: %d\n", attributes->label, attributes->paramsQty, attributes->type,
             attributes->displacement);
    }
  }
}