/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: The input is expected to consist of y_dim lines of x_dim       *
 *              members of {0, 1, 2, 3}, where x_dim and y_dim are at least    *
 *              equal to 2 and at most equal to MAX_X_DIM and MAX_Y_DIM,       *
 *              respectively, with possibly lines consisting of spaces only    *
 *              that will be ignored and with possibly spaces anywhere on the  *
 *              lines with digits.                                             *
 *              The xth digit n of the yth line, with 0 <= x < x_dim and       *
 *              0 <= y < y_dim, is to be associated with a point situated      *
 *              x * 0.5 cm to the right and y * 0.5 cm below an origin, is to  *
 *              be connected to the point 0.5 cm to its right                  *
 *              if n = 1 or n = 3, and is to be connected to the point         *
 *              0.5 cm below itself if n = 2 or n = 3.                         *
 *              The last digit on every line cannot be equal to 1 or 3, and    *
 *              the digits on the last line cannot be equal to 2 or 3, which   *
 *              ensures that the input encodes a maze, that is, a grid of      *
 *              width (x_dim - 1) * 0.5 cm and of height (y_dim - 1) * 0.5 cm, *
 *              with possibly gaps on the sides and inside. A point not        *
 *              connected to any of its neighbours is thought of as a pillar;  *
 *              a point connected to at least one of its neighbours is thought *
 *              of as part of a wall.                                          *
 *              We talk about "inner point" to refer to a point that lies      *
 *              (x + 0.5) * 0.5 cm to the right of and (y + 0.5) * 0.5 cm      *
 *              below the origin with 0 <= x < x_dim - 1 and                   *
 *              0 <= y < y_dim - 1.                                            *
 *                                                                             *
 *              Practically, the input will be stored in a file and its        *
 *              contents redirected to standard input. The program will be run *
 *              with either co command-line argument or with "print" as unique *
 *              command line argument; otherwise it will exit. The program     *
 *              will also exit immediately if the input is not as expected.    *
 *                                                                             *
 *              When provided with no command-line argument, the program does  *
 *              the following.                                                 *
 *              - It outputs the number of gates, that is, the number of       *
 *              consecutive points on one of the four sides of the maze   *
 *              that are not connected.                                        *
 *              - It outputs the number of sets of connected walls.            *
 *              - It outputs the number of inner points that cannot be         *
 *                accessed from any gate, starting from the point in the       *
 *                middle of a gate and going from inner points to neighbouring *
 *                inner points.                                                *
 *              - It outputs the number of maximal areas that can be accessed  *
 *                from at least one gate.                                      *
 *              - It outputs the number of accessible cul-de-sacs.             *
 *              - It outputs the number of paths consisting of inner points    *
 *                that go from a gate to another gate and such that the        *
 *                resulting path is choice-free, that is, such that leaving    *
 *                the path, at any inner point where that is possible,         *
 *                immediately leads into a cul-de-sac.                         *
 *                                                                             *
 *              When provided with "print" as unique command-line argument,    *
 *              the program outputs some .tex code to depict the maze          *
 *              as a tiz picture.                                              *
 *              - Walls are drawn in blue. There is a command for every        *
 *                longest segment that is part of a wall. Horizontal segments  *
 *                are drawn starting with the topmost leftmost segment and     *
 *                finishing with the bottommost rightmost segment. Then        *
 *                vertical segments are drawn starting with the topmost        *
 *                leftmost segment and finishing with the bottommost rightmost *
 *                segment.                                                     *
 *              - Pillars are drawn as green circles.                          *
 *              - Inner points in accessible cul-de-sacs are drawn as red      *
 *                crosses.                                                     *
 *              - The choice-free paths are drawn as dashed yellow lines.      *
 *                There is a command for every longest segment on such a       *
 *                path. Horizontal segments are drawn starting with the        *
 *                topmost leftmost segment and finishing with the bottommmost  *
 *                rightmost segment, with those segments that end at a gate    *
 *                sticking out by 0.25 cm. Then vertical segments are drawn    *
 *                starting with the topmost leftmost segment and finishing     *
 *                with the bottommmost rightmost segment, with those segments  *
 *                that end at a gate sticking out by 0.25 cm.                  *
 *                                                                             *
 * Written by *** for COMP9021                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_X_DIM 31
#define MAX_Y_DIM 41
/* Possibly include extra macros */

/* Include your global variables */
char maze[MAX_Y_DIM][MAX_X_DIM];
int actual_x_dim = 0;
int actual_y_dim = 0;
bool dummyMaze[MAX_Y_DIM][MAX_X_DIM];
bool mazeInXDim[MAX_Y_DIM][MAX_X_DIM];
bool mazeInYDim[MAX_Y_DIM][MAX_X_DIM];
bool tempMaze[MAX_Y_DIM][MAX_X_DIM];
bool mazeInXDimDummy[MAX_Y_DIM][MAX_X_DIM];
bool mazeInYDimDummy[MAX_Y_DIM][MAX_X_DIM];

