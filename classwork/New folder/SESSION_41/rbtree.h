#ifndef _RB_TREE_H 
#define _RB_TREE_H 

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1 
#define TRUE 1 
#define FALSE 0 
#define RB_DATA_NOT_FOUND 2 
#define RB_TREE_EMPTY 3 
#define RB_NO_PREDECESSOR 4 
#define RB_NO_SUCCESSOR 5 

typedef int data_t; 
typedef int status_t; 
typedef long long int ssize_t; 
typedef enum color color_t; 

typedef struct rb_node rb_node_t; 
typedef struct rb_tree rb_tree_t; 

enum color 
{
    RED=1, 
    BLACK
}; 

struct rb_node
{
    data_t data; 
    color_t color; 
    struct rb_node* left; 
    struct rb_node* right; 
    struct rb_node* parent; 
}; 

struct rb_tree
{
    rb_node_t* root_node; 
    rb_node_t* nil; 
    ssize_t nr_elements; 
}; 

rb_tree_t* create_rb_tree(void)
{
    rb_tree_t* p_rb_tree = NULL;
    p_rb_tree = (rb_tree_t*)xcalloc(1, sizeof(rb_tree_t));
    
    p_rb_tree->nil = (rb_node_t*)xcalloc(1, sizeof(rb_node_t));
    
    p_rb_tree->root_node = p_rb_tree->nil;
    p_rb_tree->nr_elements = 0;

    return (p_rb_tree);
}


status_t insert(rb_tree_t* p_rb_tree, data_t new_data); 
status_t remove(rb_tree_t* p_rb_tree, data_t r_data); 
void inorder(rb_tree_t* p_rb_tree); 
status_t destroy(rb_tree_t** pp_rb_tree); 

void preorder(rb_tree_t* p_rb_tree); 
void postorder(rb_tree_t* p_rb_tree); 
status_t find(rb_tree_t* p_rb_tree); 
ssize_t height(rb_tree_t* p_rb_tree); 
status_t max_in_tree(rb_tree_t* p_rb_tree); 
status_t max_in_tree(rb_tree_t* p_rb_tree); 
status_t inorder_predecessor(rb_tree_t* p_rb_tree, data_t* p_pred_data); 
status_t inorder_successor(rb_tree_t* p_rb_tree, data_t* p_succ_data); 

/* Auxillary routines */
/* 
    void rb_insert_fixup(rb_node_t* p_node); 
    void rb_remove_fixup(rb_node_t* p_node); 
    void left_rotate(rb_node_t* x);
    void right_rotate(rb_node_t* x); 
*/ 
void preorder_nodelevel(rb_node_t* root_node); 
void inorder_nodelevel(rb_node_t* root_node); 
void postorder_nodelevel(rb_node_t* root_node); 
ssize_t height_nodelevel(rb_node_t* root_node); 
rb_node_t* inorder_predecessor_nodelevel(rb_node_t* p_node); 
rb_node_t* inorder_successor_nodelevel(rb_node_t* p_node); 
rb_node_t* search_node(rb_tree_t* p_rb_tree, data_t search_data); 
rb_node_t* get_node(rb_tree_t* p_rb_tree, data_t new_data)
{
    rb_node_t* p_new_node = NULL;
    
    p_new_node = (rb_node_t*)xcalloc(1, sizeof(rb_node_t));
    p_new_node->data = new_data;
    p_new_node->color  = RED;
    p_new_node->left = p_rb_tree->nil;
    p_new_node->right = p_rb_tree->nil;
    p_new_node->parent = p_rb_tree->nil;

    return (p_new_node);
}
void* xcalloc(size_t number_of_elements, size_t size_per_element)
{
    void* p = NULL;
    p = calloc(number_of_elements, size_per_element);
    if(p == NULL)
    {
        fprintf(stderr, "fatal:calloc(): out of memory\n");
        exit(EXIT_FAILURE);
    }

    return (p);
}

#endif /* _RB_TREE_H */