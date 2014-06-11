#include "logic.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

#define MAXSIZE 1000

typedef enum {
    NORMAL = 0, NOT, AND, OR, IMPLIES, IFF
} TYPE;

struct predicate {
    char *predicat_name;
    int arity;
} predicates[MAXSIZE];

struct formula {
    TYPE type;
    char *predicate_name;
    char *name[100];
    int name_num;
    Formula subf1;
    Formula subf2;
    bool is_subf;
};

typedef struct single_interpretation {
    char *predicate_name;
    char *name[100];
    int name_num;
}*Single_Interpretation;

struct interpretation {
    struct single_interpretation *s_intepret[MAXSIZE];
    int interp_num;
};

struct t_f_table {
    Formula needtobetrue[MAXSIZE];
    Formula needtobefalse[MAXSIZE];
    int needtobetrue_size;
    int needtobefalse_size;
};

/* Global variables declaration */
int name_sum;
int predicate_sum;
int interpretation_size;
char *name[MAXSIZE];
char *predicate_name[MAXSIZE];
int aritys[MAXSIZE];

/* Function declaration */

// formulas
void get_input_formula(char *buf);
void generate_formula(char **buf, Formula *formula);
void store_normal_formual(Formula *formula, char **buf);
void check_opts(char **buf, Formula *formula);
bool is_syntactically_correct(Formula formula);
bool is_correct_predicate(char *name, int name_sum);

// interpretations
void process_single_interpretation(Interpretation *inte, char *atom, int intepret_index);
void process_interpretation_names(Single_Interpretation *inter, char *atom, int name_index);

// Helper functions
int get_File_Contents(FILE *file, char *desc[]);

bool is_valid_c_identifiers(char c);
bool in_needtobetrue(Formula formula, struct t_f_table * tf_tb);
bool in_needtobefalse(Formula formula, struct t_f_table * tf_tb);
bool make_true(Formula formula, int target, struct t_f_table * tf_tb);
bool get_value(Formula formula, Interpretation interpretation);
bool is_same(Formula formula, Interpretation interpretation);

int get_File_Contents(FILE *file, char *desc[]) {
    char *temp = malloc(sizeof(char) * MAXSIZE);
    char *token;
    char *delim = " ";
    int i = 0;

    while (!feof(file)) {
        fgets(temp, MAXSIZE, file);

        if (temp[strlen(temp) - 1] == '\n')
            temp[strlen(temp) - 1] = 0;

        token = strtok(temp, delim);
        while (token != NULL) {
            desc[i] = malloc(sizeof(char) * strlen(token));
            strcpy(desc[i], token);
            token = strtok(NULL, delim);
            ++i;
        }
    }
    free(temp);

    return i;
}

void get_constants(FILE *file) {
    name_sum = get_File_Contents(file, name);
}

void get_predicates(FILE * file) {
    predicate_sum = get_File_Contents(file, predicate_name);

    for (int i = 0; i < predicate_sum; ++i) {
        predicates[i].predicat_name = malloc(sizeof(char) * strlen(predicate_name[i]));
        char *token = malloc(sizeof(char) * strlen(predicate_name[i]));
        strcpy(token, predicate_name[i]);

        token = strtok(token, "/");
        strcpy(predicates[i].predicat_name, token);

        token = strchr(predicate_name[i], '/');
        ++token;
        int arity = atoi(token);
        predicates[i].arity = arity;

        for (int j = 0; j < strlen(predicate_name[i]); ++j) {
            if (predicate_name[i][j] == '/') {
                aritys[i] = atoi(predicate_name[i] + j + 1);
                predicate_name[i][j] = '\0';
                j += 2;
            }
        }
    }
}

Formula make_formula() {
    char *buf = malloc(sizeof(char) * MAXSIZE);

    get_input_formula(buf);
    // printf("input str is: %s\n", buf);

    // check if input is illegal
    for (int i = 0; i < strlen(buf); ++i)
        // valid input: ' ', \n, \t, [, ], ',', (, ), 0-9, A-Z, a-z
        if (!(isspace(buf[i]) || isdigit(buf[i]) || isalpha(buf[i]) || buf[i] == '[' || buf[i] == ']' || buf[i] == '_' || buf[i] == '(' || buf[i] == ')' || buf[i] == ','))
            return NULL;

    Formula formula = (Formula) malloc(sizeof(struct formula));
    generate_formula(&buf, &formula);

    return formula;
}

