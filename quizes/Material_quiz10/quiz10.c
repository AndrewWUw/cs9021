/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes +s and digits as command line arguments, checks whether  *
 *              they make up a valid infix expression, and evaluates it        *
 *              in case it is.                                                 *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_stack.c                                                      *
 *       my_code_sol.c                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_code.h"
#include "tailored_stack.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Provide at least one command line argument.\n");
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; ++i)
        if (strlen(argv[i]) != 1 || !isdigit(argv[i][0]) && argv[i][0] != '+') {
            printf("Command line arguments should be digits or + only.\n");
            return EXIT_FAILURE;
        }
    Stack stack;
    initialise_stack(&stack);
    store_command_line_args_in_stack(argc, argv, &stack);
    if (!is_correct_prefix_expression(&stack) || !is_empty_stack(&stack)) {
        printf("Not a correct prefix expression.\n");
        return EXIT_SUCCESS;
    }
    empty_stack(&stack);
    store_command_line_args_in_stack(argc, argv, &stack);
    printf("The expression evaluates to %d\n", evaluate_expression(&stack));
    return EXIT_SUCCESS;
}
