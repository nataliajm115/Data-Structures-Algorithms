/**
 * @file trains.c
 * @brief Railway routing system using Dijkstra's algorithm.
 *
 * This program simulates a GPS system in the Netherlands, creating an
 * undirected graph that represents the railway system with weights representing
 * the time needed to get from one station (node) to the other. It takes
 * disruptions in the network and the start and end of the desired journey as
 * input. Then it outputs the shortest route the user should take as well as the
 * minutes it will take for the user to get there. The program achieves this by
 * using Dijkstra's algorithm and a min-heap.
 *
 * Input format:
 * 	- Number of disruptions
 * 	- Disrupted connection (pair of stations)
 * 	- Pairs of station names of routing queries
 * 	- ! terminating the input
 *
 * Due Date: 22/12/2025
 * Course: Data Structures and Algorithms
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 12
#define INF 1000000000

// ********************************************************
//                 GRAPH CONSTRUCTION
// ********************************************************

/**
 * @struct Station
 * @brief Node in adjacency list representing a railway connection.
 *
 * @var station		station ID
 * @var time		travel time
 * @var next		pointer to next edge in adjacency list
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
 * @brief Mapping from station ID (int) to station name (string).
 */
const char* stationNames[N] = {"Amsterdam", "Den Haag", "Den Helder",
                               "Eindhoven", "Enschede", "Groningen",
                               "Leeuwarden", "Maastricht", "Meppel",
                               "Nijmegen", "Utrecht", "Zwolle"};

/*
 * @brief Convert station name to station ID
 *
 * @param name	station name
 *
 * @return station ID if found, -1 otherwise
 */
int stationId(const char* name) {
  for (int i = 0; i < N; i++) {
    if (strcmp(name, stationNames[i]) == 0) {
      return i;
    }
  }
  return -1;
}

/*
 * @brief Initialize empty railway graph.
 *
 * @param graph    railway graph
 *
 * @pre   graph is allocated with size N
 * @post  all adjacency lists are NULL
 */
void initEmptyRailway(Railway graph[]) {
  for (int i = 0; i < N; i++) {
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
 * @brief Build complete railway network
 *
 * @post graph contains all predefined bidirectional connections
 */
void buildRailway(Railway graph[]) {
  initEmptyRailway(graph);

  addUndirectedEdge(graph, stationId("Amsterdam"), stationId("Den Haag"), 46);

  addUndirectedEdge(graph, stationId("Amsterdam"), stationId("Den Helder"), 77);

  addUndirectedEdge(graph, stationId("Amsterdam"), stationId("Utrecht"), 26);

  addUndirectedEdge(graph, stationId("Den Haag"), stationId("Eindhoven"), 89);

  addUndirectedEdge(graph, stationId("Eindhoven"), stationId("Maastricht"), 63);

  addUndirectedEdge(graph, stationId("Eindhoven"), stationId("Nijmegen"), 55);

  addUndirectedEdge(graph, stationId("Eindhoven"), stationId("Utrecht"), 47);

  addUndirectedEdge(graph, stationId("Enschede"), stationId("Zwolle"), 50);

  addUndirectedEdge(graph, stationId("Groningen"), stationId("Leeuwarden"), 34);

  addUndirectedEdge(graph, stationId("Groningen"), stationId("Meppel"), 49);

  addUndirectedEdge(graph, stationId("Leeuwarden"), stationId("Meppel"), 40);

  addUndirectedEdge(graph, stationId("Maastricht"), stationId("Nijmegen"), 111);

  addUndirectedEdge(graph, stationId("Meppel"), stationId("Zwolle"), 15);

  addUndirectedEdge(graph, stationId("Nijmegen"), stationId("Zwolle"), 77);

  addUndirectedEdge(graph, stationId("Utrecht"), stationId("Zwolle"), 51);
}

/*
 * @brief Remove directed edge.
 *
 * @param graph  railway graph
 * @param from   starting station
 * @param to 	 destination station
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
 */
void freeRailway(Railway graph[]) {
  for (int i = 0; i < N; i++) {
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
 * @post An empty heap is created with initial capacity N+1.
 */
Heap makeHeap(void) {
  Heap h;
  // Initial capacity avoids unnecessary resizings
  h.size = N + 1;
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
 * @param hp	pointer to a heap
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
// Array initializations for dijkstra's
// Final distances in time for each station from the start
int dist[N];

// Predecessor of each station on the shortest path
int prev[N];

// True if distance in dist array is final (useful for Dijkstra's algorithm)
bool cloud[N];

/*
 * @brief Compute shortest paths using Dijkstra's algorithm.
 *
 * Uses a min-heap to select the station with the smallest
 * known distance from the start station.
 *
 * @param graph  railway graph
 * @param start  starting station ID
 *
 * @post dist[]  contains shortest distances from the start
 * @post prev[]  allows reconstruction of shortest paths
 */
void dijkstra(Railway graph[], int start) {
  for (int i = 0; i < N; i++) {
    dist[i] = INF;
    prev[i] = -1;
    cloud[i] = false;
  }

  Heap toDo = makeHeap();

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
}

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
void printPath(int start, int goal) {
  if (dist[goal] == INF) {
    printf("UNREACHABLE\n");
    return;
  }

  int path[N];
  int len = 0;

  // Follow predecessor pointers from goal back to start
  for (int v = goal; v != -1; v = prev[v]) {
    path[len++] = v;
  }

  for (int i = len - 1; i >= 0; i--) {
    printf("%s\n", stationNames[path[i]]);
  }

  printf("%d\n", dist[goal]);
}

// *************************************************
//                   MAIN SECTION
// *************************************************
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
bool readStation(char buf[], int size) {
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
 * @brief Main: builds railway network, handles disruptions,
 * 		and answers shortest route queries.
 *
 * The program constructs the full railway graph, then removes disrupted
 * connections from the network. Afterwards, it reads routing queries
 * and finds the shortest path between pairs of stations using
 * Dijkstra's algorithm.
 *
 * @pre   Input follows format
 * @post  For each query, either shortest path is printed with its total travel
 * time, or "UNREACHABLE" if no path exists.
 *
 * @returns 0 on successful execution
 */
int main(void) {
  Railway graph[N];
  // Initialize full railway network
  buildRailway(graph);

  int disruptions;
  // Number of disrupted connections
  scanf("%d\n", &disruptions);

  char station1[64];
  char station2[64];

  // Remove disrupted connections
  for (int i = 0; i < disruptions; i++) {
    readStation(station1, 64);
    readStation(station2, 64);

    int st1 = stationId(station1);
    int st2 = stationId(station2);

    if (st1 != -1 && st2 != -1) {
      removeConnection(graph, st1, st2);
    }
  }

  // Process routing queries until '!' is read
  while (readStation(station1, 64)) {
    if (strcmp(station1, "!") == 0) {
      break;
    }

    readStation(station2, 64);

    int start = stationId(station1);
    int end = stationId(station2);

    // Invalid station names imply no valid route
    if (start == -1 || end == -1) {
      printf("UNREACHABLE\n");
      continue;
    }

    // Compute shortest distances from start
    dijkstra(graph, start);

    // Print route and total travel time
    printPath(start, end);
  }
  // Release all allocated memory
  freeRailway(graph);

  return 0;
}
