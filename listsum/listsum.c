#include <stdio.h>
#include <stdlib.h>
#include "libs/LibList.h"

// Write a function that, given a list,
// returns the sum of all its elements.

// You should write two answers, one with
// recursion and another using "while".

int listSumRecursion(List li) {
   if (isEmptyList(li)) {
        return 0;
    }
    return firstItem(li) + listSumRecursion(li->next);
}

int listSumIteration(List li) {
  int sum = 0;
    List li1 = li;

    while (li1 != NULL) {
        sum += firstItem(li1);
        li1 = li1->next;
    }

    return sum;
}

// do not modify the main function
int main(void) {
  int count = 0;
  printf("How many numbers?\n");
  scanf("%d", &count);
  List li = newEmptyList();
  printf("Please enter the numbers, one per line:\n");
  int next = 0;
  while (count > 0) {
    scanf("%d", &next);
    li = addItem(next, li);
    count--;
  }
  printf("Using recursion the sum of the numbers is %d.\n", listSumRecursion(li));
  printf("Using while the sum of the numbers is %d.\n", listSumIteration(li));
  freeList(li);
  exit(0);
}
