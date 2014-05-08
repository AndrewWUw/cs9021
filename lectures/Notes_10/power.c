#include <stdio.h>
#include <stdlib.h>

int power(int, int);	// function prototype

int main(void) {
    for (int p = 0; p < 10; ++p) // call function twice
        printf("%d %d %d\n", p, power(2, p), power(-3, p));
    return EXIT_SUCCESS;
}

/* power(base, n) raises base to the power n, n >= 0 */
int power(int base, int n) {	// function definition
    int p = 1;
    for (int i = 1; i <= n; ++i)
        p *= base;
    return p;
}
