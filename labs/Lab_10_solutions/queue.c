/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Other source files, if any, one per line, starting on the next line:        *
 *       test_queue.c                                                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "queue.h"
#include <assert.h>
#include <stdlib.h>

Queue create_empty_queue(void) {
    Queue queue;
    queue.capacity = MAX_QUEUE;
    queue.front = 0;
    queue.rear = queue.capacity - 1;
    return queue;
}

bool is_empty_queue(Queue queue) {
    return queue.front == (queue.rear + 1) % queue.capacity;
}

Queue empty_queue(Queue queue) {
    queue.front = (queue.rear + 1) % queue.capacity;
    return queue;
}

Queue enqueue(Node node, Queue queue) {
    queue.rear = ++queue.rear % queue.capacity;
    queue.contents[queue.rear] = node;
    return queue;
}

Queue dequeue(Queue queue) {
    queue.front = ++queue.front % queue.capacity;
    return queue;
}

void process_queue(void (*function)(Node), Queue queue) {
    if (is_empty_queue(queue))
        return;
    if (queue.front <= queue.rear)
        for (int i = queue.front; i <= queue.rear; ++i) 
            function(queue.contents[i]);
    else {
        for (int i = queue.front; i < queue.capacity; ++i) 
            function(queue.contents[i]);
        for (int i = 0; i <= queue.rear; ++i) 
            function(queue.contents[i]);
    }
}

int queue_length(Queue queue) {
    return (queue.front - queue.rear) % queue.capacity + 1;
}

bool is_full_queue(Queue queue) {
    return (queue.rear + 1) % queue.capacity == queue.front;
}

    
    

        



