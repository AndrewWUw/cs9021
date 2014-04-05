/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Assigns a digit to each letter that occurs in the words        *
 *              "three", "four" and "eight", distinct letters being assigned   *
 *              distinct digits, and the digit assigned to the first letter    *
 *              of each of the three words being nonzero, such that            *
 *              - three is prime,                                              *
 *              - four is a perfect square, and                                *
 *              - eight is a perfect cube.                                     *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* The least possible value for eight is 10234,
 * and the cubic root of 10234 is 21.71.
 * The greatest possible value for eight is 98765,
 * and the cubic root of 98765 is 46.22. */
#define MIN_EIGHT 22
#define MAX_EIGHT 46
/* The least possible value for four is 1023,
 * and the square root of 1023 is 31.98.
 * The greatest possible value for four is 9876,
 * and the square root of 9876 is 99.38. */
#define MIN_FOUR 32
#define MAX_FOUR 99

bool is_prime(int);

int main(void) {
    for (int n = MIN_EIGHT; n <= MAX_EIGHT; ++n) {
        int eight = n * n * n;
        int digits_eight[10] = {0};
        int e = eight / 10000;
        /* three has to be prime hence e cannot be even. */
        if (e % 2 == 0)
            continue;
        /* We memorise e. */
        digits_eight[e] = 1;
        int i = eight / 1000 % 10;
        /* digits_eight[i] becomes equal to 1 if i has not been seen, and to 2 otherwise. */
        if (++digits_eight[i] == 2)
            continue;
        int g = eight / 100 % 10;
        /* digits_eight[g] becomes equal to 1 if g has not been seen, and to 2 otherwise. */
        if (++digits_eight[g] == 2)
            continue;
        int h = eight / 10 % 10;            
        /* digits_eight[h] becomes equal to 1 if h has not been seen, and to 2 otherwise. */
        if (++digits_eight[h] == 2)
            continue;
        int t = eight % 10;
        /* three does not start with 0. */
        if (t == 0)
            continue;
        /* digits_eight[t] becomes equal to 1 if t has not been seen, and to 2 otherwise. */
        if (++digits_eight[t] == 2)
            continue;
        for (int m = MIN_FOUR; m <= MAX_FOUR; ++m) {
            /* If the current attempt at setting four to a suitable value eventually fails
             * then we need to remember the current value of eight. */
            int digits_eight_four[10];
            for (int i = 0; i < 10; ++i)
                digits_eight_four[i] = digits_eight[i];
            int four = m * m;
            int f = four / 1000;
            /* digits_eight_four[f] becomes equal to 1 if f has not been seen, and to 2 otherwise. */
            if (++digits_eight_four[f] == 2)
                continue;
            int o = four / 100 % 10;
            /* digits_eight_four[o] becomes equal to 1 if o has not been seen, and to 2 otherwise. */
            if (++digits_eight_four[o] == 2)
                continue;
            int u = four / 10 % 10;
            /* digits_eight_four[u] becomes equal to 1 if u has not been seen, and to 2 otherwise. */
            if (++digits_eight_four[u] == 2)
                continue;
            int r = four % 10;
            if (digits_eight_four[r])
                continue;
            int three = 10000 * t + 1000 * h + 100 * r + 10 * e + e;
            if (is_prime(three))
                printf("three = %d, four = %d and eight = %d is a solution.\n", three, four, eight);
        }
    }
    return EXIT_SUCCESS;
}

bool is_prime(int n) {
    /* Returns false if n is even. */
    if ((n % 2) == 0)
        return false;
    /* If n is not prime then it has a factor at most equal to its square root. */
    const int max = sqrt(n);
    /* Returns false if n is divisible by an odd number. */
    for (int k = 3; k <= max; k += 2) {
        if (n % k == 0)
            return false;
    }
    return true;
}

