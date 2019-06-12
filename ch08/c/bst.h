#ifndef BST_H
#define BST_H

#include "vector.h"
#include "bst_types.h"

// Functions that we use in the binary node:
binary_node *node_new(int value,
                      binary_node *left, binary_node *right, binary_node *parent);
void node_destroy(binary_node *node);
bool node_has_sibling(binary_node *node);
binary_node *node_get_sibling(binary_node *node);
bool node_is_leaf(binary_node *node);
bool node_is_equal(binary_node *node, binary_node *other_node);

// Functions that we use in the binary search tree:
// Creation & Insertion
bst *bst_new(void);
void bst_add_root(bst *tree, binary_node *node);
void bst_insert(bst *tree, int value);
void __bst_insert_helper(binary_node *new_node, binary_node *cur_node);
void bst_from_array(bst *tree, int *arr, int arr_len);
void __bst_from_array_helper(int *arr, int arr_len, binary_node *parent, int position);

// Search
int bst_search_val(bst *tree, int item, binary_node *start_node);
binary_node *bst_search_node(bst *tree, int item, binary_node *start_node);

int bst_get_min(bst *tree, binary_node *start_node);
binary_node *bst_get_min_node(bst *tree, binary_node *start_node);
int bst_get_max(bst *tree, binary_node *start_node);
binary_node *bst_get_max_node(bst *tree, binary_node *start_node);

int bst_get_before(bst *tree, int item);
binary_node *bst_get_before_node(bst *tree, int item);
int bst_get_after(bst *tree, int item);
binary_node *bst_get_after_node(bst *tree, int item);

// Compute key stats
int bst_get_num_nodes(bst *tree);
int bst_get_height(bst *tree, binary_node *start_node);

// Traversal functions
darray *bst_traverse(bst *tree, int type);
void __inorder_rec(binary_node *node, darray *arr);
void __postorder_rec(binary_node *node, darray *arr);
void __preorder_rec(binary_node *node, darray *arr);
void __bfs_helper(bst *tree, darray *arr);

// Deletion
void bst_destroy(bst *tree, bool free_mem);
void __bst_destroy_node(binary_node *node);
void bst_delete_node(bst *tree, int item, binary_node *start_node);

// Misc
bool bst_verify(bst *tree, binary_node *start_node);
void bst_balance(bst *tree);
void bst_print(bst *tree);
int intcmp (const void * a, const void * b);
#endif