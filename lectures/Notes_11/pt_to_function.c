#include <stdio.h>
#include <stdlib.h>

void to_upper(char *);
void show(void (*)(char *), char *);

int main(void) {
    char str[] = "comp9021";
    show(&to_upper, &str);
    return EXIT_SUCCESS;
}

void to_upper(char *str) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z')
            *str += 'A' - 'a';
        ++str;
    }
}

void show(void (*fn)(char *), char *str) {
    fn(str);
    printf("%s\n", str);
}

    
