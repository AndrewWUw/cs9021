/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Finds all possible ways of inserting 3 multiplication signs    *
 *              in the sequence 1238965740 in two different manners            *
 *              such that both resulting products of 4 numbers are equal       *
 *              and not equal to 0.                                            *
 *                                                                             *
 * Written for COMP9021                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool create_partition(int *const, int *const, int *const);
void generate_numbers(const int, const int, const int, int *const);
void print_solution(const int *const, const int *const, const int);

const int digits[] = {1, 2, 3, 8, 9, 6, 5, 7, 4, 0};

int main(void) {
    int i1 = 1, j1 = 2, k1 = 2;
    /* Give i1, j1 and k1 all possible values with 0 < i1 < j1 < k1 < 9. */
    while (create_partition(&i1, &j1, &k1)) {
        int numbers1[4];
        /* Store in numbers1 the number consisting
         * of the first i1 digits in digits[],
         * then the number consisting of the j1 - i1 next digits in digits[],
         * then the number consisting of the k1 - j1 next digits in digits[],
         * and eventually the number consisting
         * of the remaining digits in digits[],
         * with at least 2 of those remaining digits.*/
        generate_numbers(i1, j1, k1, numbers1);
        int i2 = i1;
        int j2 = j1;
        int k2 = k1;
        /* Give i2, j2 and k2 all possible values with 0 < i2 < j2 < k2 < 9
         * and (i1, j1, k1) < (i2, j2, k2). */
        while (create_partition(&i2, &j2, &k2)) {
            int numbers2[4];
            /* Store in numbers2 the number consisting
             * of the first i2 digits in digits[],
             * then the number consisting of the j2 - i2 next digits in digits[],
             * then the number consisting of the k2 - j2 next digits in digits[],
             * and eventually the number consisting
             * of the remaining digits in digits[],
             * with at least 2 of those remaining digits.*/
            generate_numbers(i2, j2, k2, numbers2);
            int product = numbers1[0] * numbers1[1] * numbers1[2] * numbers1[3];
            if (numbers2[0] * numbers2[1] * numbers2[2] * numbers2[3] == product)
                print_solution(numbers1, numbers2, product);
        }
    }
    return EXIT_SUCCESS;
}


bool create_partition(int *const i, int *const j, int *const k) {
    if (++*k == 9) {
        if (++*j == 8) {
            if (++*i == 7)
                return false;
            *j = *i + 1;
        }
        *k = *j + 1;
    }
    return true;
}


void generate_numbers(const int i, const int j, const int k, int *const numbers) {
    int n = 0;
    numbers[0] = digits[0];
    while (++n < i)
        numbers[0] = numbers[0] * 10 + digits[n];
    numbers[1] = digits[n];
    while (++n < j)
        numbers[1] = numbers[1] * 10 + digits[n];
    numbers[2] = digits[n];
    while (++n < k)
        numbers[2] = numbers[2] * 10 + digits[n];
    numbers[3] = digits[n];
    while (++n < 9)
        numbers[3] = numbers[3] * 10 + digits[n];
    numbers[3] *= 10;
}


void print_solution(const int * const numbers1, const int * const numbers2,
                    const int product) {
    putchar(' ');
    printf("%d * %d * %d * %d = ", numbers1[0], numbers1[1], numbers1[2], numbers1[3]);
    printf("%d * %d * %d * %d = ", numbers2[0], numbers2[1], numbers2[2], numbers2[3]);
    printf("%d\n", product);
}
