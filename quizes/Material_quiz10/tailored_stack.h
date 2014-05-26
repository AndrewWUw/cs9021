#ifndef _STACK_H_
#define _STACK_H_

/* Change if another capacity is required. */
#define INITIAL_CAPACITY 1

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/* Change if stack store values of another type. */
typedef int Value;

typedef struct {
    Value *pt_to_bottom;
    int height;
    int capacity;
} Stack;

/* Initialises the 3 fields of the stack stored at pt_to_stack. */
void initialise_stack(Stack *pt_to_stack);

/* Returns true or false, depending on whether or not the stack stored at
 * pt_to_stack is empty. */
bool is_empty_stack(const Stack *const pt_to_stack);

/* Returns the height of the stack stored at pt_to_stack. */
int stack_height(const Stack *const pt_to_stack);

/* Applies the function which is the value of pt_to_function to the values stored
 * in the stack stored at pt_to_stack. */
void apply_to_stack(void (*const pt_to_function)(), const Stack *const pt_to_stack);

/* If the stack stored at pt_to_stack is not full, pushes val on top of the stack
 * stored at pt_to_stack, and updates the 3 fields of the stack. */
void push(const Value val, Stack *const pt_to_stack);

/* If the stack stored at pt_to_stack is not empty, then pops the value
 * stored on top of the stack, stores the popped value at pt_to_value, and
 * returns true; otherwise, return false.
 * In any case, updates the 3 fields of the stack. */
bool pop(Stack *const pt_to_stack, Value *pt_to_value);

/* Deletes all nodes of the stack stored at pt_to_stack, and resets the 3 fields of the stack. */
void empty_stack(Stack *pt_to_stack);

#endif
