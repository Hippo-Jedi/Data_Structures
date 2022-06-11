/*
 * Name: Michael Smith
 * Email: Smitmic5@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "dynarray.h"

struct dynarray {
  void** data;
  int size;
  int capacity;
};

/*
 * This function allocates and initializes a new, empty dynamic array and
 * return a pointer to it. Has an initial capacity of 2.
 */
struct dynarray* dynarray_create() {
  struct dynarray* da = malloc(sizeof(struct dynarray));
  da->size = 0;
  da->capacity = 2;
  da->data = malloc(da->capacity * sizeof(void *));
  return da;
}

/*
 * This function frees the memory associated with a dynamic array.
 *
 * Params:
 *   da - the dynamic array to be destroyed.  May not be NULL.
 */
void dynarray_free(struct dynarray* da) {
  for (int i=0; i<da->size; i++) {
    da->data[i] = NULL;
  }
  free(da->data);
  da->size = 0;
  da->capacity = 0;
  free(da);
}

/*
 * This function returns the size of a given dynamic array.
 */
int dynarray_size(struct dynarray* da) {
  return da->size;
}

/*
 * This function inserts a new value to the end of dynamic array.
 *
 * Params:
 *   da - the dynamic array into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_insert(struct dynarray* da, void* val) {
  if (da->size >= da->capacity) {
    da->capacity = da->capacity * 2;
    da->data = realloc(da->data, da->capacity * sizeof(val));
  }
  da->data[da->size] = val;
  da->size++;
}

/*
 * This function removes an element at a specified index from dynamic
 * array.  All existing elements following the specified index are moved
 * forward to fill in the gap left by the removed element.
 *
 * Params:
 *   da - the dynamic array from which to remove an element.  May not be NULL.
 *   idx - the index of the element to be removed.  The value of `idx` must be
 *     between 0 (inclusive) and n (exclusive), where n is the number of
 *     elements stored in the array.
 */
void dynarray_remove(struct dynarray* da, int idx) {
  for (int i = idx; i<=da->size-2; i++) {
    da->data[i] = da->data[i + 1];
  }
  da->size--;
  da->capacity--;
  da->data = realloc(da->data, da->capacity * sizeof(void *));
}

/*
 * This function returns the value of an existing element in dynamic
 * array.
 *
 * Params:
 *   da - the dynamic array from which to get a value.  May not be NULL.
 *   idx - the index of the element whose value should be returned.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 */
void* dynarray_get(struct dynarray* da, int idx) {
  return da->data[idx];
}

/*
 * This function updates (i.e. overwrite) the value of an existing
 * element in the dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_set(struct dynarray* da, int idx, void* val) {
  da->data[idx] = val;
}
