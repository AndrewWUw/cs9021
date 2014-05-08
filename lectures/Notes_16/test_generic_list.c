/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Tests the functions defined in generic_list.h and int_list.h.  *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       generic_list.c                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "generic_list.h"

int cmp(const int *const, const int *const);
void print_list(const List *const);
void print_value(const int *const);
void test_empty_list(void);
void test_one_node_list(void);
void test_longer_lists(void);

int main(void) {
    test_empty_list();
    putchar('\n');
    test_one_node_list();
    putchar('\n');
    test_longer_lists();
    return EXIT_SUCCESS;
}

void test_empty_list(void) {
    List *pt_to_list = create_list(sizeof(int), cmp);
    printf("Length of (): %d\n", list_length(pt_to_list));
    printf("() is sorted: %s\n", list_is_sorted(pt_to_list) ? "yes" : "no");
    List *pt_to_cloned_list = duplicate_list(pt_to_list);
    reverse_list(pt_to_cloned_list);
    pt_to_list = append_list_to_list(pt_to_list, pt_to_cloned_list);
    printf("List obtained by appending the reversed duplicate of () to (): "),
        print_list(pt_to_list);
    printf("Position of 0 in (): %d\n", position_of_value_in_list(0, pt_to_list));
    int *const pt_to_value;
    printf("The last value of () can be retrieved: %s\n",
           get_last_value_from_list(pt_to_list, &pt_to_value) ? "yes" : "no");
    printf("The value at position 0 can be retrieved from (): %s\n",
           get_value_from_list_at(pt_to_list, 0, &pt_to_value) ? "yes" : "no");
    const int x2 = 2;
    prepend_to_list(&x2, pt_to_list);
    printf("() prepended with 2: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    const int x3 = 3;
    append_to_list(&x3, pt_to_list);
    printf("() appended with 3: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    const int x4 = 4;
    insert_in_list_at(&x4, pt_to_list, 8);
    printf("() with 4 inserted at location 8: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    const int x5 = 5, x9 = 9;
    printf("5 can be inserted into () before 9: %s\n",
           insert_in_list_before(&x5, pt_to_list, &x9) ? "yes" : "no");
    empty_list(pt_to_list);
    printf("5 can be inserted into () after 9: %s\n",
           insert_in_list_after(&x5, pt_to_list, &x9) ? "yes" : "no");
    empty_list(pt_to_list);
    const int x6 = 6;
    insert_in_sorted_list(&x6, pt_to_list);
    printf("6 inserted into () so that the list remains sorted: "),
        print_list(pt_to_list);
    empty_list(pt_to_list);
}

void test_one_node_list(void) {
    List *pt_to_list = create_list(sizeof(int), cmp);
    const int x1 = 1;
    prepend_to_list(&x1, pt_to_list);
    printf("Length of (1): %d\n", list_length(pt_to_list));
    printf("(1) is sorted: %s\n", list_is_sorted(pt_to_list) ? "yes" : "no");
    List *pt_to_cloned_list = duplicate_list(pt_to_list);
    reverse_list(pt_to_cloned_list);
    pt_to_list = append_list_to_list(pt_to_list, pt_to_cloned_list);
    printf("List obtained by appending the reversed duplicate of (1) to (1): "),
        print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    const int x0 = 0;
    printf("Position of 0 in (1): %d\n", position_of_value_in_list(&x0, pt_to_list));
    printf("Position of 1 in (1): %d\n", position_of_value_in_list(&x1, pt_to_list));
    int *const pt_to_value;
    get_last_value_from_list(pt_to_list, &pt_to_value);
    printf("The last value of (1): %d\n", *pt_to_value);
    get_value_from_list_at(pt_to_list, 0, &pt_to_value);
    printf("The value of (1) at position 0: %d\n", *pt_to_value);
    const int x2 = 2;
    prepend_to_list(&x2, pt_to_list);
    printf("(1) prepended with 2: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    const int x3 = 3;
    append_to_list(&x3, pt_to_list);
    printf("(1) appended with 3: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    const int x4 = 4;
    insert_in_list_at(&x4, pt_to_list, 0);
    printf("(1) with 4 inserted at location 0: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    insert_in_list_at(&x4, pt_to_list, 1);
    printf("(1) with 4 inserted at location 1: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    insert_in_list_before(&x4, pt_to_list, &x1);
    printf("(1) with 4 inserted before 1: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    insert_in_list_after(&x4, pt_to_list, &x1);
    printf("(1) with 4 inserted after 1: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    const int x6 = 6;
    insert_in_sorted_list(&x6, pt_to_list);
    printf("6 inserted into (1) so that the list remains sorted: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    const int x_6 = -6;
    insert_in_sorted_list(&x_6, pt_to_list);
    printf("-6 inserted into (1) so that the list remains sorted: "), print_list(pt_to_list);
    empty_list(pt_to_list);
}

void test_longer_lists(void) {
    List *pt_to_list = create_list(sizeof(int), cmp);
    const int x3 = 3;
    append_to_list(&x3, pt_to_list);
    const int x2 = 2;
    prepend_to_list(&x2, pt_to_list);
    const int x4 = 4;
    append_to_list(&x4, pt_to_list);
    const int x1 = 1;
    prepend_to_list(&x1, pt_to_list);
    const int x5 = 5;
    append_to_list(&x5, pt_to_list);
    printf("List obtained from (3) by prepending 2, then appending 4,\n"
           "  then prepending 1, then appending 5: "), print_list(pt_to_list);
    printf("Length of (1,2,3,4,5): %d\n", list_length(pt_to_list));
    printf("(1,2,3,4,5) is sorted: %s\n", list_is_sorted(pt_to_list) ? "yes" : "no");
    List *pt_to_cloned_list = duplicate_list(pt_to_list);
    reverse_list(pt_to_cloned_list);
    pt_to_list = append_list_to_list(pt_to_list, pt_to_cloned_list);
    printf("List obtained by appending the reversed duplicate\n"
           "  of (1,2,3,4,5) to (1,2,3,4,5): "), print_list(pt_to_list);
    printf("(1,2,3,4,5,5,4,3,2,1) is sorted: %s\n", list_is_sorted(pt_to_list) ? "yes" : "no");
    
    printf("Position of 3 in (1,2,3,4,5,5,4,3,2,1): %d\n", position_of_value_in_list(&x3, pt_to_list));
    int *const pt_to_value;
    get_last_value_from_list(pt_to_list, &pt_to_value);
    printf("The last value of (1,2,3,4,5,5,4,3,2,1): %d\n", *pt_to_value);
    get_value_from_list_at(pt_to_list, 6, &pt_to_value);
    printf("The value of (1,2,3,4,5,5,4,3,2,1) at position 6: %d\n", *pt_to_value);
    const int x6 = 6;
    insert_in_list_at(&x6, pt_to_list, 3);
    printf("(1,2,3,4,5,5,4,3,2,1) with 6 inserted at location 3: "), print_list(pt_to_list);
    const int x7 = 7;
    insert_in_list_before(&x7, pt_to_list, &x3);
    printf("(1,2,3,6,4,5,5,4,3,2,1) with 7 inserted before 3: "), print_list(pt_to_list);
    const int x8 = 8;
    insert_in_list_after(&x8, pt_to_list, &x5);
    printf("(1,2,7,3,6,4,5,5,4,3,2,1) with 8 inserted after 5: "), print_list(pt_to_list);
    empty_list(pt_to_list);
    prepend_to_list(&x1, pt_to_list);
    append_to_list(&x3, pt_to_list);
    append_to_list(&x5, pt_to_list);
    append_to_list(&x7, pt_to_list);
    insert_in_sorted_list(&x6, pt_to_list);
    printf("6 inserted into (1,3,5,7) so that the list remains sorted: "),
        print_list(pt_to_list);
    remove_from_list(&x1, pt_to_list);
    printf("1 removed from (1,3,5,6,7): "),
        print_list(pt_to_list);
    remove_from_list(&x5, pt_to_list);
    printf("5 removed from (3,5,6,7): "),
        print_list(pt_to_list);
    remove_from_list(&x7, pt_to_list);
    printf("7 removed from (3,6,7): "),
        print_list(pt_to_list);
    empty_list(pt_to_list);
}

void print_list(const List *const pt_to_list) {
    if (!pt_to_list->pt_to_head)
        printf("()\n");
    else {
        printf("(");
        apply_to_list(print_value, pt_to_list);
        printf("\b)\n");
    }
}

void print_value(const int *pt_to_int) {
    printf("%d,", *pt_to_int);
}  

int cmp(const int const *a, const int *const b) {
    return *a - *b;
}

