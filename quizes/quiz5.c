/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Randomly fills an array of size 10x10 with 0s and 1s, and      *
 *              outputs the number of parallelograms with horizonatal sides.   *
 *                                                                             *
 * Written by Eric Martin and *** for COMP9021                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 10
#define STRAIGHT 0
#define LEFT -1
#define RIGHT 1

bool grid[DIM][DIM];

//bool grid[DIM][DIM] = {
//        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
//        {0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {1, 0, 0, 0, 0, 1, 0, 1, 1, 0},
//        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
//        {0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
//        {0, 0, 0, 0, 1, 1, 0, 0, 1, 0},
//        {0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
//        {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
//        };
//
//bool grid[DIM][DIM] = {
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//};
//
//bool grid[DIM][DIM] = {
//        {0, 1, 1, 0, 1, 1, 0, 1, 0, 1},
//        {0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
//        {0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
//        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
//        {0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
//        {0, 0, 0, 0, 1, 0, 1, 1, 1, 0},
//        {0, 0, 1, 1, 0, 0, 1, 1, 0, 1},
//        {1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
//        {1, 1, 0, 0, 1, 0, 1, 1, 1, 1},
//        {0, 1, 0, 1, 1, 0, 0, 1, 1, 1},
//};
//
//bool grid[DIM][DIM] = {
//                {1, 1, 1, 0, 0, 0, 0, 0, 1, 1}, {
//                0 ,1 ,0, 0, 1, 1, 1, 1, 0, 0}, {
//                1 ,1 ,1, 1, 0, 1, 1, 0, 0, 1}, {
//                1 ,0 ,0, 1, 0, 1, 1, 1, 1, 1}, {
//                1 ,0 ,1, 0, 1, 1, 0, 1, 0, 1}, {
//                1 ,1 ,0, 0, 0, 0, 0, 0, 0, 1}, {
//                0 ,0 ,1, 0, 1, 1, 1, 0, 0, 1}, {
//                0 ,1 ,1, 1, 1, 0, 1, 0, 1, 1}, {
//                1 ,0, 1, 1, 1, 1, 1, 0, 1, 0}, {
//                0 ,1, 1, 0, 0, 0, 0, 1, 0, 0}
//};
//
//bool grid[DIM][DIM] = {
//                {1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, {
//                0, 1, 0, 1, 0, 1, 1 ,1, 1 ,1}, {
//                0, 1, 0, 1, 1, 0, 0 ,0, 1 ,1}, {
//                1, 1, 1, 1, 1, 0, 1 ,1, 0 ,0}, {
//                1, 1, 1, 0, 1, 1, 1 ,1, 0 ,1}, {
//                1, 1, 1, 1, 1, 1, 0 ,1, 0 ,1}, {
//                1, 1, 0, 1, 1, 1, 0 ,0, 0 ,1}, {
//                1, 1, 1, 1, 0, 1, 1 ,0, 1 ,1}, {
//                0, 1, 0, 1, 1, 1, 0 ,1, 0 ,0}, {
//                0, 1, 1, 1, 0, 1, 1 ,0, 1 ,0}
//};
//
//bool grid[DIM][DIM] = {
//        {0, 0, 1, 1, 0, 1, 0, 1, 1, 1},{
//                1, 0, 1, 0, 0, 0, 1, 0, 1, 0},{
//                1, 1, 0, 1, 1, 0, 0, 0, 1, 1},{
//                1, 1, 1, 0, 1, 1, 0, 1, 1, 1},{
//                1, 1, 1, 1, 0, 0, 0, 1, 1, 1},{
//                1, 1, 1, 1, 1, 0, 1, 1, 1, 0},{
//                1, 0, 0, 1, 1, 1, 1, 0, 1, 0},{
//                0, 1, 1, 1, 0, 1, 1, 0, 1, 1},{
//                1, 0, 0, 1, 1, 0, 1, 1, 1, 1},{
//                1, 1, 1, 0, 0, 1, 1, 1, 1, 1}
//};
//
//bool grid[DIM][DIM] = {
//        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

void display_grid(void);
int size_of_largest_parallelogram(void);
int size_of_largest_parallelogram_with_given_top_side(int i, int j1, int j2, int dir);
int find_longest_one(int i, int j);
int find_largest_size_in_one_position(int i, int j, int length);

