/*
 * multiplication.c
 *
 *  Created on: Apr 6, 2014
 *      Author: xwux288
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main(void) {

    for (int m = 222; m <= 777; ++m) {
        int m_1 = m / 100;
        int m_2 = m % 100 / 10;
        int m_3 = m % 10;
        if (!(m_1 == 2 || m_1 == 3 || m_1 == 5 || m_1 == 7))
            continue;
        if (!(m_2 == 2 || m_2 == 3 || m_2 == 5 || m_2 == 7))
            continue;
        if (!(m_3 == 2 || m_3 == 3 || m_3 == 5 || m_3 == 7))
            continue;

        for (int n = 22; n < 77; ++n) {
            int n_1 = n / 10;
            int n_2 = n % 10;
            if (!(n_1 == 2 || n_1 == 3 || n_1 == 5 || n_1 == 7))
                continue;
            if (!(n_2 == 2 || n_2 == 3 || n_2 == 5 || n_2 == 7))
                continue;

            // product = *****
            int product = m * n;
            if (product < 10000)
                continue;
            int p_1 = product / 10000;
            int p_2 = product % 10000 / 1000;
            int p_3 = product % 10000 % 1000 / 100;
            int p_4 = product % 10000 % 1000 % 100 / 10;
            int p_5 = product % 10000 % 1000 % 100 % 10;
            if (!(p_1 == 2 || p_1 == 3 || p_1 == 5 || p_1 == 7))
                continue;
            if (!(p_2 == 2 || p_2 == 3 || p_2 == 5 || p_2 == 7))
                continue;
            if (!(p_3 == 2 || p_3 == 3 || p_3 == 5 || p_3 == 7))
                continue;
            if (!(p_4 == 2 || p_4 == 3 || p_4 == 5 || p_4 == 7))
                continue;
            if (!(p_5 == 2 || p_5 == 3 || p_5 == 5 || p_5 == 7))
                continue;

            int partial_product1 = m * (n % 10);
            if (partial_product1 < 1000)
                continue;
            int partial_product2 = m * (n / 10 % 10);
            if (partial_product2 < 1000)
                continue;
            /* Write first partial product as p11 p12 p13 p14. */
            int p11 = partial_product1 / 1000;
            int p12 = partial_product1 / 100 % 10;
            int p13 = partial_product1 / 10 % 10;
            int p14 = partial_product1 % 10;
            /* Write second partial product as p21 p22 p23 p24. */
            int p21 = partial_product2 / 1000;
            int p22 = partial_product2 / 100 % 10;
            int p23 = partial_product2 / 10 % 10;
            int p24 = partial_product2 % 10;

            if (!(p11 == 2 || p11 == 3 || p11 == 5 || p11 == 7))
                continue;
            if (!(p12 == 2 || p12 == 3 || p12 == 5 || p12 == 7))
                continue;
            if (!(p13 == 2 || p13 == 3 || p13 == 5 || p13 == 7))
                continue;
            if (!(p14 == 2 || p14 == 3 || p14 == 5 || p14 == 7))
                continue;
            if (!(p21 == 2 || p21 == 3 || p21 == 5 || p21 == 7))
                continue;
            if (!(p22 == 2 || p22 == 3 || p22 == 5 || p22 == 7))
                continue;
            if (!(p23 == 2 || p23 == 3 || p23 == 5 || p23 == 7))
                continue;
            if (!(p24 == 2 || p24 == 3 || p24 == 5 || p24 == 7))
                continue;

            printf("%6d\n x%4d\n", m, n);
            printf("   ---\n");
            printf("%6d\n%5d\n", partial_product1, partial_product2);
            printf("------\n");
            printf("%d\n", product);
        }
    }
    return EXIT_SUCCESS;
}
