/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by *** for COMP9021                                                 *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *        logic.c                                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "logic.h"

int main(void) {
     FILE *file = fopen("names.txt", "r");
     if (!file) {
          printf("Could not open names file. Bye!\n");
          return EXIT_FAILURE;
     }
     get_constants(file);
     fclose(file);
     file = fopen("predicates.txt", "r");
     if (!file) {
          printf("Could not open predicates file. Bye!\n");
          return EXIT_SUCCESS;
     }
     get_predicates(file);
     fclose(file);
     printf("Input possible formula: ");     
     Formula form = make_formula();
     if (!form || ! is_syntactically_correct(form)) {
          printf("Possible formula is not a formula.\n");
          return EXIT_SUCCESS;
     }
     printf("Possible formula is indeed a formula.\n");
     file = fopen("true_atoms.txt", "r");
     if (!file) {
          printf("Could not open interpretation file. Bye!\n");
          return EXIT_FAILURE;
     }
     Interpretation interp = make_interpretation(file);
     fclose(file);
     if (is_true(form, interp)) {
          printf("Formula is true in given interpretation.\n");
          return EXIT_SUCCESS;
     }
     printf("Formula is false in given interpretation.\n");
     if (is_satisfiable(form))
          printf("Formula is satisfiable.\n");
     else
          printf("Formula is not satisfiable.\n");
    return EXIT_SUCCESS;
}
