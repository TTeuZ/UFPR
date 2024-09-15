#include "intStack.h"

void initIntStack(intStack_t *stack) { stack->sp = -1; }

void intStackPush(intStack_t *stack, int value) {
  if (stack->sp < MAX_INT_STACK_SIZE - 1) stack->contents[++stack->sp] = value;
}

int intStackPop(intStack_t *stack) {
  if (stack->sp >= 0) return stack->contents[stack->sp--];
  return -1;
}