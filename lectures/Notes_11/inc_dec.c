/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out values obtained by derefencing pointers.            *
 *                                                                             *
 * Purpose:  Illustrate how the dereference operator operates together with    *
 *           the increment operator.                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *          
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int data[2] = {100, 200};
int moredata[2] = {300, 400};

int main(void) {
    int *p1, *p2, *p3;
    p1 = p2 = data;
    p3 = moredata;
    printf("  *p1 = %d,   *p2 = %d,     *p3 = %d\n",
            *p1     ,   *p2     ,     *p3);
    printf("*p1++ = %d, *++p2 = %d, (*p3)++ = %d\n",
          *p1++     , *++p2     , (*p3)++);
    printf("  *p1 = %d,   *p2 = %d,     *p3 = %d\n",
            *p1     ,   *p2     ,     *p3);
    return EXIT_SUCCESS;
}

