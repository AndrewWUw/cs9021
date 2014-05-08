/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Passes an array as an argument to a function,                  *
 *              and prints out size of array and size of argument,             *
 *              together with the result of an operation on the array.         *
 *                                                                             *
 * Purpose: Illustrate that arrays are cast to pointers when passed as args.   *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int sum(int *, int);

int main(void) {
    int array[SIZE] = {20, 10, 5, 39, 4, 16, 19, 26, 31, 20};
    int answer = sum(array, SIZE);
    printf("Sum of members of array: %d.\n", answer);
    printf("The size of array is %lu bytes.\n", sizeof array);
    return EXIT_SUCCESS;
}

int sum(int *ar, int n) {
    int total = 0;
    for(int i = 0; i < n; ++i)
        total += ar[i];
    printf("The size of ar is %lu bytes.\n", sizeof ar);
    return total;
}
