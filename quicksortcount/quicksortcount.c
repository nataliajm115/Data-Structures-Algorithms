#include <stdio.h>
#include <stdlib.h>

int numSplits = 0; // global variable to count splits

// An implementation of QuickSort for arrays.

// Swap the values at the two given positions
void swap(int A[], int i, int j) {
  int temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

// Using A[s] as a pivot, rearrange the values in the
// sub-array between positions s and e such that items
// left of A[r] are lower or equal and items right of
// are larger or equal. Returns position r.
int distribute(int A[], int s, int e) {
  numSplits++; // count this split

  int l = s + 1;
  int r = e;
  while (l <= r) {
    while (A[l] <= A[s] && l <= r)
      l++;
    while (A[r] >= A[s] && l <= r)
      r--;
    if (l < r)
      swap(A, l, r);
  }
  swap(A, r, s);
  return r;
}

void quicksortFromTo(int A[], int s, int e) {
  // Sort the sub-array between s and e.
  if (e > s) {
    int pivot = distribute(A, s, e);
    quicksortFromTo(A, s, pivot - 1);
    quicksortFromTo(A, pivot + 1, e);
  }
}

// TODO: change this function to return an int, the number of splits.
void sort(int A[], int size) {
  numSplits = 0;
  quicksortFromTo(A, 0, size - 1);
}

// do not modify this function
void printArr(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// TODO: adjust the main function to also print the number of splits
int main(void) {
  int length = 0;
  printf("How many numbers?\n");
  scanf("%d", &length);
  int* arr = malloc(length * sizeof(int));
  printf("Please enter the numbers, one per line:\n");
  for (int i = 0; i < length; i++) {
    scanf("%d", &arr[i]);
  }
  printf("The original array: ");
  printArr(arr, length);
  sort(arr, length);
  printf("The sorted array: ");
  printArr(arr, length);
  printf("Number of splits needed: %d\n", numSplits);
  free(arr);
  exit(0);
}
