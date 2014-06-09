#include "logic.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *name[10000];
char *predicate_name[10000];
int name_size;
int predicate_size;
int interpretation_size;
int args[10000];

#define MAXSIZE 65535

typedef enum {
    NORMAL = 0, NOT, AND, OR, IMPLIES, IFF
} TYPE;

struct formula {
    TYPE type; // 0-6
    char *predicate_name;
    int name_size;
    char *name[100];
    Formula subf1;
    Formula subf2;
};

struct interpretation {
    char *predicate_name;
    int name_size;
    char *name[100];
} interpretation[1000];

bool findspace(char * buf);
bool findspace(char * buf);
Formula parse_formula(char ** buf);
int is_C_identifiers(char c);
char * match(char * buf, char * partner);
char * passspace(char * buf);

int get_File_Contents(FILE *file, char *file_buf[]) {
    char *buf = malloc(sizeof(char) * MAXSIZE);
    char *token;
    char *delim = " ";
    int i = 0;

    while (!feof(file)) {
        fgets(buf, MAXSIZE, file);

        buf[strlen(buf) - 1] = 0;

        token = strtok(buf, delim);
        while (token != NULL) {
            file_buf[i] = malloc(sizeof(char) * strlen(token));
            strcpy(file_buf[i], token);
            token = strtok(NULL, delim);
            ++i;
        }
    }
    free(buf);

//    for (int j = 0; j < i; ++j) {
//        printf("%s ", file_buf[j]);
//    }
//    printf("\n");

    return i;
}

void get_constants(FILE *file) {
    name_size = get_File_Contents(file, name);

}

void get_predicates(FILE * file) {
    predicate_size = get_File_Contents(file, predicate_name);

    for (int i = 0; i < predicate_size; ++i) {
        for (int j = 0; j < strlen(predicate_name[i]); ++j) {
            if (predicate_name[i][j] == '/') {
                args[i] = atoi(predicate_name[i] + j + 1);
            }
        }
    }
}

Formula make_formula() {
    char *buf = malloc(sizeof(char) * MAXSIZE);
//    fgets(buf, MAXSIZE, stdin);

    int c;
    int i = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            c = ' ';
        buf[i] = c;
        ++i;
    }
    buf[strlen(buf) - 1] = '\0';

//    printf("\n");
//    for(int i = 0; i < strlen(buf); ++i)
//        printf("%c", buf[i]);
//    printf("\n");

    if (findspace(buf)) {
        if (buf[0] != '[')
            return NULL;
    }

    Formula ret = parse_formula(&buf);

    return ret;
}

bool findspace(char * buf) {
    for (int i = 0; i < strlen(buf); ++i)
        if (buf[i] == ' ')
            return true;

    return false;
}

