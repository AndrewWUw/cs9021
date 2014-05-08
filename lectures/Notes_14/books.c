/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user to input some information on books.           *
 *                                                                             *
 * Purpose: Illustrates the use of arrays of structures.                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define MAX_TITLE_LENGTH   40
#define MAX_AUTHOR_LENGTH  30
#define MAX_BOOKS          100

struct book {
    char title[MAX_TITLE_LENGTH + 1];
    char author[MAX_AUTHOR_LENGTH + 1];
    float price;
};

int main(void) {
    struct book copies[MAX_BOOKS];
    struct book copy;
    printf("Type [enter] when you are done.\n");
    printf("Enter the book title: ");
    int i = 0;
    while (i < MAX_BOOKS &&
           fgets(copies[i].title, MAX_TITLE_LENGTH + 1, stdin) != NULL
           && copies[i].title[0] != '\n') {
        *strchr(copies[i].title, '\n') = '\0';
        printf("Enter the author: ");
        fgets(copies[i].author, MAX_AUTHOR_LENGTH + 1, stdin);
        *strchr(copies[i].author, '\n') = '\0';
        printf("Enter the price: ");
        scanf("%f", &copies[i++].price);
        while (getchar() != '\n')
            continue;
        if (i < MAX_BOOKS)
            printf("Enter the next book title: ");
    }
    printf("List of your books:\n");
    for (int j = 0; j < i; ++j)
    printf("%s: \"%s\" ($%.2f)\n", copies[j].author,
          copies[j].title, copies[j].price);
    return EXIT_SUCCESS;
}

