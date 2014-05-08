/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the strchr, strrchr and memchr functions           *
 *              provided in string.h                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char s[] = "12321";
    printf("String %s stored at location %p\n", s, s);    
    char *c = strchr(s, '1');
    printf("1 first found at location %p\n", c);
    c = strchr(s, '\0');
    printf("Null character first found at location %p\n", c);
    c = strchr(s, '4');
    printf("4 first found at location %p\n", c);
    c = strrchr(s, '1');
    printf("1 last found at location %p\n\n", c);

    char *const values = malloc(8 * sizeof(char));
    *values = 0; *(values + 1) = 1;
    *(values + 2) = 2; *(values + 3) = 3;
    *(values + 4) = '\0';
    *(values + 5) = 4; *(values + 6) = 4;
    *(values + 7) = '\0';
    printf("Data stored at location %p\n", values);    
    const int *v = memchr(values, 4, 4);
    printf("4 first found at location %p\n", v);
    v = memchr(values, 4, 6);
    printf("4 first found at location %p\n", v);
    v = memchr(values, 4, 8);
    printf("4 first found at location %p\n", v);
    
    return EXIT_SUCCESS;
}

