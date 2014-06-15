/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes as command line argument a single string that represents *
 *              an arithmetic expression written in reverse Polish notation.   *
 *              Evaluates the expression and outputs the result.               *      
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_correct(const char *const, const int);
int evaluate(const char *const, int *const, int *const);
int number(const char *const, int *const, const int *const);

int main(int argc, char **argv) {
    char *expression;
    if (argc == 2)
        expression = *++argv;
    else {
        printf("A single string should be provided as command-line argument.\n");
        return EXIT_FAILURE;
    }
    int length = strlen(expression);
    if (!is_correct(expression, length--)) {
        printf("Input is not syntactically correct.\n");
        return EXIT_FAILURE;
    }
    int start = -1;
    printf("%d\n", evaluate(expression, &start, &length));
    return EXIT_SUCCESS;
}

/* Checks that string provided as input, together with its length,
 * is syntactically correct. The input is scanned with a counter set to 0.
 * When a number is encountered the counter is increased by 1.
 * When an operator is encountered the counter is decreased by 1.
 * The input is correct if the counter is never going down from 1 to 0
 * and its final value is 1. */
bool is_correct(const char *const expression, const int length) {
    int rank = 0, i = 0;
    while (i < length) {
        if (expression[i] == ' ')
            ++i;
        else if (isdigit(expression[i])) {
            while (++i < length && isdigit(expression[i]))
                ;
            ++rank;
        }
        else if (rank > 1 && (expression[i] == '+' ||
                              expression[i] == '-' ||
                              expression[i] == '*' ||
                              expression[i] == '/')) {
            --rank;
            ++i;
        }
        else
            return false;
    }
    return rank == 1;
}
     
/* Evaluates the expession pointed to from position after position pointed to by m
 * to position pointed to by n. */        
int evaluate(const char *const expression, int *const m, int *const n) {
    int *i = m, *j = n;
    int left, right;   
    while (expression[*j] == ' ') {
        --*j;
    }
    if (expression[*j] == '+') {
        --*j;
        right = evaluate(expression, i, j);
        left = evaluate(expression, m, i);
        return left + right;
    }
    if (expression[*j] == '-') {
        --*j;
        right = evaluate(expression, i, j);
        left = evaluate(expression, m, i);
        return left - right;
    }
    if (expression[*j] == '*') {
        --*j;
        right = evaluate(expression, i, j);
        left = evaluate(expression, m, i);
        return left * right;
    }
    if (expression[*j] == '/') {
        --*j;
        right = evaluate(expression, i, j);
        if (right == 0) {
            printf("Division by zero.\n");
            exit(EXIT_FAILURE);
        }
        left = evaluate(expression, m, i);        
        return left / right;
    }
    return number(expression, i, j);
}

/* Determines the value of the number located at an offset whose value
 * is located at m from expression to the offset whose value
 * is located at n from expression. */
int number(const char *const expression, int *const m, const int *const n) {
    int i = *n;
    int number = expression[i] - '0';
    int factor = 1;
    while (isdigit(expression[--i])) {
        factor *= 10;
        number += factor * (expression[i] - '0');
    }
    *m = i;
    return number;
}
   
    
