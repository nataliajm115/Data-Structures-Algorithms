/* 
 * @file trainsinternational.c
 * @brief International railway routing system (Bonus Part B)
 * This program reads a number of railway networs and computes
 * shortest travel time paths between stations using Dijkstra's algorithm.
 * 
 * The program supports temporary disruptions by removing specified connections
 * before processing queries.
 *
 * Input and output formats follow specification of Bonus Part B.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 100000000
#define MAX_NAME_LEN 256

// ********************************************************
//                 GRAPH CONSTRUCTION
// ********************************************************

/**
 * @struct Station
 * @brief Node in adjacency list representing a railway connection.
 *
 * @var station         station ID
 * @var time            travel time
 * @var next            pointer to next edge in adjacency list
 */
typedef struct Station {
  int station;
  int time;
  struct Station* next;
} Station;

/*
 * Railway graph represented as an array of adjacency lists.
 */
typedef Station* Railway;

/*
 * @brief Initialize empty railway graph.
 *
 * @param graph	 railway graph
 * @param n	 number of stations in graph
 *
 * @pre   graph is allocated with size n
 * @post  all adjacency lists are NULL
 */
void initEmptyRailway(Railway graph[], int n) {
  for (int i = 0; i < n; i++) {
    graph[i] = NULL;
  }
}

/*
 * @brief Add a one way connection to the graph.
 *
 * @param graph  railway graph
 * @param from   source station ID
 * @param to     destination station ID
 * @param time   travel time
 *
 * @post a new edge is inserted
 */
void addEdge(Railway graph[], int from, int to, int time) {
  Station* newNode = malloc(sizeof(Station));
  assert(newNode != NULL);

  newNode->station = to;
  newNode->time = time;
  newNode->next = graph[from];
  graph[from] = newNode;
}

/*
 * @brief Creates the undirected connection between the two stations
 *
 * @param a     station A
 * @param b     station B
 * @param time  travel time between the two stations
 *
 * @post two-way connection between two stations is created
 */
void addUndirectedEdge(Railway graph[], int a, int b, int time) {
  addEdge(graph, a, b, time);
  addEdge(graph, b, a, time);
}

/*
 * @brief Remove directed edge.
 *
 * @param graph  railway graph
 * @param from   starting station
 * @param to     destination station
 *
 * @post directed edge is removed if it exists
 */