void get_input_formula(char *buf) {
    int c;
    int i = 1;

    // skip any space, \n and \t before formula
    while (isspace(c = getchar()) || c == '\n' || c == '\t')
        continue;

    buf[0] = c;
    while ((c = getchar()) != '\n') {
        // get input and remove duplicate spaces
        if (c == '\n' || c == '\t')
            c = ' ';

        if (isspace(c)) {
            if (buf[i - 1] == ' ' || buf[i - 1] == '[' || buf[i - 1] == '(')
                continue;
        } else if (isspace(c)) {
            continue;
        } else if ((c == ']' || c == ')' || c == '(') && (buf[i - 1] == ' ')) {
            buf[i - 1] = c;
            continue;
        }

        buf[i] = c;
        ++i;
    }
    buf[i] = '\0';

    // remove space in the end of input formula
    int buf_size = strlen(buf);
    for (i = buf_size - 1; i >= 0; --i) {
        if (isspace(buf[i]) && isspace(buf[i - 1]))
            --buf_size;
    }
    if (isspace(buf[buf_size - 1]))
        --buf_size;

    buf[buf_size] = '\0';
}

void generate_formula(char ** buf, Formula *formula) {

    if (isspace((*buf)[0]))
        *buf += 1;

    if ((*buf)[0] == '[') {
        // input is a combined formula
        *buf += 1;

        (*formula)->predicate_name = malloc(sizeof(char) * MAXSIZE);
        (*formula)->predicate_name = "";
        (*formula)->name_num = 0;

        // recursively create sub formula for current combined formula
        (*formula)->subf1 = (Formula) malloc(sizeof(struct formula));
        (*formula)->subf1->is_subf = true;
        generate_formula(buf, &((*formula)->subf1));

        check_opts(buf, formula);
        if (!(*formula) == NULL) {
            (*formula)->subf2 = (Formula) malloc(sizeof(struct formula));
            (*formula)->subf2->is_subf = true;
            generate_formula(buf, &((*formula)->subf2));
        }
        // every left-bracket must end with correspond right-bracket
        if ((*buf)[0] == ']') {
            *buf += 1;
        } else {
            *formula = NULL;
        }
    } else if (strncmp(*buf, "not ", 4) == 0) {
        // input is a not formula
        *buf += 4;
        if (!isalpha((*buf)[0]))
            *formula = NULL;
        else {
            generate_formula(buf, formula);
            (*formula)->type = NOT;
        }
    } else {
        (*formula)->type = NORMAL;
        (*formula)->predicate_name = (char *) malloc(sizeof(char) * MAXSIZE);

        store_normal_formual(formula, buf);
        if ((*formula)->is_subf == false && strlen(*buf) > 0)
            *formula = NULL;
    }
}

void store_normal_formual(Formula *formula, char **buf) {

    for (int i = 0; i < strlen(*buf); ++i) {
        if (is_valid_c_identifiers((*buf)[i])) {
            (*formula)->predicate_name[i] = (*buf)[i];
        } else {
            (*formula)->predicate_name[i] = 0;
            *buf += i;
            break;
        }
    }

    (*formula)->name_num = 0;
    // process names
    if (*buf[0] == '(') {
        int i = 0;
        *buf += 1;
        int pos = (*formula)->name_num;
        (*formula)->name[pos] = (char *) malloc(sizeof(char) * MAXSIZE);
        while ((*buf)[0] != ')') {
            if ((*buf)[0] == ',') {
                *buf += 1;
                pos = ++(*formula)->name_num;
                (*formula)->name[pos] = (char *) malloc(sizeof(char) * MAXSIZE);
                i = 0;
            } else {
                (*formula)->name[pos][i] = (*buf)[0];
                ++i;
                *buf += 1;
            }
        }
        (*formula)->name_num++;
        *buf += 1;
    }
    (*formula)->subf1 = NULL;
    (*formula)->subf2 = NULL;
}

