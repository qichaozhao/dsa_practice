#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

darray *darray_new(int capacity)
{
    darray *darr = malloc(sizeof(darray));
    darr->capacity = capacity;
    darr->n = 0;
    darr->arr = malloc(sizeof(int) * capacity);
    if (!darr->arr)
    {
        printf("Could not allocate new array!");
        exit(1);
    }

    return darr;
}

void _darray_resize(darray *darr, int new_capacity)
{
    // Create the new array
    darray *new_darr = darray_new(new_capacity);
    new_darr->n = darr->n;

    // Copy the contents over
    for (int i = 0; i < darr->n; i++)
    {
        new_darr->arr[i] = darr->arr[i];
    }

    // De-allocate the old array then return the new one
    *darr = *new_darr;
    free(new_darr);
}

void darray_append(darray *darr, int item)
{
    // Check we are not over capacity
    // If so resize the array
    if (darr->n == darr->capacity)
    {
        _darray_resize(darr, darr->capacity * 2);
    }

    // Perform the append
    darr->arr[darr->n] = item;
    darr->n += 1;
}

int darray_pop(darray *darr)
{
    return darray_pop_idx(darr, -1);
}

int darray_pop_idx(darray *darr, int idx)
{
    int item;
    if (idx == -1)
    {
        darr->n -= 1;
        item = darr->arr[darr->n];
    }
    else if ((idx >= 0) && (idx < darr->n))
    {
        darr->n -= 1;
        item = darr->arr[idx];

        // Now we need to shift all the elements left by 1
        for (int i = idx; i < darr->n; i++)
        {
            darr->arr[i] = darr->arr[i + 1];
        }
    }
    else
    {
        printf("Index out of bounds!");
        exit(1);
    }

    // Now check if we need to shrink the array
    if (darr->n < darr->capacity / 4)
    {
        _darray_resize(darr, darr->capacity / 2);
    }

    return item;
}

bool darray_is_empty(darray *darr)
{
    if (darr->n == 0) {
        return true;
    } else {
        return false;
    }
}

void darray_insert(darray *darr, int idx, int item)
{
    if (darr->n == darr->capacity)
    {
        _darray_resize(darr, darr->capacity * 2);
    }

    // Shift all the elements rightward by 1
    for (int i = darr->n - 1; i >= idx; i--)
    {
        darr->arr[i + 1] = darr->arr[i];
    }

    // Insert the item
    darr->arr[idx] = item;
    darr->n += 1;
}

void darray_prepend(darray *darr, int item)
{
    darray_insert(darr, 0, item);
}

void darray_delete(darray *darr, int idx)
{
    if ((0 <= idx) && (idx < darr->n))
    {
        darr->n -= 1;

        // To delete we just shift all the elements left by 1
        for (int i = 0; i < darr->n; i++)
        {
            darr->arr[i] = darr->arr[i + 1];
        }
    }
    else
    {
        printf("Index out of bounds!");
        exit(1);
    }

    // Now check if we should shrink the array
    if (darr->n < darr->capacity / 4)
    {
        _darray_resize(darr, darr->capacity / 2);
    }
}

void darray_remove(darray *darr, int item)
{
    darray *idxes = darray_new(10);
    for (int i = 0; i < darr->n; i++)
    {
        if (darr->arr[i] == item)
        {
            darray_append(idxes, i);
        }
    }

    for (int i = 0; i < idxes->n; i++)
    {
        darray_delete(darr, i);
    }

}

int darray_find(darray *darr, int item)
{
    for (int i = 0; i < darr->n; i++)
    {
        if (darr->arr[i] == item)
        {
            return i;
        }
    }

    return -1;
}

void darray_set(darray *darr, int idx, int item)
{
    if ((0 <= idx) && (idx < darr->n))
    {
        darr->arr[idx] = item;
    }
    else
    {
        printf("Index out of bounds!");
        exit(1);
    }}

int darray_at(darray *darr, int idx)
{
    if ((0 <= idx) && (idx < darr->n))
    {
        return darr->arr[idx];
    }
    else
    {
        printf("Index out of bounds!");
        exit(1);
    }
}

void darray_print(darray *darr)
{
    printf("[");
    for (int i = 0; i < darr->n - 1; i++)
    {
        printf("%i, ", darr->arr[i]);
    }
    printf("%i]", darr->arr[darr->n - 1]);
    printf("\n");
}

int darray_size(darray *darr)
{
    return darr->n;
}
