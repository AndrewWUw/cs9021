/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Stores 2 and 3 in memory, adds them up and stores the result   *
 *              in memory, and displays that result.                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 2;
    int m = 3;
    int sum = n + m;
    printf("The sum of %d and %d is: %d\n", n, m, sum);
    return EXIT_SUCCESS;
}

