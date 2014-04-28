/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Randomly fills an array of size 10x10 with 0s and 1s, and      *
 *              outputs the number chess knights needed to jump from 1s to 1s  *
 *              and visit all 1s (they can jump back to locations previously   *
 *              visited.                                                       *
 *                                                                             *
 * Written by Eric Martin and *** for COMP9021                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define DIM 10

int grid[DIM][DIM];
//int grid[DIM][DIM] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0,
//		0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0,
//		0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0,
//				0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, {
//				0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
//
//int grid[DIM][DIM] = {
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {
//	0 ,1, 0, 0, 0, 0, 0, 0, 0, 0}, {
//	0 ,0, 0, 0, 0, 0, 0, 0, 0, 0}, {
//	1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {
//	0 ,1, 0, 0, 0, 0, 0, 0, 0, 0}, {
//	0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {
//	0 ,0, 0, 0, 0, 0, 0, 0, 0, 0}, {
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//};
//
//int grid[DIM][DIM] = {
//		   {1, 0, 0, 0, 0, 0, 1, 0, 0, 0},{
//			0, 1, 0, 0, 1, 0, 0, 0, 0, 0},{
//			0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{
//			1, 0, 0, 0, 0, 0, 0, 0, 1, 0},{
//			0, 1, 0, 0, 0, 1, 0, 0, 0, 0},{
//			0, 1, 0, 0, 0, 0, 0, 0, 0, 1},{
//			0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{
//			0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{
//			0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{
//			0, 0, 0, 0, 0, 1, 0, 0, 0, 0}
//};
//
//int grid[DIM][DIM] = {
//		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0},{
//		0, 1, 0, 0, 1, 0, 0, 1, 0, 0},{
//		0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{
//		1, 0, 0, 0, 0, 0, 0, 0, 1, 0},{
//		0, 1, 0, 0, 0, 1, 0, 0, 0, 0},{
//		0, 1, 0, 0, 1, 0, 0, 1, 0, 1},{
//		0, 0, 0, 1, 0, 0, 0, 0, 0, 0},{
//		0, 0, 0, 0, 0, 0, 0, 0, 0, 1},{
//		0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{
//		0, 0, 0, 0, 0, 1, 0, 0, 0, 1}
//};
//
//int grid[DIM][DIM] = {
//	   {0, 1, 1, 0, 1, 1, 0, 1, 0, 1},{
//		0, 0, 0, 0, 0, 0, 1, 1, 0, 0},{
//		0, 1, 1, 0, 1, 1, 0, 1, 1, 1},{
//		0, 1, 0, 0, 0, 0, 1, 0, 0, 0},{
//		0, 0, 1, 1, 0, 0, 1, 0, 0, 0},{
//		0, 0, 0, 0, 1, 0, 1, 1, 1, 0},{
//		0, 0, 1, 1, 0, 0, 1, 1, 0, 1},{
//		1, 1, 0, 0, 1, 1, 0, 0, 0, 1},{
//		1, 1, 0, 0, 1, 0, 1, 1, 1, 1},{
//		0, 1, 0, 1, 1, 0, 0, 1, 1, 1}
//};
//
//int grid[DIM][DIM] = {
//	   {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},{
//		1, 0, 1, 0, 1, 0, 1, 1, 0, 1},{
//		1, 1, 1, 1, 1, 1, 1, 1, 1, 1},{
//		0, 1, 1, 1, 1, 0, 1, 0, 0, 1},{
//		1, 0, 1, 1, 1, 1, 1, 0, 1, 1},{
//		1, 0, 1, 0, 1, 1, 1, 1, 1, 0},{
//		1, 1, 1, 1, 0, 0, 1, 1, 0, 1},{
//		1, 1, 0, 0, 1, 1, 0, 1, 0, 1},{
//		1, 1, 0, 1, 1, 0, 1, 1, 1, 1},{
//		1, 1, 1, 1, 1, 1, 0, 1, 1, 1}
//};

void display_grid(void);
int explore_board(void);
/* Assuming that the cell at the intersection of row i and column j contains a 1 and
 * a knight is placed on this cell, lets the knight jump in all possible ways (consistently
 * with the rules of chess) to cells filled with 1s and eventually replaces those 1s with 0s. */
void bolt_crazy_horse(int i, int j);

int main(int argc, char **argv) {
	/* We run the program with two command line arguments. */
	if (argc != 3) {
		printf("Please provide 2 command line arguments.\n");
		return EXIT_FAILURE;
	}
	/* The first one will determine our probability distribution;
	 * it is meant to be nonzero. */
	int nb_of_possible_outcomes = strtol(argv[1], NULL, 10);
	if (!nb_of_possible_outcomes) {
		printf("The first command line argument should not be 0.\n");
		return EXIT_FAILURE;
	}
	/* We use the second command line argument, meant to be a nonnegative integer,
	 * as a seed for the random number generator. */
	srand(strtoul(argv[2], NULL, 10));
	/* We fill the grid with randomly generated 0s and 1s,
	 * with for every cell, a probability of 1/nb_of_possible_outcomes to generate a 0. */
	if (nb_of_possible_outcomes > 0)
		for (int i = 0; i < DIM; ++i)
			for (int j = 0; j < DIM; ++j)
				grid[i][j] = rand() % nb_of_possible_outcomes > 0;
	else {
		for (int i = 0; i < DIM; ++i)
			for (int j = 0; j < DIM; ++j)
				grid[i][j] = rand() % nb_of_possible_outcomes == 0;
	}
	puts("Here is the grid that has been generated:\n");
	display_grid();
	int nb_of_knights = explore_board();
	if (!nb_of_knights)
		printf("No chess knight has explored this board.\n");
	else
		printf("At least %d chess", nb_of_knights),
				nb_of_knights == 1 ?
						printf(" knight has ") : printf(" knights have "), printf(
				"explored this board.\n");
	return EXIT_SUCCESS;
}

void display_grid(void) {
	for (int i = 0; i < DIM; ++i) {
		printf("    ");
		for (int j = 0; j < DIM; ++j)
			grid[i][j] ? printf(" 1") : printf(" 0");
		putchar('\n');
	}
	putchar('\n');
}

int explore_board(void) {
	int num = 0;
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (grid[i][j] == 1) {
				bolt_crazy_horse(i, j);
				num++;
			}
		}
	}
	return num;
}

