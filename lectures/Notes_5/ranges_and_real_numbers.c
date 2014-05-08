/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Outputs some information associated with the types             *
 *              meant to represent real numbers                                *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("The minimum normalised positive float is %e.\n", FLT_MIN);
    printf("The maximum positive integer that can be represented by a float is %.0f.\n", FLT_MAX);
    printf("The number of bits in the mantissa of a float is %d\n", FLT_MANT_DIG);
    printf("The number of decimal digits of precision of a float is %d\n\n", FLT_DIG);
    
    printf("The minimum normalised positive double is %le.\n", DBL_MIN);
    printf("The maximum positive integer that can be represented by a double is %.0lf.\n", DBL_MAX);
    printf("The number of bits in the mantissa of a double is %d\n", DBL_MANT_DIG);
    printf("The number of decimal digits of precision of a double is %d\n\n", DBL_DIG);

    printf("The minimum normalised positive long double is %Le.\n", LDBL_MIN);
    printf("The maximum positive integer that can be represented by a long double is %.0Lf.\n", LDBL_MAX);
    printf("The number of bits in the mantissa of a long double is %d\n", LDBL_MANT_DIG);
    printf("The number of decimal digits of precision of a long double is %d\n\n", LDBL_DIG);
return EXIT_SUCCESS;
}

