#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "libs/LibTree.h"

// Goal: a function to remove an element from a search tree.
// Use the pseudocode of "RemoveFromSearchTree" in the slides.

// First, write a helper function that given t will find
// the in-order successor u of t, then removes u from the
// tree and returns the value that was stored at u.

int removeInOrderSuccessor(Tree t) {
  if (t == NULL || t->rightChild == NULL) return 0;

  Tree parent  = t;
  Tree u = t->rightChild;

  while (u->leftChild != NULL){
	  parent = u;
	  u = u->leftChild;
  }

  int n = u->item;

  if (parent->rightChild == u) {
	  parent->rightChild = u->rightChild;
  } else {
	  parent->leftChild = u->rightChild;
  }
  
  free(u);
  return n;
}

// Second, write a function to remove a value from a search tree.

Tree removeFromSearchTree(Tree t, int n) {
	if (t == NULL){
		return NULL;
	}
	if (n < t->item) {
		t->leftChild = removeFromSearchTree(t->leftChild, n);
		return t;
	} else if (n > t->item) {
		t->rightChild = removeFromSearchTree(t->rightChild, n);
		return t;
	}
	if (t->leftChild == NULL && t->rightChild == NULL) {
		free(t);
		return NULL;
	}
	if(t->leftChild == NULL) {
		Tree r = t->rightChild;
		free(t);
		return r;
	}
	if (t->rightChild == NULL) {
		Tree l = t->leftChild;
		free(t);
		return l;
	}
	t->item = removeInOrderSuccessor(t);
	return t;

}

// do not modify the main function
int main(void) {
  printf("Please enter positive values to insert into a search tree.\n");
  printf("Enter one value per line and use -1 to finish.\n");
  Tree t = emptyTree();
  int val = 0;
  scanf("%d", &val);
  while (val != -1) {
    t = addInSearchTree(t, val);
    scanf("%d", &val);
  }
  printf("Printing the given tree in-order:\n");
  inOrder(t);
  printf("Now enter some values to be removed from the search tree.\n");
  printf("Enter one value per line and use -1 to finish.\n");
  scanf("%d", &val);
  while (val != -1) {
    t = removeFromSearchTree(t, val);
    scanf("%d", &val);
  }
  printf("Printing the remaining tree in-order:\n");
  inOrder(t);
  freeTree(t);
  exit(0);
}