Formula parse_formula(char ** buf) {
    // printf("parse_formula\n");
    Formula ret;
    ret = (Formula) malloc(sizeof(struct formula));

    char *delim = " ";
    *buf = passspace(*buf);
    if ((*buf)[0] == '[') // is a combination
            {
        *buf = match(*buf, "[");

        *buf = passspace(*buf);
        // printf("%s\n", *buf);

        ret->subf1 = (Formula) malloc(sizeof(struct formula));
        ret->predicate_name = malloc(sizeof(char) * MAXSIZE);
        strcpy(ret->predicate_name, "");
        ret->name_size = 0;

        ret->subf1 = parse_formula(buf);
        // printf("ret->first->predicate_name %s\n", ret->first->predicate_name);

        *buf = passspace(*buf);

        check_relation_opts(buf, &ret);
        if (ret == NULL)
            return ret;

        *buf = passspace(*buf);

        ret->subf2 = (Formula) malloc(sizeof(struct formula));
        ret->subf2 = parse_formula(buf);

        *buf = passspace(*buf);

        if ((*buf)[0] == ']') {
            *buf = match(*buf, "]");
            *buf = passspace(*buf);
            // printf("last %s\n", *buf);
        } else {
            ret = NULL;
            return ret;
        }
    } else if (strncmp(*buf, "not", 3) == 0) { // not
        *buf = match(*buf, "not");
        *buf = passspace(*buf);
        ret = parse_formula(buf);
        ret->type = NOT;
        // printf("not %s\n", ret->predicate_name);
    } else { // normal
        ret->type = NORMAL;
        ret->predicate_name = (char *) malloc(sizeof(char) * MAXSIZE);
        for (int i = 0; i < strlen(*buf); ++i) {
            if (is_C_identifiers((*buf)[i])) {
                ret->predicate_name[i] = (*buf)[i];
                // printf("%c\n", (*buf)[i]);
            } else {
                ret->predicate_name[i] = 0;
                *buf = (*buf) + i;
                // printf("%s\n", *buf);
                break;
            }
        }
        // printf("%s\n", ret->predicate_name);

        ret->name_size = 0;
        int i = 0;
        if ((*buf)[0] == '(') // has name
                {
            *buf = match(*buf, "(");
            ret->name[ret->name_size] = (char *) malloc(sizeof(char) * MAXSIZE);
            while ((*buf)[0] != ')') {
                if ((*buf)[0] == ',') {
                    *buf = match(*buf, ",");
                    ret->name_size++;
                    ret->name[ret->name_size] = (char *) malloc(
                            sizeof(char) * MAXSIZE);
                    i = 0;
                } else {
                    ret->name[ret->name_size][i] = (*buf)[0];
                    //printf("%c\n", buf[0]);
                    ++i;
                    *buf = *buf + 1;
                }
            }
            ret->name_size++;
            *buf = match(*buf, ")");
        }
        *buf = passspace(*buf);

        // for (i = 0; i < ret->name_size; ++i)
        // {
        //   printf("%s\n", ret->name[i] );
        // }

        ret->subf1 = NULL;
        ret->subf2 = NULL;

        // printf("%s\n", ret->predicate_name);
    }
    return ret;
}

void check_relation_opts(char ** buf, Formula* ret) {

    if (strncmp(*buf, "or", 2) == 0) {
        // printf("or\n");
        (*ret)->type = OR;
        *buf = match(*buf, "or");
    } else if (strncmp(*buf, "and", 3) == 0) {
        // printf("and\n");
        (*ret)->type = AND;
        *buf = match(*buf, "and");
    } else if (strncmp(*buf, "implies", 7) == 0) {
        // printf("implies\n");
        (*ret)->type = IMPLIES;
        *buf = match(*buf, "implies");
    } else if (strncmp(*buf, "iff", 3) == 0) {
        // printf("iff\n");
        (*ret)->type = IFF;
        *buf = match(*buf, "iff");
    } else {
        ret = NULL;
    }

}

int is_C_identifiers(char c) {
    if (c >= 'a' && c <= 'z') {
        return 1;
    } else if (c >= 'A' && c <= 'Z') {
        return 1;
    } else if (c == '_') {
        return 1;
    } else if (c >= '0' && c <= '9') {
        return 1;
    } else {
        return 0;
    }
}

char * match(char * buf, char * partner) {
    return buf + strlen(partner);
}

char * passspace(char * buf) {
    while (buf[0] == ' ') {
        buf += 1;
    }
    return buf;
}

Interpretation make_interpretation(FILE * file) {
    char *buf;
    buf = malloc(sizeof(char) * MAXSIZE);

    char *token;
    char *delim = " ";
    char *tmp_predicate_name;
    int i = 0, j = 0, k = 0;

    fgets(buf, MAXSIZE, file);
    while (!feof(file)) {
        // rm '\n'
        buf[strlen(buf) - 1] = 0;

        /* get the first token */
        token = strtok(buf, delim);
        /* walk through other tokens */
        while (token != NULL) {
            // printf("%s\n", token);
            interpretation[i].predicate_name = malloc(
                    sizeof(char) * strlen(token));
            // store to the predicate_name
            for (j = 0; j < strlen(token) && token[j] != '('; ++j) {
                // printf("%c", token[j]);
                interpretation[i].predicate_name[j] = token[j];
            }

            interpretation[i].name_size = 0;
            // has name
            if (token[j] == '(') {
                ++j;
                interpretation[i].name[interpretation[i].name_size] =
                        (char *) malloc(sizeof(char) * MAXSIZE);
                while (token[j] != ')') {
                    if (token[j] == ',') {
                        ++j;
                        // printf("%s\n", interpretation[i].name[interpretation[i].name_size]);
                        interpretation[i].name_size++;
                        interpretation[i].name[interpretation[i].name_size] =
                                (char *) malloc(sizeof(char) * MAXSIZE);
                        k = 0;
                    } else {
                        interpretation[i].name[interpretation[i].name_size][k] =
                                token[j];
                        ++k;
                        ++j;
                    }
                }
                interpretation[i].name_size++;
                ++j;
            }

            // next token
            token = strtok(NULL, delim);

            ++i;
        }
        // update predicate_name' size
        predicate_size = i;

        fgets(buf, MAXSIZE, file);
    }
    interpretation_size = i;
    // for(i = 0; i < interpretation_size; ++i){
    //   printf("%s ", interpretation[i].predicate_name);
    // }
    // printf("\n");

}

