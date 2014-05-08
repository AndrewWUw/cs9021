/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Tests the functions defined in tailored_list.h.                *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_list.c                                                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "tailored_list.h"

void print_list(const Node *const);
void print_node(const Node);
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
    Node *list = NULL;
    printf("Length of (): %d\n", list_length(list));
    printf("() is sorted: %s\n", list_is_sorted(list) ? "yes" : "no");
    Node *cloned_list = duplicate_list(list);
    reverse_list(&cloned_list);
    list = append_list_to_list(list, cloned_list);
    printf("List obtained by appending the reversed duplicate of () to (): "),
        print_list(list);
    printf("Position of 0 in (): %d\n", position_of_value_in_list(0, list));
    int value;
    printf("The last value of () can be retrieved: %s\n",
           get_last_value_from_list(list, &value) ? "yes" : "no");
    printf("The value at position 0 can be retrieved from (): %s\n",
           get_value_from_list_at(list, 0, &value) ? "yes" : "no");
    prepend_to_list(2, &list);
    printf("() prepended with 2: "), print_list(list);
    delete_list(&list);
    append_to_list(3, &list);
    printf("() appended with 3: "), print_list(list);
    delete_list(&list);
    insert_in_list_at(4, &list, 8);
    printf("() with 4 inserted at location 8: "), print_list(list);
    delete_list(&list);
    printf("5 can be inserted into () before 9: %s\n",
           insert_in_list_before(5, &list, 9) ? "yes" : "no");
    delete_list(&list);
    printf("5 can be inserted into () after 9: %s\n",
           insert_in_list_after(5, list, 9) ? "yes" : "no");
    delete_list(&list);
    insert_in_sorted_list(6, &list);
    printf("6 inserted into () so that the list remains sorted: "),
        print_list(list);
    delete_list(&list);
}

void test_one_node_list(void) {
    Node *list = create_node(1);
    printf("Length of (1): %d\n", list_length(list));
    printf("(1) is sorted: %s\n", list_is_sorted(list) ? "yes" : "no");
    Node *cloned_list = duplicate_list(list);
    reverse_list(&cloned_list);
    list = append_list_to_list(list, cloned_list);
    printf("List obtained by appending the reversed duplicate of (1) to (1): "),
        print_list(list);
    delete_list(&list);
    list = create_node(1);
    printf("Position of 0 in (1): %d\n", position_of_value_in_list(0, list));
    printf("Position of 1 in (1): %d\n", position_of_value_in_list(1, list));
    int value;
    get_last_value_from_list(list, &value);
    printf("The last value of (1): %d\n", value);
    get_value_from_list_at(list, 0, &value);
    printf("The value of (1) at position 0: %d\n", value);
    prepend_to_list(2, &list);
    printf("(1) prepended with 2: "), print_list(list);
    delete_list(&list);
    list = create_node(1);
    append_to_list(3, &list);
    printf("(1) appended with 3: "), print_list(list);
    delete_list(&list);
    list = create_node(1);
    insert_in_list_at(4, &list, 0);
    printf("(1) with 4 inserted at location 0: "), print_list(list);
    delete_list(&list);
    list = create_node(1);
    insert_in_list_at(4, &list, 1);
    printf("(1) with 4 inserted at location 1: "), print_list(list);
    delete_list(&list);
    list = create_node(1);
    insert_in_list_before(4, &list, 1);
    printf("(1) with 4 inserted before 1: "), print_list(list);
    delete_list(&list);
    list = create_node(1);
    insert_in_list_after(4, list, 1);
    printf("(1) with 4 inserted after 1: "), print_list(list);
    delete_list(&list);
    list = create_node(1);
    insert_in_sorted_list(6, &list);
    printf("6 inserted into (1) so that the list remains sorted: "), print_list(list);
    delete_list(&list);
    list = create_node(1);
    insert_in_sorted_list(-6, &list);
    printf("-6 inserted into (1) so that the list remains sorted: "), print_list(list);
    delete_list(&list);
}

void test_longer_lists(void) {
    Node *list = create_node(3);
    prepend_to_list(2, &list);
    append_to_list(4, &list);
    prepend_to_list(1, &list);
    append_to_list(5, &list);
    printf("List obtained from (3) by prepending 2, then appending 4,\n"
           "  then prepending 1, then appending 5: "), print_list(list);
    printf("Length of (1,2,3,4,5): %d\n", list_length(list));
    printf("(1,2,3,4,5) is sorted: %s\n", list_is_sorted(list) ? "yes" : "no");
    Node *cloned_list = duplicate_list(list);
    reverse_list(&cloned_list);
    list = append_list_to_list(list, cloned_list);
    printf("List obtained by appending the reversed duplicate\n"
           "  of (1,2,3,4,5) to (1,2,3,4,5): "), print_list(list);
    printf("(1,2,3,4,5,5,4,3,2,1) is sorted: %s\n", list_is_sorted(list) ? "yes" : "no");
    printf("Position of 3 in (1,2,3,4,5,5,4,3,2,1): %d\n", position_of_value_in_list(3, list));
    int value;
    get_last_value_from_list(list, &value);
    printf("The last value of (1,2,3,4,5,5,4,3,2,1): %d\n", value);
    get_value_from_list_at(list, 6, &value);
    printf("The value of (1,2,3,4,5,5,4,3,2,1) at position 6: %d\n", value);
    insert_in_list_at(6, &list, 3);
    printf("(1,2,3,4,5,5,4,3,2,1) with 6 inserted at location 3: "), print_list(list);
    insert_in_list_before(7, &list, 3);
    printf("(1,2,3,6,4,5,5,4,3,2,1) with 7 inserted before 3: "), print_list(list);
    insert_in_list_after(8, list, 5);
    printf("(1,2,7,3,6,4,5,5,4,3,2,1) with 8 inserted after 5: "), print_list(list);
    delete_list(&list);
    list = create_node(1);
    append_to_list(3, &list);
    append_to_list(5, &list);
    append_to_list(7, &list);
    insert_in_sorted_list(6, &list);
    printf("6 inserted into (1,3,5,7) so that the list remains sorted: "),
        print_list(list);
    delete_list(&list);
}

void print_list(const Node *const pt_to_node) {
    if (!pt_to_node)
        printf("()\n");
    else {
        printf("(");
        apply_to_list(print_node, pt_to_node);
        printf("\b)\n");
    }
}

void print_node(const Node node) {
    printf("%d,", node.value);
}  
