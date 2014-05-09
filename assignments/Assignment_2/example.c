/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: The input is expected to consist of y_dim lines of x_dim       *
 *              members of {0, 1, 2, 3}, where x_dim and y_dim are at least    *
 *              equal to 2 and at most equal to MAX_X_DIM and MAX_Y_DIM,       *
 *              respectively, with possibly lines consisting of spaces only    *
 *              that will be ignored and with possibly spaces anywhere on the  *
 *              lines with digits.                                             *
 *              The xth digit n of the yth line, with 0 <= x < x_dim and *
 *              0 <= y < y_dim, is to be associated with a point situated*
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
 *              below the origin with 0 <= x < x_dim - 1 and             *
 *              0 <= y < y_dim - 1.                                      *
 *                                                                             *
 *              Practically, the input will be stored in a file and its        *
 *              contents redirected to standard input. The program will be run *
 *              with either co command-line argument or with "print" as unqiue *
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
 * Written by Huang Ruixin  for the second Assignment of COMP9021              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "others.c"

#define MAX_X_DIM 31
#define MAX_Y_DIM 41

/*function declare*/
int standardization(void);
void findareas(int, int);
void findcul(int, int);
void gatesno(void);
void print_maze(void);
void print_maze_pdf(int *);
void print_pdf_walls_x(int *, int, int);
void print_pdf_walls_y(int *, int, int);
void findwalls(int *, int, int);

/*global variables declare*/
int areas_status[MAX_Y_DIM][MAX_X_DIM][9];
int recorder[MAX_Y_DIM][MAX_X_DIM];
int print_recorder[MAX_Y_DIM - 1][MAX_X_DIM - 1];
int path_recorder[MAX_Y_DIM - 1][MAX_X_DIM - 1];
int x_count, y_count, num_count, path, cul_de_sacs, gates, access_areas,
        inaccess_areas, walls, path_no;
int printer1, printer2;
bool circle;
char *p_martix;

