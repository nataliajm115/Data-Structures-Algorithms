#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/LibTree.h"

// Write a function that prints a tree given in pointer representation.
// For example, this tree:
//      1
//   12   14
// 5     6  7
// should be printed as:
// 1
// . 12
// . . 5
// . 14
// . . 6
// . . 7
//
// Hint: You will need a helper function!

void printTreeHelper(Tree t, int depth) {
	if (t == NULL) {
		return;
	}

	for (int i = 0; i< depth; i++) {
		printf(". ");
	}
	printf("%d\n", t->item);
	printTreeHelper(t->leftChild, depth + 1);
	printTreeHelper(t->rightChild, depth +1);
}

void printTree(Tree t) {
	printTreeHelper(t, 0);
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
  printf("Now we print the tree.\n");
  printTree(ts[1]);
  freeTree(ts[1]);
  exit(0);
}
