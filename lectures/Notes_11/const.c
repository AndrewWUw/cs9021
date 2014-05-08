/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Assigns some value to a const variable a,                      *
 *              then assigns another value to the same memory location         *
 *              through another variable, and displays the new value of a.     *
 *              one of them being referred to by a const variable.             *
 *                                                                             *
 * Purpose: Demonstrates that const qualifies names, not memory loacations.    *
 *                                                                             *
 * Written for COMP9021                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(void) {
    const int a = 10;
    int *b = &a;
    *b = 20;
    printf("The value of a is: %d\n", a);
    return EXIT_SUCCESS;
}

