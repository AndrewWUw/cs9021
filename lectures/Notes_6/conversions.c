/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Performs some arithmetic operations that illustrate            *
 *              the conversion rules.                                          *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const double i = FLT_MAX;
    const double j = 2 * 3.40282347e+38;
    const double k = 3.40282347e+38F;
    const double l = 2 * FLT_MAX;
    const double m = 2 * 3.40282347e+38F;
    printf("FLT_MAX = %le\n", FLT_MAX);
    printf("2 * i = %le\n", 2 * i);
    printf("j = %le\n", j);
    printf("2 * k = %le\n", 2 * k);
    printf("l = %le\n", l);
    printf("m = %le\n\n", m);
    return EXIT_SUCCESS;
}

