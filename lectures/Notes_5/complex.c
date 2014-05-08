/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Computes sums and products of a few complex numbers.           *
 *                                                                             *
 * Purpose: Describe the representation of complex numbers                     *
 *          and the creal() and cimag() functions.                             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const float _Complex a = I;
    const float _Complex b = 1 - I;
    const float _Complex c = 5 + 2J;
    const float _Complex d = 11 -7j;
    const float _Complex e = 3;
    printf("  Sums         Products\n");
    printf("%2.0f + %2.0fi       %2.0f + %2.0fi\n",
           creal(a + b), cimag(a + b), creal(a * b), cimag(a * b));
    printf("%2.0f + %2.0fi       %2.0f + %2.0fi\n",
           creal(c + d), cimag(c + d), creal(c * d), cimag(c * d));
    printf("%2.0f + %2.0fi       %2.0f + %2.0fi\n",
           creal(a + e), cimag(a + e), creal(a * e), cimag(a * e));
    return EXIT_SUCCESS;
}

