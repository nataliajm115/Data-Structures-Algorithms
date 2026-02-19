/* by Gerard Renardel and Malvin Gattinger */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "LibQueue.h"

typedef struct QueueS {
  int* array;
  int back;
  int front;
  int size;
} QueueS;

const int INITIAL_QUEUE_SIZE = 7;

Queue newQueue(void) {
  Queue q = malloc(sizeof(QueueS));
  assert(q != NULL);
  q->array = malloc(INITIAL_QUEUE_SIZE * sizeof(int));
  assert(q->array != NULL);
  q->back = 0;
  q->front = 0;
  q->size = INITIAL_QUEUE_SIZE;
  return q;
}

int isEmptyQueue(Queue q) {
  return (q->back == q->front);
}

void queueEmptyError(void) {
  printf("queue empty\n");
  abort();
}

void doubleQueueSize(Queue q) {
  int oldSize = q->size;
  q->size = 2 * oldSize;
  q->array = realloc(q->array, q->size * sizeof(int));
  assert(q->array != NULL);
  for (int i = 0; i < q->back; i++) { /* eliminate split configuration */
    q->array[oldSize + i] = q->array[i];
  }
  q->back = q->back + oldSize; /* update q->back */
}

void enqueue(int item, Queue q) {
  q->array[q->back] = item;
  q->back = (q->back + 1) % q->size;
  if (q->back == q->front) {
    doubleQueueSize(q);
  }
}

int dequeue(Queue q) {
  if (isEmptyQueue(q)) {
    queueEmptyError();
  }
  int item = q->array[q->front];
  q->front = (q->front + 1) % q->size;
  return item;
}

void freeQueue(Queue q) {
  free(q->array);
  free(q);
}
