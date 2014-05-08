/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Multiplies an integer by 2 or 8                                *
 *              and displays integer and result.                               *
 *                                                                             *
 * Purpose: Raise awareness of the difference between the realm of computing   *
 *          and the realm of mathematics.                                      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define TEN_TO_THE_POWER_9             1000000000
#define TWO_TIMES_TEN_TO_THE_POWER_9   2000000000
#define FOUR_TIMES_TEN_TO_THE_POWER_9  4000000000

int main(void) {
    int x, y;
    
    x = TEN_TO_THE_POWER_9;
    y = 2 * x;
    printf("x = %-12d 2 * x = %d\n\n", x, y);

    x = TWO_TIMES_TEN_TO_THE_POWER_9;
    y = 2 * x;
    printf("x = %-12d 2 * x = %d\n\n", x, y);
    
    x = FOUR_TIMES_TEN_TO_THE_POWER_9;
    y = 2 * x;
    printf("x = %-12d 2 * x = %d\n", x, y);
    y = 4 * x;
    printf("                 4 * x = %d\n", y);
    y = 8 * x;
    printf("                 8 * x = %d\n", y);
    return EXIT_SUCCESS;
}

