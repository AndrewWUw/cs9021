/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Modifies the elements of an array passed as argument           *
 *              to a function and prints out its elements                      *
 *                                                                             *
 * Purpose: Illustrate the use of const to prevent the modification of         *
 *          the elements of an array passed as argument.                       *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

void show_array(const double *, int);
void mult_array(double *, int, double);

int main(void) {
    double array[SIZE] = {20.0, 17.66, 8.2, 15.3, 22.22};

    printf("The original array:\n");
    show_array(array, SIZE); 
    mult_array(array, SIZE, 2.5);
    printf("The array  after calling mult_array():\n");
    show_array(array, SIZE);
    return EXIT_SUCCESS;
}

void show_array(const double *ar, int n) {
    for (int i = 0; i < n; ++i)
        printf("%8.3f ", ar[i]);
    putchar('\n');
}

void mult_array(double *ar, int n, double mult) {
    for (int i = 0; i < n; ++i)
        ar[i] *= mult;
}
