#include <stdio.h>
#include <stdlib.h>

void move_towers(int, int, int, int);

int main(void) {
    int num;
    printf("Enter a positive integer: ");
    scanf("%d", &num);
    move_towers(num, 1, 3, 2);
    return EXIT_SUCCESS;
}

/* Move a tower of n disks on the start-peg
   to the finish-peg using the spare-peg
   as an intermediary.*/
void move_towers(const int n, const int start, const int finish, const int spare) {
    if (n == 1)
        printf("Move a disk from peg %1d to peg %1d\n",
                          start, finish);   
    else {
        move_towers(n - 1, start, spare, finish);
        printf("Move a disk from peg %1d to peg %1d\n",
                          start, finish);
        move_towers(n - 1, spare, finish, start);
    }
}
