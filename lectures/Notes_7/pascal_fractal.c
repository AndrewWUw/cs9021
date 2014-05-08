/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Generates Latex code that can be processed with pdflatex       *
 *              to create a .pdf file that depicts the Sierpinski triangle     *
 *              obtained from the Pascal triangle by drawing a black rectangle *
 *              when the corresponding number is even.                         *
 *              Uses a particular case of Luca's theorem which states that     *
 *              the number of ways of choosing k objects out of n is odd iff   *
 *              all digits in the binary representation of k are digits in the *
 *              binary representation of n.                                    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define DIM 128

int main(void) {
    printf("\\documentclass[10pt]{article}\n"
           "\\usepackage{tikz}\n"
           "\\pagestyle{empty}\n"
           "\n"
           "\\begin{document}\n"
           "\n"
           "\\vspace*{\\fill}\n"
           "\\begin{center}\n"
           "\\begin{tikzpicture}[scale=0.047]\n");
    for (int n = 0; n < DIM; ++n)
        for (int k = 0; k <= n; ++k)
            if ((k | n) == n)
                printf("\\fill(%d,%d) rectangle(%d,%d);\n", 2 * k - n, -(2 * n),                                                  2 * k - n + 2, -(2 * n) + 2);
    printf("\\end{tikzpicture}\n"
           "\\end{center}\n"
           "\\vspace*{\\fill}\n"
           "\n"
           "\\end{document}\n");
    return EXIT_SUCCESS;
}

