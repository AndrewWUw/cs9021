/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all perfect 3-digit numbers.                             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

/* The smallest 3-digit number */
#define MIN 100
/* The largest 3-digit number */
#define MAX 999

int main(void) {
    printf("The solutions are:\n\n");
    for (int i = MIN; i <= MAX; ++i) {
        /* 1 is a divisor, we will check whether 2, 3, ..., i/2 are divisors */
        int sum_of_divisors = 1;
        for (int j = 2; j <= i / 2; ++j)
            if (i % j == 0)
                /* This can also be written: sum_of_divisors = sum_of_divisors + j */
                sum_of_divisors += j;
        if (i == sum_of_divisors)
            printf("%d is a solution.\n", i);
    }
    return EXIT_SUCCESS;
}

