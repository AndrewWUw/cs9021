/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Implements a simple version of the tr Unix utility that can:   *
 *              - take two strings of equal length as command line arguments,  *
 *                and replace in the text provided from standard input         *
 *                all occurrences of a character given in the first string     *
 *                by the corresponding character in the second string;         *
 *              - take the -d option followed by a string, and delete          *
 *                in the text provided from standard input all occurrences     *
 *                of characters given in the string;                           *
 *              - take the -s option followed by a string, and squeeze         *
 *                in the text provided from standard input all occurrences     *
 *                of characters given in the string;                           *
 *              - take the -s option followed by two strings,                  *
 *                replace in the text provided from standard input             *
 *                all occurrences of a character given in the first string,    *
 *                by the corresponding character in the second string, and     *
 *                squeeze in the resulting text all occurrences of characters  *
 *                given in the second string.                                  *      
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_char(const int, const char *const, const int);

int main(int argc, char **argv) {
    bool translate = false, squeeze = false, delete = false;
    char *chars1, *chars2;
    if (**++argv == '-') {
        if (*++*argv == 's')
            squeeze = true;
        else if (**argv == 'd')
            delete = true;
        else {
            printf("Unknown option -%s\n", *argv);
            return EXIT_FAILURE;
        }
        ++argv;
    }
    if (delete) {
        if (argc != 3) {
            printf("-d should be followed by exactly one string.\n");
            return EXIT_FAILURE;
        }
    }
    else if (squeeze) {
        if (argc == 4)
            translate = true;
        else if (argc != 3) {
            printf("-s should be followed by one string or two.\n");
            return EXIT_FAILURE;
        }
   }
    else if (argc !=3) {
        printf("Without any option,"
               " exactly two strings should be given as arguments.\n");
        return EXIT_FAILURE;
    }
    else
        translate = true;
    chars1 = *argv;
    if (translate && strlen(chars1) != strlen(chars2 = *++argv)) {
        printf("The strings provided as arguments should have equal lengths.\n");
        return EXIT_FAILURE;
    }
    int current, previous = '\0';
    int nb_of_chars = strlen(chars1);
    while ((current = getchar()) != EOF) {
        if (delete) {
            if (find_char(current, chars1, nb_of_chars) == nb_of_chars)
                putchar(current);
            continue;
        }
        int i = find_char(current, chars1, nb_of_chars);
        if (translate) {
            if (i != nb_of_chars)
                current = chars2[i];
            if (squeeze && (i = find_char(current, chars2, nb_of_chars)) != nb_of_chars)
                current = chars2[i];
        }
        if (squeeze && i != nb_of_chars && current == previous)
            continue;
        putchar(current);
        previous = current;
    }
    return EXIT_SUCCESS;
}

int find_char(int current, const char *const chars, const int nb_of_chars) {
    for (int i = 0; i < nb_of_chars; ++i) {
        if (current == chars[i])
            return i;
    }
    return nb_of_chars;
}
        
        
    
