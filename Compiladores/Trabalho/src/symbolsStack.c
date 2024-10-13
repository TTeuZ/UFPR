#include "symbolsStack.h"

void initSymbolsStack(symbolsStack_t *stack) { stack->sp = -1; }

void symbolsStackPush(symbolsStack_t *stack, symbolDescriber_t *value) {
  if (stack->sp < MAX_PARAM_STACK_SIZE - 1) stack->contents[++stack->sp] = value;
}

symbolDescriber_t *symbolsStackPop(symbolsStack_t *stack) {
  if (stack->sp >= 0) return stack->contents[stack->sp--];
  return NULL;
}