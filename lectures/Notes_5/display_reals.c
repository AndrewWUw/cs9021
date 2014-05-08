/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Displays 1200.75 in a number of different ways.                *
 *                                                                             *
 * Purpose: Illustrates the conversion specifications of printf()              *
 *          when displaying real numbers.                                      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define FINE 1200.75

int main(void) {
    printf("*%f* *%2f* *%15f* *%-15f* *%015f*\n", FINE, FINE, FINE, FINE, FINE);
    printf("*%.2f* *% .2f* *%15+.2f* *%015+.2f*\n", FINE, FINE, FINE, FINE);
    printf("*%e* *%.3e* *%15e* *%-15E* *%015E*\n", FINE, FINE, FINE, FINE, FINE);
    printf("*%.1g* *%.2g* *%15+.3G* *%15+.4G* *%015+.2G*\n", FINE, FINE, FINE, FINE, FINE);
    return EXIT_SUCCESS;
}

