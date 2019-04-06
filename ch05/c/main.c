#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

int main(void)
{
    // Here we go through step by step to test our implementation
    printf("Allocating new vector!\n");
    darray *arr = darray_new(3);

    // Now check we made an empty array of size 10
    printf("Checking new array allocation...\n");
    assert(arr->n == 0);
    assert(arr->capacity == 3);

    // Now we append 
    printf("Checking appends...\n");
    darray_append(arr, 1);
    darray_append(arr, 1);
    darray_append(arr, 2);
    darray_append(arr, 2);

    assert(arr->n == 4);
    assert(arr->capacity == 6);
    assert(arr->arr[0] == 1);
    assert(arr->arr[1] == 1);
    assert(arr->arr[2] == 2);
    assert(arr->arr[3] == 2);

    // Now we pop
    printf("Checking pops!\n");
    int popped = darray_pop(arr);
    assert(popped == 2);
    assert(arr->n == 3);

    // Now we pop with index
    printf("Checking pop with index!\n");
    popped = darray_pop_idx(arr, 1);
    assert(popped = 1);
    assert(arr->n == 2);

    // Now we check if the array resizes down
    printf("Checking resizing down...\n");
    popped = darray_pop(arr);
    popped = darray_pop(arr);
    assert(arr->capacity == 3);
    assert(arr->n == 0);

    // Checking isempty
    printf("Checking is_empty function...\n");
    assert(darray_is_empty(arr) == true);

    // Checking insert
    printf("Checking insert functions...\n");
    darray_append(arr, 1);
    darray_insert(arr, 0, 0);
    darray_prepend(arr, -1);

    assert(arr->arr[0] == -1);
    assert(arr->arr[1] == 0);
    assert(arr->arr[2] == 1);

    // Checking delete
    printf("Checking delete functions...\n");
    darray_delete(arr, 0);
    assert(arr->arr[0] == 0);
    assert(arr->n == 2);

    // Checking remove
    printf("Checking remove functions...\n");
    darray_remove(arr, 0);
    assert(arr->n == 1);
    assert(arr->arr[0] == 1);

    // Checking darray_find
    printf("Checking find...\n");
    darray_append(arr, 2);
    darray_append(arr, 3);

    int idx = darray_find(arr, 2);
    assert(idx == 1);

    idx = darray_find(arr, 5);
    assert(idx == -1);

    // Checking darray set
    printf("Checking array set...\n");
    darray_set(arr, 0, 10);
    assert(arr->arr[0] == 10);

    // Checking array at
    printf("Checking array get...\n");
    int get = darray_at(arr, 0);
    assert(get == 10);

    // Checking darray print
    printf("Printing current array state\n");
    darray_print(arr);

    // Checking size
    printf("Checking arr size...\n");
    assert(darray_size(arr) == arr->n);
}   

