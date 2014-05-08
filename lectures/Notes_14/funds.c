/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Performs a few operations on structures.                       *
 *                                                                             *
 * Purpose: Illustrates the different ways of manipulating a structure.        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define FUNDLEN 50

struct funds {
    char   cheque[FUNDLEN];
    double cheque_fund;
    char   savings[FUNDLEN];
    double savings_fund;
};

double sum1(double, double);
double sum2(struct funds);
double sum3(const struct funds *);

int main(void) {
    struct funds jim = {
        "Commonwealth Bank",
        20308.78,
        "SaintGeorge Bank",
        73203.11
    };
    printf("Jim has a total of $%.2f.\n",
           sum1(jim . cheque_fund, jim . savings_fund));
    printf("Jim has a total of $%.2f.\n",
           sum2(jim));
    printf("Jim has a total of $%.2f.\n",
           sum3(&jim));
    return EXIT_SUCCESS;
}

double sum1(double x, double y) {
    return x + y;
}

double sum2(struct funds money) {
    return money . cheque_fund + money . savings_fund;
}

double sum3(const struct funds * money) {
    return money -> cheque_fund + money -> savings_fund;
}

