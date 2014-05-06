/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Keeps only digits and stores them in reverse order             *
 *              in the reordered command line arguments, where the             *
 *              first one remains first, the second one becomes last,          *
 *              the third one becomes second, the fourth one becomes           *
 *              penultimate, etc.                                              *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       my_code.c                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void process_command_line_arguments(char **, int);

int main(int argc, char **argv) {
    process_command_line_arguments(argv, argc);
	for (int i = 1; i < argc; ++i)
		printf("  %s", argv[i]);
	putchar('\n');
    return EXIT_SUCCESS;
}

