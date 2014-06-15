/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user to input on the next line a sequence of       *
 *              letters, blanks (simple spaces or tabs) and punctuation marks  *
 *              (commas, full stops, colons, question marks or exclamation     *
 *              marks) and displays the output as follows.                     *
 *              - Words (maximal nonempty sequences of consecutive letters)    *
 *                have their first letter displayed in upper case and the      *
 *                remaining letters in lower case.                             *
 *              - Any punctuation mark that does not follow a word with        *
 *                possibly spaces in-between is ignored.                       *
 *              - Any punctuation mark that follows a word with possibly       *
 *                spaces in-between is displayed next to the word.             *
 *              - Successive words with possibly a punctation mark attached    *
 *                to their ends are separated by a single space.               *
 *              - The first word, if any, is not preceded by any space.        *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Enter a sequence of letters, blanks and punctuation marks on one line:\n");
    int c;
    bool in_word = false, word_seen = false, punct_seen = false;
    while ((c = getchar()) != '\n') {
        if (ispunct(c)) {
            if (!punct_seen && word_seen) {
                putchar(c);
                punct_seen = true;
            }
            in_word = false;
        }
        else if (isalpha(c)) {
            if (!in_word) {
                if (word_seen)
                    putchar(' ');
                putchar(toupper(c));
                in_word = true;
            }
            else
                putchar(tolower(c));
            word_seen = true;
            punct_seen = false;
        }
        else
            in_word = false;
    }
    putchar('\n');
    return EXIT_SUCCESS;
}
