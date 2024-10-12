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

char *getLoadCommand(passTypes passType, int actualParam, paramItem_t *actualParamsList) {
  if (actualParam == -1 && passType == p_value)
    return "CRVL";
  else if (actualParam == -1 && passType == p_reference)
    return "CRVI";
  else if (passType == p_value && actualParamsList[actualParam].passType == p_value)
    return "CRVL";
  else if (passType == p_value && actualParamsList[actualParam].passType == p_reference)
    return "CREN";
  else if (passType == p_reference && actualParamsList[actualParam].passType == p_value)
    return "CRVI";
  else if (passType == p_reference && actualParamsList[actualParam].passType == p_reference)
    return "CRVL";

  return "NADA";
}