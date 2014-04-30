/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for two numbers and prints their gcd.         *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

long long gcd(const long long, const long long);

int main(void) {
    long long nb1, nb2;
    do {
        printf("Input two positive integers at least one of which is not equal to 0: ");
        rewind(stdin);
    } while (scanf("%lld %lld", &nb1, &nb2) != 2 || (nb1 == 0 && nb2 == 0) && !fflush(stdin));
    printf("The gcd of %lld and %lld is %lld.\n", nb1, nb2, gcd(nb1, nb2));
    return EXIT_SUCCESS;
}

long long gcd(const long long nb1, const long long nb2) {
    if (nb2 == 0)
        return nb1 > 0 ? nb1 : -nb1;
    return gcd(nb2, nb1 % nb2);
}

    

