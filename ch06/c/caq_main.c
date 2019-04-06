#include "circarr_queue.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

void test_new(void);
void test_enqueue(void);
void test_dequeue(void);
void test_first(void);
void test_isempty(void);
void test_size(void);
void test_resize(void);
void test_destroy(void);

int main(void)
{
    printf("Testing queue_new\n");
    test_new();

    printf("Testing enqueue\n");
    test_enqueue();

    printf("Testing dequeue\n");
    test_dequeue();

    printf("Testing first\n");
    test_first();

    printf("Testing is_empty\n");
    test_isempty();

    printf("Testing size\n");
    test_size();

    printf("Testing resize\n");
    test_resize();

    printf("testing destroy\n");
    test_destroy();
}

void test_new(void)
{
    Queue *queue = queue_new(10);

    assert(queue->capacity == 10);
    assert(queue->n == 0);
}

void test_enqueue(void)
{
    Queue *queue = queue_new(5);
    queue_enqueue(queue, 10);

    assert(queue->data[0] == 10);
    assert(queue->n == 1);

    queue_enqueue(queue, 20);
    assert(queue->data[0] == 10);
    assert(queue->data[1] == 20);
    assert(queue->n == 2);

    queue_enqueue(queue, 30);
    assert(queue->data[0] == 10);
    assert(queue->data[1] == 20);
    assert(queue->data[2] == 30);
    assert(queue->n == 3);

    queue_destroy(queue);
}

void test_dequeue(void)
{
    Queue *queue = queue_new(5);
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);

    int item = queue_dequeue(queue);
    assert(item == 10);
    assert(queue->n == 1);

    item = queue_dequeue(queue);
    assert(item == 20);
    assert(queue->n == 0);

    queue_destroy(queue);
}

void test_first(void)
{
    Queue *queue = queue_new(5);
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);

    int item = queue_first(queue);
    assert(item == 10);
    assert(queue->n == 2);

    item = queue_first(queue);
    assert(item == 10);

    queue_destroy(queue);
}

void test_isempty(void)
{
    Queue *queue = queue_new(5);
    assert(queue_isempty(queue));

    queue_enqueue(queue, 10);
    assert(queue_isempty(queue) == false);

    queue_destroy(queue);
}

void test_size(void)
{
    Queue *queue = queue_new(3);
    queue_enqueue(queue, 10);
    assert(queue_size(queue) == 1);

    queue_enqueue(queue, 20);
    assert(queue_size(queue) == 2);

    queue_destroy(queue);
}

void test_destroy(void)
{
    Queue *queue = queue_new(5);
    queue_destroy(queue);
}

void test_resize(void)
{
    Queue *queue = queue_new(3);
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 10);
    assert(queue->capacity == 3);

    queue_enqueue(queue, 10);
    assert(queue->capacity == 6);
    assert(queue->n == 4);

    queue_destroy(queue);

    queue = queue_new(8);
    assert(queue->capacity == 8);

    queue_enqueue(queue, 10);
    queue_dequeue(queue);
    assert(queue->capacity == 4);

    queue_destroy(queue);
}