#include "subroutines.h"

symbolDescriber_t *checkSymbol(char *identifier, operations operation) {
  int symbolPos = searchSymbol(identifier);
  if (symbolPos == -1) printError("simbolo nao declarado ou fora do escopo!");

  symbolDescriber_t *symbol = symbolsTable.symbols[symbolPos];
  switch (operation) {
    case o_attribution:
      if (symbol->category == c_procedure) printError("Mal uso de identificador!");
      break;
    case o_procedure:
      if (symbol->category != c_procedure) printError("Mal uso de identificador!");
      break;
    case o_function:
      if (symbol->category != c_function) printError("Mal uso de identificador!");
      break;
    case o_read:
      if (symbol->category == c_procedure) printError("Mal uso de identificador!");
      break;
    case o_factor:
      if (symbol->category == c_procedure) printError("Mal uso de identificador!");
      break;
    default:
      break;
  }

  return symbol;
}

char *getLoadCommand(passTypes passType, int actualParam, symbolDescriber_t *symbol) {
  paramItem_t *params = NULL;

  if (symbol != NULL && symbol->category == c_procedure) {
    procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;
    params = attributes->params;
  } else if (symbol != NULL && symbol->category == c_function) {
    functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;
    params = attributes->params;
  }

  if (actualParam == -1 && passType == p_value)
    return "CRVL";
  else if (actualParam == -1 && passType == p_reference)
    return "CRVI";
  else if (passType == p_value && params[actualParam].passType == p_value)
    return "CRVL";
  else if (passType == p_value && params[actualParam].passType == p_reference)
    return "CREN";
  else if (passType == p_reference && params[actualParam].passType == p_value)
    return "CRVI";
  else if (passType == p_reference && params[actualParam].passType == p_reference)
    return "CRVL";

  return "NADA";
}

void checkParamType(int type, int param, symbolDescriber_t *symbol) {
  if (symbol->category == c_procedure) {
    procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;

    if (param >= attributes->paramsQty) printError("Quantidade invalida de parametros!");
    if (attributes->params[param].type != type) printError("Parametro de tipo incompativel!");
  } else if (symbol->category == c_function) {
    functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;

    if (param >= attributes->paramsQty) printError("Quantidade invalida de parametros!");
    if (attributes->params[param].type != type) printError("Parametro de tipo incompativel!");
  }
}