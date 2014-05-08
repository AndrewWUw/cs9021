/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Performs a few operations on a union.                          *
 *                                                                             *
 * Purpose: Illustrates the concept of union.                                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

union a_union {
    int x;
    double y;
};

int main(void) {
    union a_union u;
    printf("Size of a_union: %lu bytes\n", sizeof u);
    printf("Address of u: %p\n", &u);
    printf("Address of u.x: %p\n", &u.x);
    printf("Address of u.y: %p\n", &u.y);
    u.x = 23;
    printf("u.x: %d\n", u.x);
    u.y = -45.25;
    printf("u.y: %f\n", u.y);
    printf("u.x: %d\n", u.x);
    return EXIT_SUCCESS;
}