int is_in_predicate_name(char *name) {
    int len;
    for (int i = 0; i < predicate_size; ++i) {
        // printf("%s\n", predicate_name[i]);
        for (len = 0; i < strlen(predicate_name[i]); ++len) {

            if (predicate_name[i][len] == '/') {
                break;
            }
        }

        if (strncmp(name, predicate_name[i], len - 1) == 0)
            return i;
    }
    return -1;
}

bool is_in_name(char *inname[], int size, int position) {
    bool fail;
    if (args[position] != size) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        fail = true;
        for (int j = 0; j < name_size; ++j) {
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
    int position;
    switch (formula->type) {
    case NORMAL:
    case NOT:
        position = is_in_predicate_name(formula->predicate_name);
        if (position == -1)
            return false;
        break;
    default:
        if (formula->subf1 != NULL && !is_syntactically_correct(formula->subf1))
            return false;
        if (formula->subf2 != NULL && !is_syntactically_correct(formula->subf2))
            return false;
    }
    return true;
}

bool is_same(Formula formula) {
    int fail;
    for (int i = 0; i < interpretation_size; ++i) {
        if (strcmp(interpretation[i].predicate_name, formula->predicate_name)
                == 0) {
            if (formula->name_size != interpretation[i].name_size)
                continue;

            fail = 0;
            for (int j = 0; j < formula->name_size; ++j) {
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
        if (strcmp(tf_tb->needtobetrue[i]->predicate_name,
                formula->predicate_name) == 0) {
            if (formula->name_size != tf_tb->needtobetrue[i]->name_size) {
                continue;
            }
            fail = 0;
            for (int j = 0; j < formula->name_size; ++j) {
                if (strcmp(formula->name[j], tf_tb->needtobetrue[i]->name[j])
                        != 0) {
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
        if (strcmp(tf_tb->needtobefalse[i]->predicate_name,
                formula->predicate_name) == 0) {
            if (formula->name_size != tf_tb->needtobefalse[i]->name_size) {
                continue;
            }
            fail = 0;
            for (int j = 0; j < formula->name_size; ++j) {
                if (strcmp(formula->name[j], tf_tb->needtobefalse[i]->name[j])
                        != 0) {
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
        return make_true(formula->subf1, 1, tf_tb)
                && make_true(formula->subf2, 1, tf_tb);

        break;
    case OR:
        if (formula->subf2->type == NOT)
            return make_true(formula->subf2, 1, tf_tb)
                    || make_true(formula->subf1, 1, tf_tb);
        else
            return make_true(formula->subf1, 1, tf_tb)
                    || make_true(formula->subf2, 1, tf_tb);
        break;
    case IMPLIES:
        if (make_true(formula->subf1, 1, tf_tb)
                && make_true(formula->subf2, 0, tf_tb))
            return false;
        else
            return true;

        break;
    case IFF:
        if (make_true(formula->subf1, 1, tf_tb)
                && make_true(formula->subf2, 1, tf_tb))
            return true;
        else {
            if (make_true(formula->subf1, 1, tf_tb))
                tf_tb->needtobetrue_size--;
            if (make_true(formula->subf2, 1, tf_tb))
                tf_tb->needtobetrue_size--;

            return make_true(formula->subf1, 0, tf_tb)
                    && make_true(formula->subf2, 0, tf_tb);
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
            if (tf_tb->needtobetrue[i]->name_size) {
                fprintf(fp, "(");
                for (int j = 0; j < tf_tb->needtobetrue[i]->name_size; ++j) {
                    fprintf(fp, "%s", tf_tb->needtobetrue[i]->name[j]);
                    if (j != tf_tb->needtobetrue[i]->name_size - 1) {
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

