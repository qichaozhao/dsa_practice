#ifndef BST_TYPES_H
#define BST_TYPES_H

// Define the struct for the Binary Node
typedef struct __binary_node
{
    struct __binary_node *left;
    struct __binary_node *right;
    struct __binary_node *parent;
    int value;
} binary_node;

// Define the struct for the Binary Tree
typedef struct __binary_search_tree
{
    struct __binary_node *root;
    int num_nodes;
    int height;
} bst;

#endif