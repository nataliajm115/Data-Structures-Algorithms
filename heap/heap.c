#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// The following are all the heap functions from the lecture slides.
// Still missing are upheap() and downheap().
// Implement them, according to the pseudocode given on the slides.
// Please do not modify any of the other functions.

typedef struct Heap {
  int* array;
  int front;
  int size;
} Heap;

Heap makeHeap(void) {
  Heap h;
  h.array = malloc(1 * sizeof(int));
  assert(h.array != NULL);
  h.front = 1;
  h.size = 1;
  return h;
}

int isEmptyHeap(Heap h) {
  return (h.front == 1);
}

void heapEmptyError(void) {
  printf("heap empty\n");
  abort();
}

void doubleHeapSize(Heap* hp) {
  int newSize = 2 * hp->size;
  hp->array = realloc(hp->array, newSize * sizeof(int));
  assert(hp->array != NULL);
  hp->size = newSize;
}

// A helper function for upheap and downheap.
void swap(int* x, int* y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

// TODO
void upheap(Heap* hp, int n) {
	if (n == 1) {
		return;
	}
	int u = n / 2;

	if (hp->array[u] < hp->array[n]) {
		swap(&hp->array[u], &hp->array[n]);
		upheap(hp, u);
	}
}

void enqueue(int n, Heap *hp) {
  if (hp->front == hp->size) {
    doubleHeapSize(hp);
  }
  hp->array[hp->front] = n;
  upheap(hp, hp->front);
  (hp->front)++;;
}

// TODO
void downheap(Heap* hp, int n) {
	int best = n;
	int l = 2 * n;
	int r = 2 * n + 1;

	if (l <= hp->front && hp->array[n] < hp->array[l]) {
		best = l;
	}
	if (r <= hp->front && hp->array[best] < hp->array[n]) {
		best = r;
	}
	if (best != n) {
		swap(&hp->array[best], &hp->array[n]);
		downheap(hp, best);
	}
}

int removeMax(Heap *hp) {
  if (isEmptyHeap(*hp)) {
    heapEmptyError();
  }
  int n = hp->array[1];
  hp->front--;
  hp->array[1] = hp->array[hp->front];
  downheap(hp, 1);
  return n;
}

void freeHeap(Heap* hp) {
  free(hp->array);
}

// do not modify the main function
int main(void) {
  printf("Please enter one of the following:\n");
  printf("- any positive value to insert into the heap\n");
  printf("- a 0 to remove and print the maximum element\n");
  printf("- a -1 to quit.\n");
  Heap h = makeHeap();
  int val = 0;
  scanf("%d", &val);
  while (val != -1) {
    if (val == 0) {
      printf("Removed maximum value from heap: %d\n", removeMax(&h));
    } else {
      enqueue(val, &h);
    }
    scanf("%d", &val);
  }
  freeHeap(&h);
  exit(0);
}
