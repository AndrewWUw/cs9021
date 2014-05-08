/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for yearly salary and comments on the figure. *
 *                                                                             *
 * Purpose: Illustrates the use of some escape sequences and the time function *
 *          from the time standard library.                                    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    double salary;
    /* Beep or flash for 2 seconds. */
    time_t time_start, time_now;
    time(&time_start);
    do {
        time(&time_now);
        putchar('\a');
    } while (time_now - time_start < 2);
    do {
        printf("Enter your \"year\ly\" Salary\": $______\b\b\b\b\b\b");
        rewind(stdin);
    } while (!scanf("%lf", &salary) && !fflush(stdin));
    if (salary > 100000)
        printf("That's not bad!\n");
    else if (salary < 50000)
        printf("Mmm, with the big family you have, ends of months must be tough sometimes.\n");
    else
        printf("You could be worse off!\n");
    return EXIT_SUCCESS;
}

