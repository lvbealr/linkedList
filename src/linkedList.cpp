#include <cstdio>
#include <cstdlib>
#include <memory.h>

#include "linkedList.h"
#include "customWarning.h"

#define CHECK_ERROR(listPtr, expression, error) { \
  if (!(expression)) {                            \
    (listPtr)->errorCode |= error;                \
    return error;                                 \
  }                                               \
}

static linkedListError fillWithPoison(linkedList *list) {
  customWarning(list                  != NULL, LIST_BAD_POINTER);

  CHECK_ERROR(list, sizeof(list->data[0]) == sizeof(POISON_VALUE), BAD_POISON_SIZE);

  for (size_t index = 0; index < list->capacity; index++) {
    list->data[index] = POISON_VALUE;
  }

  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError linkedListInitialize(linkedList *list, size_t capacity) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = (ssize_t)capacity + 1;

  list->data     = (elem_t  *)calloc((size_t)list->capacity, sizeof(elem_t));
  list->prev     = (ssize_t *)calloc((size_t)list->capacity, sizeof(ssize_t));
  list->next     = (ssize_t *)calloc((size_t)list->capacity, sizeof(ssize_t));

  CHECK_ERROR(list, list->data != NULL,     DATA_BAD_POINTER);
  CHECK_ERROR(list, list->prev != NULL, PREVIOUS_BAD_POINTER);
  CHECK_ERROR(list, list->next != NULL,     NEXT_BAD_POINTER);

  fillWithPoison(list);

  list->prev[0]  = 0;
  list->next[0]  = 0;
  list->freeNode = 1;

  for (ssize_t nodeIndex = list->freeNode; nodeIndex < list->capacity; nodeIndex++) {
    list->next[nodeIndex] = (nodeIndex + 1) % list->capacity;
    list->prev[nodeIndex] = -1;
  }

  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError linkedListDestruct(linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = -1;
  list->freeNode = -1;
  list->errorCode = 0;

  FREE_(list->data);
  FREE_(list->prev);
  FREE_(list->next);

  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError linkedListVerify    (linkedList *list) {
  customWarning(list                  !=                                NULL, LIST_BAD_POINTER    );

  CHECK_ERROR   (list, list->data     !=                                NULL, DATA_BAD_POINTER    );
  CHECK_ERROR   (list, list->prev     !=                                NULL, PREVIOUS_BAD_POINTER);
  CHECK_ERROR   (list, list->next     !=                                NULL, NEXT_BAD_POINTER    );
  CHECK_ERROR   (list, list->capacity >=                                   0, BAD_CAPACITY        );
  CHECK_ERROR   (list, list->next[0]  >= 0 && list->next[0] < list->capacity, BAD_HEAD            );
  CHECK_ERROR   (list, list->prev[0]  >= 0 && list->prev[0] < list->capacity, BAD_TAIL            );

  ssize_t freeIndex = list->freeNode;

  while (freeIndex) {
    if (list->prev[freeIndex] <= 0) {
      list->errorCode |= BAD_FREE_NODE;
      return BAD_FREE_NODE;
    }

    else {
      freeIndex = list->next[freeIndex];
    }
  }

  return NO_ERRORS;
}

linkedListError linkedListDump      (linkedList *list) {
  printf("\033[1;33mhui hui bolshoi zhirny cherny hui pisya popa hui chlenik\n\033[0m");
  return NO_ERRORS;
}

linkedListError insertNode          (linkedList *list, ssize_t index, ssize_t *newIndex, elem_t value) {
  customWarning(list != NULL, NODE_BAD_POINTER);

  CHECK_ERROR(list, index             >=  0 && index < list->capacity,    BAD_INDEX);
  CHECK_ERROR(list, list->prev[index] !=                           -1,    BAD_INDEX);
  CHECK_ERROR(list, list->freeNode    !=                            0, BAD_CAPACITY);

  *newIndex                     = list->freeNode;
  list->freeNode                = list->next[list->freeNode];
  list->data[*newIndex]         = value;
  list->prev[list->next[index]] = *newIndex;
  list->prev[*newIndex]         = index;

  list->next[*newIndex]         = list->next[index];

  list->next[index]             = *newIndex;

  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError deleteNode          (linkedList *list, ssize_t index) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  CHECK_ERROR(list, index > 0 && index < list->capacity, BAD_INDEX);
  CHECK_ERROR(list, list->prev[index] !=             -1, BAD_INDEX);

  list->data[index] = POISON_VALUE;

  list->prev[list->next[index]] = list->prev[index];
  list->next[list->prev[index]] = list->next[index];

  list->next[index] = list->freeNode;
  list->prev[index] = -1;
  list->freeNode    = index;

  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError getNodeValue         (linkedList *list, ssize_t index, elem_t *value) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  CHECK_ERROR  (list, index >= 0 && index < list->capacity,            BAD_INDEX);
  CHECK_ERROR  (list, value !=                        NULL, BAD_GET_NODE_POINTER);

  *value = list->data[index];

  linkedListVerify(list);

  return NO_ERRORS;
}



