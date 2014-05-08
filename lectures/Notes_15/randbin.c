#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

int main() {
    double numbers[MAX_SIZE];
    const char *file = "numbers.dat";
    // create a set of double values
    for(int i = 0; i < MAX_SIZE; ++i)
        numbers[i] = 100.0 * i + 1.0 / (i + 1);
    FILE *iofile;
    if ((iofile = fopen(file, "wb")) == NULL) {
        fprintf(stderr, "Cannot write from %s.\n", file);
        exit(1);
    }
    // write array in binary format to file
    fwrite(numbers, sizeof(double), MAX_SIZE, iofile);
    fclose(iofile);
    if ((iofile = fopen(file, "rb")) == NULL) {
        fprintf(stderr,
            "Cannot read from %s.\n", file);
        exit(1);
    }
    printf("Enter an index in the range 0-%d: ", MAX_SIZE - 1);
    long i;
    scanf("%ld", &i);
    while (i >= 0 && i < MAX_SIZE) {
        long pos = i * sizeof(double); // calculate offset
        fseek(iofile, pos, SEEK_SET);    // go there
        double value;
        fread(&value, sizeof(double), 1, iofile);
        printf("The value there is %f.\n", value);
        printf("Next index (out of range to quit): ");
        scanf("%d", &i);
    }
    fclose(iofile);
    puts("Bye!");
    return EXIT_SUCCESS;
}

