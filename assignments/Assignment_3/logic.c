#include "logic.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

#define MAXSIZE 10000

typedef enum {
    NORMAL = 0, NOT, AND, OR, IMPLIES, IFF
} TYPE;

typedef struct predicate {
    char *predicat_name;
    int arity;
}*Predicate;

struct formula {
    TYPE type;
    char *predicate_name;
    char *name[100];
    int name_num;
    Formula subf1;
    Formula subf2;
};

struct interpretation {
    char *predicate_name;
    char *name[100];
    int name_num;
} interpretation[1000];

// Global variables declaration
int name_sum;
int predicate_sum;
int interpretation_size;
char *name[MAXSIZE];
char *predicate_name[MAXSIZE];
int args[MAXSIZE];
Predicate predicates[MAXSIZE];

// Function declaration
Formula generate_formula(char **buf);
void store_normal_formual(Formula *formula, char **buf);

void check_opts(char **buf, Formula *formula);

// interpretations
void process_interpretation_names(char *intepret, int intepret_index, int name_index);

// Helper functions
bool is_valid_c_identifiers(char c);
bool is_in_predicate_name(char *name);

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

//    for (int j = 0; j < i; ++j) {
//        printf("%s ", file_buf[j]);
//    }
//    printf("\n");

    return i;
}

void get_constants(FILE *file) {
    name_sum = get_File_Contents(file, name);
}

void get_predicates(FILE * file) {
    predicate_sum = get_File_Contents(file, predicate_name);

    for (int i = 0; i < predicate_sum; ++i) {
        // Predicate pred;
        // pred = (Predicate) malloc(sizeof(struct predicate));
        for (int j = 0; j < strlen(predicate_name[i]); ++j) {
            if (predicate_name[i][j] == '/') {
                // pred->predicat_name[j] = '\0';
                // pred->arity = atoi(predicate_name[i] + j + 1);
                args[i] = atoi(predicate_name[i] + j + 1);
                predicate_name[i][j] = '\0';
                j += 2;
            } //else {
              // pred->predicat_name[j] = predicate_name[i][j];
              // }
        }
        // predicates[i] = pred;
    }
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

Formula make_formula() {
    char *buf = malloc(sizeof(char) * MAXSIZE);

    get_input_formula(buf);
    printf("input str is: %s\n", buf);

    // check if input is illegal
    for (int i = 0; i < strlen(buf); ++i)
        // valid input: ' ', \n, \t, [, ], ',', (, ), 0-9, A-Z, a-z
        if (!(isspace(buf[i]) || isdigit(buf[i]) || isalpha(buf[i]) || buf[i] == '['
                || buf[i] == ']' || buf[i] == '_' || buf[i] == '(' || buf[i] == ')' || buf[i] == ','))
            return NULL;

    Formula formula = generate_formula(&buf);

    return formula;
}

Formula generate_formula(char ** buf) {
    Formula formula;
    formula = (Formula) malloc(sizeof(struct formula));

    if (isspace((*buf)[0]))
        *buf += 1;

    if ((*buf)[0] == '[') {
        // input is a combined formula
        *buf += 1;

        formula->predicate_name = malloc(sizeof(char) * MAXSIZE);
        formula->predicate_name = "";
        formula->name_num = 0;

        // recursively create sub formula for current combined formula
        formula->subf1 = (Formula) malloc(sizeof(struct formula));
        formula->subf1 = generate_formula(buf);
        printf("formula->first->predicate_name %s\n", formula->subf1->predicate_name);

        check_opts(buf, &formula);
        if (formula == NULL)
            return formula;

        formula->subf2 = (Formula) malloc(sizeof(struct formula));
        formula->subf2 = generate_formula(buf);
        printf("formula->second->predicate_name %s\n", formula->subf2->predicate_name);

        // every left-bracket must end with correspond right-bracket
        if ((*buf)[0] == ']') {
            *buf += 1;
        } else {
            return NULL;
        }
    } else if (strncmp(*buf, "not", 3) == 0) {
        // input is a not formula
        *buf += 3;
        formula = generate_formula(buf);
        formula->type = NOT;
        printf("not formula: %s\n", formula->predicate_name);
    } else {
        formula->type = NORMAL;
        formula->predicate_name = (char *) malloc(sizeof(char) * MAXSIZE);

        store_normal_formual(&formula, buf);
    }
    return formula;
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

//    printf("predicate is: %s\n", (*formula)->predicate_name);
//    for (int i = 0; i < (*formula)->name_size; ++i) {
//        printf("%s\n", (*formula)->name[i]);
//    }

}

void check_opts(char **buf, Formula *formula) {

    if (isspace(*buf[0]))
        *buf += 1;

    if (strncasecmp(*buf, "or", 2) == 0) {
        (*formula)->type = OR;
        *buf += 2;
    } else if (strncasecmp(*buf, "and", 3) == 0) {
        (*formula)->type = AND;
        *buf += 3;
    } else if (strncasecmp(*buf, "implies", 7) == 0) {
        (*formula)->type = IMPLIES;
        *buf += 7;
    } else if (strncasecmp(*buf, "iff", 3) == 0) {
        (*formula)->type = IFF;
        *buf += 3;
    } else {
        formula = NULL;
    }

    if (isspace(*buf[0]))
        *buf += 1;
}

bool is_valid_c_identifiers(char c) {
    if (isalpha(c) || isdigit(c) || c == '_')
        return true;
    else
        return false;
}

void process_single_interpretation(char *intepret, int intepret_index) {

    bool has_lbracket = false;
    int i = 0;

    for (i = 0; i < strlen(intepret); ++i) {
        if (intepret[i] == '(') {
            has_lbracket = true;
            ++i;
            break;
        }
    }

    interpretation[intepret_index].name_num = 0;
    interpretation[intepret_index].predicate_name = malloc(sizeof(char) * strlen(intepret));
    if (!has_lbracket) {
        strcpy(interpretation[intepret_index].predicate_name, intepret);
    } else {
        char *token;
        token = strtok(intepret, "(");
        strcpy(interpretation[intepret_index].predicate_name, token);
        intepret += i;

        ++interpretation[intepret_index].name_num;
        process_interpretation_names(intepret, intepret_index, 0);

    }

}

void process_interpretation_names(char *intepret, int intepret_index, int name_index) {

    bool has_comma = false;
    int i = 0;
    for (i = 0; i < strlen(intepret); ++i) {
        if (intepret[i] == ',') {
            has_comma = true;
            ++i;
            break;
        }
    }

    interpretation[intepret_index].name[name_index] = (char *) malloc(
            sizeof(char) * strlen(intepret));
    if (!has_comma) {
        if (intepret[strlen(intepret) - 1] == ')')
            intepret[strlen(intepret) - 1] = '\0';

        strcpy(interpretation[intepret_index].name[name_index], intepret);
    } else {
        char *token;
        token = strtok(intepret, ",");
        strcpy(interpretation[intepret_index].name[name_index], token);

        intepret += i;
        ++interpretation[intepret_index].name_num;
        process_interpretation_names(intepret, intepret_index,
                interpretation[intepret_index].name_num);
    }

}

Interpretation make_interpretation(FILE * file) {

    char *temp[MAXSIZE];
    int true_atom_num = get_File_Contents(file, temp);

    for (int i = 0; i < true_atom_num; ++i) {
        process_single_interpretation(temp[i], i);
    }
// for(i = 0; i < interpretation_size; ++i){
//   printf("%s ", interpretation[i].predicate_name);
// }
// printf("\n");

}

bool is_in_predicate_name(char *name) {
    for (int i = 0; i < predicate_sum; ++i) {
        if (strcmp(name, predicate_name[i]) == 0)
            return true;
    }
    return false;
}

bool is_in_name(char *inname[], int size, int position) {
    bool fail;
    if (args[position] != size) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        fail = true;
        for (int j = 0; j < name_sum; ++j) {
            if (strcmp(inname[i], name[j]) == 0) {
                fail = false;
                break;
            }
        }
        if (fail) {
            return false;
        }
    }
    return true;
}

