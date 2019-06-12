#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "circarr_queue.h"

/*
* Start with our binary node functions
*/

binary_node *node_new(int value,
                      binary_node *left, binary_node *right, binary_node *parent)
{
    binary_node *new_node = malloc(sizeof(binary_node));
    if (!new_node)
    {
        printf("Unable to allocate new node, exiting...");
        exit(1);
    }

    new_node->left = left;
    new_node->right = right;
    new_node->parent = parent;
    new_node->value = value;

    return new_node;
}

void node_destroy(binary_node *node)
{
    free(node);
}

bool node_has_sibling(binary_node *node)
{
    if (!node_get_sibling(node))
    {
        return true;
    }

    return false;
}

binary_node *node_get_sibling(binary_node *node)
{
    if (node->parent->left == node)
    {
        return node->parent->right;
    }
    else if (node->parent->right == node)
    {
        return node->parent->left;
    }
    else
    {
        return NULL;
    }
}

bool node_is_leaf(binary_node *node)
{
    return (!node->left && !node->right);
}

bool node_is_equal(binary_node *node, binary_node *other_node)
{
    return (node->value == other_node->value);
}

/*
* Now comes all of our tree functions
*/

bst *bst_new(void)
{
    bst *tree = malloc(sizeof(bst));
    if (!tree)
    {
        printf("Unable to allocate new tree!");
        exit(1);
    }

    tree->root = NULL;
    tree->num_nodes = 0;
    tree->height = 0;

    return tree;
}

void bst_add_root(bst *tree, binary_node *node)
{
    if (tree->root)
    {
        printf("Unable to add new root, one already exists!");
    }
    else
    {
        tree->root = node;
        tree->num_nodes += 1;
    }
}

void bst_insert(bst *tree, int value)
{

    binary_node *new_node = node_new(value, NULL, NULL, NULL);

    // If we have an empty tree, we just add the root!
    if (!tree->root)
    {
        bst_add_root(tree, new_node);
        return;
    }
    // Else we use a recursive helper to add the node in the right place
    else
    {
        __bst_insert_helper(new_node, tree->root);
        tree->num_nodes += 1;
        tree->height = bst_get_height(tree, tree->root);
        return;
    }
}

void __bst_insert_helper(binary_node *new_node, binary_node *cur_node)
{
    // Case 1: Item already exist:
    if (new_node->value == cur_node->value)
    {
        printf("Not inserting new node, value already exists...");
    }

    // Case 2: Perform the insertion here as the current node is a leaf node
    else if (node_is_leaf(cur_node))
    {
        new_node->parent = cur_node;

        if (new_node->value < cur_node->value)
        {
            cur_node->left = new_node;
        }
        else if (new_node->value > cur_node->value)
        {
            cur_node->right = new_node;
        }
        else
        {
            printf("Should not reach this code area! Something went wrong!");
            exit(1);
        }
    }

    // Case 3: Current node has free LEFT child and new node value is less
    else if (!cur_node->left && new_node->value < cur_node->value)
    {
        cur_node->left = new_node;
    }

    // Case 4: Current node has free RIGHT child and new node value is more
    else if (!cur_node->right && new_node->value > cur_node->value)
    {
        cur_node->right = new_node;
    }

    // Case 5: We need to recurse
    else
    {
        if (new_node->value < cur_node->value)
        {
            __bst_insert_helper(new_node, cur_node->left);
        }
        else if (new_node->value > cur_node->value)
        {
            __bst_insert_helper(new_node, cur_node->right);
        }
        else
        {
            printf("Something went badly wrong!");
            exit(1);
        }
    }
}

void bst_from_array(bst *tree, int *arr, int arr_len)
{
    if (tree->root)
    {
        printf("Cannot build a tree as the root already exists");
    }

    if (arr_len == 0)
    {
        printf("Must take an array of at least 1 element");
    }

    // Sort the array
    qsort(arr, arr_len, sizeof(int), intcmp);

    // Extract the pivot in the middle of the array
    int m = arr_len / 2;
    int v = arr[m];
    binary_node *root = node_new(v, NULL, NULL, NULL);
    bst_add_root(tree, root);

    // Now prepare the array slices that we will iterate over
    int left_arr_len = m;
    int *left_arr = malloc(sizeof(int) * left_arr_len);
    int right_arr_len = arr_len - m - 1;
    int *right_arr = malloc(sizeof(int) * (right_arr_len));
    if (!left_arr)
    {
        printf("Unable to allocate left_arr");
        exit(1);
    }

    if (!right_arr)
    {
        printf("Unable to allocate right_arr");
        exit(1);
    }

    for (int i = 0; i < left_arr_len; i++)
    {
        left_arr[i] = arr[i];
    }

    for (int i = 0; i < right_arr_len; i++)
    {
        right_arr[i] = arr[i + (m + 1)];
    }

    // Now we can recurse
    __bst_from_array_helper(left_arr, left_arr_len, root, 0);
    __bst_from_array_helper(right_arr, right_arr_len, root, 1);

    // Now set the final parameters
    tree->num_nodes = arr_len;
    tree->height = bst_get_height(tree, tree->root);
}

