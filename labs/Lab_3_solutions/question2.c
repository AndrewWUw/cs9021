/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Decodes all multiplications of the form                        *
 *                                                                             *
 *                        *  *  *                                              *
 *                   x       *  *                                              *
 *                     ----------                                              *
 *                     *  *  *  *                                              *
 *                     *  *  *                                                 *
 *                     ----------                                              *
 *                     *  *  *  *                                              *
 *                                                                             *
 *              such that the sum of all digits in all 4 columns is constant.  *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    for (int x = 100; x < 1000; ++x)
        for (int y = 10; y < 100; ++y) {
            const int product0 = x * (y % 10);
            if (product0 < 1000)
                continue;
            const int product1 = x * (y / 10);
            if (product1 >= 1000)
                continue;
            const int total = product0 + 10 * product1;
            if (total >= 10000)
                continue;
            const int sum = x % 10 + y % 10 + product0 % 10 + total % 10;
            if (x / 10 % 10 + y / 10 + product0 / 10 % 10 + product1 % 10 + total / 10 % 10 != sum)
                continue;
            if (x / 100 + product0 / 100 % 10 + product1 / 10 % 10 + total / 100 % 10 != sum)
                continue;
            if (product0 / 1000 + product1 / 100 + total / 1000 == sum)
                printf("%d * %d = %d, all columns adding up to %d.\n", x, y, total, sum);
        }
    return EXIT_SUCCESS;
}
