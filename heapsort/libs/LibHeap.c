#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "LibHeap.h"

typedef struct HeapS {
  int* array;
  int front;
  int size;
} HeapS;

Heap makeHeap(void) {
  Heap h = malloc(sizeof(HeapS));
  assert(h != NULL);
  h->array = malloc(1 * sizeof(int));
  assert(h->array != NULL);
  h->front = 1;
  h->size = 1;
  return h;
}

int isEmptyHeap(Heap h) {
  return (h->front == 1);
}

void heapEmptyError(void) {
  printf("heap empty\n");
  abort();
}

void doubleHeapSize(Heap h) {
  int newSize = 2 * h->size;
  h->array = realloc(h->array, newSize * sizeof(int));
  assert(h->array != NULL);
  h->size = newSize;
}

void swap(int* x, int* y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void upheap(Heap h, int n) {
  if (n > 1 && h->array[n / 2] < h->array[n]) {
    swap(&(h->array[n / 2]), &(h->array[n]));
    upheap(h, n / 2);
  }
}

void enqueue(int n, Heap h) {
  if (h->front == h->size) {
    doubleHeapSize(h);
  }
  h->array[h->front] = n;
  upheap(h, h->front);
  (h->front)++;
}

void downheap(Heap h, int n) {
  if (h->front < 2 * n + 1) {  // node n is a leaf, do nothing
    return;
  }
  if (h->front == 2 * n + 1) {  // node n has only one child
    if (h->array[2 * n] > h->array[n]) {
      swap(&(h->array[n]), &(h->array[2 * n]));
      // no recursion, because 2 * n is the last element
      return;
    }
  }
  // now h->front > 2 * n + 1) i.e. node n has two children
  if (h->array[2 * n] > h->array[n] &&
      h->array[2 * n] >= h->array[2 * n + 1]) {
    swap(&(h->array[2 * n]), &(h->array[n]));
    downheap(h, 2 * n);
  }
  if (h->array[2 * n + 1] > h->array[n]) {
    swap(&(h->array[2 * n + 1]), &(h->array[n]));
    downheap(h, 2 * n + 1);
  }
}

int removeMax(Heap h) {
  if (isEmptyHeap(h)) {
    heapEmptyError();
  }
  int n = h->array[1];
  h->front--;
  h->array[1] = h->array[h->front];
  downheap(h, 1);
  return n;
}

void freeHeap(Heap h) {
  free(h->array);
  free(h);
}
