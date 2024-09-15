#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 1024

typedef struct stack {
  void *contents[MAX_STACK_SIZE];
  int sp;
} stack_t;

void initStack(stack_t *stack);
void stackPush(stack_t *stack, void *value);
void *stackPop(stack_t *stack);

#endif