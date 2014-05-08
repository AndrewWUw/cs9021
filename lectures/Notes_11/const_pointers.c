/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Does not compile.                                              *
 *              Change from a constant pointer to an int to a pointer          *
 *              to a constant int to make it compile.                          *
 *                                                                             *
 * Purpose: Illustrates the use of const applied to pointers.                  *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

void modify(const int *);

int main(void) {
    int a[] = {1, 2, 3};
    modify(a);
    return EXIT_SUCCESS;
}

void modify(const int *ar) {
    *ar = 10;
}
