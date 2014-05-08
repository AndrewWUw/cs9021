/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out the evaluation of four integer expressions.         *
 *                                                                             *
 * Purpose: Illustrates the use of parentheses in the definition of            *
 *          macros with arguments                                              *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define expr1(x, y) x / y
#define expr2(x, y) (x) / (y)
#define expr3(x, y) (x / y)
#define expr4(x, y) ((x) / (y))

int main(void) {
    printf("%d\n", 3 / expr1(1 + 1, 1 + 1)); // (3 / 1) + (1 / 1) + 1
    printf("%d\n", 3 / expr2(1 + 1, 1 + 1)); // (3 / (1 + 1)) / (1 + 1)
    printf("%d\n", 3 / expr3(1 + 1, 1 + 1)); // 3 / (1 + (1 / 1) + 1)
    printf("%d\n", 3 / expr4(1 + 1, 1 + 1)); // 3 / ((1 + 1) / (1 + 1))
    return EXIT_SUCCESS;
}