void check_opts(char **buf, Formula *formula) {

    if (isspace(*buf[0]))
        *buf += 1;
    if (strncasecmp(*buf, "or ", 3) == 0) {
        (*formula)->type = OR;
        *buf += 3;
    } else if (strncasecmp(*buf, "and ", 4) == 0) {
        (*formula)->type = AND;
        *buf += 4;
    } else if (strncasecmp(*buf, "implies ", 8) == 0) {
        (*formula)->type = IMPLIES;
        *buf += 8;
    } else if (strncasecmp(*buf, "iff ", 4) == 0) {
        (*formula)->type = IFF;
        *buf += 4;
    } else {
        *formula = NULL;
    }
}

bool is_syntactically_correct(Formula formula) {
    bool is_correct = false;
    if (formula->type == NORMAL) {
        if (formula->subf1 != NULL || formula->subf2 != NULL)
            is_correct =  false;
        else
            is_correct = is_correct_predicate(formula->predicate_name, formula->name_num);
    } else if (formula->type == NOT) {
        is_correct =  is_correct_predicate(formula->predicate_name, formula->name_num);
    } else if (formula->subf1 != NULL) {
        is_correct= is_syntactically_correct(formula->subf1);
    } else if (formula->subf2 != NULL) {
        is_correct = is_syntactically_correct(formula->subf2);
    } else {
        is_correct= true;
    }
    return is_correct;
}

bool is_correct_predicate(char *name, int name_sum) {
    for (int i = 0; i < predicate_sum; ++i) {
        if (strcmp(name, predicates[i].predicat_name) == 0 && name_sum == predicates[i].arity)
            return true;
    }
    return false;
}

bool is_valid_c_identifiers(char c) {
    if (isalpha(c) || isdigit(c) || c == '_')
        return true;
    else
        return false;
}

Interpretation make_interpretation(FILE * file) {

    char *temp[MAXSIZE];
    int true_atom_num = get_File_Contents(file, temp);

    Interpretation interp;
    interp = (Interpretation) malloc(sizeof(struct interpretation));

    for (int i = 0; i < true_atom_num; ++i) {
        process_single_interpretation(&interp, temp[i], i);
    }

    interp->interp_num = true_atom_num;
//    for (int i = 0; i < true_atom_num; ++i) {
//        printf("interp : %s\n", interp->s_intepret[i]->predicate_name);
//        for (int j = 0; j < 100; ++j)
//            printf("name   : %s\n", *(interp->s_intepret[i])->name[j]);
//    }
    return interp;
}

void process_single_interpretation(Interpretation *inter, char *atom, int intepret_index) {

    bool has_lbracket = false;
    int i = 0;

    for (i = 0; i < strlen(atom); ++i) {
        if (atom[i] == '(') {
            has_lbracket = true;
            ++i;
            break;
        }
    }

    (*inter)->s_intepret[intepret_index] = (Single_Interpretation) malloc(sizeof(struct single_interpretation));
    (*inter)->s_intepret[intepret_index]->predicate_name = malloc(sizeof(char) * strlen(atom));
    (*inter)->s_intepret[intepret_index]->name_num = 0;

    if (!has_lbracket) {
        strcpy((*inter)->s_intepret[intepret_index]->predicate_name, atom);
    } else {
        char *token = malloc(sizeof(char) * strlen(atom));
        strcpy(token, atom);
        token = strtok(token, "(");
        strcpy((*inter)->s_intepret[intepret_index]->predicate_name, token);

        atom += i;

        ++(*inter)->s_intepret[intepret_index]->name_num;
        process_interpretation_names(&((*inter)->s_intepret[intepret_index]), atom, 0);
    }
}

