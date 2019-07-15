#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>

HashMap *hashmap_new(int capacity, int p)
{
    // Allocate a new dynamic array for the hash table
    HashItem **table = malloc(sizeof(HashItem *) * capacity);
    if (!table)
    {
        printf("Unable to allocate hash item table, eoiting...");
        exit(1);
    }

    // Initialise all values as available
    HashItem *init = malloc(sizeof(HashItem));
    init->key = 0;
    init->value = 0;
    init->is_available = true;
    for (int i = 0; i < capacity; i++)
    {
        table[i] = init;
    }

    // Allocate our hashmap struct
    HashMap *hashmap = malloc(sizeof(HashMap));
    if (!hashmap)
    {
        printf("Unable to allocate hash map, eoiting...");
        exit(1);
    }

    // Populate the contents
    hashmap->table = table;
    hashmap->n = 0;
    if (p == 0) { p = 109345121; }
    hashmap->p = p;
    hashmap->a = 1 + (rand() % (p - 1));
    hashmap->b = (rand() % (p - 1));
    hashmap->tbl_capacity = capacity;

    return hashmap;
}

int hashmap_hash(HashMap *hmap, int o)
{
    // Hash using a simple MAD schema
    return (((hmap->a * o) + hmap->b) % hmap->p) % hmap->tbl_capacity;
}

Slot *hashmap_find_slot(HashMap *hmap, int key)
{
    // Obtain the hash of the key
    int hashed_key = hashmap_hash(hmap, key);
    printf("Key: %i, Hashed Key: %i\n", key, hashed_key);

    // Try to read from the table
    HashItem *tbl_entry = hmap->table[hashed_key];
    while (tbl_entry->is_available == false)
    {
        if (key == tbl_entry->key)
        {
            Slot *slot = malloc(sizeof(Slot));
            slot->found = true;
            slot->hashed_key = hashed_key;
            return slot;
        }

        hashed_key = (hashed_key + 1) % (hmap->tbl_capacity);
        tbl_entry = hmap->table[hashed_key];
    }

    Slot *slot = malloc(sizeof(Slot));
    slot->found = false;
    slot->hashed_key = hashed_key;

    return slot;
}

int hashmap_get(HashMap *hmap, int key)
{
    Slot *slot = hashmap_find_slot(hmap, key);

    if (slot->found == true)
    {
        return hmap->table[slot->hashed_key]->value;
    }
    else
    {
        printf("Key not found!");
        exit(1);
    }
}

void hashmap_set(HashMap *hmap, int key, int value)
{
    Slot *slot = hashmap_find_slot(hmap, key);

    if (slot->found == true)
    {
        hmap->table[slot->hashed_key]->value = value;
    }
    else
    {
        HashItem *item = malloc(sizeof(HashItem));
        item->is_available = false;
        item->key = key;
        item->value = value;

        hmap->table[slot->hashed_key] = item;
        hmap->n += 1;
    }

    // Check if we need to resize our underlying table
    if (hmap->n > hmap->tbl_capacity / 2)
    {
        hashmap_resize(hmap, hmap->tbl_capacity * 2 - 1);
    }
}

void hashmap_del(HashMap *hmap, int key)
{
    Slot *slot = hashmap_find_slot(hmap, key);

    if (slot->found == true)
    {
        hmap->table[slot->hashed_key]->is_available = true;
        hmap->n -= 1;
    }
    else
    {
        printf("Key not found!");
        exit(1);
    }
    
}

void hashmap_resize(HashMap *hmap, int capacity)
{
    printf("Resizing!\n");
    HashItem **new_table = malloc(sizeof(HashItem *) * capacity);
    HashItem **old_table = hmap->table;

    HashItem *init = malloc(sizeof(HashItem));
    init->key = 0;
    init->value = 0;
    init->is_available = true;

    // Initialise the new table first
    for (int i = 0; i < capacity; i++)
    {
        new_table[i] = init;
    }

    // Now add the contents from the old to the new table
    hmap->table = new_table;
    int old_capacity = hmap->tbl_capacity;
    hmap->tbl_capacity = capacity;
    hmap->n = 0;

    for (int i = 0; i < old_capacity; i++)
    {
        if (old_table[i]->is_available == false)
        {
            printf("Adding key: %i, value: %i at index %i\n", old_table[i]->key, old_table[i]->value, i);
            hashmap_set(hmap, old_table[i]->key, old_table[i]->value);
        }
    }

    // Now update the other things
    free(old_table);
}

HashItem *hashmap_iter(HashMap *hmap)
{
    HashItem *out = malloc(sizeof(HashItem) * hmap->n);

    // Copy each actual hashitem into our out array
    int out_idx = 0;
    for (int i = 0; i < hmap->tbl_capacity; i++)
    {
        if (hmap->table[i]->is_available == false)
        {
            out[out_idx] = *hmap->table[i];
            out_idx += 1;
        }
    }

    return out;
}
