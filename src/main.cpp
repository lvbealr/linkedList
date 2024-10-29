#include <cstdio>
#include <cstdlib>

#include "../include/linkedList.h"

int main() {
  linkedList LIST = {};
  linkedListInitialize(&LIST, 10);
  linkedListNode *CURRENT_NODE = LIST.head;
  // fprintf(stderr, "HEAD: %p\n", CURRENT_NODE);
  // fprintf(stderr, "TAIL: %p\n", LIST.tail);

  while (CURRENT_NODE) {
    // fprintf(stderr, "NOW: %p\t AFTER: %p\n", CURRENT_NODE, CURRENT_NODE->nextListNode);
    CURRENT_NODE = CURRENT_NODE->nextListNode;
  }

  linkedListDestruct(&LIST);

  // printf("%p %p %p", LIST.head, LIST.root, LIST.tail);
  return 0;
}