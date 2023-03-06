#ifndef _BST_H
#define _BST_H

#define SUCCESS 1
#define TRUE    1
#define FALSE   0

typedef int data_t;
typedef int status_t;
typedef Bool;
typedef struct bst_node bst_node_t;
typedef struct bst  bst_t;

struct bst_node
{
    int data;
    struct bst_node* parent;
    struct bst_node* left;
    struct bst_node* right;
};

struct bst
{
    struct bst_node* root_node;
    size_t nr_element;
};

bst_t* create_bst(void);
status_t insert_bst(bst_t* p_bst, data_t new_data);
status_t remove_bst(bst_t* p_bst, data_t r_data);
status_t destroy_bst(bst_t** pp_bst);
Bool search_bst(bst_t* p_bst, data_t s_data);

bst_node_t* search_node(bst_t* p_bst, data_t s_data);

bst_node_t* get_bst_node(data_t new_data);
void* Xcalloc(size_t nr_element, size_t size_per_element);

#endif   /*_BST_H */