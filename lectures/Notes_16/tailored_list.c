/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Defines list processing functions for lists whose nodes store  *
 *              values of type Value, by default defined as int in             *
 *              tailored_list.h, but that can be changed to another type       *
 *              to accomodate other needs; the function compare_values(),      *
 *              also defined in tailored_list.h, should then be changed        *
 *              accordingly.                                                   *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "tailored_list.h"

Node *create_node(const Value value) {
    Node *const pt_to_node = malloc(sizeof(Node));
    assert(pt_to_node);
    pt_to_node->value = value;
    pt_to_node->pt_to_next_node = NULL;
    return pt_to_node;
}

Node *duplicate_list(const Node *pt_to_node) {
    if (!pt_to_node)
        return NULL;
    Node *const pt_to_node_copy = create_node(pt_to_node->value);
    Node *pt_to_current_node = pt_to_node_copy;
    while (pt_to_node = pt_to_node->pt_to_next_node) {
        pt_to_current_node->pt_to_next_node = create_node(pt_to_node->value);
        pt_to_current_node = pt_to_current_node->pt_to_next_node;
    }
    pt_to_current_node->pt_to_next_node = NULL;
    return pt_to_node_copy;
}

int list_length(const Node *pt_to_node) {
    int length = 0;
    while (pt_to_node) {
        pt_to_node = pt_to_node->pt_to_next_node;
        ++length;
    }
    return length;
}

void apply_to_list(void (*const function)(), const Node *pt_to_node) {
    while (pt_to_node) {
        function(pt_to_node->value);
        pt_to_node = pt_to_node->pt_to_next_node;
    }
}

bool list_is_sorted(const Node *pt_to_node) {
    if (!pt_to_node)
        return true;
    while (pt_to_node->pt_to_next_node) {
        if (compare_values(pt_to_node->value, pt_to_node->pt_to_next_node->value) > 0)
            return false;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    return true;
}
Node *append_list_to_list(Node *const pt_to_node_1, Node *const pt_to_node_2) {
    if (!pt_to_node_1)
        return pt_to_node_2;
    if (!pt_to_node_2)
        return pt_to_node_1;
    Node *pt_to_node = pt_to_node_1;
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_node_2;
    return pt_to_node_1;
}

void reverse_list(Node **const pt_to_pt_to_node) {
    if (!*pt_to_pt_to_node)
        return;
    Node *pt_to_last_node = NULL;
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node) {
        Node *pt_to_current_node = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
        pt_to_current_node->pt_to_next_node = pt_to_last_node;
        pt_to_last_node = pt_to_current_node;
    }
    *pt_to_pt_to_node = pt_to_last_node;
}

int position_of_value_in_list(const Value value, Node *pt_to_node) {
    int position = 0;
    while (pt_to_node) {
        if (!compare_values(pt_to_node->value, value))
            return position;
        ++position;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    return -1;
}

bool get_last_value_from_list(const Node *pt_to_node, Value *pt_to_value) {
    if (!pt_to_node)
        return false;
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    *pt_to_value = pt_to_node->value;
    return true;
}

bool get_value_from_list_at(const Node *pt_to_node, int position, Value *pt_to_value) {
    if (position < 0)
        return false;
    while (position-- && pt_to_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (pt_to_node) {
        *pt_to_value = pt_to_node->value;
        return true;
    }
    return false;
}

void prepend_to_list(const Value value, Node **const pt_to_pt_to_node) {
    Node *pt_to_new_node = create_node(value);
    pt_to_new_node->pt_to_next_node = *pt_to_pt_to_node;
    *pt_to_pt_to_node = pt_to_new_node;
}

void append_to_list(const Value value, Node **const pt_to_pt_to_node) {
    Node *pt_to_new_node = create_node(value);
    if (!*pt_to_pt_to_node) {
        *pt_to_pt_to_node = pt_to_new_node;
        return;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

void insert_in_list_at(const Value value, Node **const pt_to_pt_to_node, int position) {
    if (position <= 0) {
        prepend_to_list(value, pt_to_pt_to_node);
        return;
    }
    Node *pt_to_new_node = create_node(value);
    if (!*pt_to_pt_to_node) {
        *pt_to_pt_to_node = pt_to_new_node;
        return;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    while (--position && pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

bool insert_in_list_before(const Value value_1, Node **const pt_to_pt_to_node, const Value value_2) {
    if (!*pt_to_pt_to_node)
        return false;
    if (!compare_values((*pt_to_pt_to_node)->value, value_2)) {
        prepend_to_list(value_1, pt_to_pt_to_node);
        return true;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node->pt_to_next_node && compare_values(pt_to_node->pt_to_next_node->value, value_2))
        pt_to_node = pt_to_node->pt_to_next_node;
    if (!pt_to_node->pt_to_next_node)
        return false;
    Node *const pt_to_new_node = create_node(value_1);
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
    return true;
}
    
bool insert_in_list_after(const Value value_1, Node *pt_to_node, const Value value_2) {
    if (!pt_to_node)
        return false;
    while (compare_values(pt_to_node->value, value_2) && pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (compare_values(pt_to_node->value, value_2))
        return false;
    Node *const pt_to_new_node = create_node(value_1);
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
    return true;
}

void insert_in_sorted_list(const Value value, Node **const pt_to_pt_to_node) {
    Node *const pt_to_new_node = create_node(value);
    if (!*pt_to_pt_to_node) {
        *pt_to_pt_to_node = pt_to_new_node;
        return;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    if (compare_values(pt_to_node->value, value) >= 0) {
        pt_to_new_node->pt_to_next_node = pt_to_node;
        *pt_to_pt_to_node = pt_to_new_node;
        return;
    }
    while (pt_to_node->pt_to_next_node && compare_values(pt_to_node->pt_to_next_node->value, value) < 0)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

bool remove_from_list(const Value value, Node **const pt_to_pt_to_node) {
    if (!*pt_to_pt_to_node)
        return false;
    Node *pt_to_node = *pt_to_pt_to_node;
    if (!compare_values(pt_to_node->value, value)) {
        *pt_to_pt_to_node = pt_to_node->pt_to_next_node;
        free(pt_to_node);
        return true;
    }
    if (!pt_to_node->pt_to_next_node)
        return false;
    while (compare_values(pt_to_node->pt_to_next_node->value, value) && pt_to_node->pt_to_next_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (compare_values(pt_to_node->pt_to_next_node->value, value))
        return false;
    Node *const pt_to_found_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_found_node->pt_to_next_node;
    free(pt_to_found_node);
    return true;
}

void delete_list(Node **const pt_to_pt_to_node) {
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node) {
        Node *const pt_to_current_node = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
        free(pt_to_current_node);
    }
    *pt_to_pt_to_node = NULL;
}
