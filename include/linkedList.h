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
  NO_SUCH_FILE                  = -1,
  NO_ERRORS                     =  0,
  LIST_BAD_POINTER              =  1,
  PREVIOUS_BAD_POINTER          =  2,
  NEXT_BAD_POINTER              =  3,
  DATA_BAD_POINTER              =  4,
  BAD_CAPACITY                  =  5,
  BAD_HEAD                      =  6,
  BAD_TAIL                      =  7,
  NODE_BAD_POINTER              =  8,
  ROOT_BAD_POINTER              =  9,
  BAD_POISON_SIZE               = 10,
  BAD_FREE_NODE                 = 11,
  BAD_INDEX                     = 12,
  BAD_GET_NODE_POINTER          = 13,
  OPEN_FILE_ERROR               = 14,
  BAD_FILE_NAME_POINTER         = 15,
  BAD_FUNC_NAME_POINTER         = 16,
  INFO_NULL_POINTER             = 17,
  BAD_BORN_LINE_VALUE           = 18,
  DUMP_FILE_BAD_POINTER         = 19,
  BAD_BUFFER_POINTER            = 20,
  BAD_PATH_TO_DUMP_FILE_POINTER = 21,
  BAD_DUMP_TEXT_POINTER         = 22,
  BAD_READ_DUMP_FILE            = 23,
  BAD_WRITE_DUMP_FILE           = 24
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