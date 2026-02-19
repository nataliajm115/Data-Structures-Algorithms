/* by Gerard Renardel and Malvin Gattinger */

#ifndef LIBSTACK_H
#define LIBSTACK_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StackS* Stack;

Stack newStack(void);

void push(int value, Stack st);
int pop(Stack st);

int isEmptyStack(Stack st);
void freeStack(Stack st);

#endif
