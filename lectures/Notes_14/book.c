/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user to input some informaion about books.         *
 *                                                                             *
 * Purpose: Illustrates structure initialisation.                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define MAX_TITLE_LENGTH   40
#define MAX_AUTHOR_LENGTH  30

struct book {
    char title[MAX_TITLE_LENGTH + 1];
    char author[MAX_AUTHOR_LENGTH + 1];
    float price;
};

int main(void) {
    struct book copy;
    printf("Enter the book title: ");
    fgets(copy.title, MAX_TITLE_LENGTH + 1, stdin);
    *strchr(copy.title, '\n') = '\0';
    printf("Enter the author: ");
    fgets(copy.author, MAX_AUTHOR_LENGTH + 1, stdin);
    *strchr(copy.author, '\n') = '\0';
    printf("Enter the price: ");
    scanf("%f", &copy.price);
    printf("%s: \"%s\" ($%.2f)\n", copy.author, copy.title, copy.price);
    return EXIT_SUCCESS;
}



