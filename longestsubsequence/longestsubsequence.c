#include <stdio.h>
#include <stdlib.h>

// Write a function that finds the starting position
// of the longest increasing subsequence in an array.
//
// For example, given the numbers [2,1,2,1,2,3,6,1,2],
// it should return 3 because [1,2,3,6] is the longest
// increasing subsequence and starts at position 3.
//
// You may also define additional helper functions.

int longestSeqStart(int arr[], int arrLength) {
	int finalSeqLen = 0;
	int start = 0;
	for (int i = 0; i < arrLength-1; i++){
		if (arr[i]<arr[i+1]){
			int tempSeqLen = 2;
			int j = i+1;
			while (j < arrLength-1 && arr[j] < arr[j+1]){
				tempSeqLen++;
				j++;
			}
			if (tempSeqLen > finalSeqLen){
				finalSeqLen = tempSeqLen;
				start = i;
			}
		}
	}
	return start;
}

// do not modify the main function
int main(void) {
  int arrLength = 0;
  printf("How many numbers?\n");
  scanf("%d", &arrLength);
  int* numbers = malloc(arrLength * sizeof(int));
  printf("Please enter the numbers, one per line:\n");
  for (int i = 0; i < arrLength; i++) {
    scanf("%d", &numbers[i]);
  }
  int start = longestSeqStart(numbers, arrLength);
  printf("The longest increasing sequence starts at position %d:\n", start);
  int curPos = start;
  printf("%d\n", numbers[curPos]);
  while (curPos < arrLength - 1 && numbers[curPos] < numbers[curPos + 1]) {
    curPos++;
    printf("%d\n", numbers[curPos]);
  }
  free(numbers);
}
