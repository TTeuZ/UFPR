#ifndef __SUBROUTINES_H__
#define __SUBROUTINES_H__

#include "symbolsTable.h"

typedef enum operations { o_attribution, o_procedure, o_function, o_read, o_factor } operations;

symbolDescriber_t *checkSymbol(char *identifier, operations operation);

char *getLoadCommand(passTypes passType, int actualParam, paramItem_t *actualParamsList);

#endif