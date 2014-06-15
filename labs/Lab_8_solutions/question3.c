/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Expects some command line arguments and behaves as follows.    *
 *              - If no command line is provided then the program prints out   *
 *                  "Provide at least one command line argument!"              *
 *                and stops.                                                   *
 *              - If some command line argument does not consist of nonzero    *
 *                digits only, then the program prints out                     *
 *                  "Invalid command line arguments!"                          *
 *                and stops.                                                   *
 *              - Otherwise, the program proceeds as follows:                  *
 *                . It prints the first digit d_1 of the first command line    *
 *                  argument, which is considered to be 'eaten up.'            *
 *                . If there are at least d_1 command line arguments and       *
 *                  not all digits of the d_1^{st} command line argument have  *
 *                  been eaten up, then it prints the first digit d_2 of the   *
 *                  d_1^{st} command line argument that has not been eaten up. *
 *                . If there are at least d_2 command line arguments and not   *
 *                  all digits of the d_2^{nd} command line argument have been *
 *                  eaten up, then it prints the first first digit d_3 of the  *
 *                  d_2^{nd} command line argument that has not been eaten up. *
 *                . Etc., until no digit can be printed any more.              *
 *                For instance, if the command line arguments are "312 3 215"  *
 *                then the program prints out and eats up 3 at the beginning   *
 *                of 312, looks at the 3rd command line argument, prints out   *
 *                and eats up 2 at the beginning of 215, looks at the 2nd      *
 *                command line  argument, prints out and eats up 3 (so there   *
 *                is nothing left from the 2nd command line argument), looks   *
 *                at the 3rd command line argument, prints out and eats up 1   *
 *                in the middle of 215, looks at the 1st command line          *
 *                argument, prints out and eats up 1 in the middle of 312,     *
 *                looks at the 1st command line argument again and prints out  *
 *                and eats up 2 at the end of 312 (so there is nothing left    *
 *                from the 1st command line argument), and as there is nothing *
 *                left from the 2nd command line argument, stops.              *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Provide at least one command line argument!\n");
        return EXIT_SUCCESS;
    }
    for (int i = 1; i < argc; ++i)
        for (int j = 0; j < strlen(argv[i]); ++j)
            if (argv[i][j] < '1' || argv[i][j] > '9') {
                printf("Invalid command line arguments!\n");
                return EXIT_SUCCESS;
            }
    int t = 0;
    for (int i = 1; i < argc; ++i)
        t += strlen(argv[i]);
    char *output = malloc(t * sizeof(char));
    int n = 1;
    int i = 0;
    while (true) {
        if (*argv[n] && '0' < *argv[n] && *argv[n] <= '9') {
            output[i++] = *argv[n];
            int p = n;
            if (*argv[n] - '0' < argc) {
                n = *argv[n] - '0';
                ++argv[p];
            }
            else
                break;
        }
        else
            break;
    }
    for (int j = 0; j < i; ++j)
        putchar(output[j]);
    putchar('\n');
    return EXIT_SUCCESS;
}

