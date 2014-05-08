#ifndef _BERNOUILLI_H_
#define _BERNOUILLI_H_
#include <stdbool.h>

/* For all n and k, let B(n, k) be equal to 1 if n = 0 or k = 0,
 * and to B(n - 1, k) + B(n, k) otherwise.
 * These values define the Bernouilli rectangle.
 * Note that:
 * - if k > n then B(n, k) is equal to B(n, n);
 * - if k <= n then B(n, k) is equal to the sum of n choose k1
 *   where k1 ranges over {0, ..., k}. */
/* Stores at location row the values of B(n, k1), for all k in {0, ..., k}. */
void bernouilli_row_up_to(const int n, const int k, unsigned long long *const row);
/* Stores at location row the values of B(n, k1), for all k1 in {0, ..., k},
 * with n assumed not be equal to 0, computed from the values of B(n - 1, k1),
 * for all k1 in {0, ..., k} assumed to be stored at location previous_row. */
void bernouilli_next_row_up_to(int n, const int k,
                    unsigned long long *const row,
                    const unsigned long long *const previous_row);
/* Updates at location row the values of n choose k1, for all k1 in {0, ..., k},
 * with n assumed not to be equal to 0, computed from the values of B(n - 1, k1),
 * for all k1 in {0, ..., k} assumed to be stored at location row. */
void bernouilli_change_to_next_row_up_to(int n, const int k, unsigned long long *const row);

#endif
