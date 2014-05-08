
#include <stdio.h>

long long iter_fibonacci(int);
long long rec_fibonacci(int);

int main(void) {
    int num;
    printf("Enter a positive integer: ");
    scanf("%d", &num);
    printf("Via iteration: %lld\n", iter_fibonacci(num));
    printf("Via recursion: %lld\n", rec_fibonacci(num));
    return 0;
}

long long iter_fibonacci(const int n) {
    int previous = 0, current = 1;
    if (n < 2)
        return n;
    for (int i = 2; i <= n; ++i) {
        int temp = current;
        current += previous;
        previous = temp;
    }
    return current;
}

long long rec_fibonacci(const int n) {
    if (n >= 2)
        return rec_fibonacci(n - 2) + rec_fibonacci(n - 1);
    return n;
}
