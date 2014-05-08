/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out the values of some predefined macros                *
 *              and identifiers.                                               *
 *                                                                             *
 * Purpose: Illustrates the use of the __LINE__, __FILE__, __DATE__ and        *
 *          __TIME__ predefined macros and of the __func__ predefined          *
 *          identifier.                                                        *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

void f(void);

int main(void) {
    printf("Printing values of predefined macros occurring on line %d\n"
           "                                               of file %s\n"
           "                                                    on %s\n"
           "                                                    at %s\n",
           __LINE__, __FILE__, __DATE__, __TIME__);
    printf("Printing the name of the calling function:             %s\n", __func__);
    f();
    return EXIT_SUCCESS;
}

void f(void) {
    printf("Printing the name of the called function:              %s\n", __func__);
}


