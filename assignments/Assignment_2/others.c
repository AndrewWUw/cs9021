/*
 * others.c
 *
 *  Created on: May 8, 2014
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//int standardization(void);
//void findareas(int, int);
//void findcul(int, int);
//void gatesno(void);
//void print_maze(void);
//void print_maze_pdf(int *);
//void print_pdf_walls_x(int *, int, int);
//void print_pdf_walls_y(int *, int, int);
//void findwalls(int *, int, int);

#define MAX_X_DIM 31
#define MAX_Y_DIM 41

int areas_status[MAX_Y_DIM][MAX_X_DIM][9];
int recorder[MAX_Y_DIM][MAX_X_DIM];
int print_recorder[MAX_Y_DIM - 1][MAX_X_DIM - 1];
int path_recorder[MAX_Y_DIM - 1][MAX_X_DIM - 1];
int x_count, y_count, num_count, path, cul_de_sacs, gates, access_areas,
        inaccess_areas, walls, path_no;
int printer1, printer2;
bool circle;
char *p_martix;

/*gatesno() just judge how many gates exists in a maze. it acquire the maze from
 global variables *p_martix.*/
/*gatesno() checks each point and its neigbours to judge if they form a gate*/
void gatesno() {
    gates = 0;
    char martix[y_count][x_count];
    char *p = martix;
    for (int i = 0; i < (y_count * x_count); i++)
        *(p + i) = *(p_martix + i);
    for (int i = 0; i < (x_count - 1); i++) {
        if ((martix[0][i] == '0') || (martix[0][i] == '2'))
            gates++;
        if ((martix[y_count - 1][i] == '0') || (martix[y_count - 1][i] == '2'))
            gates++;
    }
    for (int i = 0; i < (y_count - 1); i++) {
        if ((martix[i][0] == '0') || (martix[i][0] == '1'))
            gates++;
        if ((martix[i][x_count - 1]) == '0' || (martix[i][x_count - 1] == '1'))
            gates++;
    }
}

/*findwalls() use recursion to find all the sets of connected walls.*/
/*in this function, it use a global array recorder[][] to memorize which points
 have been checked, to avoid check them again and get a end of recursion*/
void findwalls(int *p, int y, int x) {
    int status[y_count][x_count][4];
    int *q = status;
    for (int i = 0; i < (y_count * x_count * 4); i++)
        *(q + i) = *(p + i);

    if (!recorder[y][x]) {
        recorder[y][x] = 1;
        if ((status[y][x][0]) && (!recorder[y - 1][x]))
            findwalls(status, y - 1, x);
        if ((status[y][x][1]) && (!recorder[y][x + 1]))
            findwalls(status, y, x + 1);
        if ((status[y][x][2]) && (!recorder[y + 1][x]))
            findwalls(status, y + 1, x);
        if ((status[y][x][3]) && (!recorder[y][x - 1]))
            findwalls(status, y, x - 1);
    }
}

/*findareas() can find how many paths exist in a maze, and the set of accessible areas*/
/*similar with findwalls(), this function use recursion in areas_status[][][] by the
 connectability information stored in areas_status[][][].*/
/*the footprints of paths is recorded in globel array path_recorder[][],only the situation
 that in one recursion the number of paths is 2, the record of this recursion can be remained*/
/*the number of path baes on the number of gates which is found in this process of a recursion*/
void findareas(int y, int x) {
    int if_circle[4] = { 0 };
    if (!areas_status[y][x][1]) {
        areas_status[y][x][1] = 1;
        path_recorder[y][x] = 1;
        if ((areas_status[y][x][3]) && (path_recorder[y - 1][x]))
            if_circle[0] = 1;
        if ((areas_status[y][x][4]) && (path_recorder[y][x + 1]))
            if_circle[1] = 1;
        if ((areas_status[y][x][5]) && (path_recorder[y + 1][x]))
            if_circle[2] = 1;
        if ((areas_status[y][x][6]) && (path_recorder[y][x - 1]))
            if_circle[3] = 1;
        if ((if_circle[0] + if_circle[1] + if_circle[2] + if_circle[3]) > 1)
            circle = true;
        if (areas_status[y][x][2])
            for (int i = 3; i < 7; i++)
                if (areas_status[y][x][i] == 2)
                    path++;
        if ((areas_status[y][x][3]) && (!areas_status[y - 1][x][1]) && (y > 0))
            findareas(y - 1, x);
        if ((areas_status[y][x][4]) && (!areas_status[y][x + 1][1])
                && (x < x_count - 2))
            findareas(y, x + 1);
        if ((areas_status[y][x][5]) && (!areas_status[y + 1][x][1])
                && (y < y_count - 2))
            findareas(y + 1, x);
        if ((areas_status[y][x][6]) && (!areas_status[y][x - 1][1]) && (x > 0))
            findareas(y, x - 1);
    }
}

