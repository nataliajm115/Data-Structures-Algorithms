#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// For graphs without weights we can reuse the list library.
#include "libs/LibList.h"

// Note: this is *not* the same as the typedef in the slides.
typedef struct ListGraph {
  int N;             // number of nodes
  List* neighbours;  // array of adjacency lists
} ListGraph;

// Write a function to convert a graph given in the array
// representation to a graph using adjacency lists.

// Note that we are working with *directed* graphs here.

ListGraph arrayToListGraph(int** arrayGraph, int N) {
  ListGraph g;
  g.N = N;

  g.neighbours = malloc(N *sizeof(List));

  for (int i = 0; i < N; i++) {
	  g.neighbours[i] = newEmptyList();
  }

  for (int i = 0; i < N; i++) {
	  for (int j = 0; j < N; j++) {
		  if (arrayGraph[i][j] == 1) {
			  g.neighbours[i] = addItem(j, g.neighbours[i]);
		  }
	  }
  }

  return g;
}

// do not modify this function
void freeListGraph(ListGraph g) {
  for (int x = 0; x < g.N; x++) {
    freeList(g.neighbours[x]);
  }
  free(g.neighbours);
}

// do not modify this function
void printListGraph(ListGraph g) {
  for (int x = 0; x < g.N; x++) {
    printf("reachable from %d:", x);
    List li = g.neighbours[x];
    while (li != NULL) {
      printf(" %d", li->item);
      li = li->next;
    }
    printf("\n");
  }
}

// do not modify the main function
int main(void) {
  int N = 0;
  printf("How many nodes does the graph have?\n");
  scanf("%d", &N);
  int** arrayGraph = malloc(N * sizeof(int*));
  for (int x = 0; x < N; x++) {
    arrayGraph[x] = calloc(N, sizeof(int));
  }
  printf("To add an edge, enter two nodes (between 0 and %d) separated by a space.\n", N - 1);
  printf("To finish and convert the graph, enter '!'.\n");
  while (1) {
    char c = getchar();
    if (c == '!') {
      // convert and print the graph:
      ListGraph lg = arrayToListGraph(arrayGraph, N);
      printListGraph(lg);
      // free memory used for the list graph:
      freeListGraph(lg);
      // free all memory we used for the array graph:
      for (int x = 0; x < N; x++) {
        free(arrayGraph[x]);
      }
      free(arrayGraph);
      exit(0);
    }
    ungetc(c, stdin);
    int a, b;
    scanf("%d %d", &a, &b);
    arrayGraph[a][b] = 1;
  }
}
