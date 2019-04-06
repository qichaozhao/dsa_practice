#include "linked_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

// Allocate a new node and and return the pointer
_node *linkedlist_new_node(void)
{
    _node *node = malloc(sizeof(_node));
    if (!node)
    {
        printf("Unable to allocate memory for new node.\n");
    }
    return node;
}


// Get the number of places in an integer
int __num_places(int n) {
    if (n < 0) return __num_places ((n == INT_MIN) ? INT_MAX : -n);
    if (n < 10) return 1;
    return 1 + __num_places (n / 10);
}


// Allocate a new linked list and return the pointer
LinkedList *linkedlist_new(void)
{
    LinkedList *ll = malloc(sizeof(LinkedList));
    if (!ll) {
        printf("Unable to allocate memory for new linked list.\n");
    }

    ll->size = 0;

    // Now allocate the sentinel node and set the head and tail pointers
    _node *sentinel = linkedlist_new_node();
    sentinel->item = 0;
    sentinel->next = NULL;

    ll->head = sentinel;
    ll->tail = sentinel;

    return ll;
}


int linkedlist_size(LinkedList *ll)
{
    return ll->size;
}


int linkedlist_getitem(LinkedList *ll, int idx)
{
    _node *node = linkedlist_getnode(ll, idx);
    return node->item;
}


_node *linkedlist_getnode(LinkedList *ll, int idx)
{
    if ((idx >= 0) && (idx < ll->size)) {
        // Traverse the list from the start until we hit our index n
        _node *sentinel = ll->head;
        _node *node = sentinel->next;

        for (int i = 0; i < idx; i++) {
            node = node->next;
        }

        return node;

    } else {

        // Return an empty node
        printf("Index out of bounds or list is empty.\n");
        _node *empty = linkedlist_new_node();
        empty->item = 0;
        empty->next = NULL;

        return empty;
    }
}


void linkedlist_reverse(LinkedList *ll)
{
    _node *sentinel = ll->head;
    _node *cur_node = sentinel->next;

    // The new tail of the list will be the first node, so let's update
    ll->tail = cur_node;

    // Now traverse through pairs of nodes in the list (cur_node, next_node)
    while (cur_node->next) {
        _node *next_node = cur_node->next;

        // Reverse the pointer held by the next node to point at the current node
        _node *tmp = next_node->next;
        next_node->next = cur_node;

        // Traverse forward one step
        cur_node = next_node;
        next_node = tmp;
    }

    // Now update the sentinel to point at the new first node
    sentinel->next = cur_node;
}


char **linkedlist_tostr(LinkedList *ll)
{
    // Malloc a list of pointers to char *s
    char **str_arr = malloc(sizeof(char *) * ll->size);

    // Now traverse the linked list, convert the int to a string and store the pointer in our array
    _node *sentinel = ll->head;
    _node *cur_node = sentinel->next;

    int i = 0;
    while (cur_node) {

        // Get the length of integer
        int num_places = __num_places(cur_node->item);
        // printf("%i places for %i\n", num_places, cur_node->item);

        // Declare a string buffer to hold this integer
        // Remember the +1 for the null terminator
        char *buf = malloc(sizeof(char) * (num_places + 1));

        // Use sprintf to read into this buffer
        sprintf(buf, "%i", cur_node->item);

        // Store the buffer in the str_list
        str_arr[i] = buf;

        // Advance
        cur_node = cur_node->next;
        i++;
    }

    return str_arr;
}


void linkedlist_print(LinkedList *ll)
{
    // Loop through each element in the ll and print it
    _node *sentinel = ll->head;
    _node *cur_node = sentinel->next;

    printf("[");
    while (cur_node) {

        printf("%i", cur_node->item);

        // Add a comma seperator if not the last element
        if (cur_node->next) {
            printf(", ");
        }
    }
    printf("]");
}


void linkedlist_prepend(LinkedList *ll, int item)
{
    linkedlist_insert(ll, 0, item);
}


