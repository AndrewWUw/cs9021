/*
 * division.c
 *
 *  Created on: Apr 6, 2014
 *      Author: xwux288
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void outputResult();

int main(void) {

    for (int divisor = 100; divisor < 1000; divisor++) {
        for (int n = 97999; n >= 17000; n--) {
            int n1 = n / 10000;
            int n2 = n % 10000 / 1000;
            int n3 = n % 10000 % 1000 / 100;
            int n4 = n % 10000 % 1000 % 100 / 10;
            int n5 = n % 10000 % 1000 % 100 % 10;

            if (n1 == 0 || n2 != 7 || n3 == 0 || n5 == 0)
                continue;

            // Calculate production of each bit of n with divisor
            int product1 = divisor * n1;
            int product2 = divisor * n2;
            int product3 = divisor * n3;
            int product4 = divisor * n4;
            int product5 = divisor * n5;

            // Check if product1 is ****, and product2 is ***,
            // and product3 is ***, and product4 is ****
            if (product1 < 1000)
                continue;
            if (product2 >= 1000)
                continue;
            if (product3 >= 1000)
                continue;
            if (product4 != 0)
                continue;
            if (product5 < 1000)
                continue;

            // Check if the dividend is correct
            int dividend = product1 * 10000 + product2 * 1000 + product3 * 100
                    + product4 * 10 + product5;
            if (dividend < 10000000)
                continue;
            if (dividend != (divisor * n))
                continue;

            // Calculate & check reminders
            int reminder5 = product5;
            int reminder3 = reminder5 / 100 + product3;
            int reminder2 = reminder3 / 10 + product2;

            if (reminder3 < 1000 || reminder3 == 0)
                continue;
            if (reminder2 > 1000 || reminder2 == 0)
                continue;
            if ((reminder2 / 10 + product1) != dividend / 10000)
                continue;

            int data[10] = { divisor, dividend, n, product1, product2, product3,
                    product5, reminder2, reminder3, reminder5 };
            outputResult(data);
        }
    }
    return EXIT_SUCCESS;
}

/*
 * Output computing result in desired format
 */
void outputResult(int data[]) {
    printf("%d|%d\n", data[1], data[0]);
    printf("        |-----\n");
    printf("%d    |%d\n", data[3], data[2]);
    printf("----    |\n");
    printf("  %d   |\n", data[7]);
    printf("  %d   |\n", data[4]);
    printf("  ---   |\n");
    printf("  %d  |\n", data[8]);
    printf("   %d  |\n", data[5]);
    printf("   ---  |\n");
    printf("    %d|\n", data[9]);
    printf("    %d|\n", data[6]);
    printf("    ----|\n");
    printf("       0|\n");
}
