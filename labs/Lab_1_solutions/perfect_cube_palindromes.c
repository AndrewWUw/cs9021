/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all 7-digit palindromes that are perfect cubes.          *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

/* The cubic root of 1,000,000 */
#define MIN 100
/* The largest integer smaller at most equal to the cubic root of 9,999,999 */
#define MAX 215

int main(void) {
    printf("The solutions are:\n\n");
    
    int digits[7];
    for (int i = MIN; i <= MAX; ++i) {
        int i_cube = i * i * i;
        int k = 7;
        /* Test whether k is positive.
         * If not, exit the while loop.
         * Otherwise, decrease k by 1 and execute the body of the loop. */
        while (k--) {
            /* Make (k + 1)st element of the sequence 'digits' (whose elements are indexed
             * by 0, 1, 2, 3, 4, 5 and 6) the last digit of i_cube,
             * which is nothing but the remainder of the division
             * of is_cube by 10. */
            digits[k] = i_cube % 10;
            /* Get rid of the last digit of i_cube,
             * which amounts to dividing i_cube by 10
             * and let i_cube become the integral part of the result. */
            i_cube /= 10;
        }
        /* i * i * i is a palindrome if its first and seventh digits are equal,
         * its second and sixth digits are equal, and its third and fifth digits are equal. */
        if (digits[0] == digits[6] && digits[1] == digits[5] && digits[2] == digits[4])
            printf("%d (equal to the cube of %d)\n", i * i * i, i);
    }
    return EXIT_SUCCESS;
}

