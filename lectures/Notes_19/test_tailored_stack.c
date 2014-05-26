/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Tests the functions defined in tailored_stack.h.               *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_stack.c                                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "tailored_stack.h"

void print_stack(const Stack *const);
void print_value(const Value);

int main(void) {
    Stack stack;
    Value value;
    initialise_stack(&stack);
    printf("Stack after initialisation: "), print_stack(&stack);
    printf("Height of (): %d\n", stack_height(&stack));
    printf("() is empty: %s\n", is_empty_stack(&stack) ? "yes" : "no");
    pop(&stack, &value);
    printf("Stack after popping: "), print_stack(&stack);
    push(0, &stack);
    printf("Stack after pushing 0: "), print_stack(&stack);
    printf("Height of (0): %d\n", stack_height(&stack));
    printf("(0) is empty: %s\n", is_empty_stack(&stack) ? "yes" : "no");
    pop(&stack, &value);
    printf("Stack after popping: "), print_stack(&stack);
    printf("Value being popped: %d\n", value);
    push(0, &stack);
    push(1, &stack);
    printf("Stack after pushing 0 and then 1: "), print_stack(&stack);
    printf("Height of (0,1): %d\n", stack_height(&stack));
    printf("(0,1) is empty: %s\n", is_empty_stack(&stack) ? "yes" : "no");
    pop(&stack, &value);
    printf("Stack after popping: "), print_stack(&stack);
    printf("Value being popped: %d\n", value);
    push(2, &stack);
    push(3, &stack);
    printf("Stack after pushing 2 and then 3: "), print_stack(&stack);
    printf("Height of (0,2,3): %d\n", stack_height(&stack));
    empty_stack(&stack);
    printf("Stack after it has been emptied: "), print_stack(&stack);
}

void print_stack(const Stack *const pt_to_stack) {
    if (!pt_to_stack->height)
        printf("()\n");
    else {
        printf("(");
        apply_to_stack(print_value, pt_to_stack);
        printf("\b)\n");
    }
}

void print_value(const Value value) {
    printf("%d,", value);
}  
