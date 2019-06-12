#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"

// Helper function for generating BSTs
bst *generate_bst(int num_nodes)
{
    int *arr = malloc(sizeof(int) * num_nodes);
    if (!arr)
    {
        printf("Unable to allocate array");
        exit(1);
    }

    for (int i=0; i<num_nodes; i++)
    {
        arr[i] = i;
    }

    bst *t = bst_new();
    bst_from_array(t, arr, num_nodes);

    return t;
}

// Tests for each of the separate bst functions defined here
void test_bst_create(void)
{
    printf("Testing bst creation...");
    bst *t = bst_new();

    assert(t->root == NULL);
    assert(t->num_nodes == 0);
    assert(t->height == 0);
    printf("OK!\n");
}

void test_bst_add_root(void)
{
    printf("Testing bst adding root...");
    bst *t = bst_new();
    binary_node *root = node_new(123, NULL, NULL, NULL);

    bst_add_root(t, root);

    assert(t->root);
    assert(t->root->value == 123);
    assert(t->height == 0);
    assert(t->num_nodes == 1);
    printf("OK!\n");
}

void test_bst_insert_empty(void)
{
    printf("Testing bst empty insertion...");
    bst *t = bst_new();

    bst_insert(t, 123);

    assert(t->root);
    assert(t->root->value == 123);
    assert(t->height == 0);
    assert(t->num_nodes == 1);
    printf("OK!\n");
}

void test_bst_insert_non_empty(void)
{
    printf("Testing bst non-empty insertion...");
    bst *t = generate_bst(3);

    bst_insert(t, 123);

    assert(t->num_nodes == 4);
    assert(t->root->value == 1);
    assert(t->root->left->value == 0);
    assert(t->root->right->value == 2);
    assert(t->root->right->right->value == 123);
    assert(t->height == 2);
    printf("OK!\n");
}

void test_bst_search_exists(void)
{
    printf("Testing bst search for existing value...");
    bst *t = generate_bst(7);
    int val = bst_search_val(t, 6, NULL);

    assert(val == 6);
    printf("OK!\n");
}

void test_bst_search_notexists(void)
{
    printf("Testing bst search for non-existent value...");
    bst *t = generate_bst(7);
    int val = bst_search_val(t, 60, NULL);

    assert (val == -1);
    printf("OK!\n");
}

void test_bst_num_nodes(void)
{
    printf("Checking bst get num nodes...");
    bst *t = generate_bst(7);
    int nodes = bst_get_num_nodes(t);

    assert (nodes == 7);
    printf("OK!\n");
}

void test_delete_tree(void)
{
    printf("Testing bst delete tree...");
    bst *t = generate_bst(4);
    bst_destroy(t, false);

    assert (t->root == NULL);
    assert (t->num_nodes == 0);
    assert (t->height == 0);
    printf("OK!\n");
}

void test_delete_node(void)
{
    printf("Testing bst delete node...\n");

    // Where node is leaf
    bst *t1 = generate_bst(4);
    bst_delete_node(t1, 3, NULL);

    assert (t1->root->right == NULL);
    assert (t1->num_nodes == 3);
    assert (t1->height == 2);

    printf("Node is leaf OK...\n");
    // Where node has 1 child
    bst *t2 = generate_bst(4);
    bst_delete_node(t2, 1, NULL);

    assert(t2->root->left->value == 0);
    assert(t2->root->left->left == NULL);
    assert(t2->num_nodes == 3);
    assert(t2->height == 1);

    printf("Node has 1 child OK...\n");

    // Where node has 2 children
    bst *t3 = generate_bst(4);
    bst_delete_node(t3, 2, NULL);

    assert (t3->root->value == 3);
    assert (t3->root->right == NULL);
    assert (t3->root->left->value == 1);
    assert (t3->root->left->left->value == 0);
    assert (t3->num_nodes == 3);
    assert (t3->height == 2);
    printf("OK!\n");
}

void test_get_min(void)
{
    printf("Testing bst get minimum...");
    bst *t = generate_bst(6);
    int t_min = bst_get_min(t, NULL);
    int t_r_min = bst_get_min(t, t->root->right);

    assert(t_min == 0);
    assert(t_r_min == 4);
    printf("OK!\n");
}

void test_get_max(void)
{
    printf("Testing bst get maximum...");
    bst *t = generate_bst(6);
    int t_max = bst_get_max(t, NULL);
    int t_l_max = bst_get_max(t, t->root->left);

    assert (t_max == 5);
    assert (t_l_max == 2);
    printf("OK!\n");
}

