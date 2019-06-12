#include <stdlib.h>
#include <stdio.h>
#include "circarr_queue.h"

// Define the functions here
Queue *queue_new(int capacity)
{
    Queue *queue = malloc(sizeof(Queue));
    if (!queue)
    {
        printf("Unable to malloc queue.");
    }

    queue->front = 0;
    queue->capacity = capacity;
    queue->n = 0;
    queue->data = malloc(sizeof(binary_node *) * capacity);
    if (!queue->data)
    {
        printf("Unable to malloc data array in queue");
    }

    return queue;
}

void queue_enqueue(Queue *queue, binary_node *item)
{
    if (queue->n == queue->capacity)
    {
        _queue_resize(queue, queue->capacity * 2);
    }

    int idx = (queue->n + queue->front) % queue->capacity;
    // printf("Append at idx: %i, %i\n", idx, item);

    queue->data[idx] = item;
    queue->n += 1;
}

binary_node *queue_dequeue(Queue *queue)
{
    binary_node *item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->n -= 1;

    if (queue->n < queue->capacity / 4)
    {
        _queue_resize(queue, queue->capacity / 2);
    }

    return item;
}

binary_node *queue_first(Queue *queue)
{
    return queue->data[queue->front];
}

bool queue_isempty(Queue *queue)
{
    return queue->n == 0;
}

int queue_size(Queue *queue)
{
    return queue->n;
}

void queue_destroy(Queue *queue)
{
    free(queue->data);
    free(queue);
}

void _queue_resize(Queue *queue, int new_capacity)
{
    binary_node **new_data = malloc(sizeof(binary_node *) * new_capacity);
    if (!new_data)
    {
        printf("Unable to alloc new array!");
    }

    for (int i = 0; i < queue->n; i++)
    {
        int idx = (queue->front + i) % queue->capacity;
        new_data[i] = queue->data[idx];
    }

    // Overwrite the original struct with the new struct
    free(queue->data);
    queue->data = new_data;

    // Reset the front of the queue to 0
    queue->front = 0;
    queue->capacity = new_capacity;
}