void linkedlist_insert(LinkedList *ll, int idx, int item)
{
    // Guard against the idx being out of bounds
    if ((idx < 0) || (idx > ll->size)) {
        printf("Index out of bounds");
        return;
    }

    // Now in order ot insert we find the anchor (i.e. the node before our insert node)
    _node *anchor = NULL;
    if (idx == 0) {
        // Here we need to get the sentinel node
        anchor = ll->head;
    } else {
        // Rely on our getnode function
        anchor = linkedlist_getnode(ll, idx - 1);
    }

    // Create a new node and insert it after the anchor
    _node *new_node = linkedlist_new_node();
    new_node->item = item;
    new_node->next = anchor->next;
    anchor->next = new_node;

    // Update tail node in case of last insert
    if (idx == ll->size) {
        ll->tail = new_node;
    }

    // Increment the size
    ll->size += 1;
}


void linkedlist_append(LinkedList *ll, int item)
{
    _node *new_node = linkedlist_new_node();
    new_node->item = item;
    new_node->next = NULL;

    _node *last_node = ll->tail;
    last_node->next = new_node;
    ll->tail = new_node;

    ll->size += 1;
}


int linkedlist_pop(LinkedList *ll)
{
    return linkedlist_pop_idx(ll, ll->size - 1);
}


int linkedlist_pop_idx(LinkedList *ll, int idx)
{
    // Guard against the idx being out of bounds
    // We exit instead of making a return value because the return values
    // are all integers and so it can be easy to confuse a valid
    // and erroneous value
    if ((idx < 0) || (idx > ll->size) || (ll->size == 0)) {
        printf("Index out of bounds or list is empty");
        exit(1);
    }

    _node *anchor = NULL;
    if (idx == 0) {
        // Here we need to get the sentinel node
        anchor = ll->head;
    } else {
        // Rely on our getnode function
        anchor = linkedlist_getnode(ll, idx - 1);
    }

    _node *popped = anchor->next;
    anchor->next = popped->next;

    // Now update the tail pointer if we popped the last element
    if (idx == ll->size - 1) {
        ll->tail = anchor;
    }

    ll->size -= 1;

    // Now we need to deallocate the node
    int item = popped->item;
    free(popped);

    return item;
}


int linkedlist_front(LinkedList *ll)
{
    // Peek at the first element without popping it
    _node *sentinel = ll->head;
    _node *first = sentinel->next;

    return first->item;
}


int linkedlist_back(LinkedList *ll)
{
    // Peek at the last element without popping it
    _node *last = ll->tail;

    return last->item;
}


void linkedlist_del_elem(LinkedList *ll, int idx)
{
    // To delete an element we just pop it but don't return the value
    linkedlist_pop_idx(ll, idx);
}


void linkedlist_remove_elem(LinkedList *ll, int item)
{
    // Traverse the list and removes the first matching element
    int i = 0;
    _node *sentinel = ll->head;
    _node *cur_node = sentinel->next;

    while (cur_node) {
        if (cur_node->item == item) {
            linkedlist_del_elem(ll, i);
        }

        // Next item
        cur_node = cur_node->next;
        i++;
    }
}


int linkedlist_find(LinkedList *ll, int item)
{
    int i = 0;
    _node *sentinel = ll->head;
    _node *cur_node = sentinel->next;

    while (cur_node) {
        if (cur_node->item == item) {
            return i;
        }

        cur_node = cur_node->next;
        i++;
    }

    return -1;
}


bool linkedlist_isempty(LinkedList *ll)
{
    return ll->size == 0;
}


void linkedlist_destroy(LinkedList *ll)
{
    // Here we must de-allocate our entire linked list
    // We can do so recursively from the end of the list
    _node *sentinel = ll->head;
    dealloc_nodes_rec(sentinel);
    free(ll);
}


void dealloc_nodes_rec(_node *node)
{
    // Recursively deallocate all nodes along the chain of nodes
    // Base case
    if (!node->next) {
        free(node);
    } else {
        dealloc_nodes_rec(node->next);
    }
}
