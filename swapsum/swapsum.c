#include <stdio.h>
#include <stdlib.h>

// Write a function that swaps the values of two given arguments.

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

// Write a function that takes three arguments x, y, z and
// assigns the sum of x and y to z.
// NOTE: You will have to change the type of the arguments
// here, and how the function is called in main(). below.

void setSum(int x, int y, int* z) {
	*z = x + y;
}

// Example for an exam question: For both functions above, explain
// which argument need to be pointers and which ones not, and why.

int main(void) {
  printf("Please enter two numbers, one per line:\n");
  int x = 0;
  int y = 0;
  int z = 0;
  scanf("%d", &x);
  scanf("%d", &y);
  swap(&x, &y);
  setSum(x, y, &z);  // change this line if needed
  printf("x = %d, y = %d, z = %d\n", x, y, z);
}
