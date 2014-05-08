/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the use of bitwise operators.                      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const int a = 9, b = 10;
    printf("a & b: %d\n", a & b);
    printf("a ^ b: %d\n", a ^ b);
    printf("a | b: %d\n", a | b);
    printf("a << 2: %d\n", a << 2);
    printf("a >> 2: %d\n", a >> 2);
    return EXIT_SUCCESS;
}

