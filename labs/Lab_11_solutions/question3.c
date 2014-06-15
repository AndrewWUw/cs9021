/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user to enter some text (possibly with spaces,     *
 *              that is, simple spaces or tabs) ending in a new line character *
 *              and behaves as follows.                                        *
 *              - If more than 30 nonspace characters are input before the     *
 *                final new line character then the program prints out         *
 *                    "Too many nonspace characters!"                          *
 *                and stops.                                                   *
 *              - Otherwise, if some nonspace character is neither a lowercase *
 *                nor an uppercase letter then the program prints out          *
 *                    "Some incorrect characters!"                             *
 *                and stops.                                                   *
 *              - Otherwise, if some word in the input (that is, maximal       *
 *                sequence of letters) consists of more than 6 letters then    *
 *                the program prints out                                       *
 *                    "Some word is too long!"                                 *
 *                and stops.                                                   *
 *              - Otherwise, if only spaces have been input then the program   *
 *                prints out                                                   *
 *                    "No word has been input!"                                *
 *                and stops.                                                   *
 *              - Otherwise, for all l in {0,1,2,3,4,5,6}, if the input        *
 *                contains some word with exactly l occurrences of uppercase   *
 *                letters then the program prints out:                         *
 *                    "Words with l upper case letters:"                       *
 *                followed by all words with l uppercase letters, output in    *
 *                the order in which they have been input.                     *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char input[30];
    int words[31];
    printf("Enter words: ");
    int i = 0;
    int word_count = -1;
    char c;
    bool incorrect_character = false;
    bool word_too_long = false;
    bool in_word = false;
    while ((c = getchar()) != '\n') {
        if (isspace(c)) {
            in_word = false;
            continue;
        }
        if (i == 30) {
            printf("Too many nonspace characters!\n");
            return EXIT_SUCCESS;
        }
        if (!isalpha(c)) {
            incorrect_character = true;
        }
        if (!in_word) {
            words[++word_count] = i;
            in_word = true;
        }
        else if (i - words[word_count] > 5)
            word_too_long = true;
        input[i++] = c;
    }
    words[++word_count] = i;
    if (incorrect_character) {
        printf("Some incorrect characters!\n");
        return EXIT_SUCCESS;
    }
    if (word_too_long) {
        printf("Some word is too long!\n");
        return EXIT_SUCCESS;
    }
    if (!word_count) {
        printf("No word has been input!\n");
        return EXIT_SUCCESS;
    }
    for (int l = 0; l < 7; ++l) {
        bool word_seen = false;
        for (int i = 0; i < word_count; ++i) {
            int p = 0;
            for (int j = words[i]; j < words[i + 1]; ++j)
                if (isupper(input[j]))
                    ++p;
            if (p == l) {
                if (!word_seen) {
                    word_seen = true;
                    printf("Words with %d upper case letters:\n", l);
                }
                printf("   ");
                for (int j = words[i]; j < words[i + 1]; ++j)
                    putchar(input[j]);
                putchar('\n');
            }
        }
    }
    return EXIT_SUCCESS;
}
