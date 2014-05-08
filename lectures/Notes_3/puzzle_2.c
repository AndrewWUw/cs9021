/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all sets of positive integers {x, y, z} such that        *
 *              x, y and z have no occurrence of 0,                            *
 *              every nonzero digit occurs exactly once in one of x, y or z,   *
 *              and x, y and z are perfect squares.                            *
 *                                                                             *
 * Purpose: Gives a partial but significant overview of the C language.        *
 *          Second variant, that uses bitwise operations.                      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* A number at least equal to any of the three numbers of any solution. */
#define MAX 9876532
/* In binary, a sequence of ten 1's. */
#define TEN_ONES 1023

bool test(int, int *const);

int main(void) {
    int nb_of_solutions = 0;
    /* If it was a perfect square, MAX would, associated with 1 and 4,
     * be the largest member of a possible solution. */
    const int max = sqrt(MAX);
    for (int i = 1; i <= max; ++i) {
        const int i_square = i * i;
        int i_digits = 1;
        /* Tests whether all digits that occur in i_square are distinct
         * and not equal to 0.
         * Next line could also be written as follows.
         * if (test(i_square, &i_digits) == false) */
        if (!test(i_square, &i_digits))
            continue;
        for (int j = i + 1; j <= max; ++j) {
            const int j_square = j * j;
            int i_and_j_digits = i_digits;
            /* Tests whether all digits that occur in j_square are distinct,
             * not equal to 0, and do not occur in i_square.
             * Next line could also be written as follows.
             * if (test(j_square, &i_and_j_digits) == false) */
            if (!test(j_square, &i_and_j_digits))
                continue;            
            for (int k = j + 1; k <= max; ++k) {
                const int k_square = k * k;
                int i_and_j_and_k_digits = i_and_j_digits;
                /* Tests whether all digits that occur in k_square are distinct,
                 * not equal to 0, and do not occur in either i_square or j_square.
                 * Next line could also be written as follows.
                 * if (test(k_square, &i_and_j_and_k_digits) == false) */
                if (!test(k_square, &i_and_j_and_k_digits))
                    continue;
                /* Tests whether every nonnull digit occurs in one of the three squares. */
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
 * and examines whether the dig-th bit of *digits is set to 1.
 * If that is the case, returns false to indicate that an occurrence of 0 has been
 * found in candidate solution member, or a second occurrence of dig has been found
 * in candidate solution member. Otherwise, sets dig-th bit of digits to 1
 * for each digit dig that occurs in i and returns true. */

bool test(int i, int *const pt_to_digits) {
    /* Next line could also be written as follows.
     * while (i != 0) */
    while (i) {
        const int dig = 1 << i % 10;
        /* Next line could also be written as follows.
         * if (*pt_to_digits & dig != 0) */
        if (*pt_to_digits & dig)
            return false;
        /* Next line could also be written as follows.
         * *pt_to_digits = *pt_to_digits | dig; */
        *pt_to_digits |= dig;
        /* Next line could also be written as follows.
         * i = i / 10; */
        i /= 10;
    }
    return true;
}
