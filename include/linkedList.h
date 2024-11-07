#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <cstdlib>
#include <cinttypes>

typedef int elem_t;

const elem_t POISON_VALUE = -666;

#define FREE_(field) { \
    free(field);       \
    field = NULL;      \
  }

struct linkedListInfo {
  char *bornFileName               = {};
  char *bornFunctionName           = {};
  int   bornLine                   = {};
  char *dumpFolderName             = {};
  char *dumpFileName               = {};
  char *lastUsedFileName           = {};
  char *lastUsedFunctionName       = {};
  int   lastUsedLine               = {};
  char *htmlDumpFileName           = {};
};

struct linkedList {
  elem_t         *data             = {};
  ssize_t        *prev             = {};
  ssize_t        *next             = {};
  ssize_t         capacity         = -1;
  ssize_t         freeNode         = -1;
  uint64_t        errorCode        =  0;
  linkedListInfo *infoData         = {};
};

struct svgFile {
  char  *data  = {};
  size_t size  =  0;
};

enum linkedListError {
  NO_ERRORS             =       0,
  LIST_BAD_POINTER      = 1 <<  1,
  PREVIOUS_BAD_POINTER  = 1 <<  2,
  NEXT_BAD_POINTER      = 1 <<  3,
  DATA_BAD_POINTER      = 1 <<  4,
  BAD_CAPACITY          = 1 <<  5,
  BAD_HEAD              = 1 <<  6,
  BAD_TAIL              = 1 <<  7,
  NODE_BAD_POINTER      = 1 <<  8,
  ROOT_BAD_POINTER      = 1 <<  9,
  BAD_POISON_SIZE       = 1 << 10,
  BAD_FREE_NODE         = 1 << 11,
  BAD_INDEX             = 1 << 12,
  BAD_GET_NODE_POINTER  = 1 << 13,
  OPEN_FILE_ERROR       = 1 << 14,
  BAD_FILE_NAME_POINTER = 1 << 15,
  BAD_FUNC_NAME_POINTER = 1 << 16,
  INFO_NULL_POINTER     = 1 << 17,
  BAD_BORN_LINE_VALUE   = 1 << 18,
  DUMP_FILE_BAD_POINTER = 1 << 19,
  BAD_BUFFER_POINTER    = 1 << 20
};

// FUNCTION PROTOTYPES //
linkedListError linkedListInitialize    (linkedList *list, size_t capacity                                              );
linkedListError linkedListInfoInitialize(linkedList *list, const char *fileName, const char *functionPrototype, int line);
linkedListError linkedListDestruct      (linkedList *list                                                               );
linkedListError linkedListInfoDestruct  (linkedList *list                                                               );
linkedListError linkedListVerify        (linkedList *list                                                               );
linkedListError insertNode              (linkedList *list, ssize_t index,  ssize_t *newIndex, elem_t data               );
linkedListError deleteNode              (linkedList *list, ssize_t index                                                );
linkedListError getNodeValue            (linkedList *list, ssize_t index,  elem_t *value                                );
// FUNCTION PROTOTYPES //

#endif // LINKED_LIST_H_