void process_interpretation_names(Single_Interpretation *inter, char *atom, int name_index) {

    bool has_comma = false;
    int i = 0;
    for (i = 0; i < strlen(atom); ++i) {
        if (atom[i] == ',') {
            has_comma = true;
            ++i;
            break;
        }
    }

    (*inter)->name[name_index] = (char *) malloc(sizeof(char) * strlen(atom));
    if (!has_comma) {
        if (atom[strlen(atom) - 1] == ')')
            atom[strlen(atom) - 1] = '\0';

        strcpy((*inter)->name[name_index], atom);
    } else {
        char *token = malloc(sizeof(char) * strlen(atom));
        strcpy(token, atom);
        token = strtok(token, ",");
        strcpy((*inter)->name[name_index], token);

        atom += i;
        ++(*inter)->name_num;
        process_interpretation_names(inter, atom, (*inter)->name_num - 1);
    }
}

bool is_true(Formula formula, Interpretation interpretation) {
    return get_value(formula, interpretation);
}

bool get_value(Formula formula, Interpretation interpretation) {
    switch (formula->type) {
    case NORMAL:
        return is_same(formula, interpretation);
        break;
    case NOT:
        // printf("not %s\n", formula->predicate_name);
        // printf("%s %s\n", formula->name[0], formula->name[1]);
        // printf("%d\n", is_same(formula));
        return !is_same(formula, interpretation);
        break;
    case AND:
        return get_value(formula->subf1, interpretation) && get_value(formula->subf2, interpretation);
        break;
    case OR:
        return get_value(formula->subf1, interpretation) || get_value(formula->subf2, interpretation);
        break;
    case IMPLIES:
        return !(get_value(formula->subf1, interpretation) && !get_value(formula->subf2, interpretation));
        break;
    case IFF:
        return (get_value(formula->subf1, interpretation) && get_value(formula->subf2, interpretation)) || (!get_value(formula->subf1, interpretation) && !get_value(formula->subf2, interpretation));
        break;
    }
}

bool is_same(Formula formula, Interpretation inter) {
    int fail;
    for (int i = 0; i < inter->interp_num; ++i) {

        if (!strcmp(inter->s_intepret[i]->predicate_name, formula->predicate_name)) {
            if (formula->name_num != inter->s_intepret[i]->name_num)
                continue;

            fail = 0;
            for (int j = 0; j < formula->name_num; ++j) {
                // printf("%s %s\n", formula->name[j], interpretation[i].name[j]);
                if (strcmp(formula->name[j], inter->s_intepret[i]->name[j]) != 0) {
                    fail = 1;
                    break;
                }
            }
            if (!fail)
                return true;

        }
    }
    return false;
}

bool in_needtobetrue(Formula formula, struct t_f_table * tf_tb) {
    int fail;
    for (int i = 0; i < tf_tb->needtobetrue_size; ++i) {
        if (strcmp(tf_tb->needtobetrue[i]->predicate_name, formula->predicate_name) == 0) {
            if (formula->name_num != tf_tb->needtobetrue[i]->name_num) {
                continue;
            }
            fail = 0;
            for (int j = 0; j < formula->name_num; ++j) {
                if (strcmp(formula->name[j], tf_tb->needtobetrue[i]->name[j]) != 0) {
                    fail = 1;
                    break;
                }
            }
            if (!fail)
                return true;
        }
    }
    return false;
}

bool in_needtobefalse(Formula formula, struct t_f_table * tf_tb) {
    int fail;
    for (int i = 0; i < tf_tb->needtobefalse_size; ++i) {
        if (strcmp(tf_tb->needtobefalse[i]->predicate_name, formula->predicate_name) == 0) {
            if (formula->name_num != tf_tb->needtobefalse[i]->name_num) {
                continue;
            }
            fail = 0;
            for (int j = 0; j < formula->name_num; ++j) {
                if (strcmp(formula->name[j], tf_tb->needtobefalse[i]->name[j]) != 0) {
                    fail = 1;
                    break;
                }
            }
            if (!fail)
                return true;
        }
    }
    return false;
}

