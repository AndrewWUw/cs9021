/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the strlen function provided in string.h           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("Length of \"\": %zd\n", strlen(""));
    printf("Length of \"\\0\": %zd\n", strlen("\0"));
    char s[] = "123";
    printf("Length of %s: %zd\n", s, strlen(s));
    return EXIT_SUCCESS;
}

