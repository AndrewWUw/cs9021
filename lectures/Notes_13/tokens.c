/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the strtok function                                *
 *              provided in string.h                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char string[] = "989abc01ed223fgh123\"''456ij\"?kl789??";
    const char first_separators[] = "0123456789";
    const char second_separators[] = "\"'?";
    const char *token = strtok(string, first_separators);
    printf("First token: %s\n", token);
    token = strtok(NULL, first_separators);
    printf("Second token: %s\n", token);
    token = strtok(NULL, second_separators);
    printf("Third token: %s\n", token);
    token = strtok(NULL, second_separators);
    printf("Fourth token: %s\n", token);
    token = strtok(NULL, second_separators);
    printf("Fifth token: %s\n", token);
    token = strtok(NULL, second_separators);
    printf("%p\n", token);
    return EXIT_SUCCESS;
}

