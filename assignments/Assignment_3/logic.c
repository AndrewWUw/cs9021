#include "logic.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

#define MAXSIZE 1000
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}

typedef enum {
    NORMAL = 0, NOT, AND, OR, IMPLIES, IFF
} TYPE;

struct predicate {
    char *predicate_name;
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

/* Global variables declaration */
int name_sum;
int predicate_sum;
int true_formula_sum;
int false_formula_sum;

char *name[MAXSIZE];
char *predicate_name[MAXSIZE];
Formula true_formula[MAXSIZE];
Formula false_formula[MAXSIZE];

/* Function declaration */

// formulas
void get_input_formula(char *buf);
void generate_formula(char **buf, Formula *formula);
void store_normal_formual(Formula *formula, char **buf);
void check_opts(char **buf, Formula *formula);
bool is_correct_predicate_and_aritys(char *predicat_name, int predicat_name_sum);
bool is_correct_predicate_names(char *names[], int num);

// interpretations
void process_single_interpretation(Interpretation *inte, char *atom, int intepret_index);
void process_interpretation_names(Single_Interpretation *inter, char *atom, int name_index);
bool match_formula(Formula formula, Interpretation interpretation);
bool is_a_match(Formula formula, Interpretation interpretation);
bool match_formula_pred_names(char *names1[], char *names2[], int len);

// satisfiable
bool find_satisfiable(Formula formula, bool required_condition);
bool is_in_formula_array(Formula formula, bool array_type);
bool is_satisfy_normal_form(Formula formula, bool required_condition);
void write_to_file(FILE *file);

// Helper functions
int get_File_Contents(FILE *file, char *desc[]);
bool is_valid_c_identifiers(char c);

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
        predicates[i].predicate_name = malloc(sizeof(char) * strlen(predicate_name[i]));
        char *token = malloc(sizeof(char) * strlen(predicate_name[i]));
        strcpy(token, predicate_name[i]);

        token = strtok(token, "/");
        strcpy(predicates[i].predicate_name, token);

        token = strchr(predicate_name[i], '/');
        ++token;
        int arity = atoi(token);
        predicates[i].arity = arity;

    }
}

