#include "linked_list.h"
#include <stdbool.h>

// Define an alias for our linked list that stores data
typedef LinkedList Queue;

// Define the functions here
Queue *queue_new(void);
void queue_enqueue(Queue *queue, int item);
int queue_dequeue(Queue *queue);
int queue_first(Queue *queue);
bool queue_isempty(Queue *queue);
int queue_size(Queue *queue);
void queue_destroy(Queue *queue);