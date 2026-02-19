#include <stdio.h>
#include <stdlib.h>

// Write a function that sorts an array

void sort(int arr[], int size) {
	if (size < 2) {
		return;
	}
	int middle = size / 2;
	int* left = malloc(middle * sizeof(int));
	int* right = malloc((size - middle) * sizeof(int));
	for (int i = 0; i < middle; i++) {
		left[i] = arr[i];
	}
	for (int j = middle; j < size; j++) {
		right[j - middle] = arr[j];
	}
	sort(left, middle);
	sort(right, size - middle);

	int i = 0, j = 0, k = 0;
	while (i < middle && j < size - middle) {
		if (left[i] <= right[j]) {
			arr[k++] = left[i++];
		} else {
			arr[k++] = right[j++];
		}
	}
	while (i < middle) {
		arr[k++] = left[i++];
	}
	while (j < size - middle) {
		arr[k++] = right[j++];
	}
	free(left);
	free(right);
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
  sort(arr, count);
  printf("The sorted array: ");
  printArr(arr, count);
  free(arr);
  exit(0);
}
