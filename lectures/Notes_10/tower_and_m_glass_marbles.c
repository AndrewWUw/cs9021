/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Solves the tower and m glass marbles problem. The user is      *
 *              prompted to enter the number n of floors of a building.        *
 *              Using m marbles, one has to discover the highest floor,        *
 *              if any, such that dropping a marble from that floor makes      *
 *              it break, using a strategy that minimises the number of        *
 *              drops in the worst case (it is assumed that any marble would   *
 *              break when dropped from a floor where one marble breaks, and   *
 *              also when dropped from any higher floor; the marbles might     *
 *              not break when dropped from any floor).                        *
 *                                                                             *
 *              The idea is to ask: what is the maximum height h of a building *
 *              such that an answer can always be found with no more than d    *
 *              drops? Let H(d, m) denote that maximum height.                 *
 *              - If the marble breaks, m - 1 marbles remain                   *
 *                and no higher floor needs to be tested.                      *
 *              - If the marble does not break, m  marbles remain              *
 *                and no lower floor needs to be tested.                       *
 *              - In any case, d - 1 drops remain.                             *
 *              This yields: H(d, m) = H(d - 1, m - 1) + H(d - 1, m) + 1.      *
 *              The base cases are when either d = 0 or m = 0, in which case   *
 *              H(d, m) = 0.                                                   *
 *              This allows one to compute d as the least integer with         *
 *              H(d, m) >= n.                                                  *
 *              For the simulation, if low is the highest floor from which     *
 *              it is known that a marble can be dropped without breaking,     *
 *              d' is the number of drops that remain, and m' is the number    *
 *              of marbles that remain, then the next marble should be dropped *
 *              from floor low + H(d' - 1, m' - 1) + 1.                        *
 *                                                                             *
 *              Set B(0, k) = 1 for all k, B(n, 0) = 1 for all n, and          *
 *              B(n + 1, k + 1) = B(n, k) + B(n, k + 1).                       *
 *              The recurrence relation is identical to the one that           *
 *              determines the binomial coefficients.                          *
 *              It is easy to verify that:                                     *
 *              - H(n, k) is equal to B(n, k) - 1;                             *
 *              - if k > n then B(n, k) is equal to B(n, n);                   *
 *              - if k <= n then B(n, k) is equal to the sum of n choose k1    *
 *                where k1 ranges over {0, ..., k}.                            *
 *              The values B(n, k) determine the Bernouilli rectangle,         *
 *              whose rows are computed similarly to the rows of               *
 *              Pascal triangle. The program makes direct use of B(., .),      *
 *              and indirect use of H(., .).                                   * 
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       bernouilli.c                                                          *         
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bernouilli.h"

int nb_of_drops_needed(const int, const int);

int main(void) {
    /* The n from the program description. */
    int n;
    do {
        printf("Enter the number of floors (a strictly positive number): ");
        rewind(stdin);
    } while ((!scanf("%d", &n) || n < 1 ) && !fflush(stdin));
    /* The m from the program description. */
    int m;
    do {
        printf("Enter the number of marbles (a strictly positive number): ");
        rewind(stdin);
    } while ((!scanf("%d", &m) || m < 1 ) && !fflush(stdin));
    /* The d from the program description. */
    int d = nb_of_drops_needed(n, m);
    printf("At most %d drops will be needed.\n\n", d);
    /* Compute and store B(i, k) for all i in {0, ..., d - 1} and k in {0, ..., m - 1}. */
    unsigned long long bernouilli_rows[d][m];
    for (int i = 0; i < m; ++i)
        bernouilli_rows[0][i] = 1;
    for (int i = 1; i < d; ++i)
        bernouilli_next_row_up_to(i, m - 1, bernouilli_rows[i], bernouilli_rows[i - 1]);
    /* The highest floor such that it is known that a marble dropped from that floor
     * does not break. */
    int low = 0;
    /* The smallest floor such that it is known that a marble dropped from that floor
     * breaks (it is convenient to assume that a glass dropped from a level one more
     * than the height of the building breaks). */
    int high = n + 1;
    int drop = 0;
    int marble = 1;
    srand(time(NULL));
    /* We randomly make marbles break on one of floors 1, 2, ..., n + 1
     * (in case the value is n + 1, the marble does not break when dropped from
     * any floor of the building). */
    const int breaking_floor = rand() % (n + 1) + 1;
    while (low < high - 1) {
        int floor = fmin(low + bernouilli_rows[--d][m - 1], high - 1);
        if (breaking_floor <= floor) {
            printf("Drop #%d with marble #%d, from floor %d... marble breaks!\n",
                   ++drop, marble++, floor);
            high = floor;
            --m;
        }
        else {
            printf("Drop #%d with marble #%d, from floor %d... marble does not break!\n",
                   ++drop, marble, floor);
            low = floor;
        }
    }
    return EXIT_SUCCESS;
}

/* Computes the least d with H(d, m) >= n,
 * taking advantage of the fact that when k >= i, H(i, k) = B(i, k) - 1 = 2^i - 1. */
int nb_of_drops_needed(const int n, const int m) {
    int d = 1;
    int height = 1;
    while (height < n && ++d <= m)
        height = pow(2, d) - 1;
    if (height >= n)
        return d;
    unsigned long long bernouilli_row[m + 1];
    bernouilli_row_up_to(d, m, bernouilli_row);
    while (bernouilli_row[m] - 1 < n)
        bernouilli_change_to_next_row_up_to(++d, m, bernouilli_row);
    return d;
}

