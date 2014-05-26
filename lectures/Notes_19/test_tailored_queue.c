/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Tests the functions defined in tailored_queue.h.               *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_queue.c                                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "tailored_queue.h"

void print_queue(const Queue *const);
void print_node(const Node);

int main(void) {
    Queue queue;
    Value value;
    initialise_queue(&queue);
    printf("Queue after initialisation: "), print_queue(&queue);
    printf("Length of (): %d\n", queue_length(&queue));
    printf("() is empty: %s\n", is_empty_queue(&queue) ? "yes" : "no");
    dequeue(&queue, &value);
    printf("Queue after dequeuing: "), print_queue(&queue);
    enqueue(0, &queue);
    printf("Queue after enqueuing 0: "), print_queue(&queue);
    printf("Length of (0): %d\n", queue_length(&queue));
    printf("(0) is empty: %s\n", is_empty_queue(&queue) ? "yes" : "no");
    dequeue(&queue, &value);
    printf("Queue after dequeuing: "), print_queue(&queue);
    printf("Value being dequeued: %d\n", value);
    enqueue(0, &queue);
    enqueue(1, &queue);
    printf("Queue after enqueuing 0 and then 1: "), print_queue(&queue);
    printf("Length of (0,1): %d\n", queue_length(&queue));
    printf("(0,1) is empty: %s\n", is_empty_queue(&queue) ? "yes" : "no");
    dequeue(&queue, &value);
    printf("Queue after dequeuing: "), print_queue(&queue);
    printf("Value being dequeued: %d\n", value);
    enqueue(2, &queue);
    enqueue(3, &queue);
    printf("Queue after enqueuing 2 and then 3: "), print_queue(&queue);
    printf("Length of (1,2,3): %d\n", queue_length(&queue));
    empty_queue(&queue);
    printf("Queue after it has been emptied: "), print_queue(&queue);
}

void print_queue(const Queue *const pt_to_queue) {
    if (!pt_to_queue->length)
        printf("()\n");
    else {
        printf("(");
        apply_to_queue(print_node, pt_to_queue);
        printf("\b)\n");
    }
}

void print_node(const Node node) {
    printf("%d,", node.value);
}  
