#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Given a graph in array representation,
// print whether it has an Euler path/cycle.
void euler(int** arrayGraph, int N) {
	int oddCount = 0;

	for (int i = 0; i < N; i++) {
		int degree = 0;
		for (int j = 0; j < N; j++) {
			degree += arrayGraph[i][j];
		}
		if (degree % 2 != 0) {
			oddCount++;
		}
	}

	if(oddCount == 0) {
		printf("This graph has an Euler cycle.\n");
	}
	else if (oddCount == 2) {
		printf("This graph has an Euler path, but not an Euler cycle.\n");
	}
	else {
		printf("This graph has no Euler path.\n");
	}
}

// do not modify the main function
int main(void) {
  int N = 0;
  printf("How many nodes does the graph have?\n");
  scanf("%d", &N);
  // allocate memory for a two-dimensional array of size N*N:
  int** arrayGraph = malloc(N * sizeof(int*));
  for (int x = 0; x < N; x++) {
    arrayGraph[x] = calloc(N, sizeof(int));
  }
  printf("To add an edge, enter two nodes (between 0 and %d) separated by a space.\n", N - 1);
  printf("The graph is undirected, so whether you enter '0 1' or '1 0' makes no difference.\n");
  printf("To finish and check if the graph has an Euler path/cycle, enter '!'.\n");
  while (1) {
    char c = getchar();
    if (c == '!') {
      // print whether the graph has an euler path/cycle:
      euler(arrayGraph, N);
      // free all memory we used for the graph:
      for (int x = 0; x < N; x++) {
        free(arrayGraph[x]);
      }
      free(arrayGraph);
      exit(0);
    }
    ungetc(c, stdin);
    int a, b;
    scanf("%d %d", &a, &b);
    getchar();  // ignore line break after using scanf
    arrayGraph[a][b]++;
    arrayGraph[b][a]++;
  }
}
