/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out a string.                                           *
 *                                                                             *
 * Purpose: Illustrates the use of ... and __VAR_ARGS__ in the definition      *
 *          of macros expected to accept a variable number of arguments.       *
  *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define PRINT(stream, ...) fprintf(stream, "It is well known that " __VA_ARGS__)

int main(void) {
    PRINT(stdout, "%d plus %d equals %d.\n", 2, 3, 5);
    return EXIT_SUCCESS;
}

