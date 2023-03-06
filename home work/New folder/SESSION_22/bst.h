#ifndef _BST_H
#define _BST_H

#define SUCCESS     1
#define TRUE        1
#define FALSE       0

#define BST_DATA_NOT_FOUND  2
#define BST_EMPTY           3
#define BST_NO_SUCCESSOR    4
#define BST_NO_PREDECESSOR  5

typedef int data_t;
typedef int status_t;
typedef int Bool;
typedef unsigned int height_t;
typedef struct bst_node bst_node_t;
typedef struct bst  bst_t;

struct bst_node
{
    data_t data;
    struct bst_node* parent;
    struct bst_node* left;
    struct bst_node* right;
};

struct bst
{
    struct bst_node* root_node;
    size_t nr_element;
};

/*      Interface routines      */
bst_t* create_bst(void);
status_t insert_bst(bst_t* p_bst, data_t new_data);
status_t remove_bst(bst_t* p_bst, data_t r_data);
void preorder_traversal(bst_t* p_bst);
void inorder_traversal(bst_t* p_bst);
void postorder_traversal(bst_t* p_bst);
height_t height_bst(bst_t* p_bst);
status_t max_bst(bst_t* p_bst, data_t* p_max_element);
status_t min_bst(bst_t* p_bst, data_t* p_min_element);
status_t inorder_successor(bst_t* p_bst, data_t e_data, data_t* p_succ_data);
status_t inorder_predecessor(bst_t* p_bst, data_t e_data, data_t* p_pred_data);
Bool search_bst(bst_t* p_bst, data_t s_data);
status_t remove_bst_expanded(bst_t* p_bst, data_t r_data);
status_t destroy_bst(bst_t** pp_bst);

/* Auxillary routines */
void transplant(bst_t* p_bst, bst_node_t* u, bst_node_t* v);
void preorder_traversal_nodelevel(bst_node_t* root_node);
void inorder_traversal_nodelevel(bst_node_t* root_node);
void postorder_traversal_nodelevel(bst_node_t* root_node);
height_t height_bst_nodelevel(bst_node_t* root_node);
bst_node_t* max_bst_nodelevel(bst_node_t* root_node);
bst_node_t* min_bst_nodelevel(bst_node_t* root_node);
bst_node_t* inorder_successor_nodelevel(bst_node_t* p_node);
bst_node_t* inorder_predecessor_nodelevel(bst_node_t* p_node);
void destory_bst_nodelevel(bst_node_t* root_node);
bst_node_t* search_node(bst_node_t* root_node, data_t s_data);
bst_node_t* get_bst_node(data_t new_data);
void* xcalloc(size_t nr_element, size_t size_per_element);

#endif /* _BST_H */