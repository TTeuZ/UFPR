#include "stack.h"

void initStack(stack_t *stack) { stack->sp = -1; }

void stackPush(stack_t *stack, void *value) {
  if (stack->sp < MAX_STACK_SIZE - 1) stack->contents[++stack->sp] = value;
}

void *stackPop(stack_t *stack) {
  if (stack->sp >= 0) return stack->contents[stack->sp--];
  return NULL;
}