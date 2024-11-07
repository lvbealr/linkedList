#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include "graphVizDump.h"
#include "customWarning.h"

static const size_t MAX_HEADER_SIZE     = 500;

char *setDumpFileName(const char *dumpFolder) {
  const time_t currentTime = time(NULL);
  tm localTime = *localtime(&currentTime);

  char *fileName = (char *)calloc(MAX_FILE_NAME_SIZE, sizeof(char));

  customWarning(fileName != NULL, NULL);

  snprintf(fileName, FILENAME_MAX, "%s/%.2d.%.2d.%.4d-%.2d:%.2d:%.2d",
                                    dumpFolder, localTime.tm_mday, localTime.tm_mon,
                                    localTime.tm_year + 1900, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

  return fileName;
}

linkedListError linkedListDump(linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  char *dumpFileName = setDumpFileName(list->infoData->dumpFolderName);
  strncpy(list->infoData->dumpFileName,   dumpFileName, MAX_DUMP_FILE_NAME);
  strcat(list->infoData->dumpFileName,    ".dot");

  FILE *dumpFile = fopen(list->infoData->dumpFileName, "w");
  customWarning(dumpFile != NULL, DUMP_FILE_BAD_POINTER);

  // .DOT HEADER /////////////////////////////////////////////////////////////////////////////////
  fprintf(dumpFile, "digraph linkedList{\nsplines=ortho;\nrankdir=HR;\nnodesep=0.4;"
                    "\nnode [shape=record, fontname=\"JetBrains Mono\", fontsize=\"10\"];\n"
                    "edge [style=bold, color=\"#00BFFF:black;0.001\", weight=10, penwidth=2, "
                    "arrowsize=0.4];\n");
  ////////////////////////////////////////////////////////////////////////////////////////////////

  // HEAD ////////////////////////////////////////////////////////////////////////////////////////
  fprintf(dumpFile, "0 ");
  fprintf(dumpFile, "[style = \"filled, rounded\", fillcolor=\"#FDF4E3\", label=\" "
                    "{index = %d | data = %d | next = %d | prev = %d}\" ];\n", 0, list->data[0], list->next[0], list->prev[0]);
  ////////////////////////////////////////////////////////////////////////////////////////////////

  // ALL NODES ///////////////////////////////////////////////////////////////////////////////////
  for (size_t index = 1; index < list->capacity; index++) {
    fprintf(dumpFile, "%d ", index);
    fprintf(dumpFile, "[style = \"filled, rounded\", fillcolor=\"#CC99FE\", label=\" "
                      "{index = %d | data = %d | next = %d | prev = %d}\" ];\n",
                      index, list->data[index], list->next[index], list->prev[index]);
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////

  // LAST FREE ///////////////////////////////////////////////////////////////////////////////////
  fprintf(dumpFile, "free [style = \"filled, rounded\", fillcolor=\"#FFC0CB\", label=\"free = %d\" ];\n", list->freeNode);
  ////////////////////////////////////////////////////////////////////////////////////////////////

  // FREE NODES //////////////////////////////////////////////////////////////////////////////////
  ssize_t freeIndex = list->freeNode;

  while (freeIndex != 0) {
    fprintf(dumpFile, "%d ", freeIndex);
    fprintf(dumpFile, "[style = \"filled, rounded\", fillcolor=\"#808080\"];\n");

    freeIndex = list->next[freeIndex];
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////
  fprintf(dumpFile, "{ rank = same; ");
  for (size_t index = 0; index < list->capacity; index++) {
    fprintf(dumpFile, "%d; ", index);
  }

  fprintf(dumpFile, "}\n");
  ////////////////////////////////////////////////////////////////////////////////////////////////

  // ARROWS TO NEXT //////////////////////////////////////////////////////////////////////////////
  fprintf(dumpFile, "free->%d;\n", list->freeNode);

  for (size_t index = 0; index < list->capacity; index++) {
    if (index && list->next[index]) {
      fprintf(dumpFile, "%d->%d;\n", index, list->next[index]);
    }
  }

  fprintf(dumpFile, "0->%d;\n", list->next[0]);
  fprintf(dumpFile, "%d->0;\n", list->prev[0]);
  ////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////
  fprintf(dumpFile, "edge [style=bold, color=\"#FF0000:black;0.001\", weight=0, penwidth=2.5, arrowsize=0.4];\n");
  ////////////////////////////////////////////////////////////////////////////////////////////////z

  // ARROWS TO PREV //////////////////////////////////////////////////////////////////////////////
  size_t index = 0;
  do {
    fprintf(dumpFile, "%d->%d;\n", index, list->prev[index]);
    index = list->prev[index];
  } while (index != 0);
  ////////////////////////////////////////////////////////////////////////////////////////////////

  fprintf(dumpFile, "}\n");
  fclose(dumpFile);

  char *buffer = (char *)calloc(MAX_CMD_BUFFER_SIZE, sizeof(char));
  customWarning(buffer != NULL, BAD_BUFFER_POINTER);

  writeHtmlHeader(list);

  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "dot -Tsvg %s >> %s", list->infoData->dumpFileName, list->infoData->htmlDumpFileName);
  system(buffer);

  FREE_(buffer);

  return NO_ERRORS;
}

linkedListError writeHtmlHeader(linkedList *list) {
  customWarning(list       != NULL, LIST_BAD_POINTER);
  customWarning(list->infoData->htmlDumpFileName != NULL, DUMP_FILE_BAD_POINTER);

  char *header = (char *)calloc(MAX_HEADER_SIZE, sizeof(char));
  snprintf(header, MAX_HEADER_SIZE, "<br><br><div style='font-size:22px'><b><u>linkedList</u><font color='DeepSkyBlue'>" " [%p]" "</font></b>"
                                    " at <b><u>%s:%d</u> <u>(%s)</u></b> <font color='DarkOrange'><b><br>born at</b></font>"
                                    " <b><u>%s:%d</u></b> (%s)<br><br></div>",
          list, list->infoData->lastUsedFileName, list->infoData->lastUsedLine, list->infoData->lastUsedFunctionName,
                list->infoData->bornFileName,     list->infoData->bornLine,     list->infoData->bornFunctionName);

  int openFile = open(list->infoData->htmlDumpFileName, O_WRONLY | O_APPEND);
  customWarning(openFile != NO_SUCH_FILE, NO_SUCH_FILE);

  ssize_t writeFile = write(openFile, header, MAX_HEADER_SIZE);

  close(openFile);

  return NO_ERRORS;
}