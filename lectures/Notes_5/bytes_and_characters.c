/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Outputs the number of bytes allocated to some of the types     *
 *              meant to represent characters                                  *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("There is %zd byte in a plain char.\n", sizeof(char));
    printf("There is %zd byte in a signed char.\n", sizeof(signed char));
    printf("There is %zd byte in an unsigned char.\n", sizeof(unsigned char));
    return EXIT_SUCCESS;
}

