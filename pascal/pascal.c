#include <stdio.h>
#include <stdlib.h>

int factorial(int number){
	int result = 1;
	for (int i = 1; i <= number; i++){
		result *= i;
	}
	return result;
}

int binomialCoefficient(int row, int position){
	return factorial(row) / (factorial(position) * factorial(row - position));
}

int main(void) {
  printf("What is n?\n");
  int numberOfRows = 10;
  scanf("%d", &numberOfRows);
  for (int j = 0; j < numberOfRows; j++){
	  for (int spaces = 0; spaces < numberOfRows - j -1; spaces++){
		  printf("   ");
	  }
	  for (int k = 0; k <= j; k++){
		  printf("%6d", binomialCoefficient(j,k));
	  }
	  printf("\n");
  }
  exit(0);

}
