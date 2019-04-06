#include <stdbool.h>

// Define a struct for our queue.
typedef struct __queue {
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
bool queue_isfull(Queue *queue);
int queue_size(Queue *queue);
void queue_destroy(Queue *queue);