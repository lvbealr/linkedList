#include <cstdio>
#include <cstdlib>
#include <memory.h>

#include "linkedList.h"
#include "customWarning.h"

// TODO VERIFY IN EVERY FUNCTION

linkedListError linkedListInitialize(linkedList *list, size_t capacity) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = (ssize_t)capacity + 1;

  // list->data     = (elem_t  *)customCalloc((size_t)list->capacity, sizeof(elem_t), 666);
  list->data     = (elem_t  *)calloc((size_t)list->capacity, sizeof(elem_t));
  list->prev     = (ssize_t *)calloc((size_t)list->capacity, sizeof(ssize_t));
  list->next     = (ssize_t *)calloc((size_t)list->capacity, sizeof(ssize_t));

  customWarning(list->data != NULL, DATA_BAD_POINTER);
  customWarning(list->prev != NULL, PREVIOUS_BAD_POINTER); // TODO MAYBE RENAME ENUM
  customWarning(list->next != NULL, NEXT_BAD_POINTER);     // TODO MAYBE RENAME ENUM

  list->data[0]  = 0; // TODO all cells to poison
  list->prev[0]  = 0; // ПУСТАЯ ЯЧЕЙКА, НИКУДА НЕ УКАЗЫВАЕТ
  list->next[0]  = 0; // ПУСТАЯ ЯЧЕЙКА, НИКУДА НЕ УКАЗЫВАЕТ
  list->freeNode = 1; // В НУЛЕВУЮ ЯЧЕЙКУ НИЧЕГО НЕ КЛАДЕМ, ВСЕ УЗЛЫ СЕЙЧАС СВОБОДНЫ, НАЧИНАЕМ С ПЕРВОГО РАССТАВЛЯТЬ ИНДЕКСЫ

  for (ssize_t nodeIndex = list->freeNode; nodeIndex < list->capacity; nodeIndex++) {
    list->next[nodeIndex] = (nodeIndex + 1) % list->capacity; // КОЛЬЦЕВАЯ ИНДЕКСАЦИЯ
    list->prev[nodeIndex] = -1;                               // НЕВАЛИДНЫЙ ПОИНТЕР
  }

  // for (ssize_t nodeIndex = list->freeNode; nodeIndex < list->capacity; nodeIndex++) {
  //   printf("[%d]->%d ", nodeIndex, list->next[nodeIndex]);
  // }
  // printf("\n");

  return NO_ERRORS;
}

linkedListError linkedListDestruct(linkedList *list) {
  customWarning(list != NULL, LIST_BAD_POINTER);

  list->capacity = -1;
  list->freeNode = -1;

  FREE_(list->data);
  FREE_(list->prev);
  FREE_(list->next);

  return NO_ERRORS;
}

linkedListError linkedListVerify    (linkedList *list) {
  // TODO do list with errors like in stack instead of custom warnings
  customWarning(list           != NULL,                                LIST_BAD_POINTER    );
  customWarning(list->data     != NULL,                                DATA_BAD_POINTER    );
  customWarning(list->prev     != NULL,                                PREVIOUS_BAD_POINTER);
  customWarning(list->next     != NULL,                                NEXT_BAD_POINTER    );
  customWarning(list->capacity < 0,                                    BAD_CAPACITY        );
  customWarning(list->prev[0]  < 0 || list->prev[0] >= list->capacity, BAD_TAIL            );
  customWarning(list->next[0]  < 0 || list->prev[0] >= list->capacity, BAD_HEAD            );

  // TODO CHECK freeNode?

  // TODO MORE CHECKS

  return NO_ERRORS;
}

linkedListError linkedListDump      (linkedList *list) {
  printf("\033[1;33mhui hui bolshoi zhirny cherny hui pisya popa hui chlenik\n\033[0m");
  return NO_ERRORS;
}

linkedListError insertNode          (linkedList *list, ssize_t index, ssize_t *newIndex, elem_t value) {
  customWarning(list != NULL, NODE_BAD_POINTER);
  // TODO CHECK INDEX, CAPACITY

  *newIndex                     = list->freeNode;             // newIndex - индекс свободной (freeNode) ячейки
  list->freeNode                = list->next[list->freeNode]; // свободной становится ячейка, следующая от предыдущей свободной

  list->data[*newIndex]         = value;                      // в новую (свободную) ячейку кладем значение

  list->prev[list->next[index]] = *newIndex;                  // для следующей от старой ячейки, указателем на предыдущую становится новый индекс
  list->prev[*newIndex]         = index;                      // для новой ячейки предыдущая ячейка - та, после которой вставляем,
                                                              // то есть с индексом index

  list->next[*newIndex]         = list->next[index];          // следующей для новой ячейки становится указатель на следующую для старой
                                                              // (просто поместили между ними)
  list->next[index]             = *newIndex;                  // новая ячейка встала справа от старой, значит для старойуказатель на след.
                                                              // - указатель на новую

  return NO_ERRORS;
}

linkedListError deleteNode          (linkedList *list, ssize_t index) {
  customWarning(list != NULL, LIST_BAD_POINTER);
  // TODO CHECKER

  list->prev[list->next[index]] = list->prev[index]; // [A -> B -> C], del B, [A -> C], для С предыдущей становится предыдущая для В, т. е. А
  list->next[list->prev[index]] = list->next[index]; // [A -> B -> C], del B, [A -> C], для А следующей  становится следующая  для В, т. е. С

  list->next[index] = list->freeNode;                // [A -> ... -> С]
  list->prev[index] = -1;                            // эмэаээаэаэа надо подумать поч невалидный поинтер на предыдущую 🤔🤔🤔🤔🤔
  list->freeNode    = index;                         // ячейка, которую занимала В, теперь свободна
  // TODO это как будто не совсем правильно, наверное узлы должны сдвигаться друг к другу? так между ними пустые узлы
  // UPD: нет вроде нормально

  return NO_ERRORS;
}

// TODO подумать как лучше это реализовать? сделать отдельную структурку, чтобы вытаскивать целую структуру с next, prev, value
// TODO или достаточно доставать только значение по индексу например (чекнуть дефолтные функции на cppreference)

// linkedListError getNode             (linkedList *list, linkedListNode *getNodeInfo, size_t index) {
//   customWarning(list != NULL, LIST_BAD_POINTER);
//   // TODO CHECK FOR GET NODE INFO PTR

//   getNodeInfo->value = list->data[index];
//   getNodeInfo->prev  = list->prev[index];
//   getNodeInfo->next  = list->next[index];

//   return NO_ERRORS;
// }



