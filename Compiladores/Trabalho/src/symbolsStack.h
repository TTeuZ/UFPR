#ifndef __PARAMS_STACK_H__
#define __PARAMS_STACK_H__

#include "symbolsTable.h"

#define MAX_PARAM_STACK_SIZE 1024

typedef struct symbolsStack {
  symbolDescriber_t *contents[MAX_PARAM_STACK_SIZE];
  int sp;
} symbolsStack_t;

void initSymbolsStack(symbolsStack_t *stack);
void symbolsStackPush(symbolsStack_t *stack, symbolDescriber_t *value);
symbolDescriber_t *symbolsStackPop(symbolsStack_t *stack);

#endif