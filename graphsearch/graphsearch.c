#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "libs/LibList.h"
#include "libs/LibQueue.h"

// The goal in this exercise is to implement four different search alogrithms:
//
// (a) DFS for the two-dimensional array representation
// (b) DFS for the adjacency list representation
// (c) BFS for the two-dimensional array representation
// (d) BFS for the adjacency list representation
//
// Note: we asumme undirected unweighted graphs here!

typedef struct ListGraph {
  int N;             // number of nodes
  List* neighbours;  // array of adjacency lists
} ListGraph;

typedef struct ArrayGraph {
  int N;        // number of nodes
  bool** edge;  // two-dimenstional array
} ArrayGraph;

// Each search function should print all nodes of the
// graph in the order in which they are visited.

// (a) DFS for the two-dimensional array representation

const int new = 1;
const int old = 2;

// we need additional arguments for the labels
void aDFS_helper(ArrayGraph ag, int v, bool* visited, int** edgeLabel) {
	visited[v] = true;
	printf("%d\n", v);

	for (int w = 0; w < ag.N; w++) {
		if (ag.edge[v][w]) {
			if (!visited[w]) {
				edgeLabel[v][w] = new;
				aDFS_helper(ag, w, visited, edgeLabel);
				edgeLabel[v][w] = old;
			}
		}
	}
}

void aDFS(ArrayGraph ag, int v) {
  bool* visited = calloc(ag.N, sizeof(bool));
  int** edgeLabel = calloc(ag.N, sizeof(int*));
  for (int x = 0; x < ag.N; x++) {
    edgeLabel[x] = calloc(ag.N, sizeof(int));
  }
  aDFS_helper(ag, v, visited, edgeLabel);
  for (int x = 0; x < ag.N; x++) {
    free(edgeLabel[x]);
  }
  free(edgeLabel);
  free(visited);
}

// (b) BFS for the two-dimensional array representation
void aBFS(ArrayGraph ag, int v) {
  bool* visited = calloc(ag.N, sizeof(bool));
  int** edgeLabel = calloc(ag.N, sizeof(int*));
  for (int x = 0; x < ag.N; x++) {
    edgeLabel[x] = calloc(ag.N, sizeof(int));
  }

  Queue q = newQueue();
  enqueue(v, q);
  visited[v] = true;
  printf("%d\n", v);

  while (!isEmptyQueue(q)) {
	  int u = dequeue(q);
	  
	  for (int w = 0; w < ag.N; w++) {
		  if (ag.edge[u][w]) {
			  if (!visited[w]) {
				  edgeLabel[u][w] = new;
				  visited[w] = true;
				  printf("%d\n", w);
				  enqueue(w, q);
			  } else {
				  edgeLabel[u][w] = old;
			  }
		  }
	  }
  }

  freeQueue(q);

  for (int x = 0; x < ag.N; x++) {
    free(edgeLabel[x]);
  }
  free(edgeLabel);
  free(visited);
}

// helper function to check if x is in the list l
bool isInList(int x, List l) {
  if (l == NULL) {
    return false;
  }
  return ((l->item == x) || isInList(x, l->next));
}

// (c) DFS for the adjacency list representation
void lDFS_helper(ListGraph lg, int v, List* visited, List* newEdges, List* oldEdges) {
  *visited = addItem(v, *visited);
  printf("%d\n", v);
  List l = lg.neighbours[v];
  while (l != NULL) {
	  int w = l->item;
	  if(!isInList(w, *visited)) {
		  newEdges[v] = addItem(w, newEdges[v]);
		  lDFS_helper(lg, w, visited, newEdges, oldEdges);
	  } else {
		  oldEdges[v] = addItem(w, oldEdges[v]);
	  }
	  l = l->next;
  }
}

void lDFS(ListGraph lg, int v) {
  List visited = newEmptyList();
  List* newEdges = malloc(lg.N * sizeof(List));
  for (int x = 0; x < lg.N; x++) {
    newEdges[x] = newEmptyList();
  }
  List* oldEdges = malloc(lg.N * sizeof(List));
  for (int x = 0; x < lg.N; x++) {
    oldEdges[x] = newEmptyList();
  }
  lDFS_helper(lg, v, &visited, newEdges, oldEdges);
  for (int x = 0; x < lg.N; x++) {
    freeList(newEdges[x]);
    freeList(oldEdges[x]);
  }
  free(newEdges);
  free(oldEdges);
  freeList(visited);
}

