#ifndef _BST_H
#define _BST_H

#define SUCCESS 1
#define TRUE    1
#define FALSE   0

typedef int data_t;
typedef int status_t;
typedef int Bool;
typedef unsigned int height_t;
typedef struct bst_node bst_node_t;
typedef struct bst  bst_t;

struct bst_node
{
    int data;
    struct bst_node* parent;
    struct bst_node* left;
    struct bst_node* rigth;
};

struct bst
{
    struct bst_node* root_node;
    size_t nr_elements;
};

bst_t* create_bst(void);
status_t insert_bst(bst_t* p_bst, data_t new_data);
status_t remove_bst(bst_t* p_bst, data_t r_data);
void preorder_traversal(bst_t* p_bst);
void inorder_traversal(bst_t* p_bst);
void postorder_traversal(bst_t* p_bst);
height_t height_bst(bst_t* p_bst);
status_t destory_bst(bst_t** pp_bst);
Bool search_bst(bst_t* p_bst, data_t s_data);

#endif  /*_BST_H*/
