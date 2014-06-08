#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int coeff;
    int degree;
} Monomial;

typedef struct {
    int nb_of_monomials;
    Monomial *monomials;
} Polynomial;

void initialize_poly(Polynomial **const );
void free_poly(Polynomial *);
void display_poly(Polynomial *const);
bool read_poly(FILE *const, Polynomial *const);
Polynomial *add_polys(const Polynomial *const, const Polynomial *const);
Polynomial *multiply_polys(const Polynomial *const, const Polynomial *const);
Polynomial *divide_polys(const Polynomial *const, const Polynomial *const);

#endif



