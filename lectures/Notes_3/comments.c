/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out a string literal.                                   *
 *                                                                             *
 * Purpose: Illustrates the rules that govern the use of comments.             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) { // Comments that start with // run to the end of the line
    /* Comments that start with /* contain no embedded comment,
hence can contain occurrences of /* that are just amongst the characters
that are commented out, and end at the first occurrence of */
    /* So this line consists of one comment *///immediately followed by another one.
    printf("A comment cannot be /* inserted /* in a string literal.\n");
    int n = 2+/*The preprocessor replaces each comment with a space*/+3;
    // So the previous line assigns 5 to n, whereas "int n = 2++3" would not compile.
    return EXIT_SUCCESS;
}

