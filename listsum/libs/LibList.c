/* by Gerard Renardel and Malvin Gattinger */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "LibList.h"

List newEmptyList(void) {
  return NULL;
}

int isEmptyList(List li) {
  return (li == NULL);
}

void listEmptyError(void) {
  printf("list empty\n");
  abort();
}

List addItem(int n, List li) {
  List newList = malloc(sizeof(struct ListNode));
  assert(newList != NULL);
  newList->item = n;
  newList->next = li;
  return newList;
}

int firstItem(List li) {
  if (li == NULL) {
    listEmptyError();
  }
  return li->item;
}

List removeFirstNode(List li) {
  List returnList;
  if (li == NULL) {
    listEmptyError();
  }
  returnList = li->next;
  free(li);
  return returnList;
}

void freeList(List li) {
  List li1;
  while (li != NULL) {
    li1 = li->next;
    free(li);
    li = li1;
  }
  return;
}

void printList(List li) {
  while (li != NULL) {
    printf("%d ", li->item);
    li = li->next;
  }
}

void printListRec(List li) {
  if (li == NULL) {
    return;
  }
  printf("%d ", li->item);
  printListRec(li->next);
}

void listTooShort(void) {
  printf("List too short\n");
  abort();
}

int itemAtPos(List li, int p) {
  if (li == NULL) {
    listTooShort();
  }
  if (p == 0) {
    return firstItem(li);
  } else {
    return itemAtPos(li->next, p - 1);
  }
}

List addItemAtPos(List li, int n, int p) {
  if (p == 0) {
    return addItem(n, li);
  }
  if (li == NULL) {
    listTooShort();
  }
  li->next = addItemAtPos(li->next, n, p - 1);
  return li;
}

List addItemAtPosIt(List li, int n, int p) {
  List li1;
  if (p == 0) {
    return addItem(n, li);
  }
  li1 = li;
  while (li1 != NULL && p > 1) {
    li1 = li1->next;
    p--;
  }
  if (li1 == NULL) {
    listTooShort();
  }
  /* now li1 points to the node on position p-1 */
  li1->next = addItem(n, li1->next);
  return li;
}

List removeItem(List li, int n) {
  if (li == NULL) {
    return li;
  }
  if (li->item == n) {
    return removeFirstNode(li);
  }
  li->next = removeItem(li->next, n);
  return li;
}

List removeItemIt(List li, int n) {
  List li1;
  if (li == NULL) {
    return li;
  }
  if (li->item == n) {
    return removeFirstNode(li);
  }
  li1 = li;
  while (li1->next != NULL && (li1->next)->item != n) {
    li1 = li1->next;
  }
  if (li1->next != NULL) { /* so (li1->next)->item == n */
    li1->next = removeFirstNode(li1->next);
  }
  return li;
}
