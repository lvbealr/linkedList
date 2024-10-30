#include <cstdio>
#include <cstdlib>

#include "linkedList.h"

#define PRINT_LL {                                                                        \
  printf("NEXT: ");                                                                       \
  for (int i = 0; i < 10; i++) {                                                          \
    printf("\033[36;1m[%d]->%2d\033[0m [%3d] ", i, LIST.next[i], LIST.data[LIST.next[i]]);\
  }                                                                                       \
  printf("\n");                                                                           \
  printf("PREV: ");                                                                       \
  for (int i = 0; i < 10; i++) {                                                          \
    printf("\033[36;1m[%d]->%2d\033[0m [%3d] ", i, LIST.prev[i], LIST.data[LIST.prev[i]]);\
  }                                                                                       \
  printf("\n\n");                                                                         \
}

int main() {
  linkedList LIST = {};

  linkedListInitialize(&LIST, 10);

  ssize_t newIndex = 0;

  insertNode(&LIST, 0,        &newIndex, 111); // newIndex = 0, freeNode = 1; => newIndex = 1, freeNode = 2
  PRINT_LL;
  // NEXT:   1 [111]   0 [  0]   3 [  0]   4 [  0]   5 [  0]   6 [  0]   7 [  0]   8 [  0]   9 [  0]  10 [  0]
  // PREV:   1 [111]   0 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]

  insertNode(&LIST, newIndex, &newIndex, 222); // newIndex = 1, freeNode = 2; => newIndex = 2, freeNode = 3
  PRINT_LL;
  // NEXT:   1 [111]   2 [222]   0 [  0]   4 [  0]   5 [  0]   6 [  0]   7 [  0]   8 [  0]   9 [  0]  10 [  0]
  // PREV:   2 [222]   0 [  0]   1 [111]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]

  insertNode(&LIST, newIndex, &newIndex, 333); // newIndex = 2, freeNode = 3; => newIndex = 3, freeNode = 4;
  PRINT_LL;
  // NEXT:   1 [111]   2 [222]   3 [333]   0 [  0]   5 [  0]   6 [  0]   7 [  0]   8 [  0]   9 [  0]  10 [  0]
  // PREV:   3 [333]   0 [  0]   1 [111]   2 [222]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]

  deleteNode(&LIST, 1);                        // newIndex = 3, freeNode = 4; => newIndex = 3, freeNode = 1
  PRINT_LL;
  // NEXT:   2 [222]   4 [  0]   3 [333]   0 [  0]   5 [  0]   6 [  0]   7 [  0]   8 [  0]   9 [  0]  10 [  0]
  // PREV:   3 [333]  -1 [  0]   0 [  0]   2 [222]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]

  insertNode(&LIST, newIndex, &newIndex, 444); // newIndex = 3, freeNode = 1; => newIndex = 1, freeNode = 4
  PRINT_LL;
  // NEXT:   2 [222]   0 [  0]   3 [333]   1 [444]   5 [  0]   6 [  0]   7 [  0]   8 [  0]   9 [  0]  10 [  0]
  // PREV:   1 [444]   3 [333]   0 [  0]   2 [222]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]  -1 [  0]

  linkedListDestruct(&LIST);
  return 0;
}