/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for two numbers: an unsigned long long,       *
 *              say digits, and an int, say sum, and outputs                   *
 *              the number of ways of selecting digits from digits             *
 *              that sum up to sum.                                            *
 *                                                                             *
 *  Written by Eric Martin for COMP9021                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int solve(const unsigned long long, const int);

int main(void) {
    unsigned long long digits;
    int sum;
    printf("Input an unsigned long long and an int: ");
    scanf("%llu %d",&digits, &sum);
    const int nb_of_solutions = solve(digits, sum);
    if (nb_of_solutions == 0)
        printf("There is no solution.\n");
    else if (nb_of_solutions == 1)
        printf("There is a unique solution\n");
    else
        printf("There are %d solutions.\n", nb_of_solutions);
    return EXIT_SUCCESS;
}

int solve(const unsigned long long digits, const int sum) {
    if (sum < 0)
        return 0;
    if (digits == 0)
        if (sum == 0)
            return 1;
        else
            return 0;
    /* Either take the last digit d form digits and try to get sum - d
     * from the remaining digits, or do not take the last digit and
     * try to get sum from the remaining digits. */
    return solve(digits / 10, sum) + solve(digits / 10, sum - digits % 10);
}
