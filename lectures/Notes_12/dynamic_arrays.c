/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for data, with the user indicating            *
 *              at run time how much data to provide.                          *
 *                                                                             *
 * Purpose: Illustrates dynamic memory allocation with malloc,                 *
 *          or with dynamic arrays.                                            *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int max;
    puts("What's the max. number of type double entries? ");
    scanf("%d", &max);
    double *ptd = (double *)malloc(max * sizeof (double));
    double arr[max];
    if (ptd == NULL) {
        puts("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    puts("Enter the values (q to quit):");
    int i = 0;
    double entry;
    while (i < max && scanf("%lf", &entry) == 1) {
        ptd[i] = entry;
        arr[i++] = entry;
    }
    int number_of_entries = i;
    printf("Here are your %d entries:\n", number_of_entries);
    for (i = 0; i < number_of_entries; ++i) {
        printf("%7.2f ", ptd[i]);
        if (i % 7 == 6)
            putchar('\n');
    }
    if (i % 7)
        putchar('\n');
    puts("Again:");
    for (i = 0; i < number_of_entries; ++i) {
        printf("%7.2f ", arr[i]);
        if (i % 7 == 6)
            putchar('\n');
    }
    if (i % 7)
        putchar('\n');
    free(ptd);
    return EXIT_SUCCESS;
}