void test_verify_bst(void)
{
    printf("Testing bst verify...");
    bst *t = generate_bst(3);
    assert(bst_verify(t, NULL) == true);

    t->root->left->value = 5;
    assert(bst_verify(t, NULL) == false);
    printf("OK!\n");
}

void test_get_before(void)
{
    printf("Testing bst get before...");
    bst *t = generate_bst(6);
    int bf = bst_get_before(t, 3);

    assert (bf == 2);
    printf("OK!\n");
}

void test_get_after(void)
{
    printf("Testing bst get after...");
    bst *t = generate_bst(6);
    int af = bst_get_after(t, 3);

    assert (af == 4);
    printf("OK!\n");
}

void test_bst_iter_inorder(void)
{
    printf("Testing bst inorder iteration...");
    bst *t = generate_bst(6);
    darray *arr = bst_traverse(t, 0);

    for (int i = 0; i < 6; i++)
    {
        assert (arr->arr[i] == i);
    }
    printf("OK\n");
}

void test_bst_iter_preorder(void)
{
    printf("Testing bst pre-order iteration...");
    bst *t = generate_bst(6);
    darray *arr = bst_traverse(t, 1);
    int ref[6] = {3, 1, 0, 2, 5, 4};

    for (int i = 0; i < 6; i++)
    {
        assert (arr->arr[i] == ref[i]);
    }
    printf("OK\n");
}

void test_bst_iter_postorder(void)
{
    printf("Testing bst post-order iteration...");
    bst *t = generate_bst(6);
    darray *arr = bst_traverse(t, 2);
    int ref[6] = {0, 2, 1, 4, 5, 3};

    for (int i = 0; i < 6; i++)
    {
        assert (arr->arr[i] == ref[i]);
    }
    printf("OK\n");
}

void test_bst_iter_bfs(void)
{
    printf("Testing bst bfs iteration...");
    bst *t = generate_bst(6);
    darray *arr = bst_traverse(t, 3);
    int ref[6] = {3, 1, 5, 0, 2, 4};

    for (int i = 0; i < 6; i++)
    {
        assert (arr->arr[i] == ref[i]);
    }
    printf("OK\n");
}

void test_bst_get_height(void)
{
    printf("Testing bst get height...");
    bst *t = generate_bst(6);

    assert (bst_get_height(t, t->root) == 2);
    printf("OK\n");
}

void test_bst_balance(void)
{
    printf("Testing bst balance...");
    bst *t = generate_bst(3);
    t->root->left->value = 2;
    t->root->right->value = 0;

    assert (bst_verify(t, NULL) == false);

    bst_balance(t);

    assert (t->root->value == 1);
    assert (t->root->left->value == 0);
    assert (t->root->right->value == 2);
    assert (bst_verify(t, NULL) == true);
    printf("OK\n");
}

void test_bst_from_array(void)
{
    printf("Testing bst instantion from array...");
    bst *t = bst_new();
    int *arr = malloc(sizeof(int) * 3);
    if (!arr)
    {
        printf("Cannot allocate array");
        exit(1);
    }

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    
    bst_from_array(t, arr, 3);

    assert (t->root->value == 1);
    assert (t->root->left->value == 0);
    assert (t->root->right->value == 2);
    printf("OK\n");
}

void test_bst_print(void)
{
    printf("Testing bst_print of array with 3 nodes...\n");
    bst *t1 = generate_bst(3);
    bst_print(t1);

    printf("Testing bst_print of array with 4 nodes...\n");
    bst *t2 = generate_bst(4);
    bst_print(t2);

    printf("Testing bst_print of array with 8 nodes...\n");
    bst *t3 = generate_bst(8);
    bst_print(t3);
}

int main(void)
{
    test_bst_create();
    test_bst_add_root();
    test_bst_insert_empty();
    test_bst_insert_non_empty();
    test_bst_from_array();
    test_bst_search_exists();
    test_bst_search_notexists();
    test_bst_num_nodes();
    test_delete_tree();
    test_delete_node();
    test_get_min();
    test_get_max();
    test_verify_bst();
    test_get_before();
    test_get_after();
    test_bst_iter_inorder();
    test_bst_iter_preorder();
    test_bst_iter_postorder();
    test_bst_iter_bfs();
    test_bst_get_height();
    test_bst_balance();
    test_bst_print();
}