#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

int main(void) {
    FILE *fp;
    printf("Enter the name of file to be processed: ");
    char file[MAX_LEN];    
    fgets(file, MAX_LEN, stdin);
    file[strlen(file) - 1] = '\0';
    if ((fp = fopen(file,"r")) == NULL) {
        printf("cannot open %s\n", file);
        exit(1);
    }
    fseek(fp, 0L, SEEK_END);  // go to end of file
    long i = ftell(fp);
    for (long count = 1L; count <= i; ++count) {
        fseek(fp, -count, SEEK_END);  // go backward
        putchar(getc(fp));
   }
    putchar('\n');
    fclose(fp);
    return EXIT_SUCCESS;
}
