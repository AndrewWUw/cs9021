/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Defines and performs some operations on arrays of structures.  *
 *                                                                             *
 * Purpose: Illustrates that structure names do not refer to                   *
 *          structure addresses.                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define LEN 20

struct names {
    char first_name[LEN];
    char last_name[LEN];
};

struct mate {
    struct names id;
    char favourite_food[LEN];
    char job[LEN];
    float income;
};

int main(void) {
    struct mate people[2] = {
        {{ "John", "Smith"},
         "Fish and chips",
         "accountant",
         255000.00
        },
        {{"Paul", "Simpson"},
         "Meat pie",
         "editor",
         340000.00
        }
    };
    printf("people: %p\n", people);
    printf("people[0]: %p\n", people[0]);
    printf("&people[0]: %p\n", &people[0]);
    printf("&people[1]: %p\n", &people[1]);
    struct mate * people_pt = &people[0];
    printf("people_pt: %p\npeople_pt + 1: %p\n", people_pt, people_pt + 1);
    printf("people_pt->income is $%.2f\n",
         people_pt->income);
    ++people_pt;
    printf("people_pt->favourite_food is: %s \npeople_pt->id.last_name is: %s\n",
         people_pt->favourite_food, people_pt->id.last_name);
    return EXIT_SUCCESS;
}

