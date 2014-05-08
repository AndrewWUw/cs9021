
#include <stdio.h>
#include <stdlib.h>
#define MAX 40

int main(void) {
    FILE *fp;
    fp = fopen("words_file", "a+");
    puts("Enter words to add to the file, one per line.");
    puts("Press Enter to terminate.");
    char words[MAX];
    while (fgets(words, MAX, stdin) != NULL && words[0] != '\n')
        fprintf(fp, "%s", words);
    puts("File contents:");
    rewind(fp);
    while (fscanf(fp,"%s", words) == 1)
        puts(words);
    fclose(fp);
    return EXIT_SUCCESS;
}

