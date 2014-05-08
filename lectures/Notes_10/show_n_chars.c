#include <stdio.h>
#include <string.h>    // for the function strlen()
#define NAME "CSE School office"
#define ADDRESS "UNSW Sydney NSW 2052"
#define NB_OF_STARS 45
#define SPACE ' '

int main(void) {
    show_n_char('*', NB_OF_STARS);  // a constant as argument
    printf("\n");
    int spaces = (NB_OF_STARS - strlen(NAME)) / 2;
    show_n_char(SPACE, spaces);     // a variable as argument
    printf("%s\n", NAME);
    show_n_char(SPACE, (NB_OF_STARS - strlen(ADDRESS)) / 2);
                                    // an expression as argument
    printf("%s\n", ADDRESS);
    show_n_char('*', NB_OF_STARS);
    printf("\n");
    return 0;
}

void show_n_char(char ch, int num);

void show_n_char(char ch, int num) {
    for (int count = 0; count < num; ++count)
        printf("%c", ch);
}