void bolt_crazy_horse(int i, int j) {

	grid[i][j] = 0;

	if (grid[i - 2][j - 1] > 0 && (i - 2) >= 0 && (j - 1) >= 0)
		bolt_crazy_horse(i - 2, j - 1);
	if (grid[i - 2][j + 1] > 0 && (i - 2) >= 0 && (j + 1) < DIM)
		bolt_crazy_horse(i - 2, j + 1);
	if (grid[i + 2][j - 1] > 0 && (i + 2) < DIM && (j - 1) >= 0)
		bolt_crazy_horse(i + 2, j - 1);
	if (grid[i + 2][j + 1] > 0 && (i + 2) < DIM && (j + 1) < DIM)
		bolt_crazy_horse(i + 2, j + 1);

	if (grid[i - 1][j - 2] > 0 && (i - 1) >= 0 && (j - 2) >= 0)
		bolt_crazy_horse(i - 1, j - 2);
	if (grid[i - 1][j + 2] > 0 && (i - 1) >= 0 && (j + 2) < DIM)
		bolt_crazy_horse(i - 1, j + 2);
	if (grid[i + 1][j - 2] > 0 && (i + 1) < DIM && (j - 2) >= 0)
		bolt_crazy_horse(i + 1, j - 2);
	if (grid[i + 1][j + 2] > 0 && (i + 1) < DIM && (j + 2) < DIM)
		bolt_crazy_horse(i + 1, j + 2);
}
