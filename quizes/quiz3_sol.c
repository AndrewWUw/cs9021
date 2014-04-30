/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for a floating point number in base 3         *
 *              represented as a dot                                           *
 *               - preceded by between 1 and 20 digits equal to 0, 1 or 2,     *
 *                 the first of which is not 0 and is possibly preceded by     *
 *                 + or -, and                                                 *
 *               - followed by between 0 and 10 digits equal to 0, 1 or 2.     *
 *               Outputs a representation of this number in base 10            *
 *               and in base 2.                                                *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define MAX_SIZE 33
#define PRECISION 10 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Enter a floating point number in base 3 represented as a dot\n"
           "- preceded by between 1 and 20 digits equal to 0, 1 or 2,\n"
           "the first of which is not 0 and is possibly preceded by + or -, and\n"
           "- followed by between 0 and 10 digits equal to 0, 1 or 2:\n");
    char characters[MAX_SIZE];
    int i = 0;
    int c;
    while ((c = getchar()) != '\n')
        characters[i++] = c;
    characters[i] = '\0';
    double number;
    char sign = '+';
    int exponent = 0;
    int mantissa[PRECISION] = {0};
    i = 0;
    if (characters[0] == '+' || characters[0] == '-')
        i = 1;
    number = characters[i] - '0';
    while (characters[++i])
        if (characters[i] != '.')
            number = number * 3 + characters[i] - '0';
    while (characters[--i] != '.')
        number /= 3;
    if (characters[0] == '-')
        number *= -1;
    double number_copy = number;
    if (number_copy < 0) {
        number_copy *= -1;
        sign = '-';
    }
    while (number_copy >= 2) {
        number_copy /= 2;
        ++exponent;
    }
    number_copy -= 1;
    for (i = 0; i < PRECISION; ++i) {
        number_copy *= 2;
        if (number_copy >= 1) {
            mantissa[i] = 1;
            number_copy -= 1;
        }
    }
    printf("The number that has been input is approximately equal to %f\n", number);
    printf("In base 2, this number is approximately equal to %c1.", sign);
    for (i = 0; i < PRECISION; ++i)
        if (mantissa[i])
            putchar('1');
        else
            putchar('0');
    printf(" * 2^%d\n", exponent);
    return EXIT_SUCCESS;
}    
