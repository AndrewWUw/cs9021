/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Reads a string of digits, letters from a to f and              *
 *              letters from A to F, interpreted as a hexadecimal number,      *
 *              and prints out its value in decimal.                           *
 *              Input can be preceded with or followed by blanks.              *
 *              Nothing is output when no character or only blanks are input.  *
 *              An error message is output in response to inputs               *
 *              that are incorrect or too large to fit in an unsigned long.    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void convert(int);
bool only_blanks_left(int);

int main(void) {
     printf("Enter a nonzero hexadecimal number: ");
    /* Character being read */
     int c;
     /* Skip blanks that possibly precede input. */
     while ((c = getchar()) != '\n' && isblank(c))
          ;
     /* Make sure that input starts with 0x or 0X followed by a nonzero digit. */
     if (c != '0' ||
         (c = getchar()) != 'x' && c != 'X' ||
         !isxdigit(c = getchar()) || c == '0') {
         printf("Input is incorrect\n");
         return EXIT_FAILURE;
     }
     convert(c);
     return EXIT_SUCCESS;
}

/* convert() is called until getchar() fails to return an hexadecimal digit.
 * If decimal equivalent of x_1...x_n is number then decimal equivalent of
 * x_1...x_n x_{n+1} is number * 16 plus decimal equivalent of x_{n+1}. */
void convert(int c) {
    unsigned long number = 0;
    int nb_of_digits = 0;
    /* A byte allows one to code numbers from 0x0 to 0xff.  */
    const int max_nb_of_hex_digits = sizeof(unsigned long) * 2;
    while (isxdigit(c)) {
        if (++nb_of_digits > max_nb_of_hex_digits) {
            printf("Input is too large or incorrect\n");
            exit(EXIT_FAILURE);
        }
        if (isdigit(c))
            number = number * 16 + c - '0';
        else
            number = number * 16 + tolower(c) - 'a' + 10;
        c = getchar();
    }
    if (only_blanks_left(c))
        printf("The decimal value of 0x%lx is %lu\n", number, number);
    else
        printf("Incorrect input\n");
}

bool only_blanks_left(int c) {
    while (c != '\n')
        if (isblank(c))
            c = getchar();
        else
            return false;
    return true;
}
