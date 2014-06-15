/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Other source files, if any, one per line, starting on the next line:        *
 *       test_DL_list.c                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "DL_list.h"
#include <assert.h>
#include <stdlib.h>

DL_list create_empty_DL_list(void) {
    return NULL;
}

bool is_empty_DL_list(DL_list list) {
    return !list;
}

DL_list empty_DL_list(DL_list list) {
    while (list) {
        DL_list next = list->next;
        free(list);
        list = next;
    }
    return NULL;
}

DL_list insert_value_in_DL_list(int value, DL_list list) {
    DL_list beginning = list, previous = NULL;
    while (list) {
        if (list->value == value)
            return beginning;
        else if (list->value > value) {
            DL_node *node = malloc(sizeof(DL_node));
            assert(node);
            node->value = value;
            node->previous = previous;
            node->next = list;
            list->previous = node;
            if (previous) {
                previous->next = node;
                return beginning;
            }
            return node;
        }
        previous = list;
        list = list->next;
    }
    DL_node *node = malloc(sizeof(DL_node));
    assert(node);
    node->value = value;
    node->previous = previous;
    node->next = NULL;
    if (previous) {
        previous->next = node;
        return beginning;
    }
    return node;
}

DL_list delete_value_from_DL_list(int value, DL_list list) {
    DL_list beginning = list, previous = NULL;
    while (list) {
        if (list->value == value) {
            if (previous)
                previous->next = list->next;
            else
                beginning = beginning->next;
            if (list->next)
                list->next->previous = previous;
            free(list);
            return beginning;
        }
        previous = list;
        list = list->next;
    }
    return beginning;
}

void process_DL_list(void (*function)(DL_node), DL_list list) {
    while (list) {
        function(*list);
        list = list->next;
    }
    putchar('\n');
}

    

        



