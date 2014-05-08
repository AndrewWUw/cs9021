/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Performs assignments between different types.                  *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const short x1 = 10;                   /* An int assigned to a short */
    printf("x1: %d\n", x1);
    const long long int y1a = x1;          /* A short assigned to a long long */    
    printf("y1a: %Ld\n", y1a);
    const unsigned long long y1b = x1;     /* A short assigned to an unsigned long long */
    printf("y1b: %Lu\n\n", y1b);

    const short x2 = -20;                  /* An int assigned to a short */
    printf("x2: %hd\n", x2);
    const long long int y2a = x2;          /* A short assigned to a long long */    
    printf("y2a: %Ld\n", y2a);
    const unsigned long long y2b = x2;     /* A short assigned to an unsigned long long */
    printf("y2b: %llu\n\n", y2b);

                                     /* An unsigned long long assigned to an unsigned short */
    const unsigned short y3 = 12345678901234567890;
    printf("y3:  %hu\n", y3);
    return EXIT_SUCCESS;
}

