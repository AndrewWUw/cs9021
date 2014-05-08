/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Defines list processing functions for generic lists whose      *
 *              nodes store values of type pointer to void.                    *
 *              A list is a structure with three fields:                       *
 *                - a pointer to the head node;                                *
 *                - the size of the data associated with a node and stored     *
 *                  at the location the node keeps track of;                   *
 *                - a pointer to a comparison function.                        *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "generic_list.h"

static Node *create_node(const int, const char *);

List *create_list(const int data_size, int (*const pt_to_compare)()) {
    List *const pt_to_list = malloc(sizeof(List));
    assert(pt_to_list);
    pt_to_list->pt_to_head = NULL;
    pt_to_list->data_size = data_size;
    pt_to_list->pt_to_compare = pt_to_compare;
    return pt_to_list;
}  

List *duplicate_list(const List *const pt_to_list) {
    List *const pt_to_list_copy = create_list(pt_to_list->data_size, pt_to_list->pt_to_compare);
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (pt_to_node) {
        pt_to_list_copy->pt_to_head = create_node(pt_to_list->data_size, pt_to_node->pt_to_value);
        Node *pt_to_node_copy = pt_to_list_copy->pt_to_head;
        while (pt_to_node = pt_to_node->pt_to_next_node) {
            pt_to_node_copy->pt_to_next_node = create_node(pt_to_list->data_size, pt_to_node->pt_to_value);
            pt_to_node_copy = pt_to_node_copy->pt_to_next_node;
        }
        pt_to_node_copy = NULL;
    }
    return pt_to_list_copy;
}

int list_length(const List *const pt_to_list) {
    int length = 0;
    Node *pt_to_node = pt_to_list->pt_to_head;
    while (pt_to_node) {
        pt_to_node = pt_to_node->pt_to_next_node;
        ++length;
    }
    return length;
}

void apply_to_list(void (*const function)(), const List *const pt_to_list) {
    Node *pt_to_node = pt_to_list->pt_to_head;
    while (pt_to_node) {
        function(pt_to_node->pt_to_value);
        pt_to_node = pt_to_node->pt_to_next_node;
    }
}

