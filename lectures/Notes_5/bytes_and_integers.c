/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Outputs the number of bytes allocated to some of the types     *
 *              meant to represent integers     y                               *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("There are %zd bytes in a signed short int.\n", sizeof(short));
    printf("There are %zd bytes in a signed int.\n", sizeof(int));
    printf("There are %zd bytes in a signed long int.\n", sizeof(long));
    printf("There are %zd bytes in a signed long long int.\n", sizeof(long long));
    return EXIT_SUCCESS;
}

