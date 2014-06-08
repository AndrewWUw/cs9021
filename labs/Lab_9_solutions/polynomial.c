/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Implements the functions declared in polynomial.h              *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       test.c                                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "polynomial.h"

static bool get_monomial(int, Monomial **, FILE *const);
static bool get_number(int c, int *const, FILE *const);
static bool expand_poly(const int, Polynomial *const, FILE *const);
static void add_monomial_to_poly(const int, const int, Polynomial *const);
static Polynomial *copy_poly(const Polynomial *const);
static void multiply_monomial_to_poly(const int, const int, Polynomial *const);

void initialize_poly(Polynomial **const pt_to_pt_to_poly) {
    Polynomial *pt_to_poly = malloc(sizeof(Polynomial));
    assert(pt_to_poly);
    pt_to_poly->nb_of_monomials = 0;
    pt_to_poly->monomials = NULL;
    *pt_to_pt_to_poly = pt_to_poly;
}

void free_poly(Polynomial *pt_to_poly) {
    if (pt_to_poly->nb_of_monomials)
        free(pt_to_poly->monomials);
    free(pt_to_poly);
}

/* W.r.t. the polynomial 0, we set pt_to_poly->monomials to NULL
 * rather than having a monomial with a coefficient of 0.  */
bool read_poly(FILE *const file, Polynomial *const pt_to_poly) {
    bool first_monomial_processed = false;
    int c;
    /* In case the input file has only one line or not line at all,
     * we set the second polynomial or both polynomials to 0, respectively. */
    while ((c = getc(file)) != '\n' && c != EOF) {
        if (isblank(c))
            continue;
        if (first_monomial_processed) {
            if (!expand_poly(c, pt_to_poly, file))
                return false;
            continue;
        }
        Monomial *pt_to_monomial;
        if (!get_monomial(c, &pt_to_monomial, file))
            return false;
        if (!pt_to_monomial)
            pt_to_poly->nb_of_monomials = 0;
        else
            pt_to_poly->nb_of_monomials = 1;
        pt_to_poly->monomials = pt_to_monomial;
        first_monomial_processed = true;
    }
    return true;
}

bool get_monomial(int c, Monomial **pt_to_pt_to_monomial, FILE *const file) {
    int coefficient;
    if (!get_number(c, &coefficient, file))
        return false;
    /* Monomial is a constant. */
    if ((c = getc(file)) != 'x') {
        ungetc(c, file);
        if (coefficient == 0) {
            *pt_to_pt_to_monomial = NULL;
            return true;
        }
        Monomial *pt_to_monomial = malloc(sizeof(Monomial));
        assert(pt_to_monomial);
        pt_to_monomial->coeff = coefficient;
        pt_to_monomial->degree = 0;
        *pt_to_pt_to_monomial = pt_to_monomial;
        return true;
    }
    int degree;
    if (coefficient == 0) {
        *pt_to_pt_to_monomial = NULL;
        /* We have seen x. If monomial is of the form "coefficient x^exponent"
         * then get rid of "^exponent". */
        if ((c = getc(file)) != '^') {
            ungetc(c, file);
            return true;
        }
        if ((c = getc(file)) == '-')
            return false;
        if (c == '+')
            c = getc(file);
        if (!get_number(c, &degree, file))
            return false;
        return true;
    }   
    Monomial *pt_to_monomial = malloc(sizeof(Monomial));
    assert(pt_to_monomial);
    pt_to_monomial->coeff = coefficient;
    if ((c = getc(file)) != '^') {
        ungetc(c, file);
        pt_to_monomial->degree = 1;
    }
    else {
        if ((c = getc(file)) == '-')
            return false;
        if (c == '+')
            c = getc(file);
        if (!get_number(c, &degree, file))
            return false;
        pt_to_monomial->degree = degree;
    }
    *pt_to_pt_to_monomial = pt_to_monomial;
    return true;
}