void __bst_from_array_helper(int *arr, int arr_len, binary_node *parent, int position)
{
    // Base Case
    if (arr_len == 0)
    {
        return;
    }
    else
    {
        // Extract the pivot in the middle of the array
        int m = arr_len / 2;
        int v = arr[m];

        // Now we can set the node
        binary_node *new_node = node_new(v, NULL, NULL, parent);
        // Child is LEFT of parent:
        if (position == 0)
        {
            parent->left = new_node;
        }
        // Child is RIGHT of parent
        else if (position == 1)
        {
            parent->right = new_node;
        }
        else
        {
            printf("This is the shadowlands, Simba should never come here.");
            exit(1);
        }

        // Now prepare the array slices that we will iterate over
        int left_arr_len = m;
        int *left_arr = malloc(sizeof(int) * left_arr_len);
        int right_arr_len = arr_len - m - 1;
        int *right_arr = malloc(sizeof(int) * (right_arr_len));
        if (!left_arr)
        {
            printf("Unable to allocate left_arr");
            exit(1);
        }

        if (!right_arr)
        {
            printf("Unable to allocate right_arr");
            exit(1);
        }

        for (int i = 0; i < left_arr_len; i++)
        {
            left_arr[i] = arr[i];
        }

        for (int i = 0; i < right_arr_len; i++)
        {
            right_arr[i] = arr[i + (m + 1)];
        }

        // Now we can recurse
        __bst_from_array_helper(left_arr, left_arr_len, new_node, 0);
        __bst_from_array_helper(right_arr, right_arr_len, new_node, 1);
    }
}

// Search
int bst_search_val(bst *tree, int item, binary_node *start_node)
{
    binary_node *node = bst_search_node(tree, item, start_node);
    if (node)
    {
        return bst_search_node(tree, item, start_node)->value;
    }
    else
    {
        return -1;
    }    
}

binary_node *bst_search_node(bst *tree, int item, binary_node *start_node)
{
    if (!start_node)
    {
        start_node = tree->root;
    }

    // Base Case - We have found it:
    if (start_node->value == item)
    {
        return start_node;
    }

    // Base Case - We exhausted the search:
    if (!start_node || node_is_leaf(start_node))
    {
        return NULL;
    }

    // Recursive Case
    if (item < start_node->value)
    {
        return bst_search_node(tree, item, start_node->left);
    }
    else if (item > start_node->value)
    {
        return bst_search_node(tree, item, start_node->right);
    }
    else
    {
        printf("We should never get here!");
        exit(1);
    }
}

int bst_get_min(bst *tree, binary_node *start_node)
{
    binary_node *node = bst_get_min_node(tree, start_node);
    if (node)
    {
        return bst_get_min_node(tree, start_node)->value;
    }
    else
    {
        return -1;
    }
    
}

binary_node *bst_get_min_node(bst *tree, binary_node *start_node)
{
    if (!start_node)
    {
        start_node = tree->root;
    }

    while (start_node->left)
    {
        start_node = start_node->left;
    }

    return start_node;
}

int bst_get_max(bst *tree, binary_node *start_node)
{
    binary_node *node = bst_get_max_node(tree, start_node);
    if (node)
    {
        return bst_get_max_node(tree, start_node)->value;
    }
    else
    {
        return -1;
    }
    
}

binary_node *bst_get_max_node(bst *tree, binary_node *start_node)
{
    if (!start_node)
    {
        start_node = tree->root;
    }

    while (start_node->right)
    {
        start_node = start_node->right;
    }

    return start_node;
}

int bst_get_before(bst *tree, int item)
{
    binary_node *node = bst_get_before_node(tree, item);
    if (node)
    {
        return bst_get_before_node(tree, item)->value;
    }
    else
    {
        return -1;
    }
    
}

binary_node *bst_get_before_node(bst *tree, int item)
{
    binary_node *node = bst_search_node(tree, item, tree->root);

    if (node && node->left)
    {
        return bst_get_max_node(tree, node->left);
    }
    else
    {
        return NULL;
    }
}

