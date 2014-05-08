/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Sums the rows and columns of a 2-dimentional array.            *
 *                                                                             *
 * Purpose: Illustrates passing multi-dimensional arrays to functions.         *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#define ROWS 3
#define COLUMNS 4

void sum_rows(int (*)[COLUMNS], int);
void sum_cols(int (*)[COLUMNS], int);

int main(void) {
    int array[ROWS][COLUMNS] = {{2, 4, 6, 8},
                             {3, 5, 7, 9},
                             {12, 10, 8, 6}};    
     sum_rows(array, ROWS);
     sum_cols(array, ROWS);
     return EXIT_SUCCESS;
}

void sum_rows(int (*ar)[COLUMNS], int nb_of_rows) {
    for (int row = 0; row < nb_of_rows; ++row) {
        int total = 0;
        for (int column = 0; column < COLUMNS; ++column)
            total += ar[row][column];
        printf("row %d: sum = %d\n", row, total);
    }
}

void sum_cols(int (*ar)[COLUMNS], int nb_of_rows) {
    for (int column = 0; column < COLUMNS; ++column) {
        int total = 0;
        for (int row = 0; row < nb_of_rows; ++row)
            total += ar[row][column];
        printf("col %d: sum = %d\n", column, total);
    }
}

