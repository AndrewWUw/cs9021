/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Outputs the number of bytes allocated to some of the types     *
 *              meant to represent natural numbers                             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("There are %zd bytes in an unsigned short int.\n", sizeof(unsigned short));
    printf("There are %zd bytes in an unsigned int.\n", sizeof(unsigned));
    printf("There are %zd bytes in an unsigned long int.\n", sizeof(unsigned long));
    printf("There are %zd bytes in an unsigned long long int.\n", sizeof(unsigned long long));
    return EXIT_SUCCESS;
}

