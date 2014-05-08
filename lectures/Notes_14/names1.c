/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user to input some information abiut himself.      *
 *                                                                             *
 * Purpose: Illustrates passing pointers to structures                         *
 *          as arguments to functions to initialise structure members          *
 *          for which storage has been set.                                    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct name {
    char first_name[20];
    char last_name[20];
    int letters;
};

void get_info(struct name *);
void make_info(struct name *);
void show_info(const struct name *);

int main(void) {
    struct name person;
    get_info(&person);
    make_info(&person);
    show_info(&person);
    return EXIT_SUCCESS;
}

void get_info (struct name *pt_to_person) {
    printf("Please enter your first name: ");
    scanf("%s", pt_to_person->first_name);
    printf("Please enter your last name: ");
    scanf("%s", pt_to_person->last_name);
}

void make_info (struct name *pt_to_person) {
    pt_to_person->letters =
        strlen(pt_to_person->first_name) +
        strlen(pt_to_person->last_name);
}

void show_info (const struct name *pt_to_person) {
    printf("%s %s, your name contains %d letters.\n",
           pt_to_person->first_name,
           pt_to_person->last_name,
           pt_to_person->letters);
}

