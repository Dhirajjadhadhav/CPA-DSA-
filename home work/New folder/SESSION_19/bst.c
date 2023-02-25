#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

bst_t* create_bst(void)
{
    return ((bst_t*)Xcalloc(1, sizeof(bst_t)));
}

status_t insert_bst(bst_t* p_bst, data_t new_data)
{
    bst_node_t* p_new_node = NULL;
    bst_node_t* p_run= NULL;

    p_new_node  = get_bst_node(new_data);
    if(p_bst->root_node ==  NULL)
    {
        /*Inserting in empty BST */
        p_bst->root_node = p_new_node;
        p_bst->nr_element += 1;
        return (SUCCESS);
    }

    /* Insert in non-empty BST */
    p_run = p_bst->root_node;
    while(TRUE)
    {
        if(p_run->data<=new_data)
        {
            if(p_run->left == NULL)
                break;
            p_run = p_run->left;
        }
        else
        {
            if(p_run->right == NULL)
                break;
            p_run = p_run->right;
        }
    }

    if(p_run->data <= new_data)
        p_run->left = p_new_node;
    else
        p_run->right = p_new_node;
    p_new_node->parent = p_run;
    p_bst->nr_element += 1;

    return (SUCCESS);
}

bst_node_t* get_bst_node(data_t new_data)
{
    bst_node_t* p_node = NULL;
    
    p_node  = (bst_node_t*)Xcalloc(1, sizeof(bst_node_t));
    p_node->data = new_data;

    return (p_node);
}

void* Xcalloc(size_t nr_element, size_t size_per_element)
{
    void* p = NULL;
    p = calloc(nr_element, size_per_element);
    if(NULL == p)
    {
        fprintf(stderr, "calloc():out of memroy\n");
        exit(EXIT_FAILURE);
    }

    return (p);
}
