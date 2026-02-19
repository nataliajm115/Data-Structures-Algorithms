/**
 * @file doctor2.c
 * @brief Simulates a hospital's waiting room using a priority linked list.
 *
 * This program allows adding, treating, and listing patients in the waiting room,
 * ordered by priority. The implementation uses
 * linked list operations to maintain the waiting room.
 *
 * Date: 30/10/2025
 * Course: Data Structures and Algorithms (Lab 2)
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************
 *                     LINKED LIST LIBRARY
 *  Contains all functions related to the Patient structure:
 *  creating the waiting room, adding new patients, treating them, listing them, and freeing memory.
 ************************************************************/

typedef struct Patient {
  char name[201];        // patient's name (string)
  int age;               // patient's age
  int priority;          // patient's priority number
  struct Patient* next;  // pointer to the next patient in the list
} Patient;

/**
 * @brief Creates and returns a new empty waiting room.
 *
 * @pre   None.
 * @post  Returns a NULL pointer representing an empty waiting room.
 *
 * @return NULL pointer.
 */
Patient* newEmptyPatient(void) {
  return NULL;
}

/**
 * @brief  Checks whether the waiting room is empty or not.
 *
 * @pre    The input parameter may point to NULL or to a valid Patient node.
 * @post   Does not modify the list.
 *
 * @param  p Pointer to the head of the waiting room.
 * @return 1 if list is empty, 0 otherwise.
 */
int isEmpty(Patient* p) {
  return (p == NULL);
}

/**
 * @brief  Prints an error message when the waiting room is empty.
 *
 * @pre    Only called when the patient list is known to be empty.
 * @post   Prints error message and returns NULL.
 *
 * @return NULL pointer.
 */
Patient* listEmptyError(void) {
  printf("No patients to treat!\n");
  return NULL;
}

/**
 * @brief  Allocates and initializes a new Patient structure.
 *
 * @pre    'name' should be a valid string.
 * 	   'age' and 'priority' should be a valid integers.
 * @post   Returns pointer to new patient object with all its fields.
 *
 * @param  name		Patient's name.
 * @param  age		Patient's age.
 * @param  priority	Patient's priority level.
 * @return Pointer to the new patient.
 */
Patient* newPatient(char name[], int age, int priority) {
  Patient* new = malloc(sizeof(Patient));
  assert(new != NULL);
  strcpy(new->name, name);
  new->age = age;
  new->priority = priority;
  new->next = NULL;
  return new;
}

/**
 * @brief  Iterates trhough the waiting room to find patient's
 * position according to its priority.
 *
 * @pre    'head' may point to NULL or point to a valid patient.
 *         'name' should be a valid string.
 *         'age' and 'priority' should be valid integers
 * @post   Returns new head pointer to the newly updated list.
 *
 * @param  head		Pointer to the first patient.
 * @param  name 	Patient's name.
 * @param  age 		Patient's age.
 * @param  priority 	Patient's priority.
 * @return Pointer to the head of the updated waiting room.
 */
Patient* insertInOrder(Patient* head, char name[], int age, int priority, int* counter) {
  Patient* new = newPatient(name, age, priority);

  // Case 1: empty list or new patient has highest priority
  if (isEmpty(head) || priority > head->priority) {
    new->next = head;
    (*counter)++;
    return new;
  }

  // Case 2: find correct position
  Patient* current = head;
  while (current->next != NULL && current->next->priority >= priority) {
    // Use >= to give higher priority to patients that arrived earlier
    current = current->next;
  }

  // Insert patient in the right position
  new->next = current->next;
  current->next = new;
  (*counter)++;
  return head;
}

/**
 * @brief Removes first patient of the waiting room if not empty.
 *
 * @pre   'head' may be NULL or point to a valid patient.
 * @post  First patient is freed and the head pointer moves to the next patient.
 *
 * @param  head		Pointer to the first patient.
 * @return Pointer to the head of the new waiting room.
 */
Patient* removeFirstPatient(Patient* head) {
  if (isEmpty(head)) {
    listEmptyError();
  }
  Patient* next = head->next;
  free(head);
  return next;
}

/**
 * @brief  Treats a patient by printing their details and freeing
 * it (by highest priority).
 *
 * @pre    'head' may be NULL or point to a valid patient.
 * @post   Prints and frees the first patient when waiting room is not empty.
 *
 * @param  head		Pointer to the first patient.
 * @return Pointer to the head of the new waiting room.
 */
Patient* treatPatient(Patient* head, int* counter) {
  if (isEmpty(head)) {
    listEmptyError();
  }
  printf("Treating the patient %s (age: %d, priority: %d).\n", head->name, head->age, head->priority);
  head = removeFirstPatient(head);
  (*counter)--;
  return head;
}

/**
 * @brief  Recursively lists all patients in the waiting room by priority.
 *
 * @pre    'head' may be NULL or point to a valid patient.
 * @post   Prints one line per patient without destructing the list.
 *
 * @param  head		Pointer to the first patient.
 */
void listAllPatients(Patient* head) {
  if (isEmpty(head)) {
    return;
  }
  printf("%s (age: %d, priority: %d)\n", head->name, head->age, head->priority);
  listAllPatients(head->next);
}

/**
 * @brief  Frees all patients in the waiting room.
 *
 * @pre    'head' may be NULL or point to a valid patient.
 * @post   All allocated memory for the waiting room is released.
 *
 * @param  head		Pointer to the first patient.
 */
void freeAll(Patient* head) {
  while (!isEmpty(head)) {
    Patient* temp = head;
    head = head->next;
    free(temp);
  }
}

/************************************************************
 *                     MAIN PROGRAM
 *  Implements the waiting room interface to manage patients.
 *  Handles user input and uses the linked list library above.
 ************************************************************/

int main(void) {
  // Initialization:
  // Program manages a waiting room of patients in a hospital,
  // ordered by priority (highest to lowest).
  // Starts with an empty list and a patient counter.
  Patient* waitingRoom = newEmptyPatient();
  int count = 0;
  char command;

  // Main loop.
  while (1) {
    // Display the number of patients that are currently in
    // the waiting room.
    printf("Currently there are %d patients in the queue.\n", count);

    // Shows the user the available options.
    if (count == 0) {
      printf("What do you want to do? [N]ew patient, [Q]uit:\n");
    } else {
      printf("What do you want to do? [N]ew patient, [T]reat patient, [L]ist, [Q]uit:\n");
    }

    // Read user command skipping whitespaces and newline characters.
    scanf(" %c", &command);

    // Option: add new patient.
    if (command == 'N') {
      char name[201];
      int age, priority;

      printf("What is the name of the patient?\n");
      scanf(" %200[^\n]", name);
      printf("What is the age of the patient?\n");
      scanf("%d", &age);
      printf("What is the priority of the patient?\n");
      scanf("%d", &priority);

      waitingRoom = insertInOrder(waitingRoom, name, age, priority, &count);
    }

    // Option: treat patient.
    else if (command == 'T') {
      waitingRoom = treatPatient(waitingRoom, &count);
    }

    // Option: list all patients by priority.
    else if (command == 'L') {
      listAllPatients(waitingRoom);
    }

    // Option: quit program.
    else if (command == 'Q') {
      printf("Goodbye!\n");
      break;
    }
  }

  // Cleanup: free the waiting room from memory.
  freeAll(waitingRoom);
  return 0;
}