int main(int argc, char **argv) {
    /* We run the program with two command line arguments. */
    if (argc != 3) {
        printf("Please provide 2 command line arguments.\n");
        return EXIT_FAILURE;
    }
    /* The first one will determine our probability distribution;
     * it is meant to be nonzero. */
    int nb_of_possible_outcomes = strtol(argv[1], NULL, 10); // convert string to long int
    if (!nb_of_possible_outcomes) {
        printf("The first command line argument should not be 0.\n");
        return EXIT_FAILURE;
    }
    /* We use the second command line argument, meant to be a nonnegative integer,
     * as a seed for the random number generator. */
    srand(strtoul(argv[2], NULL, 10));
    /* We fill the grid with randomly generated 0s and 1s,
     * with for every cell, a probability of 1/nb_of_possible_outcomes to generate a 0. */
    if (nb_of_possible_outcomes > 0)
        for (int i = 0; i < DIM; ++i)
            for (int j = 0; j < DIM; ++j)
                grid[i][j] = rand() % nb_of_possible_outcomes > 0;
    else {
        for (int i = 0; i < DIM; ++i)
            for (int j = 0; j < DIM; ++j)
                grid[i][j] = rand() % nb_of_possible_outcomes == 0;
    }
    puts("Here is the grid that has been generated:\n");
    display_grid();

    int size = size_of_largest_parallelogram();
    if (size)
        printf("The largest parallelogram with horizontal sides has a size of %d.\n", size_of_largest_parallelogram());
    else
        printf("There is no parallelogram with horizontal sides.\n");
    return EXIT_SUCCESS;
}

void display_grid(void) {
    for (int i = 0; i < DIM; ++i) {
        printf("    ");
        for (int j = 0; j < DIM; ++j)
            printf(" %d", grid[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

int size_of_largest_parallelogram(void) {
    int sizeArray[DIM] = { 0 };
    for (int i = 0; i < DIM; i++) {
        int size = 0;
        for (int j = 0; j < DIM; j++) {
            // for every position that grid[i][j] == 1, find the longest length of '1's,
            // then try to find the largest size in this position
            // in the last, save the largest size in this line to sizeArray[i]
            int length = 0;
            if (grid[i][j] == 1) {
                int temp = 0;
                length = find_longest_one(i, j) - 1;
                temp = find_largest_size_in_one_position(i, j, length);
                if (temp > size) {
                    size = temp;
                }
                j += length;
            } else {
                length = 0;
            }
        }
        // a parallelogram can't have the size of 1/2/3
        if (size < 4) {
            size = 0;
        }
        sizeArray[i] = size;
    }

    int size = 0;
    for (int i = 0; i < DIM; i++) {
        if (size < sizeArray[i]) {
            size = sizeArray[i];
        }
    }
    return size;
}

/*******************************************************************************************
 * If j1 < j2 and the grid has a 1 at the intersection of row i and column j
 * for all j in {j1, ..., j2}, then returns the side of the largest parallelogram
 * having this row of 1s as top side, and with vertical sides going down in 1 of 3 possible
 * directions as selected by dir.
 */
int size_of_largest_parallelogram_with_given_top_side(int i1, int j1, int j2, int dir) {

    int size = j2 - j1 + 1;
    for (int j = j1; j <= j2; ++j) {
        if (grid[i1][j] != 1) {
            return 0;
        }
    }
    switch (dir) {
    case STRAIGHT:
        if (i1 < DIM - 1) {
            size = size + size_of_largest_parallelogram_with_given_top_side(i1 + 1, j1, j2, STRAIGHT);
        }
        break;
    case LEFT:
        if (i1 < DIM - 1 && j1 > 0) {
            size = size + size_of_largest_parallelogram_with_given_top_side(i1 + 1, j1 - 1, j2 - 1, LEFT);
        }
        break;
    case RIGHT:
        if (i1 < DIM - 1 && j2 < DIM - 1) {
            size = size + size_of_largest_parallelogram_with_given_top_side(i1 + 1, j1 + 1, j2 + 1, RIGHT);
        }
        break;
    }
    return size;
}

int find_longest_one(int i, int j) {
    int length = 0;
    for (int k = j; k < DIM; k++) {
        if (grid[i][k] == 1) {
            length++;
        } else
            break;
    }
    return length;
}

int find_largest_size_in_one_position(int i, int j, int length) {
    int size = 0;
    for (int k = j; k <= j + length; k++) {
        int temp = 0;
        temp = size_of_largest_parallelogram_with_given_top_side(i, j, k,STRAIGHT);
        if (size  < size_of_largest_parallelogram_with_given_top_side(i, j, k, LEFT)) {
            temp = size_of_largest_parallelogram_with_given_top_side(i, j, k, LEFT);
        }
        if (size < size_of_largest_parallelogram_with_given_top_side(i, j, k, RIGHT)) {
            temp = size_of_largest_parallelogram_with_given_top_side(i, j, k, RIGHT);
        }
        if (temp > size) {
            size = temp;
        }
    }
    return size;
}
