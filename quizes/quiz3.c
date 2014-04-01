/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for a floating point number in base 3         *
 *              represented as a dot                                           *
 *               - preceded by between 1 and 20 digits equal to 0, 1 or 2,     *
 *                 the first of which is not 0 and is possibly preceded by     *
 *                 + or -, and                                                 *
 *               - followed by between 0 and 10 digits equal to 0, 1 or 2.     *
 *               Outputs a representation of this number in base 10            *
 *               and in base 2.                                                *
 *                                                                             *
 * Written by Eric Martin and *** for COMP9021                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define MAX_SIZE 32
#define PRECISION 10

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double convertCharToFloat(int flag, char characters[]);

int main(void) {
	printf(	"Enter a floating point number in base 3 represented as a dot\n"
		"- preceded by between 1 and 20 digits equal to 0, 1 or 2,\n"
		"the first of which is not 0 and is possibly preceded by + or -, and\n"
		"- followed by between 0 and 10 digits equal to 0, 1 or 2:\n");
	char characters[MAX_SIZE];
	int length = 0;
	int c;
	while ((c = getchar()) != '\n')
		characters[length++] = c;
	characters[length] = '\0';
	double number;
	char sign = '+';
	int exponent = 0;
	int mantissa[PRECISION] = { 0 };

	// Convert char array to double
	if (characters[0] == '+') {
		number = convertCharToFloat(1, characters);
	} else if (characters[0] == '-') {
		sign = '-';
		number = -1 * convertCharToFloat(1, characters);
	} else {
		number = convertCharToFloat(0, characters);
	}

	printf("The number that has been input is approximately equal to %f\n",	number);
	printf("In base 2, this number is approximately equal to %c1.", sign);

	double temp = 0;
        
	number = fabs(number);
	for (int i = 0; i < MAX_SIZE; i++) {
		if (number / pow(2, i) < 2 && number / pow(2, i) >= 1) {
			exponent = i;
			temp = number / pow(2, i) - 1;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (temp - pow(2, 0 - i - 1) >= 0) {
			mantissa[i] = 1;
			temp = temp - pow(2, 0 - i - 1);
		}

	}
        
	for (int i = 0; i < PRECISION; ++i)
		if (mantissa[i])
			putchar('1');
		else
			putchar('0');
	printf(" * 2^%d\n", exponent);
	return EXIT_SUCCESS;
}

/*******************************************************
 * Convert input char array to double and return
 ******************************************************/
double convertCharToFloat(int flag, char characters[]) {
	double number = 0;
	int length = 0;
	int dot = 0;

	for (int i = 0; i < 32; i++) {
		if (characters[i] != '\0') {
			length++;
			if (characters[i] == '.') {
				dot = i;
			}
		} else if (characters[i] == '\0')
			i = 32;
	}

	int dec[dot];
	int fra[length - dot - 1];
	for (int i = 0; i < length; i++) {
		if (i < dot)
			dec[i] = characters[i] - '0';
		else if (i > dot)
			fra[i - dot - 1] = characters[i] - '0';
	}

	for (int i = flag; i < dot; i++) {
		number += pow(3, dot - i - 1) * dec[i];
	}
	for (int i = 0; i < length - dot - 1; i++) {
		number += pow(3, -i - 1) * fra[i];
	}
	return number;
}


