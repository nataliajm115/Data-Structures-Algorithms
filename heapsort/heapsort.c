#include <stdio.h>
#include <stdlib.h>

#include "libs/LibHeap.h"

// Write a function that sorts an array, using a heap.

void heapsort(int arr[], int size) {
  Heap h = makeHeap();

  for (int i = 0; i < size; i++) {
	  enqueue(arr[i], h);
  }

  for (int end = size - 1; end >= 0; end--) {
	  arr[end] = removeMax(h);
  }

  freeHeap(h);

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
  int count = 0;
  printf("How many numbers?\n");
  scanf("%d", &count);
  int* arr = malloc(count * sizeof(int));
  printf("Please enter the numbers, one per line:\n");
  for (int i = 0; i < count; i++) {
    scanf("%d", &arr[i]);
  }
  printf("The original array: ");
  printArr(arr, count);
  heapsort(arr, count);
  printf("The sorted array: ");
  printArr(arr, count);
  free(arr);
  exit(0);
}
