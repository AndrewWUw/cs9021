/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for a positive number, and converts it        *
 *              from base 10 to base 2, using two recursive procedures,        *
 *              one of which is tail-recursive.                                *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

void to_binary_1(unsigned);
void to_binary_2(unsigned, int);

int main(void) {
    unsigned num;
    printf("Enter a positive integer: ");
    scanf("%u", &num);
    printf("Binary equivalent:\n");
    to_binary_1(num);
    putchar('\n');
    if (num == 0)
        putchar('0');
    else
        to_binary_2(num, (int)log2(num));
    putchar('\n');
    return EXIT_SUCCESS;
}

void to_binary_1(const unsigned n) {
    if (n >= 2)
        to_binary_1(n / 2);
    putchar('0' + n % 2);
}

void to_binary_2(const unsigned n, const int exp) {
    if (exp < 0)
        return;        
    if (pow(2, exp) <= n) {
        putchar('1');
        to_binary_2(n - pow(2, exp), exp - 1);
    }
    else {
        putchar('0');
        to_binary_2(n, exp - 1);
    }
}
