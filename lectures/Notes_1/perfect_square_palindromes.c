/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all 6-digit palindromes that are perfect squares.        *
 *                                                                             *
 * Purpose: A small exercise in problem solving                                *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

/* The square root of 100,000 is approximately equal to 316.23 */
#define MIN 317
#define MAX 999

int main(void) {
    printf("The solutions are:\n\n");
    
    int digits[6];
    for (int i = MIN; i <= MAX; ++i) {
        int i_square = i * i;
        for (int k = 0; k < 6; ++k) {
            /* Make (k+1)st element of the sequence 'digits' (whose elements are indexed
             * by 0, 1, 2, 3, 4 and 5) the last digit of i_square,
             * which is nothing but the remainder of the division
             * of i_square by 10. */
            digits[k] = i_square % 10;
            /* Get rid of the last digit of i_square,
             * which amounts to dividing i_square by 10
             * and let i_square become the integral part of the result.
             * Next line could also be written as follows.
             * i_square = i_square / 10; */
            i_square /= 10;
        }
        /* i * i is a palindrome if its first and sixth digits are equal,
         * its second and fifth digits are equal, and its third and fourth digits are equal. */
        if (digits[0] == digits[5] && digits[1] == digits[4] && digits[2] == digits[3])
            printf("%d (equal to the square of %d)\n", i * i, i);
    }
    return EXIT_SUCCESS;
}

