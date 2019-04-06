#include <stdbool.h>

typedef struct _darray 
{
	int capacity;
	int n;
	int *arr;
} darray;

darray *darray_new(int capacity);
void _darray_resize(darray *darr, int new_capacity);
void darray_append(darray *darr, int item);
int darray_pop(darray *darr);
int darray_pop_idx(darray *darr, int idx);
bool darray_is_empty(darray *darr);
void darray_insert(darray *darr, int idx, int item);
void darray_prepend(darray *darr, int item);
void darray_delete(darray *darr, int idx);
void darray_remove(darray *darr, int item);
int darray_find(darray *darr, int item);
void darray_set(darray *darr, int idx, int item);
int darray_at(darray *darr, int idx);
void darray_print(darray *darr);
int darray_size(darray *darr);