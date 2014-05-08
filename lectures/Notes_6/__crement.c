/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Increments some variables.                                     *
 *                                                                             *
 * Purpose: Illustrate the difference between the prefix and postfix versions  *
 *          of the incrment and decrement operators.                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a = 1, b = 1;
    const int a_plus = a++;
    const int plus_b = ++b;
    printf("a   a_plus   b   plus_b \n");
    printf("%d%6d%7d%6d\n", a, a_plus, b, plus_b);

    return EXIT_SUCCESS;
}

