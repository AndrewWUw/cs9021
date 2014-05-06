/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds the largest prime factor of a positive number.           *
 *              Linear worst case complexity, which is unexceptable for some   *
 *              inputs.                                                        *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Variable number is equal to 1 or is of the form n1^e1 * n2^e2 * ... * nk^ek
     * for some prime numbers n1, ..., nk with n1 < n2 < ... < nk and nonzero e1, ..., ek. */
    int number;
    printf("Enter a strictly positive number: ");
    scanf("%d", &number);
    int divisor = 1;
    /* If number != 1 then there exists i such that divisor < ni and
     * number = ni^ei * ... * nk^ek. */
    printf("The largest divisor of %d ", number);
    while (number != 1) {
        ++divisor;
        /* Test fails if divisor is not ni,
         *      succeeds ei times otherwise, changing number to ni+1^ei+1 * ... * nk^ek
         *                                                      (1 in case i = k).      */
        while (number % divisor == 0)
            number /= divisor;
    }
    printf("is %d.", divisor);
    return EXIT_SUCCESS;
}