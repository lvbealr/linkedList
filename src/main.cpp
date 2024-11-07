#include <cstdio>
#include <cstdlib>

#include "linkedList.h"

#define INIT_LINKED_LIST(listPtr, capacity) {                                 \
  linkedListInitialize    (listPtr, capacity);                                \
  linkedListInfoInitialize(listPtr, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
}

int main() {
  linkedList LIST = {};

  INIT_LINKED_LIST(&LIST, 10)

  ssize_t newIndex = 0;

  insertNode(&LIST, 0,        &newIndex, 111);
  insertNode(&LIST, newIndex, &newIndex, 222);
  insertNode(&LIST, newIndex, &newIndex, 333);

  deleteNode(&LIST, 1);

  insertNode(&LIST, newIndex, &newIndex, 444);

  linkedListDestruct(&LIST);
  return 0;
}