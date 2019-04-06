#include "linked_list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

// Function to run all tests sequentially
void test_all(void);

// Main tests
void test_new_list(void);
void test_append(void);
void test_getitem(void);
void test_getnode(void);
void test_tostr(void);
void test_prepend(void);
void test_insert(void);
void test_append(void);
void test_pop(void);
void test_pop_idx(void);
void test_front(void);
void test_back(void);
void test_del_elem(void);
void test_remove_elem(void);
void test_find(void);
void test_isempty(void);
void test_destroy(void);

// Helper function tests
void test_new_node(void);
void test_num_places(void);
void test_dealloc_nodes(void);


int main(void)
{
    test_all();
}


void test_all(void)
{
    printf("Test new list\n");
    test_new_list();

    printf("Test append\n");
    test_append();

    printf("Test getitem \n");
    test_getitem();

    printf("Test getnode\n");
    test_getnode();

    printf("Test tostr\n");
    test_tostr();

    printf("Test prepend\n");
    test_prepend();

    printf("Test insert\n");
    test_insert();

    printf("Test append\n");
    test_append();

    printf("Test pop\n");
    test_pop();

    printf("Test pop idx\n");
    test_pop_idx();

    printf("Test front\n");
    test_front();

    printf("Test back\n");
    test_back();

    printf("Test delete elem\n");
    test_del_elem();

    printf("Test remove elem\n");
    test_remove_elem();

    printf("Test find\n");
    test_find();

    printf("Test isempty\n");
    test_isempty();

    printf("Test destroy\n");
    test_destroy();
}


void test_new_list(void)
{
    LinkedList *ll = linkedlist_new();

    _node *head = ll->head;
    _node *tail = ll->tail;

    assert(head == tail);
    assert(ll->size == 0);
    assert(head->next == NULL);
}


void test_append(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 20);

    int ll0 = linkedlist_getitem(ll, 0);

    assert(ll->size == 1);
    assert(ll0 == 20);
}


void test_getitem(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 20);
    linkedlist_append(ll, 40);

    int ll1 = linkedlist_getitem(ll, 1);

    assert(ll1 == 40);
}


void test_getnode(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 20);
    linkedlist_append(ll, 40);

    _node *ll1 = linkedlist_getnode(ll, 1);

    assert(ll1->item == 40);
    assert(ll1->next == NULL);
}


void test_tostr(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 20);
    linkedlist_append(ll, 40);

    char **ll_str = linkedlist_tostr(ll);

    for (int i = 0; i < 2; i++) {
        printf("%s ", ll_str[i]);
    }
    printf("\n");

    assert(strcmp(ll_str[0], "20") == 0);
    assert(strcmp(ll_str[1], "40") == 0);
}


void test_prepend(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 20);
    linkedlist_append(ll, 40);
    linkedlist_prepend(ll, 10);

    int ll0 = linkedlist_getitem(ll, 0);
    int ll1 = linkedlist_getitem(ll, 1);
    int ll2 = linkedlist_getitem(ll, 2);

    assert(ll0 == 10);
    assert(ll1 == 20);
    assert(ll2 == 40);
}


void test_insert(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);

    linkedlist_insert(ll, 1, 1);
    linkedlist_insert(ll, 3, 3);

    for (int i = 0; i < 4; i++) {
        int item = linkedlist_getitem(ll, i);
        assert(item == i);
    }
}


void test_pop(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);
    linkedlist_insert(ll, 1, 1);
    linkedlist_insert(ll, 3, 3);

    int item = linkedlist_pop(ll);
    assert(item == 3);
    assert(ll->size == 3);

    item = linkedlist_pop(ll);
    assert(item == 2);
    assert(ll->size == 2);

    item = linkedlist_pop(ll);
    assert(item == 1);
    assert(ll->size == 1);

    item = linkedlist_pop(ll);
    assert(item == 0);
    assert(ll->size == 0);
}


void test_pop_idx(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);
    linkedlist_insert(ll, 1, 1);
    linkedlist_insert(ll, 3, 3);

    int item = linkedlist_pop_idx(ll, 3);
    assert(item == 3);
    assert(ll->size == 3);

    item = linkedlist_pop_idx(ll, 1);
    assert(item == 1);
    assert(ll->size == 2);

    item = linkedlist_pop_idx(ll, 1);
    assert(item == 2);
    assert(ll->size == 1);

    item = linkedlist_pop_idx(ll, 0);
    assert(item == 0);
    assert(ll->size == 0);
}


void test_front(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);

    int item = linkedlist_front(ll);

    assert(item == 0);
}


void test_back(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);

    int item = linkedlist_back(ll);

    assert(item == 2);
}


void test_del_elem(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);
    linkedlist_insert(ll, 1, 1);
    linkedlist_insert(ll, 3, 3);

    linkedlist_del_elem(ll, 2);

    int ll0 = linkedlist_getitem(ll, 0);
    int ll1 = linkedlist_getitem(ll, 1);
    int ll2 = linkedlist_getitem(ll, 2);

    assert(ll->size == 3);
    assert(ll0 == 0);
    assert(ll1 == 1);
    assert(ll2 == 3);
}


void test_remove_elem(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);
    linkedlist_insert(ll, 1, 1);
    linkedlist_insert(ll, 3, 3);

    linkedlist_remove_elem(ll, 2);

    int ll0 = linkedlist_getitem(ll, 0);
    int ll1 = linkedlist_getitem(ll, 1);
    int ll2 = linkedlist_getitem(ll, 2);

    assert(ll->size == 3);
    assert(ll0 == 0);
    assert(ll1 == 1);
    assert(ll2 == 3);
}


void test_find(void)
{
    LinkedList *ll = linkedlist_new();
    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);
    linkedlist_insert(ll, 1, 1);
    linkedlist_insert(ll, 3, 3);

    int idx = linkedlist_find(ll, 0);
    assert(idx == 0);

    idx = linkedlist_find(ll, 3);
    assert(idx == 3);
}


void test_isempty(void)
{
    LinkedList *ll = linkedlist_new();

    assert(linkedlist_isempty(ll));
}


void test_destroy(void)
{
    LinkedList *ll = linkedlist_new();

    linkedlist_append(ll, 0);
    linkedlist_append(ll, 2);
    linkedlist_insert(ll, 1, 1);
    linkedlist_insert(ll, 3, 3);

    linkedlist_destroy(ll);
}