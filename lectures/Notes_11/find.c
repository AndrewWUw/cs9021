/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Simulates the grep utility with options -n and -v.             *
 *                                                                             *
 * Purpose: Illustrate the use of command line arguments.                      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int getline(char *, int);

int main(int argc, char **argv) {
    char line[MAXLINE];
    long lineno = 0;
    int c, found = 0;
    bool except = false, number = false;
    
    while (--argc && **++argv == '-')
        while (c = *++*argv)
            switch(c) {
                case 'v': except = true;
                          break;
                case 'n': number = true;
                          break;
                default: printf("Illegal option %c\n", c);
                         return EXIT_FAILURE;
            }
    if (argc != 1)  // pattern is missing
        printf("Usage: find [vn] pattern\n");
    else
        while (getline(line, MAXLINE)) {
            ++lineno;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                ++found;
            }
        }
    return found;
}

int getline(char *s, int lim) {
    int i = 0;
    char c;        
    for ( ; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