bool list_is_sorted(const List *const pt_to_list) {
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (!pt_to_node)
        return true;
    int (*const cmp)() = pt_to_list->pt_to_compare;
    while (pt_to_node->pt_to_next_node) {
        if (cmp(pt_to_node->pt_to_value, pt_to_node->pt_to_next_node->pt_to_value) > 0)
            return false;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    return true;
}
List *append_list_to_list(List *const pt_to_list_1, List *const pt_to_list_2) {
    Node *pt_to_node_1 = pt_to_list_1->pt_to_head;
    if (!pt_to_node_1)
        return pt_to_list_2;
    Node *pt_to_node_2 = pt_to_list_2->pt_to_head;
    if (!pt_to_node_2)
        return pt_to_list_1;
    Node *pt_to_node = pt_to_node_1;
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_node_2;
    return pt_to_list_1;
}

void reverse_list(List *const pt_to_list) {
    Node *pt_to_first_node_in_reversed = NULL;
    Node *pt_to_node = pt_to_list->pt_to_head;
    while (pt_to_node) {
        Node *pt_to_new_first_node_in_reversed = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
        pt_to_new_first_node_in_reversed->pt_to_next_node = pt_to_first_node_in_reversed;
        pt_to_first_node_in_reversed = pt_to_new_first_node_in_reversed;
    }
    pt_to_list->pt_to_head = pt_to_first_node_in_reversed;
}

int position_of_value_in_list(const void *const pt_to_value, const List *const pt_to_list) {
    Node *pt_to_node = pt_to_list->pt_to_head;
    int (*const cmp)() = pt_to_list->pt_to_compare;
    int position = 0;
    while (pt_to_node) {
        if (!cmp(pt_to_node->pt_to_value, pt_to_value))
            return position;
        ++position;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    return -1;
}

bool get_last_value_from_list(const List *const pt_to_list, const void **const pt_to_pt_to_value) {
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (!pt_to_node)
        return false;
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    *pt_to_pt_to_value = pt_to_node->pt_to_value;
    return true;
}

bool get_value_from_list_at(const List *const pt_to_list, int position, const void **const pt_to_pt_to_value) {
    if (position < 0)
        return false;
    Node *pt_to_node = pt_to_list->pt_to_head;
    while (position-- && pt_to_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (pt_to_node) {
        *pt_to_pt_to_value = pt_to_node->pt_to_value;
        return true;
    }
    return false;
}

void prepend_to_list(const void *const pt_to_value, List *const pt_to_list) {
    Node *pt_to_node = create_node(pt_to_list->data_size, pt_to_value);
    pt_to_node->pt_to_next_node = pt_to_list->pt_to_head;
    pt_to_list->pt_to_head = pt_to_node;
}

void append_to_list(const void *const pt_to_value, List *const pt_to_list) {
    Node *const pt_to_new_node = create_node(pt_to_list->data_size, pt_to_value);
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (!pt_to_node) {
        pt_to_list->pt_to_head = pt_to_new_node;
        return;
    }
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

void insert_in_list_at(void *const pt_to_value, List *const pt_to_list, int position) {
    if (position <= 0) {
        prepend_to_list(pt_to_value, pt_to_list);
        return;
    }
    Node *const pt_to_new_node = create_node(pt_to_list->data_size, pt_to_value);
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (!pt_to_node) {
        pt_to_list->pt_to_head = pt_to_new_node;
        return;
    }
    while (--position && pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

bool insert_in_list_before(const void *const pt_to_value_1, const List *const pt_to_list, const void *const pt_to_value_2) {
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (!pt_to_node)
        return false;
    int (*const cmp)() = pt_to_list->pt_to_compare;    
    if (!cmp(pt_to_node->pt_to_value, pt_to_value_2)) {
        prepend_to_list(pt_to_value_1, pt_to_list);
        return true;
    }
    while (pt_to_node->pt_to_next_node && cmp(pt_to_node->pt_to_next_node->pt_to_value, pt_to_value_2))
        pt_to_node = pt_to_node->pt_to_next_node;
    if (!pt_to_node->pt_to_next_node)
        return false;
    Node *const pt_to_new_node = create_node(pt_to_list->data_size, pt_to_value_1);
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
    return true;
}
    
bool insert_in_list_after(const void *const pt_to_value_1, const List *const pt_to_list, const void *const pt_to_value_2) {
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (!pt_to_node)
        return false;
    int (*const cmp)() = pt_to_list->pt_to_compare;    
    while (cmp(pt_to_node->pt_to_value, pt_to_value_2) && pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (cmp(pt_to_node->pt_to_value, pt_to_value_2))
        return false;
    Node *const pt_to_new_node = create_node(pt_to_list->data_size, pt_to_value_1);
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
    return true;
}

void insert_in_sorted_list(const void *const pt_to_value, List *const pt_to_list) {
    Node *const pt_to_new_node = create_node(pt_to_list->data_size, pt_to_value);
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (!pt_to_node) {
        pt_to_list->pt_to_head = pt_to_new_node;
        return;
    }
    int (*const cmp)() = pt_to_list->pt_to_compare;   
    if (cmp(pt_to_value, pt_to_node->pt_to_value) <= 0) {
        pt_to_new_node->pt_to_next_node = pt_to_node;
        pt_to_list->pt_to_head = pt_to_new_node;
        return;
    }
    while (pt_to_node->pt_to_next_node && cmp(pt_to_node->pt_to_next_node->pt_to_value, pt_to_value) < 0)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

bool remove_from_list(const void *pt_to_value, List *const pt_to_list) {
    Node *pt_to_node = pt_to_list->pt_to_head;
    if (!pt_to_node)
        return false;
    int (*const cmp)() = pt_to_list->pt_to_compare;   
    if (!cmp(pt_to_node->pt_to_value, pt_to_value)) {
        Node *const pt_to_found_node = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
        pt_to_value = pt_to_found_node->pt_to_value;
        free(pt_to_value);
        free(pt_to_found_node);
        pt_to_list->pt_to_head = pt_to_node;
        return true;
    }
    if (!pt_to_node->pt_to_next_node)
        return false;
    while (cmp(pt_to_node->pt_to_next_node->pt_to_value, pt_to_value) && pt_to_node->pt_to_next_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (cmp(pt_to_node->pt_to_next_node->pt_to_value, pt_to_value))
        return false;
    Node *const pt_to_found_node = pt_to_node->pt_to_next_node;
    pt_to_value = pt_to_found_node->pt_to_value;
    pt_to_node->pt_to_next_node = pt_to_found_node->pt_to_next_node;
    free(pt_to_value);
    free(pt_to_found_node);
    return true;
}

void empty_list(List *const pt_to_list) {
    Node *pt_to_node = pt_to_list->pt_to_head;
    while (pt_to_node) {
        Node *const pt_to_node_to_delete = pt_to_node;
        void *const pt_to_value = pt_to_node->pt_to_value;
        pt_to_node = pt_to_node->pt_to_next_node;
        free(pt_to_value);
        free(pt_to_node_to_delete);
    }
    pt_to_list->pt_to_head = NULL;
}

static Node *create_node(const int data_size, const char *pt_to_value) {
    Node *const pt_to_node = malloc(sizeof(Node));
    assert(pt_to_node);
    pt_to_node->pt_to_value = malloc(data_size);
    for (int i = 0; i < data_size; ++i)
        *((char *)pt_to_node->pt_to_value + i) = *pt_to_value++;
    pt_to_node->pt_to_next_node = NULL;
    return pt_to_node;
}
