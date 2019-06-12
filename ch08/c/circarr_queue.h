#ifndef CIRCARR_QUEUE_H
#define CIRCARR_QUEUE_H

#include <stdbool.h>
#include "bst_types.h"

// Define an alias for our vector that stores data
typedef struct __queue
{
    int front;
    int capacity;
    int n;
    binary_node **data;
} Queue;

// Define the functions here
Queue *queue_new(int capacity);
void queue_enqueue(Queue *queue, binary_node *item);
binary_node *queue_dequeue(Queue *queue);
binary_node *queue_first(Queue *queue);
bool queue_isempty(Queue *queue);
int queue_size(Queue *queue);
void queue_destroy(Queue *queue);
void _queue_resize(Queue *queue, int new_capacity);

#endif