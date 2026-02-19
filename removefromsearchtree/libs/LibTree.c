/* by Malvin Gattinger */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "LibTree.h"

Tree emptyTree(void) {
  return NULL;
}

Tree newTree(int n, Tree tL, Tree tR) {
  Tree new = malloc(sizeof(struct TreeNode));
  assert(new != NULL);
  new->item = n;
  new->leftChild = tL;
  new->rightChild = tR;
  return new;
}

void preOrder(Tree t) {
  if (t == NULL) {
    return;
  }
  printf("%d\n", t->item);
  preOrder(t->leftChild);
  preOrder(t->rightChild);
}

void postOrder(Tree t) {
  if (t == NULL) {
    return;
  }
  postOrder(t->leftChild);
  postOrder(t->rightChild);
  printf("%d\n", t->item);
}

void inOrder(Tree t) {
  if (t == NULL) {
    return;
  }
  inOrder(t->leftChild);
  printf("%d\n", t->item);
  inOrder(t->rightChild);
}

void freeTree(Tree t) {
  if (t == NULL) {
    return;
  }
  freeTree(t->leftChild);
  freeTree(t->rightChild);
  free(t);
}

Tree searchNode(Tree t, int n) {
  if (t == NULL) {
    return NULL;
  }
  if (n == t->item) {
    return t;
  }
  t = (n < t->item ? t->leftChild : t->rightChild);
  return searchNode(t, n);
}

Tree addInSearchTree(Tree t, int n) {
  if (t == NULL) {
    return newTree(n, emptyTree(), emptyTree());
  }
  if (n < t->item) {
    t->leftChild = addInSearchTree(t->leftChild, n);
  } else if (n > t->item) {
    t->rightChild = addInSearchTree(t->rightChild, n);
  }
  return t;
}
