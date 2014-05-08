/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out two string literals.                                *
 *                                                                             *
 * Purpose: Illustrates the use of single and double number signs              *
 *          in the definition of macro definitions,                            *
 *          # to surround the argument by double quotes and replace            *
 *          any sequence of spaces by a single space,                          *
 *          and ## to merge tokens.                                            *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define PRINT(x) printf(#x#x    #x"\n");
#define PR(x) pr ## x

int main(void) {
    PRINT(*    !);
    PR(intf("***\n"));
    return EXIT_SUCCESS;
}

