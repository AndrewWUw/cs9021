/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Given two strings sigma and tau of lowercase letters,          *
 *              say that tau is a "good subsequence" of sigma if tau           *
 *              is obtained from sigma by deleting (possibly empty) initial    *
 *              and final segments of sigma, with two consecutive letters      *
 *              in tau being such that the first one is alphabetically before  *
 *              the second one. For instance, u, aef, bh, bcd and de are       *
 *              amongst the good subsequences of uaeffbhbcdde.                 *
 *                                                                             *
 *              Prompts the user to input a sequence of at most 20 lowercase   *
 *              letters on one line, ending in carriage return, and prints out *
 *              the longest, lexicographically first good subsequence          *
 *              of the input (between two good subsequences of different       *
 *              length, the longest is preferred; between two good             *
 *              subsequences of the same length, the one that comes first      *
 *              lexicographically is preferred).). The program reports an      *
 *              error message in case the input contains nonlowercase letters  *
 *              or more than 20 lowercase letters before the final new line    *
 *              character.                                                     *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char input[20];
    int length[20];
    int c;
    int size = 0;
    printf("Enter input: ");   
    while ((c = getchar()) != '\n') {
        if (!islower(c) || size == 20) {
            printf("Input is incorrect or too long.\n");
            return EXIT_FAILURE;
        }
        input[size++] = c;
    }
    for (int i = 0; i < size; ++i) {
        length[i] = 1;
        for (int j = 0; j < i; ++j)
            if (j + length[j] == i && input[j + length[j] - 1] < input[i])
                ++length[j];
    }
    int begin = 0;
    for (int i = 1; i < size; ++i)
        if (length[i] > length[begin])
            begin = i;
    for (int j = 0; j < size; ++j)
        if (length[j] == length[begin])
            for (int k = 0; k < length[begin]; ++k) {
                if (input[j + k] < input[begin + k]) {
                    begin = j;
                    break;
                }
                if (input[j + k] > input[begin + k])
                    break;
            }
    printf("The solution is: %.*s\n", length[begin], input + begin);
    return EXIT_SUCCESS;
}
