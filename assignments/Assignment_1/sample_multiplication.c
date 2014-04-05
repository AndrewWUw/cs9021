/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all multiplications of the form                          *
 *                            *  *  *                                          *
 *                        x   *  *  *                                          *
 *                            -------                                          *
 *                         *  *  *  *                                          *
 *                      *  *  *  *                                             *
 *                   *  *  *  *                                                *
 *                   ----------------                                          *
 *                   *  *  *  *  *  *                                          *
 *              that satisfy the following conditions:                         *
 *              - each star stands for a digit, with the leftmost star         *
 *                on each line standing for a nonzero digit;                   *
 *              - all partial products are made up of the same digits;         *
 *              - the first and second partial products are different;         *
 *              - the orderings of digits in the second and third              *
 *                partial products are inverse of each other;                  *
 *              - the third partial product is the sum of the first two        *
 *                partial products.                                            *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    for (int m = 100; m < 1000; ++m)
        for (int n = 100; n < 1000; ++n) {
            int product = m * n;
            if (product < 100000)
                continue;
            int partial_product1 = m * (n % 10);
            if (partial_product1 < 1000)
                continue;
            int partial_product2 = m * (n / 10 % 10);
            if (partial_product2 < 1000)
                continue;
            if (partial_product1 == partial_product2)
                continue;
            int partial_product3 = m * (n / 100);
            if (partial_product3 < 1000)
                continue;
            if (partial_product3 != partial_product1 + partial_product2)
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
            /* Write third partial product as p31 p32 p33 p34. */
            int p31 = partial_product3 / 1000;
            int p32 = partial_product3 / 100 % 10;
            int p33 = partial_product3 / 10 % 10;
            int p34 = partial_product3 % 10;
            /* Check that ordering of digits in second and third partial products
             * are inverse of each other. */
            if (p21 != p34 || p22 != p33 || p23 != p32 || p24 != p31)
                continue;
            /* Set the p11-th, p12-th, p13-th and p14-th bits of digits_1 to 1. */
            int digits_1 = 1 << p11;
            digits_1 |= 1 << p12;           
            digits_1 |= 1 << p13;
            digits_1 |= 1 << p14;
            /* Set the p21-th, p22-th, p23-th and p24-th bits of digits_2 to 1. */
            int digits_2 = 1 << p21;
            digits_2 |= 1 << p22;           
            digits_2 |= 1 << p23;
            digits_2 |= 1 << p24;
            /* Check that first and second partial products, hence all partial products,
             * are made up of the same digits. */
            if (digits_1 != digits_2)
                continue;
            printf("%6d\n x%4d\n", m, n);
            printf("   ---\n");
            printf("%6d\n%5d\n%4d\n", partial_product1, partial_product2, partial_product3);
            printf("------\n");
            printf("%d\n", product);
        }
    return EXIT_SUCCESS;
}

