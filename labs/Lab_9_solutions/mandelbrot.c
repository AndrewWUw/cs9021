/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Creates a file named mandelbrot.pnm to represent part of       *
 *              the Mandelbrot set, defined as the set of all points c         *
 *              in the complex plane such that the sequence of complex         *
 *              numbers defined as z_{n+1}=z_n^2+c does not tend to            *
 *              infinity. The program used an approximation given by the set   *
 *              of all points c such that for all n <= 50, z_n remains         *
 *              in the disk D centered at 0 and of radius 4. Moreover,         *
 *              only the points c = x + iy with x in {-2, 0.5} and             *
 *              y in {-1.25, 1.25} are considered, and the image is assumed    *
 *              to consist of 256 x 256 pixels.                                   *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 256
#define MAX_ITERATIONS 50

typedef struct {
    unsigned char red, green, blue;
} Colour;

typedef struct {
    int width;
    int height;
    Colour pixels[DIM][DIM];
} Image;

void mandel(const double, const double, const double, const double, Image *const);
int iterate(double, double, int);
complex add(const complex, const complex);
complex multiply(const complex, const complex);
complex square(const complex);
void save_image(const char *, const Image *const);

Colour black = {0, 0, 0}, white = {255, 255, 255};

int main(void) {
    Image image;
    image.width = DIM;
    image.height = DIM;
    mandel(-1.25, -2, 1.25, 0.5, &image);
    save_image("mandelbrot.pnm", &image);
    return EXIT_SUCCESS;
}

void mandel(const double i1, const double j1, const double i2, const double j2, Image *const image) {
    for (int i = 0; i < image->height; ++i)
        for (int j = 0; j < image->width; ++j) {
            const int n = iterate(j1 + (j2 - j1) / image->width * j,
                            i1 + (i2 - i1) / image->width * i, MAX_ITERATIONS);
            image->pixels[i][j] = n < MAX_ITERATIONS ? white : black;
        }
}

int iterate(const double x, const double y, const int max_nb_of_iterations) {
    int iteration;
    complex z = 0;
    const complex c = x + y * I;
    for (iteration = 0; iteration < max_nb_of_iterations && cabs(z) < 4; ++iteration)
        z = add(square(z), c);
    return iteration;
}

complex add(const complex x, const complex y) {
    return creal(x) + creal(y) +
        (cimag(x) + cimag(y)) * I;
}

complex multiply(const complex x, const complex y) {
    return creal(x) * creal(y) - cimag(x) * cimag(y) +
        (creal(x) * cimag(y) + cimag(x) * creal(y)) * I;
}

complex square(const complex x) {
    return multiply(x, x);
}

void save_image(const char *file_name, const Image *const image) {
    FILE* file = fopen(file_name,"w");
    if (!file) {
        printf("Cannot open %s\n",file_name);
        exit(1);
    }
    fprintf(file, "P6\n%i %i\n255\n", image->width, image->height);
    for (int i = 0; i < image->height; ++i)
        for (int j = 0; j < image->width; ++j) {
            putc(image->pixels[i][j].red, file);
            putc(image->pixels[i][j].green, file);
            putc(image->pixels[i][j].blue, file);
        }
    fclose(file);
}
