/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the strcmp, strncmp and memcmp functions           *
 *              provided in string.h                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char *const s0 = "1234";
    const char *const s1 = "1234";
    const char *const s2 = "124";
    const char *const s3 = "12345";
    printf("Comparing s0 to s1 as addresses: %d\n", s0 == s1);
    printf("Comparing s0 to s1 as strings: %d\n", strcmp(s0, s1));
    printf("Comparing s1 to s2: %d\n", strcmp(s1, s2));
    printf("Comparing s3 to s1: %d\n", strcmp(s3, s1));
    printf("Comparing at most first 3 characters of s1 and s3: %d\n", strncmp(s1, s3, 3));
    printf("Comparing at most first 4 characters of s1 and s3: %d\n", strncmp(s1, s3, 4));
    printf("Comparing at most first 5 characters of s1 and s3: %d\n", strncmp(s1, s3, 5));
    printf("Comparing at most first 6 characters of s1 and s3: %d\n\n", strncmp(s1, s3, 6));

    char *const s4 = malloc(6 * sizeof(char));
    char *const s5 = malloc(6 * sizeof(char));
    for (int i = 0; i < 3; ++i)
        *(s4 + i) = *(s5 + i) = i;
    *(s4 + 3) = *(s5 + 3) = *(s5 + 4) = '\0';
    *(s4 + 4) = '3'; *(s4 + 5) = '4';
    *(s5 + 5) = '5';
    printf("Comparing at most 6 characters of s4 and s5 treated as strings: %d\n",
           strncmp(s4, s5, 6));
    printf("Comparing 6 characters of s4 and s5 treated as contents of memory: %d\n",
           memcmp(s4, s5, 6));
    return EXIT_SUCCESS;
}