void removeEdgeOneWay(Railway graph[], int from, int to) {
  Station* curr = graph[from];
  Station* prev = NULL;
  while (curr != NULL) {
    if (curr->station == to) {
      if (prev == NULL) {
        // removing first node
        graph[from] = curr->next;
      } else {
        prev->next = curr->next;
      }
      free(curr);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

/*
 * @param Remove bidirectional railway connection.
 *
 * @param graph  railway graph
 * @param a      station A
 * @param b      station B
 *
 * @post both directed edges between a and b are removed if they exist
 */
void removeConnection(Railway graph[], int a, int b) {
  removeEdgeOneWay(graph, a, b);
  removeEdgeOneWay(graph, b, a);
}

/*
 * @brief Free all memory used by railway graph.
 *
 * @param graph   railway graph
 * @param n       number of stations
 */
void freeRailway(Railway graph[], int n) {
  for (int i = 0; i < n; i++) {
    Station* curr = graph[i];
    while (curr != NULL) {
      Station* next = curr->next;
      free(curr);
      curr = next;
    }
    graph[i] = NULL;
  }
}

// ********************************************************
//                      MIN HEAP
// ********************************************************

/**
 * @struct HeapNode
 * @brief Node in min-heap used in Dijkstra's.
 *
 * @var station   station ID
 * @var dist      current distance from the start station
 */
typedef struct {
  int station;
  int dist;
} HeapNode;

/**
 * @struct Heap
 * @brief Min-heap storing HeapNodes ordered by time.
 *
 * @var array     dynamic array storing heap elements
 * @var front     index of the next free position (heap size + 1)
 * @var size      allocated capacity of the array
 */
typedef struct {
  HeapNode* array;
  int front;
  int size;
} Heap;

/*
 * @brief Create an empty min-heap.
 *
 * @param n    number of stations
 *
 * @post An empty heap is created with initial capacity n+1.
 */
Heap makeHeap(int n) {
  Heap h;
  // Initial capacity avoids unnecessary resizings
  h.size = n + 1;
  h.array = malloc(h.size * sizeof(HeapNode));
  assert(h.array != NULL);
  h.front = 1;
  return h;
}

/*
 * @brief Check whether the heap is empty.
 */
bool isEmptyHeap(Heap* h) {
  return h->front == 1;
}

/*
 * @brief Prints error message for an empty heap
 */
void emptyHeapError() {
  printf("Heap is empty");
}

/*
 * @brief Double the capacity of the heap.
 *
 * @param hp    pointer to a heap
 *
 * @pre   hp is a valid heap
 * @post  heap capacity is doubled
 */
void doubleHeapSize(Heap* hp) {
  hp->size *= 2;
  hp->array = realloc(hp->array, hp->size * sizeof(HeapNode));
  assert(hp->array != NULL);
}

/*
 * @brief Swap two elements in the heap
 */
void swap(HeapNode* a, HeapNode* b) {
  HeapNode t = *a;
  *a = *b;
  *b = t;
}

/*
 * @brief Restore the structural property after enqueueing a new element
 *
 * @param hp   min-heap
 * @param n    index where there might be a violation of
 *             structural property
 */
void upheap(Heap* hp, int n) {
  if (n > 1 && hp->array[n / 2].dist > hp->array[n].dist) {
    swap(&hp->array[n / 2], &hp->array[n]);
    upheap(hp, n / 2);
  }
}

/*
 * @brief Insert new node into heap.
 *
 * @param station  station ID
 * @param dist     distance (time) value
 * @param hp       pointer to heap
 *
 * @pre   hp is a valid heap
 * @post  new element is inserted and structural property is restored
 */
void enqueue(int station, int dist, Heap* hp) {
  if (hp->front == hp->size)
    doubleHeapSize(hp);
  hp->array[hp->front].station = station;
  hp->array[hp->front].dist = dist;
  upheap(hp, hp->front);
  hp->front++;
}

/*
 * @brief Return index of smallest element among node n and its children.
 *
 * @param hp  pointer to heap
 * @param n   index of current node
 *
 * @return index of node with smallest distance (time) value
 */
int bestNode(Heap* hp, int n) {
  int best = n;
  int l = 2 * n;
  int r = l + 1;
  if (hp->front > l && hp->array[l].dist < hp->array[best].dist)
    best = l;
  if (hp->front > r && hp->array[r].dist < hp->array[best].dist)
    best = r;
  return best;
}

/*
 * @brief Restore structural property downwards from index n.
 *
 * @param hp  pointer to heap
 * @param n   index where structural heap property may have been violated
 *
 * @pre   structural property may be violated at n
 * @post  min-heap property is restored
 */
void downheap(Heap* hp, int n) {
  int b = bestNode(hp, n);
  if (b != n) {
    swap(&hp->array[n], &hp->array[b]);
    downheap(hp, b);
  }
}

/*
 * @brief Remove and return minimum element from heap.
 *
 * @param hp pointer to heap
 *
 * @post smallest element of the heap is removed and structural property is
 * restored
 *
 * @return HeapNode with minimum distance (time)
 */
HeapNode removeMin(Heap* hp) {
  if (isEmptyHeap(hp)) {
    emptyHeapError();
  }
  HeapNode min = hp->array[1];
  hp->front--;
  hp->array[1] = hp->array[hp->front];
  downheap(hp, 1);
  return min;
}

/*
 * @brief Free all memory used by the heap.
 *
 * @param hp   pointer to a heap
 *
 * @post  heap memory is released
 */
void freeHeap(Heap* hp) {
  free(hp->array);
  hp->array = NULL;
  hp->front = 1;
  hp->size = 0;
}

// *************************************************
//                  DIJKSTRA'S
// *************************************************
/*
 * @brief Compute shortest paths using Dijkstra's algorithm.
 *
 * Uses a min-heap to select the station with the smallest
 * known distance from the start station.
 *
 * @param graph  railway graph
 * @param n      number of stations
 * @param start  starting station ID
 * @param dist   array with final distances
 * @param prev   array to construct shortest path later
 *
 *
 * @post dist[]  contains shortest distances from the start
 * @post prev[]  allows reconstruction of shortest paths
 */
void dijkstra(Railway graph[], int n, int start, int* dist, int* prev) {
  bool* cloud = calloc(n, sizeof(bool));
  assert(cloud != NULL);

  for (int i = 0; i < n; i++) {
    dist[i] = INF;
    prev[i] = -1;
  }

  Heap toDo = makeHeap(n);

  dist[start] = 0;
  enqueue(start, 0, &toDo);

  while (!isEmptyHeap(&toDo)) {
    HeapNode hn = removeMin(&toDo);
    int u = hn.station;

    if (cloud[u]) {
      continue;
    }

    cloud[u] = true;

    for (Station* p = graph[u]; p != NULL; p = p->next) {
      int v = p->station;
      int w = p->time;

      if (!cloud[v] && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        prev[v] = u;
        enqueue(v, dist[v], &toDo);
      }
    }
  }

  freeHeap(&toDo);
  free(cloud);
}

//*********************************************************
//               ADDITIONAL HELPERS
//*********************************************************

/*
 * @brief Print shortest path and total travel time from start to destination
 *
 * If the destination is unreachable, print "UNREACHABLE".
 * Otherwise, reconstruct shortest path by following
 * predecessor links stored in prev[] starting from
 * destination and moving backwards.
 *
 * @param start   starting station ID
 * @param goal    destination station ID
 *
 * @pre    dijkstra() has been correctly executed with the same start station
 * @post   shortest path is printed one station per line, followed by
 * the total travel time
 */
void printPath(int start, int goal, int* dist, int* prev, char stationNames[][MAX_NAME_LEN]) {
  if (dist[goal] == INF) {
    printf("UNREACHABLE\n");
    return;
  }

  int pathSize = 0;
  int* path = malloc(1024 * sizeof(int));
  assert(path != NULL);

  // Follow predecessor pointers from goal back to start
  for (int v = goal; v != -1; v = prev[v]) {
    path[pathSize++] = v;
  }

  for (int i = pathSize - 1; i >= 0; i--) {
    printf("%s\n", stationNames[path[i]]);
  }

  printf("%d\n", dist[goal]);

  free(path);
}

/*
 * @brief Read a station name from standard input.
 *
 * @param buf    buffer to store station name
 * @param size   buffer size
 *
 * @return true if a line was read, false on EOF
 *
 * @post newline character is removed if present
 */
bool readLine(char buf[], int size) {
  if (fgets(buf, size, stdin) == NULL) {
    return false;
  }

  int i = 0;
  while (buf[i] != '\0') {
    if (buf[i] == '\n') {
      buf[i] = '\0';
      break;
    }
    i++;
  }
  return true;
}

/*
 * @brief Return station ID corresponding to its name.
 *
 * @param stationNames  array containing station names indexed by ID
 * @param n             number of stations
 * @param name          station name to search for
 *
 * @return station ID if found, or -1 if the name does not exist
 */
static int stationIdByName(char stationNames[][MAX_NAME_LEN], int n, const char* name) {
  for (int i = 0; i < n; i++) {
    if (strcmp(stationNames[i], name) == 0)
      return i;
  }
  return -1;
}

//*****************************************************
//                   MAIN SECTION
//*****************************************************

/*
 * @brief Program entry point.
 *
 * Reads multiple railway networks from standard input. For each network,
 * it reads stations, connections, and disruptions, then prints
 * shortest paths until a termination symbol is encountered.
 *
 * @return 0 on successful execution
 */
int main(void) {
  int networks;
  scanf("%d\n", &networks);
  for (int l = 0; l < networks; l++) {
    int stations;
    scanf("%d\n", &stations);
    char stationNames[stations][MAX_NAME_LEN];

    //Read stations
    for (int i = 0; i < stations; i++) {
      int id;
      scanf("%d ", &id);
      readLine(stationNames[id], MAX_NAME_LEN);
    }

    Railway* graph = malloc(stations * sizeof(Railway));
    assert(graph != NULL);
    initEmptyRailway(graph, stations);

    //Read connections
    int connections;
    scanf("%d\n", &connections);

    for (int j = 0; j < connections; j++) {
      int a, b, t;
      scanf("%d %d %d", &a, &b, &t);
      addUndirectedEdge(graph, a, b, t);
    }

    //Read disruptions
    char s1[MAX_NAME_LEN], s2[MAX_NAME_LEN];

    int disruptions;
    scanf("%d", &disruptions);
    readLine(s1, MAX_NAME_LEN);

    for (int k = 0; k < disruptions; k++) {
      readLine(s1, MAX_NAME_LEN);
      readLine(s2, MAX_NAME_LEN);

      int a = stationIdByName(stationNames, stations, s1);
      int b = stationIdByName(stationNames, stations, s2);

      if (a != -1 && b != -1)
        removeConnection(graph, a, b);
    }

    // Dijkstra
    int* dist = malloc(stations * sizeof(int));
    int* prev = malloc(stations * sizeof(int));
    assert(dist != NULL && prev != NULL);
    while (readLine(s1, MAX_NAME_LEN)) {
      if (strcmp(s1, "!") == 0) {
        break;
      }

      readLine(s2, MAX_NAME_LEN);

      int start = stationIdByName(stationNames, stations, s1);
      int goal = stationIdByName(stationNames, stations, s2);

      if (start == -1 || goal == -1) {
        printf("UNREACHABLE\n");
        continue;
      }

      dijkstra(graph, stations, start, dist, prev);
      printPath(start, goal, dist, prev, stationNames);
    }
    free(dist);
    free(prev);
    freeRailway(graph, stations);
    free(graph);
  }
  return 0;
}
