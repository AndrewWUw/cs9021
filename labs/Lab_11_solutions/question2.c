/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes as input letters and spaces, possibly over many lines,   *
 *              with carriage return followed by Control D indicating the end  *
 *              of input, and displays the output as follows.                  *
 *              - If some word (maximal sequence of  consecutive letters)      *
 *                in the input contains more than 10 letters then the program  *
 *                outputs an error message.                                    *
 *              - Otherwise, if no word has been input then the program        *
 *                outputs another error message.                               *
 *              - Otherwise, the program announces the `winner' and outputs,   *
 *                amongst the words of maximal length, the one that comes last *
 *                in alphabetical order as given by the ASCII character set    *
 *                (where uppercase letters come before lowercase letters).     *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* x will store the current best word, and y the last word. */
    char x[10], y[10];
    /* Length of the currrent longest word, that will be set to 11
     * if some word has more than 10 letters. */
    int length = 0;
    int c;
    int i = 0;
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            if (i == 10) {
                length = 11;
                /* Eat up all remaining characters to avoid that program exits
                 * before it EOF is reached. */
                while ((c = getchar()) != EOF)
                    ;
                break;
            }
            y[i++] = c;
        }
        else {
            if (i > length) {
                length = i;
                memcpy(x, y, length);
            }
            else if (i == length && memcmp(x, y, length) < 0)
                memcpy(x, y, length);
            i = 0;
        }
    }
    if (length == 11)
        printf("Some word is too long!\n");
    else if (!length)
        printf("No word has been input!\n");
    else {
        printf("The winner is: ");
        for (int i = 0; i < length; ++i)
            putchar(x[i]);
        putchar('\n');
    }
    return EXIT_SUCCESS;
}
