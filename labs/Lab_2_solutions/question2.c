/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all triples of consecutive positive three-digit integers *
 *              each of which is the sum of two squares.                       *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

/* The largest number whose square is a 3-digit number */
#define MAX 31

int nb_of_consecutive_squares(int);

/* For all n in [100, 999], if n is found to be of the form a^2 + b^2
 * then sums_of_two_squares[n] will be set to a + b * 100,
 * so a and b can be easily retrieved.
 * Note that there might be other decompositions of n into a sum of 2 squares;
 * we just recall the first decomposition we find.
 * Also note that we waste the 100 first elements of the array;
 * we can afford it and this choice makes the program simpler. */
int sums_of_two_squares[1000];

int main(void) {
    for (int i = 0; i <= MAX; ++i)
        for (int j = i; j <= MAX; ++j) {
            const int n = i * i + j * j;
            if (n < 100)
                continue;
            if (n > 1000)
                break;
            sums_of_two_squares[n] = i + j * 100;
        }
    for (int n = 100; n < 1000; ++n) {
        const int i = nb_of_consecutive_squares(n);
        if (i < 3) {
            /* There is no potential triple before n + i + 1; the loop will increment n by i. */
            n += i;
            continue;
        }
        printf("(%d, %d, %d) "
               "(equal to (%d^2+%d^2, %d^2+%d^2, %d^2+%d^2)) is a solution.\n",
               n, n + 1, n + 2,
               sums_of_two_squares[n] % 100, sums_of_two_squares[n] / 100,
               sums_of_two_squares[n + 1] % 100, sums_of_two_squares[n + 1] / 100,
               sums_of_two_squares[n + 2] % 100, sums_of_two_squares[n + 2] / 100);
        /* We assume we could have two solutions of the form
         * (n, n + 1, n + 2) and (n + 1, n + 2, n + 3)
         * (but as the solution shows, this never happens...),
         * hence n is incremented by 1 only in the next iteration of the loop.
         * We could avoid checking that sums_of_two_squares[n + 1] and
         * sums_of_two_squares[n + 2] are not equal to 0, but why make the program
         * more complicated for no significant gain? */
    }
    return EXIT_SUCCESS;
}

int nb_of_consecutive_squares(int n) {
    if (sums_of_two_squares[n] == 0)
        return 0;
    if (sums_of_two_squares[++n] == 0)
        return 1;
    if (sums_of_two_squares[++n] == 0)
        return 2;
    return 3;
}

    
    
