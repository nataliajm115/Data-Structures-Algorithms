#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/LibQueue.h"
#include "libs/LibStack.h"

// some global constants
const int maxHangar = 5;
const int maxRunway = 7;

/*
 * @brief Frees runway by giving takeoff signal
 *
 * @param count Pointer to the number of planes in the runway
 * @param q Runway queue
 */
void freeRunway(int* count, Queue q) {
  if (!isEmptyQueue(q)) {
    printf("Ready for takeoff!\n");
    while (!isEmptyQueue(q)) {
      printf("%d\n", dequeue(q));
    }
    *count = 0;
  }
}

/*
 * @brief Frees Hangar by moving all planes to the waiting runway
 *
 * @param stackCount Pointer to the number of planes in the hangar
 * @param queueCount Pointer to the number of planes in the waiting runway
 * @param s Hangar stack
 * @param q Runway queue
 */
void freeHangar(int* stackCount, int* queueCount, Stack s, Queue q) {
  while (!isEmptyStack(s)) {
    enqueue(pop(s), q);
    (*stackCount)--;
    (*queueCount)++;
  }
}

/*
 * @brief Main simulation for airport management
 *
 * Reads input planes, decides whether they go to the hangar
 * or runway, handles capacity of both, and runs end-of-day cleanup
 */
int main(void) {
  int n;  // number of planes to read
  int id;
  char repair[6];  // string to store user input

  // airport structures
  Stack hangar = newStack();
  int hangarCount = 0;  // planes in the hangar
  Queue waitingRunway = newQueue();
  int runwayCount = 0;  // planes in the waiting runway

  scanf("%d", &n);  // input: number of planes for the day

  for (int i = 0; i < n; i++) {
    scanf("%d %5s", &id, repair);
    // If plane needs repair, place it in the hangar
    if (repair[0] == 'y') {
      if (hangarCount == maxHangar) {
        freeRunway(&runwayCount, waitingRunway);
        freeHangar(&hangarCount, &runwayCount, hangar, waitingRunway);
      }
      push(id, hangar);
      hangarCount++;
      if (hangarCount == maxHangar) {
        freeRunway(&runwayCount, waitingRunway);
        freeHangar(&hangarCount, &runwayCount, hangar, waitingRunway);
      }
    }
    // Otherwise, place it in the waiting runway
    else if (repair[0] == 'n') {
      if (runwayCount == maxRunway) {
        freeRunway(&runwayCount, waitingRunway);
      }
      enqueue(id, waitingRunway);
      runwayCount++;
      if (runwayCount == maxRunway) {
        freeRunway(&runwayCount, waitingRunway);
      }
    }
  }

  // End of the day
  freeRunway(&runwayCount, waitingRunway);
  freeHangar(&hangarCount, &runwayCount, hangar, waitingRunway);
  freeStack(hangar);
  freeRunway(&runwayCount, waitingRunway);
  freeQueue(waitingRunway);
  return 0;
}
