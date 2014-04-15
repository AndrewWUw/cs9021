/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Reads a line of input and transforms it in some way...         *
 *                                                                             *
 * Written by Eric Martin and *** for COMP9021                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int smain(void) {
    int largest_digit = 0;
    char beginning_of_word[8];
    int minimal_length = 0;
    bool fully_processed_previous_word = true;
    int word_length = 0;
    int c;
    
    char input[999999];
    int length = 0;
        
    while ((c = getchar()) != '\n') {
    /* ... REPLACE THIS COMMENT WITH YOUR CODE ... */
        input[length++] = c;
    }
    if (word_length && word_length >= minimal_length)
        printf(".\n");
    return EXIT_SUCCESS;
}

