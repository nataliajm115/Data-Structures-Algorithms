#include <stdio.h>
#include <stdlib.h>

#include "libs/LibStack.h"

int main(void) {
  Stack s = newStack();

  int a, b, c;

  printf("What is the first number?\n");
  scanf("%d", &a);
  push(a, s);

  printf("What is the second number?\n");
  scanf("%d", &b);
  push(b, s);

  printf("What is the third number?\n");
  scanf("%d", &c);
  push(c, s);

  printf("Now we will pop from the stack.\n");
  printf("%d\n", pop(s));
  printf("%d\n", pop(s));
  printf("%d\n", pop(s));

  freeStack(s);

  exit(0);
}