// counters for different output
int gateCounter = 0;
int wallCounter = 0;
int inAccAreaCounter = 0;
int accAreaCounter = 0;
int culdesacsCounter = 0;
int pathCounter = 0;

/* read input functions */
bool get_input(void);
bool checkMaze(int x_dim, int y_dim);

/* calculate functions */
void countGates();
void countWalls();
void countInAccAreas();
void countAccAreas();
void countCuldesacs();
void countPaths();

/* Output functions */
void outputResult();
void drawMaze();
void drawWalls();
void drawPillars();
void drawInnerPoints();

/* helper functions */
void printMaze();
void wallCounterHelper(int i, int j);
void countCuldHelper(int i, int j);
void convertMaze();
int findLongestlength(int i, int j, int direction);
void drawInnerPointsHelper();

int main(int argc, char **argv) {

    if (argc > 2 || (argc == 2 && strcmp(argv[1], "print"))) {
        printf(
                "I expect no command line argument or \"print\" as unique command line argument.\n");
        return EXIT_FAILURE;
    }
    if (!get_input()) {
        printf("Incorrect input.\n");
        return EXIT_FAILURE;
    }
    convertMaze();
    if (argc == 2) {
        drawMaze();
        return EXIT_SUCCESS;
    }

    countGates();
    countWalls();
    countInAccAreas();
    countAccAreas();
    countCuldesacs();
    countPaths();
    outputResult();

    return EXIT_SUCCESS;
}

bool get_input() {
    bool isCorrectInput = true;
    char c;
    int x_dim = 0;
    int y_dim = 0;

    while ((c = getchar()) != EOF) {
        if (isspace(c) || (c >= '0' && c <= '3') || c == '\n') {
            switch (c) {
            case ' ':
                break;
            case '0':
            case '1':
            case '2':
            case '3':
                if (x_dim > 31) {
                    isCorrectInput = false;
                } else {
                    maze[y_dim][x_dim++] = c;
                }
                break;
            case '\n':
                if (x_dim != 0 && x_dim >= 2) {
                    x_dim = 0;
                    y_dim++;
                } else if (y_dim > 41 || x_dim == 1) {
                    isCorrectInput = false;
                }
                break;
            }
        } else {
            isCorrectInput = false;
            break;
        }
    }

    if (isCorrectInput && y_dim >= 2) {
        x_dim = 0;
        for (int i = 0; i < MAX_X_DIM; i++) {
            if (isdigit(maze[0][i]))
                x_dim++;
        }
        isCorrectInput = checkMaze(x_dim, y_dim);
    }

    if (isCorrectInput) {
        actual_x_dim = x_dim;
        actual_y_dim = y_dim;
    }

    return isCorrectInput;
}

/*
 * check if the maze satisfied boundary restrictions
 */
bool checkMaze(int x_dim, int y_dim) {
    bool isCorrectMaze = true;

    for (int i = 0; i < y_dim; i++) {
        if (maze[i][x_dim] == '1' || maze[i][x_dim] == '3') {
            isCorrectMaze = false;
        }
    }

    for (int j = 0; j < x_dim; j++) {
        if (maze[y_dim][j] == '2' || maze[y_dim][j] == '3') {
            isCorrectMaze = false;
        }
    }

    return isCorrectMaze;
}

/* ====================================================================== */

void countGates() {

    for (int i = 1; i < actual_x_dim - 1; ++i) {
        if (maze[0][i] == '0' || maze[0][i] == '2')
            gateCounter++;
        if (maze[actual_y_dim - 1][i] == '0')
            gateCounter++;
    }

    for (int i = 1; i < actual_y_dim - 1; i++) {
        if (maze[i][0] == '0' || maze[i][0] == '1')
            gateCounter++;
        if (maze[i][actual_x_dim - 1] == '0')
            gateCounter++;
    }

    if (maze[0][actual_x_dim - 1] == '0' && maze[1][actual_x_dim - 1] != '2')
        gateCounter++;
    if (maze[actual_y_dim - 1][actual_x_dim - 1] == '0'
            && maze[actual_y_dim - 2][actual_x_dim - 1] != '2')
        gateCounter++;
    if (maze[actual_y_dim - 1][0] == '0')
        gateCounter++;
    if (maze[0][0] == '0')
        gateCounter++;
}

void countWalls() {
    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; ++j) {
            dummyMaze[i][j] = false;
        }
    }

    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; ++j) {
            if (dummyMaze[i][j] == false) {
                wallCounterHelper(i, j);
                if (maze[i][j] != '0')
                    wallCounter++;
            }
        }
    }
}

