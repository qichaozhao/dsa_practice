// This is a queue implementation backed by a linked list
// Relies on the linked_list functions
#include "ll_queue.h"

Queue *queue_new(void)
{
    // Constructs a new linked list and passes back the pointer
    Queue *queue = linkedlist_new();
    return queue;
}

void queue_enqueue(Queue *queue, int item)
{
    // Use append to append a new item
    linkedlist_append(queue, item);
}

int queue_dequeue(Queue *queue)
{
    // Use pop with idx = 0 to dequeue the head item
    int item = linkedlist_pop_idx(queue, 0);
    return item;
}

int queue_first(Queue *queue)
{
    // Use the peek function of the linkedlist to check the head
    int item = linkedlist_front(queue);
    return item;
}

bool queue_isempty(Queue *queue)
{
    // Use the is_empty function of our linkedlist
    return linkedlist_isempty(queue);
}

int queue_size(Queue *queue)
{
    // Use the size variable of our linkedlist
    return queue->size;
}

void queue_destroy(Queue *queue)
{
    // Use the linkedlist destructor
    linkedlist_destroy(queue);
}