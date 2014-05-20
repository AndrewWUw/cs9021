/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes as command line argument a nonnegative int N followed    *
 *              by at least N+1 characters, builds a linked list from these    *
 *              characters, and modifies this list so that it starts with the  *
 *              (N+1)st node A and is followed by every second node, moving    *
 *              backwards and wrapping around, followed by the node preceding  *
 *              A again followed by every second node, moving backwards and    *
 *              wrapping around.                                               *
 *                                                                             *
 * Written by *** for COMP9021                                                 *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_list.c                                                       *
 *       quiz9.c                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* THIS IS THE ONLY FILE YOU HAVE TO SUBMIT.
 * IT WILL BE COMPILED WITH THE OTHER FILES YOU HAVE BEEN PROVIDED WITH. */

#include "modify_list.h"
#include <stdbool.h>

void modify_list(Node ** const pt_to_pt_to_node, const int starting_point) {

    int length = 1;
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node->pt_to_next_node) {
        pt_to_node = pt_to_node->pt_to_next_node;
        ++length;
    }

    Node *nodes[length];
    pt_to_node = *pt_to_pt_to_node;
    for (int i = 0; i < length; ++i) {
        nodes[i] = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
    }

    bool isVisited[length];
    Node *sorted_Nodes[length];
    int pos = 0;
    int i = starting_point;
    while (pos < length) {
        if (!isVisited[i]) {
            sorted_Nodes[pos] = nodes[i];
            isVisited[i] = true;
            if (i - 2 >= 0) {
                i -= 2;
            } else {
                i = length + i - 2;
            }
            ++pos;
        } else {
            if (i - 1 >= 0)
                --i;
            else
                i = length - 1;
        }
    }

    for (int i = 0; i < length; i++) {
        sorted_Nodes[i]->pt_to_next_node = sorted_Nodes[i + 1];
    }

    sorted_Nodes[length - 1]->pt_to_next_node = NULL;
    *pt_to_pt_to_node = sorted_Nodes[0];
}

