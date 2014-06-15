/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Performs a few operations on queues, in particular,            *
 *              enqueue and dequeue.                                           *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *     queue.c                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void print_node(Node);

void print_node(Node node) {
    printf("%d ", node);
}

/* void print_node(Node node) { */
/*     printf("%s %d\n", node.label, node.value); */
/* } */

int main(void) {
    Queue queue = create_empty_queue();
    process_queue(print_node, queue);
    empty_queue(queue);
    queue = create_empty_queue();
    queue = enqueue(1, queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = enqueue(3, queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = enqueue(5, queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = dequeue(queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = enqueue(7, queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = dequeue(queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = enqueue(7, queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = dequeue(queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = enqueue(7, queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = dequeue(queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = enqueue(7, queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = dequeue(queue);
    process_queue(print_node, queue);
    putchar('\n');
    queue = enqueue(7, queue);
    process_queue(print_node, queue);
    while (!is_empty_queue(queue))
        queue = dequeue(queue);
    process_queue(print_node, queue);
    return EXIT_SUCCESS;
}

/* int main(void) { */
/*     Queue queue = create_empty_queue(); */
/*     printf("Queue length: %d\n", queue.length); */
/*     process_queue(print_node, queue); */
/*     empty_queue(queue); */
/*     queue = create_empty_queue(); */
/*     Node node1; */
/*     node1.label = "label1"; */
/*     node1.value = 1; */
/*     queue = enqueue(node1, queue); */
/*     printf("Queue length: %d\n", queue.length); */
/*     process_queue(print_node, queue); */
/*     putchar('\n'); */
/*     Node node3; */
/*     node3.label = "label3"; */
/*     node3.value = 3; */
/*     queue = enqueue(node3, queue); */
/*     printf("Queue length: %d\n", queue.length); */
/*     process_queue(print_node, queue); */
/*     putchar('\n'); */
/*     Node node5; */
/*     node5.label = "label5"; */
/*     node5.value = 5; */
/*     queue = enqueue(node5, queue); */
/*     printf("Queue length: %d\n", queue.length); */
/*     process_queue(print_node, queue); */
/*     putchar('\n'); */
/*     queue = dequeue(queue); */
/*     printf("Queue length: %d\n", queue.length); */
/*     process_queue(print_node, queue); */
/*     putchar('\n'); */
/*     Node node7; */
/*     node7.label = "label7"; */
/*     node7.value = 7; */
/*     queue = enqueue(node7, queue); */
/*     printf("Queue length: %d\n", queue.length); */
/*     process_queue(print_node, queue); */
/*     putchar('\n'); */
/*     while (!is_empty_queue(queue)) { */
        
/*         printf("%p\n", queue.front); */
/*         queue = dequeue(queue); */
/*     } */
    
/*     printf("Queue length: %d\n", queue.length); */
/*     process_queue(print_node, queue); */
/*     return EXIT_SUCCESS; */
/* } */

