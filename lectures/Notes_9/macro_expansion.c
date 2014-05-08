/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out three string literals.                              *
 *                                                                             *
 * Purpose: Illustrates sucessive macro expansion.                             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define STAR_BLOCK_1 QUOTED_STARS"\n"QUOTED_STARS"\n"QUOTED_STARS"\n"
#define QUOTED_STARS QUOTED_STAR QUOTED_STAR QUOTED_STAR QUOTED_STAR QUOTED_STAR
#define QUOTED_STAR "*"

#define STAR_BLOCK_2 STARS"\n"STARS"\n"STARS"\n"
#define STARS "STAR STAR STAR STAR STAR"
#define STAR *

#define STAR_BLOCK_3 "STARS\nSTARS\nSTARS\n"

int main(void) {
    printf(STAR_BLOCK_1);
    putchar('\n');
    printf(STAR_BLOCK_2);
    putchar('\n');
    printf(STAR_BLOCK_3);
    putchar('\n');
    printf("STAR_BLOCK_1 STAR_BLOCK_2 STAR_BLOCK_3\n");
    return EXIT_SUCCESS;
}

