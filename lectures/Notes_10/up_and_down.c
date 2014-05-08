#include <stdio.h>
#include <stdlib.h>

void up_and_down(int);
int main(void) {
    up_and_down(1);
    return EXIT_SUCCESS;
}

void up_and_down(int n) {
    printf("Level %d\n", n);    // print #1
    if (n < 4)
        up_and_down(n + 1);
    printf("LEVEL %d\n", n);    // print #2
}
