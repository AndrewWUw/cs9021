#ifndef _GENERIC_LIST_H_
#define _GENERIC_LIST_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/* The pt_to_value field is a generic pointer to a value whose type can be arbitrary;
 * we use the expression "datum address" to refer to this field. */
typedef struct node {
    void *pt_to_value;
    struct node *pt_to_next_node;
} Node;

/* At each datum address, data_size bytes are allocated to store the datum.
 * Besides this, a list keeps track of the address of the first node
 * (NULL if the list is empty) and of the function used to compare two data. */
typedef struct {
    Node *pt_to_head;
    char data_size;
    int (*pt_to_compare)();
} List;

/* Returns the address of a newly created list. */
List *create_list(const int data_size, int (*const pt_to_compare)());

/* Returns the address of a list that is the clone of the list pointed to by pt_to_list.
 * The data will be duplicated, so the data addresses of the nodes which make up the list
 * whose address is provided as argument and the data addresses of the nodes
 * which make up the list whose address is returned are different. */
List *duplicate_list(const List *const pt_to_list);

/* Returns the length of the list pointed to by pt_to_list. */
int list_length(const List *const pt_to_list);

/* Applies the function which is the value of pt_to_function to the values stored
 * at all data addresses in the list pointed to by pt_to_list. */
void apply_to_list(void (*const pt_to_function)(), const List *const pt_to_list);

/* Returns true or false, depending on whether or not the list pointed to by pt_to_list
 * is sorted. */
bool list_is_sorted(const List *const pt_to_list);

/* Concatenates the list pointed to by pt_to_list_1 and the list pointed to by
 * pt_to_list_2.
 * If the first list is not empty then its head becomes the head of the concatenated list;
 * otherwise the head of the second list becomes the head of the concatenated list. */
List *append_list_to_list(List *const pt_to_list_1, List *const pt_to_list_2);

/* Reverses the list pointed to by pt_to_list and updates its head to the address
 * of the first node of the resulting list (that is, the last node of the original list). */
void reverse_list(List *const pt_to_list);

/* If the value stored at pt_to_value is identical to one of the values stored at
 * the data addresses of the list pointed to by pt_to_list, then returns the index
 * (indexing the nodes from 0) of the first node that has such a datum address;
 * otherwise returns -1. */
int position_of_value_in_list(const void *const pt_to_value, const List *const pt_to_list);

/* Returns true if the list pointed to by pt_to_list is not empty, and false otherwise;
 * in the first case, stores at location pt_to_pt_to_value the datum address of the last node
 * of the list pointed to by pt_to_list. */
bool get_last_value_from_list(const List *const pt_to_list, const void **const pt_to_pt_to_value);

/* Returns true if the list pointed to by pt_to_list has at least n+1 elements,
 * and false otherwise; in the first case, stores at location pt_to_pt_to_value
 * the datum address of the node of index x (indexing the nodes from 0). */
bool get_value_from_list_at(const List *const pt_to_list, int n, const void **const pt_to_pt_to_value);

/* Adds at the beginning of the list that starts at the value of pt_to_pt_to_node,
 * a node whose datum address is a location where a value equal to the value stored
 * at pt_to_value is stored, and updates the value of pt_to_pt_to_node to the address
 * of the first node of the resulting list. */
void prepend_to_list(const void *const pt_to_value, List *const pt_to_list);

/* Adds at the end of the list pointed to by pt_to_list a node whose datum address
 * is a location where a value equal to the value stored at pt_to_value is stored. */
void append_to_list(const void *const pt_to_value, List *const pt_to_list);

/* Inserts at index n (indexing the nodes from 0) in the list pointed to by pt_to_list
 * a node whose datum address is a location where a value equal to
 * the value stored at pt_to_value is stored.
 * If the index is smaller than 0 then the node is inserted at the beginning.
 * If the index is at least equal to the length of the original list
 * then the node is inserted at the end. */
void insert_in_list_at(void *const pt_to_value, List *const pt_to_list, int n);

/* Inserts in the list pointed to by pt_to_list before the first node whose datum address
 * is a location where a value equal to the value stored at pt_to_value_2 is stored,
 * a node whose datum address is a location where a value equal to the value stored
 * at pt_to_value_1 is stored.
 * If the value stored at pt_to_value_2 is not stored in the list then the list
 * is unchanged and the function returns false; otherwise the function returns true. */
bool insert_in_list_before(const void *const pt_to_value_1, const List *const pt_to_list, const void *const pt_to_value_2);

/* Inserts in the list pointed to by pt_to_list after the first node whose datum address
 * is a location where a value equal to the value stored at pt_to_value_2 is stored,
 * a node whose datum address is a location where a value equal to the value stored
 * at pt_to_value_1 is stored.
 * If the value stored at pt_to_value_2 is not stored in the list then the list
 * is unchanged and the function returns false; otherwise the function returns true. */
 bool insert_in_list_after(const void *const pt_to_value_1, const List *const pt_to_list, const void *const pt_to_value_2);

/* Inserts in the list pointed to by pt_to_list and that is assumed to be sorted,
 * a node whose datum address is a location where a value equal to the value
 * stored at pt_to_value is stored, so that the resulting list remains sorted. */
void insert_in_sorted_list(const void *const pt_to_value, List *const pt_to_list);

/* Removes in the list pointed to by pt_to_list the first node whose datum address
 * is a location where a value equal to the value stored at pt_to_value is stored.
 * If the value stored at pt_to_value is not stored in the list then the list
 * is unchanged and the function returns false; otherwise the function returns true. */
bool remove_from_list(const void *pt_to_value, List *const pt_to_list);

/* Deletes all nodes of the list pointed to by pt_to_list and sets its head to NULL. */
void empty_list(List *const pt_to_list);

#endif
