/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Defines stack processing functions for stacks of that store    *
 *              values of type Value, by default defined as int in             *
 *              tailored_stack.h, but that can be changed to another type to   *
 *              accomodate other needs.                                        *
 *              The initial capacity of a stack is set by default to 1 in      *
 *              tailored_stack.h, but that can be changed to another value.    *              
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "tailored_stack.h"

void initialise_stack(Stack *const pt_to_stack) {
    pt_to_stack->pt_to_bottom = NULL;
    pt_to_stack->height = 0;
    pt_to_stack->capacity = 0;
}

bool is_empty_stack(const Stack *const pt_to_stack) {
    return !pt_to_stack->height;
}

int stack_height(const Stack *const pt_to_stack) {
    return pt_to_stack->height;
}

void apply_to_stack(void (*const pt_to_function)(), const Stack *const pt_to_stack) {
    for (int i = 0; i < pt_to_stack->height; ++i)
        pt_to_function(pt_to_stack->pt_to_bottom[i]);
}

void push(const Value val, Stack *const pt_to_stack) {
    if (pt_to_stack->height >= pt_to_stack->capacity) {
        pt_to_stack->capacity = (pt_to_stack->capacity + 1) * 2;
        pt_to_stack->pt_to_bottom = realloc(pt_to_stack->pt_to_bottom,
                                      sizeof(Value) * pt_to_stack->capacity);
        assert(pt_to_stack->pt_to_bottom);
    }
    pt_to_stack->pt_to_bottom[pt_to_stack->height++] = val;
}
    
bool pop(Stack *const pt_to_stack, Value *const pt_to_value) {
    if (!pt_to_stack->height)
        return false;
    *pt_to_value = pt_to_stack->pt_to_bottom[--pt_to_stack->height];
    return true;
}

void empty_stack(Stack *const pt_to_stack) {
    if (pt_to_stack->pt_to_bottom) {
        free(pt_to_stack->pt_to_bottom);
        pt_to_stack->pt_to_bottom = NULL;
        pt_to_stack->height = pt_to_stack->capacity = 0;
    }
}




    
    

        



