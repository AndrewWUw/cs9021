/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the strspn, strcspn and strpbrk functions          *
 *              provided in string.h                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char s[] = "12345678";
    
    const char set1[] = "311932";
    printf("Length of longest initial segment of %s consisting of symbols in %s: %zu\n",
           s, set1, strspn(s, set1));
    printf("Length of longest initial segment of %s consisting of symbols in %s: %zu\n",
           s, s, strspn(s, s));
    printf("Length of longest initial segment of %s consisting of symbols in \"\": %zu\n\n",
           s, strspn(s, ""));

    const char set2[] = "3938467";
    printf("Length of longest leftmost segment of %s consisting of symbols not in %s: %zu\n",
           s, set2, strcspn(s, set2));
    printf("Length of longest leftmost segment of %s consisting of symbols not in %s: %zu\n",
           s, s, strcspn(s, s));
    printf("Length of longest leftmost segment of %s consisting of symbols not in \"\": %zu\n\n",
           s, strcspn(s, ""));

    const char set3[] = "85549";
    printf("String %s stored at location %p\n", s, s);
    printf("Location of the first occurrence in %s of a character in %s: %p\n",
           s, set3, strpbrk(s, set3));
    printf("Location of the first occurrence in %s of a character in \"\": %p\n",
           s, strpbrk(s, ""));
    printf("Location of the first occurrence in %s of a character in \"\\0\": %p\n",
           s, strpbrk(s, "\0"));
    
    return EXIT_SUCCESS;
}

