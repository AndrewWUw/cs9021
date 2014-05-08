#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    FILE *fp;                    
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Can't open %s\n", argv[1]);
        exit(1);
    }
    int c;
    long count = 0;
    while ((c = getc(fp)) != EOF)
        ++count;
    fclose(fp);
    printf("File %s contains %ld characters\n", argv[1], count);
    return EXIT_SUCCESS;
}
