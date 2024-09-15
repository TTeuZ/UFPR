#ifndef __INT_STACK_H__
#define __INT_STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT_STACK_SIZE 1024

typedef struct intStack {
  int contents[MAX_INT_STACK_SIZE];
  int sp;
} intStack_t;

void initIntStack(intStack_t *stack);
void intStackPush(intStack_t *stack, int value);
int intStackPop(intStack_t *stack);

#endif