/*findcul()() use recursion to find the sets of cul-de-sacs*/
/*we use a digit areas_status[y][x][7] to memorize the connection for different recursion
 footprint starting from each dead ends*/
/*so if a recursion footprint meet the connection have been meet in another recursion process
 that means the two recursion footprint is connected,the set of cul-de-scas should be
 calculated just once*/
/*in a recursion, the squares whose value in areas_status[y][x][0] is 2, 3, 4 will be reduced*/
/*at last, any squares whose areas_status[y][x][0] is 1 will be cul-de-scas*/
void findcul(int y, int x) {
    switch (areas_status[y][x][0]) {
    case 0:
        break;
    case 1:
        if (areas_status[y][x][7] == 9)
            cul_de_sacs--;
        if (!areas_status[y][x][1]) {
            areas_status[y][x][1] = 1;
            if ((areas_status[y][x][3]) && (!areas_status[y - 1][x][1])
                    && (y > 0))
                findcul(y - 1, x);
            if ((areas_status[y][x][4]) && (!areas_status[y][x + 1][1])
                    && (x < x_count - 2))
                findcul(y, x + 1);
            if ((areas_status[y][x][5]) && (!areas_status[y + 1][x][1])
                    && (y < y_count - 2))
                findcul(y + 1, x);
            if ((areas_status[y][x][6]) && (!areas_status[y][x - 1][1])
                    && (x > 0))
                findcul(y, x - 1);
        }
        break;
    case 2:
        if (areas_status[y][x][7] == 9)
            cul_de_sacs--;
        if (!areas_status[y][x][1]) {
            areas_status[y][x][1] = 1;
            areas_status[y][x][0]--;
            if ((areas_status[y][x][3]) && (!areas_status[y - 1][x][1])
                    && (y > 0))
                findcul(y - 1, x);
            if ((areas_status[y][x][4]) && (!areas_status[y][x + 1][1])
                    && (x < x_count - 2))
                findcul(y, x + 1);
            if ((areas_status[y][x][5]) && (!areas_status[y + 1][x][1])
                    && (y < y_count - 2))
                findcul(y + 1, x);
            if ((areas_status[y][x][6]) && (!areas_status[y][x - 1][1])
                    && (x > 0))
                findcul(y, x - 1);
        }
        break;
    case 3:
        areas_status[y][x][7] = 9;
        areas_status[y][x][1] = 0;
        areas_status[y][x][0]--;
        break;
    case 4:
        areas_status[y][x][7] = 9;
        areas_status[y][x][1] = 0;
        areas_status[y][x][0]--;
        break;
    }
}

/*use for acquire the original data from files, and reform them into a martix,which is
 used for the following processing*/
