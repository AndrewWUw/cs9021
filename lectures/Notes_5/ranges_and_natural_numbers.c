/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Outputs the maximum values associated with the types           *
 *              meant to represent natural numbers                             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("The maximum value for an unsigned short int is %hu.\n", USHRT_MAX);
    printf("The maximum value for an unsigned int is %u.\n", UINT_MAX);
    printf("The maximum value for an unsigned long int is %lu.\n", ULONG_MAX);
    printf("The maximum value for an unsigned long long int is %llu.\n", ULLONG_MAX);
    return EXIT_SUCCESS;
}