// (d) BFS for the adjacency list representation
void lBFS(ListGraph lg, int v) {
  List visited = newEmptyList();
  List* newEdges = malloc(lg.N * sizeof(List));
  for (int x = 0; x < lg.N; x++) {
    newEdges[x] = newEmptyList();
  }
  List* oldEdges = malloc(lg.N * sizeof(List));
  for (int x = 0; x < lg.N; x++) {
    oldEdges[x] = newEmptyList();
  }

  Queue q = newQueue();
  enqueue(v, q);

  visited = addItem(v, visited);
  printf("%d\n", v);

  while (!isEmptyQueue(q)) {
	  int u = dequeue(q);

	  List l = lg.neighbours[u];
	  while (l != NULL) {
		  int w = l->item;

		  if (!isInList(w, visited)) {
			  newEdges[u] = addItem(w, newEdges[u]);
			  visited = addItem(w, visited);
			  printf("%d\n", w);
			  enqueue(w, q);
		  } else {
			  oldEdges[u] = addItem(w, oldEdges[u]);
		  }

		  l = l->next;
	  }
  }

  freeQueue(q);

  for (int x = 0; x < lg.N; x++) {
    freeList(newEdges[x]);
    freeList(oldEdges[x]);
  }
  free(newEdges);
  free(oldEdges);
  freeList(visited);
}

// do not modify this function
void freeListGraph(ListGraph g) {
  for (int x = 0; x < g.N; x++) {
    freeList(g.neighbours[x]);
  }
  free(g.neighbours);
}

List insertInOrder(int x, List l) {
  if (l == NULL || l->item > x) {
    return addItem(x, l);
  }
  l->next = insertInOrder(x, l->next);
  return l;
}

// do not modify the main function
int main(void) {
  int N = 0;
  printf("How many nodes does the graph have?\n");
  scanf("%d", &N);
  getchar();
  // prepare the array graph:
  ArrayGraph ag;
  ag.N = N;
  ag.edge = malloc(N * sizeof(bool*));
  for (int x = 0; x < N; x++) {
    ag.edge[x] = calloc(N, sizeof(int));
  }
  // prepare the list graph:
  ListGraph lg;
  lg.N = N;
  lg.neighbours = malloc(N * sizeof(List));
  for (int x = 0; x < N; x++) {
    lg.neighbours[x] = NULL;
  }
  // read in the edges:
  printf("To add an edge, enter two nodes (between 0 and %d) separated by a space.\n", N - 1);
  printf("We assume undirected unweighted graphs here. Hence, if you add the\n");
  printf("edge '0 1' then please also add '1 0' etc. To finish, enter '!'.\n");
  char c;
  while ((c = getchar()) && c != '!') {
    ungetc(c, stdin);
    int a, b;
    scanf("%d %d", &a, &b);
    getchar();
    ag.edge[a][b] = 1;
    lg.neighbours[a] = insertInOrder(b, lg.neighbours[a]);
  }
  // choose a search algorithm:
  printf("What is the starting node?\n");
  int v = 0;
  scanf("%d", &v);
  getchar();
  printf("Which search algorithm do you want to run?\n");
  printf(" Write 'a' to use DFS for the two-dimensional array representation.\n");
  printf(" Write 'b' to use BFS for the two-dimensional array representation.\n");
  printf(" Write 'c' to use DFS for the adjacency list representation.\n");
  printf(" Write 'd' to use BFS for the adjacency list representation.\n");
  char algo = ' ';
  scanf("%c", &algo);
  getchar();  // ignore line break
  if (algo == 'a') {
    aDFS(ag, v);
  }
  if (algo == 'b') {
    aBFS(ag, v);
  }
  if (algo == 'c') {
    lDFS(lg, v);
  }
  if (algo == 'd') {
    lBFS(lg, v);
  }
  // free all memory we used for both graph representations:
  for (int x = 0; x < N; x++) {
    free(ag.edge[x]);
    freeList(lg.neighbours[x]);
  }
  free(lg.neighbours);
  free(ag.edge);
  exit(0);
}
