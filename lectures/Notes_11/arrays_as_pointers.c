/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Displays values and addresses of arrays.                       *
 *                                                                             *
 * Purpose: Illustrates how arrays can be treated as pointers.                 *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 4
#define JAN 1
#define APR 4
#define JUL 7
#define OCT 10

int main(void) {
    short dates[SIZE] = {JAN, APR, JUL, OCT};
    double rates[SIZE] = {102.00, 105.00, 108.00, 110.00};
    short *pti = dates;
    double *ptf = rates;
    printf("           %s       %s      %s\n", "index", "short", "double");
    for (int i = 0; i < SIZE; ++i)
          printf("addresses: %5d  %10p  %10p\n", i, pti + i, ptf + i);
    for (int i = 0; i < SIZE; ++i)
        printf("values:    %5d  %10d  %10.2f\n", i, *(pti + i), *(ptf + i));
    return EXIT_SUCCESS;
}

