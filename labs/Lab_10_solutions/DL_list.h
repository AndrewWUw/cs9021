#ifndef DL_LIST_H
#define DL_LIST_H

#include <stdbool.h>

 typedef struct DL_node {
    int value;
    struct DL_node *previous;
    struct DL_node *next;
} DL_node;

typedef DL_node *DL_list;

DL_list create_empty_DL_list(void);
bool is_empty_DL_list(DL_list);
DL_list empty_DL_list(DL_list);
/* Returns the list obtained from inserting in the list
 * passed as second argument
 * the value passed as first argument.
 * List is unchanged if value already occurs in it.
 * List passed as arguments and returned list are sorted. */
DL_list insert_value_in_DL_list(int, DL_list);
/* Returns the list obtained from deleting from the list
 * passed as second argument
 * the value passed as first argument.
 * List is unchanged if value does not occur in it. */
DL_list delete_value_from_DL_list(int, DL_list);
/* Applies function provided as first argument to
 * all nodes in the list
 * passed as second argument. */
void process_DL_list(void (*)(DL_node), DL_list);

#endif



