#include "heap_arr.h"
#include <stdio.h>
#include <stdlib.h>

// Implement the public functions first
MinHeap *minheap_new(void)
{
    MinHeap *hp = darray_new(16);
    return hp;
}

int minheap_len(MinHeap *heap)
{
    return heap->n;
}

void minheap_insert(MinHeap *heap, int key, int value)
{
    // Create a new item from the key and value
    HeapItem item;
    item.key = key;
    item.value = value;

    // Insert this at the end of the array
    darray_append(heap, item);

    // Up-sift
    __minheap_sift_up(heap, heap->n - 1);
}

HeapItem minheap_min(MinHeap *heap)
{
    // Return the item at the front of the priority queue without popping it
    return darray_at(heap, 0);
}

HeapItem minheap_pop(MinHeap *heap)
{
    // Return the item at the front of the priority and also remove it
    // Move the root item to the back of the queue
    __minheap_swap(heap, 0, heap->n - 1);
    
    // Pop the item
    HeapItem item = darray_pop(heap);

    // Sift down the new root
    __minheap_sift_down(heap, 0);

    return item;
}

// Private
int __minheap_left(MinHeap *heap, int idx)
{
    // Return the index of the left child based on our current index
    return 2 * idx + 1;
}

int __minheap_right(MinHeap *heap, int idx)
{
    // Return the index of the right child based on our current index
    return 2 * idx + 2;
}

int __minheap_parent(MinHeap *heap, int idx)
{
    // Return the parent of the current idx
    return (idx - 1) / 2;
}

bool __minheap_has_left(MinHeap *heap, int idx)
{
    // Return true if the current node has a left child
    return __minheap_left(heap, idx) < heap->n;
}

bool __minheap_has_right(MinHeap *heap, int idx)
{
    // Return true if the current node has a right child
    return __minheap_right(heap, idx) < heap->n;
}

void __minheap_swap(MinHeap *heap, int i, int j)
{
    // Make a swap!
    HeapItem tmp = heap->arr[i];
    heap->arr[i] = heap->arr[j];
    heap->arr[j] = tmp;
}

void __minheap_sift_up(MinHeap *heap, int idx)
{
    // If idx and parent of idx satisfy the heap property (key of idx > key of parent) then don't swap
    int parent_idx = __minheap_parent(heap, idx);
    if ((heap->arr[parent_idx].key < heap->arr[idx].key) | (idx == 0))
    {
        return;
    }
    else
    {
        // Swap the parent and the element and sift on the parent
        __minheap_swap(heap, parent_idx, idx);
        __minheap_sift_up(heap, parent_idx);
    }
}
void __minheap_sift_down(MinHeap *heap, int idx)
{
    // First we must decide which child we compare with
    int c = -1;

    // First we consider if don't have any children
    if ((__minheap_has_left(heap, idx) == false) & (__minheap_has_right(heap, idx) == false))
    {
        return;
    }
    // Now consider if we only have a left child
    else if ((__minheap_has_left(heap, idx) == true) & (__minheap_has_right(heap, idx) == false))
    {
        c = __minheap_left(heap, idx);
    }
    // Now consider if we have both children
    else if ((__minheap_has_left(heap, idx) == true) & (__minheap_has_right(heap, idx) == true))
    {
        int left_key = heap->arr[__minheap_left(heap, idx)].key;
        int right_key = heap->arr[__minheap_right(heap, idx)].key;

        if (left_key < right_key)
        {
            c = __minheap_left(heap, idx);
        }
        else
        {
            c = __minheap_right(heap, idx);
        }
    }
    else
    {
        printf("We should never get here!");
        exit(1);
    }

    // Now we check our base case, if the heap property is satisfied
    if (heap->arr[idx].key <= heap->arr[c].key)
    {
        return;
    }
    else
    {
        // Swap and sift down on the child
        __minheap_swap(heap, idx, c);
        __minheap_sift_down(heap, c);
    }
}