/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: This program tries and move in memory forever to larger        *
 *              addresses, read the values stored at those addresses,          *
 *              and print them out.                                            *
 *              It should crash at some point.                                 *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char n;
    char *address_where_n_s_value_is_stored = &n;
    while (true)
        printf("%c\n", *++address_where_n_s_value_is_stored);     
    return EXIT_SUCCESS;
}

