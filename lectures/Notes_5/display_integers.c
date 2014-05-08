/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Displays 2008 in a number of different ways.                   *
 *                                                                             *
 * Purpose: Illustrates the conversion specifications of printf()              *
 *          when displaying integers.                                          *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define YEAR 2011

int main(void) {
    printf("*%d* *%2d* *%8d* *%-8d* *%0+8d*\n", YEAR, YEAR, YEAR, YEAR, YEAR);
    printf("*%.2d* *%.6d* *% .6d* *%10+.6d*\n", YEAR, YEAR, YEAR, YEAR, YEAR);
    printf("*%o* *%#o* *%x0* *%#XO* \n", YEAR, YEAR, YEAR, YEAR);
    return EXIT_SUCCESS;
}

