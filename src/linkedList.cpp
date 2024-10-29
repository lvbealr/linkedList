#include <cstdio>
#include <cstdlib>

#include "../include/linkedList.h"
#include "../customWarning/customWarning.h"

linkedListError linkedListInitialize(linkedList *list, size_t capacity) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = (ssize_t)capacity + 1;

  list->root = (linkedListNode *)calloc(1, sizeof(linkedListNode));
  customWarning(list->root != NULL, ROOT_BAD_POINTER);

  list->head = list->root;
  list->tail = list->root;

  list->root->data             = 0;
  list->root->previousListNode = NULL;
  list->root->nextListNode     = NULL;

  size_t nodeIndex = 0;
  linkedListNode *currentNode = list->head;

  while (currentNode && nodeIndex < list->capacity) {
    linkedListNode *nextNode = (linkedListNode *)calloc(1, sizeof(linkedListNode));

    customWarning(nextNode != NULL, NODE_BAD_POINTER);

    nextNode->data             = 0;
    nextNode->previousListNode = currentNode;
    nextNode->nextListNode     = NULL;

    currentNode->nextListNode  = nextNode;

    currentNode = currentNode->nextListNode;
    nodeIndex++;

    list->tail = currentNode;
  }

  return NO_ERRORS;

  // TODO freeNode - what does it do?
}

linkedListError linkedListDestruct(linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = -1;
  list->freeNode = -1;

  // TODO LOTS OF MACRO FOR FREE

  size_t nodeIndex = 0;
  linkedListNode *currentNode = list->head;

  while (currentNode != list->tail) {
    // fprintf(stderr, "\nBEFORE SHIFT: %p\n", currentNode);
    currentNode = currentNode->nextListNode;
    // fprintf(stderr, "NOW: %p\n\t DELETE: %p\n", currentNode, currentNode->previousListNode);
    free(currentNode->previousListNode);
    currentNode->previousListNode = NULL;
  }

  free(currentNode);
  currentNode = NULL;

  list->root = NULL;
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

  return NO_ERRORS;
}

linkedListError linkedListDump      (linkedList *list) {
  printf("\033[1;33mhui hui bolshoi zhirny cherny hui pisya popa hui chlenik\n\033[0m");
  return NO_ERRORS;
}

linkedListError insertNode          (linkedList *node, size_t index, elem_t data) {
  customWarning(node != NULL, NODE_BAD_POINTER);
  // TODO
  return NO_ERRORS;
}

linkedListError deleteNode          (linkedList *node) {
  return NO_ERRORS;
}

linkedListError getNode             (linkedList *node) {
  return NO_ERRORS;
}