Formula make_formula() {
    char *buf = malloc(sizeof(char) * MAXSIZE);

    get_input_formula(buf);

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
    while ((c = getchar()) != EOF) {
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

    int i = 0;
    for (i = 0; i < strlen(*buf); ++i) {
        if (is_valid_c_identifiers((*buf)[i])) {
            (*formula)->predicate_name[i] = (*buf)[i];
        } else {
            (*formula)->predicate_name[i] = '\0';
            break;
        }
    }
    *buf += i;

    (*formula)->name_num = 0;

    // process names
    if (*buf[0] == '(') {
        i = 0;
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
    bool is_correct;

    if (formula->type == NORMAL) {
        if (formula->subf1 != NULL || formula->subf2 != NULL)
            is_correct = false;
        else {
            bool is_correct_names;
            bool is_correct_preds;
            is_correct_preds = is_correct_predicate_and_aritys(formula->predicate_name, formula->name_num);
            is_correct_names = is_correct_predicate_names(formula->name, formula->name_num);
            is_correct = is_correct_names && is_correct_preds;
        }
    }

    if (formula->type == NOT) {
        bool is_correct_names;
        bool is_correct_preds;
        is_correct_preds = is_correct_predicate_and_aritys(formula->predicate_name, formula->name_num);
        is_correct_names = is_correct_predicate_names(formula->name, formula->name_num);
        is_correct = is_correct_names && is_correct_preds;
    }

    if (formula->subf1 != NULL)
        is_correct = is_syntactically_correct(formula->subf1);

    if (formula->subf2 != NULL)
        is_correct = is_syntactically_correct(formula->subf2);

    return is_correct;
}

bool is_correct_predicate_and_aritys(char *predicat_name, int predicat_name_sum) {

    // check for correct predicate
    bool is_pred_correct = false;
    for (int i = 0; i < predicate_sum; ++i) {
        if (strcmp(predicat_name, predicates[i].predicate_name) == 0 && predicat_name_sum == predicates[i].arity)
            is_pred_correct = true;
    }

    return is_pred_correct;
}

bool is_correct_predicate_names(char *names[], int num) {
    // check if names correct
    bool is_name_correct[num];
    bool is_correct = true;

    int i = 0, j = 0;
    for (i = 0; i < num; ++i) {
        for (j = 0; j < name_sum; ++j) {
            if (strcmp(names[i], name[j]) == 0) {
                is_name_correct[i] = true;
                break;
            } else
                is_name_correct[i] = false;
        }
    }

    i = 0;
    while (i < num) {
        is_correct = is_correct && is_name_correct[i];
        ++i;
    }

    return is_correct;
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
    return match_formula(formula, interpretation);
}

bool match_formula(Formula formula, Interpretation interpretation) {

    switch (formula->type) {
    case NORMAL:
        return is_a_match(formula, interpretation);
        break;
    case NOT:
        return !is_a_match(formula, interpretation);
        break;
    case AND:
        return match_formula(formula->subf1, interpretation) && match_formula(formula->subf2, interpretation);
        break;
    case OR:
        return match_formula(formula->subf1, interpretation) || match_formula(formula->subf2, interpretation);
        break;
    case IMPLIES:
        return !(match_formula(formula->subf1, interpretation) && !match_formula(formula->subf2, interpretation));
        break;
    case IFF:
        return (match_formula(formula->subf1, interpretation) && match_formula(formula->subf2, interpretation))
                || (!match_formula(formula->subf1, interpretation) && !match_formula(formula->subf2, interpretation));
        break;
    default:
        break;
    }
}

bool is_a_match(Formula formula, Interpretation inter) {

    for (int i = 0; i < inter->interp_num; ++i) {
        if (strcmp(inter->s_intepret[i]->predicate_name, formula->predicate_name) == 0) {
            bool is_correct;
            bool is_correct_pred_name = true;
            bool is_corect_arity_name;

            is_corect_arity_name = match_formula_pred_names(formula->name, inter->s_intepret[i]->name, inter->s_intepret[i]->name_num);

            is_correct = is_correct_pred_name && is_corect_arity_name;
            if (is_correct) {
                return is_correct;
            }
        }
    }
    return false;
}

bool match_formula_pred_names(char *names1[], char *names2[], int len) {

    bool is_name_correct[len];
    bool is_correct = true;

    for (int i = 0; i < len; ++i) {
        if (strcmp(names1[i], names2[i]) == 0) {
            is_name_correct[i] = true;
        } else
            is_name_correct[i] = false;
    }

    int i = 0;
    while (i < len) {
        is_correct = is_correct && is_name_correct[i];
        ++i;
    }

    return is_correct;
}

bool is_satisfiable(Formula formula) {

    bool ret;
    true_formula_sum = 0;
    false_formula_sum = 0;

    ret = find_satisfiable(formula, 1);

    if (ret) {
        FILE *file;
        file = fopen("witnesses_satisfiability.txt", "wb");
        if (!file)
            printf("Could not open witnesses_satisfiability file.\n");

        write_to_file(file);
        fclose(file);
    }

    return ret;
}

bool find_satisfiable(Formula formula, bool required_condition) {

    switch (formula->type) {
    case NORMAL:
        return is_satisfy_normal_form(formula, required_condition);
        break;
    case NOT:
        return is_satisfy_normal_form(formula, !required_condition);
        break;
    case AND:
        return find_satisfiable(formula->subf1, true) && find_satisfiable(formula->subf2, true);
        break;
    case OR:
        if (formula->subf2->type == NOT)
            return find_satisfiable(formula->subf2, true) || find_satisfiable(formula->subf1, true);
        else
            return find_satisfiable(formula->subf1, true) || find_satisfiable(formula->subf2, true);
        break;
    case IMPLIES:
        if (find_satisfiable(formula->subf1, true) && find_satisfiable(formula->subf2, false))
            return false;
        else
            return true;
        break;
    case IFF:
        if (find_satisfiable(formula->subf1, true) && find_satisfiable(formula->subf2, true))
            return true;
        else {
            if (find_satisfiable(formula->subf1, true))
                --true_formula_sum;
            if (find_satisfiable(formula->subf2, true))
                --true_formula_sum;
            return find_satisfiable(formula->subf1, false) && find_satisfiable(formula->subf2, false);
        }
        break;
    }
}

bool is_satisfy_normal_form(Formula formula, bool required_condition) {

    if (is_in_formula_array(formula, !required_condition)) {
        return false;
    } else {
        if (!is_in_formula_array(formula, required_condition) && required_condition) {
            true_formula[true_formula_sum] = formula;
            ++true_formula_sum;
        } else {
            false_formula[false_formula_sum] = formula;
            ++false_formula_sum;
        }

        return true;
    }
}

bool is_in_formula_array(Formula formula, bool array_type) {
    Formula *form;
    int len;
    if (array_type) {
        form = true_formula;
        len = true_formula_sum;
    } else {
        form = false_formula;
        len = false_formula_sum;
    }

    for (int i = 0; i < len; ++i) {
        if (strcmp(formula->predicate_name, form[i]->predicate_name) == 0) {
            bool is_correct;
            bool is_correct_pred_name = true;
            bool is_corect_arity_name;

            is_corect_arity_name = match_formula_pred_names(formula->name, form[i]->name, form[i]->name_num);

            is_correct = is_correct_pred_name && is_corect_arity_name;
            if (is_correct) {
                return is_correct;
            }
        }
    }
    return false;
}

void write_to_file(FILE *file) {

    for (int i = 0; i < true_formula_sum; ++i) {
        fprintf(file, "%s", true_formula[i]->predicate_name);

        if (true_formula[i]->name_num) {
            fprintf(file, "(");

            for (int j = 0; j < true_formula[i]->name_num; ++j) {
                fprintf(file, "%s", true_formula[i]->name[j]);
                if (j != true_formula[i]->name_num - 1) {
                    fprintf(file, ",");
                }
            }

            fprintf(file, ")");
        }
        fprintf(file, "\n");
    }

}
