/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: An example of program split over many files.                   *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *      diceroll2.c                                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int roll_count  = 0;   // not private to this file

static int rollem(int sides) {  // private to this file
    ++roll_count;
    return rand() % sides + 1;
}

int roll_n_dice(int dice, int sides) { // not private to this file
    int total = 0;
    if (sides < 2) {
        printf("Need at least 2 sides.\n");
        return -2;
    }
    if (dice < 1) {
        printf("Need at least 1 die.\n");
        return -1;
    }
    for (int i = 0; i < dice; ++i)
        total += rollem(sides);
    return total;
} 

