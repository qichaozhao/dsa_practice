#include "vector.h"
#include <stdbool.h>

typedef darray MinHeap;

// Our function definitions
// Public
MinHeap *minheap_new(void);
int minheap_len(MinHeap *heap);
void minheap_insert(MinHeap *heap, int key, int value);
HeapItem minheap_min(MinHeap *heap);
HeapItem minheap_pop(MinHeap *heap);

// Private
int __minheap_left(MinHeap *heap, int idx);
int __minheap_right(MinHeap *heap, int idx);
int __minheap_parent(MinHeap *heap, int idx);
bool __minheap_has_left(MinHeap *heap, int idx);
bool __minheap_has_right(MinHeap *heap, int idx);
void __minheap_swap(MinHeap *heap, int i, int j);
void __minheap_sift_up(MinHeap *heap, int idx);
void __minheap_sift_down(MinHeap *heap, int idx);