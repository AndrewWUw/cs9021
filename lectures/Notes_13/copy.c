/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the strcpy, strncpy, memcpy and memmove functions  *
 *              provided in string.h                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *const source = malloc(8 * sizeof(char));
    *source = 'a'; *(source + 1) = 'b';
    *(source + 2) = 'c'; *(source + 3) = 'd';
    *(source + 4) = '\0';
    *(source + 5) = 'e'; *(source + 6) = 'f';
    *(source + 7) = '\0';
    
    char *dest_8 = malloc(9 * sizeof(char));
    for (int i = 0; i < 8; ++i)
        *(dest_8 + i) = '0' + i;
    *(dest_8 + 8) = '\0';
    dest_8 = strcpy(dest_8, source);
    printf("New contents of dest_8: %s\n", dest_8);
    printf("Character at offset 6 from dest_8: %c\n\n", *(dest_8 + 6));

    char *dest_6 = malloc(7 * sizeof(char));
    for (int i = 0; i < 6; ++i)
        *(dest_6 + i) = '0' + i;
    *(dest_6 + 6) = '\0';
    dest_6 = strncpy(dest_6, source, 0);
    printf("New contents of dest_6: %s\n", dest_6);
    dest_6 = strncpy(dest_6, source, 3);
    printf("New contents of dest_6: %s\n\n", dest_6);

    char *const dest_9 = malloc(10 * sizeof(char));
    for (int i = 0; i < 9; ++i)
        *(dest_9 + i) = '0' + i;
    *(dest_9 + 9) = '\0';
    strncpy(dest_9, source, 8);
    printf("New contents of dest_9: %s\n", dest_9);
    printf("Character at offset 6 from dest_9: %c\n", *(dest_9 + 6));
    printf("Character at offset 7 from dest_9: %c\n", *(dest_9 + 7));
    printf("Character at offset 8 from dest_9: %c\n\n", *(dest_9 + 8));

    char *const dest_10 = malloc(11 * sizeof(char));
    for (int i = 0; i < 10; ++i)
        *(dest_10 + i) = '0' + i;
    *(dest_10 + 10) = '\0';
    memcpy(dest_10, source, 7);
    printf("New contents of dest_10: %s\n", dest_10);
    printf("Character at offset 6 from dest_10: %c\n", *(dest_10 + 6));
    printf("Character at offset 7 from dest_10: %c\n\n", *(dest_10 + 7));
   
    char *dest_7 = malloc(8 * sizeof(char));
    for (int i = 0; i < 7; ++i)
        *(dest_7 + i) = '0' + i;
    *(dest_7 + 7) = '\0';
    memmove(dest_7, dest_7 + 2, 4);
    printf("New contents of dest_7: %s\n", dest_7);

    return EXIT_SUCCESS;
}