int main(int argc, char **argv) {
    /*standardization() is used to replace get_input()
     besides get the characters from file, it has more powerful function
     it can have the input characters arranged with standard format
     and let the arrays just keep the vaild characters*/
    if (standardization())
        return EXIT_FAILURE;
    /*gatesno() is used to get the number of maze's gates*/
    gatesno();
    /*the 3-level array is for keep the connectability information
     for each point in a maze */
    int status[y_count][x_count][4];
    /*the 2-level array is for contain the vaild characters */
    char martix[y_count][x_count];
    /*the pointer is for obtaining the modified array from a file */
    char *p;
    /*variables initialization*/
    access_areas = 0;
    inaccess_areas = 0;
    path_no = 0;
    walls = 0;
    p = martix;
    /*let the main() get the modified array from standardization()*/
    for (int i = 0; i < (y_count * x_count); i++)
        *(p + i) = *(p_martix + i);
    /* for(int j = 0;j < y_count;j++){
     putchar('\n');
     for(int i = 0;i < x_count;i++)
     printf("%c",martix[j][i]);
     }*/
    /*arrays initialization*/
    for (int j = 0; j < y_count; j++)
        for (int i = 0; i < x_count; i++)
            for (int z = 0; z < 4; z++)
                status[j][i][z] = 0;
    for (int j = 0; j < MAX_Y_DIM; j++)
        for (int i = 0; i < MAX_X_DIM; i++)
            recorder[j][i] = 0;
    for (int j = 0; j < MAX_Y_DIM - 1; j++)
        for (int i = 0; i < MAX_X_DIM - 1; i++)
            print_recorder[j][i] = 0;
    for (int j = 0; j < MAX_Y_DIM - 1; j++)
        for (int i = 0; i < MAX_X_DIM - 1; i++)
            path_recorder[j][i] = 0;
    /* the loops get the connectability information on the maze
     and store them into the status[][][]. status[][][] is a
     3-level array,whose format is 4 digits [0][0][0][0] means
     this point isn't connected with any neigbour, [1][0][0][0]
     means it is connected with the point locates up of it,
     [0][1][0][1] means it is connected the points locates up
     and left of it...*/
    for (int j = 0; j < y_count; j++) {
        for (int i = 0; i < x_count; i++) {
            switch (martix[j][i]) {
            case '0':
                if (((martix[j - 1][i] == '2') || (martix[j - 1][i] == '3'))
                        && (j >= 1))
                    status[j][i][0] = 1;
                if (((martix[j][i - 1] == '1') || (martix[j][i - 1] == '3'))
                        && (i >= 1))
                    status[j][i][3] = 1;
                break;
            case '1':
                if (((martix[j - 1][i] == '2') || (martix[j - 1][i] == '3'))
                        && (j >= 1))
                    status[j][i][0] = 1;
                if (((martix[j][i - 1] == '1') || (martix[j][i - 1] == '3'))
                        && (i >= 1))
                    status[j][i][3] = 1;
                if ((martix[j][i + 1] >= '0') && (i < x_count - 1))
                    status[j][i][1] = 1;
                break;
            case '2':
                if (((martix[j - 1][i] == '2') || (martix[j - 1][i] == '3'))
                        && (j >= 1))
                    status[j][i][0] = 1;
                if (((martix[j][i - 1] == '1') || (martix[j][i - 1] == '3'))
                        && (i >= 1))
                    status[j][i][3] = 1;
                if ((martix[j + 1][i] >= '0') && (j < y_count - 1))
                    status[j][i][2] = 1;
                break;
            case '3':
                if (((martix[j - 1][i] == '2') || (martix[j - 1][i] == '3'))
                        && (j >= 1))
                    status[j][i][0] = 1;
                if (((martix[j][i - 1] == '1') || (martix[j][i - 1] == '3'))
                        && (i >= 1))
                    status[j][i][3] = 1;
                if ((martix[j][i + 1] >= '0') && (i < x_count - 1))
                    status[j][i][1] = 1;
                if ((martix[j + 1][i] >= '0') && (j < y_count - 1))
                    status[j][i][2] = 1;
                break;
            }
        }
    }
    /*use findwall() to find the numbers of walls, for some isolated point,that is
     the kind of point isn't connected with any neigbours, findwall() will avoid
     to check them */
    for (int j = 0; j < y_count; j++)
        for (int i = 0; i < x_count; i++) {
            if (!(status[j][i][0] || status[j][i][1] || status[j][i][2]
                    || status[j][i][3]))
                continue;
            if (!recorder[j][i]) {
                findwalls(status, j, i);
                walls++;
            }
        }
    /*use another 3-level array to store the information of every squares
     in the maze. the connectability of each squares can be analyzed from
     the 2 points formed the square .*/
    /*similarly, we use 4 digits out of 9 digits to represent the connection.
     from areas_status[y][x][3] to areas_status[y][x][6], these digits is
     used to represent the connectability on up,right,down,left respectively*/
    for (int j = 0; j < 41; j++)
        for (int i = 0; i < 31; i++)
            for (int z = 0; z < 9; z++)
                areas_status[j][i][z] = 0;
    for (int j = 0; j < y_count - 1; j++)
        for (int i = 0; i < x_count - 1; i++) {
            if ((martix[j][i] == '0') || (martix[j][i] == '2'))
                areas_status[j][i][3] = 1;
            if ((martix[j][i + 1] == '0') || (martix[j][i + 1] == '1'))
                areas_status[j][i][4] = 1;
            if ((martix[j + 1][i] == '0') || (martix[j + 1][i] == '2'))
                areas_status[j][i][5] = 1;
            if ((martix[j][i] == '0') || (martix[j][i] == '1'))
                areas_status[j][i][6] = 1;
        }
    /*we use the areas_status[y][x][0] to represent how many directions the
     squares have,its value is equare to the sum from areas_status[y][x][3]
     to areas_status[y][x][6]*/
    for (int j = 0; j < y_count - 1; j++)
        for (int i = 0; i < x_count - 1; i++)
            for (int z = 3; z < 7; z++)
                areas_status[j][i][0] += areas_status[j][i][z];
    /*these following statement is to judge if the current squares is a gate,
     if it is a gate, we use 2 from areas_status[y][x][3] to areas_status[y][x][6],
     instead of 1,to represent the gates for diff direction*/
    /* and we use areas_status[y][x][2] to represent it is a gate.*/
    for (int i = 0; i < (x_count - 1); i++)
        if ((martix[0][i] == '0') || (martix[0][i] == '2')) {
            areas_status[0][i][3] = 2;
            areas_status[0][i][2] = 1;
        }
    for (int i = 0; i < (x_count - 1); i++)
        if ((martix[y_count - 1][i] == '0')
                || (martix[y_count - 1][i] == '2')) {
            areas_status[y_count - 2][i][5] = 2;
            areas_status[y_count - 2][i][2] = 1;
        }
    for (int i = 0; i < (y_count - 1); i++)
        if ((martix[i][0] == '0') || (martix[i][0] == '1')) {
            areas_status[i][0][6] = 2;
            areas_status[i][0][2] = 1;
        }
    for (int i = 0; i < (y_count - 1); i++)
        if ((martix[i][x_count - 1]) == '0'
                || (martix[i][x_count - 1] == '1')) {
            areas_status[i][x_count - 2][4] = 2;
            areas_status[i][x_count - 2][2] = 1;
        }
    /*use areas_status[y][x][1] to represent if the square has been checked*/
    /*use findareas() to find the number of accessible areas.*/
    /*use path_recorder[][] to store the records of checking, and to clean the
     records when one path have more than one exits. only for the situation that
     "one enter--one exit" will be remained, and stored in path_recorder[][].*/
    /*    for(int j = 0;j < y_count - 1;j++){
     putchar('\n');
     for(int i = 0;i < x_count - 1;i++){
     putchar(' ');
     for(int z = 2;z < 7;z++)
     printf("%d",areas_status[j][i][z]);
     }
     }*/
    for (int j = 0; j < y_count - 1; j++)
        for (int i = 0; i < x_count - 1; i++)
            if ((!areas_status[j][i][1]) && (areas_status[j][i][2])) {
                path = 0;
                circle = false;
                for (int k = 0; k < y_count - 1; k++)
                    for (int g = 0; g < x_count - 1; g++)
                        if (path_recorder[k][g] == 1)
                            path_recorder[k][g]++;
                findareas(j, i);
                if ((path == 2)&&(circle == false))
                path_no ++;
                else
                for(int k = 0;k < y_count -1;k++)
                for(int g =0;g < for(int 1;j++
                                )
                                1* areas_status[j][i][0] ends, maze, *the checked* shouldn?t cul_de_scas cul_de_sacs, findcul() *use areas_status[j][i][1]="0;" 1;i++
                                ) * examined *clean inaccess_areas++; areas_status[j][i][8](
                                        !areas_status[j][i][1])
                                {
                                    squares* here
                                    usages other
                                    areas_status[y][x][1]
                                    need *because
                                    must then
                                examinated, havn?t findares(), *by square* digit,areas_status[y][x][8],to}
                            * ?,path_recorder[j][i]); printf(?%d putchar(?\n?); 1;
                            j++
                        ) { access_areas++; path_recorder[k][g]="0;" 1) (path_recorder[k][g]="=" 1;g++)>

                        }
                    }
        }