/*this function also can judge the correct or incorrect input*/
int standardization() {
    char temp_arr[2500] = { ' ' };
    x_count = 0;
    y_count = 0;
    num_count = 0;
    int k = 0, temp = 0;
    int i_first_char, i_first_newline;
    int line[50] = { 0 };
    for (int i = 0; i < 2500; i++)
        temp_arr[i] = getchar();
    for (int j = 0; j < 50; j++) {
        for (int i = temp; i < 2500; i++)
            if ((temp_arr[i] >= '0') && (temp_arr[i] <= '3')) {
                i_first_char = i;
                break;
            }
        for (int i = i_first_char; i < 2500; i++)
            if (temp_arr[i] == 10) {
                i_first_newline = i;
                temp = i;
                break;
            }
        x_count = 0;
        for (int i = i_first_char; i <= i_first_newline; i++)
            if ((temp_arr[i] >= '0') && (temp_arr[i] <= '3'))
                x_count++;
        line[j] = x_count;
    }
    /*the number of digits for each line*/
    for (int j = 1; j < 50; j++)
        if (line[j] != line[j - 1]) {
            puts("Incorrect input.");
            return EXIT_FAILURE;
        }
    for (int i = 0; i < 2500; i++)
        if ((temp_arr[i] >= '0') && (temp_arr[i] <= '3'))
            num_count++;
    if ((num_count % x_count) == 0)
        y_count = num_count / x_count;
    else {
        puts("Incorrect input.");
        return EXIT_FAILURE;
    }
    if ((x_count < 2) || (y_count < 2)) {
        puts("Incorrect input.");
        return EXIT_FAILURE;
    }
    if ((x_count > 31) || (y_count > 41)) {
        puts("Incorrect input.");
        return EXIT_FAILURE;
    }
    char martix[y_count][x_count];
    p_martix = martix;
    for (int j = 0; j < y_count; j++)
        for (int i = 0; i < x_count; i++)
            martix[j][i] = ' ';
    for (int i = 0; i < 2500; i++)
        if ((temp_arr[i] >= '0') && (temp_arr[i] <= '3')) {
            *(p_martix + k) = temp_arr[i];
            k++;
        }
    for (int i = 0; i < y_count; i++)
        if ((martix[i][x_count - 1] == '1')
                || (martix[i][x_count - 1] == '3')) {
            puts("Incorrect input.");
            return EXIT_FAILURE;
        }
    for (int i = 0; i < x_count; i++)
        if ((martix[y_count - 1][i] == '2')
                || (martix[y_count - 1][i] == '3')) {
            puts("Incorrect input.");
            return EXIT_FAILURE;
        }
    return EXIT_SUCCESS;
}

/*print a .txt form file to contain all the information of a maze*/
/*when type command like "a.out"*/
void print_maze() {
    if (gates == 0)
        printf("The maze has no gate.\n");
    if (gates == 1)
        printf("The maze has a single gate.\n");
    if (gates > 1)
        printf("The maze has %d gates.\n", gates);
    if (walls == 0)
        printf("The maze has no wall.\n");
    if (walls == 1)
        printf("The maze has walls that are all connected.\n");
    if (walls > 1)
        printf("The maze has %d sets of walls that are all connected.\n",
                walls);
    if (inaccess_areas == 0)
        printf("The maze has no inaccessible inner point.\n");
    if (inaccess_areas == 1)
        printf("The maze has a unique inaccessible inner point.\n");
    if (inaccess_areas > 1)
        printf("The maze has %d inaccessible inner points.\n", inaccess_areas);
    if (access_areas == 0)
        printf("The maze has no accessible area.\n");
    if (access_areas == 1)
        printf("The maze has a unique accessible area.\n");
    if (access_areas > 1)
        printf("The maze has %d accessible areas.\n", access_areas);
    if (cul_de_sacs == 0)
        printf("The maze has no accessible cul-de-sac.\n");
    if (cul_de_sacs == 1)
        printf("The maze has accessible cul-de-sacs that are all connected.\n");
    if (cul_de_sacs > 1)
        printf(
                "The maze has %d sets of accessible cul-de-sacs that are all connected.\n",
                cul_de_sacs);
    if (path_no == 0)
        printf(
                "The maze has no entry-exit path with no intersection not to cul-de-sacs.\n");
    if (path_no == 1)
        printf(
                "The maze has a unique entry-exit path with no intersection not to cul-de-sacs.\n");
    if (path_no > 1)
        printf(
                "The maze has %d entry-exit paths with no intersections not to cul-de-sacs.\n",
                path_no);
}