void wallCounterHelper(int i, int j) {
    if (dummyMaze[i][j] == false) {
        dummyMaze[i][j] = true;
        switch (maze[i][j]) {
        case '1':
            if (j + 1 < actual_x_dim)
                wallCounterHelper(i, j + 1);
            break;
        case '2':
            wallCounterHelper(i + 1, j);
            break;
        case '3':
            wallCounterHelper(i, j + 1);
            wallCounterHelper(i + 1, j);
            break;
        default:
            break;
        }

        if ((maze[i - 1][j] == '2' || maze[i - 1][j] == '3') && (i - 1 >= 0))
            wallCounterHelper(i - 1, j);
        if ((maze[i][j - 1] == '1' || maze[i][j - 1] == '3') && (j - 1 >= 0))
            wallCounterHelper(i, j - 1);
    }
}

void countInAccAreas() {

    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            if (mazeInXDim[i][j] == true)
                inAccAreasCounterHelper(i, j);
        }
    }

}

void inAccAreasCounterHelper(int i, int j) {
    if (mazeInXDim[i][j] == true) {
        if (mazeInYDim[i][j] == true) {
            inAccAreasCounterHelper(i, j + 1);
            inAccAreasCounterHelper(i + 1, j);
        } else {
            inAccAreasCounterHelper(i, j + 1);
            inAccAreasCounterHelper(i + 1, j);
            inAccAreasCounterHelper(i, j - 1);
        }
    }
}

void countAccAreas() {

}
void countCuldesacs() {
    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            tempMaze[i][j] = false;
            mazeInXDimDummy[i][j] = mazeInXDim[i][j];
            mazeInYDimDummy[i][j] = mazeInYDim[i][j];
        }
    }

    int counter = 0;
    int currentCounter = 0;
    do {
        counter = currentCounter;
        currentCounter = 0;
        drawInnerPointsHelper();

        for (int i = 0; i < actual_y_dim; i++) {
            for (int j = 0; j < actual_x_dim; j++) {
                if (tempMaze[i][j] == true)
                    currentCounter++;
            }
        }
    } while (counter != currentCounter);

    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            if (tempMaze[i][j] == true) {
                countCuldHelper(i, j);
                culdesacsCounter++;
            }
        }
    }
}

void countCuldHelper(int i, int j) {
    if (tempMaze[i][j] == true)
        tempMaze[i][j] = false;

    if (tempMaze[i - 1][j] == true)
        countCuldHelper(i - 1, j);
    if (tempMaze[i + 1][j] == true)
        countCuldHelper(i + 1, j);
    if (tempMaze[i][j - 1] == true)
        countCuldHelper(i, j - 1);
    if (tempMaze[i][j + 1] == true)
        countCuldHelper(i, j + 1);
}

void countPaths() {

}

/* ========================================================================== */

void drawMaze() {

    printf("\\documentclass[10pt]{article}\n");
    printf("\\usepackage{tikz}\n");
    printf("\\usetikzlibrary{shapes.misc}\n");
    printf("\\usepackage[margin=0cm]{geometry}\n");
    printf("\\pagestyle{empty}\n");
    printf("\\tikzstyle{every node}=[cross out, draw, red]\n");
    printf("\n");
    printf("\\begin{document}\n");
    printf("\n");
    printf("\\vspace*{\\fill}\n");
    printf("\\begin{center}\n");
    printf("\\begin{tikzpicture}[x=0.5cm, y=-0.5cm, ultra thick, blue]\n");
    printf("% Walls\n");
    drawWalls();

    printf("% Pillars\n");
    drawPillars();

    printf("% Inner points in accessible cul-de-sacs\n");
    drawInnerPoints();

    printf("% Entry-exit paths without intersections\n");

    printf("\\end{tikzpicture}\n");
    printf("\\end{center}\n");
    printf("\\vspace*{\\fill}\n");
    printf("\n");
    printf("\\end{document}\n");
}

void drawWalls() {
    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            if (mazeInXDim[i][j] == true) {
                printf("    \\draw (%d,%d) -- ", j, i);
                int l = findLongestlength(i, j, 0);
                printf("(%d,%d);\n", j + l, i);
                j = j + l;
            }
        }
    }
    for (int j = 0; j < actual_x_dim; j++) {
        for (int i = 0; i < actual_y_dim; i++) {
            if (mazeInYDim[i][j] == true) {
                printf("    \\draw (%d,%d) -- ", j, i);
                int l = findLongestlength(i, j, 1);
                printf("(%d,%d);\n", j, i + l);
                i = i + l;
            }
        }
    }
}

void drawPillars() {
    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            if (mazeInXDim[i][j - 1] == false && mazeInXDim[i][j] == false
                    && mazeInYDim[i - 1][j] == false
                    && mazeInYDim[i][j] == false) {
                printf("    \\fill[green] (%d,%d) circle(0.2);\n", j, i);
            }
        }

    }
}

