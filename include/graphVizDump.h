#ifndef GRAPH_VIZ_DUMP_H_
#define GRAPH_VIZ_DUMP_H_

#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>

#include "linkedList.h"

const size_t MAX_FILE_NAME_SIZE   =  50;
const size_t MAX_BORN_FUNC_NAME   =  50;
const int    MAX_LINE_LENGTH      =   4;
const size_t MAX_DUMP_FOLDER_NAME =  20;
const size_t MAX_DUMP_FILE_NAME   =  50;
const size_t MAX_PATH_TO_FILE     = 100;
const size_t MAX_CMD_BUFFER_SIZE  = 100;

// FUNCTION PROTOTYPES //
linkedListError linkedListDump (linkedList *list);
char           *setDumpFileName(const char *dumpFolder);
linkedListError writeHtmlHeader(linkedList *list);
// FUNCTION PROTOTYPES //

#endif // GRAPH_VIZ_DUMP_H_