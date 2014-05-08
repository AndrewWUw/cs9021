/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Plays the game of life on a grid of size 8 x 8.                *
 *              - The grid is randomly initialised with an expectation of      *
 *                of one third of locations being filled with alive cells.     *
 *              - After initialisation, the player can decide to display       *
 *                the next generation or quit.                                 *
 *              - A cell survives to the next generation if it has two or      *
 *                three neighbours.                                            *
 *              - A cell dies from overcrowding if it has at least four        *
 *                neighbours.                                                  *
 *              - A cell dies from loneliness if it has less than two          *
 *                neighbours.                                                  *
 *              - A cell is born into an empty position if it has exactly      *
 *                three neighbours.                                            *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_OF_ROWS 8
#define NB_OF_COLUMNS 8
#define DEAD ' '
#define ACTIVE '*'
/* Ratio of dead over active cells */
#define RATIO 3

char grid[NB_OF_ROWS][NB_OF_COLUMNS];
char next_grid[NB_OF_ROWS][NB_OF_COLUMNS];

void initialise_grid(void);
void display_grid(void);
void determine_next_generation(void);
void update_grid(void);

int main(void) {
    initialise_grid();
    display_grid();
    while (true) {
        printf("Hit return to see next generation: ");
        if (getchar() != '\n')
            return EXIT_SUCCESS;
        determine_next_generation();
        update_grid();
        display_grid();
    }
    return EXIT_SUCCESS;
}

void initialise_grid(void) {
    srand(time(NULL));    
    for (int i = 0; i < NB_OF_ROWS; ++i)
        for (int j = 0; j < NB_OF_COLUMNS; ++j)
            /* With probability 1/3, each cell is made active */
            if (rand() % RATIO)
                grid[i][j] = DEAD;
            else
                grid[i][j] = ACTIVE;
}

void display_grid(void) {
    puts("        0000000000000000000");
    for (int i = 0; i < NB_OF_ROWS; ++i) {
        printf("        0 ");
        for (int j = 0; j < NB_OF_COLUMNS; ++j) {
            putchar(grid[i][j]);
            putchar(' ');
        }
        puts("0");
    }
    puts("        0000000000000000000");
}
    
void determine_next_generation(void) {
    for (int i = 0; i < NB_OF_ROWS; ++i)
        for (int j = 0; j < NB_OF_COLUMNS; ++j) {
            /* Count the number cells around the grid[i][j]
             * that are alive, from top to bottom and from left to right */
            int cell_count = 0;
            if (i && j && grid[i - 1][j - 1] == ACTIVE)
                ++cell_count;
            if (i && grid[i - 1][j] == ACTIVE)
                ++cell_count;
            if (i && j < NB_OF_COLUMNS - 1 && grid[i - 1][j + 1] == ACTIVE)
                ++cell_count;
            if (j && grid[i][j - 1] == ACTIVE)
                ++cell_count;
            if (j < NB_OF_COLUMNS - 1 && grid[i][j + 1] == ACTIVE)
                ++cell_count;
            if (i < NB_OF_ROWS - 1 && j && grid[i + 1][j - 1] == ACTIVE)
                ++cell_count;
            if (i < NB_OF_ROWS - 1 && grid[i + 1][j] == ACTIVE)
                ++cell_count;
            if (i < NB_OF_ROWS - 1 && j < NB_OF_COLUMNS - 1 && grid[i + 1][j + 1] == ACTIVE)
                ++cell_count;
            /* Apply the rules of the game that determine
             * which cells come to life, which cells remain alive,
             * and which cells die. */
            if (grid[i][j]  == DEAD && cell_count == 3)
                next_grid[i][j] = ACTIVE;
            else if (grid[i][j] == ACTIVE && (cell_count == 2 || cell_count == 3))
                next_grid[i][j] = ACTIVE;
            else
                next_grid[i][j] = DEAD;
        }
}

void update_grid(void) {
    for (int i = 0; i < NB_OF_ROWS; ++i)
        for (int j = 0; j < NB_OF_COLUMNS; ++j)
            grid[i][j] = next_grid[i][j];
}           