int bst_get_after(bst *tree, int item)
{
    binary_node *node = bst_get_after_node(tree, item);
    if (node)
    {
        return bst_get_after_node(tree, item)->value;
    }
    else
    {
        return -1;
    }
    
}

binary_node *bst_get_after_node(bst *tree, int item)
{
    binary_node *node = bst_search_node(tree, item, tree->root);

    if (node && node->right)
    {
        return bst_get_min_node(tree, node->right);
    }
    else
    {
        return NULL;
    }
    
}

// Compute key stats
int bst_get_num_nodes(bst *tree)
{
    // Perform an inorder traversal to get the array
    darray *arr = bst_traverse(tree, 0);
    return arr->n;
}

int bst_get_height(bst *tree, binary_node *start_node)
{
    // Base Case
    if (!start_node || node_is_leaf(start_node))
    {
        return 0;
    }

    // Recursive Case
    else
    {
        int left_height = bst_get_height(tree, start_node->left);
        int right_height = bst_get_height(tree, start_node->right);
        if (left_height < right_height)
        {
            return 1 + right_height;
        }
        else
        {
            return 1 + left_height;
        }
    }
}

// Traversal functions
darray *bst_traverse(bst *tree, int type)
{
    darray *res = darray_new(4);

    // Guard against empty trees
    if (!tree->root)
    {
        return res;
    }

    // Use the type of traversal to switch into the right function
    switch (type)
    {
    // Inorder
    case 0:
        __inorder_rec(tree->root, res);
        break;

    // Preorder
    case 1:
        __preorder_rec(tree->root, res);
        break;

    // Postorder
    case 2:
        __postorder_rec(tree->root, res);
        break;

    // BFS
    case 3:
        __bfs_helper(tree, res);
        break;
    }

    return res;
}

void __inorder_rec(binary_node *node, darray *arr)
{
    if (node->left)
    {
        __inorder_rec(node->left, arr);
    }

    darray_append(arr, node->value);

    if (node->right)
    {
        __inorder_rec(node->right, arr);
    }
}

void __preorder_rec(binary_node *node, darray *arr)
{
    darray_append(arr, node->value);

    if (node->left)
    {
        __preorder_rec(node->left, arr);
    }

    if (node->right)
    {
        __preorder_rec(node->right, arr);
    }
}

void __postorder_rec(binary_node *node, darray *arr)
{
    if (node->left)
    {
        __postorder_rec(node->left, arr);
    }

    if (node->right)
    {
        __postorder_rec(node->right, arr);
    }

    darray_append(arr, node->value);
}

void __bfs_helper(bst *tree, darray *arr)
{
    // This could be a pain to implement
    // We need a queue that stores pointer to nodes
    // This needs to be implemented separately before we can do this
    Queue *queue = queue_new(tree->num_nodes);

    queue_enqueue(queue, tree->root);
    while (!queue_isempty(queue))
    {
        binary_node *node = queue_dequeue(queue);

        if (node)
        {
            darray_append(arr, node->value);
            queue_enqueue(queue, node->left);
            queue_enqueue(queue, node->right);
        }
    }
}

// Deletion
void bst_destroy(bst *tree, bool free_mem)
{
    __bst_destroy_node(tree->root);

    if (free_mem)
    {
        free(tree);
    }
    else
    {
        tree->num_nodes = 0;
        tree->height = 0;
        tree->root = NULL;
    }
    
}

void __bst_destroy_node(binary_node *node)
{
    if (!node)
    {
        return;
    }

    __bst_destroy_node(node->left);
    __bst_destroy_node(node->right);

    free(node);
}

void bst_delete_node(bst *tree, int item, binary_node *start_node)
{
    if (!start_node)
    {
        start_node = tree->root;
    }

    binary_node *to_del = bst_search_node(tree, item, start_node);
    if (!to_del)
    {
        printf("Trying to delete a value that does not exist");
    }

    // 3 possibilities for deletion
    // 1. Node is leaf (just delete)
    if (node_is_leaf(to_del))
    {
        if (to_del->parent->left == to_del)
        {
            to_del->parent->left = NULL;
        }
        else if (to_del->parent->right == to_del)
        {
            to_del->parent->right = NULL;
        }
        else
        {
            printf("Unknown error!");
        }

        tree->num_nodes -= 1;
        tree->height = bst_get_height(tree, tree->root);
        free(to_del);
    }

    // 2. Node has one child (left empty)
    // Replace node value with child value and delete the child
    else if (to_del->left == NULL)
    {
        to_del->value = to_del->right->value;

        free(to_del->right);
        to_del->right = NULL;

        tree->num_nodes -= 1;
        tree->height = bst_get_height(tree, tree->root);
    }

    // 2. Node has one child (right empty)
    // Replace node value with child value and delete the child
    else if (to_del->right == NULL)
    {
        to_del->value = to_del->left->value;

        free(to_del->left);
        to_del->left = NULL;
        
        tree->num_nodes -= 1;
        tree->height = bst_get_height(tree, tree->root);
    }

    // 3. Node is a full node
    // Find the inorder successor and delete that
    // Inorder successor is the min value of the right branch
    else
    {
        binary_node *succ = bst_get_min_node(tree, to_del->right);
        to_del->value = succ->value;
        bst_delete_node(tree, succ->value, succ);
    }
}

