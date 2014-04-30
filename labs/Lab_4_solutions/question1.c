/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for a strictly positive number N              *
 *              and outputs an equilateral triangle of height N.               *
 *              The top of the triangle (line 1) is labeled with the letter A. *
 *              For all nonzero p < N, line p+1 of the triangle is labeled     *
 *              with letters that go up in alphabetical order modulo 26        *
 *              from the beginning of the line to the middle of the line,      *
 *              starting wth the letter that comes next in alphabetical order  *
 *              modulo 26 to the letter in the middle of line p,               *
 *              and then down in alphabetical order modulo 26                  *
 *              from the middle of the line to the end of the line.            *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char c = 'A';
    int height;
    do {
        printf("Enter strictly positive number: ");
        rewind(stdin);
    } while ((!scanf("%d", &height) || height < 1 ) && !fflush(stdin));
    for (int i = 1; i <= height; ++i) {
        /* Displays spaces on the left */
        for (int j = 0; j < height - i; ++j)
            printf(" ");
        /* Displays letters before middle column */
        for (int k = 1; k < i; ++k) {
            printf("%c", c);
            /* code of next letter */
            c = (c - 'A' + 1) % 26 + 'A';
        }
        /* Displays middle column */
        printf("%c", c);
        /* Displays letters after middle column */
        for (int k = 1; k < i; ++k) {
            /* Code of previous letter */
            c = (c -'A' + 25) % 26 + 'A';
            printf("%c", c);
        }
        printf("\n");
        /* Code of first letter to be input on next line */
        c = ((1 + i) * i / 2) % 26 + 'A';
    }
    return EXIT_SUCCESS;
}
