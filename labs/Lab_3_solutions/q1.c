/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int num);

int main(void) {
    for(int i = 10001; i < 99999; i+= 2) {
        int count =0;
        int gap = 0;
        if (isPrime(i)) {
            if(count == 0 || count == gap) {
                count++;
                gap = 1;
            } else {
                count = gap = 1;
            }
            if (count == 6) {
                printf("%d %d %d %d %d %d\n", i, i , i , i,i,i );
            }
        } else if (count && ++gap > count) {
            count = gap = 0;
        }
    }
    
    return EXIT_SUCCESS;
}

bool isPrime(int num) {
    bool is_prime = true;
    for (int k = 3; k <= sqrt(num); k += 2){
        if (num % k == 0) {
            is_prime = false;
            break;
        }
    }
    return is_prime;
}