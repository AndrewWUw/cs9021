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

void process_command_line_arguments(char **argv, int argc) {
	char *temp;

	for (int i = 1; i < argc; i++) {
		temp = *&argv[i];
		cleanData(*&argv[i], sizeof(*&argv[i]));
		for (int j = i; j < argc; j++) {
//			if (isEven(i)) {
//				if (i != 0) {
//
//				}
//			}
//		arg
		}
//		printf("%d \n", (*temp) - '0');
	}

}

void swap(char *arr1, char *arr2) {
	char *temp;
	temp = arr1;
	arr1 = arr2;
	arr2 = temp;
}

bool isEven(int pos) {
	return (pos % 2 == 0) ? true : false;
}

void cleanData(char *data, int size) {
	int count;
	char temp[size];
	for (int i = 0; i < size; i++) {
		if (isdigit(data[i])) {
			count++;
		}
		temp[i] = &data[i];
		printf("%d\n", temp[i] - '0');
	}

	char newArr[count];
	for (int i = size - 1; i >= 0; i--) {
		int pos = 0;
		if (isdigit(temp[i])) {
//			newArr[pos] = data[i];
			data[pos] = temp[i];
			pos++;
		}
	}
//	return *newArr;
}

