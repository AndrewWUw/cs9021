/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes +s and digits as command line arguments, checks whether  *
 *              they make up a valid infix expression, and evaluates it        *
 *              in case it is.                                                 *
 *                                                                             *
 * Written by ***         for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_stack.c                                                      *
 *       quiz10.c                                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* THIS IS THE ONLY FILE YOU HAVE TO SUBMIT.
 * IT WILL BE COMPILED WITH THE OTHER FILES YOU HAVE BEEN PROVIDED WITH. */

#include "my_code.h"

void store_command_line_args_in_stack(int argc, char **argv,
        Stack * const pt_to_stack) {

    for (int i = 1; i < argc; ++i) {
        push(argv[i][0], pt_to_stack);
    }
}

bool is_correct_prefix_expression(Stack * const pt_to_stack) {

    int height = stack_height(pt_to_stack);
    Value items[height];
    int operatorSum = 0;
    int digitSum = 0;

    for (int i = height - 1; i >= 0; --i) {
        pop(pt_to_stack, &items[i]);
        if (isdigit(items[i])) {
            ++digitSum;
        } else if (items[i] == '+') {
            ++operatorSum;
        }
    }

    if (!isdigit(items[height - 1]) || (operatorSum + 1 != digitSum)) {
        return false;
    } else if (height >= 2) {
        if (!isdigit(items[height - 2]))
            return false;
    } else if (height == 1) {
        if (isdigit(items[0]))
            return true;
        else
            return false;
    } else {
        return true;
    }
}

Value evaluate_expression(Stack * const pt_to_stack) {
    Stack stack;
    initialise_stack(&stack);
    int height = stack_height(pt_to_stack);
    Value value_1, value_2, value;
    Value items[height];

    for (int i = 0; i < height; ++i) {
        pop(pt_to_stack, &items[i]);
    }

//    for (int i = 0; i < height; ++i) {
//        printf("%c ", items[i]);
//    }
//    printf("\n");

    for (int i = 0; i < height; ++i) {
        if (items[i] == '+') {
            pop(&stack, &value_1);
            pop(&stack, &value_2);
            push(value_1 + value_2, &stack);
        } else {
            push(items[i] - '0', &stack);
        }
    }

    pop(&stack, &value);
    empty_stack(&stack);
    return value;
}
