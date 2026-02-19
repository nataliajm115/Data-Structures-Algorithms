#include <stdio.h>
#include <stdlib.h>
#include "libs/LibList.h"

// Write a function backwards that, given a list,
// prints all elements in reverse order, with
// one element per line.
// Hint: use recursion!

void backwards(List li) {
  if (isEmptyList(li)){
	  return;
  }
  else{
	  backwards(li->next);
	  printf("%d\n", firstItem(li));
  }

}

// do not modify the main function
int main(void) {
  int count = 0;
  printf("How many numbers?\n");
  scanf("%d", &count);
  List li = newEmptyList();
  printf("Please enter %d numbers, one per line:\n", count);
  int next = 0;
  for (int p = 0; p < count; p++) {
    scanf("%d", &next);
    li = addItemAtPos(li, next, p);
  }
  printf("The given list is: ");
  printList(li);
  printf("\n");
  printf("Printing the list in reverse order:\n");
  backwards(li);
  freeList(li);
  exit(0);
}
