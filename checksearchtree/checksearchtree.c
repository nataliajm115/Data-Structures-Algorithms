#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libs/LibTree.h"

// Write a function to check if a given tree is a search tree.

bool leftSubtree(Tree t, int x) {
	if (t == NULL) {
		return true;
	}
	return (t->item < x) && leftSubtree(t->leftChild, x)&& leftSubtree(t->rightChild, x);
}

bool rightSubtree(Tree t, int x){
	if (t == NULL) {
		return true;
	}
	return (t->item > x) && rightSubtree(t->leftChild, x) && rightSubtree(t->rightChild, x);
}

bool isSearchTree(Tree t) {
  if (t == NULL) {
	  return true;
  }
  return leftSubtree(t->leftChild, t->item) && rightSubtree(t->rightChild, t->item) && isSearchTree(t->leftChild) && isSearchTree(t->rightChild);
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
  printf("Printing the tree in-order:\n");
  inOrder(ts[1]);
  if (isSearchTree(ts[1])) {
    printf("That is a search tree.\n");
  } else {
    printf("That is NOT a search tree.\n");
  }
  freeTree(ts[1]);
  exit(0);
}
