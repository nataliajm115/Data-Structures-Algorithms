/* by Gerard Renardel and Malvin Gattinger */

#ifndef LIBLIST_H
#define LIBLIST_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode* Tree;

struct TreeNode {
  int item;
  Tree leftChild;
  Tree rightChild;
};

Tree emptyTree(void);

Tree newTree(int n, Tree tL, Tree tR);

void preOrder(Tree t);
void postOrder(Tree t);
void inOrder(Tree t);

void freeTree(Tree t);

Tree searchNode(Tree t, int n);
Tree addInSearchTree(Tree t, int n);

#endif
