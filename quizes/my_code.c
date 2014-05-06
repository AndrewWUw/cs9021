/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Keeps only digits and stores them in reverse order             *
 *              in the reordered command line arguments, where the             *
 *              first one remains first, the second one becomes last,          *
 *              the third one becomes second, the fourth one becomes           *
 *              penultimate, etc.                                              *
 * Written by *** for COMP9021                                                 *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       quiz7.c                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void cleanData(char *data);
void sort(int argc, char **argv, int offset);
void swap(char *, char *);
bool isEven(int pos);
void moveElement(int argc, char **argv, int offset);
void outPutArgs(int argc, char **argv);

void process_command_line_arguments(char **argv, int argc) {

	for (int i = 1; i < argc; i++) {
		cleanData(*&argv[i]);
		if (!isEven(i) && i > 1) {
				moveElement(argc, argv, i);
		}

	}

//	if (isEven(argc)) {
//		for (int i = (argc - 2); i > 1; i -= 2) {
//			sort(argc, argv, i);
//		}
//	} else {
//		for (int i = (argc - 3); i > 1; i -= 2) {
//			sort(argc, argv, i);
//		}
//
//	}
}

void moveElement(int argc, char **argv, int offset) {
	for (int i = offset; i < argc; i++) {
		swap(*&argv[i], *&argv[i - 1]);
	}
	outPutArgs(argc, argv);
}

void swap(char *arr1, char *arr2) {
	char temp;
	temp = *arr1;
	*arr1 = *arr2;
	*arr2 = temp;
}

void sort(int argc, char **argv, int offset) {
	char *temp;
	while (offset < argc - 1) {
		temp = *(argv + offset);
		*(argv + offset) = *(argv + offset + 1);
		*(argv + offset + 1) = temp;
//		swap(*(argv + offset), *(argv + offset + 1));
		offset++;
	}
}

bool isEven(int pos) {
	return (pos % 2 == 0) ? true : false;
}

void cleanData(char *data) {
	int count = 0;
	int size = 0;

	while (data[size++] != '\0') {
		if (isdigit(data[size - 1])) {
			count++;
		}
	}
	size--;

	char temp[count];
	int pos = 0;
	for (int i = size - 1; i >= 0; i--) {
		if (isdigit(data[i])) {
			temp[pos] = data[i];
			pos++;
		}
	}
	for (int i = 0; i < count; i++) {
		data[i] = temp[i];
	}
	data[count] = '\0';

	count = 0;
	size = 0;
	while (data[size++] != '\0') {
		if (isdigit(data[size - 1])) {
			count++;
		}
	}
}

void outPutArgs(int argc, char **argv) {
	for (int i = 1; i < argc; i++)
		printf("%s  ", argv[i]);
	printf("\n");
}
