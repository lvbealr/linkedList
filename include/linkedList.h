#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <cstdlib>

typedef int elem_t;

const elem_t POISON_VALUE = -666;

struct linkedListNode {
  elem_t          data             = {};
  linkedListNode *previousListNode = {};
  linkedListNode *nextListNode     = {};
};

struct linkedList {
  linkedListNode *root             = {};
  linkedListNode *head             = {};
  linkedListNode *tail             = {};
  ssize_t         capacity         = -1;
  ssize_t         freeNode         = -1;
};

enum linkedListError {
  NO_ERRORS            = 0,
  LIST_BAD_POINTER     = 1,
  PREVIOUS_BAD_POINTER = 2,
  NEXT_BAD_POINTER     = 3,
  DATA_BAD_VALUE       = 4,
  BAD_CAPACITY         = 5,
  BAD_HEAD             = 6,
  BAD_TAIL             = 7,
  NODE_BAD_POINTER     = 8,
  ROOT_BAD_POINTER     = 9
};

// FUNCTION PROTOTYPES //
linkedListError linkedListInitialize(linkedList     *list, size_t  capacity            );
linkedListError linkedListDestruct  (linkedList     *list                              );
linkedListError linkedListVerify    (linkedList     *list                              );
linkedListError linkedListDump      (linkedList     *list                              );
linkedListError insertNode          (linkedListNode *node, elem_t data                 );
linkedListError deleteNode          (linkedListNode *node                              );
linkedListError getNode             (linkedListNode *node                              );
// FUNCTION PROTOTYPES //

#endif // LINKED_LIST_H_