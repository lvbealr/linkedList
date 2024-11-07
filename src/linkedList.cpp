#include <cstdio>
#include <cstdlib>
#include <memory.h>

#include "linkedList.h"
#include "customWarning.h"
#include "graphVizDump.h"

#define CHECK_ERROR(listPtr, expression, error) { \
  if (!(expression)) {                            \
    (listPtr)->errorCode |= error;                \
    return error;                                 \
  }                                               \
}

#define DELETE_TEMP_FILE(listPtr) {                                                                      \
  char *buffer = (char *)calloc(2 * MAX_CMD_BUFFER_SIZE, sizeof(char));                                  \
  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "rm -rf %s.svg & rm -rf %s", (listPtr)->infoData->dumpFileName,  \
                                                                     (listPtr)->infoData->dumpFileName); \
  system(buffer);                                                                                        \
  FREE_ (buffer);                                                                                        \
}

#define DUMP_(listPtr) { \
  (listPtr)->infoData->lastUsedFileName     = (char *)__FILE__;            \
  (listPtr)->infoData->lastUsedFunctionName = (char *)__PRETTY_FUNCTION__; \
  (listPtr)->infoData->lastUsedLine         =         __LINE__;            \
  linkedListDump(listPtr);                                                 \
}

#define saveDumpImage(listPtr) { \
  char *buffer = (char *)calloc(MAX_CMD_BUFFER_SIZE, sizeof(char));     \
  customWarning(buffer != NULL, BAD_BUFFER_POINTER);                    \
                                                                        \
  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "dot -Tsvg %s -o %s.svg",       \
           list->infoData->dumpFileName, list->infoData->dumpFileName); \
  system(buffer);                                                       \
                                                                        \
  FREE_(buffer);                                                        \
}

static linkedListError fillWithPoison(linkedList *list) {
  customWarning(list                  != NULL, LIST_BAD_POINTER);

  CHECK_ERROR(list, sizeof(list->data[0]) == sizeof(POISON_VALUE), BAD_POISON_SIZE);

  for (size_t index = 0; index < list->capacity; index++) {
    list->data[index] = POISON_VALUE;
  }

  // DUMP_(list); // ! подумтаь куда перенести пойзоновку либо не делать дамп здесь
  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError linkedListInitialize(linkedList *list, size_t capacity) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = (ssize_t)capacity + 1;

  list->data     = (elem_t  *)calloc((size_t)list->capacity, sizeof(elem_t));
  list->prev     = (ssize_t *)calloc((size_t)list->capacity, sizeof(ssize_t));
  list->next     = (ssize_t *)calloc((size_t)list->capacity, sizeof(ssize_t));

  list->infoData = (linkedListInfo *)calloc(1, sizeof(linkedListInfo));

  CHECK_ERROR(list, list->data != NULL,     DATA_BAD_POINTER);
  CHECK_ERROR(list, list->prev != NULL, PREVIOUS_BAD_POINTER);
  CHECK_ERROR(list, list->next != NULL,     NEXT_BAD_POINTER);

  list->prev[0]  = 0;
  list->next[0]  = 0;
  list->freeNode = 1;

  for (ssize_t nodeIndex = list->freeNode; nodeIndex < list->capacity; nodeIndex++) {
    list->next[nodeIndex] = (nodeIndex + 1) % list->capacity;
    list->prev[nodeIndex] = -1;
  }

  fillWithPoison(list);
  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError linkedListInfoInitialize(linkedList *list, const char *fileName, const char *functionPrototype, int line) {
  customWarning(list              != NULL, LIST_BAD_POINTER);
  customWarning(fileName          != NULL, BAD_FILE_NAME_POINTER);
  customWarning(functionPrototype != NULL, BAD_FUNC_NAME_POINTER);
  customWarning(line               >    0, BAD_BORN_LINE_VALUE);

  list->infoData->bornFileName         = (char *)calloc(MAX_BORN_FILE_NAME,   sizeof(char));
  list->infoData->bornFunctionName     = (char *)calloc(MAX_BORN_FUNC_NAME,   sizeof(char));
  list->infoData->bornLine             = line;
  list->infoData->dumpFolderName       = (char *)calloc(MAX_DUMP_FOLDER_NAME, sizeof(char));
  list->infoData->dumpFileName         = (char *)calloc(MAX_DUMP_FILE_NAME,   sizeof(char));
  list->infoData->lastUsedFileName     = (char *)calloc(MAX_BORN_FILE_NAME,   sizeof(char)); // TODO RENAME COMMON CONSTANT
  list->infoData->lastUsedFunctionName = (char *)calloc(MAX_BORN_FUNC_NAME,   sizeof(char)); // TODO
  list->infoData->lastUsedLine         = line;
  list->infoData->htmlDumpFileName     = (char *)calloc(MAX_DUMP_FILE_NAME,   sizeof(char));

  CHECK_ERROR(list, list->infoData->bornFileName         != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(list, list->infoData->bornFunctionName     != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(list, list->infoData->dumpFolderName       != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(list, list->infoData->dumpFileName         != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(list, list->infoData->lastUsedFileName     != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(list, list->infoData->lastUsedFunctionName != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(list, list->infoData->htmlDumpFileName     != NULL, INFO_NULL_POINTER);

  strncpy(list->infoData->bornFileName,     fileName,          MAX_BORN_FILE_NAME);
  strncpy(list->infoData->bornFunctionName, functionPrototype, MAX_BORN_FUNC_NAME);

  const char *dumpFolderName = "graphVizDumps"; // TODO by console i think, check makefile!!!
  strncpy(list->infoData->dumpFolderName, dumpFolderName, MAX_DUMP_FOLDER_NAME);

  const char *dumpFileName   = setDumpFileName(list->infoData->dumpFolderName);
  strncpy(list->infoData->dumpFileName,   dumpFileName, MAX_DUMP_FILE_NAME);

  DUMP_(list);            // !
  DELETE_TEMP_FILE(list); // !

  return NO_ERRORS;
}

linkedListError linkedListDestruct(linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  DUMP_(list);         // !
  saveDumpImage(list); // !

  list->capacity  = -1;
  list->freeNode  = -1;
  list->errorCode =  0;

  FREE_(list->data);
  FREE_(list->prev);
  FREE_(list->next);

  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError linkedListInfoDestruct(linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  FREE_(list->infoData->bornFileName    );
  FREE_(list->infoData->bornFunctionName);
  FREE_(list->infoData->dumpFileName    );
  FREE_(list->infoData->dumpFolderName  );

  list->infoData->bornLine = 0;

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

  DUMP_(list);            // !
  DELETE_TEMP_FILE(list); // !

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

  DUMP_(list);            // !
  DELETE_TEMP_FILE(list); // !

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

  DUMP_(list);            // !
  DELETE_TEMP_FILE(list); // !

  linkedListVerify(list);

  return NO_ERRORS;
}

linkedListError getNodeValue         (linkedList *list, ssize_t index, elem_t *value) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  CHECK_ERROR  (list, index >= 0 && index < list->capacity,            BAD_INDEX);
  CHECK_ERROR  (list, value !=                        NULL, BAD_GET_NODE_POINTER);

  *value = list->data[index];

  DUMP_(list);            // !
  DELETE_TEMP_FILE(list); // !

  linkedListVerify(list);

  return NO_ERRORS;
}
