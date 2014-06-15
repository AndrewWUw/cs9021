#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>

#define MAX_QUEUE 4

/* By default, nodes are data items of type int.
 * Modify as needed. */
typedef int Node;

/* typedef struct { */
/*     char *label; */
/*     int value; */
/* } Node; */

typedef struct {
    int front;
    int rear;
    int capacity;
    Node contents[MAX_QUEUE];
} Queue;

/* Returns an empty queue. */
Queue create_empty_queue(void);
bool is_empty_queue(Queue);
/* Deletes the queue passed as argument and returns an empty queue. */
Queue empty_queue(Queue);
/* Returns the queue obtained from inserting to the rear of the queue passed as second argument
 * the node passed as first argument. */
Queue enqueue(Node, Queue);
/* Returns the queue obtained from deleting the front of the queue passed as argument.
 * Assumes that queue is not empty. */
Queue dequeue(Queue);
/* Applies function provided as first argument to all nodes in the queue
 * passed as second argument.
 * Might need to assume that queue is not full. */
void process_queue(void (*)(Node), Queue);
int queue_length(Queue);
/* Queue is full if it contains at least MAX_QUEUE elements */
bool is_full_queue(Queue);


#endif




    
