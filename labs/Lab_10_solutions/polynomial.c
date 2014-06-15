/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Other source files, if any, one per line, starting on the next line:        *
 *       test_poly.c                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "polynomial.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

static bool get_monom(FILE *, int *, int *);
static bool expand_poly(int c, Polynomial *, FILE *);
static void add_monom_to_poly(int, int, Polynomial *);
static Polynomial copy_poly(Polynomial);
static void multiply_monom_to_poly(int, int, Polynomial);

void free_poly(Polynomial poly) {
    Monomial *next;
    while (poly) {
        next = poly->next_monomial;
        free(poly);
        poly = next;
    }
}

bool read_poly(FILE *file, Polynomial *poly) {
    int c, coeff, degree;
    int first_monomial = true;
    while ((c = getc(file)) != '\n' && c != EOF) {
        if (isspace(c))
            continue;
        if (!first_monomial) {
            if (!expand_poly(c, poly, file))
                return false;
            continue;
        }
        ungetc(c, file);
        if (!get_monom(file, &coeff, &degree))
            return false;
        if (coeff) {
            Monomial *monom = malloc(sizeof(Monomial));
            assert(monom);
            monom->coeff = coeff;
            monom->degree = degree;
            monom->next_monomial = NULL;
            *poly = monom;
            first_monomial = false;
        }
    }
    return true;
}

bool get_monom(FILE *file, int *coeff, int *degree) {
    int c;
    bool has_coeff = true;
    /* Monomial starts with x */
    if (fscanf(file, "%d", coeff) != 1) {
        *coeff = 1;
        has_coeff = false;
    }
    if ((c = getc(file)) != 'x') {
        if (!has_coeff)
            return false;
        ungetc(c, file);
        *degree = 0;
        return true;
    }
    if ((c = getc(file)) != '^') {
       ungetc(c, file);
        *degree = 1;
        return true;
    }
    assert(isdigit(c = getc(file)));
    ungetc(c, file);
    fscanf(file, "%d", degree);
    return true;
}

bool expand_poly(int c, Polynomial *poly, FILE *file) {
    if (c != '+' && c != '-')
        return false;
    int coeff, degree;
    if (!get_monom(file, &coeff, &degree))
        return false;
    if (coeff) {
        if (c == '-')
            coeff *= -1;
        add_monom_to_poly(coeff, degree, poly);
    }
    return true;
}

void add_monom_to_poly(int coeff, int degree, Polynomial *poly) {
    Monomial *current = *poly;
    Monomial *previous = NULL;
    while (current) {
        if (current->degree == degree) {
            if (current->coeff == -coeff) {
                if (!previous)
                    *poly = (*poly)->next_monomial;
                else
                    previous->next_monomial = current->next_monomial;
                free(current);
            }
            else
                current->coeff += coeff;
            return;
        }
        else if (current->degree < degree) {
            Monomial *monom = malloc(sizeof(Monomial));
            assert(monom);
            monom->coeff = coeff;
            monom->degree = degree;
            if (!previous) {
                monom->next_monomial = *poly;
                *poly = monom;
            }
            else {
                monom->next_monomial = current;
                previous->next_monomial = monom;
            }
            return;
        }
        previous = current;
        current = current->next_monomial;
    }
    Monomial *monom = malloc(sizeof(Monomial));
    assert(monom);
    monom->coeff = coeff;
    monom->degree = degree;
    monom->next_monomial = NULL;
    if (!previous)
        *poly = monom;
    else
        previous->next_monomial = monom;
}

void display_poly(Polynomial poly) {
    if (!poly) {
        printf("    0\n");
        return;
    }
    if (poly->coeff == -1)
        printf("    -");
    else if (poly->coeff != 1)
        printf("    %d", poly->coeff);
    else
        printf("    ");
    if (poly->degree == 1)
        putchar('x');
    else if (poly->degree)
        printf("x^%d", poly->degree);
    else
        putchar('1');
    Monomial *current = poly->next_monomial;
    while (current) {
        if (current->coeff == -1)
            printf(" - ");
        else if (current->coeff == 1)
            printf(" + ");
        else if (current-> coeff > 0)
            printf(" + %d", current->coeff);
        else
            printf(" - %d", abs(current->coeff));
        if (current->degree == 1)
            putchar('x');
        else if (current->degree)
            printf("x^%d", current->degree);
        else if (abs(current->coeff) == 1)
            putchar('1');
        current = current->next_monomial;
    }
    putchar('\n');
}

Polynomial add_polys(Polynomial poly1, Polynomial poly2) {
    Polynomial poly = copy_poly(poly1);
    Monomial *current = poly2;
    while (current) {
        add_monom_to_poly(current->coeff, current->degree, &poly);
        current = current->next_monomial;
    }
    return poly;
}

Polynomial copy_poly(Polynomial poly) {
    Polynomial copy = NULL;
    if (!poly)
        return copy;
    Monomial *current = poly, *previous = NULL, *current_copy, *previous_copy;
    while (current) {
        current_copy = malloc(sizeof(Monomial));
        assert(current_copy);
        if (!previous)
            copy = current_copy;
        else
            previous_copy->next_monomial = current_copy;
        current_copy->coeff = current->coeff;
        current_copy->degree = current->degree;
        previous = current;
        previous_copy = current_copy;
        current = current->next_monomial;
    }
    current_copy->next_monomial = NULL;
    return copy;
}

void multiply_monom_to_poly(int coeff, int degree, Polynomial poly) {
    Monomial *previous = NULL;
    while (poly) {
        poly->coeff *= coeff;
        poly->degree += degree;
        previous = poly;
        poly = poly->next_monomial;
    }
}

Polynomial multiply_polys(Polynomial poly1, Polynomial poly2) {
    Polynomial product = NULL;
    if (!poly1 || !poly2)
        return product;
    Monomial *current = poly2;
    while (current) {    
        Polynomial poly = copy_poly(poly1);
        multiply_monom_to_poly(current->coeff, current->degree, poly);
        current = current->next_monomial;
        if (!product)
            product = copy_poly(poly);
        else {
            Polynomial sum = add_polys(product, poly);
            free_poly(product);
            product = sum;
        }
        free_poly(poly);
    }
    return product;
}

Polynomial divide_polys(Polynomial poly1, Polynomial poly2) {
    Polynomial tmp = copy_poly(poly1);
    Polynomial quotient = NULL;
    while (tmp) {
        double coeff = (double)tmp->coeff / poly2->coeff;
        int degree = tmp->degree - poly2->degree;
        if (coeff != (int)coeff || degree < 0)
            return NULL;
        Polynomial poly2_copy = copy_poly(poly2);
        multiply_monom_to_poly(-(int)coeff, degree, poly2_copy);
        Polynomial sum = add_polys(tmp, poly2_copy);
        free_poly(poly2_copy);
        free_poly(tmp);
        tmp = sum;
        add_monom_to_poly((int)coeff, degree, &quotient);
    }
    free_poly(tmp);
    return quotient;
    return NULL;
}

    
