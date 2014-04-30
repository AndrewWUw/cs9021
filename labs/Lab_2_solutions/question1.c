/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds a strictly positive number                               *
 *              that satisfies 13 out of the 15 conditions:                    *
 *              - It is a multiple of 2, 3, 4, 5, 6, 7, 8, 9 and 10.           *
 *              - It is smaller than 1000, 750, 550 and 500.                   *
 *              - It is greater than 400 and 450.                              *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* To keep track of the number of violated conditions.
     * Should eventually be equal to 2 for a possible solution
     * to be an actual solution. */
    int wrong;
    /* N has to be a multiple of 2, otherwise at least 5 people would be wrong.
     * N has to be a multiple of 3, otherwise at least 3 people would be wrong.
     * N has to be smaller than 750, otherwise at least 3 people would be wrong. */
    for (int N = 6; N < 750; N += 6) {
        if (N <= 400)
            wrong = 2;
        else if (N <= 450)
            wrong = 1;
        else if (N >= 550)
            wrong = 2;
        else if (N >= 500)
            wrong = 1;
        else
            wrong = 0;
        /* If N is not a multiple of 4 then it is not a multiple of 8. */
        if (N % 4 && ++wrong > 1)
                continue;
        /* If N is not a multiple of 5 then it is not a multiple of 10. */
        if (N % 5 && ++wrong > 1)
                continue;
        if (N % 7 && ++wrong > 2)
                continue;
        if (N % 8 && ++wrong > 2)
                continue;
        if (N % 9 && ++wrong > 2)
                continue;
        if (N % 10 && ++wrong > 2)
                continue;
        if (wrong == 2)
            printf("N = %d is a solution.\n", N);
    }
    return EXIT_SUCCESS;
}

