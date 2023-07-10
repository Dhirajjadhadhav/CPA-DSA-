#ifndef _BST_H
#define _BST_H

#define SUCCESS 1
#define TRUE    1
#define FALSE   0
#define BST_EMPTY           2
#define BST_DATA_NOT_FOUND  3
#define BST_NO_PREDECESSOR  4
#define BST_NO_SUCCESSOR    5

typedef int data_t;
typedef int status_t;
typedef int Bool;
typedef long long int ssize_t;
typedef long long int height_t;
typedef struct bst_node bst_node_t;
typedef struct bst  bst_t;
typedef struct bst_list_node_t

struct bst_node
{
    data_t *data;
    struct bst_node *left;
    struct bst_node *right;
    struct bst_node *parent;
};

struct bst
{
    bst_node_t *root_node;
    ssize_t nr_element; 
};

bst_t* create_bst(void);
status_t insert_bst(bst_t* p_bst, data_t* new_data);
status_t remove_bst(bst_t* p_bst, data_t* r_data);
status_t remove_bst_expanded(bst_t* p_bst);
status_t destroy(bst_t** pp_bst);

void inorder_traversal(bst_t* p_bst);
void preorder_traversal(bst_t* p_bst);
void postorder_traversal(bst_t* p_bst);

void inorder_traversal_nrc(bst_t* p_bst);
void preorder_traversal_nrc(bst_t* p_bst);
void postorder_traversal_nrc(bst_t* p_bst);

status_t max_bst(bst_t* p_bst, data_t* p_max_data);
status_t min_bst(bst_t* p_bst, data_t* p_max_data);
height_t height_bst(bst_t* p_bst);
Bool search_bst(bst_t* p_bst, data_t search_data);

status_t inorder_predecessor(p_bst* p_bst, bst_node_t** pp_pred_node);
status_t inorder_successor(p_bst* p_bst, bst_node_t** pp_succ_node);

void transpalnt(bst_t* p_bst, bst_node_t* u, bst_node_t* v);
void inorder_traversal_nodelevel(bst_node_t* root_node);
void preorder_traversal_nodelevel(bst_node_t* root_node);
void postorder_traversal_nodelevel(bst_node_t* root_node);
void destroy_nodelevel(bst_node_t* root_node);
height_t height_bst_nodelevel(bst_node_t* root_node);
bst_node_t* max_bst_nodelevel(bst_node_t* root_node);
bst_node_t* min_bst_nodelevel(bst_node_t* root_node);

bst_node_t* search_node(bst_t* p_bst, data_t search_data);
bst_node_t* get_node(data_t new_data);
void* xcalloc(ssize_t nr_element, ssize_t size_per_element);

#endif /*_BST_H*/