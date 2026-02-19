#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "libs/LibTree.h"

// Write a function that converts a tree from array to pointer representation.
// The tree contains only positive integers, empty places in the array are marked with -1.

Tree array2pointer(int arr[], int size) {
  int last = size - 1;
  if (last < 1){
	  return NULL;
  }

  Tree temp[last + 1];

  for (int i = last; i >= 1; --i) {
	  if (arr[i] == -1) {
		  temp [i] = NULL;
	  } else {
		  Tree L = (2*i <= last) ? temp[2*i] : NULL;
		  Tree R = (2*i + 1 <= last) ? temp[2*i + 1] : NULL;
		  temp [i] = newTree(arr[i], L, R);
	  }
  }
  return temp[1];
}

// do not modify this function
void printArr(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// do not modify the main function
int main(void) {
  int height = 0;
  printf("What is the height of the tree?\n");
  scanf("%d", &height);
  int count = 1 << (height + 1);
  int* arr = malloc(count * sizeof(int));
  arr[0] = -1;  // position 0 is not used for the tree
  printf("Please enter the array representation of the tree (%d items).\n", count - 1);
  printf("Start with with the root and enter one value per line.\n");
  printf("Only use positive values and -1 to denote empty spots.\n");
  for (int i = 1; i < count; i++) {
    scanf("%d", &arr[i]);
  }
  printf("The array representation: ");
  printArr(arr, count);
  Tree t = array2pointer(arr, count);
  printf("Printing the pointer tree in-order:\n");
  inOrder(t);
  freeTree(t);
  free(arr);
  exit(0);
}
