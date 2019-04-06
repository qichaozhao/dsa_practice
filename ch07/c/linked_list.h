#include <stdbool.h>

// Define our structs first
typedef struct __node {
	int item;
	struct __node *next;
} _node;

// Now define our linked list
typedef struct __ll {
	int size;
	_node *head;
	_node *tail;
} LinkedList;

// Now define all of our linked list functions
LinkedList *linkedlist_new(void);
int linkedlist_size(LinkedList *ll);
int linkedlist_getitem(LinkedList *ll, int idx);
_node *linkedlist_getnode(LinkedList *ll, int idx);
void linkedlist_reverse(LinkedList *ll);
char **linkedlist_tostr(LinkedList *ll);
void linkedlist_print(LinkedList *ll);
void linkedlist_prepend(LinkedList *ll, int item);
void linkedlist_insert(LinkedList *ll, int idx, int item);
void linkedlist_append(LinkedList *ll, int item);
int linkedlist_pop(LinkedList *ll);
int linkedlist_pop_idx(LinkedList *ll, int idx);
int linkedlist_front(LinkedList *ll);
int linkedlist_back(LinkedList *ll);
void linkedlist_del_elem(LinkedList *ll, int idx);
void linkedlist_remove_elem(LinkedList *ll, int item);
int linkedlist_find(LinkedList *ll, int item);
bool linkedlist_isempty(LinkedList *ll);
void linkedlist_destroy(LinkedList *ll);

// Helper functions
_node *linkedlist_new_node(void);
int __num_places(int num);
void dealloc_nodes_rec(_node *node);