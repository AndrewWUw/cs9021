/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: An example of program split over many files.                   *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       count2.c                                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

void report_count();
void accumulate(int);

int count = 0;       // file scope, external linkage
int main(void) {
    int value;       // automatic variable
    register int i;  // register variable, the compile can ignore the request
    printf("Count\n");
    printf("Enter a positive integer (0 to quit): ");
    while (scanf("%d", &value) == 1 && value > 0) {
        ++count;     // use file scope variable
        for (i = value; i >= 0; --i)
            accumulate(i);
        printf("Enter a positive integer (0 to quit): ");
    }
    report_count();
    return EXIT_SUCCESS;
}

void report_count() {
    printf("Loop executed %d times\n", count);
}
