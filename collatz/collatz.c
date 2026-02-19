#include <stdio.h>
#include <stdlib.h>

int main(void){

  int n;
  int flag = 0;
  while (flag == 0){
	  printf("What is n? \n");
	  if (scanf("%d", &n)!=1 || n<=0){
		  printf("Invalid input. Please enter a positive integer.\n");
		  while (getchar() != '\n');
	  }
	  else{
		  flag = 1;
	  }
  }

  while (n!=1){
	  if (n%2 == 0){
		 n = n/2;
		 printf("n is now %d\n", n);
	  }
	  else{
		 n = 3*n + 1;
		 printf("n is now %d\n", n);
	  }
  } 

  exit(0);
}
