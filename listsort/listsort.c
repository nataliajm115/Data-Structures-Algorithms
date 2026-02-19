#include <stdio.h>
#include <stdlib.h>
#include "libs/LibList.h"

// Write a function that sorts a list.

List sort(List li) {
	if (isEmptyList(li) || li->next == NULL) {
        return li; 
    }

    List sorted = newEmptyList();  
    List current = li;   

    while (current != NULL) {
        List next = current->next;  // store the next node
        if (sorted == NULL || current->item < sorted->item) {
            current->next = sorted;
            sorted = current;
        } else {
            List p = sorted;
            while (p->next != NULL && p->next->item <= current->item)
                p = p->next;
            current->next = p->next;
            p->next = current;
        }
        current = next;
    }

    return sorted;
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
  printf("The original list: ");
  printList(li);
  printf("\n");
  li = sort(li);
  printf("The sorted list: ");
  printList(li);
  printf("\n");
  freeList(li);
  exit(0);
}
