/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prints out values and addresses from a two-dimensional array.  *
 *                                                                             *
 * Purpose: Illustrate how two-dimensonal arrays can be treated as             *
 *          pointers to pointers to the type of the arrray,                    *
 *          and that array notation can be applied to pointers.                *
 *                                                                             *
 *  Written by Eric Martin for COMP9021                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int ar[4][2] = {{2, 4}, {6, 8}, {1, 3}, {5, 7}};
    printf("   ar = %p,    ar + 1 = %p\n",
               ar,         ar + 1);
    printf("ar[0] = %p, ar[0] + 1 = %p\n", 
            ar[0],      ar[0] + 1);
    printf("  *ar = %p,   *ar + 1 = %p\n", 
              *ar,        *ar + 1);
    printf("        ar[0][0] = %d\n", ar[0][0]);
    printf("          *ar[0] = %d\n", *ar[0]);
    printf("            **ar = %d\n", **ar);
    printf("        ar[2][1] = %d\n", ar[2][1]);
    printf("*(*(ar + 2) + 1) = %d\n", *(*(ar + 2) + 1));
    putchar('\n');
    

    int (*ptr)[2] = ar;
    printf("   ptr = %p,    ptr + 1 = %p\n",
               ptr,         ptr + 1);
    printf("ptr[0] = %p, ptr[0] + 1 = %p\n", 
            ptr[0],      ptr[0] + 1);
    printf("  *ptr = %p,   *ptr + 1 = %p\n", 
              *ptr,        *ptr + 1);
    printf("        ptr[0][0] = %d\n", ptr[0][0]);
    printf("          *ptr[0] = %d\n", *ptr[0]);
    printf("            **ptr = %d\n", **ptr);
    printf("        ptr[2][1] = %d\n", ptr[2][1]);
    printf("*(*(ptr + 2) + 1) = %d\n", *(*(ptr + 2) + 1));
    return EXIT_SUCCESS;
}
