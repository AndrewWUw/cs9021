/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Other source files, if any, one per line, starting on the next line:        *
 *       polynomial.c                                                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main(int argc, char **argv) {
    FILE *file = fopen(argv[1], "r");
    if (!file)
        return EXIT_FAILURE;
    Polynomial poly1 = NULL, poly2 = NULL;
    if (!read_poly(file, &poly1))
        return EXIT_FAILURE;
    if (!read_poly(file, &poly2))
        return EXIT_FAILURE;
    printf("The polynomials are:\n");
    display_poly(poly1);
    display_poly(poly2);
    Polynomial poly3 = add_polys(poly1, poly2);
    printf("The sum of the polynomials is:\n");
    display_poly(poly3);
    free_poly(poly3);
    Polynomial poly4 = multiply_polys(poly1, poly2);
    printf("The product of the polynomials is:\n");
    display_poly(poly4);
    free_poly(poly4);
    if (!poly2)
        printf("The first polynomial is not divisible by the second one.\n");
    else if (!poly1)
        printf("The quotient of the first polynomial by the second one is:\n    0\n");
    else {
        Polynomial poly5 = divide_polys(poly1, poly2);
        if (!poly5)
            printf("The first polynomial is not divisible by the second one.\n");
        else {
            printf("The quotient of the first polynomial by the second one is:\n");
            display_poly(poly5);
            free_poly(poly5);
        }
    }
    free_poly(poly1);
    free_poly(poly2);
    return EXIT_SUCCESS;
}
    
