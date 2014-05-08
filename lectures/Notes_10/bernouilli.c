/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Implements functions to:                                       *
 *              - compute the first k + 1 elements of the (n + 1)st row        *
 *                of Bernouilli rectangle;                                     *
 *              - compute the first k + 1 elements of the (n + 1)st row        *
 *                of Bernouilli rectangle from the first k + 1 elements        *
 *                of the n-th row;                                             *
 *              - change the first k + 1 elements of the (n - 1)st row         *
 *                of Bernouilli rectangle to the first k + 1 elements          *
 *                of the n-th row.                                             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "bernouilli.h"

void bernouilli_row_up_to(const int n, const int k, unsigned long long *const row) {
    for (int i = 0; i <= k; ++i)
        row[i] = 1;
    if (k == 0)
        return;
    for (int m = 1; m <= n; ++m)
        bernouilli_change_to_next_row_up_to(m, k, row);
}

void bernouilli_next_row_up_to(int n, const int k,
                    unsigned long long *const row,
                    const unsigned long long *const previous_row) {
    row[0] = 1;
    if (k == 0)
        return;
    const int min = n < k ? n : k;
    for (int i = 1; i <= min; ++i)
        row[i] = previous_row[i - 1] + previous_row[i];
    while (++n <= k)
        row[n] = row[min];
}

void bernouilli_change_to_next_row_up_to(int n, const int k, unsigned long long *const row) {
    const int min = n < k ? n : k;
    unsigned long long first_term = 1;
    for (int i = 1; i <= min; ++i) {
        unsigned long long second_term = row[i];
        row[i] += first_term;
        first_term = second_term;
    }
    while (++n <= k)
        row[n] = row[min];
}


