/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all possible ways of inserting + and - signs             *
 *              in the sequence 123456789                                      *
 *              (at most one sign before any digit) such that                  *
 *              the resulting arithmetic expression evaluates to 100.          *
 *                                                                             *
 *  Written by Eric Martin for COMP9021                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool test(int, int);
void print_solution(const int, int);

int main(void) {
    /* For each of the 8 digits 2, 3,..., 9, say d, generate one of 3 numbers:
     * - 1 causes d to become the rightmost digit of the number being built;
     * - 0 causes
     *     . the number being built to be considered fully built
     *       and subtracted or added to the running sum,
     *     . the next number to be built to begin with d and eventually
     *       be subtracted to the running sum;
     * - 2 causes
     *     . the number being built to be considered fully built
     *       and subtracted or added to the running sum,
     *     . the next number to be built to begin with d and eventually
     *       be added to the running sum. */
    for (int i = 0; i < pow(3, 8); ++i) {
        /* Let the first number be of the form 1... */
        if (test(1, i))
            print_solution(1, i);
        /* Let the first number be of the form -1... */
        if (test(-1, i))
            print_solution(-1, i);
    }
    return EXIT_SUCCESS;
}

bool test(int sign, int i) {
    int sum = 0, number = 1;   
    for (int digit = 2; digit < 10; ++digit, i /= 3) {
        int one_of_3_options = i % 3;
        if (one_of_3_options % 2)
            number = number * 10 + digit;
        else {
            sum += sign * number;
            number = digit;
            sign = --one_of_3_options;
        }
    }    
    if (sum + sign * number == 100)
        return true;
    return false;
}

void print_solution(const int one_or_minus_one, int i) {
    printf("%2d", one_or_minus_one);
    for (int digit = 2; digit < 10; ++digit, i /= 3) {
        const int one_of_3_options = i % 3;
        if (one_of_3_options % 2 == 0)
            printf(one_of_3_options ? " + " : " - ");
        printf("%d", digit);
    }    
    printf(" = 100\n");
}
