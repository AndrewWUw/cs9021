/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Displays a menu to add, subtract, multiply, or divide          *
 *              two floating point numbers, and performs the operation.        *
 *              Users are expected to input first a, s, m, d or q, and then    *
 *              two integer or floating point constants. They are prompted     *
 *              again in case they fail to do so. If they choose division      *
 *              then they are reminded that the second number they have to     *
 *              input should be nonnull.                                       *
 *                                                                             *
 *  Written by Eric Martin for COMP9021                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void add(void);
void subtract(void);
void multiply(void);
void divide(void);
double get_argument(void);
void flush(void);

int main(void) {
    while (true) {
        char operator;
        printf("\nEnter operation of choice:\n"
               "a: addition          s: subtraction\n"
               "m: multiplication    d: division\n"
               "q: quit\n");
        scanf("%c", &operator);
        flush();
        switch (operator) {
            case 'a':
                add();
                break;
            case 's':
                subtract();
                break;
            case 'm':
                multiply();
                break;
            case 'd':
                divide();
                break;
            case 'q':
                return EXIT_SUCCESS;
            default:
                printf("Unknown operation, try again.\n");
        }
    }
}

void add(void) {
    printf("Enter first argument to addition: ");
    const double i = get_argument();
    printf("Enter second argument to addition: ");
    const double j = get_argument();
    printf("%g + %g = %g\n", i, j, i + j);
}

void subtract(void) {
    printf("Enter first argument to subtraction: ");
    const double i = get_argument();
    printf("Enter second argument to subtraction: ");
    const double j = get_argument();
    printf("%g - %g = %g\n", i, j, i - j);
}

void multiply(void){
    printf("Enter first argument to multiplication: ");
    const double i = get_argument();
    printf("Enter second argument to multiplication: ");
    const double j = get_argument();
    printf("%g * %g = %g\n", i, j, i * j);
}

void divide(void) {
    printf("Enter first argument to division: ");
    const double i = get_argument();
    printf("Enter second argument to division: ");
    double j = get_argument();
    if (j == 0)
        do {
            printf("Argument cannot be null. ");
            printf("Enter second argument to division again: ");
            j = get_argument();
        } while (j == 0);
    printf("%g / %g = %g\n", i, j, i / j);
}

double get_argument(void) {
    double x;
    int status = scanf("%lg", &x);
    flush();
    if (status != 1)
        do {
            printf("Enter argument again: ");
            status = scanf("%lg", &x);
            flush();
        } while (status != 1);
    return x;
}

void flush(void) {
    while (getchar() != '\n')
        ;
}

