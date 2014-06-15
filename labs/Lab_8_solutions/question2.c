/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Say that two strings s_1 and s_2 can be merged into a third    *
 *              string s_3 if s_3 is obtained from s_1 by inserting            *
 *              arbitrarily in s_1 the characters in s_2, respecting their     *
 *              order. For instance, the two strings ab and cd can be merged   *
 *              into abcd, or cabd, or cdab, or acbd, or acdb..., but not into *
 *              adbc nor into cbda.                                            *
 *                                                                             *
 *              Takes three command line arguments and displays the output as  *
 *              follows.                                                       *
 *              - If fewer or more than 3 command-line arguments have been     *
 *                provided then the program outputs an error message.          *
 *              - Otherwise, if no command line argument can be obtained from  *
 *                the other two by merging, then the program outputs that      *
 *                thre is no solution.                                         *
 *              - Otherwise, the program outputs which of the command line     *
 *                arguments can be obtained from the other two by merging.     *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool can_merge(const char *const, const char *const, const char *const);

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Incorrect number of command line arguments!\n");
        return EXIT_SUCCESS;
    }
    int last = 1;
    if (strlen(argv[2]) > strlen(argv[last]))
        last = 2;
    if (strlen(argv[3]) > strlen(argv[last]))
        last = 3;
    int first, second;
    if (last == 1) {
        first = 2;
        second = 3;
    }
    else if (last == 2) {
        first = 1;
        second = 3;
    }
    else {
        first = 1;
        second = 2;
    }
    if (strlen(argv[last]) != strlen(argv[first]) + strlen(argv[second]) ||
        !can_merge(argv[first], argv[second], argv[last]))
        printf("No solution\n");
    else
        printf("The %s string can be obtained by merging the other two.\n",
               last == 1 ? "first" : last == 2 ? "second" : "third");
    return EXIT_SUCCESS;
}

bool can_merge(const char *const first, const char *const second, const char *const last) {
    if (!*first && !strcmp(second, last))
        return true;
    if (!*second && !strcmp(first, last))
        return true;
    if (!*first || !*second)
        return false;
    if (*first == *last && can_merge(first + 1, second, last + 1))
        return true;
    if (*second == *last && can_merge(first, second + 1, last + 1))
        return true;
    return  false;
}

    
