/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Stores 2 and 3 in memory, adds them up and stores the result   *
 *              in memory, and displays that result.                           *
 *              Also displays the locations where the numbers 2, 3 and 5       *
 *              are stored in memory.                                          *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

/* Addresses are given in base 16. */
int main(void) {
    int n = 2;
    printf("%d is stored at location: %p\n", n, &n);
    int m = 3;
    printf("%d is stored at location: %p\n", m, &m);
    int sum = n + m;
    printf("The sum of %d and %d is: %d\n", n, m, sum);
    printf("It is stored at location: %p\n", &sum);    
    return EXIT_SUCCESS;
}

