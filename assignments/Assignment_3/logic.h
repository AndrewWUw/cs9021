#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include <stdio.h>

typedef struct formula *Formula;
typedef struct interpretation *Interpretation;

void get_constants(FILE *);
void get_predicates(FILE *);
Formula make_formula();
Interpretation make_interpretation(FILE *);
bool is_syntactically_correct(Formula);
bool is_true(Formula, Interpretation);
bool is_satisfiable(Formula);

#endif
