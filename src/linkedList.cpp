#include <cstdio>
#include <cstdlib>

#include "../include/linkedList.h"
#include "../customWarning/customWarning.h"

// TODO VERIFY IN EVERY FUNCTION

linkedListError linkedListInitialize(linkedList *list, size_t capacity) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = (ssize_t)capacity + 1;

  list->data     = (elem_t  *)calloc((size_t)list->capacity, sizeof(elem_t));
  list->prev     = (ssize_t *)calloc((size_t)list->capacity, sizeof(ssize_t));
  list->next     = (ssize_t *)calloc((size_t)list->capacity, sizeof(ssize_t));

  customWarning(list->data != NULL, DATA_BAD_POINTER);
  customWarning(list->prev != NULL, PREVIOUS_BAD_POINTER); // TODO MAYBE RENAME ENUM
  customWarning(list->next != NULL, NEXT_BAD_POINTER);     // TODO MAYBE RENAME ENUM

  list->prev[0] = 0;
  list->next[0] = 0;

  list->freeNode = 1; // В НУЛЕВУЮ ЯЧЕЙКУ НИЧЕГО НЕ КЛАДЕМ, ВСЕ УЗЛЫ СЕЙЧАС СВОБОДНЫ, НАЧИНАЕМ С ПЕРВОГО РАССТАВЛЯТЬ ИНДЕКСЫ

  for (ssize_t nodeIndex = list->freeNode; nodeIndex < list->capacity; nodeIndex++) {
    list->next[nodeIndex] = (nodeIndex + 1) % list->capacity; // КОЛЬЦО
    list->prev[nodeIndex] = -1;
  }

  return NO_ERRORS;
}

linkedListError linkedListDestruct(linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = -1;
  list->freeNode = -1;

  free(list->data);
  free(list->prev);
  free(list->next);

  list->data = NULL;
  list->prev = NULL;
  list->next = NULL;

  // TODO MACRO

  return NO_ERRORS;
}

linkedListError linkedListVerify    (linkedList *list) {
  // TODO do list with errors like in stack instead of custom warnings
  customWarning(list           != NULL,                                LIST_BAD_POINTER    );
  customWarning(list->data     != NULL,                                DATA_BAD_POINTER    );
  customWarning(list->prev     != NULL,                                PREVIOUS_BAD_POINTER);
  customWarning(list->next     != NULL,                                NEXT_BAD_POINTER    );
  customWarning(list->capacity < 0,                                    BAD_CAPACITY        );
  customWarning(list->prev[0]  < 0 || list->prev[0] >= list->capacity, BAD_TAIL            );
  customWarning(list->next[0]  < 0 || list->prev[0] >= list->capacity, BAD_HEAD            );

  // TODO CHECK freeNode?

  // TODO MORE CHECKS

  return NO_ERRORS;
}

linkedListError linkedListDump      (linkedList *list) {
  printf("\033[1;33mhui hui bolshoi zhirny cherny hui pisya popa hui chlenik\n\033[0m");
  return NO_ERRORS;
}

linkedListError insertNode          (linkedList *list, size_t index, elem_t value) {
  customWarning(list != NULL, NODE_BAD_POINTER);
  // TODO CHECK INDEX, CAPACITY

  ssize_t newIndex = list->freeNode;
  list->freeNode   = list->next[list->freeNode];

  list->prev[list->next[index]] = newIndex;
  list->prev[newIndex]          = index;

  list->next[index]             = newIndex;
  list->next[newIndex]          = list->next[index];

  list->data[newIndex] = value;

  return NO_ERRORS;
}

linkedListError deleteNode          (linkedList *list, size_t index) {
  customWarning(list != NULL, LIST_BAD_POINTER);
  // TODO CHECKER

  list->data[index + 1] = POISON_VALUE;

  list->prev[list->next[index]] = list->prev[index];
  list->next[list->prev[index]] = list->next[index];

  list->next[index] = list->freeNode;
  list->prev[index] = -1;
  list->freeNode    = index;


  return NO_ERRORS;
}

linkedListError getNode             (linkedList *list, size_t index) {
  return NO_ERRORS;
}



