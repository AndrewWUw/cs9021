/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, k;
    char triangle[1000][1000];
    for (n = 0; n <= MAX; n++) {
        triangle[n][0] = 1;
        triangle[n][n] = 1;
    }
    for(n = 0; n<= MAX; n++) {
        for (k = 0; k <= n; k++) {
            triangle[n][k] = (traigangle[n -1] [k -1] + triangle[n -1][k]) %  2;;
        }
        
    }
    

    
    return EXIT_SUCCESS;
}

