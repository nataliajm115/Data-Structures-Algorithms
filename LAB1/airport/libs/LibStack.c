/* by Gerard Renardel and Malvin Gattinger */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "LibStack.h"

typedef struct StackS {
  int* array;
  int top;
  int size;
} StackS;

const int INITIAL_STACK_SIZE = 7;

Stack newStack(void) {
  Stack st = malloc(sizeof(StackS));
  assert(st != NULL);
  st->array = malloc(INITIAL_STACK_SIZE * sizeof(int));
  assert(st->array != NULL);
  st->top = 0;
  st->size = INITIAL_STACK_SIZE;
  return st;
}

void doubleStackSize(Stack st) {
  int newSize = 2 * st->size;
  st->array = realloc(st->array, newSize * sizeof(int));
  assert(st->array != NULL);
  st->size = newSize;
}

int isEmptyStack(Stack st) {
  return (st->top == 0);
}

void stackEmptyError(void) {
  printf("stack empty\n");
  abort();
}

void push(int value, Stack st) {
  if (st->top == st->size) {
    doubleStackSize(st);
  }
  st->array[st->top] = value;
  st->top++;
}

int pop(Stack st) {
  if (isEmptyStack(st)) {
    stackEmptyError();
  }
  st->top--;
  return st->array[st->top];
}

void freeStack(Stack st) {
  free(st->array);
  free(st);
}
