/* by Gerard Renardel and Malvin Gattinger */

#ifndef LIBLIST_H
#define LIBLIST_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode* List;

struct ListNode {
  int item;
  List next;
};

List newEmptyList(void);

int isEmptyList(List li);
List addItem(int n, List li);
int firstItem(List li);
List removeFirstNode(List li);
void freeList(List li);
void print(List li);
void printList(List li);
void printListRec(List li);
int itemAtPos(List li, int p);
List addItemAtPos(List li, int n, int p);
List addItemAtPosIt(List li, int n, int p);
List removeItem(List li, int n);
List removeItemIt(List li, int n);

#endif