void drawInnerPoints() {

    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            tempMaze[i][j] = false;
            mazeInXDimDummy[i][j] = mazeInXDim[i][j];
            mazeInYDimDummy[i][j] = mazeInYDim[i][j];
        }
    }

    int counter = 0;
    int currentCounter = 0;
    do {
        counter = currentCounter;
        currentCounter = 0;
        drawInnerPointsHelper();

        for (int i = 0; i < actual_y_dim; i++) {
            for (int j = 0; j < actual_x_dim; j++) {
                if (tempMaze[i][j] == true)
                    currentCounter++;
            }
        }
    } while (counter != currentCounter);

    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            if (tempMaze[i][j] == true)
                printf("    \\node at (%d.5,%d.5) {};\n", j, i);
        }
    }
}

void drawInnerPointsHelper() {
    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            int counter = 0;
            if (mazeInXDimDummy[i][j] == true)
                counter++;
            if (mazeInXDimDummy[i + 1][j] == true)
                counter++;
            if (mazeInYDimDummy[i][j] == true)
                counter++;
            if (mazeInYDimDummy[i][j + 1] == true)
                counter++;

            if (counter == 3) {
                tempMaze[i][j] = true;
                mazeInXDimDummy[i][j] = true;
                mazeInXDimDummy[i + 1][j] = true;
                mazeInYDimDummy[i][j] = true;
                mazeInYDimDummy[i][j + 1] = true;
            }
        }
    }
}

int findLongestlength(int i, int j, int direction) {
    int length = 1;

    switch (direction) {
    case 0:
        if (j + 1 < actual_x_dim && mazeInXDim[i][j + 1] == true)
            length += findLongestlength(i, j + 1, 0);
        break;
    case 1:
        if (i + 1 < actual_y_dim && mazeInYDim[i + 1][j] == true)
            length += findLongestlength(i + 1, j, 1);
        break;
    }
    return length;
}

/*
 * If no argument is given, output result directly.
 */
void outputResult() {
    switch (gateCounter) {
    case 0:
        printf("The maze has no gate.\n");
        break;
    case 1:
        printf("The maze has a single gate.\n");
        break;
    default:
        printf("The maze has %d gates.\n", gateCounter);
        break;
    }

    switch (wallCounter) {
    case 0:
        printf("The maze has no wall.\n");
        break;
    case 1:
        printf("The maze has walls that are all connected.\n");
        break;
    default:
        printf("The maze has %d sets of walls that are all connected.\n",
                wallCounter);
        break;
    }

    switch (inAccAreaCounter) {
    case 0:
        printf("The maze has no inaccessible inner point.\n");
        break;
    case 1:
        printf("The maze has a unique inaccessible inner point.\n");
        break;
    default:
        printf("The maze has %d inaccessible inner points.\n",
                inAccAreaCounter);
        break;
    }

    switch (accAreaCounter) {
    case 0:
        printf("The maze has no accessible area.\n");
        break;
    case 1:
        printf("The maze has a unique accessible area.\n");
        break;
    default:
        printf("The maze has %d accessible areas.\n", accAreaCounter);
        break;
    }

    switch (culdesacsCounter) {
    case 0:
        printf("The maze has no accessible cul-de-sac.\n");
        break;
    case 1:
        printf("The maze has accessible cul-de-sacs that are all connected.\n");
        break;
    default:
        printf(
                "The maze has %d sets of accessible cul-de-sacs that are all connected.\n",
                culdesacsCounter);
        break;
    }

    switch (pathCounter) {
    case 0:
        printf(
                "The maze has no entry-exit path with no intersection not to cul-de-sacs.\n");
        break;
    case 1:
        printf(
                "The maze has a unique entry-exit path with no intersection not to cul-de-sacs.\n");
        break;
    default:
        printf(
                "The maze has %d entry-exit paths with no intersections not to cul-de-sacs.\n",
                pathCounter);
        break;
    }
}

/*===================Helper Functions============================= */

void convertMaze() {
    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; j++) {
            switch (maze[i][j]) {
            case '1':
                mazeInXDim[i][j] = true;
                break;
            case '2':
                mazeInYDim[i][j] = true;
                break;
            case '3':
                mazeInXDim[i][j] = true;
                mazeInYDim[i][j] = true;
                break;
            }
        }
    }
}

void printMaze() {
    printf("actual_x_dim = %d\n", actual_x_dim);
    printf("actual_y_dim = %d\n", actual_y_dim);

    for (int i = 0; i < actual_y_dim; i++) {
        for (int j = 0; j < actual_x_dim; ++j) {
            printf("%d ", maze[i][j] - '0');
        }
        printf("\n");
    }
}

