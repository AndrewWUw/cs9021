/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out a string literal.                                   *
 *                                                                             *
 * Purpose: Illustrate escaped new line and string concatenation.              *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    prin\
tf("The end of line character can be escaped with a backslah,\
 anywhere, including in string literals.\n");
    printf("But a better way to include long string literals in source files"
           " is to take advantage\nof the fact that the preprocessor concatenates"
           " successive"" "     "string literals.\n");
    return EXIT_SUCCESS;
}

