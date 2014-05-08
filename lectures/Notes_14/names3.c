/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user to input some information abiut himself.      *
 *                                                                             *
 * Purpose: Illustrates passing pointers to structures                         *
 *          as arguments to functions to initialise structure members          *
 *          for which storage has not been set.                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct name {
    char *first_name;
    char *last_name;
    int letters;
};

void get_info(struct name *);
void make_info(struct name *);
void show_info(const struct name *);
void cleanup(struct name *);

int main(void) {
    struct name person;
    get_info(&person);
    make_info(&person);
    show_info(&person);
    cleanup(&person);
    return EXIT_SUCCESS;
}

void get_info (struct name *pst) {
    char temp[81];
    printf("Please enter your first name: ");
    scanf("%s", temp);
    pst->first_name = (char *)malloc(strlen(temp) + 1);
    strcpy(pst->first_name, temp);
    printf("Please enter your last name: ");
    scanf("%s", temp);
    pst->last_name = (char *)malloc(strlen(temp) + 1);
    strcpy(pst->last_name, temp);
}

void make_info (struct name *pst) {
    pst->letters = strlen(pst->first_name) + strlen(pst->last_name);
}

void show_info (const struct name *pst) {
    printf("%s %s, your name contains %d letters.\n",
        pst->first_name, pst->last_name, pst->letters);
}

void cleanup(struct name *pst) {
	free(pst->first_name);
	free(pst->last_name);
}
