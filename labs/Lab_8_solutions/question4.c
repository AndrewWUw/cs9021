/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user to enter some sequence of distinct digits     *
 *              ending in a new line character, with no other character, not   *
 *              even spaces, before the final new line character, and behaves  *
 *              as follows.                                                    *
 *              - If more than 10 characters (including spaces) are input      *
 *                before the final new line character then the program prints  *
 *                out                                                          *
 *                  "Input is too long!"                                       *
 *                and stops.                                                   *
 *              - Otherwise, if some character is not a digit then the         *
 *                program prints out                                           *
 *                  "Input is invalid!"                                        *
 *                and stops.                                                   *
 *              - Otherwise, if some digit occurs twice in the input then the  *
 *                program prints out                                           *
 *                  "Duplicate digits in input!"                               *
 *                and stops.                                                   *
 *              - Then the program prompts the user for an integer l, assumed  *
 *                to be correctly entered and readable by scanf(), and outputs *
 *                the number of increasing subsequences of the first input of  *
 *                length l at least.                                           *
 *                For instance, the sequence is 34125 has one increasing       *
 *                subsequence of length 0, five increasing subsequences of     *
 *                length 1, namely, 3, 4, 1, 2 and 5, six increasing           *
 *                subsequences of length 2, namely, 34, 35, 45, 12, 15 and 25, *
 *                two increasing sequences of length 3, namely, 345 and 125,   *
 *                and no increasing sequence of length greater than 3. Hence   *
 *                the sequence is 34125 has no increasing sequence of length 4 *
 *                at least, two increasing sequences of length 3 at least,     *
 *                eight increasing sequences of length 2 at least, thirteen    *
 *                increasing sequences of length 1 at least, and fourteen      *
 *                increasing sequences of length 0 at least.                   *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int f(const int, const int, const int);

char input[10];
int input_length;
int desired_length;

int main(void) {
    printf("Enter sequence of digits of length 10 at most: ");
    char c;
    bool invalid_input = false;
    while ((c = getchar()) != '\n') {
        if (input_length == 10) {
            printf("Input is too long!\n");
            return EXIT_SUCCESS;
        }   
        if (!isdigit(c))
            invalid_input = true;
        input[input_length++] = c - '0';
    }
    if (invalid_input) {
        printf("Input is invalid!\n");
        return EXIT_SUCCESS;
    }
    for (int i = 0; i < input_length; ++i)
        for (int j = i + 1; j < input_length; ++j)
            if (input[i] == input[j]) {
                printf("Duplicate digits in input!\n");
                return EXIT_SUCCESS;
            }
    printf("Enter desired length: ");
    scanf("%d", &desired_length);
    printf("Number of increasing sequences of length %d at least: %d\n",
           desired_length, f(0, 0, 0));
    return EXIT_SUCCESS;
}

int f(const int s, const int t, const int i) {
    if (i < input_length)
        if (t <= input[i])
            return f(s + 1, input[i], i + 1) + f(s, t, i + 1);
        else
            return f(s, t, i + 1);
     if (s >= desired_length)
        return 1;
    return 0;
}

    
