/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out three string literals.                              *
 *                                                                             *
 * Purpose: Illustrates the use of macros to redefine functions                *
 *          and the use of the #undef command.                                 *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("*\n");
#define printf(string) printf("*"string);
    printf("*\n");
#undef printf;
    printf("*\n");
    return EXIT_SUCCESS;
}

