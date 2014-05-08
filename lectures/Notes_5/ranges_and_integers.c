/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Outputs the maximum values associated with the types           *
 *              meant to represent integers                                    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("The minimum value for a signed short int is %hd.\n", SHRT_MIN);
    printf("The maximum value for a signed short int is %hd.\n", SHRT_MAX);
    printf("The minimum value for a signed int is %d.\n", INT_MIN);
    printf("The maximum value for a signed int is %d.\n", INT_MAX);
    printf("The minimum value for a signed long int is %ld.\n", LONG_MIN);
    printf("The maximum value for a signed long int is %ld.\n", LONG_MAX);
    printf("The minimum value for a signed long long int is %lld.\n", LLONG_MIN);
    printf("The maximum value for a signed long long int is %lld.\n", LLONG_MAX);
    return EXIT_SUCCESS;
}

