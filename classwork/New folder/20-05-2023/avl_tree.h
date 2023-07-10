#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#define SUCCESS 1
#define TRUE    1
#define FALSE   0
#define AVL_EMPTY   2
#define AVL_DATA_NOT_FOUND  3
#define AVL_NO_PREDECESSOR  4
#define AVL_NO_SUCCESSOR    5

typedef int data_t;
typedef int status_t;
typedef int Bool;
typedef long long int ssize_t;
typedef long long int height_t;
typedef struct avl_node avl_node_t;
typedef struct avl_tree avl_tree_t;


struct avl_node
{
    data_t data;

    struct avl_node* left;
    struct avl_node* right;
    struct avl_node* parent;
};

struct avl_tree
{
    struct avl_node* root_node;
    ssize_t nr_element;
};


avl_tree_t* create_avl_tree(void);
status_t avl_insert(avl_tree_t* p_avl, data_t new_data);
status_t avl_remove(avl_tree* p_avl, data_t r_data);
status_t avl_destroy(avL_tree_t** pp_avl);

void inorder_traversal(avl_tree_t* p_avl);
void preorder_traversal(avl_tree_t* p_avl);
void postorder_traversal(avl_tree_t* p_avl);

status_t min(avl_tree_t* p_avl, data_t* p_max_data);
status_t max(avl_tree_t* p_avl, data_t* p_min_data);
Bool search_avl(avl_tree_t* p_avl, data_t e_data);
height_t heigth(avl_tree_t* p_avl);
status_t inorder_predecessor(avl_tree_t* p_avl, avl_node_t* p_pred_node);
status_t inorder_successor(avl_tree_t*p_avl, avl_node_t* p_succ_node);

void inorder_traversal_nodelevel(avl_node_t* root_node);
void preorder_traversal_nodelevel(avl_node_t* root_node);
void postorder_traversal_nodelevel(avl_node_t* root_node);

avl_node_t* min_nodelevel(avl_node_t* p_node);
avl_node_t* max_nodelevel(avl_node_t* p_node);
avl_node_t* inorder_predecessor_nodelevel(avl_node_t* p_node);
avl_node_t* inorder_successor_nodelevel(avl_node_t* p_node);
height_t  height_nodelevel(avl_node_t* p_node);

void left_rorate(avl_tree_t* p_avl,avl_node_t* x)
void right_rorate(avl_tree_t* p_avl, avl_nodo_t* x);
int get_balace(avl_node_t* z);

avl_node_t* seach_node(avl_tree_t* p_avl, data_t e_data);
avl_node_t* get_node(data_t new_data);
void* xcalloc(ssize_t nr_element, ssize_t size_per_element);