bool get_number(int c, int *const coefficient, FILE *const file) {
    if (c == '-') {
        if (!isdigit(c  = getc(file)))
            return false;
        *coefficient = -1;
    }
    else if (c == '+') {
        if (!isdigit(c  = getc(file)))
            return false;
        *coefficient = 1;
    }
    else if (isdigit(c))
        *coefficient = 1;
    else if (c == 'x') {
        *coefficient = 1;
        ungetc(c, file);
        return true;
    }
    else
        return false;
    if (c == '0') {
        if (isdigit(c  = getc(file)))
            return false;
        *coefficient = 0;
        ungetc(c, file);
        return true;
    }
    *coefficient *= c - '0';
    while (isdigit(c  = getc(file)))
        *coefficient = *coefficient * 10 + c - '0';
    ungetc(c, file);
    return true;
}           

bool expand_poly(const int operation, Polynomial *const poly, FILE *const file) {
    if (operation != '+' && operation != '-')
        return false;
    char c;
    while (isblank(c  = getc(file)))
        continue;
    Monomial *pt_to_monomial;
    if (!get_monomial(c, &pt_to_monomial, file))
        return false;
    if (!pt_to_monomial)
        return true;
    if (operation == '-')
        pt_to_monomial->coeff *= -1;
    add_monomial_to_poly(pt_to_monomial->coeff, pt_to_monomial->degree, poly);
    return true;
}

void add_monomial_to_poly(const int coefficient, const int degree, Polynomial *const pt_to_poly) {
    int i;
    for (i = 0; i < pt_to_poly->nb_of_monomials && pt_to_poly->monomials[i].degree <= degree; ++i)
        if (pt_to_poly->monomials[i].degree == degree) {
            if (pt_to_poly->monomials[i].coeff != -coefficient) {
                pt_to_poly->monomials[i].coeff += coefficient;
                return;
            }
            /* Get rid of monomial of index i.
             * Part of the allocated memory is not used any more,
             * but there is no point in reallocating memory to request less of it. */
            for (int j = i; j < pt_to_poly->nb_of_monomials - 1; ++j)
                pt_to_poly->monomials[j] = pt_to_poly->monomials[j + 1];
            --pt_to_poly->nb_of_monomials;
            return;
        }
    pt_to_poly->monomials = realloc(pt_to_poly->monomials, sizeof(Monomial) * ++pt_to_poly->nb_of_monomials);
    for (int j = pt_to_poly->nb_of_monomials - 1; j >= i; --j)
        pt_to_poly->monomials[j] = pt_to_poly->monomials[j - 1];
    pt_to_poly->monomials[i].coeff = coefficient;
    pt_to_poly->monomials[i].degree = degree;
}

void display_poly(Polynomial *const poly) {
    if (poly->nb_of_monomials == 0) {
        printf("    0\n");
        return;
    }
    if (poly->monomials->coeff == -1)
        printf("    -");
    else if (poly->monomials->coeff != 1)
        printf("    %d", poly->monomials->coeff);
    else
        printf("    ");
    if (poly->monomials->degree == 1)
        putchar('x');
    else if (poly->monomials->degree)
        printf("x^%d", poly->monomials->degree);
    else if (poly->monomials->coeff == 1)
        putchar('1');
    for (int i = 1; i < poly->nb_of_monomials; ++i) {
        if (poly->monomials[i].coeff == -1)
            printf(" - ");
        else if (poly->monomials[i].coeff == 1)
            printf(" + ");
        else if (poly->monomials[i].coeff > 0)
            printf(" + %d", poly->monomials[i].coeff);
        else
            printf(" - %d", abs(poly->monomials[i].coeff));
        if (poly->monomials[i].degree == 1)
            putchar('x');
        else if (poly->monomials[i].degree)
            printf("x^%d", poly->monomials[i].degree);
    }
    putchar('\n');
}

Polynomial *add_polys(const Polynomial *const pt_to_poly1, const Polynomial *const pt_to_poly2) {
    Polynomial *pt_to_poly = copy_poly(pt_to_poly1);
    for (int i = 0; i < pt_to_poly2->nb_of_monomials; ++i)
        add_monomial_to_poly(pt_to_poly2->monomials[i].coeff,
                             pt_to_poly2->monomials[i].degree, pt_to_poly);
    return pt_to_poly;
}

