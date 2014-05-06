/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all sequences of consecutive prime 5-digit numbers,      *
 *              say (a, b, c, d, e, f), such that                              *
 *              b = a + 2, c = b + 4, d = c + 6, e = d + 8, and f = e + 10.    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SMALLEST_FIVE_DIGIT_ODD_NUMBER 10001
#define LARGEST_FIVE_DIGIT_ODD_NUMBER  99999

int main(void) {
    printf("The solutions are:\n\n");
    /* Number of primes found so far */
    int count = 0;
    /* Equal to 0 if first prime in sequence still has to be found;
     * otherwise, equal to 1 plus number of odd nonprime numbers seen since last prime */
    int gap = 0;
    for (int i = SMALLEST_FIVE_DIGIT_ODD_NUMBER; i <= LARGEST_FIVE_DIGIT_ODD_NUMBER; i += 2) {
        bool is_prime = true;
        for (int k = 3; k <= sqrt(i); k += 2)
            if (i % k == 0) {
                is_prime = false;
                break;
            }
        if (is_prime) {
            if (count == 0 || gap == count) {
                ++count;                
                gap = 1;
            } else
                count = gap = 1;
            if (count == 6)
                printf("    %d   %d   %d   %d   %d   %d\n",
                       i - 30, i - 28, i - 24, i - 18, i - 10, i);
        } else if (count && ++gap > count)
            count = gap = 0;
    }
    return EXIT_SUCCESS;
}
