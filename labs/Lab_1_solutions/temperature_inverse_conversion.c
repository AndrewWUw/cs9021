/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out a conversion table of temperatures from  celsius    *
 *              to fahrenheit degrees, with the former ranging from 0 to 100   *
 *              in steps of 10.                                                *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int lower = 0, upper = 100, step = 10;
    printf("celsius\tfahr\n");
    for (int celsius = lower; celsius <= upper; celsius += step) {
        /* As the possible values of celsius are multiples of 5,
         * fahr can be declared as an int and computations over ints are ok. */
        int fahr = celsius / 5 * 9 + 32;
        printf("%d\t%d\n", celsius, fahr);
    }
    return EXIT_SUCCESS;
}
