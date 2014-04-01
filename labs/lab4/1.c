/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int number;
    printf("Enter strictly positive number: ");
    scanf("%d", &number);

    for (int i = 0; i < number; i++){
        for(int j = number; j > i; j--){
            putchar(' ');
        }
        
        for (int j = 0; j < i; j++){
            putchar(j + 'A');
        }

        for (int j = i - 2; j > 0; j--) {
            putchar(j + 'A');
        }
        
        putchar('\n');
    }
    
    
    


    
    return EXIT_SUCCESS;
}

