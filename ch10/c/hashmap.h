#include <stdbool.h>

typedef struct _item
{
	int key;
	int value;
	bool is_available;
} HashItem;

typedef struct _hashmap
{
    int n;
    int p;
    int a;
    int b;
    HashItem **table;
    int tbl_capacity;
} HashMap;

typedef struct _slot
{
    bool found;
    int hashed_key;
} Slot;

HashMap *hashmap_new(int capacity, int p);
int hashmap_hash(HashMap *hmap, int o);
Slot *hashmap_find_slot(HashMap *hmap, int key);
int hashmap_get(HashMap *hmap, int key);
void hashmap_set(HashMap *hmap, int key, int value);
void hashmap_del(HashMap *hmap, int key);
void hashmap_resize(HashMap *hmap, int capacity);
HashItem *hashmap_iter(HashMap *hmap);
