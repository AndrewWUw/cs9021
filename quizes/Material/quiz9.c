/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Takes as command line argument a nonnegative int N followed    *
 *              by at least N+1 characters, builds a linked list from these    *
 *              characters, and modifies this list so that it starts with the  *
 *              (N+1)st node A and is followed by every second node, moving    *
 *              backwards and wrapping around, followed by the node preceding  *
 *              A again followed by every second node, moving backwards and    *
 *              wrapping around.                                               *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_list.c                                                       *
 *       modify_list.c                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "tailored_list.h"
#include "modify_list.h"

void print_list(const Node *const);
void print_node(const int);
int compare(const void *, const void *);

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Provide a nonnegative number N followed by at least N + 1 characters\n"
               "        as command-line arguments.\n");
        return EXIT_FAILURE;
    }
    const int length = argc - 2;
    int starting_point = strtol(argv[1], NULL, 10);
    if (starting_point < 0) {
        printf("First argument should not be negative.\n");
        return EXIT_FAILURE;
    }
    if (length < starting_point + 1) {
        printf("Not enough characters.\n");
        return EXIT_FAILURE;
    }
    Node *list = NULL;
    for (int i = 2; i < argc; ++i)
        append_to_list(argv[i][0], &list);
    Node *nodes_before[length];
    Node *pt_to_node = list;
    for (int i = 0; i < length; ++i) {
        nodes_before[i] = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    modify_list(&list, starting_point);
    print_list(list);
    Node *nodes_after[length];
    pt_to_node = list;
    for (int i = 0; i < length; ++i) {
        nodes_after[i] = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    qsort(nodes_before, length, sizeof(Node *), compare);
    qsort(nodes_after, length, sizeof(Node *), compare);
    for (int i = 0; i < length; ++i)
       if (nodes_before[i] != nodes_after[i]) {
           printf("You cheated! Failed test.\n");
           break;
       }
    return EXIT_SUCCESS;
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

void print_node(const int value) {
    printf("%c,", value);
}

int compare(const void *a, const void *b) {
     return ((Node *)b)->value - ((Node *)a)->value;
}
