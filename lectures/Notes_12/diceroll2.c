/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: An example of program split over many files.                   *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *         diceroll1.c                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int roll_n_dice(int, int);  // Defined in other file

extern int roll_count;      // defined in other file

int main(void) {
    static int dice, roll, sides;
    srand(time(0));
    printf("Diceroll\n");
    printf("Enter the number of sides per die, 0 to stop: ");
    while (scanf("%d", &sides) == 1 && sides > 0) {
        printf("How many dice? ");
        scanf("%d", &dice);
        roll = roll_n_dice(dice, sides);
        if (roll > 0)
            printf("You have rolled a %d using %d %d-sided dice.\n",
                   roll, dice, sides);
        printf("How many sides? Enter 0 to stop: ");
    }
    printf("The rollem() function was called %d time%s.\n",
           roll_count, roll_count == 1 ? "" : "s");
    printf("Bye.\n");
    return EXIT_SUCCESS;
}

