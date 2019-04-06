#include "fixarr_queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue *queue_new(int capacity)
{
    // Allocate the struct and the memory within the struct and return the pointer
    Queue *queue = malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->n = 0;
    queue->data = malloc(sizeof(int) * capacity);

    if (!queue)
    {
        printf("Unable to allocate queue.");
        exit(1);
    }

    if (!queue->data)
    {
        printf("Unable to allocate array in queue.");
        exit(1);
    }

    // Initialise data to zero
    for (int i = 0; i < capacity; i++)
    {
        queue->data[i] = 0;
    }

    return queue;
}

void queue_enqueue(Queue *queue, int item)
{
    if (queue->n == queue->capacity)
    {
        printf("Cannot enqueue, queue already full");
    }
    else
    {
        queue->data[queue->n] = item;
        queue->n += 1;
    }
}

int queue_dequeue(Queue *queue)
{
    if (queue->n == 0)
    {
        printf("Cannot dequeue an empty queue");
        exit(1);
    }

    int item = queue->data[0];

    // Shuffle all items towards the head
    for (int i = 0; i < queue->n - 1; i++)
    {
        queue->data[i] = queue->data[i + 1];
    }

    // Reduce elem counter
    queue->n -= 1;
    return item;
}

int queue_first(Queue *queue)
{
    if (queue->n == 0)
    {
        printf("Queue is empty");
        exit(1);
    }

    return queue->data[0];
}

bool queue_isempty(Queue *queue)
{
    return queue->n == 0;
}

bool queue_isfull(Queue *queue)
{
    return queue->n == queue->capacity;
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