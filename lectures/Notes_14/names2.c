/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user to input some information abiut himself.      *
 *                                                                             *
 * Purpose: Illustrates passing structures as arguments to functions           *
 *          to initialise structure members for which storage has been set.    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct name {
    char first_name[20];
    char last_name[20];
    int letters;
};

struct name get_info(void);
struct name make_info(struct name);
void show_info(const struct name);

int main(void) {
    struct name person;
    person = get_info();
    person = make_info(person);
    show_info(person);
    return EXIT_SUCCESS;
}

struct name get_info(void) {
    struct name person;
    printf("Please enter your first name: ");
    scanf("%s", person.first_name);
    printf("Please enter your last name: ");
    scanf("%s", person.last_name);
    return person;
}

struct name make_info (struct name person) {
    person.letters = strlen(person.first_name) + strlen(person.last_name);
    return person;
}

void show_info (struct name person) {
    printf("%s %s, your name contains %d letters.\n",
        person.first_name, person.last_name, person.letters);
}