/*print a .tex form file to creat a pdf file*/
void print_maze_pdf(int *p) {
    int status[y_count][x_count][4];
    int temp;
    int *q = status;
    printer1 = 1;
    printer2 = 0;
    for (int i = 0; i < (y_count * x_count * 4); i++)
        *(q + i) = *(p + i);
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
    for (int j = 0; j < y_count; j++)
        for (int i = 0; i < x_count; i++)
            if (recorder[j][i] == 1)
                print_pdf_wall_x(status, j, i);
    for (int i = 0; i < x_count; i++)
        for (int j = 0; j < y_count; j++)
            if (recorder[j][i] == 2)
                print_pdf_wall_y(status, j, i);
    printf("%Pillars\n");
    for (int j = 0; j < y_count; j++)
        for (int i = 0; i < x_count; i++)
            if (!(status[j][i][0] + status[j][i][1] + status[j][i][2]
                    + status[j][i][3]))
                printf("    \\fill[green] (%d,%d) circle(0.2);\n", i, j);
    puts("%Inner points in accessible cul-de-sacs");
    for (int j = 0; j < y_count - 1; j++)
        for (int i = 0; i < x_count - 1; i++)
            if ((areas_status[j][i][0] == 1) && (!areas_status[j][i][8]))
                printf("    \\node at (%.1f,%.1f) {};\n", i + 0.5, j + 0.5);
    puts("%Entry-exit paths without intersections");
    for (int j = 0; j < y_count - 1; j++)
        for (int i = 0; i < x_count - 1; i++)
            if ((path_recorder[j][i]) && (!print_recorder[j][i])
                    && (areas_status[j][i][0] == 2))
                print_pdf_path_x(j, i);
    for (int i = 0; i < x_count - 1; i++)
        for (int j = 0; j < y_count - 1; j++)
            if ((path_recorder[j][i]) && (print_recorder[j][i] == 1)
                    && (areas_status[j][i][0] == 2))
                print_pdf_path_y(j, i);
    puts("\\end{tikzpicture}");
    puts("\\end{center}");
    puts("\\vspace*{\\fill}");
    printf("\n");
    puts("\\end{document}");
}

/* in print_maze_pdf(), this is use to print all the underlining for walls*/
void print_pdf_wall_x(int *p, int y, int x) {
    int status[y_count][x_count][4];
    int *q = status;
    for (int i = 0; i < (y_count * x_count * 4); i++)
        *(q + i) = *(p + i);
    if (recorder[y][x] == 1) {
        recorder[y][x] = 2;
        if ((status[y][x][1]) && (recorder[y][x + 1] == 1) && (printer1)) {
            printf("    \\draw (%d,%d) -- ", x, y);
            printer1 = 0;
            printer2 = 1;
            print_pdf_wall_x(status, y, x + 1);
        }
        if ((!status[y][x][1]) && (printer2)) {
            printf("(%d,%d);\n", x, y);
            printer1 = 1;
            printer2 = 0;
        }
    }
}

/* in print_maze_pdf(), this is use to print all the vertical line for walls*/
void print_pdf_wall_y(int *p, int y, int x) {
    int status[y_count][x_count][4];
    int *q = status;
    for (int i = 0; i < (y_count * x_count * 4); i++)
        *(q + i) = *(p + i);
    if (recorder[y][x] == 2) {
        recorder[y][x] = 3;
        if ((status[y][x][2]) && (recorder[y + 1][x] == 2) && (printer1)) {
            printf("    \\draw (%d,%d) -- ", x, y);
            printer1 = 0;
            printer2 = 1;
            print_pdf_wall_x(status, y + 1, x);
        }
        if ((!status[y][x][2]) && (printer2)) {
            printf("(%d,%d);\n", x, y);
            printer1 = 1;
            printer2 = 0;
        }
    }
}