// Misc
bool bst_verify(bst *tree, binary_node *start_node)
{
    // Guard against empty trees
    if (!tree->root)
    {
        return false;
    }

    // Guard against empty start_nodes
    if (!start_node)
    {
        start_node = tree->root;
    }

    // Now go through each of the cases
    if (node_is_leaf(start_node))
    {
        return true;
    }
    else if (!start_node->right)
    {
        return start_node->left->value < start_node->value 
                && bst_verify(tree, start_node->left);
    }
    else if (!start_node->left)
    {
        return start_node->right->value > start_node->value
                && bst_verify(tree, start_node->right);
    }
    else
    {
        return start_node->left->value < start_node->value
                && bst_verify(tree, start_node->left)
                && start_node->right->value > start_node->value
                && bst_verify(tree, start_node->right);
    }
}

void bst_balance(bst *tree)
{
    // Inorder traversal which leaves us with a sorted array
    darray *arr = bst_traverse(tree, 0);

    // Now we delete the tree except for the containing struct
    bst_destroy(tree, false);

    // Now we create the new tree
    // Now we grab raw array from our dynamic array and the length too
    bst_from_array(tree, arr->arr, arr->n);
}

void bst_print(bst *tree)
{
    // Get the overall width and height of our canvas
    int w = 0;
    int h = 0;

    w = pow(2, tree->height) * 2 + 1;
    h = (tree->height + 1) * 2 + 1;

    // Plot arrays
    int plt_idx = 0;
    int *plt_x = malloc(sizeof(int) * tree->num_nodes);
    int *plt_y = malloc(sizeof(int) * tree->num_nodes);
    int *plt_val = malloc(sizeof(int) * tree->num_nodes);

    // We do a depth first traversal over the tree to formulate our plot indices
    Queue *queue = queue_new(tree->num_nodes * 2);
    queue_enqueue(queue, tree->root);
    Queue *new_queue = NULL;
    int lvl = 0;
    int idx = 0;
    int x = 0;
    int y = 0;

    while (lvl >= 0)
    {
        // In order to index whitespace properly we should construct a new queue for each level
        new_queue = queue_new(tree->num_nodes * 2);
        idx = 0;

        // Loop through the current queue and append to the plot array
        while (queue->n > 0)
        {
            // Get the next node off the queue
            binary_node *nd = queue_dequeue(queue);

            if (nd)
            {
                // Calculate the x,y co-ordinates for it
                x = w / (pow(2, lvl) + 1) * (1 + idx);
                y = lvl * 2;

                // Append to plot arrays
                printf("Appending: (%i, %i -> %i)\n", x, y, nd->value);
                plt_x[plt_idx] = x;
                plt_y[plt_idx] = y;
                plt_val[plt_idx] = nd->value;
                plt_idx++;
                idx++;

                // Grow out the new queue
                if (nd->left)
                {
                    queue_enqueue(new_queue, nd->left);
                }

                if (nd->right)
                {
                    queue_enqueue(new_queue, nd->right);
                }
                printf("Num in new queue: %i\n", new_queue->n);
            }
        }

        // Now we setup the queue for the next level
        queue_destroy(queue);
        queue = new_queue;
        if (queue->n > 0)
        {
            lvl++;
        }
        else
        {
            lvl = -1;
        }
        
    }

    // Now we read back through our plot indices and plot
    // Reset the index we use to keep track to zero, and go ahead
    plt_idx = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {

            if (plt_y[plt_idx] == i && plt_x[plt_idx] == j)
            {
                printf("%i", plt_val[plt_idx]);
                plt_idx++;
            }
            else
            {
                printf(" ");
            }
        }

        printf("\n");
    }
}

/*
* Misc
*/ 

int intcmp (const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
} // Needed for using C's "qsort" function