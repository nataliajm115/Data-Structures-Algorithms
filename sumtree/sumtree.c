#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "libs/LibTree.h"

// Write a function that returns the sum of all elements in a tree.
// For example, for this tree:
//      1
//   12   14
// 5     6  7
// your function should return 45.

int sumTree(Tree t) {
	if (t == NULL) {
		return 0;
	}
	return t->item + sumTree(t->leftChild) + sumTree(t->rightChild);
}

// do not modify the main function
int main(void) {
  printf("Please enter seven values to make a tree of height 2.\n");
  printf("Start with with the root and enter one value per line.\n");
  printf("Only use positive values or use -1 to denote empty spots.\n");
  int tmp[8];
  for (int i = 1; i < 8; i++) {
    scanf("%d", &tmp[i]);
  }
  Tree ts[8];
  for (int i = 7; i > 0; i--) {
    if (tmp[i] == -1) {
      ts[i] = NULL;
    } else {
      if (i < 4) {
        ts[i] = newTree(tmp[i], ts[2 * i], ts[2 * i + 1]);
      } else {
        ts[i] = newTree(tmp[i], NULL, NULL);
      }
    }
  }
  int s = sumTree(ts[1]);
  printf("The sum of the tree is %d.\n", s);
  freeTree(ts[1]);
  exit(0);
}
