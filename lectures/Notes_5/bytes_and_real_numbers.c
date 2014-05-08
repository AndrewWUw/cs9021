/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Outputs the number of bytes allocated to some of the types     *
 *              meant to represent real numbers                                *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("There are %zd bytes in a float.\n", sizeof(float));
    printf("There are %zd bytes in a double.\n", sizeof(double));
    printf("There are %zd bytes in a long double.\n", sizeof(long double));
    return EXIT_SUCCESS;
}

