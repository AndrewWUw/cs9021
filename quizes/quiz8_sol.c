/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Opens a file named input.txt for reading and a file named      *
 *              output a file named output.txt for writing, and outputs        *
 *              in the latter all words from the former form last to first.    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *input_file = fopen("input.txt", "r");
    if (!input_file) {
        printf("Please create a file named \"input.txt\""
                " in the working directory.\n");
        return EXIT_FAILURE;
    }
    FILE *output_file = fopen("output.txt", "w");
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    for (int i = 1; i <= file_size; ++i) {
        int j = i;
        while (j <= file_size) {
            fseek(input_file, -j, SEEK_END);
            if (isalpha(getc(input_file)))
                break;
            ++j;
        }
        if (j > file_size)
            break;
        while (++j <= file_size) {
            fseek(input_file, -j, SEEK_END);
            if (!isalpha(getc(input_file)))
                break;
        }
        i = j;
        fseek(input_file, -i + 1, SEEK_END);
        int c;
        while (isalpha(c = getc(input_file)))
            fputc(c, output_file);
        fputc('\n', output_file);
    }
    fclose(input_file);
    fclose(output_file);
    return EXIT_SUCCESS;
}
