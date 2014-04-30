/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all sets of positive integers {i, j, k} such that        *
 *              i, j and k have no occurrence of 0,                            *
 *              every nonnull digit occurs exactly once in one of i, j or k,   *
 *              and i, j and k are perfect squares.                            *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* The square of the largest number of a possible solution. */
#define MAX 9876532
/* In binary, a sequence of ten 1's. */
#define TEN_ONES 1023

int test(int, const int);

int main(void) {
    int nb_of_solutions = 0;
    /* If it was a perfect square, the square root of 9876532 would,
     * associated with 1 and 4, be the largest member of a possible solution. */
    const int max = sqrt(MAX);
    for (int i = 1; i <= max; ++i) {
        const int i_square = i * i;
        /* Tests whether all digits that occur in i_square are distinct
         * and not equal to 0. */
        const int i_digits = test(i_square, 1);
        if (i_digits == 1)
            continue;
        for (int j = i + 1; j <= max; ++j) {
            const int j_square = j * j;
            /* Tests whether all digits that occur in j_square are distinct,
             * not equal to 0, and do not occur in i_square. */
            const int i_and_j_digits = test(j_square, i_digits);
            if (i_and_j_digits == i_digits)
                continue;            
            for (int k = j + 1; k <= max; ++k) {
                const int k_square = k * k;
                /* Tests whether all digits that occur in k_square are distinct,
                 * not equal to 0, and do not occur in either i_square or j_square. */
                const int i_and_j_and_k_digits = test(k_square, i_and_j_digits);
                if (i_and_j_and_k_digits == i_and_j_digits)
                    continue;
                /* Tests whether every nonnull digit occurs
                 * in one of the three squares. */
                if (i_and_j_and_k_digits == TEN_ONES) {
                    ++nb_of_solutions;
                    printf("%-3d %-3d %-3d\n", i_square, j_square, k_square);
                }
            }
        }
    }
    if (nb_of_solutions == 0) {
        printf("No solution has been found, which is suspicious.\n");
        return EXIT_FAILURE;
    }
    if (nb_of_solutions == 1)
        printf("is the unique solution that has been found.\n");
    else
        printf("are the %d solutions that have been found.\n", nb_of_solutions);
    return EXIT_SUCCESS;
}

/* Extracts each digit dig that occurs in i, from right to left,
 * and examines whether dig is null or the dig-th bit of digits is set to 1.
 * If that is the case, returns digits unchanged to indicate
 * that an occurrence of 0 has been found in candidate solution member,
 * or a second occurrence of dig has been found in candidate solution member.
 * Otherwise, sets dig-th bit of digits to 1 for each digit dig that occurs in i
 * and returns the resulting value. */
int test(int i, const int digits) {
    int new_digits = digits;
    while (i) {
        int dig = 1 << i % 10;
        if (new_digits & dig)
            return digits;
        new_digits |= dig;
        i /= 10;
    }
    return new_digits;
}
