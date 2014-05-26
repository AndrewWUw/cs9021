#ifndef _TAILORED_LIST_H_
#define _TAILORED_LIST_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/* Change if nodes store values of another type. */
typedef int Value;

typedef struct node {
    Value value;
    struct node *pt_to_next_node;
} Node;

static int compare_values(Value, Value);

/* Change if nodes store values of another type. */
static int compare_values(Value value_1, Value value_2) {
    return value_1 - value_2;
}

/* Returns the address of a newly created node that stores val. */
Node *create_node(const Value val);

/* Returns the address of the first node of a new list that is the clone of the list
 * that starts at pt_to_node. */
Node *duplicate_list(const Node *pt_to_node);

/* Returns the length of the list that starts at pt_to_node. */
int list_length(const Node *pt_to_node);

/* Applies the function which is the value of pt_to_function to the values stored
 * in the list that starts at pt_to_node. */
void apply_to_list(void (*const pt_to_function)(), const Node *pt_to_node);

/* Returns true or false, depending on whether or not the list that starts
 * at pt_to_node is sorted. */
bool list_is_sorted(const Node *pt_to_node);

/* Concatenates the lists that start at pt_to_node_1 and pt_to_node_2, respectively.
 * If the first list is not empty then pt_to_node_1 becomes the address of the first node
 * of the concatenated list; otherwise pt_to_node_2 becomes the address of the first node
 * of the concatenated list. */
Node *append_list_to_list(Node *const pt_to_node_1, Node *const pt_to_node_2);

/* Reverses the list that starts at the value of pt_to_pt_to_node and updates the
 * value of pt_to_pt_to_node to the address of the first node of the resulting list
 * (that is, the last node of the original list). */
void reverse_list(Node **const pt_to_pt_to_node);

/* If val is identical to one of the values stored in the list that starts at
 * pt_to_node, then returns the index (indexing the nodes from 0) of the first node
 * that has such a value; otherwise returns -1. */
int position_of_value_in_list(const Value val, Node *pt_to_node);

/* If the list that starts at pt_to_node is empty then returns false;
 * otherwise, returns true and sets the value stored at pt_to_value to the value
 * that is stored in the last node of the list. */
bool get_last_value_from_list(const Node *pt_to_node, Value *pt_to_value);

/* Returns false if n is not at least equal to 0 and strictly smaller than the length
 * of the list that starts at pt_to_node; otherwise, returns true and sets
 * the value stored at pt_to_value to the value that is stored in the n-th node of the list
 * (indexing the nodes from 0). */
bool get_value_from_list_at(const Node *pt_to_node, int n, Value *pt_to_value);

/* Adds at the beginning of the list that starts at the value of pt_to_pt_to_node,
 * a node that stores val, and updates the value of pt_to_pt_to_node to the address
 * of the first node of the resulting list. */
void prepend_to_list(const Value val, Node **const pt_to_pt_to_node);

/* Adds at the end of the list that starts at the value of pt_to_pt_to_node,
 * a node that stores val, and updates the value of pt_to_pt_to_node to the address
 * of the first node of the resulting list. */
void append_to_list(const Value val, Node **const pt_to_pt_to_node);

/* Inserts at index n (indexing the nodes from 0) in the list that starts at the value
 * of pt_to_pt_to_node, a node that stores val, and updates the value of
 * pt_to_pt_to_node to the address of the first node of the resulting list.
 * If the index is smaller than 0 then the node is inserted at the beginning.
 * If the index is at least equal to the length of the original list
 * then the node is inserted at the end. */
void insert_in_list_at(const Value val, Node **const pt_to_pt_to_node, int n);

/* Inserts in the list that starts at the value of pt_to_pt_to_node, before
 * the first node that stores val_2, a node that stores val_1, and updates the
 * value of pt_to_pt_to_node to the address of the first node of the resulting list.
 * If val_2 is not stored in the list then the list is unchanged and the function
 * returns false; otherwise the function returns true. */
bool insert_in_list_before(const Value val_1, Node **const pt_to_pt_to_node, const Value val_2);

/* Inserts in the list that starts at pt_to_node, after the first node that stores val_2,
 * a node that stores val_1.
 * If val_2 is not stored in the list then the list is unchanged and the function
 * returns false; otherwise the function returns true. */
 bool insert_in_list_after(const Value val_1, Node *pt_to_node, const Value val_2);

/* Inserts in the list that starts at the value of pt_to_pt_to_node, and that is
 * assumed to be sorted, a node that stores val, so that the resulting list remains
 * sorted, and updates the value of pt_to_pt_to_node to the address of the first node
 * of the resulting list. */
void insert_in_sorted_list(const Value val, Node **const pt_to_pt_to_node);

/* Removes in the list that starts at the value of pt_to_pt_to_node, the first node that
 * stores val, and updates the value of pt_to_pt_to_node to the address of the first node
 * of the resulting list.
 * If val is not stored in the list then the list is unchanged
 * and the function returns false; otherwise the function returns true. */
bool remove_from_list(const Value val, Node **const pt_to_pt_to_node);

/* Deletes all nodes of the list that starts at the value of pt_to_pt_to_node,
 * and sets that value to NULL. */
void delete_list(Node **const pt_to_pt_to_node);

#endif
