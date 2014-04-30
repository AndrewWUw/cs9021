/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Reads a line of input and transforms it in some way...         *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void) {
    int largest_digit = 0;
    char beginning_of_word[8];
    int minimal_length = 0;
    bool fully_processed_previous_word = true;
    int word_length = 0;
    int c;
    while ((c = getchar()) != '\n') {
        if (isdigit(c)) {
            if (c - '0' > largest_digit)
                largest_digit = c - '0';
            if (word_length)
                fully_processed_previous_word = false; 
        }
        else if (isalpha(c)) {
            if (!fully_processed_previous_word) {
                if (word_length >= minimal_length)
                    printf(".\n");
                fully_processed_previous_word = true;
                word_length = 0;
                minimal_length = 0;
            }
            if (largest_digit) {
                minimal_length = largest_digit;
                largest_digit = 0;
            }
            if (word_length + 1 < minimal_length)
                beginning_of_word[word_length++] = tolower(c);
            else {
                if (++word_length == minimal_length)
                    for (int i = 0; i < minimal_length - 1; ++i)
                        putchar(beginning_of_word[i]);
                putchar(tolower(c));
            }
        }
        else if (ispunct(c)) {
            if (word_length && word_length >= minimal_length)
                printf("%c\n", c);
            fully_processed_previous_word = true;
            word_length = 0;
            minimal_length = 0;
        }
        else if (word_length)
            fully_processed_previous_word = false;
    }
    if (word_length && word_length >= minimal_length)
        printf(".\n");
    return EXIT_SUCCESS;
}

