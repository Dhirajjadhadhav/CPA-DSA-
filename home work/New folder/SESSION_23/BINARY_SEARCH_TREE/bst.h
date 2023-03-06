#ifndef _BST_H
#define _BST_H

#define SUCCCESS            1
#define TRUE                1
#define FALSE               0

#define BST_EMPTY           2
#define BST_DATA_NOT_FOUND  3
#define BST_NO_SUCCESSOR    4
#define BST_NO_PREDECESSOR  5

#define LIST_EMPTY          6
#define  STACK_EMPTY        LIST_EMPTY


struct bst_node;
struct bst;
struct bstptr_node;
enum color;


typedef int data_t;
typedef int status_t;
typedef int Bool;

typedef struct bst_node bst_node_t;
typedef struct bst  bst_t;

typedef struct bstptr_node bstptr_node_t;
typedef bstptr_node_t list_t;
typedef list_t stack_t;


typedef enum color color_t;

struct bst_node
{
    data_t data;
    struct bst_node* left;
    struct bst_node* right;
    struct bst_node* parent;
};

struct bst
{
    bst_node_t* p_root_node;
    size_t nr_element;
};

enum color
{
    WHITE,
    GREY,
    BLACK
};

struct bstptr_node
{
    struct bst_node *p_bst_node;
    color_t color;
    struct bstptr_node* next;
    struct bstptr_node* prev;
};

    /* Interface */
bst_t* create_bst(void);
status_t insert_bst(bst_t* p_bst, data_t new_data);
Bool search_bst(bst_t* p_bst, data_t s_data);
void inorder_r(bst_t* p_bst);
void preorder_r(bst_t* p_bst);
void postorder_r(bst_t* p_bst);
void inorder_nrc(bst_t* p_bst);
void preorder_nrc(bst_t* p_bst);
void postorder_nrc(bst_t* p_bst);
status_t maximum_bst(bst_t* p_bst, data_t* p_max_data);
status_t minimum_bst(bst_t* p_bst, data_t* p_min_data);
status_t inorder_successor(bst_t* p_bst, data_t e_data, data_t* p_succ_data);
status_t inorder_predecessor(bst_t* p_bst, data_t e_data, data_t* p_pred_data);
status_t remove_bst(bst_t* p_bst, data_t r_data);
status_t destroy_bst(bst_t** pp_bst);
status_t remove_bst_extended(bst_t* p_bst, data_t r_data);

/* BST Auxilarry */
bst_node_t* search_bst_node(bst_node_t* p_root_node, data_t search_data);
bst_node_t* get_bst_node(data_t new_data);
bst_node_t*  inorder_successor_nodelevel(bst_node_t* p_bst_node);
bst_node_t* inorder_predecessor_nodelevel(bst_node_t* p_bst_node);
void __inorder_r(bst_node_t* p_root_node);
void __preorder_r(bst_node_t* p_root_ndoe);
void __postorder_r(bst_node_t* p_root_node);
void __destory_bst_r(bst_node_t* p_root_node);
void transplant_bst(bst_t* p_bst, bst_node_t* u,  bst_node_t* v);

/*BST auxillary - Stack Interface */
stack_t* create_bstptr_stack();
status_t push_bstptr(stack_t* p_stack, bst_node_t* p_bst_node);
status_t top_bstptr(stack_t* p_stack, bst_node_t** pp_bst_node);
status_t pop_bstptr(stack_t* p_stack, bst_node_t** pp_bst_node);
status_t set_bstptr_top_color(stack_t* p_stack, color_t new_color);
status_t get_bstptr_top_color(stack_t* p_stack, color_t* p_top_color);
Bool is_bstptr_stack_empty(stack_t* p_stack);
status_t destory_bstptr_stack(stack_t** pp_stack);

/* BST auxillary - List interface*/

list_t * create_bstptr_list(void);
status_t insert_bstptr_end(list_t* p_list, bst_node_t* p_bst_node);
status_t examine_bstptr_end(list_t* p_list, bst_node_t** p_bst_node);
status_t examine_and_delete_bstptr_end(list_t* p_list, bst_node_t** pp_bst_node);
Bool is_bstptr_list_empty(list_t* p_list);
status_t destroy_bstptr_list(list_t** pp_list);

/* BST Auxillary -list interface - List auxillary */
void generic_bstptr_insert(bstptr_node_t* p_beg, bstptr_node_t* p_mid, bstptr_node_t* p_end);
void generic_bstptr_delete(bstptr_node_t* p_bstptr_node);
bstptr_node_t* search_bstptr_node(list_t* p_list, bst_node_t* p_bst_node);
bstptr_node_t* get_bstptr_node(bst_node_t* p_bst_node);

/* generic auxillary routines */
void* Xcalloc(size_t n, size_t s);

#endif; /* _BST_H */