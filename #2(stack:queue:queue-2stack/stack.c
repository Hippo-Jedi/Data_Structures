/*
 * Name: Michael Smith
 * Email: smitmic5@oregonstate.edu
 */

#include <stdlib.h>

#include "stack.h"
#include "list.h"

struct stack {
  struct list* list;
};

/*
 * This function allocates and initializes a new, empty stack and return
 * a pointer to it.
 */
struct stack* stack_create() {
  struct stack* stk = (struct stack*)malloc(sizeof(struct stack));
  stk->list = list_create();
  return stk;
}

/*
 * This function frees the memory associated with a stack. 
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.
 */
void stack_free(struct stack* stack) {
  list_free(stack->list);
  free(stack);
  return;
}

/*
 * This function indicates whether a given stack is currently empty.
 *
 * Params:
 *   stack - the stack whose emptiness is being questioned.  May not be NULL.
 */
int stack_isempty(struct stack* stack) {
  if (get_head(stack->list) == NULL) {
    return 1;
  } else { 
    return 0;
  }
}

/*
 * This function pushs a new value onto a given stack.  The value to be
 * pushed is specified as a void pointer. 
 *
 * Params:
 *   stack - the stack onto which a value is to be pushed.  May not be NULL.
 *   val - the value to be pushed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void stack_push(struct stack* stack, void* val) {
  list_insert(stack->list, val);
}

/*
 * This function returns the value stored at the top of a given stack
 * *without* removing that value.
 *
 * Params:
 *   stack - the stack from which to query the top value.  May not be NULL.
 */
void* stack_top(struct stack* stack) {
  return get_head(stack->list);
}

/*
 * This function pops a value from a given stack and return the popped
 * value. 
 *
 * Params:
 *   stack - the stack from which a value is to be popped.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was popped.
 */
void* stack_pop(struct stack* stack) {
  return remove_head(stack->list);
}
