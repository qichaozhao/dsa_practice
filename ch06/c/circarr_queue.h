#include <stdbool.h>

// Define an alias for our vector that stores data
typedef struct __queue
{
    int front;
    int capacity;
    int n;
    int *data;
} Queue;

// Define the functions here
Queue *queue_new(int capacity);
void queue_enqueue(Queue *queue, int item);
int queue_dequeue(Queue *queue);
int queue_first(Queue *queue);
bool queue_isempty(Queue *queue);
int queue_size(Queue *queue);
void queue_destroy(Queue *queue);
void _queue_resize(Queue *queue, int new_capacity);