/*in print_maze_pdf(), this is use to print all the underlining line for paths*/
void print_pdf_path_x(int y, int x) {
    if (!(print_recorder[y][x])) {
        print_recorder[y][x] = 1;
        if (((!areas_status[y][x][4]) || (areas_status[y][x + 1][0] == 1))
                && ((areas_status[y][x][3] + areas_status[y][x][5]) > 0)
                && (printer1) && (areas_status[y][x][6] == 2)) {
            printf("    \\draw[dashed, yellow] (%.1f,%.1f) -- (%.1f,%.1f);\n",
                    x - 0.5, y + 0.5, x + 0.5, y + 0.5);
            printer1 = 1;
            printer2 = 0;
        }
        if (((!areas_status[y][x][6]) || (areas_status[y][x - 1][0] == 1))
                && ((areas_status[y][x][3] + areas_status[y][x][5]) > 0)
                && (printer1) && (areas_status[y][x][5] == 4)) {
            printf("    \\draw[dashed, yellow] (%.1f,%.1f) -- (%.1f,%.1f);\n",
                    x + 1.5, y + 0.5, x + 0.5, y + 0.5);
            printer1 = 1;
            printer2 = 0;
        }
        if ((areas_status[y][x][4]) && (print_recorder[y][x + 1] == 0)
                && (printer1) && (areas_status[y][x][6] == 2)) {
            printf("    \\draw[dashed, yellow] (%.1f,%.1f) -- ", x - 0.5,
                    y + 0.5);
            printer1 = 0;
            printer2 = 1;
            print_pdf_path_x(y, x + 1);
        }
        if ((areas_status[y][x][4]) && (print_recorder[y][x + 1] == 0)
                && (printer1) && (areas_status[y][x][6] != 2)) {
            printf("    \\draw[dashed, yellow] (%.1f,%.1f) -- ", x + 0.5,
                    y + 0.5);
            printer1 = 0;
            printer2 = 1;
            print_pdf_path_x(y, x + 1);
        }
        if (((!areas_status[y][x][4]) || (areas_status[y][x + 1][0] == 1))
                && (printer2) && (areas_status[y][x][4] != 2)) {
            printf("(%.1f,%.1f);\n", x + 0.5, y + 0.5);
            printer1 = 1;
            printer2 = 0;
        }
        if ((areas_status[y][x][4]) && (printer2)
                && (areas_status[y][x][4] == 2)) {
            printf("(%.1f,%.1f);\n", x + 1.5, y + 0.5);
            printer1 = 1;
            printer2 = 0;
        }
    }
}

/* in print_maze_pdf(), this is use to print all the vertical line for paths*/
void print_pdf_path_y(int y, int x) {
    if (print_recorder[y][x] == 1) {
        print_recorder[y][x] = 2;
        if (((!areas_status[y][x][5]) || (areas_status[y + 1][x][0] == 1))
                && ((areas_status[y][x][4] + areas_status[y][x][6]) > 0)
                && (printer1) && (areas_status[y][x][3] == 2)) {
            printf("    \\draw[dashed, yellow] (%.1f,%.1f) -- (%.1f,%.1f);\n",
                    x + 0.5, y - 0.5, x + 0.5, y + 0.5);
            printer1 = 1;
            printer2 = 0;
        }
        if (((!areas_status[y][x][3]) || (areas_status[y - 1][x][0] == 1))
                && ((areas_status[y][x][4] + areas_status[y][x][6]) > 0)
                && (printer1) && (areas_status[y][x][5] == 2)) {
            printf("    \\draw[dashed, yellow] (%.1f,%.1f) -- (%.1f,%.1f);\n",
                    x + 0.5, y + 0.5, x + 0.5, y + 1.5);
            printer1 = 1;
            printer2 = 0;
        }
        if ((areas_status[y][x][5]) && (print_recorder[y + 1][x] == 1)
                && (printer1) && (areas_status[y][x][3] == 2)) {
            printf("    \\draw[dashed, yellow] (%.1f,%.1f) -- ", x + 0.5,
                    y - 0.5);
            printer1 = 0;
            printer2 = 1;
            print_pdf_path_y(y + 1, x);
        }
        if ((areas_status[y][x][5]) && (print_recorder[y + 1][x] == 1)
                && (printer1) && (areas_status[y][x][3] != 2)) {
            printf("    \\draw[dashed, yellow] (%.1f,%.1f) -- ", x + 0.5,
                    y + 0.5);
            printer1 = 0;
            printer2 = 1;
            print_pdf_path_y(y + 1, x);
        }
        if ((areas_status[y][x][5]) && (printer2)
                && (areas_status[y][x][5] == 2)) {
            printf("(%.1f,%.1f);\n", x + 0.5, y + 1.5);
            printer1 = 1;
            printer2 = 0;
        }
        if (((!areas_status[y][x][5]) || (areas_status[y + 1][x][0] == 1))
                && (printer2) && (areas_status[y][x][5] != 2)) {
            printf("(%.1f,%.1f);\n", x + 0.5, y + 0.5);
            printer1 = 1;
            printer2 = 0;
        }
    }
}
