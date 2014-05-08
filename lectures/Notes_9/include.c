/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out a number.                                           *
 *                                                                             *
 * Purpose: Illustrates the three possible ways of using the #include command. *
  *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define STDIO <stdio.h>
#include STDIO
#include <stdlib.h>
#include "./constant.h" // Contains const int n = 10;

int main(void) {
    printf("%d\n", n);
    return EXIT_SUCCESS;
}

