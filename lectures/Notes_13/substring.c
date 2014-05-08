/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the strstr function                                *
 *              provided in string.h                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char begin[] = "123456234567";
    const char inside1[] = "345";
    const char inside2[] = "35";
    printf("String %s stored at location %p\n", begin, begin);
    printf("Location of the first occurrence of %s in %s: %p\n",
           inside1, begin, strstr(begin, inside1));
    printf("Location of the first occurrence of %s in %s: %p\n",
           inside2, begin, strstr(begin, inside2));
    printf("Location of the first occurrence of \"\" in %s: %p\n",
           begin, strstr(begin, ""));
    
    return EXIT_SUCCESS;
}

