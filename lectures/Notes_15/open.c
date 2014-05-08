#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int c;
    
    FILE *fp;
    fp = fopen(argv[1], "r");   // open for reading; text view
    // fp = fopen(argv[1], "rb");  // open for reading; binary view
    while ((c = getc(fp)) != EOF) {
        if (c == '\r')
            printf("\\r");
        else if (c == '\n') {
            printf("\\n");
            printf("\n");
        }
        else
            putchar(c);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
            
