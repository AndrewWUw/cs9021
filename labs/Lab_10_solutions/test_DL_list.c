/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Other source files, if any, one per line, starting on the next line:        *
 *     DL_list.c                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "DL_list.h"

void print_node(DL_node node) {
    printf("%d ", node.value);
}

int main(void) {
    DL_list list = create_empty_DL_list();
    process_DL_list(print_node, list);
    list = empty_DL_list(list);
    list = insert_value_in_DL_list(5, list);
    process_DL_list(print_node, list);
    list = insert_value_in_DL_list(2, list);
    process_DL_list(print_node, list);
    list = insert_value_in_DL_list(2, list);
    process_DL_list(print_node, list);
    list = insert_value_in_DL_list(7, list);
    process_DL_list(print_node, list);
    list = insert_value_in_DL_list(7, list);
    process_DL_list(print_node, list);
    list = delete_value_from_DL_list(9, list);
    process_DL_list(print_node, list);
    list = delete_value_from_DL_list(5, list);
    process_DL_list(print_node, list);
    list = delete_value_from_DL_list(5, list);
    process_DL_list(print_node, list);
    list = delete_value_from_DL_list(2, list);
    process_DL_list(print_node, list);
    list = delete_value_from_DL_list(7, list);
    process_DL_list(print_node, list);
    list = delete_value_from_DL_list(9, list);
    process_DL_list(print_node, list);
    list = insert_value_in_DL_list(7, list);
    process_DL_list(print_node, list);
    return EXIT_SUCCESS;
}


