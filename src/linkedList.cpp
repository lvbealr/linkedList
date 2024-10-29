#include <cstdio>
#include <cstdlib>

#include "linkedList.h"
#include "customWarning/customWarning.h"

linkedListError linkedListInitialize(linkedList *list, size_t capacity) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = (ssize_t)capacity + 1;

  list->head     = (linkedListNode *)calloc(1, sizeof(linkedListNode));
  list->tail     = (linkedListNode *)calloc(1, sizeof(linkedListNode));

  customWarning(list->head != NULL, BAD_HEAD);
  customWarning(list->tail != NULL, BAD_TAIL);

  // TODO MACRO INITIALIZE BEGIN AND END NODE'S (OR FUNCTIONS, IMHO MACRO BETTER)
  list->head->data             = 0;
  list->head->previousListNode = list->tail;
  list->head->nextListNode     = list->tail;

  list->tail->data             = 0;
  list->tail->previousListNode = list->head;
  list->tail->nextListNode     = list->head;

  return NO_ERRORS;

  // TODO freeNode - what does it do?
}

linkedListError linkedListDestruct  (linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = -1;
  list->freeNode = -1;

  // TODO LOTS OF MACRO FOR FREE

  free(list->head->previousListNode);
  free(list->head->nextListNode);

  list->head->previousListNode = NULL;
  list->head->nextListNode     = NULL;

  free(list->tail->previousListNode);
  free(list->tail->nextListNode);

  list->tail->previousListNode = NULL;
  list->tail->nextListNode     = NULL;

  free(list->head);
  free(list->tail);

  list->head = NULL;
  list->tail = NULL;

  return NO_ERRORS;
}

linkedListError linkedListVerify    (linkedList *list) {
  // TODO do list with errors like in stack instead of custom warnings
  customWarning(list           != NULL, LIST_BAD_POINTER);
  customWarning(list->head     != NULL, BAD_HEAD);
  customWarning(list->tail     != NULL, BAD_TAIL);
  customWarning(list->capacity < 0,     BAD_CAPACITY);

  // TODO MACRO OR FUNCTION TO BYPASS ALL NODES
  linkedListNode *currentNode = list->head;

  while (currentNode) {
    customWarning(currentNode->data             != POISON_VALUE, DATA_BAD_VALUE);
    customWarning(currentNode->previousListNode != NULL,         PREVIOUS_BAD_POINTER);
    customWarning(currentNode->nextListNode     != NULL,         NEXT_BAD_POINTER);

    currentNode = currentNode->nextListNode;
  }

  // TODO MORE CHECKS
}

linkedListError linkedListDump      (linkedList *list) {
  printf("\033[1;33mhui hui bolshoi zhirny cherny hui pisya popa hui chlenik\n\033[0m");
}

linkedListError insertNode          (linkedList *node, size_t index, elem_t data) {
  customWarning(node != NULL, NODE_BAD_POINTER);
  // TODO
}

linkedListError deleteNode          (linkedList *node) {}

linkedListError getNode             (linkedList *node) {}



