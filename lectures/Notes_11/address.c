/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Displays values and addresses of variables                     *
 *              and function argummets.                                        *
 *                                                                             *
 * Purpose: Illustrates that functions use different space                     *
 *          for their local variables and arguments.                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

void f(int);

int main(void) {
    int a = 2, b = 5;
    printf("In main(), a = %d and &a = %p\n", a, &a);
    printf("In main(), b = %d and &b = %p\n", b, &b);
    f(a);
    return EXIT_SUCCESS;
}

void f(int b) {
    int a = 10;
    printf("In f(), a = %d and &a = %p\n", a, &a);
    printf("In f(), b = %d and &b = %p\n", b, &b);
}

