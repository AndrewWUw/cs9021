/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Solves the tower and 2 glass marbles problem. The user is      *
 *              prompted to enter the number n of floors of a building. Using  *
 *              2 marbles, one has to discover the highest floor, if any,      *
 *              such that dropping a marble from that floor makes it break,    *
 *              using a strategy that minimises the number of drops in the     *
 *              worst case (it is assumed that any marble would break when     *
 *              dropped from a floor where one marble breaks, and also when    *
 *              dropped from any higher floor; the marbles might not break     *
 *              when dropped from any floor).                                  *
 *                                                                             *
 *              The idea is to ask: what is the maximum height h of a building *
 *              such that an answer can always be found with no more than d    *
 *              drops? It is easy to verify that h is the largest integer      *
 *              such that d + (d - 1) + (d - 2) + ... + 2 + 1 >= h, and that   *
 *              the strategy consists in dropping the first glass              *
 *              from floor d, then from floor d + (d - 1), then from floor     *
 *              d + (d - 1) + (d - 2), ..., until the marble breaks, if that   *
 *              ever happens. In case that happens and i is the least integer  *
 *              such that the glass breaks when dropped from floor             *
 *              d + ... + (d - i - 1) + (d - i), then one drops the second     *
 *              glass from floor d + ... + (d - i - 1) + 1,                    *
 *              and then from floor d + ... + (d - i - 1) + 2, etc.            *
 *              until the glass breaks, if that ever hapens.                   *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    /* The n from the program description. */
    int n;
    do {
        printf("Enter the number of floors (a strictly positive number): ");
        rewind(stdin);
    } while ((!scanf("%d", &n) || n < 1 ) && !fflush(stdin));
    /* The d from the program description, equal to the least integer such that
     * d + (d - 1) + (d - 2) + ... + 2 + 1 >= n. */
    int d = ceil((sqrt(8 * n + 1) - 1) / 2);
    printf("At most %d drops will be needed.\n\n", d);
    /* The highest floor such that it is known that a marble dropped from that floor
     * does not break. */
    int low = 0;
    /* The smallest floor such that it is known that a marble dropped from that floor
     * breaks (it is convenient to assume that a glass dropped from a level one more
     * than the height of the building breaks). */
    int high = n + 1;
    int drop = 0;
    const char *marble_nb = "first";
    srand(time(NULL));
    /* We randomly make marbles break on one of floors 1, 2, ..., n + 1
     * (in case the value is n + 1, the marble does not break when dropped from
     * any floor of the building). */
    const int breaking_floor = rand() % (n + 1) + 1;
    while (low < high - 1) {
        int floor = fmin(low + d, high - 1);
        if (breaking_floor <= floor) {
            printf("Drop #%d with %s marble, from floor %d... marble breaks!\n",
                   ++drop, marble_nb, floor);
            high = floor;
            d = 1;
            marble_nb = "second";
        }
        else {
            printf("Drop #%d with %s marble, from floor %d... marble does not break!\n",
                   ++drop, marble_nb, floor);
            low = floor;
            if (d > 1)
                --d;
        }
    }
    return EXIT_SUCCESS;
}

