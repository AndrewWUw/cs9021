#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int count = 0;
    if (argc != 2) { 
         fprintf(stderr, "Usage: %s filename\n", argv[0]);
         exit(1);
    }
    FILE *in;
    if ((in = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Cannot open the file \"%s\"\n", argv[1]);
        exit(2);
    }
    char name[40];
    strcpy(name, argv[1]);   // copy filename into array
    strcat(name, ".red");    // append .red to name
    FILE *out;
    if ((out = fopen(name, "w")) == NULL) {
        fprintf(stderr,"Can't create output file.\n");
        exit(3);
    }
    char ch;
    while ((ch = getc(in)) != EOF)
        /* Print every 3rd character */
        if (count++ % 3 == 0)
            putc(ch, out);
    putc('\n', out);
    if (fclose(in) || fclose(out))
        fprintf(stderr,"Error in closing files\n");
    return EXIT_SUCCESS;
}

