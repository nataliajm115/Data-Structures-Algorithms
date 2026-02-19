#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Write a program that asks "What is n?",
  // then uses malloc to create an int-array
  // of size n, then keeps asking "What is the next number?"
  // to read in n many numbers, writes them into the array,
  // and finally prints the whole array in one line, separated by spaces.

  // ...
  int n;
  printf("What is n?\n");
  scanf("%d", &n);
  int* intarray = malloc(n * sizeof(int));
  if (intarray == NULL){
	  printf("Memory allocation failed");
	  return 1;
  }
  for(int i = 0; i < n; i++){
	  printf("What is the next number?\n");
	  scanf("%d", &intarray[i]);
  }
  for(int j = 0; j < n; j++){
	  printf("%d ", intarray[j]);
  }
  printf("\n");
  free(intarray);

  exit(0);
}
