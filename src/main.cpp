#include <cstdio>
#include <cstdlib>

#include "../include/linkedList.h"

int main() {
  linkedList LIST = {};
  linkedListInitialize(&LIST, 10);
  insertNode(&LIST, 0, 111);
  insertNode(&LIST, 3, 5);
  insertNode(&LIST, 4, 10);

  for (int i = 0; i < 10; i++) {
    printf("|%-5d| ", LIST.data[i]);
  }

  printf("\n");

  deleteNode(&LIST, 3);
  deleteNode(&LIST, 0);

  for (int i = 0; i < 10; i++) {
    printf("|%-5d| ", LIST.data[i]);
  }

  linkedListDestruct(&LIST);
  return 0;
}