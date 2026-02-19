#include <stdio.h>
#include <stdlib.h>

long long collatzLength(long long n){
	long long sumCollatz = 1;
	while (n!=1){
		if (n%2 == 0){
			n = n/2;
		}
		else{
			n = 3*n +1;
		}
		sumCollatz++;
	}
	return sumCollatz;



}

int main(void) {
	long long n;
	int flag = 0;
	while (flag == 0){
	       printf("What is n?\n");
	       if (scanf("%lld", &n) != 1 || n <= 0){
		       printf("Invalid input. Enter a positive integer.\n");
		       while (getchar() != '\n');
	       }
	       else{
		       flag = 1;
	       }
	}


	long long maxLength = 0;
	long long kNumber = 1;
	for (long long k = 1;k<=n;k++){
		long long currentLength = collatzLength(k);
		if (currentLength > maxLength){
			maxLength = currentLength;
			kNumber = k;
		}
	}
	printf("%lld \n", kNumber);

  exit(0);
}
