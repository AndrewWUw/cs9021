/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes as input a grid of size 13 x 13 delimited with           *
 *              # symbols. Consecutive # symbols are separated by a space      *
 *              in the horizontal dimension, but not in the vertical           *
 *              dimension. The grid possibly contains a number of * symbols    *
 *              at the intersection of horizontal and vertical lines that go   *
 *              through # symbols, and no other symbols anywhere else.         *
 *              Outputs how many horizontal, vertical and diagonal lines       *
 *              made up of (at least 2) * symbols are contained in the grid.   *
 *                                                                             *
 * Usage: Data is meant to be read from standard input,                        *
 *        hence if grid is stored in file filename, program should be run as   *
 *        a.out <filename                                                      *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 11

bool grid[DIM][DIM];

bool process_data(void);
bool process_line_of_data(const int, const int);
int nb_of_horizontal_lines(void);
int nb_of_vertical_lines(void);
int nb_of_diagonal_lines(void);

int main(void) {
    if (!process_data()) {
        printf("Incorrect grid.\n");
        return EXIT_FAILURE;
    }
    puts("The grid contains");
    int n = nb_of_horizontal_lines();
    printf("  - %d horizontal line", n), n == 1 ? puts("") : puts("s");
    n = nb_of_vertical_lines();
    printf("  - %d vertical line", n), n == 1 ? puts("") : puts("s");
    n = nb_of_diagonal_lines();
    printf("  - %d diagonal line", n), n == 1 ? puts("") : puts("s");
    return EXIT_SUCCESS;
}

bool process_data(void) {
    int c;
    /* offset is the number of spaces before the #s
     * that make up the left border of the grid. */
    int offset = 0;
    while (isspace(c = getchar()))
        /* Go over all blank lines that precede the top border of the grid. */
        if (c == '\n')
            offset = 0;
        else
            ++offset;
    if (c == '#') {
        /* Check that the top border of the grid is correct, ... */
        for (int j = 0; j <= DIM; ++j)
            if (getchar() != ' ' || getchar() != '#')
                return false;
        /* ... with at the end, an arbitrary amount of white space allowed. */
        while (isblank(c = getchar()))
            ;
        if (c != '\n')
            return false;
        for (int i = 0; i < DIM; ++i)
            if (!process_line_of_data(offset, i))
                return false;
    }
    /* Check that the bottom border of the grid starts where it should, ... */
    for (int j = 0; j < offset; ++j)
        if (!isspace(getchar()))
            return false;
    /* ... is correct, ... */
    if (getchar() != '#')
        return false;
    for (int j = 0; j <= DIM; ++j)
        if (getchar() != ' ' || getchar() != '#')
            return false;
    /* ... with at the end, an arbitrary amount of white space allowed. */
    while (isspace(c = getchar()))
        ;
    if (c != EOF)
        return false;
    return true;
}

bool process_line_of_data(const int offset, const int i) {
    /* Check that the this line of the grid starts where it should, ... */
    for (int j = 0; j < offset; ++j)
        if (!isspace(getchar()))
            return false;
    if (getchar() != '#')
        return false;
    int c;
    /* ... is correct, and record its contents ... */
    for (int j = 0; j < DIM; ++j) {
        if (getchar() != ' ')
            return false;
        if (isblank(c = getchar()))
            grid[i][j] = false;
        else if (c == '*')
            grid[i][j] = true;
        else
            return false;
    }
    /* ... till the right border is reached, ... */
    if (getchar() != ' ' || getchar() != '#')
        return false;
    /* ... with an arbitrary amount of white space at the end. */
    while (isblank(c = getchar()))
        ;
    if (c != '\n')
        return false;
    return true;
}

int nb_of_horizontal_lines(void) {
    int nb = 0;
    /* We have a new horizontal line associated with (i,j)
     * if the grid contains a 1 at the intersection of row i and column j,
     * a 1 to the right, and no 1 to the left. */
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            if (grid[i][j] &&
                (j == 0 || !grid[i][j - 1]) &&
                j < DIM - 1 && grid[i][j + 1])
                ++nb;
    return nb;
}

int nb_of_vertical_lines(void) {
    int nb = 0;
    /* We have a new vertical line associated with (i,j)
     * if the grid contains a 1 at the intersection of row i and column j,
     * a 1 below, and no 1 above. */
    for (int j = 0; j < DIM; ++j)
        for (int i = 0; i < DIM; ++i)
            if (grid[i][j] &&
                (i == 0 || !grid[i - 1][j]) &&
                i < DIM - 1 && grid[i + 1][j])
                ++nb;
    return nb;
}

int nb_of_diagonal_lines(void) {
    int nb = 0;
    /* We have a new diagonal line associated with (i,j)
     * if the grid contains a 1 at the intersection of row i and column j,
     * and either a 1 south-east and no 1 north-est,
     * or a 1 south-west and no 1 north-east. */
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            if (grid[i][j]) {
                if ((i == 0 || j == 0 || !grid[i - 1][j - 1]) &&
                    i < DIM - 1 && j < DIM - 1 && grid[i + 1][j + 1])
                    ++nb;
                if ((i == 0 || j == DIM - 1 || !grid[i - 1][j + 1]) &&
                    i < DIM - 1 && j && grid[i + 1][j - 1])
                    ++nb;
            }
    return nb;
}
