#include <stdio.h>  
#include <stdlib.h> 
#include "bst.h"


bst_t* create_bst(void)
{
    bst_t* p_bst = NULL;

    p_bst = xcalloc(1, sizeof(p_bst));
    p_bst->root_node = NULL;
    p_bst->nr_element  = 0;
    
    return (p_bst);
}

status_t insert_bst(bst_t* p_bst, data_t* new_data)
{
    bst_node_t* p_new_node = NULL;
    bst_node_t* p_run = NULL;

    p_new_node = get_node(new_data);

    /*Insert in empty BST*/
    if(NULL == p_bst->root_node)
    {
        p_bst->root_node = p_new_node;
        p_bst->root_node += 1;
        return (SUCCESS);   
    }
    
    /*Insert i non-empty BST */
    p_run = p_bst->root_node;
    while(TRUE)
    {
        if(new_data<=p_run->data)
        {
            if(NULL == p_run->left)
                break;
            p_run = p_run->left;
        }
        else
        {
            if(NULL == p_run->right)
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
status_t remove_bst(bst_t* p_bst, data_t* r_data)
{
    bst_node_t* z = NULL;
    bst_node_t* z_succ = NULL;

    z = search_node(p_bst, r_data);
    if(NULL == z)
        return (BST_DATA_NOT_FOUND);

    if(z->left == NULL)
        transpalnt(p_bst, z, z->right);
    else if(z->right == NULL)
        transpalnt(p_bst, z, z->left);
    else
    {
        z_succ = inorder_successor_nodelevel(z);
        if(z->right != z_succ)
        {
            transpalnt(p_bst, z_succ, z_succ->right);
            z_succ->right = z->right;
            z_succ->right->parent = z_succ;
        }
        transpalnt(p_bst, z, z_succ);
        z_succ->left = z->left;
        z_succ->left->parent = z_succ;
    }

    free(z);
    z = NULL;
    p_bst->nr_element -=1;

    return (SUCCESS);
}
status_t remove_bst_expanded(bst_t* p_bst, data_t r_data)
{
    bst_node_t* z;
    bst_node_t* z_succ = NULL;

    z = search_node(p_bst, r_data);
    if(z == NULL)
        return (BST_DATA_NOT_FOUND);

    if(z->left == NULL)
    {
        if(z->parent == NULL)
            p_bst->root_node = z->right;
        else if(z->parent->left == z)
            z->parent->left = z->right;
        else 
            z->parent->right = z->right;
        
        if(z->right)
            z->right->parent = z->parent;
    }
    else if(z->right == NULL)
    {
        if(z->parent  == NULL)
            p_bst->root_node = z->left;
        else if(z->parent->left == z)
            z->parent->left = z->left;
        else
            z->parent->right = z->right;
        
        z->left->parent = z->parent;
    }
    else
    {
        z_succ = inorder_successor_nodelevel(z);
        if(z->right != z)
        {
            z_succ->parent->left = z_succ->right;
            if(z_succ->right)
                z_succ->right->parent = z_succ->parent;
            
            z_succ->right = z->right;
            z_succ->left = z_succ->left;
        }

        if(z->parent == NULL)
            p_bst->root_node = z_succ;
        else if(z->parent->left == z)
            z->parent->left = z_succ;
        else
            z->parent->right = z_succ;
        z_succ->parent = z->parent;

        z_succ->left = z->left;
        z_succ->left->parent = z_succ;
    }

    free(z);
    z = NULL;
    p_bst->nr_element -= 1;
    
    return (SUCCESS);
}
status_t destroy(bst_t** pp_bst)
{
    bst_t* p_bst = NULL;

    p_bst = *pp_bst;
    if(NULL == p_bst)
        return (BST_EMPTY);
    destroy_nodelevel(p_bst->root_node);
    free(p_bst);
    *pp_bst = NULL;
    return (SUCCESS);
}

void inorder_traversal(bst_t* p_bst)
{
   printf("[START]->");
   inorder_traversal_nodelevel(p_bst->root_node);
   puts("[END]");
}

void preorder_traversal(bst_t* p_bst)
{
    printf("[START]->");
    preorder_traversal_nodelevel(p_bst->root_node);
    puts("[END]");
}
void postorder_traversal(bst_t* p_bst)
{
    printf("[START]->");
    postorder_traversal_nodelevel(p_bst->root_node);
    puts("[END]");
}


status_t max_bst(bst_t* p_bst, data_t* p_max_data)
{
    bst_node_t* p_max_node = NULL;

    if(NULL == p_bst->root_node)
        return (BST_EMPTY);
    p_max_node = max_bst_nodelevel(p_bst->root_node);

    *p_max_data = p_max_node->data;
    return (SUCCESS);
}

status_t min_bst(bst_t* p_bst, data_t* p_min_data)
{
    bst_node_t* p_min_node = NULL;

    if(NULL == p_bst->root_node)
        return (BST_EMPTY);
    
    p_min_node = min_bst_nodelevel(p_bst->root_node);
    *p_min_data = p_min_node->data;
    
    return (SUCCESS);  
}

height_t height_bst(bst_t* p_bst)
{
    return (height_bst_nodelevel(p_bst->root_node));
}
Bool search_bst(bst_t* p_bst, data_t search_data)
{
    return (NULL != search_node(p_bst, search_data));
}

status_t inorder_predecessor(bst_t* p_bst, data_t e_data, bst_node_t** pp_pred_node)
{
    bst_node_t* e_node = NULL;
    bst_node_t* p_pred_node = NULL;

    e_node = search_node(p_bst, e_data);
    if(NULL == e_node)
        return (BST_DATA_NOT_FOUND);
    
    p_pred_node = inorder_predecessor_nodelevel(e_node);
    if(NULL == p_pred_node)
        return (BST_NO_PREDECESSOR);
    *pp_pred_node = p_pred_node;
    
    return (SUCCESS);
}

status_t inorder_successor(bst_t* p_bst, data_t e_data, bst_node_t** pp_succ_node)
{
    bst_node_t* e_node = NULL;
    bst_node_t* p_succ_node = NULL;

    e_node = search_node(p_bst, e_data);
    if(NULL == e_node)
        return (BST_DATA_NOT_FOUND);
    
    p_succ_node = inorder_successor_nodelevel(e_node);
    
    if(NULL == p_succ_node)
        return (BST_NO_SUCCESSOR);
    *pp_succ_node = p_succ_node;
    
    return (SUCCESS);
}

void transpalnt(bst_t* p_bst, bst_node_t* u, bst_node_t* v)
{
    if(u->parent == NULL)
        p_bst->root_node = v;
    else if(u->parent->left == u)
        u->parent->left = v;
    else 
        u->parent->right = v;
    if(v)
        v->parent =u->parent;
        
}
void inorder_traversal_nodelevel(bst_node_t* root_node)
{
   if(NULL!=root_node)
   {
         inorder_traversal_nodelevel(root_node->left);
        printf("[%d]->", root_node->data);
        inorder_traversal_nodelevel(root_node->right);
   }
}

void preorder_traversal_nodelevel(bst_node_t* root_node)
{
    if(NULL!=root_node)
    {
            printf("[%d]->",root_node->data);
        preorder_traversal_nodelevel(root_node->left);
        preorder_traversal_nodelevel(root_node->right);
    }

}

void postorder_traversal_nodelevel(bst_node_t* root_node)
{
    if(NULL != root_node)
    {
        postorder_traversal_nodelevel(root_node->left);
        postorder_traversal_nodelevel(root_node->right);
        printf("%d]->", root_node);
    }
}

void destroy_nodelevel(bst_node_t* root_node)
{
    if(NULL!=root_node)
    {
        destroy_nodelevel(root_node->left);
        destroy_nodelevel(root_node->right);
        free(root_node);
    }
}
height_t height_bst_nodelevel(bst_node_t* root_node)
{
    height_t h_lst, h_rst, h_max;

    if(NULL != root_node)
        return (0);
    
    h_lst = height_bst_nodelevel(root_node->left);
    h_rst = height_bst_nodelevel(root_node->right);
    h_max = h_lst >h_rst ? h_lst : h_rst;
    return (h_max+1);
}
bst_node_t* max_bst_nodelevel(bst_node_t* root_node)
{
    if(NULL == root_node)
        return (root_node);
    
    while (NULL != root_node->left)
        root_node = root_node->left;
    
    return (root_node);
}

bst_node_t* min_bst_nodelevel(bst_node_t* root_node)
{
    if(NULL == root_node)
        return (root_node);
    while (root_node->left)
        root_node = root_node->left;
    
    return (root_node); 
}
bst_node_t* inorder_predecessor_nodelevel(bst_node_t* p_bst_node)
{
    bst_node_t *x, *y;

    x = p_bst_node;
    if(x->left != NULL)
    {
        y = max_bst_nodelevel(x->left);
        return (y);
    }

    y = x->parent;
    while(y!=NULL && y->left == x)
    {
        x = y;
        y = y->parent;
    }

    return (y);

}
bst_node_t* inorder_successor_nodelevel(bst_node_t* p_bst_node)
{
    bst_node_t *x, *y;

    x = p_bst_node;
    if(x->right!= NULL)
    {
        y = min_bst_nodelevel(x->right);
        return (y);
    }

    y = x->parent;
    while(y!=NULL && y->right == x)
    {
        x = y;
        y = y->parent;
    }

    return (y);
}

bst_node_t* search_node(bst_t* p_bst, data_t search_data)
{
    bst_node_t* p_run = NULL;

    p_run = p_bst->root_node;
    while(NULL!=p_run)
    {
        if(p_run->data == search_data)
            break;
        else if(search_data <= p_run->data)
            p_run = p_run->left;
        else    
            p_run = p_run->right;
    }
    return (p_run);
}
bst_node_t* get_node(data_t new_data)
{
    bst_node_t* p_new_node = NULL;

    p_new_node = xcalloc(1, sizeof(bst_node_t));
    p_new_node->data = new_data;

    return (p_new_node);
}
void* xcalloc(ssize_t nr_element, ssize_t size_per_element)
{
    void* p= NULL;

    p = calloc(nr_element, size_per_element);
    if(NULL == p)
    {
        fprintf(stderr, "Calloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }
    return (p);
}