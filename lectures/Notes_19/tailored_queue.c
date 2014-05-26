/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Defines queue processing functions for queues whose nodes      *
 *              store values of type Value, by default defined as int in       *
 *              tailored_queue.h, but that can be changed to another type to   *
 *              accomodate other needs.                                        *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "tailored_queue.h"

void initialise_queue(Queue *const pt_to_queue) {
    pt_to_queue->pt_to_front_node = pt_to_queue->pt_to_back_node = NULL;
    pt_to_queue->length = 0;
}

bool is_empty_queue(const Queue *const pt_to_queue) {
    return pt_to_queue->length == 0;
}

int queue_length(const Queue *const pt_to_queue) {
    return pt_to_queue->length;
}

void apply_to_queue(void (*const pt_to_function)(), const Queue *const pt_to_queue) {
    Node *pt_to_node = pt_to_queue->pt_to_front_node;
        while (pt_to_node) {
        pt_to_function(pt_to_node->value);
        pt_to_node = pt_to_node->pt_to_next_node;
    }
}

void enqueue(const Value value, Queue *const pt_to_queue) {
    Node *const pt_to_node = malloc(sizeof(Node));
    assert(pt_to_node);
    pt_to_node->value = value;
    pt_to_node->pt_to_next_node = NULL;
    if (pt_to_queue->pt_to_back_node) {
        pt_to_queue->pt_to_back_node->pt_to_next_node = pt_to_node;
        pt_to_queue->pt_to_back_node = pt_to_node;
    }
    else
        pt_to_queue->pt_to_front_node = pt_to_queue->pt_to_back_node = pt_to_node;
    ++pt_to_queue->length;
}

bool dequeue(Queue *const pt_to_queue, Value *const pt_to_value) {
    if (pt_to_queue->pt_to_front_node) {
        *pt_to_value = pt_to_queue->pt_to_front_node->value;
        Node *const pt_to_node = pt_to_queue->pt_to_front_node->pt_to_next_node;
        free(pt_to_queue->pt_to_front_node);
        pt_to_queue->pt_to_front_node = pt_to_node;
        --pt_to_queue->length;
        if (!pt_to_node)
            pt_to_queue->pt_to_back_node = NULL;
        return true;
    }
    return false;
}

void empty_queue(Queue *const pt_to_queue) {
    Node *pt_to_node = pt_to_queue->pt_to_front_node;
    while (pt_to_node) {
        Node *const pt_to_current_node = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
        free(pt_to_current_node);
    }
    pt_to_queue->pt_to_front_node = pt_to_queue->pt_to_back_node = NULL;
    pt_to_queue->length = 0;
}
