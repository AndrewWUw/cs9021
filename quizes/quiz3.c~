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

int main(void) {
    printf("Enter a floating point number in base 3 represented as a dot\n"
           "- preceded by between 1 and 20 digits equal to 0, 1 or 2,\n"
           "the first of which is not 0 and is possibly preceded by + or -, and\n"
           "- followed by between 0 and 10 digits equal to 0, 1 or 2:\n");
    char characters[MAX_SIZE];
    int i = 0;
    int c;
    while ((c = getchar()) != '\n')
        characters[i++] = c;
    characters[i] = '\0';
    double number;
    char sign = '+';
    int exponent = 0;
    int mantissa[PRECISION] = {0};
     /* ... REPLACE THIS COMMENT WITH YOUR CODE ... */
    // Convert char array to double
    i = 0;
    int dot = 0;
    for(int k = 0; k < 32; k++) {
        if (characters[k] != '\0') {
            i++;
            if (characters[k] == '.'){
                dot = k;
            }
        }else if (characters[k] == '\0') 
            k = 32;                       
    }

    int dec[dot];
    int fra[i - dot - 1];
    for(int j = 0; j < i; j++) {
        if(j < dot)
            dec[j] = characters[j] - '0';
        else if(j > dot)
            fra[j - dot - 1] = characters[j] - '0';
    }
    
    for (i = 0; i < dot; i++) {
        number += pow(10, i) + dec[i];
    }

    for (i = 0; i < i - dot -1; i++) {
        number += pow(10, 0 - i) + fra[i];
    }
    
    
    
    printf("The number that has been input is approximately equal to %f\n", number);
    printf("In base 2, this number is approximately equal to %c1.", sign);
    for (i = 0; i < PRECISION; ++i)
        if (mantissa[i])
            putchar('1');
        else
            putchar('0');
    printf(" * 2^%d\n", exponent);
    return EXIT_SUCCESS;
}
