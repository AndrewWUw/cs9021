/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out addresses and values.                               *
 *                                                                             *
 * Purpose: Illustrates some operations on pointers.                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int array[] = {100, 200, 300};
    int *ptr1 = array; 
    int *ptr2 = &array[2];
    printf("ptr1 = %p, *ptr1 =%d, &ptr1 = %p\n", ptr1, *ptr1, &ptr1);
    ptr1++;            
    printf("values after ptr1++\n");
    printf("ptr1 = %p, *ptr1 =%d, &ptr1 = %p\n", ptr1, *ptr1, &ptr1);
    printf("ptr2 = %p, *ptr2 =%d, &ptr2 = %p\n", ptr2, *ptr2, &ptr2);
    ptr2--;
    printf("values after --ptr2\n");
    printf("ptr2 = %p, *ptr2 = %d, &ptr2 = %p\n", ptr2, *ptr2, &ptr2);
    --ptr1;
    ++ptr2;   
    printf("ptr2 - ptr1 = %d\n", ptr2 - ptr1);
    return EXIT_SUCCESS;
}

