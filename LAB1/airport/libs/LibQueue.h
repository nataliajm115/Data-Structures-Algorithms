/* by Gerard Renardel and Malvin Gattinger */

#ifndef LIBQUEUE_H
#define LIBQUEUE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueS* Queue;

Queue newQueue(void);

void enqueue(int item, Queue q);
int dequeue(Queue q);

int isEmptyQueue(Queue q);
void freeQueue(Queue q);

#endif
