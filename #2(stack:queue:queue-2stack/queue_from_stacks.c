/*
 * Name: Michael Smith
 * Email: smitmic5@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "queue_from_stacks.h"

struct queue_from_stacks {
  struct stack* s1;
  struct stack* s2;
};

/*
 * This function allocates and initializes a new, empty queue-from-stacks
 * and return a pointer to it.
 */
struct queue_from_stacks* queue_from_stacks_create() {
  struct queue_from_stacks *que = malloc(sizeof(struct queue_from_stacks));
  que->s1 = stack_create();
  que->s2 = stack_create();
  return que;
}

/*
 * This function frees the memory associated with a queue-from-stacks.
 *
 * Params:
 *   qfs - the queue-from-stacks to be destroyed.  May not be NULL.
 */
void queue_from_stacks_free(struct queue_from_stacks* qfs) {
  assert(qfs);
  stack_free(qfs->s1);
  stack_free(qfs->s2);
  free(qfs);
}

/*
 * This function indicates whether a given queue-from-stacks is currently
 * empty. 
 *
 * Params:
 *   qfs - the queue-from-stacks whose emptiness is being questioned.  May not
 *     be NULL.
 */
int queue_from_stacks_isempty(struct queue_from_stacks* qfs) {
  assert(qfs);
  return (stack_isempty(qfs->s1) && stack_isempty(qfs->s2));
}

/*
 * This function enqueues a new value into a given queue-from-stacks.
 * The value to be enqueued is specified as a void pointer.
 *
 * Params:
 *   qfs - the queue-from-stacks into which a value is to be enqueued.  May not
 *     be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_from_stacks_enqueue(struct queue_from_stacks* qfs, void* val) {
  assert(qfs);
  stack_push(qfs->s1, val);
}

/*
 * This function returns the value stored at the front of a given
 * queue-from-stacks *without* removing that value.
 *
 * Params:
 *   qfs - the queue-from-stacks from which to query the front value.  May not be NULL.
 */
void* queue_from_stacks_front(struct queue_from_stacks* qfs) {
  assert(qfs);
  void* top;
  while (!stack_isempty(qfs->s1)) {
    stack_push(qfs->s2, stack_pop(qfs->s1));
  }
  top = stack_top(qfs->s2);
  while (!stack_isempty(qfs->s2)) {
    stack_push(qfs->s1, stack_pop(qfs->s2));
  }
  return top;
}

/*
 * This function dequeues a value from a given queue-from-stacks and
 * return the dequeued value.
 *
 * Params:
 *   qfs - the queue-from-stacks from which a value is to be dequeued.  May not
 *     be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void* queue_from_stacks_dequeue(struct queue_from_stacks* qfs) {
  assert(qfs);
  void* top;
  while (!stack_isempty(qfs->s1)) {
    stack_push(qfs->s2, stack_pop(qfs->s1));
  }
  top = stack_pop(qfs->s2);
  while (!stack_isempty(qfs->s2)) {
    stack_push(qfs->s1, stack_pop(qfs->s2));
  }
  return top;
}
