/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Does not compile.                                              *
 *                                                                             *
 * Purpose: Illustrates the use of the #error directive.                       *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdlib.h>

#ifndef MACRO
#error MACRO is undefined!
#endif

int main(void) {
    return EXIT_SUCCESS;
}

