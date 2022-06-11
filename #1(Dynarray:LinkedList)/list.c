/*
 * Name: Michael Smith
 * Email: Smitmic5@oregonstate.edu
 */

#include <stdlib.h>

#include "list.h"

struct link {
  void* val;
  struct link* next;
};

struct list {
  struct link* head;
};

/*
 * This function allocates and initialize sa new, empty linked list and
 * return a pointer to it.
 */
struct list* list_create() {
  struct list *list = malloc(sizeof(struct list));
  list->head = NULL;
  return list;
}

/*
 * This function frees the memory associated with a linked list.
 *
 * Params:
 *   list - the linked list to be destroyed.  May not be NULL.
 */
void list_free(struct list* list) {
  struct link *current = list->head;
  struct link *next = current;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  free(list);
}

/*
 * This function inserts a new value at head of linked list.
 *
 * Params:
 *   list - the linked list into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void list_insert(struct list* list, void* val) {
  struct link *new = malloc(sizeof(struct link));
  new->val = val;
  new->next = list->head;
  list->head = new;
}

/*
 * This function removes an element with a specified value from a given
 * linked list. 
 *
 * Params:
 *   list - the linked list from which to remove an element.  May not be NULL.
 *   val - the value to be removed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 *   cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 */
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b)) {
  struct link *link = list->head;
  struct link *old = NULL;
  while (link) {
    if (*(int *)(link->val) == *(int *)(val)) {
      break;
    }
    old = link;
    link = link->next;
  }
  if (!link) {
    return;
  }
  if (!old) {
    old = list->head;
    list->head = list->head->next;
    free(old);
  } else {
    old->next = link->next;
    free(link);
  }
}

/*
 * This function returns the position (i.e. the 0-based "index") of the
 * first instance of a specified value within a given linked list. 
 *
 * Params:
 *   list - the linked list from which to remove an element.  May not be NULL.
 *   val - the value to be located.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 *   cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 *
 * Return:
 *   This function should return the 0-based position of the first instance of
 *   `val` within `list`, as determined by the function `cmp` (i.e. the closest
 *    such instance to the head of the list) or -1 if `list` does not contain
 *    the value `val`.
 */
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b)) {
  int idx = 0;
  for (struct link *link = list->head; link; link = link->next) {
    if (*(int *)(link->val) == *(int *)(val)) {
      return idx;
    }
    idx++;
  }
  return -1;
}

/*
 * This function reverses the order of the links in a given linked list.
 *
 * Params:
 *   list - the linked list to be reversed.  May not be NULL.  When this
 *     function returns this should contain the reversed list.
 */
void list_reverse(struct list* list) {
  struct link *previous = NULL;
  struct link *current = list->head;
  struct link *next = NULL;
  while (current) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  list->head = previous;
}
