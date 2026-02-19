#include <stdio.h>
#include <stdlib.h>
#include "libs/LibList.h"

// Write a function that removes the *last* occurrence
// of a given integer in a list.

// For example, if li is the list [1,2,3,1,2,3], then
// removeLast(li, 2) should return 1 and modify the given
// list [1,2,3,1,3].

int removeLastOccurrence(List* lp, int n) {
  List current = *lp;
  List prev = NULL;
  List prevLast = NULL;
  List lastMatch = NULL;

  while (current != NULL) {
	  if (firstItem(current) == n) {
		  prevLast = prev;
		  lastMatch = current;
	  }
	  prev = current;
	  current = current->next;
  }

  if (lastMatch == NULL) {
        return 0;
    }

  if (prevLast == NULL) {
        *lp = removeFirstNode(*lp);
    } else {
        prevLast->next = removeFirstNode(prevLast->next);
    }

  return 1;
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
  printf("Of which number should the last occurence be removed?\n");
  int n = 0;
  scanf("%d", &n);
  removeLastOccurrence(&li, n);
  printf("The result after removing the last occurrence of %d is: ", n);
  printList(li);
  printf("\n");
  freeList(li);
  exit(0);
}
