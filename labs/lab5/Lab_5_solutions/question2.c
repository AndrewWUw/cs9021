/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Generates all 3 x 3 magic squares.                             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* The sum of each row and column is necessarily equal to
 * ((1 + 9) * 9 / 2) / 3 = 15 */
#define SUM 15

/* Numbering the cells of the square as
 * 1 4 2
 * 7 6 5
 * 8 9 3
 * digits[i] will keep track of the cell where i ends up
 * (with index 0 being of no use), while
 * cells[i] will keep track of the digit that ends up in cell i
 * (with index 0 being of no use). */
int digits[10];
int cells[10];

void dispatch(const int, const int, const int, const int);
bool place(const int, const int, const int);


int main(void) {
    /* Generate 3 distinct values to assign to cells 1, 2 and 3. */
    for (int i0 = 1, i1 = i0 + 1, i2 = i1 + 1; i0 < 8;
         ++i2 < 10 ||
             ++i1 < 9 && (i2 = i1 + 1) ||
             ++i0 && (i1 = i0 + 1) && (i2 = i1 + 1)) {
        /* There are 6 possible ways to dispatch i0, i1 and i2 in cells 1, 2 and 3. */
        for (int i = 0; i < 6; ++i) {
            dispatch(i, i0, i1, i2);
            /* The contents of cell 4 is determined by the contents of cells 1 and 2. */
            if (!place(cells[1], cells[2], 4))
                continue;
            /* The contents of cell 5 is determined by the contents of cells 2 and 3. */
            if (!place(cells[2], cells[3], 5))
                continue;
            /* The contents of cell 6 is determined by the contents of cells 1 and 3. */
            if (!place(cells[1], cells[3], 6))
                continue;            
            /* The contents of cell 7 is determined by the contents of cells 5 and 6. */
            if (!place(cells[5], cells[6], 7))
                continue;
            /* The contents of cell 8 is determined by the contents of cells 1 and 7.
             * The diagonal that goes through cells 2, 6 and 8 is complete. */
            if (!place(cells[1], cells[7], 8))
                continue;
            if (cells[2] + cells[6] + cells[8] != SUM)
                continue;           
            /* The contents of cell 9 is determined by the contents of cells 3 and 8.
             * The second column is complete. */
            if (!place(cells[3], cells[8], 9))
                continue;
            if (cells[4] + cells[6] + cells[9] != SUM)
                continue;
            printf("  %d  %d  %d\n", cells[1], cells[4], cells[2]);
            printf("  %d  %d  %d\n", cells[7], cells[6], cells[5]);
            printf("  %d  %d  %d\n", cells[8], cells[9], cells[3]);
            putchar('\n');
        }
    }
    return EXIT_SUCCESS;
}


/* Resets cells and digits, and dispatches i0, i1 and i2 as follows.
 * Cell  1   2   3
 *       i0  i1  i2   (for i = 0)
 *       i1  i0  i2   (for i = 1)
 *       i1  i2  i0   (for i = 2)
 *       i0  i2  i1   (for i = 3)
 *       i2  i0  i1   (for i = 4)
 *       i2  i1  i0   (for i = 5). */
void dispatch(const int i, const int i0, const int i1, const int i2) {
    for (int k = 1; k < 10; ++k)
        digits[k] = cells[k] = 0;
    digits[i0] = i % 3 + 1;
    cells[i % 3 + 1] = i0;
    digits[i1] = (i % 2 + i % 3 + 1) % 3 + 1;
    cells[(i % 2 + i % 3 + 1) % 3 + 1] = i1;
    digits[i2] = (7 - i) / 2;
    cells[(7 - i) / 2] = i2;
}


/* Place SUM - i - j in cell k, if that number is a nonzero digit
 * and has not been used already. */
bool place(const int i, const int j, const int k) {
    const int v = SUM - i - j;
    if (v > 9 || v < 0 || digits[v])
        return false;
    digits[v] = k;
    cells[k] = v;
    return true;
}