Polynomial *copy_poly(const Polynomial *const pt_to_poly) {
    Polynomial *pt_to_copy;
    initialize_poly(&pt_to_copy);
    pt_to_copy->nb_of_monomials = pt_to_poly->nb_of_monomials;
    if (!pt_to_poly->nb_of_monomials)
        return pt_to_copy;
    Monomial *monomials = malloc(sizeof(Monomial) * pt_to_poly->nb_of_monomials);
    assert(monomials);
    pt_to_copy->monomials = monomials;
    for (int i = 0; i < pt_to_poly->nb_of_monomials; ++i)
        monomials[i] = pt_to_poly->monomials[i];
    return pt_to_copy;
}

void multiply_monomial_to_poly(const int coefficient, const int degree, Polynomial *const pt_to_poly) {
    if (coefficient == 0 && pt_to_poly->nb_of_monomials) {
        free(pt_to_poly->monomials);
        pt_to_poly->nb_of_monomials = 0;
        pt_to_poly->monomials = NULL;
        return;
    }
    for (int i = 0; i < pt_to_poly->nb_of_monomials; ++i) {
        pt_to_poly->monomials[i].degree += degree;
        pt_to_poly->monomials[i].coeff *= coefficient;
    }
}

Polynomial *multiply_polys(const Polynomial *const pt_to_poly1, const Polynomial *const pt_to_poly2) {
    Polynomial *pt_to_product;
    initialize_poly(&pt_to_product);
    if (!pt_to_poly1->nb_of_monomials || !pt_to_poly2->nb_of_monomials)
        return pt_to_product;
    for (int i = 0; i < pt_to_poly2->nb_of_monomials; ++i) {
        Polynomial *pt_to_copy = copy_poly(pt_to_poly1);
        multiply_monomial_to_poly(pt_to_poly2->monomials[i].coeff,
                                  pt_to_poly2->monomials[i].degree, pt_to_copy);
        Polynomial *pt_to_sum = add_polys(pt_to_copy, pt_to_product);
        free_poly(pt_to_copy);
        if (pt_to_product->nb_of_monomials)
            free(pt_to_product->monomials);
        pt_to_product->nb_of_monomials = pt_to_sum->nb_of_monomials;
        if (pt_to_sum->nb_of_monomials)
            pt_to_product->monomials = pt_to_sum->monomials;
        free(pt_to_sum);
    }
    return pt_to_product;
}

Polynomial *divide_polys(const Polynomial *const pt_to_poly1, const Polynomial *const pt_to_poly2) {
    Polynomial *pt_to_poly = copy_poly(pt_to_poly1);
    Polynomial *pt_to_quotient;
    initialize_poly(&pt_to_quotient);
    Polynomial *pt_to_sum;
    while (pt_to_poly->nb_of_monomials) {
        double coefficient = (double)pt_to_poly->monomials->coeff / pt_to_poly2->monomials->coeff;
        int degree = pt_to_poly->monomials->degree - pt_to_poly2->monomials->degree;
        if (coefficient != (int)coefficient || degree < 0) {
            free(pt_to_poly);
            return NULL;
        }
        Polynomial *pt_to_poly2_copy = copy_poly(pt_to_poly2);
        multiply_monomial_to_poly(-(int)coefficient, degree, pt_to_poly2_copy);
        pt_to_sum = add_polys(pt_to_poly, pt_to_poly2_copy);
        free_poly(pt_to_poly2_copy);
        free(pt_to_poly->monomials);
        pt_to_poly->nb_of_monomials = pt_to_sum->nb_of_monomials;
        pt_to_poly->monomials = pt_to_sum->monomials;
        free(pt_to_sum);
        add_monomial_to_poly((int)coefficient, degree, pt_to_quotient);
    }
    free_poly(pt_to_poly);
    free(pt_to_sum);
    return pt_to_quotient;
}

