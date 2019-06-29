#include "heap_arr.h"
#include <assert.h>
#include <stdio.h>


void test_init(void)
{
    printf("Testing heap init...");
    MinHeap *hp = minheap_new();
    assert (hp->n == 0);
    printf("OK!\n");
}

void test_min(void)
{
    printf("Testing heap min...");
    MinHeap *hp = minheap_new();
    minheap_insert(hp, 5, 1);

    HeapItem item = minheap_min(hp);
    assert (item.key == 5);
    assert (item.value == 1);
    printf("OK!\n");
}

void test_insert(void)
{
    printf("Testing heap insert...");
    MinHeap *hp = minheap_new();
    minheap_insert(hp, 5, 1);

    HeapItem item = minheap_min(hp);
    assert (item.key == 5);
    assert (item.value == 1);

    minheap_insert(hp, 3, 2);

    item = minheap_min(hp);
    assert (item.key == 3);
    assert (item.value == 2);

    minheap_insert(hp, 9, 3);

    item = minheap_min(hp);
    assert (item.key == 3);
    assert (item.value == 2);

    printf("OK!\n");
}

void test_pop(void)
{
    printf("Testing heap pop...");
    MinHeap *hp = minheap_new();

    minheap_insert(hp, 5, 1);
    minheap_insert(hp, 9, 3);
    minheap_insert(hp, 3, 2);
    minheap_insert(hp, 7, 4);

    HeapItem item = minheap_pop(hp);

    assert (hp->n == 3);
    assert (minheap_min(hp).key == 5);
    assert (item.key == 3 & item.value == 2);

    item = minheap_pop(hp);
 
    assert (hp->n == 2);
    assert (minheap_min(hp).key == 7);
    assert (item.key == 5);
    assert (item.value == 1);

    item = minheap_pop(hp);
    
    assert (hp->n == 1);
    assert (minheap_min(hp).key == 9);
    assert (item.key == 7);
    assert (item.value == 4);

    printf("OK!\n");
}

int main(void)
{
    test_init();
    test_min();
    test_insert();
    test_pop();
}