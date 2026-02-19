#include <stdio.h>
#include <stdlib.h>

#include "libs/LibQueue.h"

int main(void) {
  Queue q = newQueue();
  int a, b, c;

  printf("What is the first number?\n");
  scanf("%d", &a);
  enqueue(a, q);

  printf("What is the second number?\n");
  scanf("%d", &b);
  enqueue(b, q);

  printf("What is the third number?\n");
  scanf("%d", &c);
  enqueue(c, q);

  printf("Now we will dequeue from the queue.\n");
  printf("%d\n", dequeue(q));
  printf("%d\n", dequeue(q));
  printf("%d\n", dequeue(q));
  freeQueue(q);

  exit(0);
}
