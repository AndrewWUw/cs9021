/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for two numbers, adds them up, and stores     *
 *              and displays the result.                                       *
 *              Only works when the second input provided by the user is 1.    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, l, sum;
    printf("Input a nonzero natural number: ");
    scanf("%d", &n);
    printf("Input another nonzero natural number: ");
    scanf("%d", &l);
    sum = n + 1;
    printf("The sum of %d and %d is: %d", n, l, sum);
    return EXIT_SUCCESS;
}

