/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Expects a command line argument,                               *
 *              prompts the user for a character,                              *
 *              reads a character from a file,                                 *
 *              displays the three on the screen                               *
 *              and writes them to a file.                                     *
 *                                                                             *
 * Purpose: Illustrates the different ways of dealing with input and output.   *
 *                                                                             *
 * Usage: - The user is expected to provide a character                        *
 *          as command line argument.                                          *
 *        - The user will be prompted to enter a character.                    *
 *        - The first character of a file named input_file.txt,                *
 *          stored in the working directory, will be read.                     *
 *                                                                             *
 * Note: This is a terrible program as it expects that everything              *
 *       will work smoothly, in particular, that the data will be              *
 *       available as expected, and does not take any action in case           *
 *       any misadventure happens.                                             *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    /* A datum provided as command line argument */
    const char a = argv[1][0];

    /* A datum entered by the user prompted to do so */
    printf("Enter a character please: ");
    const char b = getchar();

    /* A datum read from a file */
    FILE *const pt_to_input_file = fopen("input_file.txt", "r");
    const char c = fgetc(pt_to_input_file);
    
    FILE *const pt_to_output_file = fopen("output_file.txt", "w");
    printf("I have seen the characters %c, %c and %c\n", a, b, c); 
    fprintf(pt_to_output_file, "I have kept track of the characters %c, %c and %c\n", a, b, c);
    return EXIT_SUCCESS;
}

