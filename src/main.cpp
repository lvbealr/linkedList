#include <cstdio>
#include <cstdlib>

#include "linkedList.h"

#define PRINT_LL {                                                                        \
  printf("NEXT: ");                                                                       \
  for (int i = 0; i < 10; i++) {                                                          \
    printf("\033[36;1m[%d]->%2d\033[0m (%3d) ", i, LIST.next[i], LIST.data[LIST.next[i]]);\
  }                                                                                       \
  printf("\n");                                                                           \
  printf("PREV: ");                                                                       \
  for (int i = 0; i < 10; i++) {                                                          \
    printf("\033[36;1m[%d]->%2d\033[0m (%3d) ", i, LIST.prev[i], LIST.data[LIST.prev[i]]);\
  }                                                                                       \
  printf("\n\n");                                                                         \
}

int main() {
  linkedList LIST = {};

  linkedListInitialize(&LIST, 10);

  ssize_t newIndex = 0;

  insertNode(&LIST, 0,        &newIndex, 111);
  insertNode(&LIST, newIndex, &newIndex, 222);
  insertNode(&LIST, newIndex, &newIndex, 333);

  deleteNode(&LIST, 1);

  insertNode(&LIST, newIndex, &newIndex, 444);

  linkedListDestruct(&LIST);
  return 0;
}