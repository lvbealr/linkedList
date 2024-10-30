#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <cstdlib>

typedef int elem_t;

const elem_t POISON_VALUE = -666;

#define FREE_(field) { \
    free(field);       \
    field = NULL;      \
  }

struct linkedList {
  elem_t         *data             = {};
  ssize_t        *prev             = {};
  ssize_t        *next             = {};
  ssize_t         capacity         = -1;
  ssize_t         freeNode         = -1;
};

// TODO ENUM

enum linkedListError {
  NO_ERRORS            = 0,
  LIST_BAD_POINTER     = 1,
  PREVIOUS_BAD_POINTER = 2,
  NEXT_BAD_POINTER     = 3,
  DATA_BAD_POINTER     = 4,
  BAD_CAPACITY         = 5,
  BAD_HEAD             = 6,
  BAD_TAIL             = 7,
  NODE_BAD_POINTER     = 8,
  ROOT_BAD_POINTER     = 9
};

// FUNCTION PROTOTYPES //
linkedListError linkedListInitialize(linkedList     *list, size_t capacity                              );
linkedListError linkedListDestruct  (linkedList     *list                                               );
linkedListError linkedListVerify    (linkedList     *list                                               );
linkedListError linkedListDump      (linkedList     *list                                               );
linkedListError insertNode          (linkedList     *list, ssize_t index, ssize_t *newIndex, elem_t data);
linkedListError deleteNode          (linkedList     *list, ssize_t index                                );
// linkedListError getNode             (linkedList     *list                              );
// FUNCTION PROTOTYPES //

#endif // LINKED_LIST_H_