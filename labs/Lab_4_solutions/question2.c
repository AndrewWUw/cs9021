/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Outputs                                                        *
 *              - the number of blank characters (spaces, tabs and new lines)  *
 *              - the length of the shortest word                              *
 *                (any sequence of nonblank characters), and                   *
 *              - the length of the longest word                               *
 *                (any sequence of nonblank characters)                        *
 *              read from standard input.                                      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int nb_of_blank_chars = 0;
    int min_length = 0, max_length = 0, current_length = 0;
    /* Character being read */
    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            ++nb_of_blank_chars;
            /* A complete word has just been read iff current_length > 0,
             * which is then the length of that word. */    
            if (current_length) {
                if (min_length == 0 || current_length < min_length)
                    min_length = current_length;
                if (current_length > max_length)
                    max_length = current_length;
                current_length = 0;
            }
        }
        else
            ++current_length;
    }
    printf("Input contains %d blanks, tabs and new lines\n", nb_of_blank_chars);
    if (min_length == 0)
        printf("No word has been input\n");
    else {
        printf("Length of shortest word: %d\n", min_length);
        printf("Length of longest word: %d\n", max_length);
    }
    return EXIT_SUCCESS;
}
