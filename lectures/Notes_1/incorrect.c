/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: This program is syntactically incorrect.                       *
 *              It fails to compile.                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    integer n = 2;
    integer m = 3;
    integer sum = n + m;
    printf("The sum of %d and %d is: %d", n, m, sum);
    return EXIT_SUCCESS;
}

