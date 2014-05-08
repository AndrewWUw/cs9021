/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: An example of program split over many files.                   *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       count1.c                                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>

extern int count;      // reference declaration, external linkage
static int total_1 = 0;  // static definition, internal linkage

void accumulate(int k) { // k has block scope, no linkage
    static int total_2 = 0;  // static, no linkage
    if (k <= 0) {
        printf("loop cycle: %d\n", count);
        printf("total_1: %d; total_2: %d\n", total_1, total_2);
    }
    else {
        total_1 += k;
        total_2 += k;
    }
}



