#include <stdio.h>

struct HeapS;
typedef struct HeapS* Heap;

Heap makeHeap(void);
int isEmptyHeap(Heap h);
void enqueue(int n, Heap h);
int removeMax(Heap h);
void freeHeap(Heap h);
