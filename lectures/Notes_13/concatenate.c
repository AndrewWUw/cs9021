/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the strcat and strncat functions                   *
 *              provided in string.h                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char end[] = "abcd";

    char start_0[10] = "";
    strcat(start_0, end);
    printf("New contents of start_0: %s\n", start_0);
    char start_5[10] = "12345";
    strcat(start_5, end);
    printf("New contents of start_5, which should not be larger: %s\n\n", start_5);

    char start_4[10] = "1234";
    strncat(start_4, end, 0);
    printf("New contents of start_4: %s\n", start_4);
    strncat(start_4, end, 5);
    printf("New contents of start_4: %s\n", start_4);
    char start_3[10] = "123";
    strncat(start_3, end, 2);
    printf("New contents of start_3: %s\n", start_3);
    
    return EXIT_SUCCESS;
}

