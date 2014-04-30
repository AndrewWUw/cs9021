/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds                                                          *
 *               - the number of nonzero digits,                               *
 *               - the largest nonzero least frequent digit, and               *
 *               - the smallest nonzero most frequent digit                    *
 *              in a randomly generated sequence of 10 numbers                 *
 *              between 0 and 4.                                               *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define BOUND 5

int main(int argc, char **argv) {
    /* We run the program with one number as command line argument. */
    if (argc != 2) {
        printf("Please provide 1 command line argument.\n");
        return EXIT_FAILURE;
    }
    /* We use it as a seed for the random number generator. */
    srand(strtoul(argv[1], NULL, 10));
    int data[SIZE];
    /* We randomly generate 10 numbers in the range [0, 5) and store them in data. */
    for (int i = 0; i < SIZE; ++i)
        data[i] = rand() % BOUND;
    int digit_count[BOUND] = {0};
    int nb_of_nonzero_digits;
    int least_frequent_digit = 0, most_frequent_digit = 0;
    for (int i = 0; i < SIZE; ++i)
        ++digit_count[data[i]];
    nb_of_nonzero_digits = SIZE - digit_count[0];
    for (int i = 1; i < BOUND; ++i)
        if (digit_count[i]) {
            if (!least_frequent_digit || digit_count[i] <= digit_count[least_frequent_digit])
                least_frequent_digit = i;
            if (!most_frequent_digit || digit_count[i] > digit_count[most_frequent_digit])
                most_frequent_digit = i;
        }
    printf("The digits that have been generated are: ");
    for (int i = 0; i < SIZE; ++i)
        printf("%2d", data[i]);
    putchar('\n');
    if (!nb_of_nonzero_digits)
        printf(" All those digits are equal to 0.\n");
    else {
        printf(" %d of those digits", nb_of_nonzero_digits);
        nb_of_nonzero_digits == 1 ? printf(" is ") : printf(" are ");
        printf("not equal to 0.\n");
        printf(" The largest nonzero least frequent digit is %d\n", least_frequent_digit);
        printf(" The smallest nonzero most frequent digit is %d\n", most_frequent_digit);
    }   
    return EXIT_SUCCESS;
}
