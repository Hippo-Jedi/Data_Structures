/*
 * Name: Michael Smith
 * Email: smitmic5@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>

#include "queue.h"
#include "dynarray.h"

struct queue {
  struct dynarray* array;
};

/*
 * This function allocates and initializes a new, empty queue and return
 * a pointer to it.
 */
struct queue* queue_create() {
  struct queue* que = malloc(sizeof(struct queue));
  assert(que);
  que->array = dynarray_create();
  return que;
}

/*
 * This function frees the memory associated with a queue. 
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.
 */
void queue_free(struct queue* queue) {
  assert(queue);
  dynarray_free(queue->array);
  free(queue);
}

/*
 * This function indicates whether a given queue is currently empty.
 *
 * Params:
 *   queue - the queue whose emptiness is being questioned.  May not be NULL.
 */
int queue_isempty(struct queue* queue) {
  assert(queue);
  return dynarray_size(queue->array) == 0;
}

/*
 * This function enqueues a new value into a given queue.  The value to
 * be enqueued is specified as a void pointer. 
 *
 * Params:
 *   queue - the queue into which a value is to be enqueued.  May not be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_enqueue(struct queue* queue, void* val) {
  assert(queue);
  dynarray_insert(queue->array, val);
}

/*
 * This function returns the value stored at the front of a given queue
 * *without* removing that value.  
 *
 * Params:
 *   queue - the queue from which to query the front value.  May not be NULL.
 */
void* queue_front(struct queue* queue) {
  assert(queue);
  return dynarray_get(queue->array, 0);
}

/*
 * This function dequeues a value from a given queue and return the
 * dequeued value.
 *
 * Params:
 *   queue - the queue from which a value is to be dequeued.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void* queue_dequeue(struct queue* queue) {
  assert(queue);
  void* data = queue_front(queue);
  dynarray_remove(queue->array, 0);
  return data;
}
