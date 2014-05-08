/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Performs assignments between different types.                  *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const float x1 = 1e-30;               /* A double assigned to a float */
    printf("x1: %e\n", x1);
    const float y1 = 1e-70;               /* A double assigned to a float */    
    printf("y1: %e\n", y1);
    const long double z1 = 1e-70;         /* A double assigned to a long double */
    printf("z1: %Le\n\n", z1);

    const float x2 = 1e30;               /* A double assigned to a float */
    printf("x2: %e\n", x2);
    const float y2 = 1e70;               /* A double assigned to a float */    
    printf("y2: %e\n", y2);
    const long double z2 = 1e70;         /* A double assigned to a long double */
    printf("z2: %Le\n", z2);
    return EXIT_SUCCESS;
}

