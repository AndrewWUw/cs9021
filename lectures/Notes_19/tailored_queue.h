#ifndef _TAILORED_QUEUE_H_
#define _TAILORED_QUEUE_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/* Change if nodes store values of another type. */
/* typedef int Value; */

/* For simulate_queue. */
typedef struct {
    int arrival_time;
    int service_time;
} Value;

typedef struct node {
    Value value;
    struct node *pt_to_next_node;
} Node;

typedef struct {
    Node *pt_to_front_node;
    Node *pt_to_back_node;
    int length;
} Queue;

/* Initialises the 3 fields of the queue stored at pt_to_queue. */
void initialise_queue(Queue *const pt_to_queue);

/* Returns true or false, depending on whether or not the queue stored at
 * pt_to_queue is empty. */
bool is_empty_queue(const Queue *const pt_to_queue);

/* Returns the length of the queue stored at pt_to_queue. */
int queue_length(const Queue *const pt_to_queue);

/* Applies the function which is the value of pt_to_function to the values stored
 * in the queue stored at pt_to_queue. */
void apply_to_queue(void (*const pt_to_function)(), const Queue *const pt_to_queue);

/* Inserts at the back of the queue stored at pt_to_queue a node that stores val,
 * and updates the 3 fields of the queue. */
void enqueue(const Value val, Queue *const pt_to_queue);

/* If the queue stored at pt_to_queue is not empty, then stores the value of the node
 * at the front of that queue at pt_to_value, deletes the node and returns true;
 * otherwise, return false.
 * In any case, updates the 3 fields of the queue. */
bool dequeue(Queue *const pt_to_queue, Value *const pt_to_value);

/* Deletes all nodes of the queue stored at pt_to_queue, and resets the 3 fields of the queue. */
void empty_queue(Queue *const pt_to_queue);

#endif
