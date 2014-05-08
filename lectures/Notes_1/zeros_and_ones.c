/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Declares and initializes a variable of type int                *
 *              and displays its name, its value, its address, and             *
 *              the internal representation of its value.                      *
 *                                                                             *
 * Purpose: Illustrates how to see addresses and bits.                         *
 *          Not meant to be fully understood at this stage, but gives an       *
 *          introduction on how to access bits stored in memory.               *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void show_byte(const char *const);

int main(void) {
    printf("There are %d bits in a byte\n", CHAR_BIT);
    printf("There are %zd bytes in an int\n\n", sizeof(int));
    /* Give distance, declared as a variable of type int,
     * the value 8 + (7 x 2^8) + (6 x 2^16) + (5 x 2^24). */
    int distance = 8 +
                   7 * pow(2, CHAR_BIT) +
                   6 * pow(2, 2 * CHAR_BIT) +
                   5 * pow(2, 3 * CHAR_BIT);
    printf("Value of distance:                            %d\n", distance);
    printf("Location where distance stores its value:     %p\n", &distance);
    printf("Bits stored at that location:                 ");
    for (int i = 0; i < sizeof(int); ++i) {
        /* (char *)&distance + i is the location i bytes to the right
         * of the location where distance stores its value. */
        show_byte((char *)&distance + i);
        /* Insert a space after a byte has been processed, to make the output more readable. */
        putchar(' ');
    }    
    putchar('\n');
    return EXIT_SUCCESS;
}

void show_byte(const char *const p) {
    for (int i = 1; i <= CHAR_BIT; ++i)
        /* *p & 1 << CHAR_BIT - i is a value represented by a sequence of 8 bits
         * all equal to 0, except possibly for the ith bit, equal to the value of the bit
         * i - 1 bits to the right of location p. */
        printf("%d", (*p & 1 << CHAR_BIT - i) != 0);
}

