/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out two numbers and three stars.                        *   
 *                                                                             *
 * Purpose: Illustrates the use of the #if, #elif, #ifdef, #ifndef and         *
 *          #endif commands and the defined operator.                          *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define CHOICE
#define FIRST_CHOICE 0
#define SECOND_CHOICE 1
#define THIRD_CHOICE 1

#if FIRST_CHOICE
const int n = 10;
const int m = 15;
#elif SECOND_CHOICE
const int n = 20;
const int m = 25;
#elif THIRD_CHOICE
const int n = 30;
const int m = 35;
#endif

#define STARS
#define EXCLAMATION_MARKS
#define QUESTION_MARKS
#define PERCENT_SIGNS
#ifdef CHOICE
#define STARS "***"
#endif
#ifndef FIRST_CHOICE
#define EXCLAMATION_MARKS "!!!"
#endif
#if defined(SECOND_CHOICE)
#define QUESTION_MARKS "???"
#endif
#if defined FOURTH_CHOICE
#define PERCENT_SIGNS "%%%%"
#endif

int main(void) {
    printf("%d %d\n", n, m);
    printf(STARS EXCLAMATION_MARKS QUESTION_MARKS PERCENT_SIGNS"\n");
    return EXIT_SUCCESS;
}