bool is_syntactically_correct(Formula formula) {
    if (formula->type == NORMAL || formula->type == NOT) {
        return is_in_predicate_name(formula->predicate_name);
    } else if (formula->subf1 != NULL) {
        return is_syntactically_correct(formula->subf1);
    } else if (formula->subf2 != NULL) {
        return is_syntactically_correct(formula->subf2);
    } else {
        return true;
    }
}

bool is_same(Formula formula) {
    int fail;
    for (int i = 0; i < interpretation_size; ++i) {
        if (strcmp(interpretation[i].predicate_name, formula->predicate_name) == 0) {
            if (formula->name_num != interpretation[i].name_num)
                continue;

            fail = 0;
            for (int j = 0; j < formula->name_num; ++j) {
                // printf("%s %s\n", formula->name[j], interpretation[i].name[j]);
                if (strcmp(formula->name[j], interpretation[i].name[j]) != 0) {
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

bool get_value(Formula formula) {
    switch (formula->type) {
    case NORMAL:
        return is_same(formula);
        break;
    case NOT:
// printf("not %s\n", formula->predicate_name);
// printf("%s %s\n", formula->name[0], formula->name[1]);
// printf("%d\n", is_same(formula));
        return !is_same(formula);
        break;
    case AND:
        return get_value(formula->subf1) && get_value(formula->subf2);
        break;
    case OR:
        return get_value(formula->subf1) || get_value(formula->subf2);
        break;
    case IMPLIES:
        return !(get_value(formula->subf1) && !get_value(formula->subf2));
        break;
    case IFF:
        return (get_value(formula->subf1) && get_value(formula->subf2))
                || (!get_value(formula->subf1) && !get_value(formula->subf2));
        break;
    }
}

bool is_true(Formula formula, Interpretation interpretation) {
    return get_value(formula);
}

struct t_f_table {
    Formula needtobetrue[1000];
    Formula needtobefalse[1000];
    int needtobetrue_size;
    int needtobefalse_size;
};

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

