/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Tests the functions declared in polynomial.h                   *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       polynomial.c                                                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main(int argc, char **argv) {
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Could not find a file named %s.\n", argv[1]);
        return EXIT_FAILURE;
    }
    Polynomial *pt_to_poly1, *pt_to_poly2;
    initialize_poly(&pt_to_poly1);
    initialize_poly(&pt_to_poly2);
    if (!read_poly(file, pt_to_poly1) || !read_poly(file, pt_to_poly2)) {
        printf("The input is incorrect.\n");
        return EXIT_FAILURE;
    }
    printf("The polynomials are:\n");
    display_poly(pt_to_poly1);
    display_poly(pt_to_poly2);
    Polynomial *pt_to_poly3 = add_polys(pt_to_poly1, pt_to_poly2);
    printf("The sum of the polynomials is:\n");
    display_poly(pt_to_poly3);
    free_poly(pt_to_poly3);
    Polynomial *pt_to_poly4 = multiply_polys(pt_to_poly1, pt_to_poly2);
    printf("The product of the polynomials is:\n");
    display_poly(pt_to_poly4);
    free_poly(pt_to_poly4);
    if (!pt_to_poly2->nb_of_monomials)
        printf("The first polynomial is not divisible by the second one.\n");
    else if (!pt_to_poly1->nb_of_monomials)
        printf("The quotient of the first polynomial by the second one is:\n    0\n");
    else {
        Polynomial *pt_to_poly5 = divide_polys(pt_to_poly1, pt_to_poly2);
        if (!pt_to_poly5)
            printf("The first polynomial is not divisible by the second one.\n");
        else {
            printf("The quotient of the first polynomial by the second one is:\n");
            display_poly(pt_to_poly5);
            free_poly(pt_to_poly5);
        }
    }
    free_poly(pt_to_poly1);
    free_poly(pt_to_poly2);
    return EXIT_SUCCESS;
}

    
