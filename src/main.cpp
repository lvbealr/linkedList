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
  // NEXT: [0]-> 1 [111] [1]-> 0 [  0] [2]-> 3 [  0] [3]-> 4 [  0] [4]-> 5 [  0] [5]-> 6 [  0] [6]-> 7 [  0] [7]-> 8 [  0] [8]-> 9 [  0] [9]->10 [  0]
  // PREV: [0]-> 1 [111] [1]-> 0 [  0] [2]->-1 [  0] [3]->-1 [  0] [4]->-1 [  0] [5]->-1 [  0] [6]->-1 [  0] [7]->-1 [  0] [8]->-1 [  0] [9]->-1 [  0]

  insertNode(&LIST, newIndex, &newIndex, 222); // newIndex = 1, freeNode = 2; => newIndex = 2, freeNode = 3
  PRINT_LL;
  // NEXT: [0]-> 1 [111] [1]-> 2 [222] [2]-> 0 [  0] [3]-> 4 [  0] [4]-> 5 [  0] [5]-> 6 [  0] [6]-> 7 [  0] [7]-> 8 [  0] [8]-> 9 [  0] [9]->10 [  0]
  // PREV: [0]-> 2 [222] [1]-> 0 [  0] [2]-> 1 [111] [3]->-1 [  0] [4]->-1 [  0] [5]->-1 [  0] [6]->-1 [  0] [7]->-1 [  0] [8]->-1 [  0] [9]->-1 [  0]

  insertNode(&LIST, newIndex, &newIndex, 333); // newIndex = 2, freeNode = 3; => newIndex = 3, freeNode = 4;
  PRINT_LL;
  // NEXT: [0]-> 1 [111] [1]-> 2 [222] [2]-> 3 [333] [3]-> 0 [  0] [4]-> 5 [  0] [5]-> 6 [  0] [6]-> 7 [  0] [7]-> 8 [  0] [8]-> 9 [  0] [9]->10 [  0]
  // PREV: [0]-> 3 [333] [1]-> 0 [  0] [2]-> 1 [111] [3]-> 2 [222] [4]->-1 [  0] [5]->-1 [  0] [6]->-1 [  0] [7]->-1 [  0] [8]->-1 [  0] [9]->-1 [  0]

  deleteNode(&LIST, 1);                        // newIndex = 3, freeNode = 4; => newIndex = 3, freeNode = 1
  PRINT_LL;
  // NEXT: [0]-> 2 [222] [1]-> 4 [  0] [2]-> 3 [333] [3]-> 0 [  0] [4]-> 5 [  0] [5]-> 6 [  0] [6]-> 7 [  0] [7]-> 8 [  0] [8]-> 9 [  0] [9]->10 [  0]
  // PREV: [0]-> 3 [333] [1]->-1 [  0] [2]-> 0 [  0] [3]-> 2 [222] [4]->-1 [  0] [5]->-1 [  0] [6]->-1 [  0] [7]->-1 [  0] [8]->-1 [  0] [9]->-1 [  0]

  insertNode(&LIST, newIndex, &newIndex, 444); // newIndex = 3, freeNode = 1; => newIndex = 1, freeNode = 4
  PRINT_LL;
  // NEXT: [0]-> 2 [222] [1]-> 0 [  0] [2]-> 3 [333] [3]-> 1 [444] [4]-> 5 [  0] [5]-> 6 [  0] [6]-> 7 [  0] [7]-> 8 [  0] [8]-> 9 [  0] [9]->10 [  0]
  // PREV: [0]-> 1 [444] [1]-> 3 [333] [2]-> 0 [  0] [3]-> 2 [222] [4]->-1 [  0] [5]->-1 [  0] [6]->-1 [  0] [7]->-1 [  0] [8]->-1 [  0] [9]->-1 [  0]

  linkedListDestruct(&LIST);
  return 0;
}