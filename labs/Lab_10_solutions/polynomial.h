#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stdio.h>
#include <stdbool.h>

typedef struct monomial {
    int coeff;
    int degree;
    struct monomial *next_monomial;
} Monomial;

typedef Monomial *Polynomial;

void free_poly(Polynomial);
void display_poly(Polynomial);
bool read_poly(FILE *, Polynomial *);
Polynomial add_polys(Polynomial, Polynomial);
Polynomial multiply_polys(Polynomial, Polynomial);
Polynomial divide_polys(Polynomial, Polynomial);

#endif



