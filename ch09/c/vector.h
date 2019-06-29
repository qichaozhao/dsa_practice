#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

// Declare an item struct which we use for keeping key valeus
typedef struct _item
{
	int key;
	int value;
} HeapItem;

typedef struct _darray 
{
	int capacity;
	int n;
	HeapItem *arr;
} darray;

darray *darray_new(int capacity);
void _darray_resize(darray *darr, int new_capacity);
void darray_append(darray *darr, HeapItem item);
HeapItem darray_pop(darray *darr);
HeapItem darray_pop_idx(darray *darr, int idx);
bool darray_is_empty(darray *darr);
void darray_insert(darray *darr, int idx, HeapItem item);
void darray_prepend(darray *darr, HeapItem item);
void darray_delete(darray *darr, int idx);
void darray_remove(darray *darr, HeapItem item);
int darray_find(darray *darr, HeapItem item);
void darray_set(darray *darr, int idx, HeapItem item);
HeapItem darray_at(darray *darr, int idx);
void darray_print(darray *darr);
int darray_size(darray *darr);

#endif