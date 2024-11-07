#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include "graphVizDump.h"
#include "customWarning.h"

static const size_t MAX_HEADER_SIZE     = 300;

char *setDumpFileName(const char *dumpFolder) {
  const time_t currentTime = time(NULL);
  tm localTime = *localtime(&currentTime);

  char *fileName = (char *)calloc(MAX_FILE_NAME_SIZE, sizeof(char));

  customWarning(fileName != NULL, NULL);

  snprintf(fileName, FILENAME_MAX, "%s/%.2d.%.2d.%.4d-%.2d:%.2d:%.2d.dot",
                                    dumpFolder, localTime.tm_mday, localTime.tm_mon,
                                    localTime.tm_year + 1900, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

  return fileName;
}

// TODO add enums for working with file

linkedListError linkedListDump(linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  const char *dumpFileName = setDumpFileName(list->infoData->dumpFolderName);
  strncpy(list->infoData->dumpFileName,   dumpFileName, MAX_DUMP_FILE_NAME);

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
  customWarning(buffer != NULL, BAD_BUFFER_POINTER); // TODO

  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "dot -Tsvg %s -o %s.svg", list->infoData->dumpFileName, list->infoData->dumpFileName);
  system(buffer);

  FREE_(buffer);

  char *pathToFile = (char *)calloc(MAX_PATH_TO_FILE, sizeof(char));
  customWarning(pathToFile != NULL, BAD_BUFFER_POINTER); // TODO

  snprintf(pathToFile, MAX_PATH_TO_FILE, "%s.svg", list->infoData->dumpFileName);

  dumpToHtml(list, pathToFile, "graphVizDumps/graphVizDump.html"); // TODO html file
  FREE_(pathToFile);

  return NO_ERRORS;
}

linkedListError dumpToHtml(linkedList *list, const char *pathToFile, const char *pathToHtml) {
  customWarning(list       != NULL, LIST_BAD_POINTER     );
  customWarning(pathToFile != NULL, DUMP_FILE_BAD_POINTER);

  writeHtmlHeader(list, pathToHtml);

  svgFile file = {};

  getSvgFileInfo(list, pathToFile, &file);
  writeSvgToHtml(pathToHtml, &file);

  FREE_(file.data);
  file = {};

  return NO_ERRORS;
}

linkedListError getSvgFileInfo(linkedList *list, const char *pathToFile, svgFile *file) {
  customWarning(list       != NULL, LIST_BAD_POINTER     );
  customWarning(pathToFile != NULL, DUMP_FILE_BAD_POINTER); // TODO

  struct stat fileData = {};
  stat(pathToFile, &fileData);

  file->size = fileData.st_size;

  file->data = (char *)calloc(file->size, sizeof(char));
  customWarning(file->data != NULL, DUMP_FILE_BAD_POINTER); // TODO заебало уже прдумывать неймы для enumов

  int openFile = open(pathToFile, O_RDONLY);
  // customWarning(openFile != -1, ) // TODO короче еще один кастом ворнинг на открытый файл

  ssize_t sizeRead = read(openFile, file->data, file->size);
  // customWarning(sizeRead == file.size, ) // TODO еще один ворнинг на размер файла мб взять с онегина enum

  close(openFile);

  return NO_ERRORS;
}

linkedListError writeSvgToHtml(const char *pathToHtml, svgFile *file) {
  customWarning(pathToHtml != NULL, DUMP_FILE_BAD_POINTER); // TODO
  // customWarning(file != NULL, ) // TODO

  int openFile = open(pathToHtml, O_WRONLY | O_APPEND);
  // customWarning(openFile != -1, ) // TODO

  ssize_t writeFile = write(openFile, file->data, file->size);
  // customWarning() // TODO

  close(openFile);

  return NO_ERRORS;
}

linkedListError writeHtmlHeader(linkedList *list, const char *pathToHtml) {
  customWarning(list       != NULL, LIST_BAD_POINTER);
  customWarning(pathToHtml != NULL, DUMP_FILE_BAD_POINTER);

  char *header = (char *)calloc(MAX_HEADER_SIZE, sizeof(char));
  snprintf(header, MAX_HEADER_SIZE, "<br><br><div style='font-size:22px'>linkedList [%p] at %s:%d (%s)<br>born at %s:%d (%s)<br><br></div>",
          list, list->infoData->lastUsedFileName, list->infoData->lastUsedLine, list->infoData->lastUsedFunctionName,
                list->infoData->bornFileName,     list->infoData->bornLine,     list->infoData->bornFunctionName);

  int openFile = open(pathToHtml, O_WRONLY | O_APPEND);
  // customWarning // TODO

  ssize_t writeFile = write(openFile, header, MAX_HEADER_SIZE);
  // customWarning // TODO

  close(openFile);

  return NO_ERRORS;
}