bool make_true(Formula formula, int target, struct t_f_table * tf_tb) {
    switch (formula->type) {
    case NORMAL:
        if (target) // to be true
        {
            // printf("in_needtobefalse(formula, tf_tb) %s %d\n", formula->predicate_name, in_needtobefalse(formula, tf_tb));
            if (in_needtobefalse(formula, tf_tb)) // can't be true
                return false;
            else {
                if (!in_needtobetrue(formula, tf_tb)) {
                    tf_tb->needtobetrue[tf_tb->needtobetrue_size] = formula;
                    tf_tb->needtobetrue_size++;
                }
                return true;
            }
        } else // to be false
        {
            // printf("in_needtobetrue(formula, tf_tb) %s %d\n", formula->predicate_name, in_needtobetrue(formula, tf_tb));
            if (in_needtobetrue(formula, tf_tb)) // can't be false
                return false;
            else {
                if (!in_needtobefalse(formula, tf_tb)) {
                    tf_tb->needtobefalse[tf_tb->needtobefalse_size] = formula;
                    tf_tb->needtobefalse_size++;
                }
                return true;
            }
        }
        break;
    case NOT:
        if (!target) // to be false
        {
            if (in_needtobefalse(formula, tf_tb)) // can't be true
                return false;
            else {
                if (!in_needtobetrue(formula, tf_tb)) {
                    tf_tb->needtobetrue[tf_tb->needtobetrue_size] = formula;
                    tf_tb->needtobetrue_size++;
                }
                return true;
            }
        } else // to be true
        {
            if (in_needtobetrue(formula, tf_tb)) // can't be false
                return false;
            else {
                if (!in_needtobefalse(formula, tf_tb)) {
                    tf_tb->needtobefalse[tf_tb->needtobefalse_size] = formula;
                    tf_tb->needtobefalse_size++;
                }
                return true;
            }
        }
        break;
    case AND:
        return make_true(formula->subf1, 1, tf_tb) && make_true(formula->subf2, 1, tf_tb);

        break;
    case OR:
        if (formula->subf2->type == NOT)
            return make_true(formula->subf2, 1, tf_tb) || make_true(formula->subf1, 1, tf_tb);
        else
            return make_true(formula->subf1, 1, tf_tb) || make_true(formula->subf2, 1, tf_tb);
        break;
    case IMPLIES:
        if (make_true(formula->subf1, 1, tf_tb) && make_true(formula->subf2, 0, tf_tb))
            return false;
        else
            return true;

        break;
    case IFF:
        if (make_true(formula->subf1, 1, tf_tb) && make_true(formula->subf2, 1, tf_tb))
            return true;
        else {
            if (make_true(formula->subf1, 1, tf_tb))
                tf_tb->needtobetrue_size--;
            if (make_true(formula->subf2, 1, tf_tb))
                tf_tb->needtobetrue_size--;

            return make_true(formula->subf1, 0, tf_tb) && make_true(formula->subf2, 0, tf_tb);
        }
        break;
    }
}

bool is_satisfiable(Formula formula) {
    struct t_f_table * tf_tb;
    tf_tb = malloc(sizeof(struct t_f_table));
    tf_tb->needtobetrue_size = 0;
    tf_tb->needtobefalse_size = 0;
    bool ret = make_true(formula, 1, tf_tb);
    if (ret) {
        FILE *fp;
        if ((fp = fopen("witnesses_satisfiability.txt", "wb")) == NULL) {
            printf("can't open\n");
        }
        // printf("%d\n", tf_tb->needtobetrue_size);
        for (int i = 0; i < tf_tb->needtobetrue_size; ++i) {
            fprintf(fp, "%s", tf_tb->needtobetrue[i]->predicate_name);
            if (tf_tb->needtobetrue[i]->name_num) {
                fprintf(fp, "(");
                for (int j = 0; j < tf_tb->needtobetrue[i]->name_num; ++j) {
                    fprintf(fp, "%s", tf_tb->needtobetrue[i]->name[j]);
                    if (j != tf_tb->needtobetrue[i]->name_num - 1) {
                        fprintf(fp, ",");
                    }
                }
                fprintf(fp, ")");
            }
            fprintf(fp, "\n");
        }

        fclose(fp);
    }

    return ret;
}

