/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Uses the stack interface to evaluate an arithmetic expression  *
 *              written in postfix and built from natural numbers using only   *
 *              the binary + and * operators.                                  *              
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_stack.c                                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tailored_stack.h"

int main(int argc, char **argv) {
    char *expression = argv[1];
    Value value_1, value_2;
    Stack stack;
    initialise_stack(&stack);
    for (int i = 0; i < strlen(expression); ++i) {
        if (expression[i] == '+') {
            pop(&stack, &value_1);
            pop(&stack, &value_2);
            push(value_1 + value_2, &stack);
        }
        if (expression[i] == '*') {
            pop(&stack, &value_1);
            pop(&stack, &value_2);
            push(value_1 * value_2, &stack);
        }
        if ((expression[i] >= '0') && (expression[i] <= '9')) {
            push(expression[i++] - '0', &stack);
            while ((expression[i] >= '0') && (expression[i] <= '9')) {
                pop(&stack, &value_1);
                push(10 * value_1 + expression[i++] - '0', &stack);
            }
            --i;
        }
    }
    pop(&stack, &value_1);
    printf("%d\n", value_1);
    empty_stack(&stack);
    return EXIT_SUCCESS;
}       
