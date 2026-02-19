#include <stdio.h>
#include <stdlib.h>

// Write a function that finds the maximum value in an array.

int maxArray(int arr[], int arrLength) {
  int maxValueIndex = 0;
  for (int i = 0; i<arrLength; i++){
	  if (arr[i] >= arr[maxValueIndex]){
		 maxValueIndex = i;
	  }
  }
  return arr[maxValueIndex];
}

// do not modify the main function
int main(void) {
  int count = 0;
  printf("How many numbers?\n");
  scanf("%d", &count);
  int *arr = malloc(count * sizeof(int));
  printf("Please enter the numbers, one per line:\n");
  for (int i=0; i<count; i++) {
    scanf("%d", &arr[i]);
  }
  printf("The maximum value in this array is %d\n", maxArray(arr, count));
  free(arr);
  exit(0);
}
